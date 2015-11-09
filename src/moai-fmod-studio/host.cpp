// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include <moai-fmod-studio/host.h>
#include <moai-fmod-studio/MOAIFmodStudio.h>
#include <moai-fmod-studio/MOAIFmodStudioChannel.h>
#include <moai-fmod-studio/MOAIFmodStudioSound.h>

#ifdef MOAI_OS_IPHONE
	#include <moai-fmod-studio/host-ios.h>
#endif

//================================================================//
// MOAIFmodStudio
//================================================================//

//----------------------------------------------------------------//
void AKUFmodStudioAppFinalize () {
	
	if ( MOAIFmodStudio::IsValid ()) {
		MOAIFmodStudio::Get ().CloseSoundSystem ();
	}
}

//----------------------------------------------------------------//
void AKUFmodStudioAppInitialize () {
	
#ifdef MOAI_OS_IPHONE
	AKUInitializeIOSAudioSession ();
#endif
}

//----------------------------------------------------------------//
void AKUFmodStudioContextInitialize () {
    
	MOAIFmodStudio::Affirm ();
	
	REGISTER_LUA_CLASS ( MOAIFmodStudio )
	REGISTER_LUA_CLASS ( MOAIFmodStudioChannel )
	REGISTER_LUA_CLASS ( MOAIFmodStudioSound )
}

//----------------------------------------------------------------//
void AKUFmodStudioUpdate () {

	MOAIFmodStudio::Get ().Update ();
}

//----------------------------------------------------------------//
void AKUFmodStudioPause ( bool pause ) {
    
    if ( pause ) {
        MOAIFmodStudio::Get ().Suspend ();
    }
    else {
        MOAIFmodStudio::Get ().Resume ();
    }
}
