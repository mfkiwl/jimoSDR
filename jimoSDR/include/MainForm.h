#pragma once

#include <xtd/xtd>
#include "Device.h"
#include "device_properties.h"
#include "properties_panel.h"
#include "user_draw_buttons.h"
#include "number_display.h"
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
            void create_properties_panel();
            void create_right_panel();
            void _create_controls_panel();

            GuiNotifier m_notifier;
            std::shared_ptr<sdr::Device> _device;
            xtd::forms::vertical_layout_panel _vlp;
            xtd::forms::horizontal_layout_panel _controls_panel;
            xtd::forms::horizontal_layout_panel _main_panel;
            properties_panel _props_panel;
            xtd::forms::panel _right_panel;
            properties_button _props_button;
            xtd::forms::label _center_frequency_label;
            number_display m_centerFrequencyDisplay;

            device_properties m_deviceProps;
   };
}