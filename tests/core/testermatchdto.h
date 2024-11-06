#ifndef TESTER_MATCH_DTO
#define TESTER_MATCH_DTO

#include "common/dtosgame.h"

class TesterMatchDTO {
protected:
    MatchDto curr_state;

    void assertPlayerAreEq(const PlayerDTO& expected, const PlayerDTO& given);

public:
    explicit TesterMatchDTO(const MatchDto& firstUpdate);
    explicit TesterMatchDTO(const MatchDto&& firstUpdate);

    // Save a state for reference. To compare after.
    MatchDto getState() const;


    // Asserting
    void assertPlayerEquals(int pos, const PlayerDTO& expected);
    void assertEquals(const MatchDto& expected);
};

#endif
