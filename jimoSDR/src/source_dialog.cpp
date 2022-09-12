#include "source_dialog.h"

using namespace xtd;
using namespace xtd::forms;

namespace jimo_sdr
{
    source_dialog::source_dialog(device_properties& device_properties)
        : _device_props(device_properties)
    {
        text("SDR Device");

        _device_label.text("Device");
        _device_label.text_align(content_alignment::middle_left);

        _hardware_key_label.text_align(content_alignment::middle_center);

        _device_panel.padding(2);
        _device_panel << _device_label << _hardware_key_label ;
        _device_panel.control_layout_style(_device_label, {.5f, size_type::percent, true});
        _device_panel.control_layout_style(_hardware_key_label, {size_type::auto_size, true});

        _device_combo_box.anchor(anchor_styles::left | anchor_styles::right);
        _device_combo_box.selected_index_changed += xtd::event_handler(
            *this, &source_dialog::_on_device_source_selected);
 
        _vert_dialog_panel.anchor(anchor_styles::left | anchor_styles::top | anchor_styles::right);
        _vert_dialog_panel << _device_panel << _device_combo_box;
        _vert_dialog_panel.control_layout_style(_device_panel, {size_type::auto_size, true});
        _vert_dialog_panel.control_layout_style(_device_combo_box, {size_type::auto_size, true});
        *this << _vert_dialog_panel;

        _ok_button.text("Ok");
        _ok_button.dialog_result(dialog_result::ok);
        accept_button(_ok_button);
        client_size(_vert_dialog_panel.size() + _ok_button.size());
        client_size(drawing::size::add(client_size(), {7, 7}));
        auto dialog_size = client_size();
        auto bsize = _ok_button.size();
        _ok_button.location({dialog_size.width() - bsize.width() - 5,
            dialog_size.height() - bsize.height() - 5});
        *this << _ok_button;
        // must populate _device_combo_box after _vert_dialog_panel is added to this
        _soapy_devices = std::make_unique<soapy::devices>();
        while(_soapy_devices->cbegin() == _soapy_devices->cend())
        {
            message_dialog msg_dlg;
            msg_dlg.buttons(message_dialog_buttons::ok_cancel);
            std::string message("There are no SDRs attached.\nAttach one, then click OK\n" +
                std::string("or click Cancel to close jimoSDR"));
            msg_dlg.message(message);
            msg_dlg.text("No SDRs Found");
            auto res = msg_dlg.show_dialog(*this);
            if(res == dialog_result::cancel)
            {
                close();
            }
            else
            {
                _soapy_devices.reset();
                _soapy_devices = std::make_unique<soapy::devices>();
            }

        }
        for(auto& pdev : *_soapy_devices)
        {
            _device_combo_box.items().push_back(pdev->driver_key());
        }
        // if only one item, select it
        if(_device_combo_box.items().size() == 1)
        {
            _device_combo_box.selected_index(0);
        }
        else if(_device_combo_box.items().size() == 0)
        {
        }
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

    void source_dialog::_on_device_source_selected(object& sender, const xtd::event_args& e)
    {
        _device_props.device((*_soapy_devices)[_device_combo_box.selected_index()]);
        _show_device_properties();
    }

    void source_dialog::_show_device_properties()
    {
        _hardware_key_label.text(_device_props.device()->hardware_key());
        if((*_device_props.device())["driver"] == "rtlsdr")
        {
            _rtlsdr_props_panel = std::make_unique<rtlsdr_properties_panel>(_device_props);
            _vert_dialog_panel << *_rtlsdr_props_panel;
            _vert_dialog_panel.control_layout_style(*_rtlsdr_props_panel, {size_type::auto_size, true});
        }
    }
}