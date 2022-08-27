#pragma once

#include "devices.h"
#include "rtlsdr_group_box.h"
#include <xtd/xtd>

namespace jimo_sdr
{
    class source_panel : public xtd::forms::group_box
    {
        public:
            source_panel(soapy::devices& soapy_devices);
        private:
            xtd::forms::vertical_layout_panel _layout;
            xtd::forms::combo_box _radio_source;
            rtlsdr_group_box _rtlsdr_box;
    };
}