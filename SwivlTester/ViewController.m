//
//  ViewController.m
//  SwivlTester
//
//  Created by Josh Lytle on 9/30/13.
//  Copyright (c) 2013 Josh Lytle. All rights reserved.
//

#import "ViewController.h"
#import "SwivlCommonLib.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(receivedNotification:) name:AVSandboxSwivlDockAttached object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(receivedNotification:) name:AVSandboxSwivlDockDetached object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(receivedNotification:) name:AVSandboxTrackingStateChangedNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(receivedNotification:) name:AVSandboxPanningStateChangedNotification object:nil];

    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(receivedNotification:) name:AVSandboxRecordingStoppedNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(receivedNotification:) name:AVSandboxRecordingStartedNotification object:nil];
    
	// Do any additional setup after loading the view, typically from a nib.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(void)receivedNotification:(NSNotification *)notification
{
    NSString *string = [NSString stringWithFormat:@"Received Notification:%@",notification.name];
    self.statusTextView.text = string;
}

- (IBAction)sendNotification:(id)sender {
    NSNotification* event = [NSNotification
                             notificationWithName:AVSandboxNavToFromRecordingScreen
                             object:[NSNumber numberWithBool:YES]];
    
    [[NSNotificationCenter defaultCenter] postNotification:event];
}
@end
