#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#define CLASS_IDENTIFICATION( inCode, inClass ) \
enum { kClassId = inCode }; \
virtual uint32_t GetClassId() const { return kClassId; } \
static GameObject* CreateInstance() { return static_cast< GameObject* >( new inClass() ); } \

#include <cstdint>
#include <memory>
using std::shared_ptr;

#include "Vector3.h"

class InputMemoryBitStream;
class OutputMemoryBitStream;

/* Note:
*  This is a cut down version of that provided in the course text,
*  simplified to allow the creation of a MWE in the tutorial.
*/

class Player;

class GameObject
{
public:

	CLASS_IDENTIFICATION( 'GOBJ', GameObject )

	GameObject();
	virtual ~GameObject() {}

	virtual uint32_t GetAllStateMask()	const { return 0; }

	virtual void	Update();

	virtual void	HandleDying() {}

	void	SetIndexInWorld( int inIndex )						{ mIndexInWorld = inIndex; }
	int		GetIndexInWorld()				const				{ return mIndexInWorld; }

	void	SetRotation( float inRotation );
	float	GetRotation()					const				{ return mRotation; }

	void	SetScale( float inScale )							{ mScale = inScale; }
	float	GetScale()						const				{ return mScale; }


	const Vector3&		GetLocation()				const				{ return mLocation; }
	void		SetLocation( const Vector3& inLocation )		{ mLocation = inLocation; }

	float		GetCollisionRadius()		const				{ return mCollisionRadius; }
	void		SetCollisionRadius( float inRadius )			{ mCollisionRadius = inRadius; }

	Vector3		GetForwardVector()			const;
	Vector3		GetRightVector()			const;

	virtual bool	HandleCollisionWithPlayer(Player* inPlayer) { (void)inPlayer; return true; }
	virtual bool	OnCollisionEnter( GameObject* colObj) { ( void ) colObj; return true; }

	void		SetColor( const Vector3& inColor )					{ mColor = inColor; }
	const Vector3&		GetColor()					const				{ return mColor; }

	bool		DoesWantToDie()				const				{ return mDoesWantToDie; }
	void		SetDoesWantToDie( bool inWants )				{ mDoesWantToDie = inWants; }

	int			GetNetworkId()				const				{ return mNetworkId; }
	void		SetNetworkId( int inNetworkId );

	virtual uint32_t	Write( OutputMemoryBitStream& inOutputStream, uint32_t inDirtyState ) const	{  ( void ) inOutputStream; ( void ) inDirtyState; return 0; }
	virtual void		Read( InputMemoryBitStream& inInputStream )	{ ( void ) inInputStream; }

	bool operator==(GameObject& other);

private:

	Vector3											mLocation;
	Vector3											mColor;

	float											mCollisionRadius;

	float											mRotation;
	float											mScale;
	int												mIndexInWorld;

	bool											mDoesWantToDie;

	int												mNetworkId;
};

typedef shared_ptr< GameObject >	GameObjectPtr;

#endif // GAME_OBJECT_H_
