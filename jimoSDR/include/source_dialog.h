#pragma once

#include <xtd/xtd>
#include "devices.h"
#include "rtlsdr_properties_panel.h"

namespace jimo_sdr
{
    class source_dialog : public xtd::forms::form
    {
        public:
            source_dialog();
        private:
            void _on_device_source_selected(object& sender, const xtd::event_args& e);
            void _show_device_properties();
            xtd::forms::vertical_layout_panel _vert_dialog_panel;
            xtd::forms::horizontal_layout_panel _device_panel;
            xtd::forms::horizontal_layout_panel _sample_rate_panel;
            xtd::forms::label _device_label;
            xtd::forms::label _hardware_key_label;
            xtd::forms::combo_box _device_combo_box;
            std::unique_ptr<rtlsdr_properties_panel> _rtlsdr_props_panel;

            soapy::devices _soapy_devices;
            std::shared_ptr<soapy::device> _device;
    };
}