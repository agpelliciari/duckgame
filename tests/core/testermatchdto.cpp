#include "./testermatchdto.h"

#include "gtest/gtest.h"

TesterMatchDTO::TesterMatchDTO(const MatchDto& firstUpdate): curr_state(firstUpdate) {}

TesterMatchDTO::TesterMatchDTO(const MatchDto&& firstUpdate): curr_state(firstUpdate) {}


MatchDto TesterMatchDTO::getState() const { return curr_state; }


void TesterMatchDTO::assertPlayerAreEq(const PlayerDTO& expected, const PlayerDTO& given) {
    ASSERT_EQ(given.id, expected.id) << "Players id are the same";
    ASSERT_EQ(given.pos.x, expected.pos.x) << "Players x are the same";
    ASSERT_EQ(given.pos.y, expected.pos.y) << "Players y are the same";
    ASSERT_EQ(given.weapon, expected.weapon) << "Players weapon are the same";
    ASSERT_EQ(given.move_action, expected.move_action) << "Players move_action are the same";
    ASSERT_EQ(given.doing_action, expected.doing_action) << "Players doing_action are the same";
    ASSERT_EQ(given.is_alive, expected.is_alive) << "Players is alive are the same";
    ASSERT_EQ(given.helmet, expected.helmet) << "Players helmet are the same";
    ASSERT_EQ(given.chest_armor, expected.chest_armor) << "Players chest armor are the same";
    ASSERT_EQ(given.aiming_up, expected.aiming_up) << "Players aiming up are the same";
}


void TesterMatchDTO::assertPlayerEquals(int pos, const PlayerDTO& expected) {
    assertPlayerAreEq(expected, curr_state.players[pos]);
}


void TesterMatchDTO::assertEquals(const MatchDto& expected) {
    //ASSERT_EQ(curr_state.info.estado, expected.info.estado) << "State is the same";
    //ASSERT_EQ(curr_state.info.numronda, expected.info.numronda)
    //        << "State round number are the same";

    ASSERT_EQ(curr_state.players.size(), expected.players.size()) << "Player counts are the same";

    int ind = 0;
    for (const PlayerDTO& playerExpected: expected.players) {
        assertPlayerEquals(ind, playerExpected);
        ind++;
    }
}
