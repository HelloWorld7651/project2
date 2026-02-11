#ifndef INPUT_H
#define INPUT_H
#include <string>
#include "TextBox.h"
#include "TextEntry.h"

class Input : public df::TextEntry {
 private:
  df::TextBox *m_p_text_box;
  std::string m_name;
 public:
  Input(std::string name, df::TextBox *p_text_box);
  void callback() override;
};
#endif