//
//  TWSDocumentMetadata.h
//  Twilio Sync Client
//
//  Copyright (c) Twilio, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

/** Metadata associated with the Document. */
__attribute__((visibility("default")))
@interface TWSDocumentMetadata : NSObject

/**
 Optionally specify TTL for the Document.
 
 TTL specifies the minimum time the Document will live,
 sometime soon after this time the object will be deleted.

 If time to live is not specified, object lives infinitely long.

 TTL could be used in order to auto-recycle old unused objects,
 but it is not recommended to build some app logic like timers using ttl.

 @param ttl Time to live in seconds from now or TWSDurationInfinity to indicate no expiry.
 @return Metadata object with given ttl.
*/
+ (nullable TWSDocumentMetadata *)withTtl:(int)ttl;

@end
