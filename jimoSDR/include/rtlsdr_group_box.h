#pragma once

#include <xtd/xtd>

namespace jimo_sdr
{
    class rtlsdr_group_box : public xtd::forms::group_box
    {
        public:
            rtlsdr_group_box();
        private:
            xtd::forms::horizontal_layout_panel _sample_rate_layout;
            xtd::forms::label _sample_rate_label;
            xtd::forms::combo_box _sample_rate_combo_box;
    };
}