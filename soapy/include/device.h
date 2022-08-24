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
                rx = SOAPY_SDR_RX,
                tx = SOAPY_SDR_TX
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
            size_t number_of_channels(const direction dir) const;
            std::map<std::string, std::string> channel_info(const direction dir, 
                const size_t channel) const;
            bool full_duplex(const direction dir, const size_t channel) const;
            const std::vector<std::string> stream_formats(const direction dir,
                const size_t channel) const;
        private:
            std::map<std::string, std::string> _properties;
            SoapySDR::Device* _device;
    };
}