#include "yakclient.h"
#include "NetworkManager.h"
#include "EventNetwork.h"
#include "LogManager.h"
#include <cstring>

#define MAX_MESSAGE_SIZE 1024
enum class MessageType { UNDEFINED = -1, EXIT, CHAT };
struct PacketHeader { int size; MessageType type; };

using namespace df;

yakclient::yakclient(df::TextBox *p_box) {
    setType("YakClient");
    m_p_text_box = p_box;
    
    if (NM.isConnected()) {
        m_p_text_box->addText("Connected!\n");
    } else {
        m_p_text_box->addText("Error: Not connected.\n");
    }
    registerInterest(df::NETWORK_EVENT);
}

yakclient::~yakclient() {
    PacketHeader head;
    head.type = MessageType::EXIT;
    head.size = sizeof(head);
    NM.send(&head, sizeof(head));
    NM.closeAll();
}

int yakclient::eventHandler(const df::Event *p_e) {
    if (p_e->getType() == df::NETWORK_EVENT) {
        const EventNetwork *p_net = dynamic_cast<const EventNetwork*>(p_e);
        if (p_net->getLabel() == NetworkEventLabel::DATA) {
            handleMessage();
        }
        return 1;
    }
    return 0;
}

void yakclient::handleMessage() {
    PacketHeader header;
    int bytes = NM.receive(&header, sizeof(header), false);
    if (bytes != sizeof(header)) return;

    int len = header.size - sizeof(PacketHeader);
    char buffer[MAX_MESSAGE_SIZE];
    memset(buffer, 0, MAX_MESSAGE_SIZE);

    if (len > 0) NM.receive(buffer, len, false);

    if (header.type == MessageType::CHAT) {
        m_p_text_box->addText(buffer);
    }
}