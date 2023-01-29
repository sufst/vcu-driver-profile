/******************************************************************************
 * @file   Communicator.h
 * @author Toby Godfrey (@tg, tmag1g21@soton.ac.uk)
 * @brief  Header file for comms
 *****************************************************************************/

#pragma once

#include "flatbuffers/flatbuffer_builder.h"
#include "schema_generated.h"
#include <string>
#include <vector>

// Singleton pattern to ensure only one communicator is created
class Communicator
{
private:

    static Communicator* _instance;

    Communicator();
    ~Communicator();
    bool chunkMsg();
    struct Frame makeFrame();
    std::vector<struct Frame> makeFrameSequence();
    Comms::Version stringToVersion(std::string);
    std::string versionToString(const Comms::Version*);
    std::tuple<uint8_t*, int> createCommand(Comms::CommandID,
                                            Comms::VariableID*,
                                            int32_t*,
                                            std::string*,
                                            const Comms::Version*);

public:

    static Communicator* getInstance();

    bool set(Comms::VariableID, int32_t);
    std::string get(Comms::VariableID);
    std::string get(std::string);
    bool save(std::string, std::string);
};

struct Frame
{
    uint8_t id;
    uint16_t frameNumber;
    uint16_t totalFrames;
    char payload[8];
};
