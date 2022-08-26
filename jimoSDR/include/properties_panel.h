#pragma once

#include <xtd/xtd>
#include "devices.h"
#include "source_panel.h"

using namespace xtd;
using namespace xtd::forms;


namespace jimo_sdr
{
    class properties_panel : public vertical_layout_panel
    {
        public:
            properties_panel(soapy::devices& soapy_devices);
        private:
            source_panel _source_panel;
    };
}