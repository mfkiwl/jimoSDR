#pragma once

#include <xtd/xtd>

namespace jimo_sdr
{
    class NumberDisplayValueChangedEventArgs : public xtd::event_args
    {
        public:
            NumberDisplayValueChangedEventArgs(double newValue) : m_newValue(newValue) {}
            inline double Value() const { return m_newValue; }
        private:
            double m_newValue;
    };
}