//
//  Common.h
//  Arizona
//
//  Created by Aron Cedercrantz on 31/03/10.
//  Copyright 2009 __MyCompanyName__. All rights reserved.
//

#ifndef CD_COMMON_H
#define CD_COMMON_H
#ifdef __OBJC__

#define CD_APP_CREATOR				@"Cedercrantz"


#pragma mark Bundle information
// Bundle information
#define CD_BUNDLE_IDENTIFIER		[[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleIdentifier"]
#define CD_APP_NAME					[[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleName"]
#define CD_APP_VERSION				[[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleShortVersionString"]
#define CD_APP_VERSION_REV			[[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleVersion"]
#define CD_APP_COPYRIGHT			[[NSBundle mainBundle] objectForInfoDictionaryKey:@"NSHumanReadableCopyright"]


#pragma mark Misc application macros
// Application delegate
#define CD_APP_DELEGATE				[[NSApplication sharedApplication] delegate]


#pragma mark Misc workspace macros
// Open an URL
#define CD_OPEN_URL(urlString)		[[NSWorkspace sharedWorkspace] openURL:[NSURL URLWithString:urlString]]


#pragma mark Preferences
// Retrieving preference values
#define CD_PREF_KEY_VALUE(x)		[[[NSUserDefaultsController sharedUserDefaultsController] values] valueForKey:(x)]
#define CD_PREF_KEY_BOOL(x)			[(PREF_KEY_VALUE(x)) boolValue]
#define CD_PREF_SET_KEY_VALUE(x, y)	[[[NSUserDefaultsController sharedUserDefaultsController] values] setValue:(y) forKey:(x)]
#define CD_PREF_OBSERVE_VALUE(x, y)	[[NSUserDefaultsController sharedUserDefaultsController] addObserver:y forKeyPath:x options:NSKeyValueObservingOptionOld context:nil];


#pragma mark Key observing
// key, observer, object
#define CD_OBSERVE_VALUE(x, y, z)	[(z) addObserver:y forKeyPath:x options:NSKeyValueObservingOptionOld context:nil];


#pragma mark Accessor macros
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

#pragma mark Debug outout
// Define our own version of NSLog(...) which will only send its input to the
// output if we are in debug mode and a assertion logger which will cause an
// assertion if we are in debug mode and a in non-debug mode it will output the
// assertion via NSLog(...)
#ifdef DEBUG
	#define DLog(...) NSLog(@"%s %@", __PRETTY_FUNCTION__, [NSString stringWithFormat:__VA_ARGS__])
	#define ALog(...) [[NSAssertionHandler currentHandler] handleFailureInFunction:[NSString stringWithCString:__PRETTY_FUNCTION__ encoding:NSUTF8StringEncoding] file:[NSString stringWithCString:__FILE__ encoding:NSUTF8StringEncoding] lineNumber:__LINE__ description:__VA_ARGS__]
#else // !DEBUG
	#define DLog(...) do { } while (0)
	#ifndef NS_BLOCK_ASSERTIONS
		#define NS_BLOCK_ASSERTIONS
	#endif
	#define ALog(...) NSLog(@"%s %@", __PRETTY_FUNCTION__, [NSString stringWithFormat:__VA_ARGS__])
#endif // DEBUG
// Assertion method which use ALog(...) to print its output
#define ZAssert(condition, ...) do { if (!(condition)) { ALog(__VA_ARGS__); }} while(0)

#pragma mark -description method formats
// 1:    %@ == The object name
// 2:    %p == The object pointer
// 3...: %@ == Extra information
#define CDDescriptionMsg			@"<%@: %p { %@ }>"
#define CDDescriptionMsg1			PBDescriptionMsg
#define CDDescriptionMsg2			@"<%@: %p { %@, %@ }>"
#define CDDescriptionMsg3			@"<%@: %p { %@, %@, %@ }>"
#define CDDescriptionMsg4			@"<%@: %p { %@, %@, %@, %@}>"


#pragma mark Exception formats
// 1: %s == The method
// 2: %@ == Message
#define CDExceptionBaseFormat		@"*** %s: %@"
#define CDExceptionErrorFormat		PBExceptionBaseFormat
#define CDExceptionWarningFormat	@"+++ %s: %@"
#define CDExceptionNoticeFormat		@"=== %s: %@"


#pragma mark Object is empty category
// Definition of isEmpty function. If the pointer given points to nil, an object
// whose lenght is zero or an object with zero children the pointer and/or the
// object it points to is considered empty.
@interface NSObject (CDIsEmpty)

- (BOOL)cdIsEmpty;

@end

#endif // __OBJC__
#endif // CD_COMMON_H

