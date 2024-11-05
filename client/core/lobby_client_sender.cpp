#include "./lobby_client_sender.h"


LobbyClientSender::LobbyClientSender() {}

void LobbyClientSender::close() { actions.close(); }

void LobbyClientSender::doaction(const lobby_action& action) { actions.push(action); }


lobby_action LobbyClientSender::popaction() { return actions.pop(); }

void LobbyClientSender::notifyStart() {
    lobby_action action(PLAYER_READY, 0);
    actions.push(action);
}
