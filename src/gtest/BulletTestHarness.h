#ifndef BULLET_TESTHARNESS_H_
#define BULLET_TESTHARNESS_H_

#include <limits.h>
#include <gtest/gtest.h>

#include "Bullet.h"
#include "Player.h"

class BulletTestHarness : public ::testing::Test
{
protected:

  virtual void SetUp();
  virtual void TearDown();

  PlayerPtr pp;
  BulletPtr bp;

public:

    BulletTestHarness();
    virtual ~BulletTestHarness();
};

#endif // BULLET_TESTHARNESS_H_
