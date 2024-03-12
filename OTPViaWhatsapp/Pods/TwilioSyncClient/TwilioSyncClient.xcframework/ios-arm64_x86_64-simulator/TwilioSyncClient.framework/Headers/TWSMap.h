//
//  TWSMap.h
//  Twilio Sync Client
//
//  Copyright (c) Twilio, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <TwilioSyncClient/TWSConstants.h>
#import <TwilioSyncClient/TWSMapItem.h>
#import <TwilioSyncClient/TWSMapItemMetadata.h>
#import <TwilioSyncClient/TWSMapQueryOptions.h>
#import <TwilioSyncClient/TWSEventContext.h>

@protocol TWSMapDelegate;
@class TWSError;

/** A map stores unordered JSON objects accessible via a developer defined key. */
__attribute__((visibility("default")))
@interface TWSMap : NSObject

/** The unique identifier for this map. */
@property (readonly, nonnull) NSString *sid;

/** The unique name for this map. */
@property (readonly, nullable) NSString *uniqueName;

/** The date when this map was last updated. */
@property (readonly, nullable) NSDate *dateUpdated;

/** Request the map item with the specified key.
 
 @param key The key of the item to retrieve.
 @param completion Completion block that will specify the result of the operation and the requested item if it exists.
 */
- (void)getItemWithKey:(nonnull NSString *)key
            completion:(nonnull TWSMapItemCompletion)completion;

/** Sets the item for the specified key.
 
 @param key The key of the item to set.
 @param data The new data.
 @param objectMetadata Optional metadata for the set item, currently only ttl.
 @param completion Completion block that will specify the result of the operation and the new item.
 */
- (void)setItemWithKey:(nonnull NSString *)key
                  data:(nonnull TWSData *)data
              metadata:(nullable TWSMapItemMetadata *)objectMetadata
            completion:(nullable TWSMapItemCompletion)completion;

/** Modify the MapItem's data in a conflict-friendly way.
 
 @param key The key of the item to mutate.
 @param mutator The mutator that you provide to modify the data passed in.
 @param objectMetadata Optional metadata for the mutated item, currently only ttl.
 @param completion Completion block that will specify the result of the operation and the updated item.
 */
- (void)mutateItemWithKey:(nonnull NSString *)key
                  mutator:(nonnull TWSDataMutator)mutator
                 metadata:(nullable TWSMapItemMetadata *)objectMetadata
               completion:(nullable TWSMapItemCompletion)completion;

/** Removes the MapItem with the specified key.
 
 @param key The key of the item to remove.
 @param completion Completion block that will specify the result of the operation.
 */
- (void)removeItemWithKey:(nonnull NSString *)key
               completion:(nullable TWSCompletion)completion;

/** Query the map's items with the requested parameters. The order of items within the page is not guaranteed.
 
 @param mapQueryOptions The options for the map query.
 @param completion Completion block that will specify the result of the operation and a paginator for this page of results.
 */
- (void)queryItemsWithOptions:(nonnull TWSMapQueryOptions *)mapQueryOptions
                   completion:(nonnull TWSMapPaginatorCompletion)completion;

/**
 Set time to live for map object in seconds.
 
 This TTL specifies the minimum time the Map will live,
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
 Set time to live for an item in map.

 TTL specifies the minimum time the Item will live,
 sometime soon after this time the object will be deleted.

 If time to live is not specified, object lives infinitely long.

 TTL could be used in order to auto-recycle old unused objects,
 but it is not recommended to build some app logic like timers using ttl.

 @param ttl Time to live in seconds from now or TWSDurationInfinity to indicate no expiry.
 @param key The key of item to set ttl for.
 @param completion Completion block that will specify the result of the operation.
 */
- (void)setTtl:(TWSDuration)ttl
forItemWithKey:(nonnull NSString *)key
    completion:(nullable TWSCompletion)completion;

/** Remove the map from the system, deleting it.
 
 @param completion Completion block that will specify the result of the operation.
 */
- (void)removeMapWithCompletion:(nullable TWSCompletion)completion;

@end

/** The delegate that will be called with lifecycle updates for the map. */
__attribute__((visibility("default")))
@protocol TWSMapDelegate<NSObject>
@optional

/** Called when the map referenced is opened.
 
 @param map The map.
 */
- (void)onMapOpened:(nonnull TWSMap *)map;

/** Called when a map item is added.
 
 @param map The map.
 @param item The added item.
 @param eventContext Context for this event.
 */
- (void)onMap:(nonnull TWSMap *)map
    itemAdded:(nonnull TWSMapItem *)item
 eventContext:(nonnull TWSEventContext *)eventContext;

/** Called when a map item is updated.
 
 @param map The map.
 @param item The updated item.
 @param previousItemData The data of the item before the change.
 @param eventContext Context for this event.
 */
- (void)onMap:(nonnull TWSMap *)map
  itemUpdated:(nonnull TWSMapItem *)item
previousItemData:(nonnull TWSData *)previousItemData
 eventContext:(nonnull TWSEventContext *)eventContext;

/** Called when the map item with the specified key is removed.
 
 @param map The map.
 @param itemKey The key of the removed item.
 @param previousItemData The data of the item before removing.
 @param eventContext Context for this event.
 */
- (void)onMap:(nonnull TWSMap *)map
itemRemovedWithKey:(nonnull NSString *)itemKey
previousItemData:(nonnull TWSData *)previousItemData
 eventContext:(nonnull TWSEventContext *)eventContext;

/** Called when the map is removed.
 
 @param map The map.
 @param eventContext Context for this event.
 */
- (void)onMapCollectionRemoved:(nonnull TWSMap *)map
                  eventContext:(nonnull TWSEventContext *)eventContext;

/** Called when an error occurs as a result of a local operation.
 
 @param map The map.
 @param error The error encountered.
 */
- (void)onMap:(nonnull TWSMap *)map errorOccurred:(nonnull TWSError *)error;

@end
