#include "properties_panel.h"

namespace jimo_sdr
{
    const xtd::drawing::color properties_panel_background = 
        xtd::drawing::color::from_argb(0xFF000000);

    properties_panel::properties_panel()
    {
        auto_size_mode(auto_size_mode::grow_and_shrink);
        anchor(anchor_styles::top | anchor_styles::bottom | anchor_styles::left);
        back_color(properties_panel_background);
    }
}