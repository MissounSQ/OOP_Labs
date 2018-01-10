#ifndef LAB3_WAV_EXCEPTIONS_HPP
#define LAB3_WAV_EXCEPTIONS_HPP
#include <exception>
#include <iostream>

class IO_ERR_EXC : std::runtime_error {
public:
    explicit IO_ERR_EXC(const std::string &what_arg) : std::runtime_error(what_arg) {}
};

class BAD_FORMAT : std::runtime_error {
public:
    explicit BAD_FORMAT(const std::string &what_arg) : std::runtime_error(what_arg) {}
};

class UNSUPPORTED_FORMAT : std::runtime_error {
public:
    explicit UNSUPPORTED_FORMAT(const std::string &what_arg) : std::runtime_error(what_arg) {}
};

class BAD_PARAMS : std::runtime_error {
public:
    explicit BAD_PARAMS(const std::string &what_arg) : std::runtime_error(what_arg) {}
};

class DATA_SIZE_ERROR : std::runtime_error {
public:
    explicit DATA_SIZE_ERROR(const std::string &what_arg) : std::runtime_error(what_arg) {}
};

class HEADER_RIFF_ERROR : std::runtime_error {
public:
    explicit HEADER_RIFF_ERROR(const std::string &what_arg) : std::runtime_error(what_arg) {}
};

class HEADER_FILE_SIZE_ERROR : std::runtime_error {
public:
    explicit HEADER_FILE_SIZE_ERROR(const std::string &what_arg) : std::runtime_error(what_arg) {}
};

class HEADER_WAVE_ERROR : std::runtime_error {
public:
    explicit HEADER_WAVE_ERROR(const std::string &what_arg) : std::runtime_error(what_arg) {}
};

class HEADER_FMT_ERROR : std::runtime_error {
public:
    explicit HEADER_FMT_ERROR(const std::string &what_arg) : std::runtime_error(what_arg) {}
};

class HEADER_NOT_PCM : std::runtime_error {
public:
    explicit HEADER_NOT_PCM(const std::string &what_arg) : std::runtime_error(what_arg) {}
};

class HEADER_SUBCHUNK1_ERROR : std::runtime_error {
public:
    explicit HEADER_SUBCHUNK1_ERROR(const std::string &what_arg) : std::runtime_error(what_arg) {}
};

class HEADER_BYTES_RATE_ERROR : std::runtime_error {
public:
    explicit HEADER_BYTES_RATE_ERROR(const std::string &what_arg) : std::runtime_error(what_arg) {}
};

class HEADER_BLOCK_ALIGN_ERROR : std::runtime_error {
public:
    explicit HEADER_BLOCK_ALIGN_ERROR(const std::string &what_arg) : std::runtime_error(what_arg) {}
};

class HEADER_SUBCHUNK2_SIZE_ERROR : std::runtime_error {
public:
    explicit HEADER_SUBCHUNK2_SIZE_ERROR(const std::string &what_arg) : std::runtime_error(what_arg) {}
};




#endif //LAB3_WAV_EXCEPTIONS_HPP
