#pragma once

#include <xtd/xtd>

namespace jimo_sdr
{
    class GotSampleRatesEventArgs : public xtd::event_args
    {
        public:
            GotSampleRatesEventArgs(const std::vector<double>& rates) : m_rates(rates) {}
            inline std::vector<double> Rates() const noexcept { return m_rates; };
        private:
            std::vector<double> m_rates;
    };
}