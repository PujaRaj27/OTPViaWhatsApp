//
//  TWSResult.h
//  Twilio Sync Client
//
//  Copyright (c) Twilio, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <TwilioSyncClient/TWSError.h>

/** Result class passed via completion blocks.  Contains a boolean property, isSuccessful, which
 indicates the result of the operation and an error object if the operation failed.
 */
__attribute__((visibility("default")))
@interface TWSResult : NSObject

/** The result's TWSError if the operation failed. */
@property (nonatomic, strong, readonly, nullable) TWSError *error;

/** Indicates the success or failure of the given operation. */
@property (nonatomic, readonly) BOOL isSuccessful;

@end
