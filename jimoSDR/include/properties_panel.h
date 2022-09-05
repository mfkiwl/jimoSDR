#pragma once

#include <xtd/xtd>
#include "device.h"

using namespace xtd;
using namespace xtd::forms;


namespace jimo_sdr
{
    class main_form;
    
    class properties_panel : public vertical_layout_panel
    {
        public:
            properties_panel(main_form& frm);
            void source(const std::string& src) noexcept;
        private:
            main_form& _main_form;
            xtd::forms::group_box _source_box;
            xtd::forms::button _source_button;
    };
}