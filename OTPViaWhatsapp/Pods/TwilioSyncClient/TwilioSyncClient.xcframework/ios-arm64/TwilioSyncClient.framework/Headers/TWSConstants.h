//
//  TWSConstants.h
//  Twilio Sync Client
//
//  Copyright (c) Twilio, Inc. All rights reserved.
//

#import <TwilioSyncClient/TWSResult.h>

@class TwilioSyncClient;
@class TWSDocument;
@class TWSList;
@class TWSListItem;
@class TWSListPaginator;
@class TWSMap;
@class TWSMapItem;
@class TWSMapPaginator;
@class TWSStream;

/** Immutable representation of a data item. */
typedef NSDictionary<NSString *, id> TWSData;

/** Mutable representation of a data item. */
typedef NSMutableDictionary<NSString *, id> TWSMutableData;

/** Type for item indexes within Sync. */
typedef long long TWSItemIndex;

/** Type for durations, for example ttl, for Sync. */
typedef unsigned int TWSDuration;

/** Duration constant indicating an infinite (never expires) duration. */
FOUNDATION_EXPORT TWSDuration const TWSDurationInfinity;

/** Client connection state. */
typedef NS_ENUM(NSInteger, TWSClientConnectionState) {
    TWSClientConnectionStateUnknown,        ///< Client connection state is not yet known.
    TWSClientConnectionStateDisconnected,   ///< Client is offline and no connection attempt in process.
    TWSClientConnectionStateConnected,      ///< Client is online and ready.
    TWSClientConnectionStateConnecting,     ///< Client is offline and connection attempt is in process.
    TWSClientConnectionStateDenied,         ///< Client connection is denied because of invalid token.
    TWSClientConnectionStateError,          ///< Client connection is in the erroneous state.
    TWSClientConnectionStateFatalError      ///< Client connection is rejected and customer action is required.
};

/** List and Map contents synchronization strategy. */
typedef NS_ENUM(NSInteger, TWSSynchronizationStrategy) {
    TWSSynchronizationStrategyDefault,      ///< Fetch map and list contents when requested.
    TWSSynchronizationStrategyAggressive    ///< Pre-fetch map and list contents on entity open.
};

/** Enumeration indicating the client's logging level. */
typedef NS_ENUM(NSInteger, TWSLogLevel) {
    TWSLogLevelSilent = 0,       ///< Show no errors.
    TWSLogLevelFatal,            ///< Show fatal errors only.
    TWSLogLevelCritical,         ///< Show critical log messages as well as all Fatal log messages.
    TWSLogLevelWarning,          ///< Show warnings as well as all Critical log messages.
    TWSLogLevelInfo,             ///< Show informational messages as well as all Warning log messages.
    TWSLogLevelDebug,            ///< Show low-level debugging messages as well as all Info log messages.
    TWSLogLevelTrace             ///< Show low-level tracing messages as well as all Debug log messages.
};

/** Enumeration specifying the requested fetch order relative to the fromIndex or newest/oldest items. */
typedef NS_ENUM(NSInteger, TWSQueryOrder) {
    TWSQueryOrderAscending,      ///< Fetch items in ascending order from starting point.
    TWSQueryOrderDescending      ///< Fetch items in descending order from starting point.
};

/** Completion block which will indicate the TWSResult of the operation. */
typedef void (^TWSCompletion)(TWSResult * _Nonnull result);

/** Completion block which will indicate the TCHResult of the operation and your handle to the TwilioSyncClient instance. */
typedef void (^TWSTwilioClientCompletion)(TWSResult * _Nonnull result, TwilioSyncClient * _Nullable syncClient);

/** Completion block which will indicate the TWSResult of the operation and a document if successful. */
typedef void (^TWSDocumentCompletion)(TWSResult * _Nonnull result, TWSDocument * _Nullable document);

/** Completion block which will indicate the TWSResult of the operation and a list if successful. */
typedef void (^TWSListCompletion)(TWSResult * _Nonnull result, TWSList * _Nullable list);

/** Completion block which will indicate the TWSResult of the operation and a list item index if successful. */
typedef void (^TWSListItemIndexCompletion)(TWSResult * _Nonnull result, TWSItemIndex itemIndex);

/** Completion block which will indicate the TWSResult of the operation and a list item if successful. */
typedef void (^TWSListItemCompletion)(TWSResult * _Nonnull result, TWSListItem * _Nullable item);

/** Completion block which will indicate the TWSResult of the operation and the list paginator if successful. */
typedef void (^TWSListPaginatorCompletion)(TWSResult * _Nonnull result, TWSListPaginator * _Nullable paginator);

/** Completion block which will indicate the TWSResult of the operation and a map if successful. */
typedef void (^TWSMapCompletion)(TWSResult * _Nonnull result, TWSMap * _Nullable map);

/** Completion block which will indicate the TWSResult of the operation and a map item if successful. */
typedef void (^TWSMapItemCompletion)(TWSResult * _Nonnull result, TWSMapItem * _Nullable item);

/** Completion block which will indicate the TWSResult of the operation and the map paginator if successful. */
typedef void (^TWSMapPaginatorCompletion)(TWSResult * _Nonnull result, TWSMapPaginator * _Nullable paginator);

/** Completion block which will indicate the TWSResult of the operation and the data if successful. */
typedef void (^TWSDataCompletion)(TWSResult * _Nonnull result, TWSData * _Nullable newData);

/** Completion block which will indicate the TWSResult of the operation and a stream if successful. */
typedef void (^TWSStreamCompletion)(TWSResult * _Nonnull result, TWSStream * _Nullable stream);

/** Completion block which will indicate the TWSResult of the operation and a message SID if successful. */
typedef void (^TWSStreamMessageCompletion)(TWSResult * _Nonnull result, NSString * _Nullable messageSID);

/** Mutator to modify a block of TWSData, may be called multiple times if a conflict is encountered on save.
 The mutator you specify will be called with the current value of the data.  In the event of
 a remote update occurring prior to the successful save of the new data, your mutator may be called multiple times
 before being committed.  You can either return an updated TWSMutableData reference or nil to abort the modification.
  */
typedef TWSMutableData * _Nullable (^TWSDataMutator)(TWSMutableData * _Nullable currentData);

/** The Twilio Sync error domain used as NSError's 'domain'. */
FOUNDATION_EXPORT NSString * _Nonnull const TWSErrorDomain;

/** The errorCode specified when an error client side occurs without another specific error code. */
FOUNDATION_EXPORT NSInteger const TWSErrorGeneric;

/** The userInfo key for the error message, if any. */
FOUNDATION_EXPORT NSString * _Nonnull const TWSErrorMsgKey;

/** The userInfo key for the error status, if any. */
FOUNDATION_EXPORT NSString * _Nonnull const TWSErrorStatus;
