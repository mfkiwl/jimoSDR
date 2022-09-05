#pragma once

#include <xtd/xtd>
#include "device.h"
#include "properties_panel.h"
#include "user_draw_buttons.h"
#include "source_dialog.h"
#include "device_properties.h"

using namespace xtd::drawing;

namespace jimo_sdr
{
    const color right_panel_background = color::from_argb(0xFF202020);

    class main_form : public xtd::forms::form
    {
        public:
            main_form();
            void show_source_dlg();
            void on_source_button_click(xtd::object& sender, const xtd::event_args& e);
        protected:
            void on_form_closing(xtd::forms::form_closing_event_args& e) 
                override {
                    e.cancel(xtd::forms::message_box::show(*this, 
                        "Are you sure you want exit?", 
                        "Close Form", xtd::forms::message_box_buttons::yes_no, 
                        xtd::forms::message_box_icon::question) == 
                            xtd::forms::dialog_result::no);};

        private:
            void create_properties_panel();
            void create_right_panel();

            std::shared_ptr<soapy::device> _device;
            xtd::forms::vertical_layout_panel _vlp;
            xtd::forms::horizontal_layout_panel _controls_panel;
            xtd::forms::horizontal_layout_panel _main_panel;
            properties_panel _props_panel;
            xtd::forms::panel _right_panel;
            properties_button _props_button;

            device_properties _device_props;
   };
}