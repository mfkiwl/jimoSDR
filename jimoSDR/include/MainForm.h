#pragma once

#include <xtd/xtd>
#include "Device.h"
#include "device_properties.h"
#include "properties_panel.h"
#include "user_draw_buttons.h"
#include "NumberDisplay.h"
#include "ReceiverAction.h"
#include "RadioReceiver.h"

using namespace xtd::drawing;

namespace jimo_sdr
{
    const color right_panel_background = color::from_argb(0xFF202020);

    class MainForm : public xtd::forms::form
    {
        public:
            MainForm();
        protected:
            void on_form_closing(xtd::forms::form_closing_event_args& e) override;
       private:
            void GotCenterFrequency(xtd::object& sender, const xtd::event_args& e);
            void CreatePropertiesPanel();
            void CreateRightPanel();
            void CreateControlsPanel();

            GuiNotifier m_notifier;
            xtd::forms::vertical_layout_panel m_mainPanel;
            xtd::forms::horizontal_layout_panel m_controlsPanel;
            xtd::forms::horizontal_layout_panel m_leftRightPanel;
            properties_panel m_propertiesPanel;
            xtd::forms::panel m_rightPanel;
            properties_button m_propertiesButton;
            xtd::forms::label m_centerFrequencyLabel;
            NumberDisplay m_centerFrequencyDisplay;

            device_properties m_deviceProperties;
   };
}