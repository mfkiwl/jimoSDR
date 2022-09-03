#pragma once

#include <xtd/xtd>

namespace jimo_sdr
{
    class user_draw_button : public xtd::forms::button
    {
        public:
            user_draw_button();
        protected:
            virtual void on_paint(xtd::forms::paint_event_args& e) = 0;
    };

    class properties_button : public user_draw_button
    {
        public:
            properties_button() = default;
        protected:
            virtual void on_paint(xtd::forms::paint_event_args& e) override;
    };
}