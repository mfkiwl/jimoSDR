#pragma once

#include "devices.h"
#include "rtlsdr_group_box.h"
#include <xtd/xtd>
#include <memory>

namespace jimo_sdr
{
    class source_panel : public xtd::forms::group_box
    {
        public:
            source_panel(soapy::devices& soapy_devices);
            void show_device_panel(std::shared_ptr<soapy::device>& pdev);
        private:
            void _on_radio_source_selected(object& sender, const xtd::event_args& e);
            soapy::devices& _soapy_devices;
            std::shared_ptr<soapy::device> _device;
            xtd::forms::vertical_layout_panel _layout;
            xtd::forms::combo_box _radio_source;
            rtlsdr_group_box _rtlsdr_box;
    };
}