#include "properties_panel.h"

using namespace xtd::forms;

namespace jimo_sdr
{
    properties_panel::properties_panel()
    {
        auto_scroll(true);
        auto_size_mode(auto_size_mode::grow_and_shrink);
        anchor(anchor_styles::top | anchor_styles::bottom | anchor_styles::left);

        _source_label.text("None");
        _source_label.anchor(anchor_styles::all);
        _source_label.text_align(content_alignment::middle_center);
        
        _source_box.text("Source");
        _source_box.anchor(anchor_styles::left | anchor_styles::top | anchor_styles::right);
        _source_box << _source_label;
        _source_label.height(25);

        *this << _source_box;
        control_layout_style(_source_box, {40, size_type::absolute, true});
    }

    void properties_panel::source(const std::string& src) noexcept
    {
        _source_label.text(src);
    }
}