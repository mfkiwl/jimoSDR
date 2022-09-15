#pragma once

#include <memory>
#include <optional>
#include "device.h"

namespace jimo_sdr
{
    class device_properties
    {
        public:
            enum sampling_mode
            {
                quadrature,
                i_branch,
                q_branch
            };
            device_properties(std::shared_ptr<soapy::device> device = nullptr);
            device_properties(const device_properties&) = delete;
            device_properties(device_properties&&) = delete;
            device_properties& operator=(const device_properties) = delete;
            device_properties&& operator=(device_properties&&) = delete;
            std::shared_ptr<soapy::device> device() { return _device; }
            void device(std::shared_ptr<soapy::device> dev) { _device = dev; }
            double sample_rate() { return _sample_rate; }
            void sample_rate(double rate) { _sample_rate = rate; }
            sampling_mode sampling_mode() { return _sampling_mode; }
            void sampling_mode(enum sampling_mode mode) { _sampling_mode = mode; }
        private:
            std::shared_ptr<soapy::device> _device;
            double _sample_rate;
            enum sampling_mode _sampling_mode;
    };
}