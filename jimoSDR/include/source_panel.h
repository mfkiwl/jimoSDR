#pragma once

#include <xtd/xtd>

namespace jimo_sdr
{
    class source_panel : public xtd::forms::group_box
    {
        public:
            source_panel();
        private:
            xtd::forms::combo_box radio_source;
    };
}