//
//  MyWindow.h
//  OpenGLExampleGUI
//
//  Created by samuel de santis on 26/08/2014.
//  Copyright (c) 2014 Samuel DE SANTIS. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <OGLUIKit/OGLUIKit.h>



@interface Exhibit : NSObject
@property BOOL initialised;
//    GLhandleARB vertex_shader, fragment_shader, program_object;
//    GLUquadric *quadric;
//    BOOL gpuProcessingInit;
//    BOOL gpuProcessing;
@property(strong,nonatomic) NSValue *cppObj;

- (void)initLazy;

- (void)didUpdateWindowRect:(NSRect)rect;
- (void)renderForTime:(const CVTimeStamp*)outputTime;

@end

/* Exhibit base class */
@interface UIController : NSObject {
    IBOutlet NSTableView *table_view;
    IBOutlet NSTextView  *text_view;
    IBOutlet OpenGLDynamicView *openglview;
    
    NSArray *exhibits;
}
@end