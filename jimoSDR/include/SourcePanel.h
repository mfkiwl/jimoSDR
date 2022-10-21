#pragma once

#include <xtd/xtd>
#include "device_properties.h"
#include "GuiNotifier.h"
#include "Devices.h"

namespace jimo_sdr
{
    class SourcePanel : public xtd::forms::vertical_layout_panel
    {
        public:
            SourcePanel(device_properties& deviceProps, GuiNotifier& notifier);
        private:
            void SourcesDropDown(xtd::object& sender, const xtd::event_args& e);
            void SourceValueChanged(xtd::object& sender, const xtd::event_args& e);
            void GetReceivers();
            void GotReceivers(xtd::object& sender, const xtd::event_args& e);
            void GotDriverKey(xtd::object& sender, const xtd::event_args& e);
            xtd::forms::label m_panelLabel;
            xtd::forms::label m_spaceLabel1;
            xtd::forms::combo_box m_sources;
            xtd::forms::label m_spaceLabel2;
            xtd::forms::vertical_layout_panel m_groupBoxPanel;
            xtd::forms::horizontal_layout_panel m_sampleRatesPanel;
            xtd::forms::label m_sampleRatesLabel;
            xtd::forms::combo_box m_sampleRates;

            GuiNotifier& m_notifier;
            device_properties& m_deviceProps;
            sdr::devices m_devices;
    };
}