#include "EventNetwork.h"

using namespace df;

EventNetwork::EventNetwork(NetworkEventLabel label) {
    setType(NETWORK_EVENT);
    m_label = label;
    m_socket_index = -1;
    m_bytes = 0;
}

void EventNetwork::setLabel(NetworkEventLabel new_label) {
    m_label = new_label;
}

NetworkEventLabel EventNetwork::getLabel() const {
    return m_label;
}

void EventNetwork::setSocketIndex(int new_socket_index) {
    m_socket_index = new_socket_index;
}

int EventNetwork::getSocketIndex() const {
    return m_socket_index;
}

void EventNetwork::setBytes(int new_bytes) {
    m_bytes = new_bytes;
}

int EventNetwork::getBytes() const {
    return m_bytes;
}