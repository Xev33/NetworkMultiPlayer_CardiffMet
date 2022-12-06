#include "GameObject.h"

#include "InputMemoryBitStream.h"
#include "OutputMemoryBitStream.h"

#include "Colors.h"
#include "Maths.h"

GameObject::GameObject() :
	mColor( Colors::White ),
	mCollisionRadius( 0.5f ),
	mRotation( 0.f ),
	mScale( 1.0f ),
	mIndexInWorld( -1 ),
	mDoesWantToDie( false ),
	mNetworkId( 0 )
{
}

void GameObject::Update()
{
	//object don't do anything by default...
}


Vector3 GameObject::GetForwardVector()	const
{
	//should we cache this when you turn?
	return Vector3( sinf( mRotation ), -cosf( mRotation ), 0.f );
}

Vector3 GameObject::GetRightVector()	const
{
	//should we cache this when you turn?
	return Vector3(sinf(mRotation + 90), -cosf(mRotation + 90), 0.f);
}

void GameObject::SetNetworkId( int inNetworkId )
{
	//this doesn't put you in the map or remove you from it
	mNetworkId = inNetworkId;

}

void GameObject::SetRotation( float inRotation )
{
	//should we normalize using fmodf?
	mRotation = inRotation;
}

bool GameObject::operator==(GameObject&  other)
{
	if(this->kClassId != other.kClassId) return false;
	if (!Maths::Is3DVectorEqual(this->mColor, other.mColor)) return false;
	if (!Maths::Is3DVectorEqual(this->mLocation, other.mLocation)) return false;
	if (!Maths::FP_EQUAL(this->mCollisionRadius, other.mCollisionRadius)) return false;
	if (!Maths::FP_EQUAL(this->mScale, other.mScale)) return false;
	if (!Maths::FP_EQUAL(this->mRotation, other.mRotation)) return false;
	if (this->mIndexInWorld != other.mIndexInWorld) return false;
	if (this->mNetworkId != other.mNetworkId) return false;
	if (this->mDoesWantToDie != other.mDoesWantToDie) return false;

	return true;
}
