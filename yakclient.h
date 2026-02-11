#ifndef YAKCLIENT_H
#define YAKCLIENT_H

#include "Object.h"
#include "TextBox.h"
#include "Event.h"

class yakclient : public df::Object {
 private:
    df::TextBox *m_p_text_box;
    void handleMessage();
 public:
    yakclient(df::TextBox *p_box);
    ~yakclient();
    int eventHandler(const df::Event *p_e) override;
};
#endif