/// @copyright Copyright © 2022 Jim Orcheson. Available under the MIT License.
#pragma once
#include <xtd/xtd>

namespace jimo_sdr
{
    class DigitIncrementer : public xtd::forms::panel
    {
        public:
            DigitIncrementer();
            DigitIncrementer(xtd::forms::control& parent);
            DigitIncrementer(int32_t value);
            DigitIncrementer(xtd::forms::control& parent, int32_t value);

            DigitIncrementer(const DigitIncrementer&) = delete;
            DigitIncrementer(DigitIncrementer&&) = delete;
            DigitIncrementer& operator=(const DigitIncrementer&) = delete;
            DigitIncrementer& operator=(DigitIncrementer&&) = delete;
            virtual xtd::drawing::font font() const override;
            virtual DigitIncrementer& font(const xtd::drawing::font& font) override;
            virtual int32_t height() const override;
            virtual DigitIncrementer& height(int32_t height) override;
            virtual xtd::drawing::size size() const override;
            virtual DigitIncrementer& size(const xtd::drawing::size& size) override;
            virtual const xtd::ustring& text() const override;
            virtual DigitIncrementer& text(const xtd::ustring& value) override;
            virtual int32_t Value() const noexcept;
            DigitIncrementer& Value(int32_t new_value);
            virtual int32_t width() const override;
            virtual DigitIncrementer& width(int32_t width) override;

            virtual void Increment();
            virtual void Decrement();
            virtual xtd::ustring to_string() const noexcept override;
            friend std::ostream& operator <<(std::ostream& out, const DigitIncrementer& incrementer);

            xtd::event<DigitIncrementer, xtd::event_handler> value_changed;
            xtd::event<DigitIncrementer, xtd::event_handler> rolled_over;
            xtd::event<DigitIncrementer, xtd::event_handler> rolled_under;
        protected:
            virtual void ChangeFontSizeToFitControl();
            static void DigitIncrementerSizeChanged(xtd::object& sender, const xtd::event_args& e);
            virtual void HighlightUpperOrLower(const xtd::forms::mouse_event_args& e);
            virtual void IncrementDecrementBasedOnCursorPosition(const xtd::forms::mouse_event_args& e);
            static void MouseClicked(xtd::object& sender, const xtd::forms::mouse_event_args& e);
            static void MouseLeft(xtd::object& sender, const xtd::event_args& e);
            static void MouseMoved(xtd::object& sender, const xtd::forms::mouse_event_args& e);
            virtual void OnRollOver(const xtd::event_args& e);
            virtual void OnRollUnder(const xtd::event_args& e);
            virtual void OnValueChanged(const xtd::event_args& e);
            virtual void RemoveHighlight();
            virtual void UpdateUpperLowerPanels() noexcept;
        private:
            xtd::forms::label digit_;
            xtd::forms::panel upper_panel_;
            xtd::forms::panel lower_panel_;
            xtd::drawing::size old_size_;
    };
}