#ifndef NAMEENTRY_H
#define NAMEENTRY_H
#include "TextEntry.h"
class NameEntry : public df::TextEntry {
 public:
  NameEntry();
  void callback() override;
};
#endif