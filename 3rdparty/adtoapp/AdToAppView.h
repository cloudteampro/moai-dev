//
//  AdToAppView.h
//
//  Copyright (c) 2015 AdToApp. All rights reserved.
//

#import <UIKit/UIKit.h>

#define ADTOAPPSDK_BANNER_SIZE_300x50  (@"300x50")
#define ADTOAPPSDK_BANNER_SIZE_320x50  (@"320x50")
#define ADTOAPPSDK_BANNER_SIZE_728x90  (@"728x90")
#define ADTOAPPSDK_BANNER_SIZE_768x90  (@"768x90")
#define ADTOAPPSDK_BANNER_SIZE_300x250 (@"300x250")

#define ADTOAPPSDK_BANNER_POSITION_TOP_LEFT (@"0;0")
#define ADTOAPPSDK_BANNER_POSITION_TOP_CENTER (@"1;0")
#define ADTOAPPSDK_BANNER_POSITION_TOP_RIGHT (@"2;0")
#define ADTOAPPSDK_BANNER_POSITION_CENTER_LEFT (@"0;1")
#define ADTOAPPSDK_BANNER_POSITION_CENTER (@"1;1")
#define ADTOAPPSDK_BANNER_POSITION_CENTER_RIGHT (@"2;1")
#define ADTOAPPSDK_BANNER_POSITION_BOTTOM_LEFT (@"0;2")
#define ADTOAPPSDK_BANNER_POSITION_BOTTOM (@"1;2")
#define ADTOAPPSDK_BANNER_POSITION_BOTTOM_RIGHT (@"2;2")

@class AdToAppView;

/**
 The methods declared by the AdToAppViewDelegate protocol allow the adopting delegate to respond to messages from AdToAppView and thus respond to operations such as displaying of ad, failure to display ad and clicking on ad.
 */
@protocol AdToAppViewDelegate <NSObject>

/**
 Called if AdToApp view has successfully displayed an ad.
 */
-(void)adToAppViewDidDisplayAd:(AdToAppView*)adToAppView providerId:(int)providerId;

/**
 Called if AdToApp view has failed to displayed an ad.
 */
-(void)adToAppView:(AdToAppView*)adToAppView failedToDisplayAdWithError:(NSError*)error isConnectionError:(BOOL)isConnectionError;

@optional

/**
 Called when the user clicks on the displayed ad.
 */
-(void)adToAppViewOnClick:(AdToAppView*)view providerId:(int)providerId;

@end

@interface AdToAppView : UIView

/**
 Sets the delegate to respond to messages from AdToAppView and thus respond to operations such as displaying of ad, failure to display ad and clicking on ad.
 */
@property (nonatomic, weak) id<AdToAppViewDelegate> delegate;

/**
 A boolean value that determines whether there is an ad displayed on the AdToAppView.
 */
@property (nonatomic, readonly) BOOL adIsDisplayed;

/**
 Banner refresh interval in seconds. Default is 30. The zero value indicates that automatic refreshing is disabled and you should refresh ads manually by calling loadNextAd method.
*/
-(NSTimeInterval)refreshInterval;

/**
 Sets banner refresh interval.
 @refreshInterval banner refresh interval in seconds. Default is 30. The zero value can be set to disable automatic refreshing and to refresh ads manually by calling loadNextAd method.
 */
-(void)setRefreshInterval:(NSTimeInterval)refreshInterval;

/**
 Refreshes banner manually.
 */
-(void)loadNextAd;

/**
 Init the AdToAppView instance.
 @bannerSize can be one of predefined values:
    ADTOAPPSDK_BANNER_SIZE_300x50
    ADTOAPPSDK_BANNER_SIZE_320x50
    ADTOAPPSDK_BANNER_SIZE_728x90
    ADTOAPPSDK_BANNER_SIZE_768x90
    ADTOAPPSDK_BANNER_SIZE_300x250
 It is strongly recommended to use only ADTOAPPSDK_BANNER_SIZE_320x50 or ADTOAPPSDK_BANNER_SIZE_768x90 to archive the maximum revenue.
 @delegate to respond to messages from AdToAppView and thus respond to operations such as displaying of ad, failure to display ad and clicking on ad.
 */
-(id)initWithBannerSize:(NSString*)bannerSize delegate:(id<AdToAppViewDelegate>)delegate;

/**
 Init the AdToAppView instance.
 @view the parent view on which your banner ad will be displayed.
 @position inside the parent @view. Can be one of the following:
    ADTOAPPSDK_BANNER_POSITION_TOP_LEFT
    ADTOAPPSDK_BANNER_POSITION_TOP_CENTER
    ADTOAPPSDK_BANNER_POSITION_TOP_RIGHT
    ADTOAPPSDK_BANNER_POSITION_CENTER_LEFT
    ADTOAPPSDK_BANNER_POSITION_CENTER
    ADTOAPPSDK_BANNER_POSITION_CENTER_RIGHT
    ADTOAPPSDK_BANNER_POSITION_BOTTOM_LEFT
    ADTOAPPSDK_BANNER_POSITION_BOTTOM
    ADTOAPPSDK_BANNER_POSITION_BOTTOM_RIGHT
 @edgeInsets to specify additional edge insets of your banner.
 @bannerSize can be one of predefined values:
    ADTOAPPSDK_BANNER_SIZE_300x50
    ADTOAPPSDK_BANNER_SIZE_320x50
    ADTOAPPSDK_BANNER_SIZE_728x90
    ADTOAPPSDK_BANNER_SIZE_768x90
    ADTOAPPSDK_BANNER_SIZE_300x250
 It is strongly recommended to use only ADTOAPPSDK_BANNER_SIZE_320x50 or ADTOAPPSDK_BANNER_SIZE_768x90 to archive the maximum revenue.
 @delegate to respond to messages from AdToAppView and thus respond to operations such as displaying of ad, failure to display ad and clicking on ad.
 */
+(id)attachToView:(UIView*)view position:(NSString*)position edgeInsets:(UIEdgeInsets)edgeInsets bannerSize:(NSString*)bannerSize delegate:(id<AdToAppViewDelegate>)delegate;

@end


