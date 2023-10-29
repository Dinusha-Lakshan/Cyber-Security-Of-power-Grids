#include <string>
#include <omnetpp.h>

using namespace omnetpp;

class utilitycenter : public cSimpleModule {
private:
    cQueue messageQueue;
    int maxMessageCount;

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    void processStoredMessages();

public:
    utilitycenter();
    virtual ~utilitycenter();
};

Define_Module(utilitycenter);

utilitycenter::utilitycenter() {
    maxMessageCount = 100;
}

utilitycenter::~utilitycenter() {
    while (!messageQueue.isEmpty()) {
        delete messageQueue.pop();
    }
}

void utilitycenter::initialize() {
    // Initialize the module and variables if needed
}

void utilitycenter::handleMessage(cMessage *msg) {
    if (msg->isSelfMessage()) {
        // Process self-messages if needed
        // ...
    } else {
        // Decrypt the received message if needed
        const char encryptionKey = 'X'; // Encryption key used by the DataConcentrator

        std::string encryptedMessage = msg->getName();
        std::string decryptedMessage = encryptedMessage;
        for (char& c : decryptedMessage) {
            c = c ^ encryptionKey;
        }

        // Update the message name with the decrypted message
        msg->setName(decryptedMessage.c_str());

        // Store the decrypted message
        messageQueue.insert(msg);

        // Process the stored messages if the queue reaches the desired size
        if (messageQueue.getLength() >= maxMessageCount) {
            processStoredMessages();
        }
    }
}

void utilitycenter::processStoredMessages() {
    while (!messageQueue.isEmpty()) {
        // Retrieve the message from the front of the queue
        cMessage *msg = check_and_cast<cMessage *>(messageQueue.pop());

        // Process the stored message
        // ...

        // Delete the processed message
        delete msg;
    }
}
