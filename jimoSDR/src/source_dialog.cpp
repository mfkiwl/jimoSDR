#include "source_dialog.h"
#include "exceptions.h"

using namespace xtd;
using namespace xtd::forms;

namespace jimo_sdr
{
    source_dialog::source_dialog(device_properties& device_properties)
        : _device_props(device_properties)
    {
        start_position(xtd::forms::form_start_position::center_parent);
        text("SDR Device");
        close_box(false);
        maximize_box(false);
        minimize_box(false);
        maximum_size(size());
        minimum_size(size());

        _build_device_panel();
        _device_combo_box.selected_index_changed += xtd::event_handler(
            *this, &source_dialog::_on_device_source_selected);
 
        _vert_dialog_panel.dock(dock_style::top);
        _vert_dialog_panel << _device_panel << _device_combo_box;
        _vert_dialog_panel.control_layout_style(_device_panel, {22, size_type::absolute, false});

        _retrieve_attached_sdrs();
        _populate_device_combo_box();
        _select_appropriate_device();

        *this << _vert_dialog_panel;
        _vert_dialog_panel.height(200);

        _build_buttons_panel();
        *this << _buttons_panel;

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
        }
    }

    void source_dialog::_build_device_panel()
    {
        _device_label.text("Device");
        _device_label.text_align(content_alignment::middle_left);

        _hardware_key_label.text_align(content_alignment::middle_center);

        _device_panel << _device_label << _hardware_key_label ;
        _device_panel.control_layout_style(_device_label, {.5f, size_type::percent, true});
        _device_panel.control_layout_style(_hardware_key_label, {size_type::auto_size, true});        
    }

    void source_dialog::_build_buttons_panel()
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

    void source_dialog::_retrieve_attached_sdrs()
    {
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
                throw no_sdrs_exception();
            }
            else
            {
                _soapy_devices.reset();
                _soapy_devices = std::make_unique<soapy::devices>();
            }
        }
    }

    void source_dialog::_populate_device_combo_box()
    {
        std::transform(_soapy_devices->cbegin(), _soapy_devices->cend(), std::back_inserter(_device_combo_box.items()),
            [] (std::shared_ptr<soapy::device> dev) { return dev->driver_key(); });
    }

    void source_dialog::_select_appropriate_device()
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