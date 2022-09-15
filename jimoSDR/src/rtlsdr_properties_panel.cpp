#include "rtlsdr_properties_panel.h"

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
        *this << _sample_rate_label << _sample_rate_combo_box;

        _sampling_mode_label.text("Sampling Mode");
        _sampling_mode_label.text_align(content_alignment::middle_left);

        _sampling_mode_combo_box.items().push_back_range({"Quadrature", "Direct (I Branch)", "Direct (Q Branch)"});
        _sampling_mode_combo_box.selected_index_changed += xtd::event_handler(
            *this, &rtlsdr_properties_panel::_on_sampling_mode_selected);
        _set_sampling_mode();


        *this << _sampling_mode_label << _sampling_mode_combo_box;
    }

    void rtlsdr_properties_panel::_populate_sample_rate_combo_box()
    {
        auto rates = _dev_props.device()->sample_rates(soapy::device::direction::rx, 0);
        _sample_rate_combo_box.items().clear();
        for(auto rate : rates)
        {
            // std::format is not in the standard clang++ library, so we
            // use stringstream here.
            std::stringstream ss;
            ss << rate / 1'000'000 << " MHz";
            _sample_rate_combo_box.items().push_back(ss.str());
        }
        auto current_rate = _dev_props.device()->sample_rate(soapy::device::direction::rx, 0);
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

        void rtlsdr_properties_panel::_on_sampling_mode_selected(object& sender, const xtd::event_args& e)
        {
            switch(_sampling_mode_combo_box.selected_index())
            {
                case 0:
                    _dev_props.sampling_mode(device_properties::sampling_mode::quadrature);
                    break;
                case 1:
                    _dev_props.sampling_mode(device_properties::sampling_mode::i_branch);
                    break;  
                case 2:
                    _dev_props.sampling_mode(device_properties::sampling_mode::q_branch);
                    break;
            }
        }

        void rtlsdr_properties_panel::_set_sampling_mode()
        {
            switch(_dev_props.sampling_mode())
            {
                case device_properties::sampling_mode::quadrature:
                    _sampling_mode_combo_box.selected_index(0);
                    break;
                case device_properties::sampling_mode::i_branch:
                    _sampling_mode_combo_box.selected_index(1);
                    break;
                case device_properties::sampling_mode::q_branch:
                    _sampling_mode_combo_box.selected_index(2);
                    break;
            }
        }

}