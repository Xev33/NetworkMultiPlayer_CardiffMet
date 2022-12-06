#ifndef PLAYER_TESTHARNESS_H_
#define PLAYER_TESTHARNESS_H_

#include <limits.h>
#include <gtest/gtest.h>

#include "Player.h"

class PlayerTestHarness : public ::testing::Test
{
protected:

  virtual void SetUp();
  virtual void TearDown();

  PlayerPtr pp;

public:

    PlayerTestHarness();
    virtual ~PlayerTestHarness();
};

#endif // PLAYER_TESTHARNESS_H_
