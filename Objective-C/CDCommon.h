//
//  CDCommon.h
//
//  Created by Aron Cedercrantz on 01/01/09.
//  Copyright 2009-2011 Aron Cedercrantz. All rights reserved.
//

#ifndef CD_COMMON_H
#define CD_COMMON_H
#ifdef __OBJC__


#pragma mark - Bundle information
// Bundle information
#define CD_BUNDLE_IDENTIFIER		[[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleIdentifier"]
// Add the key "CDBundleCreatorName" to your bundle plist for this to work.
#define CD_APP_CREATOR				[[NSBundle mainBundle] objectForInfoDictionaryKey:@"CDBundleCreatorName"]
#define CD_APP_NAME					[[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleName"]
#define CD_APP_VERSION				[[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleShortVersionString"]
#define CD_APP_VERSION_REV			[[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleVersion"]
#define CD_APP_COPYRIGHT			[[NSBundle mainBundle] objectForInfoDictionaryKey:@"NSHumanReadableCopyright"]


#pragma mark - Misc application macros
// Application delegate
#if TARGET_OS_IPHONE
#	define CD_APP_DELEGATE				[[UIApplication sharedApplication] delegate]
// OS X
#else
#	define CD_APP_DELEGATE				[[NSApplication sharedApplication] delegate]
#endif // TARGET_OS_IPHONE


#pragma mark - Open URL macros
// Open an URL
#if TARGET_OS_IPHONE
#	define CD_OPEN_URL(url)			[[UIApplication sharedApplication] openURL:url]
// OS X
#else
#	define CD_OPEN_URL(url)			[[NSWorkspace sharedWorkspace] openURL:url]
#endif // TARGET_OS_IPHONE
#define CD_OPEN_URL_STR(urlStr)		CD_OPEN_URL([NSURL URLWithString:urlStr])


#pragma mark - Boxing Values in Objective-C Objects
// Box a value _val_ using NSValue.
// By Phil Jordan (@pmjordan) – https://twitter.com/pmjordan/status/221902596506529792
#define CD_BOXED(val)				({ typeof(val) _tmp_val = (val); [NSValue valueWithBytes:&(_tmp_val) objCType:@encode(typeof(val))]; })


#pragma mark - Preferences
// Retrieving preference values
#define CD_PREF_KEY_VALUE(x)		[[[NSUserDefaultsController sharedUserDefaultsController] values] valueForKey:(x)]
#define CD_PREF_KEY_BOOL(x)			[(PREF_KEY_VALUE(x)) boolValue]
#define CD_PREF_SET_KEY_VALUE(x, y)	[[[NSUserDefaultsController sharedUserDefaultsController] values] setValue:(y) forKey:(x)]
#define CD_PREF_OBSERVE_VALUE(x, y)	[[NSUserDefaultsController sharedUserDefaultsController] addObserver:y forKeyPath:x options:NSKeyValueObservingOptionOld context:nil];


#pragma mark - Accessor macros
// Atomic accessor (retain, copy and return) macros for non-atomic data types.
// From http://cocoawithlove.com/2009/10/memory-and-thread-safe-custom-property.html
#define CDAtomicRetainedSetToFrom(dest, source) \
objc_setProperty(self, _cmd, (ptrdiff_t)(&dest) - (ptrdiff_t)(self), source, YES, NO)
#define CDAtomicCopiedSetToFrom(dest, source) \
objc_setProperty(self, _cmd, (ptrdiff_t)(&dest) - (ptrdiff_t)(self), source, YES, YES)
#define CDAtomicAutoreleasedGet(source) \
objc_getProperty(self, _cmd, (ptrdiff_t)(&source) - (ptrdiff_t)(self), YES)
#define CDAtomicStructToFrom(dest, source) \
objc_copyStruct(&dest, &source, sizeof(__typeof__(source)), YES, NO)

// Non-atomic accessor (retain, copy and return) macros for non-atomic data types.
// From http://cocoawithlove.com/2009/10/memory-and-thread-safe-custom-property.html
#define CDNonatomicRetainedSetToFrom(a, b) do{if(a!=b){[a release];a=[b retain];}}while(0)
#define CDNonatomicCopySetToFrom(a, b) do{if(a!=b){[a release];a=[b copy];}}while(0)


#pragma mark - Release macros
// Release Objective-C object macro (will release and then set the variable to
// nil if not in debug mode, otherwise it will just release variable).
// From http://iphonedevelopment.blogspot.com/2010/09/dealloc.html
// Modified by Aron Cedercrantz to be ARC compatible.
#if __has_feature(objc_arc)
#	define CDRelease(x)			x = nil
#else
#	if DEBUG
#		define CDRelease(x)		[x release]
#	else
#		define CDRelease(x)		[x release], x = nil
#	endif
#endif


#pragma mark - Debug outout
// Define our own version of NSLog(...) which will only send its input to the
// output if we are in debug mode and a assertion logger which will cause an
// assertion if we are in debug mode and a in non-debug mode it will output the
// assertion via NSLog(...)
#ifdef DEBUG
#	define DLog(...) NSLog(@"=== %s %@", __PRETTY_FUNCTION__, [NSString stringWithFormat:__VA_ARGS__])
#	define DCLog(condition, ...) if ((condition)) { DLog(__VA_ARGS__); }
#	define ALog(...) [[NSAssertionHandler currentHandler] handleFailureInFunction:[NSString stringWithUTF8String:__PRETTY_FUNCTION__] file:[NSString stringWithUTF8String:__FILE__] lineNumber:__LINE__ description:__VA_ARGS__]
#else // !DEBUG
#	define DLog(...) do { } while (0)
#	define DCLog(condition, ...) do { } while (0)
#ifndef NS_BLOCK_ASSERTIONS
#	define NS_BLOCK_ASSERTIONS
#endif
#	define ALog(...) NSLog(@"*** %s %@", __PRETTY_FUNCTION__, [NSString stringWithFormat:__VA_ARGS__])
#endif // DEBUG
// Assertion method which use ALog(...) to print its output
#define ZAssert(condition, ...) do { if (!(condition)) { ALog(__VA_ARGS__); }} while(0)


#pragma mark - -description method formats
// 1:    %@ == The object name
// 2:    %p == The object pointer
// 3...: %@ == Extra information
#define CDDescriptionFormat			@"<%@: %p { %@ }>"
#define CDDescriptionFormat1		CDDescriptionMsg
#define CDDescriptionFormat2		@"<%@: %p { %@, %@ }>"
#define CDDescriptionFormat3		@"<%@: %p { %@, %@, %@ }>"
#define CDDescriptionFormat4		@"<%@: %p { %@, %@, %@, %@}>"


#pragma mark - Exception formats
// 1: %s == The method
// 2: %@ == Message
#define CDExceptionBaseFormat		@"*** %s: %@"
#define CDExceptionErrorFormat		CDExceptionBaseFormat
#define CDExceptionWarningFormat	@"+++ %s: %@"
#define CDExceptionNoticeFormat		@"=== %s: %@"


#pragma mark - Fix for files in static libraries containing only categories
/**
 * @brief Force a category to be loaded when an app starts up.
 *
 * Add this macro before each category implementation, so we don't have to use
 * -all_load or -force_load to load object files from static libraries that only contain
 * categories and no classes.
 * See http://developer.apple.com/library/mac/#qa/qa2006/qa1490.html for more info.
 * Also see https://github.com/jverkoey/nimbus for the source of this code snippet.
 */
#define CD_FIX_CATEGORY_BUG_QA1490(name) @interface CD_FIX_CATEGORY_BUG_QA1490_##name @end \
@implementation CD_FIX_CATEGORY_BUG_QA1490_##name @end


#endif // __OBJC__
#endif // CD_COMMON_H

