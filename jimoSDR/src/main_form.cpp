#include "main_form.h"

using namespace xtd;
using namespace xtd::forms;
using namespace xtd::drawing;

namespace jimo_sdr
{
    main_form::main_form()
        : _props_panel()
    {
        text("jimoSDR");
        size({1000, 800});
        start_position(xtd::forms::form_start_position::center_screen);
//        auto_size(false);

        _controls_panel.anchor(anchor_styles::left | anchor_styles::top
            | anchor_styles::right);
        _controls_panel.back_color(drawing::color::black);
        _controls_panel << _props_button;
        _controls_panel.control_layout_style(_props_button,
            {_props_button.width(),size_type::absolute, true});
        _controls_panel.padding(1);

        create_properties_panel();
        create_right_panel();
        _main_panel << _props_panel << _right_panel;
        _main_panel.control_layout_style(_props_panel, {500,
            size_type::absolute, true});
        _main_panel.control_layout_style(_right_panel, {size_type::auto_size,
            true});
        _vlp.anchor(anchor_styles::left | anchor_styles::right
            | anchor_styles::bottom);
        _vlp.back_color(color::black);
        _vlp << _controls_panel << _main_panel;
        // these properties must be set after _controls_panel is
        // added to _vlp
         _props_button.height(35);
        _vlp.control_layout_style(_controls_panel, {_props_button.height(),
            size_type::absolute, true});
        _vlp.control_layout_style(_main_panel, {size_type::auto_size,
            true});
        _vlp.width(client_size().width());
        _vlp.height(client_size().height());
        *this << _vlp;
    }

    void main_form::create_properties_panel()
    {
        _props_panel.location({0, 0});
        _props_panel.size({500, client_size().height()});
        _props_panel.back_color(color::light_gray);
    }

    void main_form::create_right_panel()
    {
        auto& main_form_client_rect = client_size();
        auto left_panel_size = _props_panel.size();
        _right_panel.location({left_panel_size.width(), 0});
        _right_panel.size({main_form_client_rect.width() - left_panel_size.width(),
            main_form_client_rect.height()});
        _right_panel.back_color(color::black);
        _right_panel.anchor(anchor_styles::top | anchor_styles::right | 
            anchor_styles:: bottom | anchor_styles::left);
    }

    void main_form::show_source_dlg()
    {
        source_dialog sdlg(_device_props);
        sdlg.show_dialog(*this);
    }
}