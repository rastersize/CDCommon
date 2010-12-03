//
//  CDCommon.m
//
//  Created by Aron Cedercrantz on 01/04/10.
//  Copyright 2010 Aron Cedercrantz. All rights reserved.
//

#import "CDCommon.h"


@implementation NSObject (CDIsEmpty)

- (BOOL)cdIsEmpty
{
    return (([self respondsToSelector:@selector(length)] &&
			 [self performSelector:@selector(length)] == 0) ||
			
			([self respondsToSelector:@selector(count)] &&
			 [self performSelector:@selector(count)] == 0));
}

@end
