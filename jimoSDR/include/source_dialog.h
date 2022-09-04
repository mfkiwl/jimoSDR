#pragma once

#include <xtd/xtd>
#include "devices.h"

namespace jimo_sdr
{
    class source_dialog : public xtd::forms::form
    {
        public:
            source_dialog();
        private:
            void _on_device_source_selected(object& sender, const xtd::event_args& e);
            xtd::forms::vertical_layout_panel _vert_dialog_panel;
            xtd::forms::horizontal_layout_panel _device_panel;
            xtd::forms::horizontal_layout_panel _sample_rate_panel;
            xtd::forms::label _device_label;
            xtd::forms::label _hardware_key_label;
            xtd::forms::combo_box _device_combo_box;
            xtd::forms::label _sample_rate_label;
            xtd::forms::combo_box _sample_rate_combo_box;

            soapy::devices _soapy_devices;
            std::shared_ptr<soapy::device> _device;

    };
}