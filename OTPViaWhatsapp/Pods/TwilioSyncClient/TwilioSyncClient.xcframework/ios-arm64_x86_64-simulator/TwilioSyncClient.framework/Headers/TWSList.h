//
//  TWSList.h
//  Twilio Sync Client
//
//  Copyright (c) Twilio, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <TwilioSyncClient/TWSConstants.h>
#import <TwilioSyncClient/TWSEventContext.h>
#import <TwilioSyncClient/TWSListItem.h>
#import <TwilioSyncClient/TWSListItemMetadata.h>
#import <TwilioSyncClient/TWSListQueryOptions.h>

@protocol TWSListDelegate;
@class TWSError;

/** An ordered list of data within Sync. */
__attribute__((visibility("default")))
@interface TWSList : NSObject

/** The unique identifier for this list. */
@property (readonly, nonnull) NSString *sid;

/** The unique name for this list. */
@property (readonly, nullable) NSString *uniqueName;

/** The date when this list was last updated. */
@property (readonly, nullable) NSDate *dateUpdated;

/** Adds a new item to the list with the provided data.

 @param data The new data.
 @param objectMetadata Optional metadata for the added item, currently only ttl.
 @param completion Completion block that will specify the result of the operation and the newly added item.
 */
- (void)addItemWithData:(nonnull TWSData *)data
               metadata:(nullable TWSListItemMetadata *)objectMetadata
             completion:(nullable TWSListItemCompletion)completion;

/** Request the list item at the specified index.
 
 @param index The index of the item to retrieve.
 @param completion Completion block that will specify the result of the operation and the requested item if it exists.
 */
- (void)getItemAtIndex:(TWSItemIndex)index
            completion:(nonnull TWSListItemCompletion)completion;

/** Sets the item at the specified index.
 
 @param index The index of the existing item to set.
 @param data The new data.
 @param objectMetadata Optional metadata for the updated item, currently only ttl.
 @param completion Completion block that will specify the result of the operation and the modified item.
 */
- (void)setItemAtIndex:(TWSItemIndex)index
                  data:(nonnull TWSData *)data
              metadata:(nullable TWSListItemMetadata *)objectMetadata
            completion:(nullable TWSListItemCompletion)completion;

/** Modify the ListItem's data in a conflict-friendly way.
 
 @param index The index of the existing item to mutate.
 @param mutator The mutator that you provide to modify the data passed in.
 @param objectMetadata Optional metadata for the mutated item, currently only ttl.
 @param completion Completion block that will specify the result of the operation and the modified item.
 */
- (void)mutateItemAtIndex:(TWSItemIndex)index
                  mutator:(nonnull TWSDataMutator)mutator
                 metadata:(nullable TWSListItemMetadata *)objectMetadata
               completion:(nullable TWSListItemCompletion)completion;

/** Removes the ListItem at the specified index.
 
 @param index The index of the item to remove.
 @param completion Completion block that will specify the result of the operation.
 */
- (void)removeItemAtIndex:(TWSItemIndex)index
               completion:(nullable TWSCompletion)completion;

/** Query the list's items with the requested parameters. The order of items within the page is not guaranteed.
 
 @param listQueryOptions The options for the list query.
 @param completion Completion block that will specify the result of the operation and a paginator for this page of results.
 */
- (void)queryItemsWithOptions:(nonnull TWSListQueryOptions *)listQueryOptions
                   completion:(nonnull TWSListPaginatorCompletion)completion;

/**
 Set time to live for list object in seconds.
 
 This TTL specifies the minimum time the List will live,
 sometime soon after this time the object will be deleted.
 
 If time to live is not specified, object lives infinitely long.
 
 TTL could be used in order to auto-recycle old unused objects,
 but it is not recommended to build some app logic like timers using ttl.
 
 @param ttl Time to live in seconds from now or TWSDurationInfinity to indicate no expiry.
 @param completion Completion block that will specify the result of the operation.
 */
- (void)setTtl:(TWSDuration)ttl
    completion:(nullable TWSCompletion)completion;

/**
 Set time to live for an item in list.

 TTL specifies the minimum time the Item will live,
 sometime soon after this time the object will be deleted.

 If time to live is not specified, object lives infinitely long.

 TTL could be used in order to auto-recycle old unused objects,
 but it is not recommended to build some app logic like timers using ttl.

 @param ttl Time to live in seconds from now or TWSDurationInfinity to indicate no expiry.
 @param index Index of item to set ttl for.
 @param completion Completion block that will specify the result of the operation.
 */
- (void)setTtl:(TWSDuration)ttl
forItemAtIndex:(TWSItemIndex)index
    completion:(nullable TWSCompletion)completion;

/** Remove the list from the system, deleting it.
 
 @param completion Completion block that will specify the result of the operation.
 */
- (void)removeListWithCompletion:(nullable TWSCompletion)completion;

@end

/** The delegate that will be called with lifecycle updates for the list. */
__attribute__((visibility("default")))
@protocol TWSListDelegate<NSObject>
@optional

/** Called when the list referenced is opened.
 
 @param list The list.
 */
- (void)onListOpened:(nonnull TWSList *)list;

/** Called when a list item is added.
 
 @param list The list.
 @param item The added item.
 @param eventContext Context for this event.
 */
- (void)onList:(nonnull TWSList *)list
     itemAdded:(nonnull TWSListItem *)item
  eventContext:(nonnull TWSEventContext *)eventContext;

/** Called when the list item at the specified index is removed.
 
 @param list The list.
 @param itemIndex The index of the removed item.
 @param previousItemData The data of the item before removing.
 @param eventContext Context for this event.
 */
- (void)onList:(nonnull TWSList *)list
itemRemovedWithIndex:(TWSItemIndex)itemIndex
previousItemData:(nonnull TWSData *)previousItemData
  eventContext:(nonnull TWSEventContext *)eventContext;

/** Called when the list item at the specified index is updated.
 
 @param list The list.
 @param item The updated item.
 @param previousItemData The data of the item before the change.
 @param eventContext Context for this event.
 */
- (void)onList:(nonnull TWSList *)list
   itemUpdated:(nonnull TWSListItem *)item
previousItemData:(nonnull TWSData *)previousItemData
  eventContext:(nonnull TWSEventContext *)eventContext;

/** Called when the list is removed.
 
 @param list The list.
 @param eventContext Context for this event.
 */
- (void)onList:(nonnull TWSList *)list collectionRemovedWithEventContext:(nonnull TWSEventContext *)eventContext;

/** Called when an error occurs.
 
 @param list The list.
 @param error The error encountered.
 */
- (void)onList:(nonnull TWSList *)list errorOccurred:(nonnull TWSError *)error;

@end
