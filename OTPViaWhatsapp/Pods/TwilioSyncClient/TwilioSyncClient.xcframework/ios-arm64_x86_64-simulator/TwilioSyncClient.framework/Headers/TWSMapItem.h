//
//  TWSMapItem.h
//  Twilio Sync Client
//
//  Copyright (c) Twilio, Inc. All rights reserved.
//

#import <TwilioSyncClient/TWSConstants.h>

/**
 An item contained within a map.
 */
__attribute__((visibility("default")))
@interface TWSMapItem : NSObject

/** The key of this map item. */
@property (readonly, nonnull) NSString *key;

/** The snapshot of the map item's current data. */
@property (readonly, nonnull) TWSData *data;

/** The date this map item was last updated. */
@property (readonly, nullable) NSDate *dateUpdated;

@end
