#include "rtlsdr_group_box.h"

using namespace xtd::forms;

namespace jimo_sdr
{
    rtlsdr_group_box::rtlsdr_group_box()
    {
        anchor(anchor_styles::top | anchor_styles::left | anchor_styles::right
            | anchor_styles::bottom);
        text("RTLSDR");

        controls().push_back(_sample_rate_layout);
        _sample_rate_layout.controls().push_back_range({_sample_rate_label,
            _sample_rate_combo_box});

        _sample_rate_label.anchor(anchor_styles::top | anchor_styles::left);
        _sample_rate_label.text("Sample Rate:");

        _sample_rate_combo_box.anchor(anchor_styles::top | anchor_styles::right);


    }
}