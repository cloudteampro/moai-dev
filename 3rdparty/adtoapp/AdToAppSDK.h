//
//  AdToAppSDK.h
//
//  Copyright (c) 2015 AdToApp. All rights reserved.
//

#import <Foundation/Foundation.h>

#define ADTOAPPSDK_VERSION (@"47.15")

#define ADTOAPP_IMAGE_INTERSTITIAL (@"Image")
#define ADTOAPP_VIDEO_INTERSTITIAL (@"Video")
#define ADTOAPP_INTERSTITIAL (@"Interstitial")//Video or Image

#define ADTOAPP_REWARDED_INTERSTITIAL (@"Rewarded")
#define ADTOAPP_BANNER (@"Banner")

/** ADS PROVIDERS **/
#define ADTOAPP_PROVIDER_ADCOLONY_IDT       (1)
#define ADTOAPP_PROVIDER_SMAATO_IDT         (3)
#define ADTOAPP_PROVIDER_STARTAPP_IDT       (5)
#define ADTOAPP_PROVIDER_INMOBI_IDT         (6)
#define ADTOAPP_PROVIDER_GOOGLEADMOBS_IDT   (7)
#define ADTOAPP_PROVIDER_APPLOVIN_IDT       (8)
#define ADTOAPP_PROVIDER_REVMOB_IDT         (11)
#define ADTOAPP_PROVIDER_AMAZON_IDT         (16)
#define ADTOAPP_PROVIDER_VUNGLE_IDT         (17)
#define ADTOAPP_PROVIDER_MYTARGET_IDT       (21)
#define ADTOAPP_PROVIDER_UNITY_IDT          (22)
#define ADTOAPP_PROVIDER_AVOCARROT_IDT      (23)
#define ADTOAPP_PROVIDER_NATIVEX_IDT        (24)
#define ADTOAPP_PROVIDER_TAPSENSE_IDT       (25)
#define ADTOAPP_PROVIDER_YANDEX_IDT         (26)
#define ADTOAPP_PROVIDER_SUPERSONIC_IDT     (27)
#define ADTOAPP_PROVIDER_WOOBI_IDT          (28)
#define ADTOAPP_PROVIDER_INSTREAMATIC_IDT   (29)
#define ADTOAPP_PROVIDER_INHOUSE_IDT        (30)
#define ADTOAPP_PROVIDER_FACEBOOK_IDT       (31)
#define ADTOAPP_PROVIDER_FLURRY_IDT         (32)

#define ADTOAPP_PROVIDER_TEST_IDT           (32767)
/***/

@class UIViewController;

/**
 The methods declared by the AdToAppSDKDelegate protocol allow the adopting delegate to respond to messages from fullscreen ads and thus respond to, and in some affect, operations such as appearance/disappearance of advertising on/from screen, clicking, receiving of reward, first load of an ad and failure to display ad.
 */
@protocol AdToAppSDKDelegate <NSObject>

/**
 Called right before appearance of an ad on the screen.
 */
-(void)onAdWillAppear:(NSString*)adType providerId:(int)providerId;

/**
 Called immediately after disappearance of an ad from the screen.
 */
-(void)onAdDidDisappear:(NSString*)adType providerId:(int)providerId;

@optional

/**
 Called if the user has viewed an ad and receives a reward
 */
-(void)onReward:(int)reward currency:(NSString*)gameCurrency providerId:(int)providerId;

/**
 Tells the delegate when the user clicks on fullscreen ad.
 */
-(void)onAdClicked:(NSString*)adType providerId:(int)providerId;

/**
 Called right before appearance of fullscreen ad on the screen. Return YES if you want to display ad. Otherwise, return NO.
 */
-(BOOL)shouldShowAd:(NSString*)adType;

/**
 Tells the delegate that the AdToApp SDK has failed to display fullscreen ad.
 */
-(void)onAdFailedToAppear:(NSString*)adType;

/**
 Tells the delegate that AdToApp SDK has loaded the first fullscreen ad and it is ready to be shown.
 */
-(void)onFirstAdLoaded:(NSString*)adType;

@end

@interface AdToAppSDK : NSObject

/**
 Initialization of the AdToApp SDK on startup.
  @appId is taken from the instruction on the adtoapp.com website
  @modules is an array of constants that are used to show ads in your application. Each them must be one of following constants: ADTOAPP_IMAGE_INTERSTITIAL, ADTOAPP_VIDEO_INTERSTITIAL, ADTOAPP_INTERSTITIAL, ADTOAPP_REWARDED_INTERSTITIAL and ADTOAPP_BANNER. For performance reasons, it is strongly recommended to exclude constants that are not used to show ads. If you want to show small banners, include ADTOAPP_BANNER constant in this array.
 */
+(void)startWithAppId:(NSString*)appId modules:(NSArray*)modules;

/**
 Sets the delegate to respond to messages from fullscreen ads and thus respond to, and in some affect, operations such as appearance/disappearance of advertising on/from screen, clicking, receiving of reward, first load of an ad and failure to display ad.
 */
+(void)setDelegate:(id<AdToAppSDKDelegate>)delegate;

/**
 A boolean value that determines whether there is an ad on the screen or not.
 */
+(BOOL)isInterstitialDisplayed;

/**
 Enables verbose console logs for debugging purpurses.
 */
+(void)enableDebugLogs;

/**
 Enables test mode.
 */
+(void)enableTestMode;

/**
 @brief Shows interstitial ads. Can only be called from the main thread.
 @param typeOfInterstitial Can be one of ADTOAPP_IMAGE_INTERSTITIAL, ADTOAPP_VIDEO_INTERSTITIAL, ADTOAPP_INTERSTITIAL, ADTOAPP_REWARDED_INTERSTITIAL.
 @warning It is strongly recommended to use ADTOAPP_INTERSTITIAL to show ads because this will maximize revenue.
 */
+(BOOL)showInterstitial:(NSString*)typeOfInterstitial;

/**
 @brief Shows interstitial ads. Can only be called from the main thread.
 @param typeOfInterstitial can be ADTOAPP_IMAGE_INTERSTITIAL, ADTOAPP_VIDEO_INTERSTITIAL, ADTOAPP_INTERSTITIAL or ADTOAPP_REWARDED_INTERSTITIAL. It is strongly recommended to use ADTOAPP_INTERSTITIAL to show ads because this will maximize revenue.
 @param vc is the active topmost view controller. Make sure it will not be removed from the screen when the user watch the ad.
 */
+(BOOL)showInterstitial:(NSString*)typeOfInterstitial fromViewController:(UIViewController*)vc;

/**
 Can only be called from the main thread. It is strongly recommended to avoid using this method. Because it makes our analytic logs too complex to be analyzed quickly. If you want to handle failure to display ads by showInterstitial: and showInterstitial:fromViewController: methods, please use onAdFailedToAppear: delegate method.
  @typeOfInterstitial can be ADTOAPP_IMAGE_INTERSTITIAL, ADTOAPP_VIDEO_INTERSTITIAL, ADTOAPP_INTERSTITIAL or ADTOAPP_REWARDED_INTERSTITIAL.
*/
+(BOOL)hasInterstitial:(NSString*)typeOfInterstitial;

/** Hides the displayed interstitial ad if it is supported by the current provider. Can only be called from the main thread.
 */
+(BOOL)hideInterstitial;

/** Currency and value which will be returned by the onReward:currency: delegate method.
 */
+(NSString*)rewardedCurrency;
+(int)rewardedValue;

@end
