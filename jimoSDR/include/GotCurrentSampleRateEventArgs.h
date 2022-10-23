#pragma once

#include <xtd/xtd>

namespace jimo_sdr
{
    class GotCurrentSampleRateEventArgs : public xtd::event_args
    {
        public:
            GotCurrentSampleRateEventArgs(const double rate) : m_rate(rate) {}
            inline double Rate() const noexcept { return m_rate; };
        private:
            double m_rate;
    };
}