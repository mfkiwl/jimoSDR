#include "MainForm.h"

using namespace xtd;
using namespace xtd::forms;
using namespace xtd::drawing;

namespace jimo_sdr
{
    MainForm::MainForm()
        :m_notifier(*this), _props_panel(*this, m_deviceProps, m_notifier), _center_frequency_display(10)
    {
        text("jimoSDR");
        size({1000, 800});
        minimum_size({1000, 800});
        start_position(xtd::forms::form_start_position::center_screen);

        _create_controls_panel();
        create_properties_panel();
        create_right_panel();
        _main_panel << _props_panel << _right_panel;
        _main_panel.control_layout_style(_props_panel, {300,
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

    void MainForm::on_form_closing(xtd::forms::form_closing_event_args& e)
    {
        enum dialog_result close = xtd::forms::message_box::show(*this, 
            "Are you sure you want exit?", 
            "Close jimoSDR", xtd::forms::message_box_buttons::yes_no, 
            xtd::forms::message_box_icon::question);
        e.cancel(close == xtd::forms::dialog_result::no);
    }

    void MainForm::create_properties_panel()
    {
        _props_panel.location({0, 0});
        _props_panel.size({300, client_size().height()});
        _props_panel.back_color(color::light_gray);
    }

    void MainForm::create_right_panel()
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

    void MainForm::_create_controls_panel()
    {
        _controls_panel.anchor(anchor_styles::left | anchor_styles::top
            | anchor_styles::right);
        _controls_panel.back_color(drawing::color::black);
        _center_frequency_label.text("Center:");
        _center_frequency_label.text_align(content_alignment::middle_center);
        _center_frequency_label.fore_color(drawing::color::white);
        _center_frequency_label.size( {20, 35} );
        _controls_panel << _props_button << _center_frequency_label << _center_frequency_display;
        _props_button.size( {_props_button.height(), _props_button.height()} );
        _controls_panel.control_layout_style(_props_button,
            {_props_button.width(),size_type::absolute, true});
        _controls_panel.padding(1);        
    }
}