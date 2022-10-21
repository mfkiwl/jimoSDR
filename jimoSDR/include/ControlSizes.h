#pragma once

namespace jimo_sdr
{
    // Main Form
    constexpr int32_t mainFormDefaultWidth = 1000;
    constexpr int32_t mainFormDefaultHeight = 800;
    constexpr int32_t mainFormMinimumWidth = mainFormDefaultWidth;
    constexpr int32_t mainFormMinimumHeight = mainFormDefaultHeight;

    // Properties Panel
    constexpr int32_t propertiesPanelWidth = 300;

    // Digit Incrementer
    constexpr int32_t digitIncrementerMinimumWidth = 11;
    constexpr int32_t digitIncrementerMinimumHeight = 16;
    constexpr int32_t digitIncrementerMaximumWidth = 6 * digitIncrementerMinimumWidth;
    constexpr int32_t digitIncrementerMaximumHeight = 6 * digitIncrementerMinimumHeight;

    // User Draw Buttons
    constexpr int32_t defaultUserDrawButtonWidth = 35;
    constexpr int32_t defaultUserDrawButtonHeight = 35;
    
    // general sizes
    constexpr float defaultControlHeight = 20;
    constexpr float defaultSpacerHeight = 3;
}