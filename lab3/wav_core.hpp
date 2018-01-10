#include <vector>
#include <fstream>
#include <iostream>
#include "wav_header.hpp"
#include "wav_exceptions.hpp"

#ifndef LAB3_WAV_CORE_HPP
#define LAB3_WAV_CORE_HPP


class WavCore {
public:

    explicit WavCore(const std::string& filename);
    explicit WavCore(std::istream& stream);
    ~WavCore() = default;

    void initialize(const std::string& filename);
    void initialize(std::istream& stream);
    void printInfo() const;
    void makeWavFile(const std::string& filename);
    void changeHeader(const WavHeaderS& new_header);
    void changeData(const std::vector<std::vector<short>>& new_data);
    void makeMono();
    void cutSecondsFromBegin(float seconds);
    void cutSecondsFromEnd(float seconds);

private:

    static constexpr uint8_t default_chunk_id[4] = {'R','I','F','F'};
    static constexpr uint8_t default_format[4] = {'W','A','V','E'};
    static constexpr uint8_t default_subchunk_1_id[4] = {'f','m','t',' '};
    static constexpr uint8_t default_subchunk_2_id[4] = {'d','a','t','a'};
    static const uint8_t default_subchunk_1_size = 16;
    static const uint8_t default_audio_format = 1;
    static const uint8_t default_header_size = 44;
    static const uint8_t default_chunk_size = 8;
    static const uint8_t default_byte_size = 8;

    std::streampos getCountStream(std::streampos pos, std::istream& stream);
    void checkHeader() const;
    void checkRiff() const;
    void checkChunkSize() const;
    void checkFormat() const;
    void checkFmt() const;
    void checkSubchunk1() const;
    void checkRate() const;
    void checkBlockAlign() const;
    void checkSubchunk2() const;
    void readData(std::istream& filename);
    void readHeader(std::istream& filename);
    void clearHeader(WavHeaderS& d_header);
    void clearData(std::vector<std::vector<short>>& d_data);
    void changeFileSize(size_t size);
    void insertAllChannelsInData(const std::vector<short>& all_channels, int chan_count, int samples_per_chan);
    void checkParams();
    void updateHeader();
    uint32_t secondsToBytes(float seconds);

    std::size_t filesize;
    WavHeaderS header;
    std::vector<std::vector<short>> channels_data;
};

#endif //LAB3_WAV_CORE_HPP
