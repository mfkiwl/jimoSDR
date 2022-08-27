#include "rtlsdr_group_box.h"

using namespace xtd::forms;

namespace jimo_sdr
{
    rtlsdr_group_box::rtlsdr_group_box()
    {
        anchor(anchor_styles::top | anchor_styles::left | anchor_styles::right);
        text("RTLSDR");
    }
}