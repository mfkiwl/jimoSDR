#include <sstream>
#include "rtlsdr_properties_panel.h"
#include "sampling_mode.h"

using namespace xtd;
using namespace xtd::forms;

namespace jimo_sdr
{
    rtlsdr_properties_panel::rtlsdr_properties_panel(device_properties& device_props)
            : _dev_props(device_props)
    {
        _sample_rate_label.text("Sample Rate");
        _sample_rate_label.text_align(content_alignment::middle_left);
        _populate_sample_rate_combo_box();
        _sample_rate_combo_box.selected_index_changed += event_handler(*this, &rtlsdr_properties_panel::_on_sample_rate_changed);
        *this << _sample_rate_label << _sample_rate_combo_box;

        _sampling_mode_label.text("Sampling Mode");
        _sampling_mode_label.text_align(content_alignment::middle_left);

        _sampling_mode_combo_box.items().push_back_range(sampling_mode::names());
        _sampling_mode_combo_box.selected_index(_dev_props.sampling_mode().mode_as_int());
        // note: we set mode before adding event handler because the event will save the
        // mode in the same place that we retrieved the mode from
        _sampling_mode_combo_box.selected_index_changed += [&] () 
            {  _dev_props.sampling_mode().mode(_sampling_mode_combo_box.selected_index()); };

        *this << _sampling_mode_label << _sampling_mode_combo_box;
    }

    void rtlsdr_properties_panel::_populate_sample_rate_combo_box()
    {
        auto rates = _dev_props.device()->sample_rates(sdr::device::direction::rx, 0);
        _sample_rate_combo_box.items().clear();
        std::transform(rates.cbegin(), rates.cend(), std::back_inserter(_sample_rate_combo_box.items()),
            [] (double rate) {
                    std::stringstream ss;
                    ss << rate / 1'000'000 << " MHz";
                    return ss.str(); });
        auto current_rate = _dev_props.device()->sample_rate(sdr::device::direction::rx, 0);
        std::stringstream ss;
        ss << current_rate / 1'000'000 << " MHz";
        std::string rate = ss.str();
        auto items = _sample_rate_combo_box.items();
        auto end_it = items.cend();
        auto it = find(items.cbegin(), end_it, list_control::item(rate));
        if(it != end_it)
        {
            _sample_rate_combo_box.selected_item(*it);
        }
    }

    void rtlsdr_properties_panel::_on_sample_rate_changed(object& sender,  const xtd::event_args& e)
    {
        std::stringstream ss(_sample_rate_combo_box.selected_item().to_string());
        double rate;
        ss >> rate;
        rate *= 1'000'000.;
        _dev_props.sample_rate(rate);
        _dev_props.device()->sample_rate(sdr::device::direction::rx, 0, rate);
    }
}