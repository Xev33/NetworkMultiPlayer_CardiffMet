#include <limits.h>
#include <math.h>
#include "gtest/gtest.h"

#include "PlayerTestHarness.h"
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

/* Reference: http://www.yolinux.com/TUTORIALS/Cpp-GoogleTest.html */

PlayerTestHarness::PlayerTestHarness()
{
  pp = nullptr;
}

PlayerTestHarness::~PlayerTestHarness()
{
  pp.reset();
}

void PlayerTestHarness::SetUp()
{
    GameObject*	go = Player::StaticCreate();
    Player* p = static_cast<Player*>(go);
    this->pp.reset(p);
}

void PlayerTestHarness::TearDown()
{
    this->pp.reset();
    this->pp = nullptr;
}

TEST_F(PlayerTestHarness,constructor_noArgs)
{
  // Check defaults are set
  // Should be no need to do these as they were tested with the base class.
  EXPECT_TRUE(Maths::Is3DVectorEqual(pp->GetColor(), Colors::White));
  EXPECT_TRUE(Maths::Is3DVectorEqual(pp->GetLocation(), Vector3::Zero));
  EXPECT_FLOAT_EQ(pp->GetCollisionRadius(), 0.5f);
  EXPECT_FLOAT_EQ(pp->GetScale(),1.0f);
  EXPECT_FLOAT_EQ(pp->GetRotation(),0.0f);
  EXPECT_EQ(pp->GetIndexInWorld(), -1);
  EXPECT_EQ(pp->GetNetworkId(), 0);

  EXPECT_TRUE(Maths::Is3DVectorEqual(pp->GetVelocity(), Vector3::Zero));
  EXPECT_EQ(pp->GetPlayerId(), 0.0f);

  //Initial state is update all
  int check = 0x000F; //Hex - binary 00000000 00000000 00000000 00001111
  EXPECT_EQ(pp->GetAllStateMask(), check);

  //Check our macro has worked.
  EXPECT_EQ(pp->GetClassId(), 'PLYR');
  EXPECT_NE(pp->GetClassId(), 'HELP');

  //Added some getters so I could check these - not an easy class to test.
  EXPECT_FLOAT_EQ(pp->GetMaxLinearSpeed(),  50.0f);
  EXPECT_FLOAT_EQ(pp->GetMaxRotationSpeed(), 5.0f);
  EXPECT_FLOAT_EQ(pp->GetWallRestitution(), 0.1f);
  EXPECT_FLOAT_EQ(pp->GetNPCRestitution(), 0.1f);
  EXPECT_FLOAT_EQ(pp->GetLastMoveTimestamp(), 0.0f);
  EXPECT_FLOAT_EQ(pp->GetThrustDir(), 0.0f);
  EXPECT_EQ(pp->GetHealth(), 10);
  EXPECT_FALSE(pp->IsShooting());
}


/* Tests Omitted
* There's a good chunk of this which cannot be tested in this limited example,
* however there should be enough to underake some testing of the serialisation code.
*/

TEST_F(PlayerTestHarness,EqualsOperator1)
{ /* Won't compile - why?
  Player a ();
  Player b ();

  a.SetPlayerId(10);
  b.SetPlayerId(10);

  EXPECT_TRUE(a == b);*/
}

TEST_F(PlayerTestHarness,EqualsOperator2)
{
  Player *a = static_cast<Player*>(Player::StaticCreate());
  Player *b = static_cast<Player*>(Player::StaticCreate());

  a->SetPlayerId(10);
  b->SetPlayerId(10);

  EXPECT_TRUE(*a == *b);
}

/* Need more tests here */

TEST_F(PlayerTestHarness,EqualsOperator3)
{
  Player *a = static_cast<Player*>(Player::StaticCreate());
  Player *b = static_cast<Player*>(Player::StaticCreate());

  a->SetPlayerId(10);
  b->SetPlayerId(30);

  EXPECT_FALSE(*a == *b);
}

TEST_F(PlayerTestHarness,EqualsOperator4)
{
  PlayerPtr b(static_cast<Player*>(Player::StaticCreate()));

  pp->SetPlayerId(10);
  b->SetPlayerId(10);

  EXPECT_TRUE(*pp == *b);
}

/* Serialistion tests in MemoryBitStreamTestHarness */