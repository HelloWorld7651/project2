#ifndef SERVERENTRY_H
#define SERVERENTRY_H

#include "TextEntry.h"

class ServerEntry : public df::TextEntry {
 public:
  ServerEntry();
  void callback() override;
};
#endif