#pragma once

#include <memory>
#include <optional>
#include "Device.h"
#include "sampling_mode.h"

namespace jimo_sdr
{
    class device_properties
    {
        public:
            device_properties(std::shared_ptr<sdr::Device> device = nullptr);
            device_properties(const device_properties&) = delete;
            device_properties(device_properties&&) = delete;
            device_properties& operator=(const device_properties) = delete;
            device_properties&& operator=(device_properties&&) = delete;
            void clear() noexcept;
            std::shared_ptr<sdr::Device> Device() { return _device; }
            void device(std::shared_ptr<sdr::Device> dev) { _device = dev; }
            inline double CenterFrequency() { return m_centerFrequency; }
            inline void CenterFrequency(double frequency) { m_centerFrequency = frequency; }
            double& sample_rate() { return _sample_rate; }
            void sample_rate(double rate) { _sample_rate = rate; }
            sampling_mode& sampling_mode() { return _sampling_mode; }
            void sampling_mode(class sampling_mode mode) { _sampling_mode = mode; }
        private:
            std::shared_ptr<sdr::Device> _device;
            double m_centerFrequency;
            double _sample_rate;
            class sampling_mode _sampling_mode;
    };
}