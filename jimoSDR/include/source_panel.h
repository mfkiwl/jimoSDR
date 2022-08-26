#pragma once

#include "devices.h"
#include <xtd/xtd>

namespace jimo_sdr
{
    class source_panel : public xtd::forms::group_box
    {
        public:
            source_panel(soapy::devices& soapy_devices);
        private:
            xtd::forms::combo_box radio_source;
    };
}