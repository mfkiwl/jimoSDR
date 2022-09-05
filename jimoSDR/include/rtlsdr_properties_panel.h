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
//            std::optional<std::unique_ptr<device_properties>>& properties() { return _dev_props;}
        private:
            xtd::forms::label _sample_rate_label;
            xtd::forms::combo_box _sample_rate_combo_box;

            device_properties& _dev_props;
    };
}