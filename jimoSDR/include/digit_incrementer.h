/// @copyright Copyright © 2022 Jim Orcheson. Available under the MIT License.
#pragma once
#include <xtd/xtd>

namespace jimo_sdr
{
    class digit_incrementer : public xtd::forms::panel
    {
        public:
            digit_incrementer();
            digit_incrementer(xtd::forms::control& parent);
            digit_incrementer(int32_t value);
            digit_incrementer(xtd::forms::control& parent, int32_t value);

            digit_incrementer(const digit_incrementer&) = delete;
            digit_incrementer(digit_incrementer&&) = delete;
            digit_incrementer& operator=(const digit_incrementer&) = delete;
            digit_incrementer& operator=(digit_incrementer&&) = delete;
            virtual xtd::drawing::font font() const override;
            virtual digit_incrementer& font(const xtd::drawing::font& font) override;
            virtual int32_t height() const override;
            virtual digit_incrementer& height(int32_t height) override;
            virtual xtd::drawing::size size() const override;
            virtual digit_incrementer& size(const xtd::drawing::size& size) override;
            virtual const xtd::ustring& text() const override;
            virtual digit_incrementer& text(const xtd::ustring& value) override;
            virtual int32_t value() const noexcept;
            digit_incrementer& value(int32_t new_value);
            virtual int32_t width() const override;
            virtual digit_incrementer& width(int32_t width) override;

            virtual void increment();
            virtual void decrement();
            virtual xtd::ustring to_string() const noexcept override;
            friend std::ostream& operator <<(std::ostream& out, const digit_incrementer& incrementer);

            xtd::event<digit_incrementer, xtd::event_handler> value_changed;
            xtd::event<digit_incrementer, xtd::event_handler> rolled_over;
            xtd::event<digit_incrementer, xtd::event_handler> rolled_under;
        protected:
            virtual void change_font_size_to_fit_control();
            static void digit_incrementer_size_changed(xtd::object& sender, const xtd::event_args& e);
            virtual void highlight_upper_or_lower(const xtd::forms::mouse_event_args& e);
            virtual void increment_decrement_based_on_cursor_position(const xtd::forms::mouse_event_args& e);
            static void mouse_clicked(xtd::object& sender, const xtd::forms::mouse_event_args& e);
            static void mouse_left(xtd::object& sender, const xtd::event_args& e);
            static void mouse_moved(xtd::object& sender, const xtd::forms::mouse_event_args& e);
            virtual void on_roll_over(const xtd::event_args& e);
            virtual void on_roll_under(const xtd::event_args& e);
            virtual void on_value_changed(const xtd::event_args& e);
            virtual void remove_highlight();
            virtual void update_upper_lower_panels() noexcept;
        private:
            xtd::forms::label digit_;
            xtd::forms::panel upper_panel_;
            xtd::forms::panel lower_panel_;
            xtd::drawing::size old_size_;
    };
}