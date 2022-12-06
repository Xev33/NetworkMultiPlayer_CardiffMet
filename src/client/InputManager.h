
#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "Move.h"
#include "InputManager.h"
#include "InputState.h"
#include "InputAction.h"
#include "MoveList.h"

#include <memory>
using std::unique_ptr;

class InputManager
{
public:


	static void StaticInit();
	static unique_ptr< InputManager >	sInstance;

	void HandleInput( EInputAction inInputAction, int inKeyCode );

	const InputState& GetState()	const	{ return mCurrentState; }

	MoveList&			GetMoveList()		{ return mMoveList; }

	const Move*			GetAndClearPendingMove()	{ auto toRet = mPendingMove; mPendingMove = nullptr; return toRet; }

	void				Update();

private:

	InputState							mCurrentState;

	InputManager();

	bool				IsTimeToSampleInput();
	const Move&			SampleInputAsMove();

	MoveList		mMoveList;
	float			mNextTimeToSampleInput;
	const Move*		mPendingMove;
};

#endif
