#include "source_panel.h"

using namespace xtd;
using namespace xtd::forms;

namespace jimo_sdr
{
    source_panel::source_panel(soapy::devices& soapy_devices)
        : _soapy_devices(soapy_devices)
    {
        anchor(anchor_styles::top | anchor_styles::left | anchor_styles::right);
        text("Source");
        *this << _layout;

        _radio_source.drop_down_style(combo_box_style::drop_down_list);
        _radio_source.anchor(anchor_styles::top | anchor_styles::left |
            anchor_styles::right);
        _radio_source.selected_index_changed += xtd::event_handler(
            *this, &source_panel::_on_radio_source_selected);

        _layout << _radio_source << _rtlsdr_box;
        _rtlsdr_box.hide();

        for(auto& pdev : soapy_devices)
        {
            _radio_source.items().push_back((*pdev)["driver"]);
        }
        // if only one item, select it
        if(_radio_source.items().size() == 1)
        {
            _radio_source.selected_index(0);
        }
    }

    void source_panel::_on_radio_source_selected(object& sender, 
        const xtd::event_args& e)
    {
        _device = _soapy_devices[_radio_source.selected_index()];
        show_device_panel(_device);
    }

    void source_panel::show_device_panel(std::shared_ptr<soapy::device>& pdev)
    {
        // hide any source group boxes
        _rtlsdr_box.hide();
        if((*pdev)["driver"] == "rtlsdr")
        {
            _rtlsdr_box.populate_panel(pdev);
            _rtlsdr_box.show();
        }
    }
}