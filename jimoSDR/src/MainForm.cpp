#include "MainForm.h"
#include "ControlSizes.h"
#include "GotCenterFrequencyEventArgs.h"

using namespace xtd;
using namespace xtd::forms;
using namespace xtd::drawing;

namespace jimo_sdr
{
    MainForm::MainForm()
        : m_notifier(*this), m_propertiesPanel(*this, m_deviceProperties, m_notifier), 
          m_centerFrequencyDisplay(10,3)
    {
        text("jimoSDR");
        name("MainForm");
        size({mainFormDefaultWidth, mainFormDefaultHeight});
        minimum_size({mainFormMinimumWidth, mainFormMinimumHeight});
        start_position(xtd::forms::form_start_position::center_screen);
        m_notifier.gotCenterFrequency += xtd::event_handler(*this, &MainForm::GotCenterFrequency);

        CreateControlsPanel();
        CreatePropertiesPanel();
        CreateRightPanel();
        m_leftRightPanel << m_propertiesPanel << m_rightPanel;
        m_leftRightPanel.control_layout_style(m_propertiesPanel, {propertiesPanelWidth,
            size_type::absolute, true});
        m_leftRightPanel.control_layout_style(m_rightPanel, {size_type::auto_size,
            true});
        m_mainPanel.anchor(anchor_styles::left | anchor_styles::right
            | anchor_styles::bottom);
        m_mainPanel.back_color(color::black);
        m_mainPanel << m_controlsPanel << m_leftRightPanel;
        // these properties must be set after _controls_panel is
        // added to m_mainPanel
         m_propertiesButton.height(35);
        m_mainPanel.control_layout_style(m_controlsPanel, {m_propertiesButton.height(),
            size_type::absolute, true});
        m_mainPanel.control_layout_style(m_leftRightPanel, {size_type::auto_size,
            true});
        m_mainPanel.width(client_size().width());
        m_mainPanel.height(client_size().height());
        *this << m_mainPanel;
    }

    void MainForm::on_form_closing(xtd::forms::form_closing_event_args& e)
    {
        enum dialog_result close = xtd::forms::message_box::show(*this, 
            "Are you sure you want exit?", 
            "Close jimoSDR", xtd::forms::message_box_buttons::yes_no, 
            xtd::forms::message_box_icon::question);
        e.cancel(close == xtd::forms::dialog_result::no);
    }

    void MainForm::CreatePropertiesPanel()
    {
        m_propertiesPanel.location({0, 0});
        m_propertiesPanel.size({propertiesPanelWidth, client_size().height()});
        m_propertiesPanel.back_color(color::light_gray);
    }

    void MainForm::CreateRightPanel()
    {
        auto& main_form_client_rect = client_size();
        auto left_panel_size = m_propertiesPanel.size();
        m_rightPanel.location({left_panel_size.width(), 0});
        m_rightPanel.size({main_form_client_rect.width() - left_panel_size.width(),
            main_form_client_rect.height()});
        m_rightPanel.back_color(color::black);
        m_rightPanel.anchor(anchor_styles::top | anchor_styles::right | 
            anchor_styles:: bottom | anchor_styles::left);
    }

    void MainForm::CreateControlsPanel()
    {
        m_controlsPanel.anchor(anchor_styles::left | anchor_styles::top
            | anchor_styles::right);
        m_controlsPanel.back_color(drawing::color::black);
        m_centerFrequencyLabel.text("Center:");
        m_centerFrequencyLabel.text_align(content_alignment::middle_center);
        m_centerFrequencyLabel.fore_color(drawing::color::white);
        m_centerFrequencyLabel.size( {20, 35} );
        m_controlsPanel << m_propertiesButton << m_centerFrequencyLabel << m_centerFrequencyDisplay;
        m_propertiesButton.size( {m_propertiesButton.height(), m_propertiesButton.height()} );
        m_controlsPanel.control_layout_style(m_propertiesButton,
            {m_propertiesButton.width(),size_type::absolute, true});
        m_controlsPanel.padding(1);        
    }

    void MainForm::GotCenterFrequency(xtd::object& sender, const xtd::event_args& e)
    {
        const GotCenterFrequencyEventArgs& args = dynamic_cast<const GotCenterFrequencyEventArgs&>(e);
        m_deviceProperties.CenterFrequency(args.CenterFrequency());
        m_centerFrequencyDisplay.SetValue(args.CenterFrequency());
    }
}