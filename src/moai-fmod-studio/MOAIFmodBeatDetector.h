// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAIFMODBEATDETECTOR_H
#define	MOAIFMODBEATDETECTOR_H

#include <moai-sim/headers.h>
#include <fmod.h>

class MOAIFmodBeat;

//================================================================//
// MOAIFmodBeatDetector
//================================================================//
/**	@name	MOAIFmodBeatDetector
	@text	FMOD singleton.
*/
class MOAIFmodBeatDetector :
	public virtual MOAINode,
	public MOAIAction {
private:
	
	static const u32		DEFAULT_FFT_WINDOW = 1024;
	static const float		HISTORY_FILTER = 0.02f;
	
	ZLLeanArray < MOAIFmodBeat > mBeats;
	
	FMOD_DSP*		mDsp;
	u32				mFftWindow;
	
	
	//----------------------------------------------------------------//
	static int		_attachToChannel		( lua_State* L );
	static int		_reserve				( lua_State* L );
	static int		_setBand				( lua_State* L );

	//----------------------------------------------------------------//
	bool			IsDone					();
	void			OnStart					();
	void			OnStop					();
	void			OnUpdate				( double step );

public:

	DECL_LUA_FACTORY ( MOAIFmodBeatDetector )
	DECL_ATTR_HELPER ( MOAIFmodBeatDetector )
	
	enum {
		ATTR_KICK = 0,
		ATTR_SNARE,
		ATTR_HAT,
		TOTAL_ATTR
	};
	
	enum {
		EVENT_BEAT = MOAIAction::TOTAL_EVENTS,
		TOTAL_EVENTS,
	};
	
	//----------------------------------------------------------------//
	bool			ApplyAttrOp				( u32 attrID, MOAIAttrOp& attrOp, u32 op );
	void			DetectBeats				( double step );
					MOAIFmodBeatDetector	();
					~MOAIFmodBeatDetector	();
	void			OnBeat					( int idx );
	void			RegisterLuaClass		( MOAILuaState& L );
	void			RegisterLuaFuncs		( MOAILuaState& L );
	void			SmoothFftBuffer			();
	void			UpdateFFT				();
	
};

//================================================================//
// MOAIFmodBeat
//================================================================//
class MOAIFmodBeat {
public:
	u32		mBandWidth;
	
	float	mAverageEnergy;
	float	mEnergyVariance;
	float	mInstantEnergy;
	
	float	mDelay;
	float	mElapsed;
	float	mPrevious;
	float	mPower;
	
	//----------------------------------------------------------------//
	bool	IsBeat			();
			MOAIFmodBeat	();
	void	Update			( double step );
};

#endif
