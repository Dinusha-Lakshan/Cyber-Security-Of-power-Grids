// CTSGenerator2.cc

#include "CTSGenerator2.h"
#include <iostream>
#include <string>

std::string Message(const std::string& message) {
    return message;
}

cMessage* generateCTSMessage2() {
    static std::vector<std::string> messages = { "8kW", "7kVar", "14kW", "6kVar", "9kW", "52kVar", "56kW", "78kVar","95kW", "95kVar" }; // List of messages
    static int index = 0;  // Current index in the list

    if (index >= messages.size()) {
        // Reached the end of the list, reset the index
        index = 0;
    }

    std::string currentMessage = messages[index];
    index++;

    cMessage* ctsMsg = new cMessage(currentMessage.c_str());
    std::string message = ctsMsg->getName();
    std::string encryptedMessage = Message(message);
    ctsMsg->setName(encryptedMessage.c_str());
    return ctsMsg;
}
