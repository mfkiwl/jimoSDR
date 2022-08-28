#include "rtlsdr_group_box.h"
#include <sstream>

using namespace xtd::forms;

namespace jimo_sdr
{
    rtlsdr_group_box::rtlsdr_group_box()
    {
        anchor(anchor_styles::top | anchor_styles::left | anchor_styles::right
            | anchor_styles::bottom);
        text("RTLSDR");
        this->width(275);

        controls().push_back(_sample_rate_layout);
        _sample_rate_layout.controls().push_back_range({
            _sample_rate_combo_box, _sample_rate_label});

        _sample_rate_label.anchor(anchor_styles::top | anchor_styles::right);
        _sample_rate_label.text("Sample Rate:");

        _sample_rate_combo_box.anchor(anchor_styles::top | anchor_styles::left);


    }

    void rtlsdr_group_box::populate_panel(std::shared_ptr<soapy::device>& pdev)
    {
        _device = pdev;
        auto rates = pdev->sample_rates(soapy::device::direction::rx, 0);
        _sample_rate_combo_box.items().clear();

        for(auto rate : rates)
        {
            // std::format is not in the standard clang++ library, so we
            // use stringstream here.
            std::stringstream ss;
            ss << rate / 1'000'000 << " MHz";
            _sample_rate_combo_box.items().push_back(ss.str());
        }
    }
}