#pragma once

#include <exception>

namespace jimo_sdr
{
    class no_sdrs_exception : public std::exception
    {
        public:
            const char* what() const noexcept override { return "Cannot get an SDR"; };
    };
}