//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

#ifndef CLOUDTEAM_UTIL_HOST_H
#define CLOUDTEAM_UTIL_HOST_H

#include <moai-core/host.h>

AKU_API void	AKUCTUtilAppFinalize		();
AKU_API void	AKUCTUtilAppInitialize		();
AKU_API void	AKUCTUtilContextInitialize	();

AKU_API void	AKUCTUtilSessionEnd			();
AKU_API void	AKUCTUtilSessionStart		();

AKU_API bool	AKUIsRelaunchScheduled		();

#endif
