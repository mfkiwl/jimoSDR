#include "main_form.h"

using namespace xtd;
using namespace xtd::forms;
using namespace xtd::drawing;

namespace jimo_sdr
{
    main_form::main_form()
    {
        text("jimoSDR");
        size({1000, 800});
        start_position(xtd::forms::form_start_position::center_screen);
        auto_size(false);

        create_left_panel();
        create_right_panel();
    }

    void main_form::create_left_panel()
    {
        _left_panel.location({0, 0});
        auto& main_form_client_rect = client_size();
        _left_panel.size({200, main_form_client_rect.height()});
        _left_panel.back_color(left_panel_background);
        *this << _left_panel;
    }

    void main_form::create_right_panel()
    {
        auto& main_form_client_rect = client_size();
        auto left_panel_size = _left_panel.size();
        _right_panel.location({left_panel_size.width(), 0});
        _right_panel.size({main_form_client_rect.width() - left_panel_size.width(),
            main_form_client_rect.height()});
        _right_panel.back_color(right_panel_background);
        *this << _right_panel;
    }
}