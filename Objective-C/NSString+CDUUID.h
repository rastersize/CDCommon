//
//  NSString+CDUUID.h
//
//  Created by Aron Cedercrantz on 31/03/11.
//  Copyright 2011 Aron Cedercrantz. All rights reserved.
//

#import <Foundation/Foundation.h>


/**
 * A category to the `NSString` adding the ability to generate `NSString`
 * instances containing an UUID string.
 */
@interface NSString (CDUUID)

/**
 * Returns a newly generated UUID string.
 *
 * @return A string containing a newly generated UUID string.
 */
+ (NSString *)stringWithUUID;

@end
