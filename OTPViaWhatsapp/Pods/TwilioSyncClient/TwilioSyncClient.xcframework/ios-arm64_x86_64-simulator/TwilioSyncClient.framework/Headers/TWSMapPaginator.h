//
//  TWSMapPaginator.h
//  Twilio Sync Client
//
//  Copyright (c) Twilio, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <TwilioSyncClient/TWSConstants.h>

@class TWSMapItem;

/** Paging interface to interact with map item query results.
 */
__attribute__((visibility("default")))
@interface TWSMapPaginator : NSObject

/** BOOL indicating the presence of a next page of results. */
@property (readonly) BOOL hasNextPage;

/** BOOL indicating the presence of a previous page of results. */
@property (readonly) BOOL hasPreviousPage;

/** Obtain the list of items contained in this page of results. The order of items within the page is not guaranteed.
 
 @return An array of TWSMapItem objects.
 */
- (nonnull NSArray<TWSMapItem *> *)getItems;

/** Request the next page of results for this query, if one exists. The order of items within the page is not guaranteed.
 
 @param completion Completion block that will specify the result of the operation and a paginator for the new page of results.
 */
- (void)requestNextPageWithCompletion:(nonnull TWSMapPaginatorCompletion)completion;

/** Request the previous page of results for this query, if one exists. The order of items within the page is not guaranteed.
 
 @param completion Completion block that will specify the result of the operation and a paginator for the new page of results.
 */
- (void)requestPreviousPageWithCompletion:(nonnull TWSMapPaginatorCompletion)completion;

@end
