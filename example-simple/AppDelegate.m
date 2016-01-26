//
//  AppDelegate.m
//  example-simple
//
//  Created by Robert Whelan on 1/25/16.
//  Copyright © 2016 smartwhere. All rights reserved.
//

#import "AppDelegate.h"

@interface AppDelegate () <SmartWhereDelegate>
@end

@implementation AppDelegate {
    SWNotification * _lastEvent;
}


#pragma mark - Application Delegate methods

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    
    // Read NSDictionary from SmartwhereConfig.plist to get custom settings
    
    NSString* plistPath = [[NSBundle mainBundle] pathForResource:@"SmartwhereConfig" ofType:@"plist"];
    NSDictionary *dict = [[NSDictionary alloc] initWithContentsOfFile:plistPath];
    
    /* instantiate the _smartwhere object passing in your Application Id, API Key and API secret along with the configuration */
    _smartwhere = [[SmartWhere alloc]
                   initWithAppId:@"xxxx"
                   apiKey:@"xxxxxxxx"
                   apiSecret:@"xxxxxxxx"
                   withConfig: dict];
    
    // set the smartwhere delegate 
    _smartwhere.delegate = self;
    return YES;
}

- (void)application:(UIApplication *)application didReceiveLocalNotification:(UILocalNotification *)notification {
    // require for processing proximity notifications
    [_smartwhere didReceiveLocalNotification:notification];
    
}


- (void)applicationDidEnterBackground:(UIApplication *)application {
    [_smartwhere applicationDidEnterBackground];
}



- (void)applicationDidBecomeActive:(UIApplication *)application {

    [_smartwhere applicationDidBecomeActive];
}

#pragma mark - SmartWhere delegates

- (void)smartWhere:(SmartWhere *)smartwhere didReceiveLocalNotification:(SWNotification *)notification {
    
    NSLog(@"SWNotification came in while in the foreground, alerting the user");
    _lastEvent = notification;

    UIAlertView * alert = [[UIAlertView alloc] initWithTitle:notification.title message:notification.message delegate:self cancelButtonTitle:@"Cancel" otherButtonTitles:nil];
    [alert addButtonWithTitle:@"Ok"];
    [alert show];
}

- (void)alertView:(UIAlertView *)alertView didDismissWithButtonIndex:(NSInteger)buttonIndex {
    if ([alertView cancelButtonIndex] != buttonIndex && _lastEvent) {
        [_smartwhere fireLocalNotificationAction:_lastEvent];

    }
    
    _lastEvent = nil;
}




@end
