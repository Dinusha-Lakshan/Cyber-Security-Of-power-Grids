// client.cc

#include <omnetpp.h>
#include "CTSGenerator.h"  // Include the header file

using namespace omnetpp;

class client : public cSimpleModule {
private:
    int messageCount;
    int maxMessageCount;
    int droppedMessageCount;
    simtime_t nextMessageTime;
    cMessage *droppedMessageRequest = nullptr;
    cQueue messageQueue;
    cQueue receivingQueue;
    cMessage *sendQueueMessage;
    cMessage *printDroppedCountMessage;

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    void sendNextMessage();
    void handleDroppedMessage(cMessage *msg);
    void transferMessageFromReceivingQueue();

public:
    client();
    virtual ~client();
};

Define_Module(client);

client::client() {
    messageCount = 0;
    maxMessageCount = 100;
    droppedMessageCount = 0;
    sendQueueMessage = nullptr;
    printDroppedCountMessage = nullptr;
}

client::~client() {
    cancelAndDelete(sendQueueMessage);
    cancelAndDelete(printDroppedCountMessage);
}

void client::initialize() {
    EV << "Client initialize" << endl;
    scheduleAt(simTime() + 0.0, sendQueueMessage = new cMessage("SendQueue"));
    scheduleAt(simTime() + 0.0, new cMessage("GenerateMessage"));
    scheduleAt(simTime() + 0.0, new cMessage("TransferMessage")); // Schedule it 1 second after initialization
    scheduleAt(simTime() + 4.0, printDroppedCountMessage = new cMessage("PrintDroppedCount"));
}

void client::handleMessage(cMessage *msg) {
    EV << "Client handle message" << endl;

    if (strcmp(msg->getName(), "Request") == 0) {
        handleDroppedMessage(msg);
    } else if (strcmp(msg->getName(), "RTS") == 0) {
        if (droppedMessageRequest) {
            const std::string& encryptedMessage = droppedMessageRequest->getName();
            cMessage *resendMessage = new cMessage(encryptedMessage.c_str());
            resendMessage->setContextPointer(droppedMessageRequest->getContextPointer());
            cModule *target = getParentModule()->getSubmodule("DataConcentrator");
            sendDirect(resendMessage, target, "radioIn");
            delete droppedMessageRequest;
            droppedMessageRequest = nullptr;
        }

        if (messageCount < maxMessageCount) {
            sendNextMessage();
        }

        delete msg;
        simtime_t interval = 1.0;
        scheduleAt(simTime() + interval, new cMessage("RTS"));
    } else if (strcmp(msg->getName(), "SendQueue") == 0) {
        while (!messageQueue.isEmpty()) {
            cMessage *queuedMsg = (cMessage *)messageQueue.pop();
            const std::string& encryptedMessage = queuedMsg->getName();
            cModule *target = getParentModule()->getSubmodule("DataConcentrator");
            sendDirect(queuedMsg, target, "radioIn");
        }

        scheduleAt(simTime() + 1.0, sendQueueMessage);
    } else if (strcmp(msg->getName(), "GenerateMessage") == 0) {
        sendNextMessage();
        simtime_t interval = 1.0;
        scheduleAt(simTime() + interval, new cMessage("GenerateMessage"));
    } else if (strcmp(msg->getName(), "ReceivingQueueMessage") == 0) {
        if (receivingQueue.getLength() >= 50) {
            // If the receivingQueue is full, drop the incoming message immediately
            EV << "Dropping incoming message because the receivingQueue is full" << endl;
            droppedMessageCount++;
            delete msg;
        } else {
            receivingQueue.insert(msg->dup());
        }
        simtime_t transferInterval = 0.1;
        scheduleAt(simTime() + transferInterval, new cMessage("TransferMessage"));
    } else if (strcmp(msg->getName(), "TransferMessage") == 0) {
        if (!receivingQueue.isEmpty()) {
            transferMessageFromReceivingQueue();
        }
        simtime_t transferInterval = 0.1; // Schedule it every 0.1 second
        scheduleAt(simTime() + transferInterval, new cMessage("TransferMessage"));
    } else if (msg->getArrivalGate() == gate("radioIn")) {
        // Check if the receivingQueue is full
        if (receivingQueue.getLength() >= 50) {
            // If the receivingQueue is full, drop the incoming message immediately
            EV << "Dropping incoming message from another client because the receivingQueue is full" << endl;
            droppedMessageCount++;
            delete msg;
        } else {
            // Insert the message into the receivingQueue
            receivingQueue.insert(msg->dup());
        }
    } else if (strcmp(msg->getName(), "PrintDroppedCount") == 0) {
        EV << "Dropped Message Count: " << droppedMessageCount << endl;
        scheduleAt(simTime() + 4.0, printDroppedCountMessage);
    } else {
        // Messages from messageQueue are forwarded to the Data Concentrator
        cModule *target = getParentModule()->getSubmodule("DataConcentrator");
        sendDirect(msg->dup(), target, "radioIn");
        delete msg;
    }
}

void client::sendNextMessage() {
    messageCount++;

    cMessage *msg = generateCTSMessage();

    const char encryptionKey = 'K';
    const std::string& originalMessage = msg->getName();
    std::string encryptedMessage = "SM1:" + std::to_string(messageCount) + ":" + originalMessage;

    for (char& c : encryptedMessage) {
        c = c ^ encryptionKey;
    }

    std::string signedMessage = encryptedMessage;
    msg->setName(signedMessage.c_str());

    messageQueue.insert(msg->dup());
}

void client::handleDroppedMessage(cMessage *msg) {
    if (droppedMessageRequest) {
        const std::string& encryptedMessage = droppedMessageRequest->getName();
        cMessage *resendMessage = new cMessage(encryptedMessage.c_str());
        resendMessage->setContextPointer(droppedMessageRequest->getContextPointer());
        cModule *target = getParentModule()->getSubmodule("DataConcentrator");
        sendDirect(resendMessage, target, "radioIn");
        delete droppedMessageRequest;
        droppedMessageRequest = nullptr;
    }
}

void client::transferMessageFromReceivingQueue() {
    if (!receivingQueue.isEmpty()) {
        cMessage *oldestMsg = (cMessage *)receivingQueue.pop();
        messageQueue.insert(oldestMsg->dup());
    }
}
