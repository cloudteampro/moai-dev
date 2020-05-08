// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include <moai-fmod-studio/MOAIFmodBeatDetector.h>
#include <moai-fmod-studio/MOAIFmodStudio.h>
#include <moai-fmod-studio/MOAIFmodStudioChannel.h>
#include <fmod.h>
#include <fmod_errors.h>
#include <fmod_dsp.h>
#include <fmod_dsp_effects.h>


//================================================================//
// local
//================================================================//

//----------------------------------------------------------------//
/**	@name	attachToChannel
	@text	Initialize beat detector by attaching to channel output.

	@in		MOAIFmodBeatDetector 	self
	@in		MOAIFmodStudioChannel	channel
	@opt	number					fftWindow	FFT window size. Default is 1024
	@opt	number					delay		Delay the sound playback by `delay` seconds.
												This way beat detector is capable of capturing future events. 
	@out	nil
*/
int MOAIFmodBeatDetector::_attachToChannel ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIFmodBeatDetector, "U" )
	
	MOAIFmodStudioChannel* moaiChannel = state.GetLuaObject < MOAIFmodStudioChannel >( 2, true );
	
	self->mFftWindow = state.GetValue < u32 >( 3, DEFAULT_FFT_WINDOW );
	float delay	= state.GetValue < float >( 4, 0.0f );
	
	FMOD_SYSTEM* soundSys = MOAIFmodStudio::Get ().GetSoundSys ();
	FMOD_CHANNEL* channel = moaiChannel->GetFmodChannel ();
	
	if ( !channel ) {
		MOAILogF ( state, ZLLog::LOG_ERROR, "MOAIFmodBeatDetector: attach to channel failed; be sure to call attach after channel:play()" );
		return 0;
	}
	
	self->ReleaseDsp ();
	
	// DSP_TAIL is executed first, insert FFT before built-in panner and fader.
	// This way fft will work on raw sound data regardless of channel volume/pan/pitch values
	FMOD_DSP* dsp;
	MOAIFmodCheckError ( FMOD_System_CreateDSPByType ( soundSys, FMOD_DSP_TYPE_FFT, &dsp ));
	MOAIFmodCheckError ( FMOD_Channel_AddDSP ( channel, FMOD_CHANNELCONTROL_DSP_TAIL, dsp ));
	
	if ( delay != 0.0f ) {
		// DELAY should be added right after FFT, use index of the fft dsp it will be shifted to the next position.
		int index;
		FMOD_Channel_GetDSPIndex ( channel, dsp, &index );
		
		FMOD_DSP* delayDsp;
		MOAIFmodCheckError ( FMOD_System_CreateDSPByType ( soundSys, FMOD_DSP_TYPE_DELAY, &delayDsp ));
		MOAIFmodCheckError ( FMOD_Channel_AddDSP ( channel, index, delayDsp ));
		
		MOAIFmodCheckError ( FMOD_DSP_SetParameterFloat ( delayDsp, FMOD_DSP_DELAY_MAXDELAY, 1000 * delay ));
		MOAIFmodCheckError ( FMOD_DSP_SetParameterFloat ( delayDsp, FMOD_DSP_DELAY_CH0, 1000 * delay ));
		MOAIFmodCheckError ( FMOD_DSP_SetParameterFloat ( delayDsp, FMOD_DSP_DELAY_CH1, 1000 * delay ));
		
		self->mDelayDsp = delayDsp;
		MOAIFmodCheckError ( FMOD_DSP_SetActive ( delayDsp, true ));
		MOAIFmodCheckError ( FMOD_DSP_SetBypass ( delayDsp, true ));
	}
	
	MOAIFmodCheckError ( FMOD_DSP_SetParameterInt ( dsp, FMOD_DSP_FFT_WINDOWTYPE, FMOD_DSP_FFT_WINDOW_TRIANGLE ));
	MOAIFmodCheckError ( FMOD_DSP_SetParameterInt ( dsp, FMOD_DSP_FFT_WINDOWSIZE, self->mFftWindow ));

	// Activate, but bypass. DSP will not be processed, but all connections will work.
	// Sound can still be heard, processing is controlled by action's start/stop methods.
	MOAIFmodCheckError ( FMOD_DSP_SetActive ( dsp, true ));
	MOAIFmodCheckError ( FMOD_DSP_SetBypass ( dsp, true ));
	
	self->mDsp = dsp;
	
	return 0;
}

//----------------------------------------------------------------//
/**	@name	reserve
	@text	Allocate internal buffers for beat recognizers. Each detector is configurable for specific frequencies
	
	@in		MOAIFmodBeatDetector	self
	@in		number	detectors		numbers of beat recognizers
	@out	nil
*/
int MOAIFmodBeatDetector::_reserve ( lua_State *L ) {
	MOAI_LUA_SETUP ( MOAIFmodBeatDetector, "UN" )
	
	u32 count = state.GetValue < u32 >( 2, 0 );
	self->mBeats.Init ( count );
	
	return 0;
}

//----------------------------------------------------------------//
/**	@name	setBand
	@text	Initialize recognizer band. Band width is the number of FFT buckets.
			For window size 1024 and sampling rate 48khz each bucket will hold 46.8hz (48khz/1024)
			Bands are allocated sequentialy.
	
	@in		MOAIFmodBeatDetector	self
	@in		number	detectorId		detector index (1-based)
	@in		number	bandWidth
	@opt	number	delay			Minimal possible delay between beats. Default is 0.2 seconds
	@out	nil
*/
int MOAIFmodBeatDetector::_setBand ( lua_State *L ) {
	MOAI_LUA_SETUP ( MOAIFmodBeatDetector, "UNN" )

	u32 idx = state.GetValue < u32 >( 2, 1 ) - 1;
	if ( MOAILogMessages::CheckIndexPlusOne ( idx, self->mBeats.Size (), L )) {
		
		MOAIFmodBeat& beat = self->mBeats [ idx ];
		beat.mBandWidth = state.GetValue < u32 >( 3, 1 );
		beat.mDelay = state.GetValue < float >( 4, beat.mDelay );
	}
	
	return 0;
}


//================================================================//
// MOAIFmodBeatDetector
//================================================================//

const float MOAIFmodBeatDetector::HISTORY_FILTER = 0.02f;

//----------------------------------------------------------------//
bool MOAIFmodBeatDetector::ApplyAttrOp ( u32 attrID, MOAIAttrOp& attrOp, u32 op ) {
	
	return false;
}

//----------------------------------------------------------------//
void MOAIFmodBeatDetector::DetectBeats ( double step ) {
	
	for ( u32 i = 0; i < this->mBeats.Size (); ++i ) {
		
		this->mBeats [ i ].Update ( step );
		if ( this->mBeats [ i ].IsBeat ()) {
			this->OnBeat ( i );
		}
	}
}

//----------------------------------------------------------------//
bool MOAIFmodBeatDetector::IsDone () {
	
	return false;
}

//----------------------------------------------------------------//
MOAIFmodBeatDetector::MOAIFmodBeatDetector () :
	mDsp ( 0 ),
	mDelayDsp ( 0 ),
	mFftWindow ( DEFAULT_FFT_WINDOW ) {
	
	RTTI_BEGIN
		RTTI_EXTEND ( MOAINode )
		RTTI_EXTEND ( MOAIAction )
	RTTI_END
}

//----------------------------------------------------------------//
MOAIFmodBeatDetector::~MOAIFmodBeatDetector () {
	
	this->ReleaseDsp ();
}

//----------------------------------------------------------------//
void MOAIFmodBeatDetector::OnBeat ( int idx ) {
	
	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	if ( this->PushListenerAndSelf ( EVENT_BEAT, state )) {
		state.Push ( idx + 1 );
		state.DebugCall ( 2, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIFmodBeatDetector::OnStart () {
	
	if ( this->mDsp ) {
		MOAIFmodCheckError ( FMOD_DSP_SetBypass ( this->mDsp, false ));
	}
	
	if ( this->mDelayDsp ) {
		MOAIFmodCheckError ( FMOD_DSP_SetBypass ( this->mDelayDsp, false ));
	}
}

//----------------------------------------------------------------//
void MOAIFmodBeatDetector::OnStop () {
	
	if ( this->mDsp ) {
		MOAIFmodCheckError ( FMOD_DSP_SetBypass ( this->mDsp, true ));
	}
	
	if ( this->mDelayDsp ) {
		MOAIFmodCheckError ( FMOD_DSP_SetBypass ( this->mDelayDsp, true ));
	}
}

//----------------------------------------------------------------//
void MOAIFmodBeatDetector::OnUpdate ( double step ) {
	
	this->UpdateFFT ();
	this->DetectBeats ( step );
}

//----------------------------------------------------------------//
void MOAIFmodBeatDetector::RegisterLuaClass ( MOAILuaState& state ) {
	
	MOAIAction::RegisterLuaClass ( state );
	
	state.SetField ( -1, "EVENT_BEAT",	( u32 )EVENT_BEAT );
}

//----------------------------------------------------------------//
void MOAIFmodBeatDetector::RegisterLuaFuncs ( MOAILuaState& state ) {

	MOAIAction::RegisterLuaFuncs ( state );
	
	luaL_Reg regTable [] = {
		{ "attachToChannel",		_attachToChannel },
		{ "reserve",				_reserve },
		{ "setBand",				_setBand },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAIFmodBeatDetector::ReleaseDsp () {
	
	if ( this->mDelayDsp ) {
		FMOD_DSP_Release ( this->mDelayDsp );
		this->mDelayDsp = 0;
	}
	
	if ( this->mDsp ) {
		FMOD_DSP_Release ( this->mDsp );
		this->mDsp = 0;
	}
}

//----------------------------------------------------------------//
void MOAIFmodBeatDetector::UpdateFFT () {
	
	if ( !this->mDsp ) return;
	
	FMOD_DSP_PARAMETER_FFT* fft;
	FMOD_DSP_GetParameterData ( this->mDsp, FMOD_DSP_FFT_SPECTRUMDATA, ( void** )&fft, 0, 0, 0 );
	
	// No data yet
	if ( fft->numchannels == 0 || fft->length == 0 || this->mBeats.Size () == 0 ) {
		return;
	}
	
	// fmod docs says that only bottom half of spectrum contains useful data
	u32 niquist = fft->length / 2;
	
	// populate FFT bands array
	u32 bucket = 0;
	for ( u32 i = 0; i < this->mBeats.Size (); ++i ) {
		
		MOAIFmodBeat& beat = this->mBeats [ i ];
		beat.mInstantEnergy = 0.0f;
		
		for ( u32 b = bucket; b < Min ( niquist, bucket + beat.mBandWidth ); ++b ) {
			// TODO: other options are using average?; maximum?
			beat.mInstantEnergy += fft->spectrum [ 0 ][ b ];
		}
		beat.mInstantEnergy = beat.mInstantEnergy / beat.mBandWidth;
		
		beat.mAverageEnergy -= HISTORY_FILTER * beat.mAverageEnergy;
		beat.mAverageEnergy += HISTORY_FILTER * beat.mInstantEnergy;
		
		float diff = beat.mInstantEnergy - beat.mAverageEnergy;
		beat.mEnergyVariance -= HISTORY_FILTER * beat.mEnergyVariance;
		beat.mEnergyVariance += HISTORY_FILTER * diff * diff;
		
		bucket += beat.mBandWidth;
		if ( bucket >= niquist ) break;
	}
}


//================================================================//
// MOAIFmodBeat
//================================================================//

//----------------------------------------------------------------//
bool MOAIFmodBeat::IsBeat () {
	
	return this->mPower == 1.0f;
}

//----------------------------------------------------------------//
MOAIFmodBeat::MOAIFmodBeat () :
	mBandWidth ( 1 ),
	mAverageEnergy ( 0.0f ),
	mInstantEnergy ( 0.0f ),
	mEnergyVariance ( 0.0f ),
	mDelay ( 0.14f ),
	mElapsed ( 0 ),
	mPrevious ( 0 ),
	mPower ( 0 ) {
	
}

//----------------------------------------------------------------//
void MOAIFmodBeat::Update ( double step ) {
	
	this->mElapsed += step;
	this->mPower = ZLFloat::Clamp ( 1.0f - ( this->mElapsed / this->mPrevious ), 0.0f, 1.0f );
	
	if ( this->mElapsed < this->mDelay ) {
		return;
	}
	
	float var = Sqrt ( this->mEnergyVariance );
	
	// The smaller the variance (noisy music), then constant `k` is less,
	//
	// if variance 0: use k ~= 1.1
	// if variance == avg: use k ~= 2.5
	float k = this->mAverageEnergy == 0 ? 1.1f : ( 1.5f * var / this->mAverageEnergy + 1.1f );
	
	if ( this->mInstantEnergy > k * this->mAverageEnergy ) {
		this->mPower = 1.0f;
		this->mPrevious = this->mElapsed;
		this->mElapsed = 0.0f;
	}
}

