#include "source_panel.h"

using namespace xtd;
using namespace xtd::forms;

namespace jimo_sdr
{
    source_panel::source_panel(soapy::devices& soapy_devices)
    {
        anchor(anchor_styles::top | anchor_styles::left | anchor_styles::right);
        text("Source");


        *this << radio_source;
        radio_source.drop_down_style(combo_box_style::drop_down_list);
        radio_source.anchor(anchor_styles::top | anchor_styles::left |
            anchor_styles::right);
        for(auto& pdev : soapy_devices)
        {
            radio_source.items().push_back((*pdev)["driver"]);
        }
        // if only one item, select it
        if(radio_source.items().size() == 1)
        {
            radio_source.selected_index(0);
        }
    }
}