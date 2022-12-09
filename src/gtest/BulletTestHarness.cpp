#include <limits.h>
#include <math.h>
#include "gtest/gtest.h"

#include "BulletTestHarness.h"
#include "Bullet.h"
#include "BulletClient.h"
#include "Player.h"
#include "PlayerClient.h"
#include "TextureManager.h"
#include "Maths.h"
#include "Colors.h"

#include "InputMemoryBitStream.h"
#include "OutputMemoryBitStream.h"

#include <iostream>
#include <fstream>
#include <thread>

/* Reference: http://www.yolinux.com/TUTORIALS/Cbp-GoogleTest.html */

BulletTestHarness::BulletTestHarness()
{
    bp = nullptr;
    pp = nullptr;
}

BulletTestHarness::~BulletTestHarness()
{
    bp.reset();
    pp.reset();
}

void BulletTestHarness::SetUp()
{
    GameObject*	go1 = Bullet::StaticCreate();
    GameObject* go = Player::StaticCreate();

    Bullet* b2 = static_cast<Bullet*>(go1);
    Player* p = static_cast<Player*>(go);

    this->bp.reset(b2);
    this->pp.reset(p);
}

void BulletTestHarness::TearDown()
{
    this->bp.reset();
    this->bp = nullptr;

    this->pp.reset();
    this->pp = nullptr;
}

TEST_F(BulletTestHarness,constructor_noArgs)
{
  // Check defaults are set
  EXPECT_TRUE(Maths::Is3DVectorEqual(bp->GetLocation(), Vector3::Zero));
  // Checking this one is important since the radius is different for each objects
  EXPECT_FLOAT_EQ(bp->GetCollisionRadius(), 0.5f);
  EXPECT_EQ(bp->GetIndexInWorld(), -1);
  EXPECT_EQ(bp->GetNetworkId(), 0);

  EXPECT_TRUE(Maths::Is3DVectorEqual(bp->GetVelocity(), Vector3::Zero));
  //EXPECT_EQ(bp->GetBulletId(), 0.0f);

  //Initial state is update all
  int check = 0x0003; //Hex - binary 00000000 00000000 00000000 00001111
  EXPECT_EQ(bp->GetAllStateMask(), check);

  //Check our macro has worked.
  EXPECT_EQ(bp->GetClassId(), 'BULT');
  EXPECT_NE(bp->GetClassId(), 'HELP');

  // Added some getters so I could check these - not an easy class to test.
  EXPECT_EQ(bp->GetHealth(), 1);
}


/* Tests Omitted
* There's a good chunk of this which cannot be tested in this limited example,
* however there should be enough to underake some testing of the serialisation code.
*/

TEST_F(BulletTestHarness,EqualsOperator1)
{
  Bullet* a = static_cast<Bullet*>(Bullet::StaticCreate());
  Bullet* b = static_cast<Bullet*>(Bullet::StaticCreate());

  a->SetBulletId(10);
  b->SetBulletId(10);

  EXPECT_TRUE(*a == *b);
}

TEST_F(BulletTestHarness,EqualsOperator2)
{
  Bullet *a = static_cast<Bullet*>(Bullet::StaticCreate());
  Bullet *b = static_cast<Bullet*>(Bullet::StaticCreate());

  a->SetBulletId(10);
  b->SetBulletId(1);

  EXPECT_FALSE(*a == *b);
}

TEST_F(BulletTestHarness,EqualsOperator3)
{
    Bullet* a = static_cast<Bullet*>(Bullet::StaticCreate());
    Bullet* b = static_cast<Bullet*>(Bullet::StaticCreate());
    Vector3 c = { 1,1,1 };

  a->SetBulletId(10);
  b->SetBulletId(10);

  a->SetVelocity(c);

  EXPECT_FALSE(*a == *b);
}

TEST_F(BulletTestHarness,EqualsOperator4)
{
  BulletPtr b(static_cast<Bullet*>(Bullet::StaticCreate()));

  bp->SetBulletId(10);
  b->SetBulletId(10);

  EXPECT_TRUE(*bp == *b);
}

TEST_F(BulletTestHarness, InitFromShouter)
{
    BulletPtr b(static_cast<Bullet*>(Bullet::StaticCreate()));
    Player* p(static_cast<Player*>(Player::StaticCreate()));

    b->InitFromShooter(p);

    EXPECT_FALSE(Maths::Is3DVectorEqual(b->GetLocation(), Vector3::Zero));
}

TEST_F(BulletTestHarness, Update)
{
    BulletPtr b(static_cast<Bullet*>(Bullet::StaticCreate()));

    b->Update();

    EXPECT_FALSE(Maths::Is3DVectorEqual(b->GetLocation(), Vector3::Zero));
}

TEST_F(BulletTestHarness, SimulateMovement)
{
    BulletPtr b(static_cast<Bullet*>(Bullet::StaticCreate()));
    Vector3 c = { 1,1,1 };
    float d = 10.0f;

    b->SetLocation(c);

    b->SimulateMovement(d);

    EXPECT_FALSE(Maths::Is3DVectorEqual(b->GetLocation(), Vector3::Zero));
}

TEST_F(BulletTestHarness, ProcessCollisions1)
{
    BulletPtr b(static_cast<Bullet*>(Bullet::StaticCreate()));

    b->ProcessCollisions();

    EXPECT_TRUE(Maths::Is3DVectorEqual(b->GetLocation(), Vector3::Zero));
}

TEST_F(BulletTestHarness, ProcessCollisions2)
{
    BulletPtr b(static_cast<Bullet*>(Bullet::StaticCreate()));
    Vector3 c = { 100,100,100 };

    b->SetLocation(c);

    EXPECT_FALSE(b->DoesWantToDie());

    b->ProcessCollisions();

    EXPECT_TRUE(b->DoesWantToDie());
}
/* Serialistion tests in MemoryBitStreamTestHarness */