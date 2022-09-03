#include "source_dialog.h"

using namespace xtd;
using namespace xtd::forms;

namespace jimo_sdr
{
    source_dialog::source_dialog()
    {
        _device_label.text("Device:");
        _device_label.anchor(anchor_styles::top | anchor_styles::left | anchor_styles::bottom);
        _device_label.text_align(content_alignment::middle_left);

        _hardware_key_label.text("R820T");
        _hardware_key_label.anchor(anchor_styles::top | anchor_styles::right | anchor_styles::left);
        _hardware_key_label.text_align(content_alignment::middle_center);

        _device_panel.padding(2);
        _device_panel.anchor(anchor_styles::left | anchor_styles::top | anchor_styles::bottom);
        _device_panel << _device_label << _hardware_key_label ;
        _device_panel.control_layout_style(_device_label, {.5f, size_type::percent, true});
        _device_panel.control_layout_style(_hardware_key_label, {size_type::auto_size, true});

        _device_combo_box.anchor(anchor_styles::left | anchor_styles::right);


        _vert_dialog_panel.anchor(anchor_styles::all);
        _vert_dialog_panel << _device_panel << _device_combo_box;
        _vert_dialog_panel.control_layout_style(_device_panel, {size_type::auto_size, true});
        _vert_dialog_panel.control_layout_style(_device_combo_box, {size_type::auto_size, true});
        _device_label.height(22);
        _hardware_key_label.height(_device_label.height());
        _device_panel.height(_device_label.height());

        _device_combo_box.height(_device_label.height());



        *this << _vert_dialog_panel;

    
    }
}