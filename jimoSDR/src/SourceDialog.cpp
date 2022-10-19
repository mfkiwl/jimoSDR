#include "SourceDialog.h"
#include "RadioReceiver.h"
#include "ReceiverAction.h"
#include "Devices.h"
#include "exceptions.h"

using namespace xtd;
using namespace xtd::forms;
using namespace std::placeholders;

namespace jimo_sdr
{
    SourceDialog::SourceDialog(GuiNotifier& notifier, device_properties& device_properties)
        : m_notifier(notifier), _device_props(device_properties)
    {
        notifier.got_receivers += xtd::event_handler(*this, &SourceDialog::gotReceivers);
        start_position(xtd::forms::form_start_position::center_parent);
        text("SDR Device");
        close_box(false);
        maximize_box(false);
        minimize_box(false);
        maximum_size(size());
        minimum_size(size());

        _build_device_panel();
        _device_combo_box.selected_index_changed += xtd::event_handler(
            *this, &SourceDialog::_on_device_source_selected);
 
        _vert_dialog_panel.dock(dock_style::top);
        _vert_dialog_panel << _device_panel << _device_combo_box;
        _vert_dialog_panel.control_layout_style(_device_panel, {22, size_type::absolute, false});

       *this << _vert_dialog_panel;
        _vert_dialog_panel.height(200);

        _build_buttons_panel();
        *this << _buttons_panel;
        getAttachedSDRs();
   }

    SourceDialog::~SourceDialog() noexcept
    {
        m_notifier.got_receivers -= xtd::event_handler(*this, &SourceDialog::gotReceivers);
    }
    
    void SourceDialog::_on_device_source_selected(const object& sender, const xtd::event_args& e)
    {
        _device_props.device((m_sdrDevices)[_device_combo_box.selected_index()]);
        _show_device_properties();
    }
    
    void SourceDialog::_show_device_properties()
    {
        _hardware_key_label.text(_device_props.device()->hardware_key());
        if((*_device_props.device())["driver"] == "rtlsdr")
        {
            _rtlsdr_props_panel = std::make_unique<rtlsdr_properties_panel>(_device_props);
            _vert_dialog_panel << *_rtlsdr_props_panel;
        }
    }

    void SourceDialog::_build_device_panel()
    {
        _device_label.text("Device");
        _device_label.text_align(content_alignment::middle_left);

        _hardware_key_label.text_align(content_alignment::middle_center);

        _device_panel << _device_label << _hardware_key_label ;
        _device_panel.control_layout_style(_device_label, {.5f, size_type::percent, true});
        _device_panel.control_layout_style(_hardware_key_label, {size_type::auto_size, true});        
    }

    void SourceDialog::_build_buttons_panel()
    {
        _ok_button.text("Ok");
        _ok_button.dialog_result(dialog_result::ok);
        accept_button(_ok_button);

        _buttons_panel.dock(dock_style::bottom);
        _buttons_panel << _filler_label << _ok_button;
        _buttons_panel.control_layout_style(_ok_button, {_ok_button.width(), size_type::absolute, false});
        _buttons_panel.control_layout_style(_filler_label, {size_type::auto_size, true});
        _buttons_panel.height(45);
        _buttons_panel.padding(10);
    }

    void SourceDialog::getAttachedSDRs()
    {
        ReceiverAction getReceivers { ReceiverTask::getReceivers, 
            std::bind(&GuiNotifier::notify_got_receivers, &m_notifier, _1), nullptr };
        RadioReceiver::GetInstance().QueueTask(getReceivers);
    }

    void SourceDialog::gotReceivers(xtd::object& sender, const xtd::event_args& e)
    {
        const auto& gotThem = dynamic_cast<const GotReceiversEventArgs&>(e);
        m_sdrDevices = gotThem.Devices();
        if (m_sdrDevices.cbegin() == m_sdrDevices.cend())
        {
            message_dialog msg_dlg;
            msg_dlg.buttons(message_dialog_buttons::ok_cancel);
            std::string message("There are no SDRs attached.\nAttach one, then click OK\n" +
                std::string("or click Cancel so you can close jimoSDR"));
            msg_dlg.message(message);
            msg_dlg.text("No SDRs Found");
            auto res = msg_dlg.show_dialog(*this);
            if(res == dialog_result::cancel)
            {
                throw no_sdrs_exception();
            }
            else
            {
                m_sdrDevices.clear();
                getAttachedSDRs();
            }
        }
        else
        {
            _populate_device_combo_box();
            _select_appropriate_device();
        }
    }

    void SourceDialog::_populate_device_combo_box()
    {
        std::transform(m_sdrDevices.cbegin(), m_sdrDevices.cend(), std::back_inserter(_device_combo_box.items()),
            [] (std::shared_ptr<sdr::device> dev) { return dev->driver_key(); });
    }

    void SourceDialog::_select_appropriate_device()
    {
        // if only one item, select it
        if(_device_combo_box.items().size() == 1)
        {
            _device_combo_box.selected_index(0);
        }
        // else select previously selected device
        else if(_device_props.device() != nullptr)
        {
            auto device = _device_props.device()->driver_key();
            auto devices = _device_combo_box.items();
            auto end_it = devices.cend();
            auto it = find(devices.cbegin(), end_it, list_control::item(device));
            if(it != end_it)
            {
                _device_combo_box.selected_item(*it);
            }
        }
    }
}