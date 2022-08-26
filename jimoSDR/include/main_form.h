#pragma once

#include <xtd/xtd>
#include "devices.h"
#include "properties_panel.h"

using namespace xtd::drawing;

namespace jimo_sdr
{
    const color right_panel_background = color::from_argb(0xFF202020);

    class main_form : public xtd::forms::form
    {
        public:
            main_form(soapy::devices& soapy_devices);
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

            properties_panel _props_panel;
            xtd::forms::panel _right_panel;
   };
}