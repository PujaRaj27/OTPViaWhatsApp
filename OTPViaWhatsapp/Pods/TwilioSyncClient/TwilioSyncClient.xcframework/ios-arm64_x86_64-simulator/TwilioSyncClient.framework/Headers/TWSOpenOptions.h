//
//  TWSOpenOptions.h
//  Twilio Sync Client
//
//  Copyright (c) Twilio, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <TwilioSyncClient/TWSConstants.h>

/** Options object specifying the open mode and parameters for a Sync entity. */
__attribute__((visibility("default")))
@interface TWSOpenOptions : NSObject

/** The SID or uniqueName of the entity for the operation. */
@property (readonly, nullable) NSString *sidOrUniqueName;

/** The synchronization strategy for the resultant entity. */
@property (readonly) TWSSynchronizationStrategy strategy;

/** The specified time to live, default is TWSDurationInfinity. */
@property (readonly) TWSDuration ttl;

/** Create a new entity with the uniqueName if provided, return an error if it exists already.
 If no uniqueName is specified, this operation will always succeed provided sufficient permissions.
 
 @param uniqueName The optional unique name for the new entity or nil if no uniqueName is desired.
 @return The new TWSOpenOptions object.
 */
+ (nonnull TWSOpenOptions *)createWithUniqueName:(nullable NSString *)uniqueName;

/** Create a new or open an existing new entity with the uniqueName provided.
 This operation will always succeed provided sufficient permissions.
 
 @param uniqueName The non-optional unique name to either retrieve or create if needed.
 @return The new TWSOpenOptions object.
 */
+ (nullable TWSOpenOptions *)withUniqueName:(nonnull NSString *)uniqueName;

/** Open an existing new entity with the SID or uniqueName provided.
 
 @param sidOrUniqueName The non-optional SID or unique name to retrieve.
 @return The new TWSOpenOptions object.
 */
+ (nullable TWSOpenOptions *)openWithSidOrUniqueName:(nonnull NSString *)sidOrUniqueName;

/** Optionally specifies the synchronization strategy in use for pre-fetching objects, the default is
 TWSSynchronizationStrategyDefault.
 
 @param strategy The synchronization strategy to use, see TWSSynchronizationStrategy.
 @return The updated TWSOpenOptions object.
 */
- (nonnull TWSOpenOptions *)synchronizationStrategy:(TWSSynchronizationStrategy)strategy;

/**
 Optionally specifies the time to live for the Sync object in seconds.

 This TTL specifies the minimum time the object will live,
 sometime soon after this time the object will be deleted.

 If time to live is not specified, object lives infinitely long.

 TTL could be used in order to auto-recycle old unused objects,
 but it is not recommended to build some app logic like timers using ttl.

 This setting works with all object types, however note that it is applicable only when creating an object.
 When (re)opening an existing object, new TTL is not applied, and instead an old setting is retained,
 in order to avoid unexpected read-only object change.

 @param ttl Time to live in seconds from now or TWSDurationInfinity to indicate no expiry.
 @return The updated TWSOpenOptions object.
 */
- (nonnull TWSOpenOptions *)ttl:(TWSDuration)ttl;

@end
