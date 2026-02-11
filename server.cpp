//
// server.cpp - The standalone Yak Server
//

// --- FIX 1: Define MessageType BEFORE includes ---
// utility.h needs this, so we must define it first.
enum class MessageType { 
    UNDEFINED = -1, 
    EXIT, 
    CHAT 
};

// Engine includes
#include "GameManager.h"
#include "LogManager.h"

// Project includes
#include "yakserver.h"
#include "Sentry.h"

int main(int argc, char *argv[]) {

  // --- FIX 2: Remove "df::" prefixes ---
  // GM, LM, and NM are macros that handle the namespace for you.
  
  if (GM.startUp())  {
    LM.writeLog("Error starting game manager!");
    return 1;
  }

  // Setup Logging
  LM.setLogLevel(2);
  LM.setFlush(true);
  LM.writeLog("Yak Server Starting...");

  // Create the Sentry (Required for networking)
  new df::Sentry();

  // Create the Server Logic
  new yakserver();

  // Run the Engine
  GM.run();

  // Shutdown
  GM.shutDown();

  return 0;
}