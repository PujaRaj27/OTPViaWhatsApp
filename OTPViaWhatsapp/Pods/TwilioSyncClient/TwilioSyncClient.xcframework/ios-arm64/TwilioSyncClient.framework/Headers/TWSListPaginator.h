//
//  TWSListPaginator.h
//  Twilio Sync Client
//
//  Copyright (c) Twilio, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <TwilioSyncClient/TWSConstants.h>

@class TWSListItem;

/** Paging interface to interact with list item query results.
 */
__attribute__((visibility("default")))
@interface TWSListPaginator : NSObject

/** Determine if there is a next page of results. */
@property (readonly) BOOL hasNextPage;

/** Determine if there is a previous page of results. */
@property (readonly) BOOL hasPreviousPage;

/** Obtain the list of items contained in this page of results. The order of items within the page is not guaranteed.
 
 @return An array of TWSListItem objects.
 */
- (nonnull NSArray<TWSListItem *> *)getItems;

/** Request the next page of results for this query, if one exists. The order of items within the page is not guaranteed.
 
 @param completion Completion block that will specify the result of the operation and a paginator for the new page of results.
 */
- (void)requestNextPageWithCompletion:(nonnull TWSListPaginatorCompletion)completion;

/** Request the previous page of results for this query, if one exists. The order of items within the page is not guaranteed.
 
 @param completion Completion block that will specify the result of the operation and a paginator for the new page of results.
 */
- (void)requestPreviousPageWithCompletion:(nonnull TWSListPaginatorCompletion)completion;

@end
