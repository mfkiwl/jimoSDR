#pragma once

#include <xtd/xtd>
#include "device.h"
#include "SourcePanel.h"
#include "properties_panel.h"
#include "device_properties.h"
#include "GuiNotifier.h"

using namespace xtd;
using namespace xtd::forms;


namespace jimo_sdr
{

    class MainForm;
    
    class properties_panel : public vertical_layout_panel
    {
        public:
            properties_panel(MainForm& frm, device_properties& deviceProps, GuiNotifier& notifier);
            void source(const std::string& src) noexcept;
        private:
            [[maybe_unused]]MainForm& _main_form;
            device_properties& m_deviceProps;
            SourcePanel m_sourcePanel;
            xtd::forms::group_box _source_box;
            xtd::forms::button _source_button;
    };
}