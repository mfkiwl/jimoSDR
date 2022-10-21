#include "SourcePanel.h"
#include "ReceiverAction.h"
#include "RadioReceiver.h"
#include "GotReceiversEventArgs.h"
#include "GotDeviceDriverKeyEventArgs.h"
#include "exceptions.h"


using namespace xtd;
using namespace xtd::forms;

namespace jimo_sdr
{
    SourcePanel::SourcePanel(device_properties& deviceProps, GuiNotifier& notifier) 
        : m_notifier(notifier), m_deviceProps(deviceProps)
    {
        text("Source");
        anchor(anchor_styles::left | anchor_styles::top | anchor_styles::right);
        m_notifier.gotReceivers += xtd::event_handler(*this, &SourcePanel::GotReceivers);
        m_notifier.gotDriverKey += xtd::event_handler(*this, &SourcePanel::GotDriverKey);

        m_sources.drop_down_style(combo_box_style::drop_down_list);
        m_sources.anchor(anchor_styles::left | anchor_styles::top | anchor_styles::right);
        m_sources.items().push_back("None");
        m_sources.drop_down += xtd::event_handler(*this, &SourcePanel::SourcesDropDown);
        m_sources.selected_value_changed += xtd::event_handler(*this, &SourcePanel::SourceValueChanged);
        *this << m_sources;
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
                ReceiverAction getDriverKey({ ReceiverTask::getDriverKey,
                    std::bind(&GuiNotifier::NotifyGotDeviceDriverKey, &m_notifier, _1), device} );
                RadioReceiver::GetInstance().QueueTask(getDriverKey);
            }
       }
    }

    void SourcePanel::GotDriverKey(xtd::object& sender, const xtd::event_args& e)
    {
        const auto& args = dynamic_cast<const GotDeviceDriverKeyEventArgs&>(e);
        auto key = args.DriverKey();
        m_sources.items().push_back(key);
    }

    void SourcePanel::SourceValueChanged(xtd::object& sender, const xtd::event_args& e)
    {
        auto index = m_sources.selected_index();
        m_deviceProps.device(m_devices[index]);
    }
}