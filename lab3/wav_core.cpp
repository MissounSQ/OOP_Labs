#include <cstring>
#include "wav_core.hpp"

WavCore::WavCore(const std::string &filename) {
    initialize(filename);
}

WavCore::WavCore(std::istream &stream) {
    initialize(stream);
}

void WavCore::printInfo() const {
    std::cout <<  "-------------------------\n";
    std::cout << " audioFormat   " << header.audio_format << std::endl;
    std::cout << " numChannels   " << header.num_channels << std::endl;
    std::cout << " sampleRate    " << header.sample_rate << std::endl;
    std::cout << " bitsPerSample " << header.bits_per_sample << std::endl;
    std::cout << " byteRate      " << header.byte_rate << std::endl;
    std::cout << " blockAlign    " << header.block_align << std::endl;
    std::cout << " chunkSize     " << header.chunk_size << std::endl;
    std::cout << " subchunk1Size " << header.subchunk_1_size << std::endl;
    std::cout << " subchunk2Size " << header.subchunk_2_size << std::endl;
    std::cout << "-------------------------\n";
}

void WavCore::initialize(const std::string &filename) {
    std::ifstream stream(filename, std::ios::binary);
    if(stream.fail())
        throw IO_ERR_EXC("Can't open file " + filename);
    initialize(stream);
}

void WavCore::initialize(std::istream &stream) {
    if(!stream)
        throw IO_ERR_EXC("Stream does not exist");
    clearData(channels_data);
    clearHeader(header);
    readHeader(stream);
    readData(stream);
}

void WavCore::clearData(std::vector<std::vector<short>> &d_data) {
    d_data.clear();
}

void WavCore::clearHeader(WavHeaderS &d_header) {
    memset(&d_header, 0, sizeof(WavHeaderS));
}

void WavCore::readHeader(std::istream &stream) {
    WavHeaderS temp{};
    clearHeader(temp);
    stream.flags((std::ios_base::fmtflags) std::ios::binary);
    stream.read(reinterpret_cast<char*>(&temp), sizeof(header));
    if(stream.gcount() != sizeof(temp))
        throw BAD_FORMAT("Bad file format");
    changeHeader(temp);

    size_t size = static_cast<size_t>(getCountStream(0, stream));
    changeFileSize(size);
    checkHeader();
}

std::streampos WavCore::getCountStream(std::streampos pos, std::istream &stream) {
    std::streampos size;
    stream.seekg(0, std::ios::end);
    size = stream.tellg() - pos;
    return size;
}

void WavCore::changeHeader(const WavHeaderS &new_header) {
    header = new_header;
}

void WavCore::changeData(const std::vector<std::vector<short>> &new_data) {
    channels_data = new_data;
}

void WavCore::changeFileSize(size_t size) {
    filesize = size;
}

void WavCore::checkHeader() const {
    checkRiff();
    checkFormat();
    checkChunkSize();
    checkFmt();
    checkSubchunk1();
    checkRate();
    checkBlockAlign();
    checkSubchunk2();
}

void WavCore::checkRiff() const {
    if(header.chunk_id[0] != default_chunk_id[0] ||
       header.chunk_id[1] != default_chunk_id[1] ||
       header.chunk_id[2] != default_chunk_id[2] ||
       header.chunk_id[3] != default_chunk_id[3])
        throw HEADER_RIFF_ERROR("RIFF error");
}

void WavCore::checkFormat() const {
    if(header.format[0] != default_format[0] ||
       header.format[1] != default_format[1] ||
       header.format[2] != default_format[2] ||
       header.format[3] != default_format[3])
        throw HEADER_WAVE_ERROR("WAVE error");
}

void WavCore::checkChunkSize() const {
    if(header.chunk_size != filesize - default_chunk_size)
        throw HEADER_FILE_SIZE_ERROR("Wrong file size");
}

void WavCore::checkFmt() const {
    if (header.subchunk_1_id[0] != default_subchunk_1_id[0] ||
        header.subchunk_1_id[1] != default_subchunk_1_id[1] ||
        header.subchunk_1_id[2] != default_subchunk_1_id[2] ||
        header.subchunk_1_id[3] != default_subchunk_1_id[3] ||
        header.subchunk_2_id[0] != default_subchunk_2_id[0] ||
        header.subchunk_2_id[1] != default_subchunk_2_id[1] ||
        header.subchunk_2_id[2] != default_subchunk_2_id[2] ||
        header.subchunk_2_id[3] != default_subchunk_2_id[3])
        throw HEADER_FMT_ERROR("FMT error");
}

void WavCore::checkSubchunk1() const {
    if(header.subchunk_1_size != default_subchunk_1_size)
        throw HEADER_SUBCHUNK1_ERROR("Subchunk1 size error");
}

void WavCore::checkRate() const {
    if(header.byte_rate != header.sample_rate * header.num_channels * header.bits_per_sample / default_byte_size)
        throw HEADER_BYTES_RATE_ERROR("Byterate error");
}

void WavCore::checkBlockAlign() const {
    if(header.block_align != header.num_channels * header.bits_per_sample / default_byte_size)
        throw HEADER_BLOCK_ALIGN_ERROR("Block align error");
}

void WavCore::checkSubchunk2() const {
    if(header.subchunk_2_size != filesize - default_header_size)
        throw HEADER_SUBCHUNK2_SIZE_ERROR("Subchunk2 size erorr");
}

void WavCore::readData(std::istream &stream) {
    stream.flags((std::ios_base::fmtflags) std::ios::binary);
    stream.seekg(sizeof(WavHeaderS));
    if(header.bits_per_sample != 16 && header.bits_per_sample != 8)
        throw UNSUPPORTED_FORMAT("Only 16-bit and 8-bit samples is supported");
    int chan_count = header.num_channels;
    int samples_per_chan = (header.subchunk_2_size / sizeof(short)) / chan_count;
    std::vector<short> all_channels;
    all_channels.resize(static_cast<unsigned int>(chan_count * samples_per_chan));
    stream.read((char*)all_channels.data(), header.subchunk_2_size);
    auto bytes = static_cast<size_t>(stream.gcount());
    auto bytes_count = static_cast<size_t>(getCountStream(sizeof(WavHeaderS), stream));
    if(bytes != bytes_count)
        throw IO_ERR_EXC("Can't read all data");
    insertAllChannelsInData(all_channels,chan_count, samples_per_chan);
}

void WavCore::insertAllChannelsInData(const std::vector<short> &all_channels, int chan_count, int samples_per_chan) {
    channels_data.resize(static_cast<unsigned int>(chan_count));
    for(auto& it : channels_data)
        it.resize(static_cast<unsigned int>(samples_per_chan));
    for(int i = 0; i < chan_count; i++)
        for(int j = 0; j < samples_per_chan; j++)
            channels_data[i][j] = all_channels[chan_count * j + i];
}

void WavCore::makeMono() {
    try {
        checkParams();
    }
    catch (std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }
    std::vector<std::vector<short>> dest_mono(1);
    dest_mono[0].resize(channels_data[0].size());
    for(size_t i = 0; i < channels_data[0].size(); i++)
        dest_mono[0][i] = static_cast<short>((channels_data[0][i] + channels_data[1][i]) / 2);
    changeData(dest_mono);
    updateHeader();
}

void WavCore::checkParams() {
    int chan_count = channels_data.size();
    if(chan_count != 2)
        throw BAD_PARAMS("Chan count isn't equal 2");
    int samples_count_per_chan = channels_data[0].size();
    for(size_t i = 0; i < chan_count; i++)
        if(channels_data[i].size() != samples_count_per_chan)
            BAD_PARAMS("Channels haven't the same number of samples");
}

void WavCore::updateHeader() { 
    size_t subchunk_size = 0;
    for(auto& it : channels_data)
        subchunk_size += it.size();
    header.subchunk_2_size = reinterpret_cast<unsigned int>(subchunk_size * sizeof(short));
    header.chunk_size = default_header_size - default_chunk_size + header.subchunk_2_size;
    header.num_channels = static_cast<uint16_t>(channels_data.size());
    changeFileSize(default_header_size + header.subchunk_2_size);
    header.byte_rate = header.sample_rate * header.num_channels * header.bits_per_sample / default_byte_size;
    header.block_align = header.num_channels * header.bits_per_sample / default_byte_size;
}

void WavCore::cutSecondsFromBegin(float seconds) {
    uint32_t bytes = secondsToBytes(seconds);
    for(auto& it : channels_data)
        it.erase(it.begin(), it.begin() + bytes);
    updateHeader();
}

void WavCore::cutSecondsFromEnd(float seconds) {
    uint32_t bytes = secondsToBytes(seconds);
    for(auto& it : channels_data)
        it.erase(it.end() - bytes, it.end());
    updateHeader();
}

uint32_t WavCore::secondsToBytes(float seconds) {
    auto bytes = static_cast<uint32_t>(
            ((header.bits_per_sample / default_byte_size) * header.sample_rate * seconds) / sizeof(short));
    return bytes;
}

void WavCore::makeWavFile(const std::string &filename) {
    checkHeader();
    std::ofstream stream(filename, std::ios::binary);
    if(stream.fail())
        throw IO_ERR_EXC("Can't create output stream");
    std::vector<short> all_channels(header.num_channels * channels_data[0].size());
    for(int i = 0; i < header.num_channels; i++)
        for(int j = 0; j < channels_data[0].size(); j++)
            all_channels[header.num_channels * j + i] = channels_data[i][j];
    stream.write((char*)&header, sizeof(WavHeaderS));
    stream.write((char*)all_channels.data(), header.subchunk_2_size);
    stream.close();
}




