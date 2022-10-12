/// @copyright Copyright © 2022 Jim Orcheson. Available under the MIT License.
#pragma once
#include "digit_incrementer.h"

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
        protected:
            virtual void create_controls();
        private:
            std::vector<std::unique_ptr<digit_incrementer>> digits_incrementers_;
            std::vector<std::unique_ptr<digit_incrementer>> decimals_incrementers_; 
            xtd::forms::label decimal_point;
    };
}