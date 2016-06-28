//
//  Copyright (c) 2014-2016 smartwhere llc. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import <SmartWhere/SWNotification.h>
#import <SmartWhere/SWTag.h>
#import <SmartWhere/SWTrigger.h>

extern const NSString * SWSmartWhereDidReceiveLocalNotification;

@class SmartWhere;

typedef void (^SWValidateScanCallBack)(SWTag* tag, NSError* err);

@protocol SmartWhereDelegate
- (void)smartWhere:(SmartWhere*)smartwhere didReceiveLocalNotification:(SWNotification*)notification;
@optional

- (void)smartWhere:(SmartWhere*)smartwhere didReceiveCustomBeaconAction:(SWAction*)action withBeaconProperties:(NSDictionary*) beaconProperties triggeredBy:(SWTriggerType) trigger;
- (void)smartWhere:(SmartWhere*)smartwhere didReceiveCustomFenceAction:(SWAction*)action withFenceProperties:(NSDictionary*) fenceProperties triggeredBy:(SWTriggerType) trigger;
- (void)smartWhere:(SmartWhere*)smartwhere didReceiveCustomTagAction:(SWAction*)action withTagProperties:(NSDictionary*) tagProperties triggeredBy:(SWTriggerType) trigger;
- (void)smartWhere:(SmartWhere*)smartwhere didReceiveCommunicationError:(NSError*) error;

@end

@interface SmartWhere : NSObject

- (id)initWithAppId:(NSString*)appid
             apiKey:(NSString*)key
          apiSecret:(NSString*)secret;

- (id)initWithAppId:(NSString*)appid
             apiKey:(NSString*)key
          apiSecret:(NSString*)secret
         withConfig:(NSDictionary*)config;

- (id)initWithAppId:(NSString*)appid
             apiKey:(NSString*)key
          apiSecret:(NSString*)secret
  maxBeaconCacheAge:(NSInteger)minutes;
- (void) invalidate;

- (void) processScan:(NSString*) code;
- (void) validateScan:(NSString*) code
             callback: (SWValidateScanCallBack) callback;

// call in the applications appdelegate application:didReceiveLocalNotification: to
// properly handle notification clicks.
- (NSDictionary*)didReceiveLocalNotification:(UILocalNotification*)notification;

// call to fire the action for the given swnotification.  Used when receiving a notification
// while the app is in the foreground and wanting to action on it.
- (NSDictionary*)fireLocalNotificationAction:(SWNotification*)notification;

// manipulate user values used for condition processing
- (void)clearUserAttributes;
- (NSDictionary*) getUserAttributes;
- (void)setUserAttributes:(NSDictionary*) attributes;
- (void)setUserInteger:(NSInteger)value forKey:(NSString*)key;
- (void)setUserString:(NSString*)value forKey:(NSString*)key;
- (void)removeUserValueForKey:(NSString*)key;
- (id)getUserValueForKey:(NSString*)key;

// manipulate user values sent with the tracking
- (void)clearUserTrackingAttributes;
- (void)setUserTrackingAttributes:(NSDictionary*) attributes;
- (NSDictionary*) getUserTrackingAttributes;
- (void)setUserTrackingString:(NSString*)value forKey:(NSString*)key;
- (void)removeUserTrackingValueForKey:(NSString*)key;
- (id)getUserTrackingValueForKey:(NSString*)key;

// use to extend beacon ranging
- (void)applicationDidEnterBackground;
- (void)applicationDidBecomeActive;

@property (nonatomic, weak) NSObject<SmartWhereDelegate>* delegate;

@end
