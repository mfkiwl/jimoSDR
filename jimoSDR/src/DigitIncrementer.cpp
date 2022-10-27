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
        
        size_changed += &DigitIncrementer::digit_incrementer_size_changed;
        digit_.mouse_move += &DigitIncrementer::mouse_moved;
        digit_.mouse_click += &DigitIncrementer::mouse_clicked;
        mouse_leave += &DigitIncrementer::mouse_left;
   }

    DigitIncrementer::DigitIncrementer(xtd::forms::control& parent)
        : DigitIncrementer()
    {
        parent << *this;
    }

    DigitIncrementer::DigitIncrementer(int32_t value)
        : DigitIncrementer()
    {
        this->value(value);
    }

    DigitIncrementer::DigitIncrementer(xtd::forms::control& parent, int32_t value)
        : DigitIncrementer(parent)
    {
        this->value(value);
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
                on_value_changed(xtd::event_args::empty);
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

    void DigitIncrementer::digit_incrementer_size_changed(xtd::object& sender, const xtd::event_args&)
    {
        DigitIncrementer& incr = dynamic_cast<DigitIncrementer&>(sender);
        incr.update_upper_lower_panels();
        incr.change_font_size_to_fit_control();
    }

    void DigitIncrementer::change_font_size_to_fit_control()
    {
        const xtd::drawing::font& old_font = font();
        auto em_size = (old_font.size() * size().height()) / old_size_.height();
        xtd::drawing::font new_font(old_font, em_size);
        digit_.font(new_font);
    }

    void DigitIncrementer::update_upper_lower_panels() noexcept
    {
        upper_panel_.size( {size().width(), size().height() / 2})
            .location( {0, 0});
        lower_panel_.size( {size().width(), height() - upper_panel_.height()})
            .location( {0, lower_panel_.height()});
    }

    int32_t DigitIncrementer::value() const noexcept
    {
        std::stringstream ss(text());
        int32_t value;
        ss >> value;
        return value;
    }

    DigitIncrementer& DigitIncrementer::value(int32_t new_value)
    {
        std::stringstream ss;
        ss << new_value;
        text(ss.str());
        return *this;
    }

    void DigitIncrementer::mouse_moved(xtd::object& sender, const xtd::forms::mouse_event_args& e)
    {
        control& ctrl = dynamic_cast<control&>(sender);
        auto& parent = ctrl.parent()->get();
        auto& incr = dynamic_cast<DigitIncrementer&>(parent);
        incr.highlight_upper_or_lower(e);
    }

    // Go back through parent controls until we find one whose background color is not transparent.
    // Use that color to determine the background color for the upper or lower panel while the mouse
    // cursor is over it.
    void DigitIncrementer::highlight_upper_or_lower(const xtd::forms::mouse_event_args& e)
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

    void DigitIncrementer::mouse_left(xtd::object& sender, const xtd::event_args& e)
    {
        auto& incr = dynamic_cast<DigitIncrementer&>(sender);
        incr.remove_highlight();
    }
    
    void DigitIncrementer::remove_highlight()
    {
        upper_panel_.back_color(xtd::drawing::color::transparent);
        lower_panel_.back_color(xtd::drawing::color::transparent);
    }

    void DigitIncrementer::mouse_clicked(xtd::object& sender, const xtd::forms::mouse_event_args& e)
    {
        control& ctrl = dynamic_cast<control&>(sender);
        auto& parent = ctrl.parent()->get();
        auto& incr = dynamic_cast<DigitIncrementer&>(parent);
        incr.increment_decrement_based_on_cursor_position(e);
    }

    void DigitIncrementer::increment_decrement_based_on_cursor_position(const xtd::forms::mouse_event_args& e)
    {
        auto upper_panel_bounds = upper_panel_.bounds();
        upper_panel_bounds.contains(e.location()) ? increment() : decrement();
   }
    
    void DigitIncrementer::increment()
    {
        auto new_value = value();
        if (++new_value > 9)
        {
            value(0);
            on_roll_over(xtd::event_args::empty);
        }
        else
        {
            value(new_value);
        }
    }

    void DigitIncrementer::decrement()
    {
        auto new_value = value();
        if (--new_value < 0)
        {
            value(9);
            on_roll_under(xtd::event_args::empty);
        }
        else
        {
            value(new_value);
        }
    }

    void DigitIncrementer::on_value_changed(const event_args& e)
    {
        xtd::event_handler handler = value_changed;
        if (!handler.is_empty())
        {
            handler.invoke(*this, e);
        }
    }

    void DigitIncrementer::on_roll_over(const event_args& e)
    {
        xtd::event_handler handler = rolled_over;
        if (!handler.is_empty())
        {
            handler.invoke(*this, e);
        }
    }

    void DigitIncrementer::on_roll_under(const event_args& e)
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