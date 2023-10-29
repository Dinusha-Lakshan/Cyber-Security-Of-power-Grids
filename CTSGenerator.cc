// CTSGenerator.cc

#include "CTSGenerator.h"
#include <iostream>
#include <string>

std::string encryptMessage(const std::string& message) {
    return message;
}

cMessage* generateCTSMessage() {
    static std::vector<std::string> messages = { "11kW", "6kVar", "9kW", "4kVar", "8kW", "25kVar", "54kW", "85kVar", "14kW", "5kVar" }; // List of messages
    static int index = 0;  // Current index in the list

    if (index >= messages.size()) {
        // Reached the end of the list, reset the index
        index = 0;
    }

    std::string currentMessage = messages[index];
    index++;

    cMessage* ctsMsg = new cMessage(currentMessage.c_str());
    std::string message = ctsMsg->getName();
    std::string encryptedMessage = encryptMessage(message);
    ctsMsg->setName(encryptedMessage.c_str());
    return ctsMsg;
}
