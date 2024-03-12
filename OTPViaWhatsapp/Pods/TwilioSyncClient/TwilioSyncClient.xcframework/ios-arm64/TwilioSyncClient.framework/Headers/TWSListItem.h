//
//  TWSListItem.h
//  Twilio Sync Client
//
//  Copyright (c) Twilio, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <TwilioSyncClient/TWSConstants.h>

/**
 An item contained within a List.
 */
__attribute__((visibility("default")))
@interface TWSListItem : NSObject

/** The index of this list item. */
@property (readonly) TWSItemIndex index;

/** The snapshot of the list item's current data. */
@property (readonly, nonnull) TWSData *data;

/** The date this list item was last updated. */
@property (readonly, nullable) NSDate *dateUpdated;

@end
