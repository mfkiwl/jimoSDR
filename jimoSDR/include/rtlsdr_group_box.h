#pragma once

#include <xtd/xtd>
#include <memory>
#include "device.h"

namespace jimo_sdr
{
    class rtlsdr_group_box : public xtd::forms::group_box
    {
        public:
            rtlsdr_group_box();
            void populate_panel(std::shared_ptr<soapy::device>& pdev);
        private:
            std::shared_ptr<soapy::device> _device;
            xtd::forms::horizontal_layout_panel _sample_rate_layout;
            xtd::forms::label _sample_rate_label;
            xtd::forms::combo_box _sample_rate_combo_box;
    };
}