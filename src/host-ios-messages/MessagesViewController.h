//
//  MessagesViewController.h
//  MessagesExtension
//
//  Created by Vavius on 22/08/16.
//  Copyright © 2016 Vavius. All rights reserved.
//

#import <Messages/Messages.h>
#import "MOAIMessagesView.h"

@interface MessagesViewController : MSMessagesAppViewController {
	
	MOAIMessagesView* mMoaiView;
}

@end
