#pragma once

#include <xtd/xtd>
#include <vector>
#include <any>
#include "GotReceiversEventArgs.h"
#include "GotDeviceDriverKeyEventArgs.h"
#include "GotSampleRatesEventArgs.h"
#include "GotCurrentSampleRateEventArgs.h"
#include "Devices.h"

namespace jimo_sdr
{
    class GuiNotifier : public xtd::object
    {
        public:
            GuiNotifier(xtd::forms::control& synchronizer);
            // Events
            xtd::event<GuiNotifier, xtd::event_handler> gotReceivers;
            xtd::event<GuiNotifier, xtd::event_handler> gotDriverKey;
            xtd::event<GuiNotifier, xtd::event_handler> gotSampleRates;
            xtd::event<GuiNotifier, xtd::event_handler> gotCurrentSampleRate;

            void OnGotReceivers(const std::vector<std::any>& args);
            void OnGotDeviceDriverKey(const std::vector<std::any>& args);
            void OnGotSampleRates(const std::vector<std::any>& args);
            void OnGotCurrentSampleRate(const std::vector<std::any>& args);

            void NotifyGotReceivers(const std::any devices);
            void NotifyGotDeviceDriverKey(const std::any key);
            void NotifyGotSampleRates(const std::any rates);
            void NotifyGotCurrentSampleRate(const std::any rate);

        private:
            xtd::forms::control& m_synchronizer;
    };
}