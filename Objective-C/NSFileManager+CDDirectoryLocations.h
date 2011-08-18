//
//  NSFileManager+CDDirectoryLocations.h
//
//  Created by Matt Gallagher on 06 May 2010
//
//  Permission is given to use this source code file, free of charge, in any
//  project, commercial or otherwise, entirely at your risk, with the condition
//  that any redistribution (in part or whole) of source code must retain
//  this copyright and permission notice. Attribution in compiled projects is
//  appreciated but not required.
//
//  Modified and extended by Aron Cedercrantz, 2011.
//

#import <Foundation/Foundation.h>

/**
 * DirectoryLocations is a set of global methods for finding the fixed location
 * directoriess.
 *
 * @warning Note: The implementation requires the CDCommon header file for its
 *          logging macros as well as the CD_FIX_CATEGORY_BUG_QA1490 macro.
 *
 * @author Matt Gallagher
 * @author Aron Cedercrantz
 */
@interface NSFileManager (CDDirectoryLocations)

#pragma mark - Getting the Path or URL to Directories
/** @name Getting the Path or URL to Directories */
/**
 * Finds an existing directory or creates one.
 *
 * Method to tie together the steps of:
 * 1. Locate a standard directory by search path and domain mask
 * 2. Select the first path in the results
 * 3. Append a subdirectory to that path
 * 4. Create the directory and intermediate directories if needed
 * 5. Handle errors by emitting a proper NSError object
 *
 * @param searchPathDirectory The search path passed to
 *            NSSearchPathForDirectoriesInDomains.
 * @param  The domain mask passed to NSSearchPathForDirectoriesInDomains.
 * @param  The subdirectory appended.
 * @param errorOut If an error occurs, upon return contains an NSError object
 *            that describes the problem. Pass NULL if you do not want error
 *            information.
 * @return A string containing the path of the directory if it exists, otherwise `nil`.
 * @author Matt Gallagher
 */
- (NSString *)dl_findOrCreateDirectory:(NSSearchPathDirectory)searchPathDirectory
							  inDomain:(NSSearchPathDomainMask)domainMask
				   appendPathComponent:(NSString *)appendComponent
								 error:(NSError **)errorOut;

#pragma mark - Getting the Path and URL to Application Directories
/** @name Getting the Path or URL to Application Directories */
/**
 * Finds the application support directory (creates it if it doesn't exist) and
 * returns the path to it.
 *
 * Will log errors using debug assertion log, meaning that in debug mode an
 * assertion will be triggered and in release mode the error will only be
 * logged to stdout.
 *
 * @return A string containing the absolute path to the application support
 *         directory.
 * @see dl_findOrCreateDirectory:inDomain:appendPathComponent:error:
 * @see dl_applicationSupportDirectoryURL
 */
+ (NSString *)dl_applicationSupportDirectoryPath;

/**
 * Finds the application support directory (creates it if it doesn't exist) and
 * returns the URL to it.
 *
 * Will log errors using debug assertion log, meaning that in debug mode an
 * assertion will be triggered and in release mode the error will only be
 * logged to stdout.
 *
 * @return An url containing the absolute path to the application support
 *         directory.
 * @see dl_findOrCreateDirectory:inDomain:appendPathComponent:error:
 * @see dl_applicationSupportDirectoryPath
 */
+ (NSURL *)dl_applicationSupportDirectoryURL;


+ (NSString *)dl_applicationDocumentsDirectoryPath;
+ (NSURL *)dl_applicationDocumentsDirectoryURL;

+ (NSString *)dl_applicationCacheDirectoryPath;
+ (NSURL *)dl_applicationCacheDirectoryURL;


@end
