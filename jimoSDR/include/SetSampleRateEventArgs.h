#pragma once

#include <xtd/xtd>

namespace jimo_sdr
{
    class SetSampleRateEventArgs : public xtd::event_args
    {
        public:
            SetSampleRateEventArgs(const double requestedRate, const double actualRate) 
                : m_requestedRate(requestedRate), m_actualRate(actualRate) {}
            inline double RequestedRate() const noexcept { return m_requestedRate; }
            inline double ActualRate() const noexcept { return m_actualRate; }
        private:
            double m_requestedRate;
            double m_actualRate;
    };
}