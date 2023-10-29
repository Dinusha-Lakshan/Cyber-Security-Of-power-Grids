#include <omnetpp.h>
#include "CTSGenerator2.h"  // Include the header file

using namespace omnetpp;

class client2 : public cSimpleModule {
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

    // Map to store dropped message counts for each prefix
    std::map<std::string, int> droppedMessageCounts;

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    void sendNextMessage();
    void handleDroppedMessage(cMessage *msg);
    void transferMessageFromReceivingQueue();
    void updateDroppedMessageCount(const std::string& prefix);

public:
    client2();
    virtual ~client2();
};

Define_Module(client2);

client2::client2() {
    messageCount = 0;
    maxMessageCount = 100;
    droppedMessageCount = 0;
    sendQueueMessage = nullptr;
    printDroppedCountMessage = nullptr;
}

client2::~client2() {
    cancelAndDelete(sendQueueMessage);
    cancelAndDelete(printDroppedCountMessage);
}

void client2::initialize() {
    EV << "client2 initialize" << endl;
    scheduleAt(simTime() + 0.0, sendQueueMessage = new cMessage("SendQueue"));
    scheduleAt(simTime() + 0.0, new cMessage("GenerateMessage"));
    scheduleAt(simTime() + 0.0, new cMessage("TransferMessage"));
    scheduleAt(simTime() + 4.0, printDroppedCountMessage = new cMessage("PrintDroppedCount"));

    // Initialize dropped message counts for each prefix
    droppedMessageCounts["SM11"] = 0;
    droppedMessageCounts["SM12"] = 0;
    droppedMessageCounts["SM13"] = 0;
    droppedMessageCounts["SM14"] = 0;
    droppedMessageCounts["SM15"] = 0;
    // Add more prefixes and initialize their counts as needed
}

void client2::handleMessage(cMessage *msg) {
    EV << "client2 handle message" << endl;

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
        simtime_t transferInterval = 0.1;
        scheduleAt(simTime() + transferInterval, new cMessage("TransferMessage"));
    } else if (msg->getArrivalGate() == gate("radioIn")) {
        if (receivingQueue.getLength() >= 50) {
            EV << "Dropping incoming message from another client2 because the receivingQueue is full" << endl;
            droppedMessageCount++;
            delete msg;
        } else {
            receivingQueue.insert(msg->dup());
        }
    } else if (strcmp(msg->getName(), "PrintDroppedCount") == 0) {
        // Print the sum of dropped messages for each prefix
        for (const auto& entry : droppedMessageCounts) {
            EV << "Dropped Message Count for Prefix " << entry.first << ": " << entry.second << endl;
        }
        scheduleAt(simTime() + 4.0, printDroppedCountMessage);
    } else {
        cModule *target = getParentModule()->getSubmodule("DataConcentrator");
        sendDirect(msg->dup(), target, "radioIn");
        delete msg;
    }
}

void client2::sendNextMessage() {
    messageCount++;

    cMessage *msg = generateCTSMessage2();

    const char encryptionKey = 'K';
    const std::string& originalMessage = msg->getName();
    std::string encryptedMessage = "SM2:" + std::to_string(messageCount) + ":" + originalMessage;

    for (char& c : encryptedMessage) {
        c = c ^ encryptionKey;
    }

    std::string signedMessage = encryptedMessage;
    msg->setName(signedMessage.c_str());

    messageQueue.insert(msg->dup());
}

void client2::handleDroppedMessage(cMessage *msg) {
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

void client2::transferMessageFromReceivingQueue() {
    if (!receivingQueue.isEmpty()) {
        cMessage *oldestMsg = (cMessage *)receivingQueue.pop();
        messageQueue.insert(oldestMsg->dup());
    }
}
