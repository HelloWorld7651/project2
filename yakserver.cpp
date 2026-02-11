#include "yakserver.h"
#include "NetworkManager.h"
#include "LogManager.h"
#include "EventNetwork.h"
#include <cstring> 

#define YAK_PORT "9876"
#define MAX_MESSAGE_SIZE 1024

enum class MessageType { UNDEFINED = -1, EXIT, CHAT };

struct PacketHeader {
    int size;
    MessageType type;
};

using namespace df;

yakserver::yakserver() {
    setType("YakServer");

    if (NM.startUp()) {
        LM.writeLog("YakServer: Error starting NetworkManager");
    }

    if (NM.setServer(true, YAK_PORT) != 0) {
        LM.writeLog("YakServer: Failed to open port %s", YAK_PORT);
    } else {
        LM.writeLog("YakServer: Listening on port %s", YAK_PORT);
    }

    registerInterest(df::NETWORK_EVENT);
}

yakserver::~yakserver() {
    NM.closeAll();
    NM.shutDown();
}

int yakserver::eventHandler(const df::Event *p_e) {
    if (p_e->getType() == df::NETWORK_EVENT) {
        const EventNetwork *p_net = dynamic_cast<const EventNetwork*>(p_e);

        switch(p_net->getLabel()) {
            case NetworkEventLabel::ACCEPT:
                LM.writeLog("YakServer: Client connected %d", p_net->getSocketIndex());
                break;
            case NetworkEventLabel::DATA:
                handleMessage(p_net->getSocketIndex());
                break;
            case NetworkEventLabel::CLOSE:
                LM.writeLog("YakServer: Client disconnected");
                break;
            default: break;
        }
        return 1;
    }
    return 0;
}

void yakserver::handleMessage(int index) {
    PacketHeader header;
    // Read Header
    int bytes = NM.receive(&header, sizeof(header), false, index);

    if (bytes != sizeof(header)) return;

    // Read Payload
    int data_len = header.size - sizeof(PacketHeader);
    char buffer[MAX_MESSAGE_SIZE];
    memset(buffer, 0, MAX_MESSAGE_SIZE);

    if (data_len > 0) {
        NM.receive(buffer, data_len, false, index);
    }

    // Process
    if (header.type == MessageType::CHAT) {
        LM.writeLog("YakServer: Broadcasting '%s'", buffer);

        // Broadcast to everyone ELSE
        int count = NM.getNumConnections();
        for (int i = 0; i < count; i++) {
            if (i != index && NM.isConnected(i)) {
                NM.send(&header, sizeof(header), i);
                NM.send(buffer, data_len, i);
            }
        }
    } else if (header.type == MessageType::EXIT) {
        NM.close(index);
    }
}