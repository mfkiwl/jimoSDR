#include "user_draw_buttons.h"

using namespace xtd::forms;
using namespace xtd::drawing;

namespace jimo_sdr
{
    user_draw_button::user_draw_button()
    {
        width(35);
        height(35);
    }

    void properties_button::on_paint(paint_event_args& e)
    {
        graphics g = e.graphics();
        back_color(color::black);
        fore_color(color::white);
        xtd::drawing::solid_brush back_brush(back_color());
        rectangle props_button_rect{0, 0, width(), height()};
        g.fill_rectangle(back_brush,props_button_rect);
        xtd::drawing::pen pen(solid_brush(fore_color()), 5);
        point_f p1{5.f, 7.5f};
        point_f p2{width() - 5.f, 7.5f};
        g.draw_line(pen, p1, p2);
        point_f p3 = {5.f, (height())/2.f};
        point_f p4 = {width() - 5.f, (height())/2.f};
        g.draw_line(pen, p3, p4);
        point_f p5 = {5.f, height() - 7.5f};
        point_f p6 = {width() - 5.f, height() - 7.5f};
        g.draw_line(pen, p5, p6);
        xtd::drawing::pen border_pen{solid_brush(fore_color()), 1};
        rectangle_f rect{0.f, 0.f, static_cast<float>(width()), 
            static_cast<float>(height())};
        g.draw_rectangle(border_pen, rect);
    }
}