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
            void SampleRatesValueChanged(xtd::object& sender, const xtd::event_args& e);
            void SamplingModeValueChanged(xtd::object& sender, const xtd::event_args& e);
            void GetReceivers();
            void GotReceivers(xtd::object& sender, const xtd::event_args& e);
            void GotSampleRates(xtd::object& sender, const xtd::event_args& e);
            void GotCurrentSampleRate(xtd::object& sender, const xtd::event_args& e);
            void SampleRateWasSet(xtd::object& sender, const xtd::event_args& e);
            xtd::forms::label m_panelLabel;
            xtd::forms::horizontal_layout_panel m_devicePanel;
            xtd::forms::label m_deviceLabel;
            xtd::forms::combo_box m_sources;
            xtd::forms::label m_spaceLabel1;
            xtd::forms::vertical_layout_panel m_groupBoxPanel;
            xtd::forms::horizontal_layout_panel m_sampleRatesPanel;
            xtd::forms::label m_sampleRatesLabel;
            xtd::forms::combo_box m_sampleRates;
            xtd::forms::label m_spaceLabel2;
            xtd::forms::horizontal_layout_panel m_samplingModePanel;
            xtd::forms::label m_samplingModeLabel;
            xtd::forms::combo_box m_samplingModes;
            xtd::forms::label m_spaceLabel3;

            GuiNotifier& m_notifier;
            device_properties& m_deviceProps;
            sdr::devices m_devices;
    };
}