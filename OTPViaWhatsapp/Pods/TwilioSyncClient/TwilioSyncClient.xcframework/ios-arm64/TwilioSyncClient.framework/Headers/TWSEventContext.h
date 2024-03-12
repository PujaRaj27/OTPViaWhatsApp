//
//  TWSEventContext.h
//  Twilio Sync Client
//
//  Copyright (c) Twilio, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

/** Contextual information related to the delegate called. */
__attribute__((visibility("default")))
@interface TWSEventContext : NSObject

/** Boolean flag to indicate whether this delegate call is in response to a locally initiated operations or a remote operation.
 
 A `true` return value here indicates the callback is in response to an operation this client requested.
 
 A `false` return value indicates the operation was remotely initiated.
 */
@property (readonly) BOOL isLocal;

@end
