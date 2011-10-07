//
//  NSFileManager+CDDirectoryLocations.m
//
//  Created by Matt Gallagher on 06 May 2010
//
//  Permission is given to use this source code file, free of charge, in any
//  project, commercial or otherwise, entirely at your risk, with the condition
//  that any redistribution (in part or whole) of source code must retain
//  this copyright and permission notice. Attribution in compiled projects is
//  appreciated but not required.
//
//  Modified and extended to by Aron Cedercrantz, 2011.
//

#import "NSFileManager+CDDirectoryLocations.h"
#import "CDCommon.h"


enum {
	kDirectoryLocationErrorNoPathFound,
	kDirectoryLocationErrorFileExistsAtLocation
};

NSString * const kDirectoryLocationDomain = @"DirectoryLocationDomain";

CD_FIX_CATEGORY_BUG_QA1490(NSFileManager_CDDirectoryLocations)
@implementation NSFileManager (CDDirectoryLocations)

#pragma mark - Getting the Path and URL to Application Directories
+ (NSString *)cd_applicationSupportDirectoryPath:(NSString *)applicationName
{	
	NSError *error;
	NSFileManager *fm = [[self alloc] init];
	NSString *result =
	[fm cd_findOrCreateDirectory:NSApplicationSupportDirectory
						inDomain:NSUserDomainMask
			 appendPathComponent:applicationName
						   error:&error];
	
	if (!result) {
		ALog(@"Unable to find or create application support directory:\n%@", error);
	}
	return result;
}

+ (NSURL *)cd_applicationSupportDirectoryURL:(NSString *)applicationName
{
	NSString *aPath = [self cd_applicationSupportDirectoryPath:applicationName];
	NSURL *anUrl = [NSURL fileURLWithPath:aPath isDirectory:YES];
	return anUrl;
}

+ (NSString *)cd_applicationDocumentsDirectoryPath
{	
	NSError *error;
	NSFileManager *fm = [[self alloc] init];
	NSString *result =
	[fm cd_findOrCreateDirectory:NSDocumentDirectory
						inDomain:NSUserDomainMask
			 appendPathComponent:nil
						   error:&error];
	
	if (!result) {
		ALog(@"Unable to find or create application documents directory:\n%@", error);
	}
	return result;
}

+ (NSURL *)cd_applicationDocumentsDirectoryURL
{
	NSString *aPath = [self cd_applicationDocumentsDirectoryPath];
	NSURL *anUrl = [NSURL fileURLWithPath:aPath isDirectory:YES];
	return anUrl;
}

+ (NSString *)cd_applicationCacheDirectoryPath:(NSString *)applicationBundleId
{	
	NSError *error;
	NSFileManager *fm = [[self alloc] init];
	NSString *result =
	[fm cd_findOrCreateDirectory:NSCachesDirectory
						inDomain:NSUserDomainMask
			 appendPathComponent:applicationBundleId
						   error:&error];
	
	if (!result) {
		ALog(@"Unable to find or create application cache directory:\n%@", error);
	}
	return result;
}

+ (NSURL *)cd_applicationCacheDirectoryURL:(NSString *)applicationBundleId
{
	NSString *aPath = [self cd_applicationCacheDirectoryPath:applicationBundleId];
	NSURL *anUrl = [NSURL fileURLWithPath:aPath isDirectory:YES];
	return anUrl;
}


#pragma mark - Getting the Path or URL to Directories
- (NSString *)cd_findOrCreateDirectory:(NSSearchPathDirectory)searchPathDirectory
							  inDomain:(NSSearchPathDomainMask)domainMask
				   appendPathComponent:(NSString *)appendComponent
								 error:(NSError **)errorOut
{
	//
	// Search for the path
	//
	NSArray* paths = NSSearchPathForDirectoriesInDomains(
														 searchPathDirectory,
														 domainMask,
														 YES);
	if ([paths count] == 0) {
		if (errorOut) {
			NSDictionary *userInfo =
			[NSDictionary dictionaryWithObjectsAndKeys:
			 NSLocalizedStringFromTable(
										@"DIR_LOCATION_NO_PATH_FOR_DIR_IN_DOMAIN",
										@"Errors",
										@"No path found for directory in domain."),
			 NSLocalizedDescriptionKey,
			 [NSNumber numberWithInteger:searchPathDirectory],
			 @"NSSearchPathDirectory",
			 [NSNumber numberWithInteger:domainMask],
			 @"NSSearchPathDomainMask",
			 nil];
			*errorOut =
			[NSError 
			 errorWithDomain:kDirectoryLocationDomain
			 code:kDirectoryLocationErrorNoPathFound
			 userInfo:userInfo];
		}
		return nil;
	}
	
	//
	// Normally only need the first path returned
	//
	NSString *resolvedPath = [paths objectAtIndex:0];
	
	//
	// Append the extra path component
	//
	if (appendComponent) {
		resolvedPath = [resolvedPath
						stringByAppendingPathComponent:appendComponent];
	}
	
	//
	// Check if the path exists
	//
	BOOL exists;
	BOOL isDirectory;
	exists = [self
			  fileExistsAtPath:resolvedPath
			  isDirectory:&isDirectory];
	if (!exists || !isDirectory) {
		if (exists) {
			if (errorOut) {
				NSDictionary *userInfo =
				[NSDictionary dictionaryWithObjectsAndKeys:
				 NSLocalizedStringFromTable(
											@"DIR_LOCATION_FILE_EXISTS_AT_REQUESTED_DIR_LOCATION",
											@"Errors",
											@"File exists at requested directory location."
											),
				 NSLocalizedDescriptionKey,
				 [NSNumber numberWithInteger:searchPathDirectory],
				 @"NSSearchPathDirectory",
				 [NSNumber numberWithInteger:domainMask],
				 @"NSSearchPathDomainMask",
				 nil];
				*errorOut =
				[NSError 
				 errorWithDomain:kDirectoryLocationDomain
				 code:kDirectoryLocationErrorFileExistsAtLocation
				 userInfo:userInfo];
			}
			return nil;
		}
		
		//
		// Create the path if it doesn't exist
		//
		NSError *error = nil;
		BOOL success = [self
						createDirectoryAtPath:resolvedPath
						withIntermediateDirectories:YES
						attributes:nil
						error:&error];
		if (!success) {
			if (errorOut) {
				*errorOut = error;
			}
			return nil;
		}
	}
	
	if (errorOut) {
		*errorOut = nil;
	}
	return resolvedPath;
}

@end
