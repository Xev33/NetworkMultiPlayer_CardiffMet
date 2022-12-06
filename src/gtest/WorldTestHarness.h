#ifndef WORLD_TEST_REGISTRY_HARNESS_H_
#define WORLD_TEST_REGISTRY_HARNESS_H_

#include <limits.h>
#include <gtest/gtest.h>

#include "World.h"


class WorldTestHarness : public ::testing::Test
{
protected:

  virtual void SetUp();
  virtual void TearDown();

  // No test object here - its a Singleton.

  GameObjectPtr go;
public:

    WorldTestHarness();
    virtual ~WorldTestHarness();
};

#endif // WORLD_TEST_REGISTRY_HARNESS_H_
