/// @copyright Copyright © 2022 Jim Orcheson. Available under the MIT License.
#pragma once
#include "DigitIncrementer.h"

namespace jimo_sdr
{
    class NumberDisplay : public xtd::forms::panel
    {
        public:
            NumberDisplay();
            NumberDisplay(uint32_t number_of_digits);
            NumberDisplay(uint32_t number_of_digits, uint32_t number_of_decimals);
            virtual uint32_t Decimals() const noexcept;
            virtual NumberDisplay& Decimals(uint32_t number_of_decimals);
            virtual uint32_t Digits() const noexcept;
            virtual NumberDisplay& Digits(uint32_t number_of_digits);
            virtual void SetValue(double value) noexcept;
        protected:
            virtual void CreateControls();
        private:
            std::vector<std::unique_ptr<DigitIncrementer>> m_digitsIncrementers;
            std::vector<std::unique_ptr<DigitIncrementer>> m_decimalsIncrementers; 
            xtd::forms::label decimal_point;
    };
}