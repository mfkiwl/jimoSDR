#pragma once

#include <xtd/xtd>
#include "device.h"
#include "device_properties.h"

namespace jimo_sdr
{
    class rtlsdr_properties_panel : public xtd::forms::vertical_layout_panel
    {
        public:
            rtlsdr_properties_panel(device_properties& device_props);
        private:
            void _populate_sample_rate_combo_box();
            void _on_sampling_mode_selected(object& sender, const xtd::event_args& e);
            void _set_sampling_mode();

            xtd::forms::label _sample_rate_label;
            xtd::forms::combo_box _sample_rate_combo_box;
            xtd::forms::label _sampling_mode_label;
            xtd::forms::combo_box _sampling_mode_combo_box;

            device_properties& _dev_props;
    };
}