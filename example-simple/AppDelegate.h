//
//  AppDelegate.h
//  example-simple
//
//  Created by Robert Whelan on 1/25/16.
//  Copyright © 2016 smartwhere. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <SmartWhere/SmartWhere.h>

@interface AppDelegate : UIResponder <UIApplicationDelegate>


@property (strong, nonatomic) UIWindow *window;
@property (readonly) SmartWhere * smartwhere;


@end

