// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#import <moai-ios/headers.h>
#import <StoreKit/StoreKit.h>
#import <moai-ios-billing/MOAIBillingIOS.h>
#import <moai-ios-billing/MOAIStoreKitListener.h>

//================================================================//
// lua
//================================================================//

//----------------------------------------------------------------//
/**	@lua	appReceipt
	@text	Returns json string containing app receipt. Can be used to
			validate purchases on iOS 7 and above.

	@out	string	or nil if not available
*/
int MOAIBillingIOS::_appReceipt ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIBillingIOS, "" )
	
	if ( NSFoundationVersionNumber >= NSFoundationVersionNumber_iOS_7_0 ) {
		
		NSData* receiptData = [ NSData dataWithContentsOfURL:[[ NSBundle mainBundle ] appStoreReceiptURL ]];
		if ( receiptData ) {
			[ receiptData toLua:state ];
			return 1;
		}
	}
	
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	canMakePayments
	@text	Determines whether or not the app has permission to 
			request payments for in-app purchases.
	
	@out	bool enabled
*/
int MOAIBillingIOS::_canMakePayments ( lua_State* L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIBillingIOS, "" )
	
	BOOL result = [ SKPaymentQueue canMakePayments ];
	lua_pushboolean ( state, result );
	
	return 1;
}

//----------------------------------------------------------------//
/**	@lua	finishTransaction
	@text	Finish transaction manually. 
			Only call if autoFinishTransactions is set to false.
	
	@in		string	transactionIdentifier	This is not productId, but a server provided
											unique identifier found in transaction table
	@out	boolead success
*/
int MOAIBillingIOS::_finishTransaction ( lua_State *L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIBillingIOS, "S" )
	
	NSString* transactionId = [[ NSString alloc ] initWithLua:state stackIndex:1 ];
	
	NSArray* transactions = [[ SKPaymentQueue defaultQueue ] transactions ];
	for ( SKPaymentTransaction* transaction in transactions ) {
		
		if ([ transactionId isEqualToString:transaction.transactionIdentifier ]) {
			[[ SKPaymentQueue defaultQueue ] finishTransaction:transaction ];
			break;
		}
	}
	
	[ transactionId release ];
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	requestPaymentForProduct
	@text	Request payment for an in-app purchase.
	
	@in		string 	sku				The SKU to purchase.
	@opt	number 	quantity		Default value is 1.
	@opt	string	username		Optional username
	@out	nil
*/
int MOAIBillingIOS::_requestPaymentForProduct ( lua_State* L ) {
	
	MOAILuaState state ( L );
	
	cc8* identifier = state.GetValue < cc8* >( 1, "" );
	int quantity	= state.GetValue < int >( 2, 1 );
	cc8* username	= state.GetValue < cc8* >( 3, 0 );
	
	if ( quantity ) {
		
		// TODO: deal with deprecation here
		// Create MOAILuaObject wrapper for SKProduct?
		SKMutablePayment* payment = [ SKMutablePayment paymentWithProductIdentifier:[ NSString stringWithUTF8String:identifier ]];
		payment.quantity = quantity;
		
		if ( username ) {
			if ([ payment respondsToSelector:@selector ( setApplicationUsername: )]) {
				payment.applicationUsername = [ NSString stringWithUTF8String:username ];
			}
		}
		[[ SKPaymentQueue defaultQueue ] addPayment:payment ];
	}
	
	return 0;
}

//----------------------------------------------------------------//
/**	@lua	requestProductIdentifiers
	@text	Verify the validity of a set of products and retrieve
			relevant information thereabout.
	
	@in		table skus				A list of SKUs.
	@out	nil
*/
int MOAIBillingIOS::_requestProductIdentifiers ( lua_State* L ) {
	
	MOAILuaState state ( L );
	
	NSMutableSet* productSet = [[[ NSMutableSet alloc ] init ] autorelease ];
	
	int top = state.GetTop ();
	for ( int i = 1; i <= top; ++i ) {
	
		if ( state.IsType ( i, LUA_TSTRING )) {
			
			cc8* identifier = state.GetValue < cc8* >( i, "" );
			[ productSet addObject :[ NSString stringWithUTF8String:identifier ]];
		}
	
		if ( state.IsType ( i, LUA_TTABLE )) {
			
			int itr = state.PushTableItr ( i );
			while ( state.TableItrNext ( itr )) {
				
				cc8* identifier = state.GetValue < cc8* >( -1, "" );
				[ productSet addObject :[ NSString stringWithUTF8String:identifier ]];
			}
		}
	}
	
	SKProductsRequest* request = [[ SKProductsRequest alloc ] initWithProductIdentifiers:productSet ];
	request.delegate = MOAIBillingIOS::Get ().mStoreKitListener;
	[ request start ];
	
	return 0;
}

//----------------------------------------------------------------//
/** @lua	restoreCompletedTransactions
	@text	Request the restoration of any previously purchased items.

	@out 	nil
*/
int MOAIBillingIOS::_restoreCompletedTransactions( lua_State* L ) {
	
	UNUSED ( L );
	
	[[ SKPaymentQueue defaultQueue ] restoreCompletedTransactions ];

	return 0;
}

//----------------------------------------------------------------//
// TODO doxygen
int MOAIBillingIOS::_setAutoFinishTransactions ( lua_State *L ) {
	MOAI_LUA_SETUP_SINGLE ( MOAIBillingIOS, "" )
	
	self->mAutoFinishTransactions = state.GetValue < bool >( 1, true );
	return 0;
}

//================================================================//
// MOAIBillingIOS
//================================================================//

//----------------------------------------------------------------//
MOAIBillingIOS::MOAIBillingIOS () :
	mAutoFinishTransactions ( true ) {

	RTTI_SINGLE ( MOAIGlobalEventSource )
	
	this->mStoreKitListener = [[ MOAIStoreKitListener alloc ] init ];
	[[ SKPaymentQueue defaultQueue ] addTransactionObserver:this->mStoreKitListener ];
}

//----------------------------------------------------------------//
MOAIBillingIOS::~MOAIBillingIOS () {

	[[ SKPaymentQueue defaultQueue ] removeTransactionObserver:this->mStoreKitListener ];
	[ this->mStoreKitListener release ];
}

//----------------------------------------------------------------//
void MOAIBillingIOS::DidReceivePaymentQueueError ( NSError* error, cc8* extraInfo ) {
	
	if ( !MOAILuaRuntime::IsValid ()) return;
	
	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	if ( this->PushListener ( PAYMENT_QUEUE_ERROR, state )) {
		
		[ error toLua:state ];
		state.Push ( extraInfo );
		state.DebugCall ( 2, 0 );
	}
}

//----------------------------------------------------------------//
void MOAIBillingIOS::DidReceiveRestoreFinished ( SKPaymentQueue* queue ) {
	
	UNUSED ( queue );
	this->InvokeListener ( PAYMENT_RESTORE_FINISHED );
}

//----------------------------------------------------------------//
void MOAIBillingIOS::PaymentQueueUpdatedTransactions ( SKPaymentQueue* queue, NSArray* transactions ) {
	
	UNUSED ( queue );

	if ( !MOAILuaRuntime::IsValid ()) return;
	
	for ( SKPaymentTransaction* transaction in transactions ) {
		
		MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
		
		if ( this->PushListener ( PAYMENT_QUEUE_TRANSACTION, state )) {
			
			this->PushPaymentTransaction ( state, transaction );
			state.DebugCall ( 1, 0 );
		}
		
		if ( this->mAutoFinishTransactions &&
			 ( transaction.transactionState != SKPaymentTransactionStatePurchasing &&
			   transaction.transactionState != SKPaymentTransactionStateDeferred )) {
			
			[[ SKPaymentQueue defaultQueue ] finishTransaction:transaction ];
		}
	}
}

//----------------------------------------------------------------//
void MOAIBillingIOS::ProductsRequestDidReceiveResponse ( SKProductsRequest* request, SKProductsResponse* response ) {
	
	if ( !MOAILuaRuntime::IsValid ()) return;
	
	MOAIScopedLuaState state = MOAILuaRuntime::Get ().State ();
	if ( this->PushListener ( PRODUCT_REQUEST_RESPONSE, state )) {
		
		NSNumberFormatter *formatter = [[ NSNumberFormatter alloc ] init ];
		[ formatter setFormatterBehavior:NSNumberFormatterBehavior10_4 ];
		[ formatter setNumberStyle:NSNumberFormatterCurrencyStyle ];
		
		lua_newtable ( state );
		
		int count = 1;
		for ( SKProduct* product in response.products ) {
		
			lua_pushnumber ( state, count++ );
			lua_newtable ( state );
		
			[ formatter setLocale:product.priceLocale ];
			NSString * formattedString = [ formatter stringFromNumber:product.price ];
			
			state.SetField ( -1, "localizedTitle",			[ product.localizedTitle UTF8String ]);
			state.SetField ( -1, "localizedDescription",	[ product.localizedDescription UTF8String ]);
			state.SetField ( -1, "price",					[ product.price floatValue ]);
			state.SetField ( -1, "localizedPrice",			[ formattedString UTF8String]);
			state.SetField ( -1, "priceLocale",				[ product.priceLocale.localeIdentifier UTF8String ]);
			state.SetField ( -1, "productIdentifier",		[ product.productIdentifier UTF8String ]);
			
			lua_settable ( state, -3 );
		}
		
		// Note: If you're testing in-app purchases, chances are your product Id
		// will take time to propagate into Apple's sandbox/test environment and
		// thus the id's will be invalid for hours(?) (at the time of writing this).
		for ( NSString *invalidProductId in response.invalidProductIdentifiers ) {
			
			NSLog(@"StoreKit: Invalid product id: %@" , invalidProductId);
		}
		
		state.DebugCall ( 1, 0 );
		[ formatter release ];
	}
	
	[ request autorelease ];
}

//----------------------------------------------------------------//
void MOAIBillingIOS::PushPaymentTransaction ( MOAILuaState& state, SKPaymentTransaction* transaction ) {

	lua_newtable ( state );
	
	state.Push ( "transactionState" );
	
	switch ( transaction.transactionState ) {
		
		case SKPaymentTransactionStatePurchasing: {
			
			state.Push ( TRANSACTION_STATE_PURCHASING );
			break;
		}
		case SKPaymentTransactionStatePurchased: {
			
			state.Push ( TRANSACTION_STATE_PURCHASED );
			break;
		}
		case SKPaymentTransactionStateFailed: {
			
			if ( transaction.error.code == SKErrorPaymentCancelled ) {
				
				state.Push ( TRANSACTION_STATE_CANCELLED );
			}
			else {
				
				state.Push ( TRANSACTION_STATE_FAILED );
			}
			break;
		}
		case SKPaymentTransactionStateRestored: {
			
			state.Push ( TRANSACTION_STATE_RESTORED );
			break;
		}
		case SKPaymentTransactionStateDeferred: {
			
			state.Push ( TRANSACTION_STATE_DEFFERED );
			break;
		}
		default: {
			
			state.Push ();
			break;
		}
	}
	
	lua_settable ( state, -3 );
	
	if ( transaction.payment ) {
		
		state.Push ( "payment" );
		lua_newtable ( state );
		
		SKPayment* payment = transaction.payment;
		
		state.SetField ( -1, "productIdentifier", [ payment.productIdentifier UTF8String ]);
		state.SetField ( -1, "quantity", ( int )payment.quantity );

		if ([ payment respondsToSelector:@selector ( applicationUsername )]) {
			if ( payment.applicationUsername ) {
				state.SetField ( -1, "applicationUsername", [ payment.applicationUsername UTF8String ]);
			}
		}
		
		lua_settable ( state, -3 );
	}
	
	if ( transaction.transactionState == SKPaymentTransactionStateFailed ) {
		
		state.SetField ( -1, "error", [[ transaction.error localizedDescription ] UTF8String ]);
	}
	
	if ( transaction.transactionState == SKPaymentTransactionStateRestored ) {
		
		state.Push ( "originalTransaction" );
		this->PushPaymentTransaction ( state, transaction.originalTransaction );
		lua_settable ( state, -3 );
	}
	
	if ( transaction.transactionState == SKPaymentTransactionStatePurchased ) {

		state.Push ( "transactionReceipt" );
		
		if ( transaction.transactionReceipt ) {
			[ transaction.transactionReceipt toLua:state ];
		}
		else {
			state.Push ();
		}
		
		lua_settable ( state, -3 );
	}
	
	if (( transaction.transactionState == SKPaymentTransactionStatePurchased ) || ( transaction.transactionState == SKPaymentTransactionStateRestored )) {
		
		state.SetField ( -1, "transactionIdentifier", [ transaction.transactionIdentifier UTF8String ]);
		
		state.Push ( "transactionDate" );
		if ( transaction.transactionDate ) {
			[ transaction.transactionDate toLua:state ];
		}
		else {
			state.Push ();
		}
		lua_settable ( state, -3 );
	}
}

//----------------------------------------------------------------//
void MOAIBillingIOS::RegisterLuaClass ( MOAILuaState& state ) {
	
	state.SetField ( -1, "PAYMENT_QUEUE_TRANSACTION",	( u32 )PAYMENT_QUEUE_TRANSACTION );
	state.SetField ( -1, "PRODUCT_REQUEST_RESPONSE",	( u32 )PRODUCT_REQUEST_RESPONSE );
	state.SetField ( -1, "PAYMENT_QUEUE_ERROR",			( u32 )PAYMENT_QUEUE_ERROR );
	state.SetField ( -1, "PAYMENT_RESTORE_FINISHED",	( u32 )PAYMENT_RESTORE_FINISHED );

	state.SetField ( -1, "TRANSACTION_STATE_PURCHASING",( u32 )TRANSACTION_STATE_PURCHASING );
	state.SetField ( -1, "TRANSACTION_STATE_PURCHASED", ( u32 )TRANSACTION_STATE_PURCHASED );
	state.SetField ( -1, "TRANSACTION_STATE_FAILED",    ( u32 )TRANSACTION_STATE_FAILED );
	state.SetField ( -1, "TRANSACTION_STATE_RESTORED",  ( u32 )TRANSACTION_STATE_RESTORED );
	state.SetField ( -1, "TRANSACTION_STATE_CANCELLED", ( u32 )TRANSACTION_STATE_CANCELLED );
	
	luaL_Reg regTable [] = {
		{ "appReceipt",						_appReceipt },
		{ "canMakePayments",				_canMakePayments },
		{ "finishTransaction",				_finishTransaction },
		{ "getListener",					&MOAIGlobalEventSource::_getListener < MOAIBillingIOS > },
		{ "restoreCompletedTransactions",	_restoreCompletedTransactions },
		{ "requestPaymentForProduct",		_requestPaymentForProduct },
		{ "requestProductIdentifiers",		_requestProductIdentifiers },
		{ "setAutoFinishTransactions",		_setAutoFinishTransactions },
		{ "setListener",					&MOAIGlobalEventSource::_setListener < MOAIBillingIOS > },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}