// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include <ct-util/host.h>
#include <ct-util/CTUtil.h>
#include <ct-util/MOAIColorBlender.h>

//================================================================//
// CTUtil
//================================================================//

//----------------------------------------------------------------//
void AKUCTUtilAppFinalize () {
	
}

//----------------------------------------------------------------//
void AKUCTUtilAppInitialize () {

}

//----------------------------------------------------------------//
void AKUCTUtilContextInitialize () {
    
	REGISTER_LUA_CLASS ( CTUtil )
	REGISTER_LUA_CLASS ( MOAIColorBlender )
}

//----------------------------------------------------------------//
void AKUCTUtilSessionEnd () {
	
	if ( CTUtil::IsValid ()) {
		CTUtil::Get ().InvokeListener ( CTUtil::SESSION_END );
	}
}

//----------------------------------------------------------------//
void AKUCTUtilSessionStart () {

	if ( CTUtil::IsValid ()) {
		CTUtil::Get ().InvokeListener ( CTUtil::SESSION_START );
	}
}

//----------------------------------------------------------------//
bool AKUIsRelaunchScheduled () {

    if ( CTUtil::IsValid ()) {
        return CTUtil::Get ().IsRelaunchScheduled ();
    }
    return false;
}
