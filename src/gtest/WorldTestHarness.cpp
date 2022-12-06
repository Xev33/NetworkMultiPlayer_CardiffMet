#include <limits.h>
#include <math.h>
#include "gtest/gtest.h"

#include "WorldTestHarness.h"
#include "GameObjectRegistry.h"
#include "GameObject.h"
#include "Player.h"
#include "World.h"
#include "Colors.h"
#include "Maths.h"

#include <iostream>
#include <fstream>
#include <thread>

/* Reference: http://www.yolinux.com/TUTORIALS/Cpp-GoogleTest.html */

WorldTestHarness::WorldTestHarness()
{

}

WorldTestHarness::~WorldTestHarness()
{
  // Don't need to destruct, rely on the destructor of unordered_map
  // destroying all elments when it goes out of scope.
}

void WorldTestHarness::SetUp()
{
    GameObjectRegistry::StaticInit();
    World::StaticInit();
    GameObjectRegistry::sInstance->RegisterCreationFunction('PLYR', &Player::StaticCreatePtr);
}

void WorldTestHarness::TearDown()
{
  // Don't need to destruct, rely on the destructor of unordered_map
  // destroying all elments when it goes out of scope.

}

TEST_F(WorldTestHarness,TestWorldAddGameObject)
{
    go = Player::StaticCreatePtr();

    EXPECT_NE(go, nullptr);

    World::sInstance->AddGameObject(go);

    EXPECT_EQ(World::sInstance->GetGameObjectCount(),1);

    // Two objects have reference to this GameObject
    // 1. The test harness (go)
    // 2. The World (list of all game objects)
    EXPECT_EQ(go.use_count(),2);

    EXPECT_EQ(go->GetClassId(), 'PLYR');

    //no need to destroy, when the temp goes out of scope
    //the reference count will drop to zero and the
    //memory will be destroyed.
}


TEST_F(WorldTestHarness,TestWorldAddAnotherGameObject)
{
    go = Player::StaticCreatePtr();

    World::sInstance->AddGameObject(go);

    EXPECT_EQ(World::sInstance->GetGameObjectCount(),1);

    GameObjectPtr another = Player::StaticCreatePtr();

    World::sInstance->AddGameObject(another);

    EXPECT_EQ(World::sInstance->GetGameObjectCount(),2);
}

TEST_F(WorldTestHarness,TestPlayerObjectSetup)
{
    go = Player::StaticCreatePtr();

    World::sInstance->AddGameObject(go);

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


TEST_F(WorldTestHarness,TestWorldRemoveGameObject)
{
    go = Player::StaticCreatePtr();

    World::sInstance->AddGameObject(go);

    EXPECT_EQ(World::sInstance->GetGameObjectCount(),1);

    GameObjectPtr another = Player::StaticCreatePtr();

    World::sInstance->AddGameObject(another);

    EXPECT_EQ(World::sInstance->GetGameObjectCount(),2);

    World::sInstance->RemoveGameObject(go);

    EXPECT_EQ(World::sInstance->GetGameObjectCount(),1);

    std::vector< GameObjectPtr >::const_iterator it;
    //Note GetGameObjets returns a const ref.
    it = (World::sInstance->GetGameObjects()).begin();
    GameObjectPtr remaining = *it;

    /* RemoveGameObject re-indexes the objects, so the remaining object always has an index of 0 */
    EXPECT_EQ(remaining->GetIndexInWorld(),0);
}

TEST_F(WorldTestHarness,TestWorldRemoveGameObject2)
{
    go = Player::StaticCreatePtr();

    World::sInstance->AddGameObject(go);

    EXPECT_EQ(World::sInstance->GetGameObjectCount(),1);

    GameObjectPtr another = Player::StaticCreatePtr();

    World::sInstance->AddGameObject(another);

    EXPECT_EQ(World::sInstance->GetGameObjectCount(),2);

    GameObjectPtr justOneMore = Player::StaticCreatePtr();

    World::sInstance->AddGameObject(justOneMore);

    EXPECT_EQ(World::sInstance->GetGameObjectCount(),3);

    World::sInstance->RemoveGameObject(another);

    EXPECT_EQ(World::sInstance->GetGameObjectCount(),2);

    std::vector< GameObjectPtr >::const_iterator it;
    //Note GetGameObjets returns a const ref.
    it = (World::sInstance->GetGameObjects()).begin();
    GameObjectPtr remaining = *it;

    EXPECT_EQ(remaining->GetIndexInWorld(),0);

    ++it;
    remaining = *it;
    EXPECT_EQ(remaining->GetIndexInWorld(),1);
}
