#include "digit_incrementer.h"
#include <sstream>
#include <iostream>

using namespace xtd;
using namespace xtd::forms;

namespace jimo_sdr
{
    const xtd::drawing::size digit_incrementer_minimum_size(11, 16);
    const xtd::drawing::size digit_incrementer_maximum_size(66, 96);
    const xtd::drawing::point digit_origin(0, 0);
    const xtd::drawing::point upper_panel_origin(digit_origin);
    const xtd::forms::padding margin_size(0);
    const xtd::forms::padding padding_size(0);
    digit_incrementer::digit_incrementer()
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
        
        size_changed += &digit_incrementer::digit_incrementer_size_changed;
        digit_.mouse_move += &digit_incrementer::mouse_moved;
        digit_.mouse_click += &digit_incrementer::mouse_clicked;
        mouse_leave += &digit_incrementer::mouse_left;
   }

    digit_incrementer::digit_incrementer(xtd::forms::control& parent)
        : digit_incrementer()
    {
        parent << *this;
    }

    digit_incrementer::digit_incrementer(int32_t value)
        : digit_incrementer()
    {
        this->value(value);
    }

    digit_incrementer::digit_incrementer(xtd::forms::control& parent, int32_t value)
        : digit_incrementer(parent)
    {
        this->value(value);
    }

    const xtd::ustring& digit_incrementer::text() const
    {
        return digit_.text();
    }

    digit_incrementer& digit_incrementer::text(const xtd::ustring& text)
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

    xtd::drawing::font digit_incrementer::font() const
    {
        return digit_.font();
    }

    digit_incrementer& digit_incrementer::font(const xtd::drawing::font& font)
    {
        auto old_font = digit_.font();
        xtd::drawing::font new_font(font.name(), old_font.size(), old_font.unit());
        digit_.font(new_font);
        return *this;
    }

    xtd::drawing::size digit_incrementer::size() const
    {
        return panel::size();
    }

    digit_incrementer& digit_incrementer::size(const xtd::drawing::size& new_size)
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
        return dynamic_cast<digit_incrementer&>(ctrl);
    }

    void digit_incrementer::digit_incrementer_size_changed(xtd::object& sender, const xtd::event_args&)
    {
        digit_incrementer& incr = dynamic_cast<digit_incrementer&>(sender);
        incr.update_upper_lower_panels();
        incr.change_font_size_to_fit_control();
    }

    void digit_incrementer::change_font_size_to_fit_control()
    {
        const xtd::drawing::font& old_font = font();
        auto em_size = (old_font.size() * size().height()) / old_size_.height();
        xtd::drawing::font new_font(old_font, em_size);
        digit_.font(new_font);
    }

    void digit_incrementer::update_upper_lower_panels() noexcept
    {
        upper_panel_.size( {size().width(), size().height() / 2})
            .location( {0, 0});
        lower_panel_.size( {size().width(), height() - upper_panel_.height()})
            .location( {0, lower_panel_.height()});
    }

    int32_t digit_incrementer::value() const noexcept
    {
        std::stringstream ss(text());
        int32_t value;
        ss >> value;
        return value;
    }

    digit_incrementer& digit_incrementer::value(int32_t new_value)
    {
        std::stringstream ss;
        ss << new_value;
        text(ss.str());
        return *this;
    }

    void digit_incrementer::mouse_moved(xtd::object& sender, const xtd::forms::mouse_event_args& e)
    {
        control& ctrl = dynamic_cast<control&>(sender);
        auto& parent = ctrl.parent()->get();
        auto& incr = dynamic_cast<digit_incrementer&>(parent);
        incr.highlight_upper_or_lower(e);
    }

    // Go back through parent controls until we find one whose background color is not transparent.
    // Use that color to determine the background color for the upper or lower panel while the mouse
    // cursor is over it.
    void digit_incrementer::highlight_upper_or_lower(const xtd::forms::mouse_event_args& e)
    {

        xtd::drawing::color panel_background;
        auto parent = this->parent();
        auto background_color = (dynamic_cast<xtd::forms::control&>(parent.value().get())).back_color();
        while (background_color == xtd::drawing::color::transparent)
        {
            parent = (dynamic_cast<xtd::forms::control&>(parent.value().get())).parent();
            background_color = (dynamic_cast<xtd::forms::control&>(parent.value().get())).back_color();;
        }
        std::cout << background_color.is_dark() << '\n';
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

    void digit_incrementer::mouse_left(xtd::object& sender, const xtd::event_args& e)
    {
        auto& incr = dynamic_cast<digit_incrementer&>(sender);
        incr.remove_highlight();
    }
    
    void digit_incrementer::remove_highlight()
    {
        upper_panel_.back_color(xtd::drawing::color::transparent);
        lower_panel_.back_color(xtd::drawing::color::transparent);
    }

    void digit_incrementer::mouse_clicked(xtd::object& sender, const xtd::forms::mouse_event_args& e)
    {
        control& ctrl = dynamic_cast<control&>(sender);
        auto& parent = ctrl.parent()->get();
        auto& incr = dynamic_cast<digit_incrementer&>(parent);
        incr.increment_decrement_based_on_cursor_position(e);
    }

    void digit_incrementer::increment_decrement_based_on_cursor_position(const xtd::forms::mouse_event_args& e)
    {
        auto upper_panel_bounds = upper_panel_.bounds();
        upper_panel_bounds.contains(e.location()) ? increment() : decrement();
   }
    
    void digit_incrementer::increment()
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

    void digit_incrementer::decrement()
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

    void digit_incrementer::on_value_changed(const event_args& e)
    {
        xtd::event_handler handler = value_changed;
        if (!handler.is_empty())
        {
            handler.invoke(*this, e);
        }
    }

    void digit_incrementer::on_roll_over(const event_args& e)
    {
        xtd::event_handler handler = rolled_over;
        if (!handler.is_empty())
        {
            handler.invoke(*this, e);
        }
    }

    void digit_incrementer::on_roll_under(const event_args& e)
    {
        xtd::event_handler handler = rolled_under;
        if (!handler.is_empty())
        {
            handler.invoke(*this, e);
        }
    }

    int32_t digit_incrementer::height() const 
    {
        return control::height();
    }

    digit_incrementer& digit_incrementer::height(int32_t height)
    {
        xtd::drawing::size minimum = minimum_size();
        int32_t width = (height * minimum.width()) / minimum.height();
        xtd::drawing::size new_size(width, height); 
        size(new_size);
        return *this;
    }

    int32_t digit_incrementer::width() const 
    {
        return control::width();
    }

    digit_incrementer& digit_incrementer::width(int32_t width)
    {
        xtd::drawing::size minimum = minimum_size();
        int32_t height = (width * minimum.height()) / minimum.width();
        xtd::drawing::size new_size(width, height); 
        size(new_size);
        return *this;
    }

    xtd::ustring digit_incrementer::to_string() const noexcept
    {
        return xtd::ustring::format("digit_incrementer value: {}", text());
    }

    std::ostream& operator <<(std::ostream& out, const digit_incrementer& incrementer)
    {
        out << incrementer.to_string();
        return out;
    }

}