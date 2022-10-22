/******************************************************************************
 * @file    InverterConfigComponent.cpp
 * @author  Tim Brewis (@t-bre)
 *****************************************************************************/

#include "InverterConfigComponent.h"

#include "../../../config/Identifiers.h"

namespace gui
{

//==============================================================================

/**
 * @brief   Constructor
 */
InverterConfigComponent::InverterConfigComponent(config::DataModel& configData)
    : torqueMap(configData.tree.getChildWithName(config::IDs::TORQUE_MAP)),
      torqueMapComponent(
          configData.tree.getChildWithName(config::IDs::TORQUE_MAP))
{
    setupInterpolationCombo();

    addAndMakeVisible(torqueMapComponent);
    addAndMakeVisible(interpolationCombo);
}

/**
 * @brief Setup interpolation method combo box
 */
void InverterConfigComponent::setupInterpolationCombo()
{
    // TODO: re-integrate
    const auto& interpolationMethods = utility::InterpolatorFactory<
        TorqueMapPoint::ValueType>::getAllIdentifiers();

    for (unsigned i = 0; i < interpolationMethods.size(); i++)
    {
        const auto itemId = static_cast<int>(i + 1);
        const auto& method = interpolationMethods.at(i).toString();

        interpolationCombo.addItem(method, itemId);

        if (method == torqueMap.interpolationMethod.get())
        {
            interpolationCombo.setSelectedId(itemId);
        }
    }

    interpolationCombo.onChange = [this]() mutable
    {
        int selectedIndex = interpolationCombo.getSelectedItemIndex();
        juce::String value = interpolationCombo.getItemText(selectedIndex);
        torqueMap.interpolationMethod.setValue(value, nullptr);
        DBG(torqueMap.state.toXmlString());
    };
}

//==============================================================================

/**
 * @brief   Implements juce::Component::resized()
 */
void InverterConfigComponent::resized()
{
    auto bounds = getLocalBounds().reduced(20);
    auto footerBounds = bounds.removeFromBottom(50);

    torqueMapComponent.setBounds(bounds);

    footerBounds.removeFromTop(5);
    footerBounds.removeFromBottom(5);
    interpolationCombo.setBounds(footerBounds);
}

} // namespace gui