#ifndef GAME_OBJECT_TESTHARNESS_H_
#define GAME_OBJECT_TESTHARNESS_H_

#include <limits.h>
#include <gtest/gtest.h>

#include "GameObject.h"


class GameObjectTestHarness : public ::testing::Test
{
protected:

  virtual void SetUp();
  virtual void TearDown();

  GameObjectPtr go;

public:

    GameObjectTestHarness();
    virtual ~GameObjectTestHarness();
};

#endif // GAME_OBJECT_TESTHARNESS_H_
