//
//  ViewController.h
//  SwivlTester
//
//  Created by Josh Lytle on 9/30/13.
//  Copyright (c) 2013 Josh Lytle. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController

@property (weak, nonatomic) IBOutlet UITextView *statusTextView;
- (IBAction)sendNotification:(id)sender;

@end
