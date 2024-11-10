#include "./lobby_action_queue.h"


LobbyActionQueue::LobbyActionQueue() {}

void LobbyActionQueue::close() { actions.close(); }

void LobbyActionQueue::doaction(const lobby_action& action) { actions.push(action); }


lobby_action LobbyActionQueue::popaction() { return actions.pop(); }

void LobbyActionQueue::notifyStart() {
    lobby_action action(PLAYER_READY, 0);
    actions.push(action);
}
