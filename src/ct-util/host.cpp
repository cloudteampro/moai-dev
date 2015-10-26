// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include <ct-util/host.h>
#include <ct-util/CTUtil.h>

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
}

//----------------------------------------------------------------//
bool AKUIsRelaunchScheduled () {

    if ( CTUtil::IsValid ()) {
        return CTUtil::Get ().IsRelaunchScheduled ();
    }
    return false;
}
