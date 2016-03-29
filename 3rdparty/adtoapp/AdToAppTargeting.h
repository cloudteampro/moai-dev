//
//  AdToAppTargeting.h
//  AdToAppSDK
//
//  Created 10/03/16.
//  Copyright © 2016 AdToApp. All rights reserved.
//

#import <Foundation/Foundation.h>

#if defined(__cplusplus)
#define ADTOAPP_EXTERN extern "C"
#else
#define ADTOAPP_EXTERN extern
#endif

/**
 * Provide with per-user non personally-identifiable information for ad targeting purposes.
 * Providing non personally-identifiable information using this API will improve targeting and unlock
 * improved earnings for your app.
 * @param targetingParam One of the predefined targeting keys.
 * @param value Either a predefined targeting value, or arbitrary value.
 */
ADTOAPP_EXTERN void AdToAppSDK_setTargetingParam(NSString* targetingParam, NSString* value);

#pragma mark - Targeting Metadata Constants

/**
 * Targeting metadata keys
 */
ADTOAPP_EXTERN NSString *const  ADTOAPP_TARGETING_PARAM_KEYWORDS;          /** application keywords. A free form set of keywords, separated by ',' e.g: @"sports,cars,bikes" */
ADTOAPP_EXTERN NSString *const  ADTOAPP_TARGETING_PARAM_USER_INTERESTS;    /** user's interests param. A free form set of interests, separated by ',' */
ADTOAPP_EXTERN NSString *const  ADTOAPP_TARGETING_PARAM_USER_AGE;          /** user's age param, e.g: @"25" */
ADTOAPP_EXTERN NSString *const  ADTOAPP_TARGETING_PARAM_USER_GENDER;       /** user's gender param */
ADTOAPP_EXTERN NSString *const  ADTOAPP_TARGETING_PARAM_USER_BIRTHDAY;     /** user's birthday param. Value should be in format dd.MM.yyyy, e.g: "01.01.2000" */
ADTOAPP_EXTERN NSString *const  ADTOAPP_TARGETING_PARAM_USER_OCCUPATION;   /** user's occupation param */
ADTOAPP_EXTERN NSString *const  ADTOAPP_TARGETING_PARAM_USER_RELATIONSHIP; /** user's relationship param */
ADTOAPP_EXTERN NSString *const  ADTOAPP_TARGETING_PARAM_USER_LATITUDE;     /** user's current latitude param */
ADTOAPP_EXTERN NSString *const  ADTOAPP_TARGETING_PARAM_USER_LONGITUDE;    /** user's current longitude param */

/**
 * Targeting metadata values (for pre-defined values)
 */
ADTOAPP_EXTERN NSString *const  ADTOAPP_TARGETING_PARAM_USER_GENDER_MALE;        /** User is male */
ADTOAPP_EXTERN NSString *const  ADTOAPP_TARGETING_PARAM_USER_GENDER_FEMALE;      /** User is female */

ADTOAPP_EXTERN NSString *const  ADTOAPP_TARGETING_PARAM_USER_OCCUPATION_SCHOOL;     /** User goes to school */
ADTOAPP_EXTERN NSString *const  ADTOAPP_TARGETING_PARAM_USER_OCCUPATION_UNIVERSITY; /** User at university */
ADTOAPP_EXTERN NSString *const  ADTOAPP_TARGETING_PARAM_USER_OCCUPATION_WORK;       /** User is working */

ADTOAPP_EXTERN NSString *const  ADTOAPP_TARGETING_PARAM_USER_RELATIONSHIP_SINGLE;   /** User is single */
ADTOAPP_EXTERN NSString *const  ADTOAPP_TARGETING_PARAM_USER_RELATIONSHIP_ENGAGED;  /** User is engaged */
ADTOAPP_EXTERN NSString *const  ADTOAPP_TARGETING_PARAM_USER_RELATIONSHIP_MARRIED;  /** User is married */
ADTOAPP_EXTERN NSString *const  ADTOAPP_TARGETING_PARAM_USER_RELATIONSHIP_DIVORCED; /** User is divorced */