#include "ServerEntry.h"
#include "NameEntry.h"
#include "NetworkManager.h"
#include "LogManager.h"
#include "WorldManager.h"

enum class MessageType { UNDEFINED = -1, EXIT, CHAT };

ServerEntry::ServerEntry() {
  setType("ServerEntry");
  setText("127.0.0.1"); // Default to Localhost
  setViewString("Enter Server IP: ");
  setBorder(true);
  setColor(df::WHITE);
  setLocation(df::CENTER_CENTER);
  setLimit(20);
}

void ServerEntry::callback() {
  std::string ip = getText();
  // Attempt connection
  if (NM.connect(ip, "9876") == -1) {
      setText("Failed. Try again.");
  } else {
      new NameEntry();
      WM.markForDelete(this);
  }
}