//
//  MyWindow.h
//  OpenGLExampleGUI
//
//  Created by samuel de santis on 26/08/2014.
//  Copyright (c) 2014 Samuel DE SANTIS. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <OGLUIKit/OGLUIKit.h>

@interface MyWindow : NSWindow
@property (weak) IBOutlet OpenGLDynamicView *openGLView;
@property (weak) IBOutlet NSOutlineView *outlineView;
@end