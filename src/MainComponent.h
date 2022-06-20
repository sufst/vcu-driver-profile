/******************************************************************************
 * @file   MainComponent.h
 * @author Tim Brewis (tab1g19@soton.ac.uk)
 * @date   2022-02-09
 * @brief  Main GUI component
 *****************************************************************************/

#pragma once

#include "ThrottleCurveComponent.h"
#include <JuceHeader.h>

/**
 * @breif Main GUI component
 */
class MainComponent : public juce::Component
{
public:

    // constructor / destructor
    MainComponent();
    ~MainComponent() override;

    // graphics
    void paint(juce::Graphics&) override;
    void resized() override;

private:

    // constants
    static const int borderSize = 20;

    // child components
    ThrottleCurveComponent throttleCurveComponent;
    juce::ComboBox interpolationMethodComboBox;
    juce::TextButton exportProfileButton;
    juce::TextButton importProfileButton;
    juce::TextButton exportCodeButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
