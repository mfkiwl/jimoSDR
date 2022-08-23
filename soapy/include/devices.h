#pragma once

#include "device.h"

namespace soapy
{
    class devices
    {
        public:
            devices() = delete;
            devices(const devices&) = delete;
            devices(devices&&) = delete;
            devices& operator=(const devices&) = delete;
            devices&& operator=(devices&&) = delete;
            static std::vector<device> get_devices();
    };
}