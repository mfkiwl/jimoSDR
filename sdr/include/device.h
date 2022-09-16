#pragma once

#include "SoapySDR/Device.hpp"
#include "SoapySDR/Constants.h"
#include <string>
#include <map>
#include <vector>
#include <memory>
#include "types.h"

namespace sdr
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
            device(device&&) = delete;
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
            const std::tuple<std::string, double> native_stream_format(
                const direction dir, const size_t channel) const;
            std::vector<sdr_arg_info> stream_args_info(const direction dir,
                const size_t channel) const;
            double center_frequency(const direction dir, const size_t channel) const;
            double sample_rate(const direction dir, const size_t channel) const;
            void sample_rate(const direction dir, const size_t channel,
                const double rate);
            std::vector<double> sample_rates(const direction dir,
                const size_t channel) const;
            std::vector<std::string> gpio_banks() const;
            std::vector<std::string> register_interfaces() const;
        private:
            std::map<std::string, std::string> _properties;
            SoapySDR::Device* _device;
    };
}