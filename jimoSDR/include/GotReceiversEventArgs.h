#pragma once

#include <xtd/xtd>
#include "Devices.h"

namespace jimo_sdr
{
    class GotReceiversEventArgs : public xtd::event_args
    {
        public:
            GotReceiversEventArgs(sdr::devices& devices) : m_devices(devices) {}
            inline sdr::devices Devices() const noexcept { return m_devices; };
        private:
            sdr::devices m_devices;
    };
}