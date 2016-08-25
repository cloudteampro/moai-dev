// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include <moai-ios-messages/host.h>
#include <moai-ios-messages/MOAIMessagesIOS.h>

//================================================================//
// aku
//================================================================//

//----------------------------------------------------------------//
void AKUIosMessagesContextInitialize () {

    REGISTER_LUA_CLASS ( MOAIMessagesIOS );
}

//----------------------------------------------------------------//
void AKUIosMessagesNotifyActivated ( MSMessagesAppViewController* vc ) {
	MOAIMessagesIOS::Get ().NotifyActivated ( vc );
}

//----------------------------------------------------------------//
void AKUIosMessagesNotifyDeactivated () {
	MOAIMessagesIOS::Get ().NotifyDeactivated ();
}

//----------------------------------------------------------------//
void AKUIosMessagesNotifyMessageSelected ( MSMessage* message ) {
	MOAIMessagesIOS::Get ().NotifyMessageSelected ( message );
}

//----------------------------------------------------------------//
void AKUIosMessagesNotifyMessageReceived ( MSMessage* message ) {
	MOAIMessagesIOS::Get ().NotifyMessageReceived ( message );
}

//----------------------------------------------------------------//
void AKUIosMessagesNotifyMessageStartSending ( MSMessage* message ) {
	MOAIMessagesIOS::Get ().NotifyMessageStartSending ( message );
}

//----------------------------------------------------------------//
void AKUIosMessagesNotifyMessageCancelSending ( MSMessage* message ) {
	MOAIMessagesIOS::Get ().NotifyMessageCancelSending ( message );
}

//----------------------------------------------------------------//
void AKUIosMessagesNotifyWillChangePresentation ( unsigned int style ) {
	MOAIMessagesIOS::Get ().NotifyWillChangePresentation (( MSMessagesAppPresentationStyle )style );
}

//----------------------------------------------------------------//
void AKUIosMessagesNotifyDidChangePresentation ( unsigned int style ) {
	MOAIMessagesIOS::Get ().NotifyDidChangePresentation (( MSMessagesAppPresentationStyle )style );
}


