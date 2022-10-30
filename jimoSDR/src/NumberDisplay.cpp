#include "NumberDisplay.h"
#include "ControlProperties.h"
#include <sstream>
#include <string>

namespace jimo_sdr
{
    constexpr uint32_t maximum_number_of_digits = 15;
    constexpr uint32_t maximum_number_of_decimals = 3;
    constexpr uint32_t decimalPointWidth = 3;
    constexpr uint32_t incrementerSeparatorWidth = 1;

    NumberDisplay::NumberDisplay() : NumberDisplay(0, 0) {}

    NumberDisplay::NumberDisplay(uint32_t number_of_digits) : NumberDisplay(number_of_digits, 0) {}
    
    NumberDisplay::NumberDisplay(uint32_t number_of_digits, uint32_t number_of_decimals)
    {
        back_color(xtd::drawing::color::black);
        decimal_point.text(".");
        decimal_point.width(decimalPointWidth);
        decimal_point.text_align(xtd::forms::content_alignment::bottom_center);
        decimal_point.back_color(xtd::drawing::color::black);
        decimal_point.fore_color(xtd::drawing::color::white);
        Digits(number_of_digits);
        Decimals(number_of_decimals);
    }


    uint32_t NumberDisplay::Digits() const noexcept
    {
        return m_digitsIncrementers.size();
    }

    NumberDisplay& NumberDisplay::Digits(uint32_t number_of_digits)
    {
        if (number_of_digits > maximum_number_of_digits)
        {
            std::stringstream ss;
            ss << R"(The number of digits that can be displayed is between 0 and 15, but )";
            ss << number_of_digits << R"( was requested.)";
            xtd::diagnostics::stack_frame frame;
            throw xtd::argument_out_of_range_exception(ss.str(), frame);
        }
        m_digitsIncrementers.clear();
        for (uint32_t digits = 0; digits < number_of_digits; ++digits)
        {
            m_digitsIncrementers.push_back(std::make_unique<DigitIncrementer>());
        }
        CreateControls();
        return *this;
    }

    uint32_t NumberDisplay::Decimals() const noexcept
    {
        return m_decimalsIncrementers.size();
    }

    NumberDisplay& NumberDisplay::Decimals(uint32_t number_of_decimals)
    {
        if (number_of_decimals > maximum_number_of_decimals)
        {
            std::stringstream ss;
            ss << R"(The number of decimals that can be displayed is between 0 and 3, but )";
            ss << number_of_decimals << R"( was requested.)";
            xtd::diagnostics::stack_frame frame;
            throw xtd::argument_out_of_range_exception(ss.str(), frame);
        }
        m_decimalsIncrementers.clear();

        for (uint32_t decimals = 0; decimals < number_of_decimals; ++decimals)
        {
            m_decimalsIncrementers.push_back(std::make_unique<DigitIncrementer>());
        }
        CreateControls();
        return *this;
    }

    void NumberDisplay::CreateControls()
    {
        controls().clear();
        int32_t x_pos = 0;
        for (auto& digit : m_digitsIncrementers)
        {
            digit->location( {x_pos, 0} );
            x_pos += digit->width()+ incrementerSeparatorWidth;
            controls().push_back(*digit);
        }
        if (m_decimalsIncrementers.size() > 0)
        {
            decimal_point.height(m_decimalsIncrementers[0]->height());
            controls().push_back(decimal_point);
            decimal_point.location( {x_pos, 0} );
            x_pos += decimal_point.width();
            for(auto& decimal : m_decimalsIncrementers)
            {
                decimal->location( {x_pos, 0} );
                x_pos += decimal->width() + incrementerSeparatorWidth;
                controls().push_back(*decimal);
            }
        }
    }

    void NumberDisplay::SetValue(double value) noexcept
    {
        value += 0.123;
        std::stringstream ss;
        ss.setf(std::ios::fixed, std::ios::floatfield);
        ss.precision(m_decimalsIncrementers.size());
        ss.fill('0');
        std::streamsize width = m_digitsIncrementers.size();
        if (m_decimalsIncrementers.size() > 0)
        {
            // 1 is needed for decimal point
            width += m_decimalsIncrementers.size() + incrementerSeparatorWidth;
        }
        ss.width(width);
        ss << value;

        for (int32_t index = m_digitsIncrementers.size() - 1; index >= 0; --index)
        {
            char val = ss.str()[index];
            int32_t digit = std::atoi(&val);
            m_digitsIncrementers[index]->Value(digit);
        }
        for (size_t index = 0; index < m_decimalsIncrementers.size(); ++index)
        {
            char val = ss.str()[width - index - 1];
            int32_t decimal = std::atoi(&val);
            m_decimalsIncrementers[m_decimalsIncrementers.size() - index - 1]->Value(decimal);
        }
    }

    NumberDisplay& NumberDisplay::height(int32_t newHeight)
    {
        auto newWidth = (newHeight * digitIncrementerMinimumWidth) / digitIncrementerMinimumHeight; 
        if (newHeight < digitIncrementerMinimumHeight)
        {
            newHeight = digitIncrementerMinimumHeight;
            newWidth = digitIncrementerMinimumWidth;
        }
        else if (newHeight > digitIncrementerMaximumHeight)
        {
            newHeight = digitIncrementerMaximumHeight;
            newWidth = digitIncrementerMaximumWidth;
        }
        int32_t xPos = 0;
        int32_t yPos = (controlsPanelHeight - newHeight) / 2;
        for (auto& digit : m_digitsIncrementers)
        {
            digit->size({ newWidth, newHeight });
            digit->location({ xPos, yPos });
            xPos += newWidth + incrementerSeparatorWidth;
        }
        if (m_decimalsIncrementers.size() > 0)
        {
            decimal_point.height(newHeight);
            decimal_point.location({ xPos, yPos });
            xPos += decimal_point.width();
            for (auto& decimal : m_decimalsIncrementers)
            {
                decimal->size({ newWidth, newHeight });
                decimal->location({ xPos, yPos });
                xPos += newWidth + incrementerSeparatorWidth;
            }
        }
        return *this;
    }

    int32_t NumberDisplay::width() const noexcept
    {
        int32_t width = 0; 
        if (m_digitsIncrementers.size() > 0)
        {
            width += m_digitsIncrementers.size() * 
                (m_digitsIncrementers[0]->width() + incrementerSeparatorWidth);
        }
        if (m_decimalsIncrementers.size() > 0)
        {
            width += decimalPointWidth + m_decimalsIncrementers.size() *
                (m_decimalsIncrementers[0]->width() + incrementerSeparatorWidth);
        }
        return width;
    }
}