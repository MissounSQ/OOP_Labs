#ifndef LAB3_WAV_HEADER_HPP
#define LAB3_WAV_HEADER_HPP
#include <cstdint>

struct WavHeaderS {
    int8_t chunk_id[4];
    uint32_t chunk_size;
    int8_t format[4];
    int8_t subchunk_1_id[4];
    uint32_t subchunk_1_size;
    uint16_t audio_format;
    uint16_t num_channels;
    uint32_t sample_rate;
    uint32_t byte_rate;
    uint16_t block_align;
    uint16_t bits_per_sample;
    int8_t subchunk_2_id[4];
    uint32_t subchunk_2_size;
};

#endif //LAB3_WAV_HEADER_HPP
