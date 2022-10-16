#pragma once

#include <xtd/xtd>
#include "device.h"

using namespace xtd;
using namespace xtd::forms;


namespace jimo_sdr
{

    class MainForm;
    
    class properties_panel : public vertical_layout_panel
    {
        public:
            properties_panel(MainForm& frm);
            void source(const std::string& src) noexcept;
        private:
            MainForm& _main_form;
            xtd::forms::group_box _source_box;
            xtd::forms::button _source_button;
    };
}