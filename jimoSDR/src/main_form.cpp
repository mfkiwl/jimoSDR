#include "main_form.h"

using namespace xtd;
using namespace xtd::forms;
using namespace xtd::drawing;

namespace jimo_sdr
{
    main_form::main_form(soapy::devices& soapy_devices)
        : _props_panel(soapy_devices)
    {
        create_properties_panel();
        create_right_panel();
        
        text("jimoSDR");
        size({1000, 800});
        start_position(xtd::forms::form_start_position::center_screen);
        auto_size(false);
    }

    void main_form::create_properties_panel()
    {
        _props_panel.location({0, 0});
        _props_panel.size({300, client_size().height()});
        *this << _props_panel;
    }

    void main_form::create_right_panel()
    {
        auto& main_form_client_rect = client_size();
        auto left_panel_size = _props_panel.size();
        _right_panel.location({left_panel_size.width(), 0});
        _right_panel.size({main_form_client_rect.width() - left_panel_size.width(),
            main_form_client_rect.height()});
        _right_panel.back_color(right_panel_background);
        _right_panel.anchor(anchor_styles::top | anchor_styles::right | 
            anchor_styles:: bottom | anchor_styles::left);
        *this << _right_panel;
    }
}