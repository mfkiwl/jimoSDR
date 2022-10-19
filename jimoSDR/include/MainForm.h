#pragma once

#include <xtd/xtd>
#include "device.h"
#include "properties_panel.h"
#include "user_draw_buttons.h"
#include "SourceDialog.h"
#include "device_properties.h"
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
            void show_source_dlg();
            void on_source_button_click(xtd::object& sender, const xtd::event_args& e);
        protected:
            void on_form_closing(xtd::forms::form_closing_event_args& e) override;
       private:
            void VisibleChanged(xtd::object& sender, const xtd::event_args& e);
            void create_properties_panel();
            void create_right_panel();
            void _create_controls_panel();

            std::shared_ptr<sdr::device> _device;
            xtd::forms::vertical_layout_panel _vlp;
            xtd::forms::horizontal_layout_panel _controls_panel;
            xtd::forms::horizontal_layout_panel _main_panel;
            properties_panel _props_panel;
            xtd::forms::panel _right_panel;
            properties_button _props_button;
            xtd::forms::label _center_frequency_label;
            number_display _center_frequency_display;

            bool m_starting;
            GuiNotifier m_notifier;
            device_properties _device_props;
   };
}