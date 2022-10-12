/// @file number_display.h
/// @brief Contains the jimo::jxtd::number_display control
/// @copyright Copyright © 2022 Jim Orcheson. Available under the MIT License.
#pragma once
#include "digit_incrementer.h"

/// @brief The jimo::jxtd namespace contains control classes that add to the classes contained in the xtd::forms namespace.
namespace jimo::jxtd
{
    /// @par Namespace
    /// jimo::jxtd
    /// @par Library
    /// libjxtd
    /// @par Examples
    /// The following code demonstrates the use of the number_display control.
    /// @include number_display/src/number_display.cpp

    /// @brief Displays a set of digit_incrementers horizontally.
    class number_display : public xtd::forms::panel
    {
        public:
            /// @name Constructors

            /// @{
            /// @brief Initialize a new instance of number_display.
            number_display();
            /// @brief Initialize a new instance of number_display.
            /// @param number_of_digits The number of digits to display (the number of digit_incrementers to
            /// the left of the decimal point).
            /// @remark The number of digits is limited to the range 0 to 15.
            /// @exception Throws xtd::argument_out_of_range_exception if the number of digits requested is
            /// greater than 15.
            number_display(uint32_t number_of_digits);
            /// @brief Initialize a new instance of number_display.
            /// @param number_of_digits The number of digits to display (the number of digit_incrementers to
            /// the left of the decimal point).
            /// @param number_of_decimals The number of decimal places to display (the number of
            /// digit_incrementers to display to the right of the decimal point).
            /// @remark The number of digits is limited to the range 0 to 15.
            /// @exception Throws xtd::argument_out_of_range_exception if the number of digits requested is
            /// greater than 15, or if the number of decimals is greater than 3.
            number_display(uint32_t number_of_digits, uint32_t number_of_decimals);
            /// @}
            /// @name Properties

            /// @{
            /// @brief Retrieve the number of decimal places.
            /// @returns The number of decimal places being displayed.
            virtual uint32_t decimals() const noexcept;
            /// @brief Set the number of decimal places.
            /// @param number_of_decimals The number of decimal digits to set
            /// @returns Reference to the number_display object. This allows chaining of property calls
            /// together.
            /// @exception Throws xtd::argument_out_of_range_exception if the number of decimals requested is
            /// greater than 3.
            virtual number_display& decimals(uint32_t number_of_decimals);
            /// @brief Retrieve the number of digits.
            /// @returns The number of digits being displayed.
            virtual uint32_t digits() const noexcept;
            /// @brief Set the number of digits.
            /// @param number_of_digits The number of digits to set
            /// @returns Reference to the number_display object. This allows chaining of property calls
            /// together.
            /// @exception Throws xtd::argument_out_of_range_exception if the number of digits requested is
            /// greater than 15.
            virtual number_display& digits(uint32_t number_of_digits);
            /// @}
        protected:
            /// @brief Create digit_incrementers, number separators, and decimal points.
            ///
            /// The number_display object is automatically resized to fit the number of controls.
            /// @remarks This method is called when the number_display is created and every time that the
            /// digits and decimals methods are called.
            virtual void create_controls();
        private:
            std::vector<std::unique_ptr<digit_incrementer>> digits_incrementers_;
            std::vector<std::unique_ptr<digit_incrementer>> decimals_incrementers_; 
            xtd::forms::label decimal_point;
    };
}