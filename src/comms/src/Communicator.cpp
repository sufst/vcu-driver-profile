/******************************************************************************
 * @file   Communicator.cpp
 * @author Toby Godfrey (@tg, tmag1g21@soton.ac.uk)
 * @brief  Main file for VCU communication
 *****************************************************************************/

#include "Communicator.hpp"

#include "Candapter_MOCK.hpp"
#include <iostream>

Communicator* Communicator::_instance;

// As we are using the singleton pattern we must allow the user to get a pointer
// to the running instance
Communicator* Communicator::getInstance()
{
    if (Communicator::_instance == nullptr)
        Communicator::_instance = new Communicator();
    return Communicator::_instance;
}

// Constructor for the Communicator object
// Opens the serial port for the candapter
Communicator::Communicator()
{
}

// Descructor for the Communicator object
// Closes the serial port
Communicator::~Communicator()
{
}

// The GET command
const Comms::VariableVals* Communicator::get()
{
    Comms::VariableVals vals;

    uint8_t* buf = Candapter_MOCK::getMsg("data.fb");
    auto cmd = flatbuffers::GetRoot<Comms::Command>(buf);

    auto data = cmd->vals();

    Communicator::printVariables(data);

    return data;
}

// The SET command
bool Communicator::set(Comms::VariableVals vals)
{

    std::tuple<uint8_t*, int> pair
        = Communicator::createCommand(Comms::CommandID_SET,
                                      &vals,
                                      nullptr,
                                      nullptr);

    Candapter_MOCK::sendMsg("data.fb", std::get<0>(pair), std::get<1>(pair));

    std::cout << "Data written" << std::endl;

    return true;
}

// The SAVE command
bool Communicator::save(std::string name, std::string version)
{
    Comms::Version v = stringToVersion(version);
    const Comms::Version* v_ptr = &v;

    std::tuple<uint8_t*, int> pair
        = Communicator::createCommand(Comms::CommandID_SAVE,
                                      nullptr,
                                      &name,
                                      v_ptr);

    Candapter_MOCK::sendMsg("version.fb", std::get<0>(pair), std::get<1>(pair));

    /* FOR TESTING PURPOSES - DELETE LATER */
    uint8_t* data = Candapter_MOCK::getMsg("version.fb");
    auto received = flatbuffers::GetRoot<Comms::Command>(data);

    auto newName = flatbuffers::GetString(received->config_name());
    auto newVersion = versionToString(received->config_version());

    std::cout << newName << " - version " << newVersion << std::endl;

    return false;
}

std::tuple<uint8_t*, int>
Communicator::createCommand(Comms::CommandID cmdID,
                            const Comms::VariableVals* vals,
                            std::string* name,
                            const Comms::Version* version)
{

    // The flatbuffer builder object
    flatbuffers::FlatBufferBuilder builder(1024);

    if (cmdID == Comms::CommandID_SAVE)
    {
        assert(vals == nullptr);
        assert(name != nullptr);
        assert(version != nullptr);

        auto fbName = builder.CreateString(*name);
        // auto fbVersion = builder.CreateStruct(version);

        Comms::CommandBuilder commandBuilder(builder);

        commandBuilder.add_id(cmdID);
        commandBuilder.add_config_name(fbName);
        commandBuilder.add_config_version(version);

        auto command = commandBuilder.Finish();
        builder.Finish(command);
    }
    else if (cmdID == Comms::CommandID_SET)
    {
        assert(vals != nullptr);
        assert(name == nullptr);
        assert(version == nullptr);

        Comms::CommandBuilder commandBuilder(builder);

        commandBuilder.add_id(cmdID);
        commandBuilder.add_vals(vals);

        auto command = commandBuilder.Finish();
        builder.Finish(command);
    }
    else if (cmdID == Comms::CommandID_GET)
    {
        assert(vals == nullptr);
        assert(name == nullptr);
        assert(version == nullptr);

        Comms::CommandBuilder commandBuilder(builder);

        commandBuilder.add_id(cmdID);

        auto command = commandBuilder.Finish();
        builder.Finish(command);
    }
    else
    {
        throw std::runtime_error(
            "This function can only be used for SAVE, GET and SET commands!");
    }

    uint8_t* buf = builder.GetBufferPointer();
    int size = builder.GetSize();

    return std::tuple<uint8_t*, int>(buf, size);
}

// Converts a flatbuffer Version struct into the version string X.X.X
std::string Communicator::versionToString(const Comms::Version* v)
{
    return (std::to_string(v->a()) + "." + std::to_string(v->b()) + "."
            + std::to_string(v->c()));
}

// Convern the version string X.X.X into a flatbuffer Version struct
Comms::Version Communicator::stringToVersion(std::string s)
{
    Comms::Version version;
    uint8_t v[3]; // Parsed version number a.b.c
    try
    {
        int pos = 0;
        std::string token;
        std::string delimiter = ".";
        for (uint8_t i = 0; i < 3; i++)
        {
            pos = s.find(delimiter);
            int n = std::stoi(s.substr(0, pos));
            // if((n >= (int)'A' && n <= (int)'Z') || (n >= (int)'a' && n <=
            // (int)'z')){
            //   std::cout << "AGH" << std::endl;
            //   throw std::runtime_error("The version must be of the format
            //   X.X.X where the Xs are integers");
            // }
            if (n > 255)
                throw std::overflow_error("Value too large");
            s.erase(0, pos + delimiter.length());
            v[i] = n;
        }
        version = Comms::Version{v[0], v[1], v[2]};
    }
    catch (const std::invalid_argument& e)
    {
        std::cerr << "The version number can only contain integers and must be "
                     "of the form X.X.X"
                  << std::endl;
        ;
    }
    catch (const std::overflow_error& e)
    {
        std::cerr << "The version number can only contain 8-bit integers"
                  << std::endl;
        ;
    }
    return version;
}

// Chunk the serialised data into small enough chunks to be sent in the payload
// of a CAN frame
bool chunkMsg()
{
    return true;
}

// Make a CAN frame
Frame makeFrame()
{
    Frame newFrame = {0, 0, 0, {0, 0, 0, 0, 0, 0, 0, 0}};
    return newFrame;
}

// Convert a command into a series of CAN frames
std::vector<Frame> makeFrameSequence()
{
    return std::vector<Frame>{};
}

void Communicator::printVariables(const Comms::VariableVals* data)
{
    std::cout << "Variable:                       Val" << std::endl;
    std::cout << "----------------------------------------------------"
              << std::endl;
    std::cout << "Torque Map:                    " << data->torque_map_val()
              << std::endl;
    std::cout << "Inverter Mode:                 " << data->torque_map_val()
              << std::endl;
    std::cout << "Disable Torque Requests:       " << data->torque_map_val()
              << std::endl;
    std::cout << "APPS 1 ADC Min:                " << data->torque_map_val()
              << std::endl;
    std::cout << "APPS 1 ADC Max:                " << data->torque_map_val()
              << std::endl;
    std::cout << "APPS 2 ADC Min:                " << data->torque_map_val()
              << std::endl;
    std::cout << "APPS 2 ADC Max:                " << data->torque_map_val()
              << std::endl;
    std::cout << "BPS ADC Min:                   " << data->torque_map_val()
              << std::endl;
    std::cout << "BPS ADC Max:                   " << data->torque_map_val()
              << std::endl;
    std::cout << "BPS Fully Pressed Threshold:   " << data->torque_map_val()
              << std::endl;
    std::cout << "Enable Lapsim Testbench:       " << data->torque_map_val()
              << std::endl;
    std::cout << "Lapsim Testbench Laps:         " << data->torque_map_val()
              << std::endl;
}