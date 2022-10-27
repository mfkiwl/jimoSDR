#include "DigitIncrementer.h"
#include "ControlSizes.h"
#include <sstream>

using namespace xtd;
using namespace xtd::forms;

namespace jimo_sdr
{
    const xtd::drawing::size digit_incrementer_minimum_size(digitIncrementerMinimumWidth, digitIncrementerMinimumHeight);
    const xtd::drawing::size digit_incrementer_maximum_size(digitIncrementerMaximumWidth, digitIncrementerMaximumHeight);
    const xtd::drawing::point digit_origin(0, 0);
    const xtd::drawing::point upper_panel_origin(digit_origin);
    const xtd::forms::padding margin_size(0);
    const xtd::forms::padding padding_size(0);

    DigitIncrementer::DigitIncrementer()
    {
        margin(margin_size);
        padding(padding_size);
        size(digit_incrementer_maximum_size);
        maximum_size(digit_incrementer_maximum_size);
        minimum_size(digit_incrementer_minimum_size);
        size(minimum_client_size());
        digit_.minimum_size(minimum_client_size());
        digit_.maximum_size(maximum_client_size());
        digit_.text("0");
        digit_.text_align(content_alignment::middle_center);
        digit_.dock(xtd::forms::dock_style::fill);
        digit_.back_color(drawing::color::transparent);

        upper_panel_.size( {size().width(), size().height() / 2})
            .location(upper_panel_origin)
            .back_color(xtd::drawing::color::transparent);
        lower_panel_.size( {size().width(), height() - upper_panel_.height()})
            .location( {upper_panel_origin.x(), lower_panel_.height()})
            .back_color(xtd::drawing::color::transparent);
        


        *this << upper_panel_ << lower_panel_ << digit_;
        digit_.location(digit_origin);
        
        size_changed += &DigitIncrementer::DigitIncrementerSizeChanged;
        digit_.mouse_move += &DigitIncrementer::MouseMoved;
        digit_.mouse_click += &DigitIncrementer::MouseClicked;
        mouse_leave += &DigitIncrementer::MouseLeft;
   }

    DigitIncrementer::DigitIncrementer(xtd::forms::control& parent)
        : DigitIncrementer()
    {
        parent << *this;
    }

    DigitIncrementer::DigitIncrementer(int32_t value)
        : DigitIncrementer()
    {
        this->Value(value);
    }

    DigitIncrementer::DigitIncrementer(xtd::forms::control& parent, int32_t value)
        : DigitIncrementer(parent)
    {
        this->Value(value);
    }

    const xtd::ustring& DigitIncrementer::text() const
    {
        return digit_.text();
    }

    DigitIncrementer& DigitIncrementer::text(const xtd::ustring& text)
    {
        int32_t value;
        bool parsed = try_parse<int32_t>(text, value);
        if (parsed)
        {
            if(value >= 0 && value <= 9)
            {
                digit_.text(text);
                OnValueChanged(xtd::event_args::empty);
                return *this;
            }
        }
        std::stringstream ss;
        ss << R"(Value passed to digit_incrementer::text() must be between "0" and "9")";
        ss << R"( but value was ")" << text << R"(")";
        diagnostics::stack_frame frame;
        throw xtd::argument_out_of_range_exception(ss.str(), frame);
    }

    xtd::drawing::font DigitIncrementer::font() const
    {
        return digit_.font();
    }

    DigitIncrementer& DigitIncrementer::font(const xtd::drawing::font& font)
    {
        auto old_font = digit_.font();
        xtd::drawing::font new_font(font.name(), old_font.size(), old_font.unit());
        digit_.font(new_font);
        return *this;
    }

    xtd::drawing::size DigitIncrementer::size() const
    {
        return panel::size();
    }

    DigitIncrementer& DigitIncrementer::size(const xtd::drawing::size& new_size)
    {
        old_size_ = size();
        xtd::drawing::size sz = new_size;
        auto max = maximum_size();
        auto min = minimum_size();
        if (sz.width() < min.width() || sz.height() < min.height())
        {
            sz = min;
        }
        else if (sz.width() > max.width() || sz.height() > max.height())
        {
            sz = max;
        }
        auto height = (new_size.width() * min.height()) / min.width();
        xtd::drawing::size h_size(sz.width(), height);
        auto width = (new_size.height() * min.width()) / min.height();
        xtd::drawing::size w_size(width, sz.height());
        if (width > sz.width())
        {
            sz = w_size;
        }
        if (height > sz.height())
        {
            sz = h_size;
        }
        digit_.size(sz);
        auto& ctrl = panel::size(sz);
        return dynamic_cast<DigitIncrementer&>(ctrl);
    }

    void DigitIncrementer::DigitIncrementerSizeChanged(xtd::object& sender, const xtd::event_args&)
    {
        DigitIncrementer& incr = dynamic_cast<DigitIncrementer&>(sender);
        incr.UpdateUpperLowerPanels();
        incr.ChangeFontSizeToFitControl();
    }

    void DigitIncrementer::ChangeFontSizeToFitControl()
    {
        const xtd::drawing::font& old_font = font();
        auto em_size = (old_font.size() * size().height()) / old_size_.height();
        xtd::drawing::font new_font(old_font, em_size);
        digit_.font(new_font);
    }

    void DigitIncrementer::UpdateUpperLowerPanels() noexcept
    {
        upper_panel_.size( {size().width(), size().height() / 2})
            .location( {0, 0});
        lower_panel_.size( {size().width(), height() - upper_panel_.height()})
            .location( {0, lower_panel_.height()});
    }

    int32_t DigitIncrementer::Value() const noexcept
    {
        std::stringstream ss(text());
        int32_t value;
        ss >> value;
        return value;
    }

    DigitIncrementer& DigitIncrementer::Value(int32_t new_value)
    {
        std::stringstream ss;
        ss << new_value;
        text(ss.str());
        return *this;
    }

    void DigitIncrementer::MouseMoved(xtd::object& sender, const xtd::forms::mouse_event_args& e)
    {
        control& ctrl = dynamic_cast<control&>(sender);
        auto& parent = ctrl.parent()->get();
        auto& incr = dynamic_cast<DigitIncrementer&>(parent);
        incr.HighlightUpperOrLower(e);
    }

    // Go back through parent controls until we find one whose background color is not transparent.
    // Use that color to determine the background color for the upper or lower panel while the mouse
    // cursor is over it.
    void DigitIncrementer::HighlightUpperOrLower(const xtd::forms::mouse_event_args& e)
    {

        xtd::drawing::color panel_background;
        auto parent = this->parent();
        auto background_color = (dynamic_cast<xtd::forms::control&>(parent.value().get())).back_color();
        while (background_color == xtd::drawing::color::transparent)
        {
            parent = (dynamic_cast<xtd::forms::control&>(parent.value().get())).parent();
            background_color = (dynamic_cast<xtd::forms::control&>(parent.value().get())).back_color();;
        }
        if (background_color.is_dark())
        {
            panel_background = xtd::drawing::color::from_argb(63, xtd::drawing::color::white);
        }
        else
        {
            panel_background = xtd::drawing::color::from_argb(63, xtd::drawing::color::black);
        }
        auto upper_panel_bounds = upper_panel_.bounds();
        if (upper_panel_bounds.contains(e.location()))
        {
            upper_panel_.back_color(panel_background);
            lower_panel_.back_color(xtd::drawing::color::transparent);
        }
        else
        {
            upper_panel_.back_color(xtd::drawing::color::transparent);
            lower_panel_.back_color(panel_background);
        }
    }

    void DigitIncrementer::MouseLeft(xtd::object& sender, const xtd::event_args& e)
    {
        auto& incr = dynamic_cast<DigitIncrementer&>(sender);
        incr.RemoveHighlight();
    }
    
    void DigitIncrementer::RemoveHighlight()
    {
        upper_panel_.back_color(xtd::drawing::color::transparent);
        lower_panel_.back_color(xtd::drawing::color::transparent);
    }

    void DigitIncrementer::MouseClicked(xtd::object& sender, const xtd::forms::mouse_event_args& e)
    {
        control& ctrl = dynamic_cast<control&>(sender);
        auto& parent = ctrl.parent()->get();
        auto& incr = dynamic_cast<DigitIncrementer&>(parent);
        incr.IncrementDecrementBasedOnCursorPosition(e);
    }

    void DigitIncrementer::IncrementDecrementBasedOnCursorPosition(const xtd::forms::mouse_event_args& e)
    {
        auto upper_panel_bounds = upper_panel_.bounds();
        upper_panel_bounds.contains(e.location()) ? Increment() : Decrement();
   }
    
    void DigitIncrementer::Increment()
    {
        auto new_value = Value();
        if (++new_value > 9)
        {
            Value(0);
            OnRollOver(xtd::event_args::empty);
        }
        else
        {
            Value(new_value);
        }
    }

    void DigitIncrementer::Decrement()
    {
        auto new_value = Value();
        if (--new_value < 0)
        {
            Value(9);
            OnRollUnder(xtd::event_args::empty);
        }
        else
        {
            Value(new_value);
        }
    }

    void DigitIncrementer::OnValueChanged(const event_args& e)
    {
        xtd::event_handler handler = value_changed;
        if (!handler.is_empty())
        {
            handler.invoke(*this, e);
        }
    }

    void DigitIncrementer::OnRollOver(const event_args& e)
    {
        xtd::event_handler handler = rolled_over;
        if (!handler.is_empty())
        {
            handler.invoke(*this, e);
        }
    }

    void DigitIncrementer::OnRollUnder(const event_args& e)
    {
        xtd::event_handler handler = rolled_under;
        if (!handler.is_empty())
        {
            handler.invoke(*this, e);
        }
    }

    int32_t DigitIncrementer::height() const 
    {
        return control::height();
    }

    DigitIncrementer& DigitIncrementer::height(int32_t height)
    {
        xtd::drawing::size minimum = minimum_size();
        int32_t width = (height * minimum.width()) / minimum.height();
        xtd::drawing::size new_size(width, height); 
        size(new_size);
        return *this;
    }

    int32_t DigitIncrementer::width() const 
    {
        return control::width();
    }

    DigitIncrementer& DigitIncrementer::width(int32_t width)
    {
        xtd::drawing::size minimum = minimum_size();
        int32_t height = (width * minimum.height()) / minimum.width();
        xtd::drawing::size new_size(width, height); 
        size(new_size);
        return *this;
    }

    xtd::ustring DigitIncrementer::to_string() const noexcept
    {
        return xtd::ustring::format("digit_incrementer value: {}", text());
    }

    std::ostream& operator <<(std::ostream& out, const DigitIncrementer& incrementer)
    {
        out << incrementer.to_string();
        return out;
    }

}