#include "source_panel.h"

using namespace xtd;
using namespace xtd::forms;

namespace jimo_sdr
{
    source_panel::source_panel()
    {
        anchor(anchor_styles::top | anchor_styles::left | anchor_styles::right);
        text("Source");


        *this << radio_source;
        radio_source.drop_down_style(combo_box_style::drop_down_list);
        radio_source.items().push_back_range({"radio1", "radio2", "radio3"});
        radio_source.anchor(anchor_styles::top | anchor_styles::left |
            anchor_styles::right);
    }
}