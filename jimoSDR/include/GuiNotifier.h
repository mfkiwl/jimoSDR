#pragma once

#include <xtd/xtd>
#include <vector>
#include <any>
#include "GotReceiversEventArgs.h"
#include "Devices.h"

using namespace std::placeholders;

namespace jimo_sdr
{
    class GuiNotifier : public xtd::object
    {
        public:
            GuiNotifier(xtd::forms::control& synchronizer) : m_synchronizer(synchronizer) {}
            // Events
            xtd::event<GuiNotifier, xtd::event_handler> gotReceivers;
            // event raised when receivers are retrieved via Devices constructor
            void OnGotReceivers(const std::vector<std::any>& args)
            {
                auto devices = any_cast<sdr::devices>(args[0]);
                GotReceiversEventArgs e(devices);
                gotReceivers.invoke(*this, e);
            }

            void NotifyGotReceivers(const std::any devices)
            {
                std::vector<std::any> args;
                args.push_back(devices);
                m_synchronizer.begin_invoke({ *this, &GuiNotifier::OnGotReceivers }, args);
            }
        private:
            xtd::forms::control& m_synchronizer;
    };
}