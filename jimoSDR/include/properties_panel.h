#pragma once

#include <xtd/xtd>
#include "device.h"

using namespace xtd;
using namespace xtd::forms;


namespace jimo_sdr
{
    class properties_panel : public vertical_layout_panel
    {
        public:
            properties_panel();
            void source(const std::string& src) noexcept;
        private:
            xtd::forms::group_box _source_box;
            xtd::forms::label _source_label;
    };
}