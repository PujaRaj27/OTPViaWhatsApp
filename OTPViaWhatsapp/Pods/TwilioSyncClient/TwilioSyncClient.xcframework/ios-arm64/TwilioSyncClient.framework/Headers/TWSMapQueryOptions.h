//
//  TWSMapQueryOptions.h
//  Twilio Sync Client
//
//  Copyright (c) Twilio, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <TwilioSyncClient/TWSConstants.h>

/**
 Options passed while querying Map objects within Sync specifying
 query parameters and result set position and sorting.
 */
__attribute__((visibility("default")))
@interface TWSMapQueryOptions : NSObject

/** The starting position for the query. */
@property (readonly, nonnull) NSString *startPosition;

/** The ordering of the query. */
@property (readonly) TWSQueryOrder queryOrder;

/** The maximum size of the page returned by the query. */
@property (readonly) NSUInteger pageSize;

/**
 Specifies the initial position of the query.  Results will be inclusive of the item as this
 position, if specified and if it exists.
 
 @param startPosition The starting map key position for the query.
 @return This object for optional method chaining.
 */
- (nonnull instancetype)withStartPosition:(nonnull NSString *)startPosition;

/**
 Specifies the ordering (i.e. direction) of the query.  If no starting position is provided,
 ascending will execute the query from beginning and descending will execute the query from the end.
 
 @param queryOrder The ordering of the query.
 @return This object for optional method chaining.
 */
- (nonnull instancetype)withQueryOrder:(TWSQueryOrder)queryOrder;

/**
 Specifies the maximum size of the page returned by the query. The page may contain less items when
 approaching the end of collection.
 
 @param pageSize The maximum size of the page returned by the query.
 @return This object for optional method chaining.
 */
- (nonnull instancetype)withPageSize:(NSUInteger)pageSize;

@end
