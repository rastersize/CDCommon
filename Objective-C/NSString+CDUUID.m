//
//  NSString+CDUUID.h
//
//  Created by Aron Cedercrantz on 31/03/11.
//  Copyright 2011 Aron Cedercrantz. All rights reserved.
//

#import "NSString+CDUUID.h"
#import "CDCommon.h"


CD_FIX_CATEGORY_BUG_QA1490(NSString_CDUUID)
@implementation NSString (CDUUID)

+ (NSString *)stringWithUUID
{
	CFUUIDRef uuidRef = CFUUIDCreate(nil);
	NSString *uuidString = (__bridge_transfer NSString *)CFUUIDCreateString(nil, uuidRef);
	CFRelease(uuidRef);
	
	return uuidString;
}

@end
