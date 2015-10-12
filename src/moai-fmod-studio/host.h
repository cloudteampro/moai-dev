//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

#ifndef MOAI_FMOD_STUDIO_HOST_H
#define MOAI_FMOD_STUDIO_HOST_H

#include <moai-core/host.h>

AKU_API void	AKUFmodStudioAppFinalize		();
AKU_API void	AKUFmodStudioAppInitialize		();
AKU_API void	AKUFmodStudioContextInitialize	();
AKU_API void	AKUFmodStudioUpdate             ();
AKU_API void    AKUFmodStudioPause              ( bool pause );

#endif
