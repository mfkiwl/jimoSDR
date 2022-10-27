/// @copyright Copyright © 2022 Jim Orcheson. Available under the MIT License.
#pragma once
#include "DigitIncrementer.h"

namespace jimo_sdr
{
    class number_display : public xtd::forms::panel
    {
        public:
            number_display();
            number_display(uint32_t number_of_digits);
            number_display(uint32_t number_of_digits, uint32_t number_of_decimals);
            virtual uint32_t decimals() const noexcept;
            virtual number_display& decimals(uint32_t number_of_decimals);
            virtual uint32_t digits() const noexcept;
            /// @brief Set the number of digits.
            virtual number_display& digits(uint32_t number_of_digits);
            virtual void SetValue(double value) noexcept;
        protected:
            virtual void create_controls();
        private:
            std::vector<std::unique_ptr<DigitIncrementer>> digits_incrementers_;
            std::vector<std::unique_ptr<DigitIncrementer>> decimals_incrementers_; 
            xtd::forms::label decimal_point;
    };
}