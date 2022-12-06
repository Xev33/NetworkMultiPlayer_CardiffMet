#include <limits.h>
#include <math.h>
#include "gtest/gtest.h"

#include "GameObjectRegistryTestHarness.h"
#include "GameObject.h"
#include "Player.h"
#include "World.h"
#include "Colors.h"
#include "Maths.h"

#include <iostream>
#include <fstream>
#include <thread>

/* Reference: http://www.yolinux.com/TUTORIALS/Cpp-GoogleTest.html */

GameObjectRegistryTestHarness::GameObjectRegistryTestHarness()
{

}

GameObjectRegistryTestHarness::~GameObjectRegistryTestHarness()
{
  // Don't need to destruct, rely on the destructor of unordered_map
  // destroying all elments when it goes out of scope.
}

void GameObjectRegistryTestHarness::SetUp()
{
    GameObjectRegistry::StaticInit();
    World::StaticInit();
    GameObjectRegistry::sInstance->RegisterCreationFunction('PLYR', &Player::StaticCreatePtr);
}

void GameObjectRegistryTestHarness::TearDown()
{
  // Don't need to destruct, rely on the destructor of unordered_map
  // destroying all elments when it goes out of scope.

}

TEST_F(GameObjectRegistryTestHarness,TestPlayerObjectCreation)
{
    go = GameObjectRegistry::sInstance->CreateGameObject('PLYR');

    EXPECT_NE(go, nullptr);

    // Two objects have reference to this GameObject
    // 1. The test harness (go)
    // 2. The World (list of all game objects)
    EXPECT_EQ(go.use_count(),2);

    EXPECT_EQ(go->GetClassId(), 'PLYR');

    //no need to destroy, when the temp goes out of scope
    //the reference count will drop to zero and the
    //memory will be destroyed.
}


TEST_F(GameObjectRegistryTestHarness,TestRegistryWorldLink)
{
    go = GameObjectRegistry::sInstance->CreateGameObject('PLYR');

    EXPECT_EQ(go->GetIndexInWorld(), 0);

    GameObjectPtr another = GameObjectRegistry::sInstance->CreateGameObject('PLYR');

    EXPECT_EQ(another->GetIndexInWorld(),1);
}

TEST_F(GameObjectRegistryTestHarness,TestPlayerObjectSetup)
{
    go = GameObjectRegistry::sInstance->CreateGameObject('PLYR');

    //https://stackoverflow.com/questions/1358143/downcasting-shared-ptrbase-to-shared-ptrderived
    //std::shared_ptr<Derived> derived =
    //           std::dynamic_pointer_cast<Derived> (base);
    PlayerPtr pp = std::dynamic_pointer_cast<Player>(go);

    // Check defaults are set
    // Should be no need to do these as they were tested with the base class.
    EXPECT_TRUE(Maths::Is3DVectorEqual(pp->GetColor(), Colors::White));
    EXPECT_TRUE(Maths::Is3DVectorEqual(pp->GetLocation(), Vector3::Zero));
    EXPECT_FLOAT_EQ(pp->GetCollisionRadius(), 0.5f);
    EXPECT_FLOAT_EQ(pp->GetScale(),1.0f);
    EXPECT_FLOAT_EQ(pp->GetRotation(),0.0f);

    //NOTE: This has been added to the world so its world index should be valid.
    EXPECT_EQ(pp->GetIndexInWorld(), 0);
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

TEST_F(GameObjectRegistryTestHarness,TestUnknownObjectCreation)
{
    EXPECT_THROW(go = GameObjectRegistry::sInstance->CreateGameObject('FISH'), UnknownGameObjectType);
}
