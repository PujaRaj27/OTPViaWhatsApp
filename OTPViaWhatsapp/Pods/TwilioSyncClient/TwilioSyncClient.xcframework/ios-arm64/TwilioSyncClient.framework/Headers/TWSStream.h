//
//  TWSStream.h
//  Twilio Sync Client
//
//  Copyright (c) Twilio, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <TwilioSyncClient/TWSConstants.h>
#import <TwilioSyncClient/TWSStreamMessage.h>
#import <TwilioSyncClient/TWSEventContext.h>

@protocol TWSStreamDelegate;
@class TWSError;

/** Interface for Sync Pub-sub messaging primitive. 
 
 Message Stream is a Sync primitive for real-time pub-sub messaging. 
 Stream Messages are not persisted, they exist only in transit, and 
 will be dropped if (due to congestion or network anomalies) they 
 cannot be delivered promptly.
 */
__attribute__((visibility("default")))
@interface TWSStream : NSObject

/** An immutable system-assigned identifier of this Message Stream. */
@property (readonly, nonnull) NSString *sid;

/** An optional unique name for this stream, assigned at creation time. */
@property (readonly, nullable) NSString *uniqueName;

/** Publish a new message to this message stream.
 
 @param data Contains the payload of the dispatched message. Maximum size in serialized JSON: 4KB.
 @param completion Completion block that will specify the result of the operation and the unique message identifier if the operation is successful.
 */
- (void)publishMessageWithData:(nonnull TWSData *)data
                    completion:(nullable TWSStreamMessageCompletion)completion;

/**
 Set time to live for stream object in seconds.
 
 This TTL specifies the minimum time the Stream will live,
 sometime soon after this time the object will be deleted.
 
 If time to live is not specified, object lives infinitely long.
 
 TTL could be used in order to auto-recycle old unused objects,
 but it is not recommended to build some app logic like timers using ttl.
 
 @param ttl Time to live in seconds from now or TWSDurationInfinity to indicate no expiry.
 @param completion Completion block that will specify the result of the operation.
 */
- (void)setTtl:(TWSDuration)ttl
    completion:(nullable TWSCompletion)completion;

/** Remove the stream from the system, deleting it.
 
 @param completion Completion block that will specify the result of the operation.
 */
- (void)removeStreamWithCompletion:(nullable TWSCompletion)completion;

@end

/** The delegate delivers events that are fired by the Message Stream as a result of asynchronous completion of locally invoked methods, or any remote operations triggered by other actors on the same Stream. */
__attribute__((visibility("default")))
@protocol TWSStreamDelegate<NSObject>
@optional
/** Called when the message stream is opened or created.
 
 @param stream The reference to the message stream.
 */
- (void)onStreamOpened:(nonnull TWSStream *)stream;

/** Called when the stream is removed.
 
 @param stream The reference to the message stream.
 @param eventContext Context for this event.
 */
- (void)onStream:(nonnull TWSStream *)stream removedWithEventContext:(nonnull TWSEventContext *)eventContext;

/** Called when the stream message is published, either as a result of a local operation or remotely.
 
 @param stream The reference to the message stream.
 @param message The published message.
 @param eventContext Context for this event.
 */
- (void)onStream:(nonnull TWSStream *)stream messagePublished:(nonnull TWSStreamMessage *)message eventContext:(nonnull TWSEventContext *)eventContext;

/** Called when an error occurs.

 This event is fired whenever any Message Stream errors occur, typically resulting
 from a locally requested operation.  Notable error conditions include stream being
 non-existent, inaccessible or message publications rate being too high.
 
 @param stream The reference to the message stream.
 @param error The error encountered.  The error object will include the error status code, extended error code and and error message.
 */
- (void)onStream:(nonnull TWSStream *)stream errorOccurred:(nonnull TWSError *)error;

@end
