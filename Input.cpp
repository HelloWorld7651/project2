#include "Input.h"
#include "NetworkManager.h"
#include "LogManager.h"
#include "GameManager.h"

enum class MessageType { UNDEFINED = -1, EXIT, CHAT };
struct PacketHeader { int size; MessageType type; };

Input::Input(std::string name, df::TextBox *p_box) {
    setType("Input");
    setText("");
    setBorder(true);
    setColor(df::WHITE);
    setLocation(df::BOTTOM_CENTER);
    setLimit(40);
    m_p_text_box = p_box;
    m_name = name + ": ";
    setViewString(m_name);
}

void Input::callback() {
    if (getText().empty()) return;
    if (getText() == "quit") df::GM.setGameOver();

    std::string msg = m_name + getText() + "\n";
    
    PacketHeader head;
    head.type = MessageType::CHAT;
    head.size = sizeof(head) + msg.length() + 1;
    
    NM.send(&head, sizeof(head));
    NM.send(msg.c_str(), msg.length() + 1);

    m_p_text_box->addText(msg);
    clearText();
}