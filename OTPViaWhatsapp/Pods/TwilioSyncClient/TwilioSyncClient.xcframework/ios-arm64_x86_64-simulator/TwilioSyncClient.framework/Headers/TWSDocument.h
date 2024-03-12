//
//  TWSDocument.h
//  Twilio Sync Client
//
//  Copyright (c) Twilio, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <TwilioSyncClient/TWSConstants.h>
#import <TwilioSyncClient/TWSEventContext.h>
#import <TwilioSyncClient/TWSDocumentMetadata.h>

@protocol TWSDocumentDelegate;
@class TWSError;

/** A document is the simplest Sync primitive that encapsulates a single JSON encoded object. */
__attribute__((visibility("default")))
@interface TWSDocument : NSObject

/** The unique identifier for this document. */
@property (readonly, nonnull) NSString *sid;

/** The unique name for this document. */
@property (readonly, nullable) NSString *uniqueName;

/** The date when this document was last updated. */
@property (readonly, nullable) NSDate *dateUpdated;

/** Obtain a snapshot of the document's current data. */
@property (readonly, nonnull) TWSData *data;

/** Update the value of the document's data.
 
 @param data The new data.
 @param objectMetadata Optional metadata for the updated document, currently only ttl.
 @param completion Completion block that will specify the result of the operation and the updated value of the data.
 */
- (void)setData:(nonnull TWSData *)data
       metadata:(nullable TWSDocumentMetadata *)objectMetadata
     completion:(nullable TWSDataCompletion)completion;

/** Modify the Document's data in a conflict-friendly way.
 
 @param mutator The mutator that you provide to modify the data passed in.
 @param objectMetadata Optional metadata for the updated document, currently only ttl.
 @param completion Completion block that will specify the result of the operation and the updated value of the data.
 */
- (void)mutateDataWith:(nonnull TWSDataMutator)mutator
              metadata:(nullable TWSDocumentMetadata *)objectMetadata
            completion:(nullable TWSDataCompletion)completion;

/**
 Set time to live for document object in seconds.
 
 This TTL specifies the minimum time the Document will live,
 sometime soon after this time the object will be deleted.
 
 If time to live is not specified, object lives infinitely long.
 
 TTL could be used in order to auto-recycle old unused objects,
 but it is not recommended to build some app logic like timers using ttl.
 
 @param ttl Time to live in seconds from now or TWSDurationInfinity to indicate no expiry.
 @param completion Completion block that will specify the result of the operation.
 */
- (void)setTtl:(TWSDuration)ttl
    completion:(nullable TWSCompletion)completion;

/** Remove the document from the system, deleting it.
 
 @param completion Completion block that will specify the result of the operation.
 */
- (void)removeDocumentWithCompletion:(nullable TWSCompletion)completion;

@end

/** The delegate that will be called with lifecycle updates for the document. */
__attribute__((visibility("default")))
@protocol TWSDocumentDelegate<NSObject>
@optional
/** Called when the document referenced is opened.
 
 @param document The document.
 */
- (void)onDocumentOpened:(nonnull TWSDocument *)document;

/** Called when the document is removed as a result of a local operation.
 
 @param document The document.
 @param previousData The data of the document before removing.
 @param eventContext Context for this event.
 */
- (void)onDocumentRemoved:(nonnull TWSDocument *)document
             previousData:(nonnull TWSData *)previousData
             eventContext:(nonnull TWSEventContext *)eventContext;

/** Called when the document is modified.
 
 @param document The document.
 @param data The updated data for the document.
 @param previousData The data of the document before the change.
 @param eventContext Context for this event.
 */
- (void)onDocument:(nonnull TWSDocument *)document
           updated:(nonnull TWSData *)data
      previousData:(nonnull TWSData *)previousData
      eventContext:(nonnull TWSEventContext *)eventContext;

/** Called when an error occurs as a result of a local operation.
 
 @param document The document.
 @param error The error encountered.
 */
- (void)onDocument:(nonnull TWSDocument *)document errorOccurred:(nonnull TWSError *)error;

@end
