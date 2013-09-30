//
//  SwivlCommonLib.h
//  SwivlCommonLib
//
//  Copyright (c) 2013 Satarii Inc. All rights reserved.
//  Updated by Mikhail Levitskiy, Satarii Inc. on 02/27/2013
//

#import <Foundation/Foundation.h>
#import "PanningProgram.h"

/**
 The library assumes the app has defined the following NSNotification keys:
 */

/** Library sends this notification when Swivl base is connected and iAP communication is established */
extern NSString* AVSandboxSwivlDockAttached;

/** Library sends this notification when Swivl base is disconnected */
extern NSString* AVSandboxSwivlDockDetached;

/** Application should send this notification whenever video recording stops for any reason (user input, error, etc)  */
extern NSString* AVSandboxRecordingStoppedNotification;

/** Application should send this notification  whenever video recording starts  */
extern NSString* AVSandboxRecordingStartedNotification;

/** Application should send this notification whenever app transitions to or from Video Recording view. Notification should include a boolean value wrapped into NSNumber: YES indicates transition to recording view; NO - from recording view.
 */
extern NSString* AVSandboxNavToFromRecordingScreen;

/** Library sends this notification whenever Swivl base indicates that Tracking was enabled or disabled. This notification also includes a boolean value: YES means tracking is now enabled; NO - disabled. */
extern NSString* AVSandboxTrackingStateChangedNotification; // to update the app; check

/** Library sends this notification when Swivl starts or stops executing a 'panning program'. This notification also includes a boolean value: YES means program started; NO - stopped. */
extern NSString* AVSandboxPanningStateChangedNotification;

/** Optionsl. Application can send this notification to inform the library that tracking mode was changed (Normal/Slow or Sports/Fast). Included boolean value: YES for Sports/Fast mode; NO for Normal/SLow mode. */
extern NSString* AVSandboxFastTrackingEnabledStateChangedNotification;


/**
 Some UIAlert strings common to both the app, and to the low-level code that manages the Swivl base:
 */
#define NEEDSFWUPDATE_TITLE         @"Required Firmware Update"
#define FWUPDATEINSTRUCTIONSURL     @"http://www.swivl.com/firmware-update/"
#define NEEDSFULLUPDATE_TITLE       @"Firmware Update Required"
#define UPDATEOLDVERSION_MSG        @"There is a required firmware update for your Swivl. Click on the Instructions button to proceed.\n" 
#define UPDATELATER_MSG             @"Not Now"
#define SHOWMEHOW_MSG               @"Instructions"



/**
 Protocol used for interaction with Swivl Library
 */
@protocol SwivlBaseDelegate <NSObject>

/**
 Called by SwivlCommonLib Library at initialization time in order to pass library version info to the app (delegate). It is provided mostly for convenience. Library version infor is not necessary for operation and can be ignored if the app does not need it.
 @param dict is a dictionary containing version, revision, author and date info; all keys and values are NSStrings.
 */
- (void) swivlLibVersion: (NSDictionary *)dict;

/**
 Called by SwivlCommonLib to request current video recording state (YES or NO) from the app. Recording state reported by this function will be later passed to Swivl Base.
 @return YES if the app is currently recording video; NO otherwise.
 */
- (BOOL) appIsRecording;

/**
 This is a request to start or stop video recording in the app. It is typically called by SwivlCommonLib when it receives a start/stop video recording command from Swivl hardware, i.e. when user pressed 'Camera' button on Swivl base or marker.
 @param recording YES for start recording request or NO for stop recording request.
 */
- (void) setAppRecording: (BOOL ) recording;

/**
 Called by SwivlCommonLib to determine wether Video Recording view is currently active in the app UI or not.
 @return YES if app UI is currently at the recording view; NO otherwise.
 */
- (BOOL) appAtRecordingView;

/**
 This is a request to transition application UI to the Video Recording view. SwivlCommonLib typically calls it to prepare the app for 'start recording' command ( @see setAppRecording ) if the app UI is not already at Video Recording view ( @see appIsRecording ). It is assumed that app UI needs to be at Video Recording View when 'start recording' command arrives. However, it depends on implementation of the app and it might be safe to ignore this call if the app knows how to process 'start recording' command in any UI state.
 */
- (void) transitionAppToRecordingView;

/**
 Obsolete. This is a request to place a tag (time stamp) into the video currently being recorded. SwivlCommonLib calls it when it receives a 'tag' command from Swivl Base hardware, i.e. when user presses 'Action (Checkmark)' button on Swivl base or marker.
 */
- (void) appTagsRecording;
@end



/**
 Swivl Common Library
 */
@interface SwivlCommonLib : NSObject

/**
 Readonly. Indicates whether Swivl Base hardware is connected and iAP communication session is established (YES or NO).
 */
@property (readonly) BOOL swivlConnected;

/**
 Readonly. YES indicates that tracking is currently enabled in Swivl hardware. NO indicates that tracking is disabled. User can enable or disable tracking by pressing 'Action (Checkmark)' hardware button on Swivl base or marker. When tracking is enabled, tracking mode can be either 'slow' or 'fast' ( @see fastTrackingEnabled property )
 */
@property (readonly) BOOL tracking;

/**
 Read/Write. YES indicates that current tracking mode is 'Fast (Sports)'. NO indicates that tracking mode is 'Slow (Normal)'. In slow mode Swivl base moves smoother resulting in a smoother video. In fast mode Swivl base is able to track faster moving objects, but resulting video might not be as smooth as in normal mode. Note that Swivl tracking will not work if ( @see tracking property ) is set to NO.
 Application can change the value of this property, but the change is not passed to Swivl Base hardware until the app calls updateBaseSettings ( @see updateBaseSettings ) or new Swivl connection is established ( @see swivlConnected property ).
 */
@property BOOL fastTrackingEnabled;

/**
 Read/Write.
 YES indicates that automatic tilting (vertical tracking) is enabled and Swivl hardware will perform simultaneous tilting and panning (simultaneous vertical and horizontal tracking) based on marker position. When autoamtic tilting is enabled, the user does not need to press any buttons to activate tilting.
 NO indicates that automatic tilting is disabled and Swivl can do either panning (horizontal tracking) or tilting (vertical tracking) at a time. When automatic tilting is disabled, Swivl will notmally perform panning, but it will switch to tilting while user is holding (for 2 seconds or more) the 'Action (Checkmark)' button on Swivl base or marker.
 Application can change the value of this property, but the change is not passed to Swivl Base hardware until the app calls updateBaseSettings ( @see updateBaseSettings ).
 */
@property BOOL verticalTrackingEnabled;


/**
 Deprecated. Swivl Base firmware as a number.
 */
@property (readonly) NSNumber *deprecatedBaseFW;

/**
 Readonly.
 Swivl Base (dock) battery level. Valid range is from 0 to 100. Negative (-1) value indicates that battery level has not been received.
 */
@property (readonly) signed char baseBatteryLevel;

/**
 Readonly.
 Swivl Marker battery level. Valid range is from 0 to 100. Negative (-1) value indicates that battery level has not been received.
 */
@property (readonly) signed char markerBatteryLevel;

/**
 Readonly. Swivl Base (dock) firmware version as a string.
 */
@property (readonly) NSString* dockFWVersion;

/**
 Read/Write. YES indicates that Swivl Base hardware is currently in 'Programmed Action' mode. NO indicates that Swivl is in normal 'Tracking' mode.
 Application can change the value of this property, but the change is not passed to Swivl Base hardware until the app calls updateBaseSettings ( @see updateBaseSettings ) or new Swivl connection is established ( @see swivlConnected property ).
 */
@property BOOL programmedActionEnabled;

/**
 Read/Write. This property is used only in 'Programmed Action' mode and only when new 'panning program' is uploaded to Swivl base ( using @see updateBaseSettings ).
 YES indicates that when 'panning program' is sent to Swivl base next time, Swivl base must execute that program immediatelly, without waiting for user input.
 NO indicates that when 'panning program' is sent to Swivl base next time, Swivl base must store that program internally (without running) and go into pause/wait state (indicated by flashing LED light). Uploaded program will be executed when user presses hardware Action/Checkmark button on Swivl base or marker.
 */
@property BOOL autoPanEnabled;

/**
 Readonly. Used in 'Programmed Action' mode. YES indicates that Swivl is currently executing a 'panning program' that was previously uploaded to Swivl using updateBaseSettings call ( @see updateBaseSettings ). NO indicates that Swivl is not executing a program at this moment. If value of this property is NO and Swivl is in "Programmed Action" mode ( @see programmedActionEnabled ), then Swivl is currently in a wait/pause state (waiting for a user to press Action/Checkmark button). Pause state is indicated by a flashing LED light on Swivl base and marker.
 */
@property (readonly) BOOL panning;



/**
 Returns shared SwivlCommonLib object. It also allocates and initialises SwivlCommonLib if it has not been initialized.
 */
+ (SwivlCommonLib* ) sharedSwivlBaseForDelegate:(id)delegate;

/**
 Sends several parameters/settings to Swivl Base hardware. It should be called by the app whenever user changes Tracking or Programmed Action settings in the UI.
 In 'Programmed Action' mode it sends new 'Panning Program' to Swivl base along with a flag that indicates whether that program should be executed immediately or not ( @see autoPanEnabled property).
 In 'Tracking' mode it sends several tracking settings to Swivl base ( @see tracking @see fastTrackingEnabled @see verticalTrackingEnabled ).
 @param program new 'panning program' that should be uploaded to Swivl if it is in Programmed Action mode. In Tracking mode this parameter is ignored.
 */
- (void) updateBaseSettings:(PanningProgram *) program;

@end

