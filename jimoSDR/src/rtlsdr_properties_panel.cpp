#include "rtlsdr_properties_panel.h"

using namespace xtd;
using namespace xtd::forms;

namespace jimo_sdr
{
    rtlsdr_properties_panel::rtlsdr_properties_panel(device_properties& device_props)
            : _dev_props(device_props)
    {
        _sample_rate_label.text("Sample Rate");
        _sample_rate_label.text_align(content_alignment::middle_left);

        auto rates = _dev_props.device()->sample_rates(soapy::device::direction::rx, 0);
        _sample_rate_combo_box.items().clear();
        for(auto rate : rates)
        {
            // std::format is not in the standard clang++ library, so we
            // use stringstream here.
            std::stringstream ss;
            ss << rate / 1'000'000 << " MHz";
            _sample_rate_combo_box.items().push_back(ss.str());
        }
        auto current_rate = _dev_props.device()->sample_rate(soapy::device::direction::rx, 0);
        std::stringstream ss;
        ss << current_rate / 1'000'000 << " MHz";
        std::string rate = ss.str();
        auto items = _sample_rate_combo_box.items();
        auto end_it = items.cend();
        auto it = find(items.cbegin(), end_it, list_control::item(rate));
        if(it != end_it)
        {
            _sample_rate_combo_box.selected_item(*it);
        }

        *this << _sample_rate_label << _sample_rate_combo_box;
    }
}