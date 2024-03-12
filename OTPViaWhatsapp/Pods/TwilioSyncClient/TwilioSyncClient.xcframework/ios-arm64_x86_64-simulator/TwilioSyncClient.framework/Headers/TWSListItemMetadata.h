//
//  TWSListItemMetadata.h
//  Twilio Sync Client
//
//  Copyright (c) Twilio, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

/** Metadata associated with the List Item. */
__attribute__((visibility("default")))
@interface TWSListItemMetadata : NSObject

/**
 Optionally specify TTL for the List Item.

 TTL specifies the minimum time the List Item will live,
 sometime soon after this time the object will be deleted.

 If time to live is not specified, object lives infinitely long.

 TTL could be used in order to auto-recycle old unused objects,
 but it is not recommended to build some app logic like timers using ttl.

 @param ttl Time to live in seconds from now or TWSDurationInfinity to indicate no expiry.
 @return Metadata object with given ttl.
 */
+ (nullable TWSListItemMetadata *)withTtl:(int)ttl;

@end
