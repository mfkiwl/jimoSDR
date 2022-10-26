#include "SourcePanel.h"
#include "ControlSizes.h"
#include "ReceiverAction.h"
#include "RadioReceiver.h"
#include "GotReceiversEventArgs.h"
#include "GotDeviceDriverKeyEventArgs.h"
#include "GotSampleRatesEventArgs.h"
#include "GotCurrentSampleRateEventArgs.h"
#include "SetSampleRateEventArgs.h"
#include "SetSampleRateData.h"
#include "exceptions.h"
#include "sampling_mode.h"


using namespace xtd;
using namespace xtd::forms;
using namespace std::placeholders;

namespace jimo_sdr
{
    SourcePanel::SourcePanel(device_properties& deviceProps, GuiNotifier& notifier) 
        : m_notifier(notifier), m_deviceProps(deviceProps)
    {
        width(300);
        m_panelLabel.text("    Source");
        m_panelLabel.dock(dock_style::top);
        m_notifier.gotReceivers += xtd::event_handler(*this, &SourcePanel::GotReceivers);
        m_notifier.gotSampleRates += xtd::event_handler(*this, &SourcePanel::GotSampleRates);
        m_notifier.gotCurrentSampleRate += xtd::event_handler(*this, &SourcePanel::GotCurrentSampleRate);
        m_notifier.setSampleRate += xtd::event_handler(*this, &SourcePanel::SampleRateWasSet);

        m_deviceLabel.text("Device: ");
        m_deviceLabel.text_align(content_alignment::middle_right);
        m_deviceLabel.dock(dock_style::left);
        m_deviceLabel.width(propertiesPanelWidth / 2);

        m_sources.drop_down_style(combo_box_style::drop_down_list);
        m_sources.dock(dock_style::right);
        m_sources.width(propertiesPanelWidth / 2);
        m_sources.items().push_back("None");
        m_sources.drop_down += xtd::event_handler(*this, &SourcePanel::SourcesDropDown);
        m_sources.selected_value_changed += xtd::event_handler(*this, &SourcePanel::SourceValueChanged);

        m_devicePanel << m_deviceLabel << m_sources;
        m_devicePanel.dock(dock_style::top);
        m_devicePanel.width(propertiesPanelWidth);

        m_sampleRatesLabel.text("Sample Rate: ");
        m_sampleRatesLabel.text_align(content_alignment::middle_right);
        m_sampleRatesLabel.dock(dock_style::left);
        m_sampleRatesLabel.width(propertiesPanelWidth / 2);

        m_sampleRates.dock(dock_style::right);
        m_sampleRates.width(propertiesPanelWidth / 2);
        m_sampleRates.selected_value_changed += xtd::event_handler(*this, &SourcePanel::SampleRatesValueChanged);

        m_sampleRatesPanel << m_sampleRatesLabel << m_sampleRates;
        m_sampleRatesPanel.width(propertiesPanelWidth);

        m_samplingModeLabel.text("Sampling Mode: ");
        m_samplingModeLabel.text_align(content_alignment::middle_right);
        m_samplingModeLabel.dock(dock_style::left);

        m_samplingModes.dock(dock_style::right);
        m_samplingModes.width(propertiesPanelWidth / 2);
        m_samplingModes.items().push_back_range(sampling_mode::names());
        m_samplingModes.selected_index(static_cast<size_t>(m_deviceProps.sampling_mode().mode()));


        m_samplingModePanel << m_samplingModeLabel << m_samplingModes;

        m_spaceLabel1.dock(dock_style::top);
        m_spaceLabel2.dock(dock_style::top);
        m_spaceLabel3.dock(dock_style::top);

        m_groupBoxPanel.dock(dock_style::top);
        m_groupBoxPanel << m_devicePanel << m_spaceLabel1 << m_sampleRatesPanel << m_spaceLabel2;
        m_groupBoxPanel << m_samplingModePanel << m_spaceLabel3;
        m_groupBoxPanel.width(propertiesPanelWidth);

        m_groupBoxPanel.back_color(drawing::color::pink);

        m_groupBoxPanel.control_layout_style(m_devicePanel, {defaultControlHeight, size_type::absolute, true});
        m_groupBoxPanel.control_layout_style(m_spaceLabel1, { defaultSpacerHeight, size_type::absolute, true});
        m_groupBoxPanel.control_layout_style(m_sampleRatesPanel, {defaultControlHeight, size_type::absolute, true});
        m_groupBoxPanel.control_layout_style(m_spaceLabel2, { defaultSpacerHeight, size_type::absolute, true});
        m_groupBoxPanel.control_layout_style(m_samplingModePanel, {defaultControlHeight, size_type::absolute, true});
        m_groupBoxPanel.control_layout_style(m_spaceLabel3, { defaultSpacerHeight, size_type::absolute, true});

        *this << m_panelLabel << m_groupBoxPanel;
    }

    void SourcePanel::SourcesDropDown(xtd::object& sender, const xtd::event_args& e)
    {
            GetReceivers();
    }

    void SourcePanel::GetReceivers()
    {
        ReceiverAction getReceivers({ ReceiverTask::getReceivers,
            std::bind(&GuiNotifier::NotifyGotReceivers, &m_notifier, _1), nullptr} );
        RadioReceiver::GetInstance().QueueTask(getReceivers);
    }

    void SourcePanel::GotReceivers(xtd::object& sender, const xtd::event_args& e)
    {
        const auto& args = dynamic_cast<const GotReceiversEventArgs&>(e);
        m_devices = args.Devices();
        if (m_devices.cbegin() == m_devices.cend())
        {
            message_dialog msgDialog;
            msgDialog.buttons(message_dialog_buttons::ok_cancel);
            std::string message("There are no SDRs attached.\nAttach one, then click OK\n"
                + std::string("or click Cancel so you can close jimoSDR."));
            msgDialog.message(message);
            msgDialog.text("No SDRs Found");
            auto result = msgDialog.show_dialog(*this);
            if (result == dialog_result::ok)
            {
                GetReceivers();
            }
        }
        else
        {
            m_sources.items().clear();

            for (auto device : m_devices)
            {
                // change this to get "label" when combo_box is sized large enough.
                // xtd version 0.3.0?
                std::string devName = "RTL: " + (*device)["serial"];
                m_sources.items().push_back(devName);
            }
            if (m_sources.items().size() == 1)
            {
                m_sources.selected_index(0);
            }
            else if (m_deviceProps.Device() != nullptr)
            {
                std::string deviceLabel = "RTL: " + (*m_deviceProps.Device())["serial"];
                auto items = m_sources.items();
                auto end_it = items.cend();
                auto it = find(items.cbegin(), end_it, list_control::item(deviceLabel));
                if (it != end_it)
                {
                    m_sources.selected_item(*it);
                }
            }
       }
    }

    void SourcePanel::SourceValueChanged(xtd::object& sender, const xtd::event_args& e)
    {
        auto index = m_sources.selected_index();
        // if m_sources is empty, then index is invalid
        if (index >= 0 && index < m_devices.size())
        {
            m_deviceProps.clear();
            m_deviceProps.device(m_devices[index]);
            ReceiverAction getSampleRates({ ReceiverTask::getSampleRates,
                std::bind(&GuiNotifier::NotifyGotSampleRates, &m_notifier, _1), m_devices[index]} );
            RadioReceiver::GetInstance().QueueTask(getSampleRates);
            if (m_deviceProps.sample_rate() == 0.)
            {
                ReceiverAction getCurrentSampleRate({ ReceiverTask::getCurrentSampleRate,
                    std::bind(&GuiNotifier::NotifyGotCurrentSampleRate, &m_notifier, _1), m_devices[index] });
                RadioReceiver::GetInstance().QueueTask(getCurrentSampleRate);
            }
        }
    }

    void SourcePanel::GotSampleRates(xtd::object& sender, const xtd::event_args& e)
    {

        const auto& args = dynamic_cast<const GotSampleRatesEventArgs&>(e);
        auto rates = args.Rates();
        m_sampleRates.items().clear();
        std::transform(rates.cbegin(), rates.cend(), std::back_inserter(m_sampleRates.items()),
            [] (double rate) {
                    std::stringstream ss;
                    ss << rate / 1'000'000 << " MHz";
                    return ss.str(); });
    }

    void SourcePanel::GotCurrentSampleRate(xtd::object& sender, const xtd::event_args& e)
    {
        const auto& args = dynamic_cast<const GotCurrentSampleRateEventArgs&>(e);
        auto currentRate = args.Rate();    
        std::stringstream ss;
        ss << currentRate / 1'000'000. << " MHz";
        std::string rate = ss.str();
        auto items = m_sampleRates.items();
        auto end_it = items.cend();
        auto it = find(items.cbegin(), end_it, list_control::item(rate));
        if (it != end_it)
        {
            m_sampleRates.selected_item(*it);
        }
    }

    void SourcePanel::SampleRatesValueChanged(xtd::object& sender, const xtd::event_args& e)
    {
        std::stringstream ss(m_sampleRates.selected_item().to_string());
        double rate;
        ss >> rate;
        rate *= 1'000'000.;
        if (m_deviceProps.sample_rate() != rate)
        {
            SetSampleRateData sampleRateData { m_deviceProps.Device(), rate };
            ReceiverAction setSampleRate({ ReceiverTask::setSampleRate,
                std::bind(&GuiNotifier::NotifySetSampleRate, &m_notifier, _1), sampleRateData });
            RadioReceiver::GetInstance().QueueTask(setSampleRate);            
        }
    }

    void SourcePanel::SampleRateWasSet(xtd::object& sender, const xtd::event_args& e)
    {
        const auto& args = dynamic_cast<const SetSampleRateEventArgs&>(e);
        auto requestedRate = args.RequestedRate();
        auto actualRate = args.ActualRate();
        if (requestedRate != actualRate)
        {
            std::stringstream ss;
            ss << "Sampling rate change error";
            ss << "While attempting to set the requested sample rate of " << requestedRate;
            ss << "the actual rate was set to " << actualRate;
            ss << "Do you want to continue with the actual rate?";
            ss << R"(Click "Yes" to continue, and "No" to terminate the program)";
    
            dialog_result close = xtd::forms::message_box::show(*this, 
                ss.str(), 
                "Sampling rate change error",
                xtd::forms::message_box_buttons::yes_no, 
                xtd::forms::message_box_icon::warning);
            if (close == xtd::forms::dialog_result::no)
            {
                auto parent = this->parent();
                while (parent.has_value() && parent->get().name() != "MainForm")
                {
                    parent = parent->get().parent();
                }
                form& mainForm = dynamic_cast<form&>(parent->get());
                mainForm.close();
            }
            m_deviceProps.sample_rate(actualRate);
        }
    }
}