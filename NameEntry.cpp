#include "NameEntry.h"
#include "Input.h"
#include "yakclient.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "TextBox.h" 

enum class MessageType { UNDEFINED = -1, EXIT, CHAT };

NameEntry::NameEntry() {
  setType("NameEntry");
  setText("");
  setViewString("Enter Username: ");
  setBorder(true);
  setColor(df::WHITE);
  setLocation(df::CENTER_CENTER);
  setLimit(20);
}

void NameEntry::callback() {
  df::TextBox *p_t = new df::TextBox();
  p_t->setSize(df::Vector(40, 15));
  p_t->setLocation(df::Vector(5, 5));

  // Spawn Client Listener
  new yakclient(p_t);
  
  // Spawn Input Bar
  new Input(getText(), p_t);

  WM.markForDelete(this);
}