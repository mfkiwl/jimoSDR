#pragma once

#include <xtd/xtd>
#include "Devices.h"

namespace jimo_sdr
{
    class GotCenterFrequencyEventArgs : public xtd::event_args
    {
        public:
            GotCenterFrequencyEventArgs(double frequency) : m_centerFrequency(frequency) {}
            inline double CenterFrequency() const noexcept { return m_centerFrequency; };
        private:
            double m_centerFrequency;
    };
}