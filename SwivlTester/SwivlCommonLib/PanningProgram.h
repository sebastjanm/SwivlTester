//
//  PanningProgram.h
//  AVSandbox
//
//  Copyright (c) 2013 Satarii Inc. All rights reserved.
//  Modified (comments only) by Mikhail Levitskiy, Satarii, 02/27/2013

#import <UIKit/UIKit.h>

/**
 Panning program describes a small action sequence (a program) that can be uploaded to Swivl base hardware for immediate or delayed execution.
 Examples:
 1) Continuous CCW pan: angle=-360, reverses=NO, repeats=YES
 2) Single CW 10 degree pan: angle=10, reverses=NO, repeats=NO
 3) Single 10 degree pan and return to original position: angle=10, reverses=YES, repeats=NO
 4) Continouos back-and-forth 10 degree panning: angle=10, reverses=YES, repeats=YES
 */
@interface PanningProgram : NSObject

/**
 Panning/rotation speed in custom units: from 0 (slowest) to 100 (fastest). Must be positive.
 It is not in units of degrees per second as the name might suggest.
 */
@property (nonatomic, assign) float degreesPerSecond;

/**
 Rotation angle in degrees. Range is from -360 to +360. Positive values for CW direction and negative for CCW.
 */
@property (nonatomic, assign) float angle;

/**
 Flag that indicates wether Swivl base should rotate back to original position after performing the rotation prescribed by @see angle property. YES = rotate back to original position. NO = do not rotate back.
 */
@property (nonatomic, assign) BOOL reverses;

/**
 Flag that determines wether Swivl should continuously repeat this program. YES = repeat continuously. NO = execute only once.
 */
@property (nonatomic, assign) BOOL repeats;


/**
 Returns a string containing names and values of all the properties (degreesPerSecond, angle, reverses, repeats). 
 */
- (NSString*)description;

/**
 Archives this object to cache file.
 @param key name of the archive
 */
- (BOOL)saveWithKey:(NSString*)key;

/**
 Initializes this object with values from a previously created archive.
 @param key name of the archive
 */
- (id)initFromKey:(NSString*)key;

@end
