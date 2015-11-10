//
//  host-ios.mm
//  cloudteam
//
//  Created by vavius on 09/11/15.
//
//

#import <AVFoundation/AVAudioSession.h>
#import <Foundation/Foundation.h>
#include <fmod_ios.h>

//----------------------------------------------------------------//
void AKUInitializeIOSAudioSession () {
	
	double rate = 24000.0;
	int blockSize = 512;
	long channels = 2;
	BOOL success = false;
	
	AVAudioSession* session = [ AVAudioSession sharedInstance ];
	
	// From the fmod sample project:
	// Make our category 'solo' for the best chance at getting our desired settings
	// Use AVAudioSessionCategoryPlayAndRecord if you need microphone input
	
	// I prefer AVAudioSessionCategoryAmbient: this permits to listen audio player while playing.
	success = [ session setCategory:AVAudioSessionCategoryAmbient error:nil ];
	
	// Set our preferred rate and activate the session to test it
	success = [ session setPreferredSampleRate:rate error:nil ];
	success = [ session setActive:TRUE error:nil ];

	// Query the actual supported rate and max channels
	rate = [ session sampleRate ];
	channels = [ session maximumOutputNumberOfChannels ];
	
	// Deactivate the session so we can change parameters without route changes each time
	success = [ session setActive:FALSE error:nil ];
	
	// Set the duration and channels based on known supported values
	success = [ session setPreferredIOBufferDuration:blockSize / rate error:nil ];
	success = [ session setPreferredOutputNumberOfChannels:channels error:nil ];


	// Set up some observers for various notifications
	[[ NSNotificationCenter defaultCenter ]
		addObserverForName:AVAudioSessionInterruptionNotification
		object:nil
		queue:nil
		usingBlock:^( NSNotification *notification ) {
	 
			bool began = [[ notification.userInfo valueForKey:AVAudioSessionInterruptionTypeKey ] intValue ] == AVAudioSessionInterruptionTypeBegan;
			NSLog ( @"Interruption %@", began ? @"Began" : @"Ended" );
			
			if ( !began ) {
				[[ AVAudioSession sharedInstance ] setActive:TRUE error:nil ];
			}
		}
	];
	
//	You can receive notification when other app starts or stops playing music, so that
//	it's possible to mute background music in the game.
//	The notification is available in iOS 8, disabled for now.

//	[[ NSNotificationCenter defaultCenter ]
//		addObserverForName:AVAudioSessionSilenceSecondaryAudioHintNotification
//		object:nil
//		queue:nil
//		usingBlock:^( NSNotification *notification ) {
//	 
//			int hint = [[ notification.userInfo valueForKey:AVAudioSessionSilenceSecondaryAudioHintTypeKey ] intValue ];
//			switch ( hint ) {
//				case AVAudioSessionSilenceSecondaryAudioHintTypeBegin:
//					// mute BG sound?
//					break;
//				case AVAudioSessionSilenceSecondaryAudioHintTypeEnd:
//					// unmute BG sound?
//					break;
//			}
//		}
//	];

	// Activate the audio session
	success = [ session setActive:TRUE error:nil ];
}
