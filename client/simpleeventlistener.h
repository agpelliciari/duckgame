#ifndef SIMPLE_EVENT_LISTENER_H
#define SIMPLE_EVENT_LISTENER_H

//#include <atomic>
#include "./eventlistener.h"
#include "common/queue.h"
class SimpleEventListener: public EventListener {
private:
    Queue<MatchDto> updates;

public:
    SimpleEventListener();

    void matchUpdated(const MatchDto& state) override;
    void matchFinished(const MatchDto& final_info) override;
    // virtual void matchCanceled(const MatchDto& final_info) = 0;

    bool try_update(MatchDto& last_update);
    bool isclosed();
    void disconnect();

    ~SimpleEventListener();
};

#endif
