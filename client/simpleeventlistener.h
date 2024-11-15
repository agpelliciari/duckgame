#ifndef SIMPLE_EVENT_LISTENER_H
#define SIMPLE_EVENT_LISTENER_H

//#include <atomic>
#include "./eventlistener.h"
#include "common/queue.h"
class SimpleEventListener: public EventListener {
private:
    Queue<MatchDto> updates;
    Queue<MatchStatsInfo> updates_stats;
public:
    SimpleEventListener();

    void matchUpdated(const MatchDto& state) override;
    void statsUpdated(const MatchStatsInfo& stats_update) override;
    // virtual void matchCanceled(const MatchDto& final_info) = 0;

    bool try_update(MatchDto& last_update);
    bool update_stats(MatchStatsInfo& last_update);
    bool isclosed();
    void disconnect();

    ~SimpleEventListener();
};

#endif
