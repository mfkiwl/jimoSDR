#pragma once

#include <xtd/xtd>
#include "device_properties.h"
#include "GuiNotifier.h"
#include "Devices.h"

namespace jimo_sdr
{
    class SourcePanel : public xtd::forms::group_box
    {
        public:
            SourcePanel(device_properties& deviceProps, GuiNotifier& notifier);
        private:
            void SourcesDropDown(xtd::object& sender, const xtd::event_args& e);
            void SourceValueChanged(xtd::object& sender, const xtd::event_args& e);
            void GetReceivers();
            void GotReceivers(xtd::object& sender, const xtd::event_args& e);
            void GotDriverKey(xtd::object& sender, const xtd::event_args& e);
            xtd::forms::combo_box m_sources;

            GuiNotifier& m_notifier;
            device_properties& m_deviceProps;
            sdr::devices m_devices;
    };
}