#pragma once

#include <xtd/xtd>
#include "Devices.h"

namespace jimo_sdr
{
    class GotDeviceDriverKeyEventArgs : public xtd::event_args
    {
        public:
            GotDeviceDriverKeyEventArgs(std::string key) : m_driverKey(key) {}
            inline std::string DriverKey() const noexcept { return m_driverKey; };
        private:
            std::string m_driverKey;
    };
}