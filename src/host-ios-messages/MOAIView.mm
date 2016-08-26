//
//  MoaiView.m
//  MOAI_imessage
//
//  Created by Vavius on 26/08/16.
//  Copyright © 2016 Vavius. All rights reserved.
//

#import "MOAIView.h"
#import <host-modules/aku_modules.h>

enum {
	MOAI_INPUT_DEVICE,
	TOTAL_INPUT_DEVICES,
};

enum {
	MOAI_TOUCH_SENSOR,
	TOTAL_SENSORS,
};

//================================================================//
// MOAIView
//================================================================//
@interface MOAIView ()

-( void ) handleTouches :( NSSet* )touches :( BOOL )down;

@end

@implementation MOAIView

-( void ) initInputDevice {
	
	self.userInteractionEnabled = YES;
	self.multipleTouchEnabled = YES;
	
	AKUSetInputConfigurationName ( "iPhone" );
	
	AKUReserveInputDevices			( TOTAL_INPUT_DEVICES );
	AKUSetInputDevice				( MOAI_INPUT_DEVICE, "device" );
	
	AKUReserveInputDeviceSensors	( MOAI_INPUT_DEVICE, TOTAL_SENSORS );
	AKUSetInputDeviceTouch			( MOAI_INPUT_DEVICE, MOAI_TOUCH_SENSOR,		"touch" );
}

//----------------------------------------------------------------//
-( void ) handleTouches :( NSSet* )touches :( BOOL )down {
	
	for ( UITouch* touch in touches ) {
		
		CGPoint p = [ touch locationInView:self ];
		
		AKUEnqueueTouchEvent (
							  MOAI_INPUT_DEVICE,
							  MOAI_TOUCH_SENSOR,
							  ( int )( long ) touch, // use the address of the touch as a unique id
							  down,
							  p.x * [[ UIScreen mainScreen ] scale ],
							  p.y * [[ UIScreen mainScreen ] scale ]
							  );
	}
}

//----------------------------------------------------------------//
-( void )touchesBegan:( NSSet* )touches withEvent:( UIEvent* )event {
	( void )event;
	
	[ self handleTouches :touches :YES ];
}

//----------------------------------------------------------------//
-( void )touchesCancelled:( NSSet* )touches withEvent:( UIEvent* )event {
	( void )touches;
	( void )event;
	
	AKUEnqueueTouchEventCancel ( MOAI_INPUT_DEVICE, MOAI_TOUCH_SENSOR );
}

//----------------------------------------------------------------//
-( void )touchesEnded:( NSSet* )touches withEvent:( UIEvent* )event {
	( void )event;
	
	[ self handleTouches :touches :NO ];
}

//----------------------------------------------------------------//
-( void )touchesMoved:( NSSet* )touches withEvent:( UIEvent* )event {
	( void )event;
	
	[ self handleTouches :touches :YES ];
}

//----------------------------------------------------------------//
-( void ) layoutSubviews {
	[ super layoutSubviews ];
	
	CGFloat scale	= self.contentScaleFactor;
	CGSize size		= self.bounds.size;
	AKUSetScreenSize ( scale * size.width, scale * size.height );
	AKUSetViewSize ( scale * size.width, scale * size.height );
}


@end
