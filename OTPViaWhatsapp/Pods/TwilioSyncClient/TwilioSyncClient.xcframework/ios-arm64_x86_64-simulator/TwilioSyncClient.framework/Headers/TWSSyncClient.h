//
//  TwilioSyncClient.h
//  Twilio Sync Client
//
//  Copyright (c) Twilio, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <TwilioSyncClient/TWSConstants.h>
#import <TwilioSyncClient/TWSOpenOptions.h>
#import <TwilioSyncClient/TWSDocument.h>
#import <TwilioSyncClient/TWSList.h>
#import <TwilioSyncClient/TWSMap.h>
#import <TwilioSyncClient/TWSStream.h>

@class TwilioSyncClientProperties;
@protocol TwilioSyncClientDelegate;

/** Represents a Sync client connection to Twilio. */
__attribute__((visibility("default")))
@interface TwilioSyncClient : NSObject

/** The logging level for the client. */
@property (class, readonly) TWSLogLevel logLevel;

/** The name of the SDK for diagnostic purposes. */
@property (class, readonly, nonnull) NSString *sdkName;

/** The version of the SDK. */
@property (class, readonly, nonnull) NSString *sdkVersion;

/** The sync client delegate. */
@property (nonatomic, weak, nullable) id<TwilioSyncClientDelegate> delegate;

/** The client's current connection state. */
@property (nonatomic, assign, readonly) TWSClientConnectionState connectionState;

/**
 Queue all completions and events would fire from.
 If not set here or in properties on a client creation, main queue would be used.
 */
@property (nonatomic, readwrite, nullable) dispatch_queue_t dispatchQueue;

/** Initialize a new Sync client instance with a token manager.
 
 @param token The client access token to use when communicating with Twilio.
 @param properties The initialization parameter for the Sync client.
 @param delegate Delegate conforming to TwilioSyncClientDelegate for Sync client lifecycle notifications.
 @param completion Completion block that will specify the result of the operation and a reference to the new TwilioSyncClient.
 */
+ (void)syncClientWithToken:(nonnull NSString *)token
                 properties:(nullable TwilioSyncClientProperties *)properties
                   delegate:(nullable id<TwilioSyncClientDelegate>)delegate
                 completion:(nonnull TWSTwilioClientCompletion)completion;

/* Direct instantiation is not supported, please use convenience method. */
- (nonnull instancetype) init __attribute__((unavailable("please use syncClientWithToken:properties:delegate: to construct instead")));

/** Sets the logging level for the client.
 
 @param logLevel The new log level.
 */
+ (void)setLogLevel:(TWSLogLevel)logLevel;

/** Updates the access token currently being used by the client.
 
 @param token The updated client access token to use when communicating with Twilio.
 @param completion Completion block that will specify the result of the operation.
 */
- (void)updateToken:(nonnull NSString *)token
         completion:(nonnull TWSCompletion)completion;

/** Cleanly shut down the sync client when you are done with it. */
- (void)shutdown;

/** Open or create a document.
 
 @param options An instance of TSOptions which specify the document to open or create.
 @param delegate Delegate for operations related to this document.
 @param completion Completion block that will specify the result of the operation and a reference to the document.
 */
- (void)openDocumentWithOptions:(nonnull TWSOpenOptions *)options
                       delegate:(nonnull id<TWSDocumentDelegate>)delegate
                     completion:(nonnull TWSDocumentCompletion)completion;

/** Open or create a list.
 
 @param options An instance of TSOptions which specify the list to open or create.
 @param delegate Delegate for operations related to this list.
 @param completion Completion block that will specify the result of the operation and a reference to the list.
 */
- (void)openListWithOptions:(nonnull TWSOpenOptions *)options
                   delegate:(nonnull id<TWSListDelegate>)delegate
                 completion:(nonnull TWSListCompletion)completion;


/** Open or create a map.
 
 @param options An instance of TSOptions which specify the map to open or create.
 @param delegate Delegate for operations related to this map.
 @param completion Completion block that will specify the result of the operation and a reference to the map.
 */
- (void)openMapWithOptions:(nonnull TWSOpenOptions *)options
                  delegate:(nonnull id<TWSMapDelegate>)delegate
                completion:(nonnull TWSMapCompletion)completion;

/** Open or create a stream.
 
 @param options An instance of TSOptions which specify the stream to open or create.
 @param delegate Delegate for operations related to this stream.
 @param completion Completion block that will specify the result of the operation and a reference to the stream.
 */
- (void)openStreamWithOptions:(nonnull TWSOpenOptions *)options
                     delegate:(nonnull id<TWSStreamDelegate>)delegate
                   completion:(nonnull TWSStreamCompletion)completion;
@end

#pragma mark -

/** The initialization parameter for the Sync client. */
__attribute__((visibility("default")))
@interface TwilioSyncClientProperties : NSObject

/** The region of Sync to connect to, defaults to 'us1'.  Instanaces exist in specific regions, so this should only be changed if needed. */
@property (nonatomic, copy, nonnull) NSString *region;

/**
 Defer certificate trust decisions to the OS, overriding the default of
 certificate pinning for Twilio back-end connections.

 Twilio client SDKs utilize certificate pinning to prevent man-in-the-middle attacks
 against your connections to our services. Customers in certain very specific
 environments may need to opt-out of this if custom certificate authorities must
 be allowed to intentionally intercept communications for security or policy reasons.

 Setting this property to `true` for a Sync Client instance will defer to iOS to
 establish whether or not a given connection is providing valid and trusted TLS certificates.

 Keeping this property at its default value of `false` allows the Twilio client SDK
 to determine trust when communicating with our servers.

 The default value is `false`.
 */
@property (nonatomic, readwrite) BOOL deferCertificateTrustToPlatform;

/**
 If useProxy flag is `true` TwilioSyncClient will try to read and apply system proxy settings.
 If this flag is `false` all proxy settings will be ignored and direct connection will be used.

 The default value is `false`.
 */
@property (nonatomic, readwrite) BOOL useProxy;

/**
 Queue all completions and events would fire from. If not set main queue would be used.
 */
@property (nonatomic, readwrite, nullable) dispatch_queue_t dispatchQueue;

@end

#pragma mark -

/** This protocol declares the Sync client delegate methods. */
__attribute__((visibility("default")))
@protocol TwilioSyncClientDelegate <NSObject>
@optional
/** Called when the client connection state changes.
 
 @param client The sync client.
 @param state The current connection state of the client.
 */
- (void)syncClient:(nonnull TwilioSyncClient *)client connectionStateChanged:(TWSClientConnectionState)state;

/**
 Called when the client's token has expired.
 
 In response, your delegate should generate a new token and call
 `syncClient:updateToken:completion:` immediately as connection to
 the server has been lost.
 
 @param client The sync client.
 */
- (void)syncClientTokenExpired:(nonnull TwilioSyncClient *)client;

/**
 Called when the client's token will expire soon.
 
 In response, your delegate should generate a new token and call
 `syncClient:updateToken:completion:` as soon as possible.
 
 @param client The sync client.
 */
- (void)syncClientTokenWillExpire:(nonnull TwilioSyncClient *)client;

@end
