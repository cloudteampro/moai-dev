//----------------------------------------------------------------//
// Copyright (c) 2010-2011 Zipline Games, Inc. 
// All Rights Reserved. 
// http://getmoai.com
//----------------------------------------------------------------//

#ifndef AKU_IOS_MESSAGES_HOST_H
#define AKU_IOS_MESSAGES_HOST_H

#include <moai-core/host.h>
#include <Messages/Messages.h>

AKU_API void	AKUIosMessagesContextInitialize		();

AKU_API void	AKUIosMessagesNotifyActivated					( MSMessagesAppViewController* vc );
AKU_API void	AKUIosMessagesNotifyDeactivated					();
AKU_API void	AKUIosMessagesNotifyMessageSelected				( MSMessage* message );
AKU_API void	AKUIosMessagesNotifyMessageReceived				( MSMessage* message );
AKU_API void	AKUIosMessagesNotifyMessageStartSending			( MSMessage* message );
AKU_API void	AKUIosMessagesNotifyMessageCancelSending		( MSMessage* message );
AKU_API void	AKUIosMessagesNotifyWillChangePresentation		( unsigned int style );
AKU_API void	AKUIosMessagesNotifyDidChangePresentation		( unsigned int style );

#endif
