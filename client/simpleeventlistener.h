#ifndef SIMPLE_EVENT_LISTENER_H
#define SIMPLE_EVENT_LISTENER_H

#include "./eventlistener.h"

class SimpleEventListener: public EventListener {
public:
    SimpleEventListener();

    void matchUpdated(const MatchDto& state) override;
    void matchFinished(const MatchDto& final_info) override;
    // virtual void matchCanceled(const MatchDto& final_info) = 0;

    ~SimpleEventListener();
};

#endif
