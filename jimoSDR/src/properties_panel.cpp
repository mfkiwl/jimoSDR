#include "properties_panel.h"
#include "MainForm.h"

using namespace xtd::forms;

namespace jimo_sdr
{
    properties_panel::properties_panel(MainForm& f)
        : _main_form(f)
    {
        auto_scroll(true);
        auto_size_mode(auto_size_mode::grow_and_shrink);
        anchor(anchor_styles::top | anchor_styles::bottom | anchor_styles::left);

        _source_button.text("None");
        _source_button.anchor(anchor_styles::all);
        _source_button.text_align(content_alignment::middle_center);
        _source_button.click += xtd::event_handler(
            _main_form, &MainForm::on_source_button_click);
        
        _source_box.text("Source");
        _source_box.anchor(anchor_styles::left | anchor_styles::top | anchor_styles::right);
        _source_box << _source_button;
        _source_button.height(40);

        *this << _source_box;
        control_layout_style(_source_box, {50, size_type::absolute, true});
    }

    void properties_panel::source(const std::string& src) noexcept
    {
        _source_button.text(src);
    }
}