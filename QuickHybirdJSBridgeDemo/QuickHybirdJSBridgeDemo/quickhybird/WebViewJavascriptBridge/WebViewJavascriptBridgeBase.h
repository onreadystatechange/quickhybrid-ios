//
//  WebViewJavascriptBridgeBase.h
//
//  Created by @LokiMeyburg on 10/15/14.
//  Copyright (c) 2014 @LokiMeyburg. All rights reserved.
//
// #define kQueueHasMessage      @"__WVJB_QUEUE_MESSAGE__"
#import <Foundation/Foundation.h>

#define kCustomProtocolScheme @"QuickHybridJSBridge"
#define kQueueHasMessage      @"epoint_bridge"
#define kCustomQueueHasMessage  @"custom_epoint_bridge"
#define kBridgeLoaded         @"__BRIDGE_LOADED__"

typedef void (^WVJBResponseCallback)(id responseData);
typedef void (^WVJBHandler)(id data, WVJBResponseCallback responseCallback);
typedef NSDictionary WVJBMessage;

@protocol WebViewJavascriptBridgeBaseDelegate <NSObject>
- (NSString*) _evaluateJavascript:(NSString*)javascriptCommand;
@end

@interface WebViewJavascriptBridgeBase : NSObject


@property (weak, nonatomic) id <WebViewJavascriptBridgeBaseDelegate> delegate;
@property (strong, nonatomic) NSMutableArray* startupMessageQueue;
@property (strong, nonatomic) NSMutableDictionary* responseCallbacks;
@property (strong, nonatomic) NSMutableDictionary* messageHandlers;
@property (strong, nonatomic) WVJBHandler messageHandler;


/**
 新增，存放各个api module
 */
@property (nonatomic, strong) NSMutableDictionary *modulesDic;

/**
 新增，存放各个 api module 的权限
 */
@property (nonatomic, strong) NSMutableDictionary *modulesAuthorityDic;

+ (void)enableLogging;
+ (void)setLogMaxLength:(int)length;
- (void)reset;
- (void)sendData:(id)data responseCallback:(WVJBResponseCallback)responseCallback handlerName:(NSString*)handlerName;
- (void)flushMessageQueue:(NSString *)messageQueueString;
//- (void)injectJavascriptFile;
- (BOOL)isCorrectProcotocolScheme:(NSURL*)url;
- (BOOL)isQueueMessageURL:(NSURL*)urll;
- (BOOL)isBridgeLoadedURL:(NSURL*)urll;
- (void)logUnkownMessage:(NSURL*)url;
- (NSString *)webViewJavascriptCheckCommand;
- (NSString *)webViewJavascriptFetchQueyCommand;
- (void)disableJavscriptAlertBoxSafetyTimeout;

- (void)excuteMsg:(NSString *)msg moduleName:(NSString *)moduleName;
- (void)excuteMsg:(NSDictionary *)msgDic;
- (NSArray*)deserializeMessageJSON:(NSString *)messageJSON;
@end
