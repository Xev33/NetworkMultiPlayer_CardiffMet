#include <limits.h>
#include <math.h>
#include "gtest/gtest.h"

#include "GameObjectTestHarness.h"
#include "GameObject.h"
#include "Colors.h"
#include "Maths.h"

#include <iostream>
#include <fstream>
#include <thread>

/* Reference: http://www.yolinux.com/TUTORIALS/Cpp-GoogleTest.html */

GameObjectTestHarness::GameObjectTestHarness()
{
  go = nullptr;
}

GameObjectTestHarness::~GameObjectTestHarness()
{
  go.reset();
}

void GameObjectTestHarness::SetUp()
{
    this->go.reset(new GameObject());
}

void GameObjectTestHarness::TearDown()
{
    this->go.reset();
    this->go = nullptr;
}

TEST_F(GameObjectTestHarness,constructor_noArgs)
{
    // Check defaults are set
  EXPECT_TRUE(Maths::Is3DVectorEqual(go->GetColor(), Colors::White));
  EXPECT_TRUE(Maths::Is3DVectorEqual(go->GetLocation(), Vector3::Zero));
  EXPECT_FLOAT_EQ(go->GetCollisionRadius(), 0.5f);
  EXPECT_FLOAT_EQ(go->GetScale(),1.0f);
  EXPECT_FLOAT_EQ(go->GetRotation(),0.0f);
  EXPECT_EQ(go->GetIndexInWorld(), -1);
  EXPECT_EQ(go->GetNetworkId(), 0);

  //Check our macro has worked.
  EXPECT_EQ(go->GetClassId(), 'GOBJ');
  EXPECT_NE(go->GetClassId(), 'HELP');
}

TEST_F(GameObjectTestHarness,GetAllStateMask)
{
  EXPECT_EQ(go->GetAllStateMask(), 0);
}

TEST_F(GameObjectTestHarness,IndexInWorld)
{
  int testValue = 20;

  //Check default before we set.
  EXPECT_EQ(go->GetIndexInWorld(), -1);

  // Set the value.
  go->SetIndexInWorld(testValue);

  //Check its been set.
  EXPECT_EQ(go->GetIndexInWorld(), testValue);
}

TEST_F(GameObjectTestHarness,Rotation)
{
  float testValue = 2.0 * Maths::PI;

  //Check default before we set.
  EXPECT_FLOAT_EQ(go->GetRotation(), 0.0f);

  // Set the value.
  go->SetRotation(testValue);

  //Check its been set.
  EXPECT_FLOAT_EQ(go->GetRotation(), testValue);
}

TEST_F(GameObjectTestHarness,Scale)
{
  float testValue = 2.0f;

  //Check default before we set.
  EXPECT_FLOAT_EQ(go->GetScale(), 1.0f);

  // Set the value.
  go->SetScale(testValue);

  //Check its been set.
  EXPECT_FLOAT_EQ(go->GetScale(), testValue);
}

TEST_F(GameObjectTestHarness,Location)
{
  Vector3 testValue(1.1f, 2.2f, 3.3f);

  //Check default before we set.
  EXPECT_TRUE(Maths::Is3DVectorEqual(go->GetLocation(), Vector3::Zero));

  // Set the value.
  go->SetLocation(testValue);

  //Check its been set.
  EXPECT_TRUE(Maths::Is3DVectorEqual(go->GetLocation(), testValue));
}

TEST_F(GameObjectTestHarness,CollisionRadius)
{
  float testValue = 2.0f;

  //Check default before we set.
  EXPECT_FLOAT_EQ(go->GetCollisionRadius(), 0.5f);

  // Set the value.
  go->SetCollisionRadius(testValue);

  //Check its been set.
  EXPECT_FLOAT_EQ(go->GetCollisionRadius(), testValue);
}

TEST_F(GameObjectTestHarness,ForwardVector)
{
  // Game is 2D
  float rot = Maths::PI;
  Vector3 answer( sinf( rot ), -cosf( rot ), 0.f );

  go->SetRotation(Maths::PI);

  EXPECT_TRUE(Maths::Is3DVectorEqual(go->GetForwardVector(), answer));
}

TEST_F(GameObjectTestHarness,Color)
{
  //Check default before we set.
  EXPECT_TRUE(Maths::Is3DVectorEqual(go->GetColor(), Colors::White));

  // Set the value.
  go->SetColor(Colors::Black);

  //Check its been set.
  EXPECT_TRUE(Maths::Is3DVectorEqual(go->GetColor(), Colors::Black));
}

TEST_F(GameObjectTestHarness,WantsToDie)
{
  bool testValue = true;

  //Check default before we set.
  EXPECT_FALSE(go->DoesWantToDie());

  // Set the value.
  go->SetDoesWantToDie(testValue);

  //Check its been set.
  EXPECT_EQ(go->DoesWantToDie(), testValue);
}

TEST_F(GameObjectTestHarness,NetworkId)
{
  int testValue = 20;

  //Check default before we set.
  EXPECT_EQ(go->GetNetworkId(), 0);

  // Set the value.
  go->SetNetworkId(testValue);

  //Check its been set.
  EXPECT_EQ(go->GetNetworkId(), testValue);
}

TEST_F(GameObjectTestHarness,EqualsOperator1)
{ /* Won't compile - why?
  GameObject a ();
  GameObject b ();

  a.SetNetworkId(10);
  b.SetNetworkId(10);

  EXPECT_TRUE(a == b); */
}

TEST_F(GameObjectTestHarness,EqualsOperator2)
{
  GameObject *a = new GameObject();
  GameObject *b = new GameObject();

  a->SetNetworkId(10);
  b->SetNetworkId(10);

  EXPECT_TRUE(*a == *b);
}

TEST_F(GameObjectTestHarness,EqualsOperator3)
{
  GameObject *a = new GameObject();
  GameObject *b = new GameObject();

  a->SetNetworkId(10);
  b->SetNetworkId(30);

  EXPECT_FALSE(*a == *b);
}


TEST_F(GameObjectTestHarness,EqualsOperator4)
{
  GameObjectPtr b(new GameObject());

  go->SetNetworkId(10);
  b->SetNetworkId(10);

  EXPECT_TRUE(*go == *b);
}
