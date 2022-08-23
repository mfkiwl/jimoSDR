#pragma once

#include "SoapySDR/Device.hpp"
#include <string>
#include <map>
#include <vector>

namespace soapy
{
    class device
    {
        public:
            device() = delete;
            device(const SoapySDR::Kwargs& kwargs);
            device(const device&) = delete;
            device(device&&);
            ~device() noexcept; 
            device& operator=(const device&) = delete;
            device&& operator=(device&&) = delete;
        private:
            std::map<std::string, std::string> _kwargs;
            SoapySDR::Device* _device;
    };
}