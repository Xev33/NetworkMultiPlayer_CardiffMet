#ifndef TIMING_H_
#define TIMING_H_

//For uint64_t
#include <cstdint>

class Timing
{
public:

	Timing();

	void Update();

	float GetDeltaTime() const { return mDeltaTime; }

	double GetTime() const;

	float GetTimef() const
	{
		return static_cast< float >( GetTime() );
	}

	float GetFrameStartTime() const { return mFrameStartTimef; }


	static Timing sInstance;

private:
	float		mDeltaTime;
	uint64_t	mDeltaTick;

	double		mLastFrameStartTime;
	float		mFrameStartTimef;
	double		mPerfCountDuration;

};

#endif  // TIMING_H_
