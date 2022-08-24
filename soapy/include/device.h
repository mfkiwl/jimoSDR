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
            const std::string operator[](const std::string& key) const;
            operator std::map<std::string, std::string>() { return _properties; }
            const std::string driver_key() const;
        private:
            std::map<std::string, std::string> _properties;
            SoapySDR::Device* _device;
    };
}