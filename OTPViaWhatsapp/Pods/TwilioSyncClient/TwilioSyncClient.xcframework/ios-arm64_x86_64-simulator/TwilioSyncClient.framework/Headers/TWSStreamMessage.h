//
//  TWSStreamMessage.h
//  Twilio Sync Client
//
//  Copyright (c) Twilio, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <TwilioSyncClient/TWSConstants.h>

/** A stream message. */
__attribute__((visibility("default")))
@interface TWSStreamMessage : NSObject

/** The unique identifier for this stream message. */
@property (readonly, nonnull) NSString *sid;

/** The data for this message. */
@property (readonly, nonnull) TWSData *data;

@end
