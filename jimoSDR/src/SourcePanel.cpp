#include "SourcePanel.h"
#include "ReceiverAction.h"
#include "RadioReceiver.h"
#include "GotReceiversEventArgs.h"
#include "exceptions.h"


using namespace xtd;
using namespace xtd::forms;

namespace jimo_sdr
{
    SourcePanel::SourcePanel(GuiNotifier& notifier) : m_notifier(notifier)
    {
        text("Source");
        anchor(anchor_styles::left | anchor_styles::top | anchor_styles::right);
        m_notifier.gotReceivers += xtd::event_handler(*this, &SourcePanel::GotReceivers);

        m_sources.drop_down_style(combo_box_style::drop_down_list);
        m_sources.anchor(anchor_styles::left | anchor_styles::top);
        m_sources.items().push_back("None");
        m_sources.drop_down += xtd::event_handler(*this, &SourcePanel::SourcesDropDown);
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
        sdr::devices devices = args.Devices();
        if (devices.cbegin() == devices.cend())
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
            std::transform(devices.cbegin(), devices.cend(),
                std::back_inserter(m_sources.items()),
                [] (std::shared_ptr<sdr::device> dev) { return dev->driver_key(); });
        }
    }
}