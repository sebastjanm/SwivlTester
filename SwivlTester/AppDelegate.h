//
//  AppDelegate.h
//  SwivlTester
//
//  Created by Josh Lytle on 9/30/13.
//  Copyright (c) 2013 Josh Lytle. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SwivlCommonLib.h"

@interface AppDelegate : UIResponder <UIApplicationDelegate, SwivlBaseDelegate>

@property (strong, nonatomic) UIWindow *window;

@property BOOL atRecordingView;
@property BOOL isRecording;

@end
