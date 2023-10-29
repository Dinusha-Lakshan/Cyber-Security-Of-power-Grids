// server.cc

#include <omnetpp.h>
using namespace omnetpp;

class server : public cSimpleModule {
private:
    cQueue messageQueue;
    cQueue droppedMessageQueue; // Queue to store dropped messages
    cQueue oldestMessagesQueue; // New queue to store the oldest messages
    int maxMessageCount; // Maximum queue length
    char seq;
    simtime_t messageInterval;
    cMessage *messageTimer;
    cMessage *moveOldestMessageTimer; // Timer to trigger moving the oldest message
    const char encryptionKey = 'K'; // Encryption key used in the client module
    const char encryptionKey2 = 'X'; // Different encryption key for sending to UtilityCenter
    int requestSent = 0;
    int droppedMessageCountSM1 = 0; // Dropped message count for SmartMeter1 in the current time period
    int droppedMessageCountSM2 = 0; // Dropped message count for SmartMeter2 in the current time period
    int droppedMessageCountSM3 = 0; // Dropped message count for SmartMeter1 in the current time period
    int droppedMessageCountSM4 = 0; // Dropped message count for SmartMeter1 in the current time period
    int droppedMessageCountSM5 = 0;
    int droppedMessageCountSM6 = 0; // Dropped message count for SmartMeter1 in the current time period
    int droppedMessageCountSM7 = 0; // Dropped message count for SmartMeter2 in the current time period
    int droppedMessageCountSM8 = 0; // Dropped message count for SmartMeter1 in the current time period
    int droppedMessageCountSM9 = 0;
    int droppedMessageCountSM10 = 0;
    int droppedMessageCountSM11 = 0; // Dropped message count for SmartMeter1 in the current time period
    int droppedMessageCountSM12 = 0; // Dropped message count for SmartMeter2 in the current time period
    int droppedMessageCountSM13 = 0; // Dropped message count for SmartMeter1 in the current time period
    int droppedMessageCountSM14 = 0; // Dropped message count for SmartMeter1 in the current time period
    int droppedMessageCountSM15 = 0;
    int droppedMessageCountSM16 = 0; // Dropped message count for SmartMeter1 in the current time period
    int droppedMessageCountSM17 = 0; // Dropped message count for SmartMeter2 in the current time period
    int droppedMessageCountSM18 = 0; // Dropped message count for SmartMeter1 in the current time period
    int droppedMessageCountSM19 = 0;
    int droppedMessageCountSM20 = 0;
    int droppedMessageCountSM21 = 0; // Dropped message count for SmartMeter1 in the current time period
    int droppedMessageCountSM22 = 0; // Dropped message count for SmartMeter2 in the current time period
    int droppedMessageCountSM23 = 0; // Dropped message count for SmartMeter1 in the current time period
    int droppedMessageCountSM24 = 0; // Dropped message count for SmartMeter1 in the current time period
    int droppedMessageCountSM25 = 0;
    int droppedMessageCountSM26 = 0; // Dropped message count for SmartMeter1 in the current time period
    int droppedMessageCountSM27 = 0; // Dropped message count for SmartMeter2 in the current time period
    int droppedMessageCountSM28 = 0; // Dropped message count for SmartMeter1 in the current time period
    int droppedMessageCountSM29 = 0;
    int droppedMessageCountSM30 = 0;
    int droppedMessageCountListSM1[100] = {0}; // Array to store dropped message count for SmartMeter1
    int droppedMessageCountListSM2[100] = {0}; // Array to store dropped message count for SmartMeter2
    int droppedMessageCountListSM3[100] = {0}; // Array to store dropped message count for SmartMeter2
    int droppedMessageCountListSM4[100] = {0}; // Array to store dropped message count for SmartMeter4
    int droppedMessageCountListSM5[100] = {0}; // Array to store dropped message count for SmartMeter5
    int droppedMessageCountListSM6[100] = {0}; // Array to store dropped message count for SmartMeter6
    int droppedMessageCountListSM7[100] = {0}; // Array to store dropped message count for SmartMeter7
    int droppedMessageCountListSM8[100] = {0}; // Array to store dropped message count for SmartMeter8
    int droppedMessageCountListSM9[100] = {0}; // Array to store dropped message count for SmartMeter9
    int droppedMessageCountListSM10[100] = {0}; // Array to store dropped message count for SmartMeter10
    int droppedMessageCountListSM11[100] = {0}; // Array to store dropped message count for SmartMeter10
    int droppedMessageCountListSM12[100] = {0}; // Array to store dropped message count for SmartMeter10
    int droppedMessageCountListSM13[100] = {0}; // Array to store dropped message count for SmartMeter10
    int droppedMessageCountListSM14[100] = {0}; // Array to store dropped message count for SmartMeter10
    int droppedMessageCountListSM15[100] = {0}; // Array to store dropped message count for SmartMeter10
    int droppedMessageCountListSM16[100] = {0}; // Array to store dropped message count for SmartMeter10
    int droppedMessageCountListSM17[100] = {0}; // Array to store dropped message count for SmartMeter10
    int droppedMessageCountListSM18[100] = {0}; // Array to store dropped message count for SmartMeter10
    int droppedMessageCountListSM19[100] = {0}; // Array to store dropped message count for SmartMeter10
    int droppedMessageCountListSM20[100] = {0}; // Array to store dropped message count for SmartMeter10
    int droppedMessageCountListSM21[100] = {0}; // Array to store dropped message count for SmartMeter10
    int droppedMessageCountListSM22[100] = {0}; // Array to store dropped message count for SmartMeter10
    int droppedMessageCountListSM23[100] = {0}; // Array to store dropped message count for SmartMeter10
    int droppedMessageCountListSM24[100] = {0}; // Array to store dropped message count for SmartMeter10
    int droppedMessageCountListSM25[100] = {0}; // Array to store dropped message count for SmartMeter10
    int droppedMessageCountListSM26[100] = {0}; // Array to store dropped message count for SmartMeter10
    int droppedMessageCountListSM27[100] = {0}; // Array to store dropped message count for SmartMeter10
    int droppedMessageCountListSM28[100] = {0}; // Array to store dropped message count for SmartMeter10
    int droppedMessageCountListSM29[100] = {0}; // Array to store dropped message count for SmartMeter10
    int droppedMessageCountListSM30[100] = {0}; // Array to store dropped message count for SmartMeter10

    int timePeriodCounter = 0; // Counter for time periods

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    void sendMessagesToUtilityCenter();
    void scheduleNextMessage();
    std::string decryptMessage(const std::string& encryptedMessage);
    std::string encryptMessage(const std::string& originalMessage, const char key);

public:
    server();
    virtual ~server();
};

Define_Module(server);

server::server() {
    maxMessageCount = 70; // Set your desired maximum queue length here
    messageInterval = 4.0;
    messageTimer = nullptr;
    moveOldestMessageTimer = nullptr;
}

server::~server() {
    cancelAndDelete(messageTimer);
    cancelAndDelete(moveOldestMessageTimer);
}

void server::initialize() {
    // Initialize the module and variables if needed
    scheduleNextMessage();

    // Schedule the periodic method call to move the oldest message
    scheduleAt(simTime() + 0.01, moveOldestMessageTimer = new cMessage("MoveOldestMessage"));
}

void server::handleMessage(cMessage *msg) {
    if (msg->isSelfMessage()) {
        // Handle self-messages (i.e., the messageTimer)
        if (msg == messageTimer) {
            sendMessagesToUtilityCenter();
            scheduleNextMessage();
        } else if (msg == moveOldestMessageTimer) {
            if (!messageQueue.isEmpty()) {
                // Retrieve the oldest message from messageQueue
                cMessage *oldestMsg = check_and_cast<cMessage *>(messageQueue.pop());

                // Decrypt the message before processing it
                /*const std::string& encryptedMessage = oldestMsg->getName();
                std::string decryptedMessage = decryptMessage(encryptedMessage);
                oldestMsg->setName(decryptedMessage.c_str());*/

                // Insert the oldest message into oldestMessagesQueue
                oldestMessagesQueue.insert(oldestMsg);

                // Schedule the next call for moving the oldest message
                scheduleAt(simTime() + 0.01, moveOldestMessageTimer);
            } else {
                // If messageQueue is empty, schedule the next call for moving the oldest message
                scheduleAt(simTime() + 0.01, moveOldestMessageTimer);
            }
        }
    } else {
        // Decrypt the message before adding it to the queue
        const std::string& encryptedMessage = msg->getName();
        std::string decryptedMessage = decryptMessage(encryptedMessage);
        msg->setName(decryptedMessage.c_str());

        // Check if the queue is full before adding the decrypted message
        if (messageQueue.getLength() >= maxMessageCount) {
            // Handle the case where the queue is full
            // ...
            EV << "Message queue is full. Dropping message: " << msg->getName() << endl;
            std::string name = msg->getName();
            EV << "Dropped sequence: " << name.substr(0, 5) << std::endl;
            droppedMessageQueue.insert(msg->dup());

            // Update the dropped message count for the corresponding Smart Meter
            if (name.compare(0, 4, "SM1:") == 0) {
                droppedMessageCountSM1++; // Increment the count for SmartMeter1
            } else if (name.compare(0, 4, "SM2:") == 0) {
                droppedMessageCountSM2++; // Increment the count for SmartMeter2
            }else if (name.compare(0, 4, "SM3:") == 0) {
                droppedMessageCountSM3++; // Increment the count for SmartMeter2
            } else if (name.compare(0, 4, "SM4:") == 0) {
                droppedMessageCountSM4++; // Increment the count for SmartMeter2
            } else if (name.compare(0, 4, "SM5:") == 0) {
                droppedMessageCountSM5++; // Increment the count for SmartMeter2
            } else if (name.compare(0, 4, "SM6:") == 0) {
                droppedMessageCountSM6++; // Increment the count for SmartMeter2
            } else if (name.compare(0, 4, "SM7:") == 0) {
                droppedMessageCountSM7++; // Increment the count for SmartMeter2
            } else if (name.compare(0, 4, "SM8:") == 0) {
                droppedMessageCountSM8++; // Increment the count for SmartMeter2
            } else if (name.compare(0, 4, "SM9:") == 0) {
                droppedMessageCountSM9++; // Increment the count for SmartMeter2
            } else if (name.compare(0, 5, "SM10:") == 0) {
                droppedMessageCountSM10++; // Increment the count for SmartMeter2
            } else if (name.compare(0, 5, "SM11:") == 0) {
                droppedMessageCountSM11++; // Increment the count for SmartMeter2
            } else if (name.compare(0, 5, "SM12:") == 0) {
                droppedMessageCountSM12++; // Increment the count for SmartMeter2
            } else if (name.compare(0, 5, "SM13:") == 0) {
                droppedMessageCountSM13++; // Increment the count for SmartMeter2
            } else if (name.compare(0, 5, "SM14:") == 0) {
                droppedMessageCountSM14++; // Increment the count for SmartMeter2
            } else if (name.compare(0, 5, "SM15:") == 0) {
                droppedMessageCountSM15++; // Increment the count for SmartMeter2
            } else if (name.compare(0, 5, "SM10:") == 0) {
                droppedMessageCountSM10++; // Increment the count for SmartMeter2
            } else if (name.compare(0, 5, "SM16:") == 0) {
                droppedMessageCountSM16++; // Increment the count for SmartMeter2
            } else if (name.compare(0, 5, "SM17:") == 0) {
                droppedMessageCountSM17++; // Increment the count for SmartMeter2
            } else if (name.compare(0, 5, "SM18:") == 0) {
                droppedMessageCountSM18++; // Increment the count for SmartMeter2
            } else if (name.compare(0, 5, "SM19:") == 0) {
                droppedMessageCountSM19++; // Increment the count for SmartMeter2
            } else if (name.compare(0, 5, "SM20:") == 0) {
                droppedMessageCountSM20++; // Increment the count for SmartMeter2
            } else if (name.compare(0, 5, "SM21:") == 0) {
                droppedMessageCountSM21++; // Increment the count for SmartMeter2
            } else if (name.compare(0, 5, "SM22:") == 0) {
                droppedMessageCountSM22++; // Increment the count for SmartMeter2
            } else if (name.compare(0, 5, "SM23:") == 0) {
                droppedMessageCountSM23++; // Increment the count for SmartMeter2
            } else if (name.compare(0, 5, "SM24:") == 0) {
                droppedMessageCountSM24++; // Increment the count for SmartMeter2
            } else if (name.compare(0, 5, "SM25:") == 0) {
                droppedMessageCountSM25++; // Increment the count for SmartMeter2
            } else if (name.compare(0, 5, "SM26:") == 0) {
                droppedMessageCountSM26++; // Increment the count for SmartMeter2
            } else if (name.compare(0, 5, "SM27:") == 0) {
                droppedMessageCountSM27++; // Increment the count for SmartMeter2
            } else if (name.compare(0, 5, "SM28:") == 0) {
                droppedMessageCountSM28++; // Increment the count for SmartMeter2
            } else if (name.compare(0, 5, "SM29:") == 0) {
                droppedMessageCountSM29++; // Increment the count for SmartMeter2
            } else if (name.compare(0, 5, "SM30:") == 0) {
                droppedMessageCountSM30++; // Increment the count for SmartMeter2
            }

            // Request dropped message from clients
            std::string firstFiveCharacters = name.substr(0, 5);
            cMessage *requestMsg = new cMessage(("Request:"+firstFiveCharacters).c_str());
            if (name.compare(0, 4, "SM1:")==0){
                sendDirect(requestMsg, getParentModule()->getSubmodule("SmartMeter1"), "radioIn");
            } else if (name.compare(0, 4, "SM2:")==0){
                sendDirect(requestMsg->dup(), getParentModule()->getSubmodule("SmartMeter2"), "radioIn");
            } else if (name.compare(0, 4, "SM3:")==0){
                sendDirect(requestMsg->dup(), getParentModule()->getSubmodule("SmartMeter3"), "radioIn");
            } else if (name.compare(0, 4, "SM4:")==0){
                sendDirect(requestMsg->dup(), getParentModule()->getSubmodule("SmartMeter4"), "radioIn");
            } else if (name.compare(0, 4, "SM5:")==0){
                sendDirect(requestMsg->dup(), getParentModule()->getSubmodule("SmartMeter5"), "radioIn");
            } else if (name.compare(0, 4, "SM6:")==0){
                sendDirect(requestMsg->dup(), getParentModule()->getSubmodule("SmartMeter6"), "radioIn");
            } else if (name.compare(0, 4, "SM7:")==0){
                sendDirect(requestMsg->dup(), getParentModule()->getSubmodule("SmartMeter7"), "radioIn");
            } else if (name.compare(0, 4, "SM8:")==0){
                sendDirect(requestMsg->dup(), getParentModule()->getSubmodule("SmartMeter8"), "radioIn");
            } else if (name.compare(0, 4, "SM9:")==0){
                sendDirect(requestMsg->dup(), getParentModule()->getSubmodule("SmartMeter9"), "radioIn");
            } else if (name.compare(0, 5, "SM10:")==0){
                sendDirect(requestMsg->dup(), getParentModule()->getSubmodule("SmartMeter10"), "radioIn");
            } else if (name.compare(0, 5, "SM11:")==0){
                sendDirect(requestMsg->dup(), getParentModule()->getSubmodule("SmartMeter11"), "radioIn");
            } else if (name.compare(0, 5, "SM12:")==0){
                sendDirect(requestMsg->dup(), getParentModule()->getSubmodule("SmartMeter12"), "radioIn");
            } else if (name.compare(0, 5, "SM13:")==0){
                sendDirect(requestMsg->dup(), getParentModule()->getSubmodule("SmartMeter13"), "radioIn");
            } else if (name.compare(0, 5, "SM14:")==0){
                sendDirect(requestMsg->dup(), getParentModule()->getSubmodule("SmartMeter14"), "radioIn");
            } else if (name.compare(0, 5, "SM15:")==0){
                sendDirect(requestMsg->dup(), getParentModule()->getSubmodule("SmartMeter15"), "radioIn");
            } else if (name.compare(0, 5, "SM16:")==0){
                sendDirect(requestMsg->dup(), getParentModule()->getSubmodule("SmartMeter16"), "radioIn");
            } else if (name.compare(0, 5, "SM17:")==0){
                sendDirect(requestMsg->dup(), getParentModule()->getSubmodule("SmartMeter17"), "radioIn");
            } else if (name.compare(0, 5, "SM18:")==0){
                sendDirect(requestMsg->dup(), getParentModule()->getSubmodule("SmartMeter18"), "radioIn");
            } else if (name.compare(0, 5, "SM19:")==0){
                sendDirect(requestMsg->dup(), getParentModule()->getSubmodule("SmartMeter19"), "radioIn");
            } else if (name.compare(0, 5, "SM20:")==0){
                sendDirect(requestMsg->dup(), getParentModule()->getSubmodule("SmartMeter20"), "radioIn");
            } else if (name.compare(0, 5, "SM21:")==0){
                sendDirect(requestMsg->dup(), getParentModule()->getSubmodule("SmartMeter21"), "radioIn");
            } else if (name.compare(0, 5, "SM22:")==0){
                sendDirect(requestMsg->dup(), getParentModule()->getSubmodule("SmartMeter22"), "radioIn");
            } else if (name.compare(0, 5, "SM23:")==0){
                sendDirect(requestMsg->dup(), getParentModule()->getSubmodule("SmartMeter23"), "radioIn");
            } else if (name.compare(0, 5, "SM24:")==0){
                sendDirect(requestMsg->dup(), getParentModule()->getSubmodule("SmartMeter24"), "radioIn");
            } else if (name.compare(0, 5, "SM25:")==0){
                sendDirect(requestMsg->dup(), getParentModule()->getSubmodule("SmartMeter25"), "radioIn");
            } else if (name.compare(0, 5, "SM26:")==0){
                sendDirect(requestMsg->dup(), getParentModule()->getSubmodule("SmartMeter26"), "radioIn");
            } else if (name.compare(0, 5, "SM27:")==0){
                sendDirect(requestMsg->dup(), getParentModule()->getSubmodule("SmartMeter27"), "radioIn");
            } else if (name.compare(0, 5, "SM28:")==0){
                sendDirect(requestMsg->dup(), getParentModule()->getSubmodule("SmartMeter28"), "radioIn");
            } else if (name.compare(0, 5, "SM29:")==0){
                sendDirect(requestMsg->dup(), getParentModule()->getSubmodule("SmartMeter29"), "radioIn");
            } else if (name.compare(0, 5, "SM30:")==0){
                sendDirect(requestMsg->dup(), getParentModule()->getSubmodule("SmartMeter30"), "radioIn");
            }

            requestSent = 1; // Set the flag to indicate a request has been sent
        } else {
            // Add the decrypted message to the queue
            messageQueue.insert(msg);
        }
    }
}

void server::sendMessagesToUtilityCenter() {
    std::string aggregatedSM1Message;
    std::string aggregatedSM2Message;
    std::string aggregatedSM3Message;
    std::string aggregatedSM4Message;
    std::string aggregatedSM5Message;
    std::string aggregatedSM6Message;
    std::string aggregatedSM7Message;
    std::string aggregatedSM8Message;
    std::string aggregatedSM9Message;
    std::string aggregatedSM10Message;
    std::string aggregatedSM11Message;
    std::string aggregatedSM12Message;
    std::string aggregatedSM13Message;
    std::string aggregatedSM14Message;
    std::string aggregatedSM15Message;
    std::string aggregatedSM16Message;
    std::string aggregatedSM17Message;
    std::string aggregatedSM18Message;
    std::string aggregatedSM19Message;
    std::string aggregatedSM20Message;
    std::string aggregatedSM21Message;
    std::string aggregatedSM22Message;
    std::string aggregatedSM23Message;
    std::string aggregatedSM24Message;
    std::string aggregatedSM25Message;
    std::string aggregatedSM26Message;
    std::string aggregatedSM27Message;
    std::string aggregatedSM28Message;
    std::string aggregatedSM29Message;
    std::string aggregatedSM30Message;

    while (!oldestMessagesQueue.isEmpty()) {
        // Retrieve the message from the front of the queue
        cMessage *msg = check_and_cast<cMessage *>(oldestMessagesQueue.pop());

        // Retrieve the message content
        std::string messageContent = msg->getName();

        // Determine the message type based on the prefix
        if (messageContent.compare(0, 4, "SM1:") == 0) {
            // SM1 message
            aggregatedSM1Message += messageContent.substr(4) + "/"; // Remove the prefix
        } else if (messageContent.compare(0, 4, "SM2:") == 0) {
            // SM2 message
            aggregatedSM2Message += messageContent.substr(4) + "/"; // Remove the prefix
        } else if (messageContent.compare(0, 4, "SM3:") == 0) {
            // SM2 message
            aggregatedSM3Message += messageContent.substr(4) + "/"; // Remove the prefix
        } else if (messageContent.compare(0, 4, "SM4:") == 0) {
            // SM2 message
            aggregatedSM4Message += messageContent.substr(4) + "/"; // Remove the prefix
        } else if (messageContent.compare(0, 4, "SM5:") == 0) {
            // SM2 message
            aggregatedSM5Message += messageContent.substr(4) + "/"; // Remove the prefix
        } else if (messageContent.compare(0, 4, "SM6:") == 0) {
            // SM2 message
            aggregatedSM6Message += messageContent.substr(4) + "/"; // Remove the prefix
        } else if (messageContent.compare(0, 4, "SM7:") == 0) {
            // SM2 message
            aggregatedSM7Message += messageContent.substr(4) + "/"; // Remove the prefix
        } else if (messageContent.compare(0, 4, "SM8:") == 0) {
            // SM2 message
            aggregatedSM8Message += messageContent.substr(4) + "/"; // Remove the prefix
        } else if (messageContent.compare(0, 4, "SM9:") == 0) {
            // SM2 message
            aggregatedSM9Message += messageContent.substr(5) + "/"; // Remove the prefix
        } else if (messageContent.compare(0, 5, "SM10:") == 0) {
            // SM2 message
            aggregatedSM10Message += messageContent.substr(4) + "/"; // Remove the prefix
        } else if (messageContent.compare(0, 5, "SM11:") == 0) {
            // SM2 message
            aggregatedSM11Message += messageContent.substr(4) + "/"; // Remove the prefix
        } else if (messageContent.compare(0, 5, "SM12:") == 0) {
            // SM2 message
            aggregatedSM12Message += messageContent.substr(4) + "/"; // Remove the prefix
        } else if (messageContent.compare(0, 5, "SM13:") == 0) {
            // SM2 message
            aggregatedSM13Message += messageContent.substr(4) + "/"; // Remove the prefix
        } else if (messageContent.compare(0, 5, "SM14:") == 0) {
            // SM2 message
            aggregatedSM14Message += messageContent.substr(4) + "/"; // Remove the prefix
        } else if (messageContent.compare(0, 5, "SM15:") == 0) {
            // SM2 message
            aggregatedSM15Message += messageContent.substr(4) + "/"; // Remove the prefix
        } else if (messageContent.compare(0, 5, "SM16:") == 0) {
            // SM2 message
            aggregatedSM16Message += messageContent.substr(4) + "/"; // Remove the prefix
        } else if (messageContent.compare(0, 5, "SM17:") == 0) {
            // SM2 message
            aggregatedSM17Message += messageContent.substr(4) + "/"; // Remove the prefix
        } else if (messageContent.compare(0, 5, "SM18:") == 0) {
            // SM2 message
            aggregatedSM18Message += messageContent.substr(4) + "/"; // Remove the prefix
        } else if (messageContent.compare(0, 5, "SM19:") == 0) {
            // SM2 message
            aggregatedSM19Message += messageContent.substr(4) + "/"; // Remove the prefix
        } else if (messageContent.compare(0, 5, "SM20:") == 0) {
            // SM2 message
            aggregatedSM20Message += messageContent.substr(4) + "/"; // Remove the prefix
        } else if (messageContent.compare(0, 5, "SM21:") == 0) {
            // SM2 message
            aggregatedSM21Message += messageContent.substr(4) + "/"; // Remove the prefix
        } else if (messageContent.compare(0, 5, "SM22:") == 0) {
            // SM2 message
            aggregatedSM22Message += messageContent.substr(4) + "/"; // Remove the prefix
        } else if (messageContent.compare(0, 5, "SM23:") == 0) {
            // SM2 message
            aggregatedSM23Message += messageContent.substr(4) + "/"; // Remove the prefix
        } else if (messageContent.compare(0, 5, "SM24:") == 0) {
            // SM2 message
            aggregatedSM24Message += messageContent.substr(4) + "/"; // Remove the prefix
        } else if (messageContent.compare(0, 5, "SM25:") == 0) {
            // SM2 message
            aggregatedSM25Message += messageContent.substr(4) + "/"; // Remove the prefix
        } else if (messageContent.compare(0, 5, "SM26:") == 0) {
            // SM2 message
            aggregatedSM26Message += messageContent.substr(4) + "/"; // Remove the prefix
        } else if (messageContent.compare(0, 5, "SM27:") == 0) {
            // SM2 message
            aggregatedSM27Message += messageContent.substr(4) + "/"; // Remove the prefix
        } else if (messageContent.compare(0, 5, "SM28:") == 0) {
            // SM2 message
            aggregatedSM28Message += messageContent.substr(4) + "/"; // Remove the prefix
        } else if (messageContent.compare(0, 5, "SM29:") == 0) {
            // SM2 message
            aggregatedSM29Message += messageContent.substr(4) + "/"; // Remove the prefix
        } else if (messageContent.compare(0, 5, "SM30:") == 0) {
            // SM2 message
            aggregatedSM30Message += messageContent.substr(4) + "/"; // Remove the prefix
        }

        delete msg;
    }

    // Encrypt the aggregated SM1 message with the original encryption key and send it
    if (!aggregatedSM1Message.empty()) {
        std::string encryptedSM1Message = encryptMessage("SM1: " + aggregatedSM1Message, encryptionKey2);
        cMessage *aggregatedSM1Msg = new cMessage();
        aggregatedSM1Msg->setName(encryptedSM1Message.c_str());

        // Retrieve the target submodule (UtilityCenter)
        cModule *target = getParentModule()->getSubmodule("UtilityCenter");

        // Send the aggregated SM1 message directly to the UtilityCenter
        sendDirect(aggregatedSM1Msg, target, "radioIn");
    }

    // Encrypt the aggregated SM2 message with a different encryption key and send it
    if (!aggregatedSM2Message.empty()) {
        std::string encryptedSM2Message = encryptMessage("SM2: " + aggregatedSM2Message, encryptionKey2);
        cMessage *aggregatedSM2Msg = new cMessage();
        aggregatedSM2Msg->setName(encryptedSM2Message.c_str());

        // Retrieve the target submodule (UtilityCenter)
        cModule *target = getParentModule()->getSubmodule("UtilityCenter");

        // Send the aggregated SM2 message directly to the UtilityCenter
        sendDirect(aggregatedSM2Msg, target, "radioIn");
    }

    // Encrypt the aggregated SM3 message with a different encryption key and send it
    if (!aggregatedSM3Message.empty()) {
        std::string encryptedSM3Message = encryptMessage("SM3: " + aggregatedSM3Message, encryptionKey2);
        cMessage *aggregatedSM3Msg = new cMessage();
        aggregatedSM3Msg->setName(encryptedSM3Message.c_str());

        // Retrieve the target submodule (UtilityCenter)
        cModule *target = getParentModule()->getSubmodule("UtilityCenter");

        // Send the aggregated SM3 message directly to the UtilityCenter
        sendDirect(aggregatedSM3Msg, target, "radioIn");
    }

    if (!aggregatedSM4Message.empty()) {
            std::string encryptedSM4Message = encryptMessage("SM4: " + aggregatedSM4Message, encryptionKey2);
            cMessage *aggregatedSM4Msg = new cMessage();
            aggregatedSM4Msg->setName(encryptedSM4Message.c_str());

            // Retrieve the target submodule (UtilityCenter)
            cModule *target = getParentModule()->getSubmodule("UtilityCenter");

            // Send the aggregated SM2 message directly to the UtilityCenter
            sendDirect(aggregatedSM4Msg, target, "radioIn");
        }

    if (!aggregatedSM5Message.empty()) {
            std::string encryptedSM5Message = encryptMessage("SM5: " + aggregatedSM5Message, encryptionKey2);
            cMessage *aggregatedSM5Msg = new cMessage();
            aggregatedSM5Msg->setName(encryptedSM5Message.c_str());

            // Retrieve the target submodule (UtilityCenter)
            cModule *target = getParentModule()->getSubmodule("UtilityCenter");

            // Send the aggregated SM2 message directly to the UtilityCenter
            sendDirect(aggregatedSM5Msg, target, "radioIn");
        }
    if (!aggregatedSM6Message.empty()) {
            std::string encryptedSM6Message = encryptMessage("SM6: " + aggregatedSM5Message, encryptionKey2);
            cMessage *aggregatedSM6Msg = new cMessage();
            aggregatedSM6Msg->setName(encryptedSM6Message.c_str());

            // Retrieve the target submodule (UtilityCenter)
            cModule *target = getParentModule()->getSubmodule("UtilityCenter");

            // Send the aggregated SM2 message directly to the UtilityCenter
            sendDirect(aggregatedSM6Msg, target, "radioIn");
        }
    if (!aggregatedSM7Message.empty()) {
            std::string encryptedSM7Message = encryptMessage("SM7: " + aggregatedSM7Message, encryptionKey2);
            cMessage *aggregatedSM7Msg = new cMessage();
            aggregatedSM7Msg->setName(encryptedSM7Message.c_str());

            // Retrieve the target submodule (UtilityCenter)
            cModule *target = getParentModule()->getSubmodule("UtilityCenter");

            // Send the aggregated SM2 message directly to the UtilityCenter
            sendDirect(aggregatedSM7Msg, target, "radioIn");
        }
    if (!aggregatedSM8Message.empty()) {
            std::string encryptedSM8Message = encryptMessage("SM8: " + aggregatedSM8Message, encryptionKey2);
            cMessage *aggregatedSM8Msg = new cMessage();
            aggregatedSM8Msg->setName(encryptedSM8Message.c_str());

            // Retrieve the target submodule (UtilityCenter)
            cModule *target = getParentModule()->getSubmodule("UtilityCenter");

            // Send the aggregated SM2 message directly to the UtilityCenter
            sendDirect(aggregatedSM8Msg, target, "radioIn");
        }
    if (!aggregatedSM9Message.empty()) {
            std::string encryptedSM9Message = encryptMessage("SM9: " + aggregatedSM9Message, encryptionKey2);
            cMessage *aggregatedSM9Msg = new cMessage();
            aggregatedSM9Msg->setName(encryptedSM9Message.c_str());

            // Retrieve the target submodule (UtilityCenter)
            cModule *target = getParentModule()->getSubmodule("UtilityCenter");

            // Send the aggregated SM2 message directly to the UtilityCenter
            sendDirect(aggregatedSM9Msg, target, "radioIn");
        }
    if (!aggregatedSM10Message.empty()) {
            std::string encryptedSM10Message = encryptMessage("SM10: " + aggregatedSM10Message, encryptionKey2);
            cMessage *aggregatedSM10Msg = new cMessage();
            aggregatedSM10Msg->setName(encryptedSM10Message.c_str());

            // Retrieve the target submodule (UtilityCenter)
            cModule *target = getParentModule()->getSubmodule("UtilityCenter");

            // Send the aggregated SM2 message directly to the UtilityCenter
            sendDirect(aggregatedSM10Msg, target, "radioIn");
        }
    if (!aggregatedSM11Message.empty()) {
            std::string encryptedSM11Message = encryptMessage("SM11: " + aggregatedSM11Message, encryptionKey2);
            cMessage *aggregatedSM11Msg = new cMessage();
            aggregatedSM11Msg->setName(encryptedSM11Message.c_str());

            // Retrieve the target submodule (UtilityCenter)
            cModule *target = getParentModule()->getSubmodule("UtilityCenter");

            // Send the aggregated SM2 message directly to the UtilityCenter
            sendDirect(aggregatedSM11Msg, target, "radioIn");
        }
    if (!aggregatedSM12Message.empty()) {
            std::string encryptedSM12Message = encryptMessage("SM12: " + aggregatedSM12Message, encryptionKey2);
            cMessage *aggregatedSM12Msg = new cMessage();
            aggregatedSM12Msg->setName(encryptedSM12Message.c_str());

            // Retrieve the target submodule (UtilityCenter)
            cModule *target = getParentModule()->getSubmodule("UtilityCenter");

            // Send the aggregated SM2 message directly to the UtilityCenter
            sendDirect(aggregatedSM12Msg, target, "radioIn");
        }
    if (!aggregatedSM13Message.empty()) {
            std::string encryptedSM13Message = encryptMessage("SM13: " + aggregatedSM13Message, encryptionKey2);
            cMessage *aggregatedSM13Msg = new cMessage();
            aggregatedSM13Msg->setName(encryptedSM13Message.c_str());

            // Retrieve the target submodule (UtilityCenter)
            cModule *target = getParentModule()->getSubmodule("UtilityCenter");

            // Send the aggregated SM2 message directly to the UtilityCenter
            sendDirect(aggregatedSM13Msg, target, "radioIn");
        }
    if (!aggregatedSM14Message.empty()) {
            std::string encryptedSM14Message = encryptMessage("SM14: " + aggregatedSM14Message, encryptionKey2);
            cMessage *aggregatedSM14Msg = new cMessage();
            aggregatedSM14Msg->setName(encryptedSM14Message.c_str());

            // Retrieve the target submodule (UtilityCenter)
            cModule *target = getParentModule()->getSubmodule("UtilityCenter");

            // Send the aggregated SM2 message directly to the UtilityCenter
            sendDirect(aggregatedSM14Msg, target, "radioIn");
        }
    if (!aggregatedSM15Message.empty()) {
            std::string encryptedSM15Message = encryptMessage("SM15: " + aggregatedSM15Message, encryptionKey2);
            cMessage *aggregatedSM15Msg = new cMessage();
            aggregatedSM15Msg->setName(encryptedSM15Message.c_str());

            // Retrieve the target submodule (UtilityCenter)
            cModule *target = getParentModule()->getSubmodule("UtilityCenter");

            // Send the aggregated SM2 message directly to the UtilityCenter
            sendDirect(aggregatedSM15Msg, target, "radioIn");
        }
    if (!aggregatedSM16Message.empty()) {
            std::string encryptedSM16Message = encryptMessage("SM16: " + aggregatedSM16Message, encryptionKey2);
            cMessage *aggregatedSM16Msg = new cMessage();
            aggregatedSM16Msg->setName(encryptedSM16Message.c_str());

            // Retrieve the target submodule (UtilityCenter)
            cModule *target = getParentModule()->getSubmodule("UtilityCenter");

            // Send the aggregated SM2 message directly to the UtilityCenter
            sendDirect(aggregatedSM16Msg, target, "radioIn");
        }
    if (!aggregatedSM17Message.empty()) {
            std::string encryptedSM17Message = encryptMessage("SM17: " + aggregatedSM17Message, encryptionKey2);
            cMessage *aggregatedSM17Msg = new cMessage();
            aggregatedSM17Msg->setName(encryptedSM17Message.c_str());

            // Retrieve the target submodule (UtilityCenter)
            cModule *target = getParentModule()->getSubmodule("UtilityCenter");

            // Send the aggregated SM2 message directly to the UtilityCenter
            sendDirect(aggregatedSM17Msg, target, "radioIn");
        }
    if (!aggregatedSM18Message.empty()) {
            std::string encryptedSM18Message = encryptMessage("SM18: " + aggregatedSM18Message, encryptionKey2);
            cMessage *aggregatedSM18Msg = new cMessage();
            aggregatedSM18Msg->setName(encryptedSM18Message.c_str());

            // Retrieve the target submodule (UtilityCenter)
            cModule *target = getParentModule()->getSubmodule("UtilityCenter");

            // Send the aggregated SM2 message directly to the UtilityCenter
            sendDirect(aggregatedSM18Msg, target, "radioIn");
        }
    if (!aggregatedSM19Message.empty()) {
            std::string encryptedSM19Message = encryptMessage("SM19: " + aggregatedSM19Message, encryptionKey2);
            cMessage *aggregatedSM19Msg = new cMessage();
            aggregatedSM19Msg->setName(encryptedSM19Message.c_str());

            // Retrieve the target submodule (UtilityCenter)
            cModule *target = getParentModule()->getSubmodule("UtilityCenter");

            // Send the aggregated SM2 message directly to the UtilityCenter
            sendDirect(aggregatedSM19Msg, target, "radioIn");
        }
    if (!aggregatedSM20Message.empty()) {
            std::string encryptedSM20Message = encryptMessage("SM20: " + aggregatedSM20Message, encryptionKey2);
            cMessage *aggregatedSM20Msg = new cMessage();
            aggregatedSM20Msg->setName(encryptedSM20Message.c_str());

            // Retrieve the target submodule (UtilityCenter)
            cModule *target = getParentModule()->getSubmodule("UtilityCenter");

            // Send the aggregated SM2 message directly to the UtilityCenter
            sendDirect(aggregatedSM20Msg, target, "radioIn");
        }
    if (!aggregatedSM21Message.empty()) {
            std::string encryptedSM21Message = encryptMessage("SM21: " + aggregatedSM21Message, encryptionKey2);
            cMessage *aggregatedSM21Msg = new cMessage();
            aggregatedSM21Msg->setName(encryptedSM21Message.c_str());

            // Retrieve the target submodule (UtilityCenter)
            cModule *target = getParentModule()->getSubmodule("UtilityCenter");

            // Send the aggregated SM2 message directly to the UtilityCenter
            sendDirect(aggregatedSM21Msg, target, "radioIn");
        }
    if (!aggregatedSM22Message.empty()) {
            std::string encryptedSM22Message = encryptMessage("SM22: " + aggregatedSM22Message, encryptionKey2);
            cMessage *aggregatedSM22Msg = new cMessage();
            aggregatedSM22Msg->setName(encryptedSM22Message.c_str());

            // Retrieve the target submodule (UtilityCenter)
            cModule *target = getParentModule()->getSubmodule("UtilityCenter");

            // Send the aggregated SM2 message directly to the UtilityCenter
            sendDirect(aggregatedSM22Msg, target, "radioIn");
        }
    if (!aggregatedSM23Message.empty()) {
            std::string encryptedSM23Message = encryptMessage("SM23: " + aggregatedSM23Message, encryptionKey2);
            cMessage *aggregatedSM23Msg = new cMessage();
            aggregatedSM23Msg->setName(encryptedSM23Message.c_str());

            // Retrieve the target submodule (UtilityCenter)
            cModule *target = getParentModule()->getSubmodule("UtilityCenter");

            // Send the aggregated SM2 message directly to the UtilityCenter
            sendDirect(aggregatedSM23Msg, target, "radioIn");
        }
    if (!aggregatedSM24Message.empty()) {
            std::string encryptedSM24Message = encryptMessage("SM24: " + aggregatedSM24Message, encryptionKey2);
            cMessage *aggregatedSM24Msg = new cMessage();
            aggregatedSM24Msg->setName(encryptedSM24Message.c_str());

            // Retrieve the target submodule (UtilityCenter)
            cModule *target = getParentModule()->getSubmodule("UtilityCenter");

            // Send the aggregated SM2 message directly to the UtilityCenter
            sendDirect(aggregatedSM24Msg, target, "radioIn");
        }
    if (!aggregatedSM25Message.empty()) {
            std::string encryptedSM25Message = encryptMessage("SM25: " + aggregatedSM25Message, encryptionKey2);
            cMessage *aggregatedSM25Msg = new cMessage();
            aggregatedSM25Msg->setName(encryptedSM25Message.c_str());

            // Retrieve the target submodule (UtilityCenter)
            cModule *target = getParentModule()->getSubmodule("UtilityCenter");

            // Send the aggregated SM2 message directly to the UtilityCenter
            sendDirect(aggregatedSM25Msg, target, "radioIn");
        }
    if (!aggregatedSM26Message.empty()) {
            std::string encryptedSM26Message = encryptMessage("SM26: " + aggregatedSM26Message, encryptionKey2);
            cMessage *aggregatedSM26Msg = new cMessage();
            aggregatedSM26Msg->setName(encryptedSM26Message.c_str());

            // Retrieve the target submodule (UtilityCenter)
            cModule *target = getParentModule()->getSubmodule("UtilityCenter");

            // Send the aggregated SM2 message directly to the UtilityCenter
            sendDirect(aggregatedSM26Msg, target, "radioIn");
        }
    if (!aggregatedSM27Message.empty()) {
            std::string encryptedSM27Message = encryptMessage("SM27: " + aggregatedSM27Message, encryptionKey2);
            cMessage *aggregatedSM27Msg = new cMessage();
            aggregatedSM27Msg->setName(encryptedSM27Message.c_str());

            // Retrieve the target submodule (UtilityCenter)
            cModule *target = getParentModule()->getSubmodule("UtilityCenter");

            // Send the aggregated SM2 message directly to the UtilityCenter
            sendDirect(aggregatedSM27Msg, target, "radioIn");
        }
    if (!aggregatedSM28Message.empty()) {
            std::string encryptedSM28Message = encryptMessage("SM28: " + aggregatedSM28Message, encryptionKey2);
            cMessage *aggregatedSM28Msg = new cMessage();
            aggregatedSM28Msg->setName(encryptedSM28Message.c_str());

            // Retrieve the target submodule (UtilityCenter)
            cModule *target = getParentModule()->getSubmodule("UtilityCenter");

            // Send the aggregated SM2 message directly to the UtilityCenter
            sendDirect(aggregatedSM28Msg, target, "radioIn");
        }
    if (!aggregatedSM29Message.empty()) {
            std::string encryptedSM29Message = encryptMessage("SM29: " + aggregatedSM26Message, encryptionKey2);
            cMessage *aggregatedSM29Msg = new cMessage();
            aggregatedSM29Msg->setName(encryptedSM29Message.c_str());

            // Retrieve the target submodule (UtilityCenter)
            cModule *target = getParentModule()->getSubmodule("UtilityCenter");

            // Send the aggregated SM2 message directly to the UtilityCenter
            sendDirect(aggregatedSM29Msg, target, "radioIn");
        }
    if (!aggregatedSM30Message.empty()) {
            std::string encryptedSM30Message = encryptMessage("SM30: " + aggregatedSM30Message, encryptionKey2);
            cMessage *aggregatedSM30Msg = new cMessage();
            aggregatedSM30Msg->setName(encryptedSM30Message.c_str());

            // Retrieve the target submodule (UtilityCenter)
            cModule *target = getParentModule()->getSubmodule("UtilityCenter");

            // Send the aggregated SM2 message directly to the UtilityCenter
            sendDirect(aggregatedSM30Msg, target, "radioIn");
        }

    std::string aggregatedDroppedMessages;
        while (!droppedMessageQueue.isEmpty()) {
            cMessage *droppedMsg = check_and_cast<cMessage *>(droppedMessageQueue.pop());
            std::string droppedMessageContent = droppedMsg->getName();
            aggregatedDroppedMessages += droppedMessageContent + "/";
            delete droppedMsg;
        }
        if (!aggregatedDroppedMessages.empty()) {
            std::string encryptedDroppedMessages = encryptMessage("Dropped: " + aggregatedDroppedMessages, encryptionKey2);
            cMessage *aggregatedDroppedMsg = new cMessage();
            aggregatedDroppedMsg->setName(encryptedDroppedMessages.c_str());

            cModule *target = getParentModule()->getSubmodule("UtilityCenter");
            sendDirect(aggregatedDroppedMsg, target, "radioIn");
        }

    // Print the dropped message count for the current time period
    EV << "Time Period " << timePeriodCounter << " - Dropped Message Count for SmartMeter1: " << droppedMessageCountSM1 << endl;
    EV << "Time Period " << timePeriodCounter << " - Dropped Message Count for SmartMeter2: " << droppedMessageCountSM2 << endl;
    EV << "Time Period " << timePeriodCounter << " - Dropped Message Count for SmartMeter3: " << droppedMessageCountSM3 << endl;
    EV << "Time Period " << timePeriodCounter << " - Dropped Message Count for SmartMeter4: " << droppedMessageCountSM4 << endl;
    EV << "Time Period " << timePeriodCounter << " - Dropped Message Count for SmartMeter5: " << droppedMessageCountSM5 << endl;
    EV << "Time Period " << timePeriodCounter << " - Dropped Message Count for SmartMeter6: " << droppedMessageCountSM6 << endl;
    EV << "Time Period " << timePeriodCounter << " - Dropped Message Count for SmartMeter7: " << droppedMessageCountSM7 << endl;
    EV << "Time Period " << timePeriodCounter << " - Dropped Message Count for SmartMeter8: " << droppedMessageCountSM8 << endl;
    EV << "Time Period " << timePeriodCounter << " - Dropped Message Count for SmartMeter9: " << droppedMessageCountSM9 << endl;
    EV << "Time Period " << timePeriodCounter << " - Dropped Message Count for SmartMeter10: " << droppedMessageCountSM10 << endl;
    EV << "Time Period " << timePeriodCounter << " - Dropped Message Count for SmartMeter11: " << droppedMessageCountSM11 << endl;
    EV << "Time Period " << timePeriodCounter << " - Dropped Message Count for SmartMeter12: " << droppedMessageCountSM12 << endl;
    EV << "Time Period " << timePeriodCounter << " - Dropped Message Count for SmartMeter13: " << droppedMessageCountSM13 << endl;
    EV << "Time Period " << timePeriodCounter << " - Dropped Message Count for SmartMeter14: " << droppedMessageCountSM14 << endl;
    EV << "Time Period " << timePeriodCounter << " - Dropped Message Count for SmartMeter15: " << droppedMessageCountSM15 << endl;
    EV << "Time Period " << timePeriodCounter << " - Dropped Message Count for SmartMeter16: " << droppedMessageCountSM16 << endl;
    EV << "Time Period " << timePeriodCounter << " - Dropped Message Count for SmartMeter17: " << droppedMessageCountSM17 << endl;
    EV << "Time Period " << timePeriodCounter << " - Dropped Message Count for SmartMeter18: " << droppedMessageCountSM18 << endl;
    EV << "Time Period " << timePeriodCounter << " - Dropped Message Count for SmartMeter19: " << droppedMessageCountSM19 << endl;
    EV << "Time Period " << timePeriodCounter << " - Dropped Message Count for SmartMeter20: " << droppedMessageCountSM20 << endl;
    EV << "Time Period " << timePeriodCounter << " - Dropped Message Count for SmartMeter21: " << droppedMessageCountSM21 << endl;
    EV << "Time Period " << timePeriodCounter << " - Dropped Message Count for SmartMeter22: " << droppedMessageCountSM22 << endl;
    EV << "Time Period " << timePeriodCounter << " - Dropped Message Count for SmartMeter23: " << droppedMessageCountSM23 << endl;
    EV << "Time Period " << timePeriodCounter << " - Dropped Message Count for SmartMeter24: " << droppedMessageCountSM24 << endl;
    EV << "Time Period " << timePeriodCounter << " - Dropped Message Count for SmartMeter25: " << droppedMessageCountSM25 << endl;
    EV << "Time Period " << timePeriodCounter << " - Dropped Message Count for SmartMeter26: " << droppedMessageCountSM26 << endl;
    EV << "Time Period " << timePeriodCounter << " - Dropped Message Count for SmartMeter27: " << droppedMessageCountSM27 << endl;
    EV << "Time Period " << timePeriodCounter << " - Dropped Message Count for SmartMeter28: " << droppedMessageCountSM28 << endl;
    EV << "Time Period " << timePeriodCounter << " - Dropped Message Count for SmartMeter29: " << droppedMessageCountSM29 << endl;
    EV << "Time Period " << timePeriodCounter << " - Dropped Message Count for SmartMeter30: " << droppedMessageCountSM30 << endl;
    // Store the dropped message count in the lists for each smart meter
    droppedMessageCountListSM1[timePeriodCounter] = droppedMessageCountSM1;
    droppedMessageCountListSM2[timePeriodCounter] = droppedMessageCountSM2;
    droppedMessageCountListSM3[timePeriodCounter] = droppedMessageCountSM3;
    droppedMessageCountListSM4[timePeriodCounter] = droppedMessageCountSM4;
    droppedMessageCountListSM5[timePeriodCounter] = droppedMessageCountSM5;
    droppedMessageCountListSM6[timePeriodCounter] = droppedMessageCountSM6;
    droppedMessageCountListSM7[timePeriodCounter] = droppedMessageCountSM7;
    droppedMessageCountListSM8[timePeriodCounter] = droppedMessageCountSM8;
    droppedMessageCountListSM9[timePeriodCounter] = droppedMessageCountSM9;
    droppedMessageCountListSM10[timePeriodCounter] = droppedMessageCountSM10;
    droppedMessageCountListSM11[timePeriodCounter] = droppedMessageCountSM11;
    droppedMessageCountListSM12[timePeriodCounter] = droppedMessageCountSM12;
    droppedMessageCountListSM13[timePeriodCounter] = droppedMessageCountSM13;
    droppedMessageCountListSM14[timePeriodCounter] = droppedMessageCountSM14;
    droppedMessageCountListSM15[timePeriodCounter] = droppedMessageCountSM15;
    droppedMessageCountListSM16[timePeriodCounter] = droppedMessageCountSM16;
    droppedMessageCountListSM17[timePeriodCounter] = droppedMessageCountSM17;
    droppedMessageCountListSM18[timePeriodCounter] = droppedMessageCountSM18;
    droppedMessageCountListSM19[timePeriodCounter] = droppedMessageCountSM19;
    droppedMessageCountListSM20[timePeriodCounter] = droppedMessageCountSM20;
    droppedMessageCountListSM21[timePeriodCounter] = droppedMessageCountSM21;
    droppedMessageCountListSM22[timePeriodCounter] = droppedMessageCountSM22;
    droppedMessageCountListSM23[timePeriodCounter] = droppedMessageCountSM23;
    droppedMessageCountListSM24[timePeriodCounter] = droppedMessageCountSM24;
    droppedMessageCountListSM25[timePeriodCounter] = droppedMessageCountSM25;
    droppedMessageCountListSM26[timePeriodCounter] = droppedMessageCountSM26;
    droppedMessageCountListSM27[timePeriodCounter] = droppedMessageCountSM27;
    droppedMessageCountListSM28[timePeriodCounter] = droppedMessageCountSM28;
    droppedMessageCountListSM29[timePeriodCounter] = droppedMessageCountSM29;
    droppedMessageCountListSM30[timePeriodCounter] = droppedMessageCountSM30;


    // Reset the dropped message counts for the next time period
    droppedMessageCountSM1 = 0;
    droppedMessageCountSM2 = 0;
    droppedMessageCountSM3 = 0;
    droppedMessageCountSM4 = 0;
    droppedMessageCountSM5 = 0;
    droppedMessageCountSM6 = 0;
    droppedMessageCountSM7 = 0;
    droppedMessageCountSM8 = 0;
    droppedMessageCountSM9 = 0;
    droppedMessageCountSM10 = 0;
    droppedMessageCountSM11 = 0;
    droppedMessageCountSM12 = 0;
    droppedMessageCountSM13 = 0;
    droppedMessageCountSM14 = 0;
    droppedMessageCountSM15 = 0;
    droppedMessageCountSM16 = 0;
    droppedMessageCountSM17 = 0;
    droppedMessageCountSM18 = 0;
    droppedMessageCountSM19 = 0;
    droppedMessageCountSM20 = 0;
    droppedMessageCountSM21 = 0;
    droppedMessageCountSM22 = 0;
    droppedMessageCountSM23 = 0;
    droppedMessageCountSM24 = 0;
    droppedMessageCountSM25 = 0;
    droppedMessageCountSM26 = 0;
    droppedMessageCountSM27 = 0;
    droppedMessageCountSM28 = 0;
    droppedMessageCountSM29 = 0;
    droppedMessageCountSM30 = 0;
    // Increment the time period counter
    timePeriodCounter++;

    // Check if the simulation has reached the desired number of time periods
    if (timePeriodCounter == 6) {
        // Print the lists at the end of the simulation
        EV << "Dropped Message Count for SmartMeter1 (Time Periods): ";
        for (int i = 0; i < timePeriodCounter; i++) {
            EV << droppedMessageCountListSM1[i] << ", ";
        }
        EV << endl;

        EV << "Dropped Message Count for SmartMeter2 (Time Periods): ";
        for (int i = 0; i < timePeriodCounter; i++) {
            EV << droppedMessageCountListSM2[i] << ", ";
        }
        EV << endl;

        EV << "Dropped Message Count for SmartMeter3 (Time Periods): ";
        for (int i = 0; i < timePeriodCounter; i++) {
            EV << droppedMessageCountListSM3[i] << ", ";
        }
        EV << endl;

        EV << "Dropped Message Count for SmartMeter4 (Time Periods): ";
        for (int i = 0; i < timePeriodCounter; i++) {
            EV << droppedMessageCountListSM4[i] << ", ";
        }
        EV << endl;

        EV << "Dropped Message Count for SmartMeter5 (Time Periods): ";
        for (int i = 0; i < timePeriodCounter; i++) {
            EV << droppedMessageCountListSM5[i] << ", ";
        }
        EV << endl;

        EV << "Dropped Message Count for SmartMeter6 (Time Periods): ";
        for (int i = 0; i < timePeriodCounter; i++) {
            EV << droppedMessageCountListSM6[i] << ", ";
        }
        EV << endl;
        EV << "Dropped Message Count for SmartMeter7 (Time Periods): ";
        for (int i = 0; i < timePeriodCounter; i++) {
            EV << droppedMessageCountListSM7[i] << ", ";
        }
        EV << endl;
        EV << "Dropped Message Count for SmartMeter8 (Time Periods): ";
        for (int i = 0; i < timePeriodCounter; i++) {
            EV << droppedMessageCountListSM8[i] << ", ";
        }
        EV << endl;

        EV << "Dropped Message Count for SmartMeter9 (Time Periods): ";
        for (int i = 0; i < timePeriodCounter; i++) {
            EV << droppedMessageCountListSM9[i] << ", ";
        }
        EV << endl;
        EV << "Dropped Message Count for SmartMeter10 (Time Periods): ";
        for (int i = 0; i < timePeriodCounter; i++) {
            EV << droppedMessageCountListSM10[i] << ", ";
        }
        EV << endl;
        EV << "Dropped Message Count for SmartMeter11 (Time Periods): ";
        for (int i = 0; i < timePeriodCounter; i++) {
            EV << droppedMessageCountListSM11[i] << ", ";
        }
        EV << endl;
        EV << "Dropped Message Count for SmartMeter12 (Time Periods): ";
        for (int i = 0; i < timePeriodCounter; i++) {
            EV << droppedMessageCountListSM12[i] << ", ";
        }
        EV << endl;
        EV << "Dropped Message Count for SmartMeter13 (Time Periods): ";
        for (int i = 0; i < timePeriodCounter; i++) {
            EV << droppedMessageCountListSM13[i] << ", ";
        }
        EV << endl;
        EV << "Dropped Message Count for SmartMeter14 (Time Periods): ";
        for (int i = 0; i < timePeriodCounter; i++) {
            EV << droppedMessageCountListSM14[i] << ", ";
        }
        EV << endl;
        EV << "Dropped Message Count for SmartMeter15 (Time Periods): ";
        for (int i = 0; i < timePeriodCounter; i++) {
            EV << droppedMessageCountListSM15[i] << ", ";
        }
        EV << endl;
        EV << "Dropped Message Count for SmartMeter16 (Time Periods): ";
        for (int i = 0; i < timePeriodCounter; i++) {
            EV << droppedMessageCountListSM16[i] << ", ";
        }
        EV << endl;
        EV << "Dropped Message Count for SmartMeter17 (Time Periods): ";
        for (int i = 0; i < timePeriodCounter; i++) {
            EV << droppedMessageCountListSM17[i] << ", ";
        }
        EV << endl;
        EV << "Dropped Message Count for SmartMeter18 (Time Periods): ";
        for (int i = 0; i < timePeriodCounter; i++) {
            EV << droppedMessageCountListSM18[i] << ", ";
        }
        EV << endl;
        EV << "Dropped Message Count for SmartMeter19 (Time Periods): ";
        for (int i = 0; i < timePeriodCounter; i++) {
            EV << droppedMessageCountListSM19[i] << ", ";
        }
        EV << endl;
        EV << "Dropped Message Count for SmartMeter20 (Time Periods): ";
        for (int i = 0; i < timePeriodCounter; i++) {
            EV << droppedMessageCountListSM20[i] << ", ";
        }
        EV << endl;
        EV << "Dropped Message Count for SmartMeter21 (Time Periods): ";
        for (int i = 0; i < timePeriodCounter; i++) {
            EV << droppedMessageCountListSM21[i] << ", ";
        }
        EV << endl;
        EV << "Dropped Message Count for SmartMeter22 (Time Periods): ";
        for (int i = 0; i < timePeriodCounter; i++) {
            EV << droppedMessageCountListSM22[i] << ", ";
        }
        EV << endl;
        EV << "Dropped Message Count for SmartMeter23 (Time Periods): ";
        for (int i = 0; i < timePeriodCounter; i++) {
            EV << droppedMessageCountListSM23[i] << ", ";
        }
        EV << endl;
        EV << "Dropped Message Count for SmartMeter24 (Time Periods): ";
        for (int i = 0; i < timePeriodCounter; i++) {
            EV << droppedMessageCountListSM24[i] << ", ";
        }
        EV << endl;
        EV << "Dropped Message Count for SmartMeter25 (Time Periods): ";
        for (int i = 0; i < timePeriodCounter; i++) {
            EV << droppedMessageCountListSM25[i] << ", ";
        }
        EV << endl;
        EV << "Dropped Message Count for SmartMeter26 (Time Periods): ";
        for (int i = 0; i < timePeriodCounter; i++) {
            EV << droppedMessageCountListSM26[i] << ", ";
        }
        EV << endl;
        EV << "Dropped Message Count for SmartMeter27 (Time Periods): ";
        for (int i = 0; i < timePeriodCounter; i++) {
            EV << droppedMessageCountListSM27[i] << ", ";
        }
        EV << endl;
        EV << "Dropped Message Count for SmartMeter28 (Time Periods): ";
        for (int i = 0; i < timePeriodCounter; i++) {
            EV << droppedMessageCountListSM28[i] << ", ";
        }
        EV << endl;
        EV << "Dropped Message Count for SmartMeter29 (Time Periods): ";
        for (int i = 0; i < timePeriodCounter; i++) {
            EV << droppedMessageCountListSM29[i] << ", ";
        }
        EV << endl;
        EV << "Dropped Message Count for SmartMeter30 (Time Periods): ";
        for (int i = 0; i < timePeriodCounter; i++) {
            EV << droppedMessageCountListSM30[i] << ", ";
        }
        EV << endl;

    }
    // ... (rest of the code remains the same)
}

void server::scheduleNextMessage() {
    if (messageTimer && messageTimer->isScheduled()) {
        // Cancel any previously scheduled message timer
        cancelEvent(messageTimer);
    }

    // Schedule the next message sending after the interval
    messageTimer = new cMessage("MessageTimer");
    scheduleAt(simTime() + messageInterval, messageTimer);
}

std::string server::decryptMessage(const std::string& encryptedMessage) {
    // Simulate the decryption delay
    scheduleAt(simTime() + 1.0e-6, new cMessage("DecryptionDelay"));

    std::string decryptedMessage = encryptedMessage;
    for (char& c : decryptedMessage) {
        c = c ^ encryptionKey;
    }
    return decryptedMessage;
}

std::string server::encryptMessage(const std::string& originalMessage, const char key) {
    // Simulate the encryption delay
    scheduleAt(simTime() + 1.0e-6, new cMessage("EncryptionDelay"));

    std::string encryptedMessage = originalMessage;
    for (char& c : encryptedMessage) {
        c = c ^ key;
    }
    return encryptedMessage;
}

