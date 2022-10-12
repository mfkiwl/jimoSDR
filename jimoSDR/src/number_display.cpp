#include "number_display.h"

namespace jimo_sdr
{
    constexpr uint32_t maximum_number_of_digits = 15;
    constexpr uint32_t maximum_number_of_decimals = 3;

    number_display::number_display() : number_display(0, 0) {}

    number_display::number_display(uint32_t number_of_digits) : number_display(number_of_digits, 0) {}
    
    number_display::number_display(uint32_t number_of_digits, uint32_t number_of_decimals)
    {
        digits(number_of_digits);
        decimals(number_of_decimals);
        decimal_point.text(".");
        decimal_point.width(3);
        decimal_point.text_align(xtd::forms::content_alignment::bottom_center);
        decimal_point.back_color(xtd::drawing::color::transparent);
    }


    uint32_t number_display::digits() const noexcept
    {
        return digits_incrementers_.size();
    }

    number_display& number_display::digits(uint32_t number_of_digits)
    {
        if (number_of_digits > maximum_number_of_digits)
        {
            std::stringstream ss;
            ss << R"(The number of digits that can be displayed is between 0 and 15, but )";
            ss << number_of_digits << R"( was requested.)";
            xtd::diagnostics::stack_frame frame;
            throw xtd::argument_out_of_range_exception(ss.str(), frame);
        }
        digits_incrementers_.clear();
        for (uint32_t digits = 0; digits < number_of_digits; ++digits)
        {
            digits_incrementers_.push_back(std::make_unique<digit_incrementer>());
        }
        create_controls();
        return *this;
    }

    uint32_t number_display::decimals() const noexcept
    {
        return decimals_incrementers_.size();
    }

    number_display& number_display::decimals(uint32_t number_of_decimals)
    {
        if (number_of_decimals > maximum_number_of_decimals)
        {
            std::stringstream ss;
            ss << R"(The number of decimals that can be displayed is between 0 and 3, but )";
            ss << number_of_decimals << R"( was requested.)";
            xtd::diagnostics::stack_frame frame;
            throw xtd::argument_out_of_range_exception(ss.str(), frame);
        }
        decimals_incrementers_.clear();

        for (uint32_t decimals = 0; decimals < number_of_decimals; ++decimals)
        {
            decimals_incrementers_.push_back(std::make_unique<digit_incrementer>());
        }
        create_controls();
        return *this;
    }

    void number_display::create_controls()
    {
        controls().clear();
        int32_t x_pos = 0;
        for (auto& digit : digits_incrementers_)
        {
            digit->location( {x_pos, 0} );
            x_pos += digit->width();
            controls().push_back(*digit);
        }
        if (decimals_incrementers_.size() > 0)
        {
            decimal_point.height(decimals_incrementers_[0]->height());
            *this << decimal_point;
            decimal_point.location( {x_pos, 0} );
            x_pos += decimal_point.width();
            for(auto& decimal : decimals_incrementers_)
            {
                decimal->location( {x_pos, 0} );
                x_pos += decimal->width();
                controls().push_back(*decimal);
            }
        }
    }
}