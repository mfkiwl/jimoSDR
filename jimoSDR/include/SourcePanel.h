#pragma once

#include <xtd/xtd>
#include "GuiNotifier.h"

namespace jimo_sdr
{
    class SourcePanel : public xtd::forms::group_box
    {
        public:
            SourcePanel(GuiNotifier& notifier);
        private:
            void SourcesDropDown(xtd::object& sender, const xtd::event_args& e);
            void GetReceivers();
            void GotReceivers(xtd::object& sender, const xtd::event_args& e);
            void GotDriverKey(xtd::object& sender, const xtd::event_args& e);
            xtd::forms::combo_box m_sources;

            GuiNotifier& m_notifier;
    };
}