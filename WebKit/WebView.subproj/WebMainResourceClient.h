/*	
    WebMainResourceClient.h

    Private header.
    
    Copyright 2001, 2002 Apple Computer Inc. All rights reserved.
*/

#import <Foundation/Foundation.h>

#import <WebKit/WebBaseResourceHandleDelegate.h>
#import <WebKit/WebControllerPolicyDelegate.h>

@class WebDownloadHandler;
@class WebDataSource;
@class WebResourceHandle;
@class WebResourceRequest;
@class WebResourceResponse;

@protocol WebResourceHandleDelegate;
@protocol WebResourceLoadDelegate;

@interface WebMainResourceClient : WebBaseResourceHandleDelegate
{
    WebDownloadHandler *downloadHandler;
    WebContentAction policyAction;
    NSMutableData *resourceData;
}

- initWithDataSource:(WebDataSource *)dataSource;
- (WebDownloadHandler *)downloadHandler;
- (NSData *)resourceData;

@end
