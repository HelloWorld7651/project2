#ifndef EVENT_NETWORK_H
#define EVENT_NETWORK_H

#include <string>
#include "Event.h"

namespace df {

const std::string NETWORK_EVENT = "df-network";

enum class NetworkEventLabel {
    UNDEFINED = -1,
    ACCEPT,
    CONNECT,
    CLOSE,
    DATA,
};

class EventNetwork : public Event {
 private:
    NetworkEventLabel m_label;
    int m_socket_index;
    int m_bytes;

 public:
    EventNetwork(NetworkEventLabel label);
    void setLabel(NetworkEventLabel new_label);
    NetworkEventLabel getLabel() const;
    void setSocketIndex(int new_socket_index);
    int getSocketIndex() const;
    void setBytes(int new_bytes);
    int getBytes() const;
};

} // end namespace df
#endif