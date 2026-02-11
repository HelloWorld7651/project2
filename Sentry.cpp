#include "Sentry.h"
#include "NetworkManager.h"
#include "EventNetwork.h"
#include "EventStep.h"
#include "WorldManager.h"

enum class MessageType { UNDEFINED = -1, EXIT, CHAT };

// Define the protocol header size here locally or use a shared header
// We assume message starts with int (size)
#define HEADER_SIZE sizeof(int)

using namespace df;

Sentry::Sentry() {
    setType("Sentry");
    setSolidness(df::SPECTRAL);
    registerInterest(df::STEP_EVENT);
}

int Sentry::eventHandler(const Event *p_e) {
    if (p_e->getType() == STEP_EVENT) {
        handleStep();
        return 1;
    }
    return 0;
}

void Sentry::handleStep() {
    // 1. Accept new connections if we are a server
    if (NM.isServer()) {
        NM.accept();
    }

    // 2. Check for incoming data
    for (int i = 0; i < NM.getNumConnections(); i++) {
        if (NM.isConnected(i)) {
            int bytes = NM.isData(i);
            
            // Check if we have enough for the Size integer
            if (bytes >= (int)HEADER_SIZE) {
                int msg_size = 0;
                // Peek at the size (leave=true)
                NM.receive(&msg_size, sizeof(int), true, i);
                
                // If we have the full message, fire the event
                if (bytes >= msg_size && msg_size > 0) {
                    EventNetwork en(NetworkEventLabel::DATA);
                    en.setSocketIndex(i);
                    en.setBytes(msg_size);
                    WM.onEvent(&en);
                }
            }
        }
    }
}