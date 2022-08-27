#include "source_panel.h"

using namespace xtd;
using namespace xtd::forms;

namespace jimo_sdr
{
    source_panel::source_panel(soapy::devices& soapy_devices)
    {
        anchor(anchor_styles::top | anchor_styles::left | anchor_styles::right);
        text("Source");
        *this << _layout;

       _radio_source.drop_down_style(combo_box_style::drop_down_list);
        _radio_source.anchor(anchor_styles::top | anchor_styles::left |
            anchor_styles::right);
        for(auto& pdev : soapy_devices)
        {
            _radio_source.items().push_back((*pdev)["driver"]);
        }
        // if only one item, select it
        if(_radio_source.items().size() == 1)
        {
            _radio_source.selected_index(0);
        }

        _layout.controls().push_back_range({_radio_source, _rtlsdr_box});
    }
}