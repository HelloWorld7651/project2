#ifndef YAKSERVER_H
#define YAKSERVER_H

#include "Object.h"
#include "Event.h"

class yakserver : public df::Object {
 private:
    void handleMessage(int index);

 public:
    yakserver();
    ~yakserver();
    int eventHandler(const df::Event *p_e) override;
};
#endif