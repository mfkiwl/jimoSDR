#include "properties_panel.h"

namespace jimo_sdr
{
    properties_panel::properties_panel(soapy::devices& soapy_devices)
        : _source_panel(soapy_devices)
    {
        auto_scroll(true);
        auto_size_mode(auto_size_mode::grow_and_shrink);
        anchor(anchor_styles::top | anchor_styles::bottom | anchor_styles::left);
        *this << _source_panel;
    }
}