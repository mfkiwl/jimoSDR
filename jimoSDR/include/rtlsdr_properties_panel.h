#pragma once

#include <xtd/xtd>
#include "device.h"

namespace jimo_sdr
{
    class rtlsdr_properties_panel : public xtd::forms::vertical_layout_panel
    {
        public:
            rtlsdr_properties_panel(std::shared_ptr<soapy::device>& soapy_device);
        private:
            xtd::forms::label _sample_rate_label;
            xtd::forms::combo_box _sample_rate_combo_box;

            std::shared_ptr<soapy::device>& _soapy_device;
    };
}