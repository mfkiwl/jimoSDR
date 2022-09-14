#pragma once

#include <xtd/xtd>
#include "devices.h"
#include "device_properties.h"
#include "rtlsdr_properties_panel.h"

namespace jimo_sdr
{
    class source_dialog : public xtd::forms::form
    {
        public:
            source_dialog(device_properties& device_properties);
            void ok_clicked(const object& sender, const xtd::event_args& e);
        private:
            void _on_device_source_selected(object& sender, const xtd::event_args& e);
            void _show_device_properties();
            void _build_device_panel();
            void _build_buttons_panel();
            xtd::forms::vertical_layout_panel _vert_dialog_panel;
            xtd::forms::horizontal_layout_panel _device_panel;
            xtd::forms::label _device_label;
            xtd::forms::label _hardware_key_label;
            xtd::forms::combo_box _device_combo_box;

            xtd::forms::horizontal_layout_panel _buttons_panel;
            xtd::forms::label _filler_label;
            xtd::forms::button _ok_button;

            std::unique_ptr<soapy::devices> _soapy_devices;
            device_properties& _device_props;
            std::unique_ptr<rtlsdr_properties_panel> _rtlsdr_props_panel;
    };
}