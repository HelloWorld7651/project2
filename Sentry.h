#ifndef SENTRY_H
#define SENTRY_H

#include "Object.h"

namespace df {

class Sentry : public Object {
 private:
    void handleStep();

 public:
    Sentry();
    int eventHandler(const Event *p_e) override;
};

} // end namespace df
#endif