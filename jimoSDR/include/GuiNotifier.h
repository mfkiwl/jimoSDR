#pragma once

#include <xtd/xtd>
#include <vector>
#include <any>
#include "GotReceiversEventArgs.h"
#include "GotDeviceDriverKeyEventArgs.h"
#include "GotSampleRatesEventArgs.h"
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
            xtd::event<GuiNotifier, xtd::event_handler> gotDriverKey;
            xtd::event<GuiNotifier, xtd::event_handler> gotSampleRates;
            // event raised when receivers are retrieved via Devices constructor
            void OnGotReceivers(const std::vector<std::any>& args)
            {
                auto devices = any_cast<sdr::devices>(args[0]);
                GotReceiversEventArgs e(devices);
                gotReceivers.invoke(*this, e);
            }

            void OnGotDeviceDriverKey(const std::vector<std::any>& args)
            {
                auto key = any_cast<std::string>(args[0]);
                GotDeviceDriverKeyEventArgs e(key);
                gotDriverKey.invoke(*this, e);
            }

            void OnGotSampleRates(const std::vector<std::any>& args)
            {
                auto rates = any_cast<std::vector<double>>(args[0]);
                GotSampleRatesEventArgs e(rates);
                gotSampleRates.invoke(*this, e);
            }

            void NotifyGotReceivers(const std::any devices)
            {
                std::vector<std::any> args;
                args.push_back(devices);
                m_synchronizer.begin_invoke({ *this, &GuiNotifier::OnGotReceivers }, args);
            }

            void NotifyGotDeviceDriverKey(const std::any key)
            {
                std::vector<std::any> args;
                args.push_back(key);
                m_synchronizer.begin_invoke({ *this, &GuiNotifier::OnGotDeviceDriverKey }, args);
            }

            void NotifyGotSampleRates(const std::any rates)
            {
                std::vector<std::any> args;
                args.push_back(rates);
                m_synchronizer.begin_invoke({ *this, &GuiNotifier::OnGotSampleRates }, args);
            }
        private:
            xtd::forms::control& m_synchronizer;
    };
}