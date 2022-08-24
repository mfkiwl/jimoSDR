#pragma once

#include "SoapySDR/Device.hpp"
#include "SoapySDR/Constants.h"
#include <string>
#include <map>
#include <vector>

namespace soapy
{
    class device
    {
        public:
            enum class direction
            {
                RX = SOAPY_SDR_RX,
                TX = SOAPY_SDR_TX
            };

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
            const std::string hardware_key() const;
            const std::map<std::string, std::string> hardware_info() const;
            const std::string frontend_mapping(const direction dir) const;
        private:
            std::map<std::string, std::string> _properties;
            SoapySDR::Device* _device;
    };
}