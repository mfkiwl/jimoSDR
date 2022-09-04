#include "rtlsdr_properties_panel.h"

using namespace xtd;
using namespace xtd::forms;

namespace jimo_sdr
{
    rtlsdr_properties_panel::rtlsdr_properties_panel(std::shared_ptr<soapy::device>& soapy_device)
        : _soapy_device(soapy_device)
    {
        _sample_rate_label.text("Sample Rate");
        _sample_rate_label.anchor(anchor_styles::left | anchor_styles::top | anchor_styles::right);
        _sample_rate_label.text_align(content_alignment::middle_left);

        _sample_rate_combo_box.anchor(anchor_styles::left | anchor_styles::right);
        auto rates = _soapy_device->sample_rates(soapy::device::direction::rx, 0);
        _sample_rate_combo_box.items().clear();
        for(auto rate : rates)
        {
            // std::format is not in the standard clang++ library, so we
            // use stringstream here.
            std::stringstream ss;
            ss << rate / 1'000'000 << " MHz";
            _sample_rate_combo_box.items().push_back(ss.str());
        }

        anchor(anchor_styles::left | anchor_styles::bottom | anchor_styles::right);
        *this << _sample_rate_label << _sample_rate_combo_box;
        control_layout_style(_sample_rate_label, {size_type::auto_size, true});
        control_layout_style(_sample_rate_combo_box, {size_type::auto_size, true});
        _sample_rate_label.height(220);
        _sample_rate_combo_box.height(_sample_rate_label.height());
    }
}