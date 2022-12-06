#ifndef GAME_OBJECT_TEST_REGISTRY_HARNESS_H_
#define GAME_OBJECT_TEST_REGISTRY_HARNESS_H_

#include <limits.h>
#include <gtest/gtest.h>

#include "GameObjectRegistry.h"


class GameObjectRegistryTestHarness : public ::testing::Test
{
protected:

  virtual void SetUp();
  virtual void TearDown();

  // No test object here - its a Singleton.

  GameObjectPtr go;
public:

    GameObjectRegistryTestHarness();
    virtual ~GameObjectRegistryTestHarness();
};

#endif // GAME_OBJECT_TEST_REGISTRY_HARNESS_H_
