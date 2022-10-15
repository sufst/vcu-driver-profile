/******************************************************************************
 * @file   Application.h
 * @author Tim Brewis (@t-bre, tab1g19@soton.ac.uk)
 * @brief  Main JUCE application
 *****************************************************************************/

#include "Application.h"

/**
 * @brief       Initialises the application
 *
 * @param[in]   commandLine     Command line arguments string
 */
void Application::initialise(const juce::String& /*commandLine*/)
{
    configValueTree = std::make_shared<ConfigurationValueTree>();

    commandManager = std::make_shared<CommandManager>();
    commandManager->registerAllCommandsForTarget(this);

    mainWindow = std::make_unique<gui::MainWindow>(getApplicationName(), configValueTree, commandManager);

    LookAndFeel::setDefaultLookAndFeel(&lookAndFeel);
}

/**
 * @brief Shuts down the application
 */
void Application::shutdown()
{
    mainWindow.reset();
}

/**
 * @brief Called when the application is being asked to quit
 */
void Application::systemRequestedQuit()
{
    quit(); // accept request to quit
}

/**
 * @brief       Called when another instance of the application is launched
 *              while this instance is running
 *
 * @param[in]   commandLine     Command line arguments string of other instance
 */
void Application::anotherInstanceStarted(const juce::String& /*commandLine*/)
{
}

/**
 * @brief Returns the name of the application
 */
const juce::String Application::getApplicationName()
{
    return ProjectInfo::projectName;
}

/**
 * @brief Returns the version string of the application
 */
const juce::String Application::getApplicationVersion()
{
    return ProjectInfo::versionString;
}

/**
 * @brief   Sets whether or not multiple instances of the application can run
 *          at the same time
 */
bool Application::moreThanOneInstanceAllowed()
{
    return false;
}

/**
 * @brief   Implements juce::ApplicationCommandTarget::getNextCommandTarget()
 *
 * @details This ensures that the main window is found as a target by the
 * CommandManager when the app launches. Without this, if the user does not
 * interact with a component inside the main window, menu bar items will be
 * greyed out (though keyboard shortcuts will still work).
 */
juce::ApplicationCommandTarget* Application::getNextCommandTarget()
{
    return mainWindow.get();
}