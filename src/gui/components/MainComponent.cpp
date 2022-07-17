/******************************************************************************
 * @file   MainComponent.cpp
 * @author Tim Brewis (tab1g19@soton.ac.uk)
 * @date   2022-02-09
 * @brief  Main component
 *****************************************************************************/

#include "MainComponent.h"

#include "../../Interpolator.h"

namespace gui
{

/**
 * @brief Default constructor
 */
MainComponent::MainComponent()
    : torqueMap(Application::getConfig().getTorqueMap()), torqueMapGraph(Application::getConfig())

{
    setSize(600, 400);

    setupInterpolationCombo();
    setupButtons();

    addAndMakeVisible(torqueMapGraph);
    addAndMakeVisible(interpolationCombo);
    addAndMakeVisible(exportProfileButton);
    addAndMakeVisible(importProfileButton);
}

/**
 * @brief Destructor
 */
MainComponent::~MainComponent()
{
    // nothing to do
}

/**
 * @brief Setup interpolation method combo box
 */
void MainComponent::setupInterpolationCombo()
{
    const auto& interpolationMethods = utility::InterpolatorFactory<int>::getAllIdentifiers();

    for (unsigned i = 0; i < interpolationMethods.size(); i++)
    {
        const int itemId = static_cast<int>(i + 1);
        const auto& method = interpolationMethods.at(i);
        interpolationCombo.addItem(method.toString(), itemId);

        if (method.toString() == torqueMap.getProperty(VCUConfiguration::InterpolationMethod).toString())
        {
            interpolationCombo.setSelectedId(itemId);
        }
    }

    interpolationCombo.onChange = [this]()
    {
        int selectedIndex = this->interpolationCombo.getSelectedItemIndex();
        auto value = this->interpolationCombo.getItemText(selectedIndex);
        this->torqueMap.setProperty(VCUConfiguration::InterpolationMethod, value, nullptr);
    };
}

/**
 * @brief Sets up the buttons
 */
void MainComponent::setupButtons()
{
    // export profile
    exportProfileButton.setButtonText("Export Profile");

    exportProfileButton.onClick = [this]()
    {
        fileChooser = std::make_unique<juce::FileChooser>("Save VCU configuration",
                                                          juce::File::getSpecialLocation(juce::File::userHomeDirectory),
                                                          "*.xml",
                                                          true);

        auto fileChooserFlags = juce::FileBrowserComponent::canSelectFiles
                                | juce::FileBrowserComponent::warnAboutOverwriting
                                | juce::FileBrowserComponent::saveMode;

        fileChooser->launchAsync(fileChooserFlags,
                                 [](const juce::FileChooser& chooser)
                                 {
                                     if (chooser.getResults().isEmpty())
                                     {
                                         return;
                                     }

                                     auto xml = Application::getConfig().exportXml();
                                     auto file = chooser.getResult();
                                     xml->getDocumentElement()->writeTo(file);
                                 });
    };

    // import profile
    importProfileButton.setButtonText("Import Profile");

    importProfileButton.onClick = [this]() {

        fileChooser = std::make_unique<juce::FileChooser>("Load VCU configuration",
                                                          juce::File::getSpecialLocation(juce::File::userHomeDirectory),
                                                          "*.xml",
                                                          true);

        auto fileChooserFlags = juce::FileBrowserComponent::canSelectFiles
                                | juce::FileBrowserComponent::openMode;

        fileChooser->launchAsync(fileChooserFlags,
                                 [](const juce::FileChooser& chooser)
                                 {
                                     if (chooser.getResults().isEmpty())
                                     {
                                         return;
                                     }
                                     auto& config = Application::getConfig();
                                     auto xml = juce::XmlDocument(chooser.getResult());
                                     config.loadFromXml(xml);
                                 });
    };
}

/**
 * @brief Painter
 *
 * @param[in]   g   Graphics context
 */
void MainComponent::paint(juce::Graphics& g)
{
    // fill background
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

/**
 * @brief Resize handler
 */
void MainComponent::resized()
{
    auto bounds = getLocalBounds().reduced(20);
    auto footer = bounds.removeFromBottom(42);
    footer.removeFromTop(10);
    footer.removeFromBottom(2);

    // graph
    torqueMapGraph.setBounds(bounds);

    // footer
    std::initializer_list<juce::Component*> footerComponents
        = {&interpolationCombo, &exportProfileButton, &importProfileButton};

    const int numFooterComponents = static_cast<int>(footerComponents.size());
    const int footerItemSpacing = borderSize / numFooterComponents;
    const int footerItemWidth = (footer.getWidth() - footerItemSpacing) / numFooterComponents;

    for (juce::Component* component : footerComponents)
    {
        component->setBounds(footer.removeFromLeft(footerItemWidth));
        footer.removeFromLeft(footerItemSpacing);
    }
}

} // namespace gui