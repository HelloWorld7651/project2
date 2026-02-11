#include "GameManager.h"
#include "LogManager.h"
#include "ServerEntry.h"

enum class MessageType { UNDEFINED = -1, EXIT, CHAT };

void populateWorld();

int main(int argc, char *argv[]) {
  if (df::GM.startUp()) {
    df::LM.writeLog("Error starting game manager!");
    return 1;
  }

  df::LM.setLogLevel(1);
  df::LM.setFlush(true);
  df::splash();

  populateWorld();

  df::GM.run();
  df::GM.shutDown();
  return 0;
}

void populateWorld() {
    new ServerEntry();
}