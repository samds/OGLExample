//
//  MyWindow.m
//  OGLExample
//
//  Created by samuel on 26/08/2014.
//  Copyright (c) 2014 SDS. All rights reserved.
//

#import "MyWindow.h"
#import "OGLExample.h"

// A row must not have the same as a group
//
//

#define BASIC_CLEAR_COLOR       @"Clear Color"
#define BASIC_TRIANGLE          @"Triangle"
#define BASIC_COLORED_TRIANGLE  @"Triangle 2"
#define BASIC_TRIANGLE_UNIFORM  @"Triangle 3"
#define BASIC_TRIANGLE_MLCOLOR  @"Triangle 4"
#define BASIC_SQUARE            @"Square"
#define BASIC_SQUARE_EBO        @"Square EBO"
#define BASIC_SCISSOR           @"Scissor"
#define BASIC_CIRCLE            @"Circle"

#define TEXTURE_1               @"Texture Basic"
#define TEXTURE_2               @"Texture Wrong"
#define TEXTURE_3               @"Texture Corrected"
#define TEXTURE_4               @"Texture GLKit"

@implementation Exhibit

- (instancetype)init:(const void *)aPointer
{
    self = [super init];
    if (self) {
        _cppObj = [NSValue valueWithPointer:aPointer];
        _initialised = NO;
    }
    return self;
}

- (void)initLazy
{
    _initialised = TRUE;
    [self initialize];
}

- (NSString*)name
{
    return [NSString stringWithUTF8String:((OGLExample*)(_cppObj.pointerValue))->name().c_str()];
}

- (void)renderForTime:(const CVTimeStamp*)outputTime
{
    if (!_initialised) {
        [self initLazy];
    }
    ((OGLExample*)(_cppObj.pointerValue))->renderForTime(outputTime);
}

- (void)didUpdateWindowRect:(NSRect)rect
{
    ((OGLExample*)(_cppObj.pointerValue))->didUpdateWindowRect(rect);
}

- (void)initialize
{
    ((OGLExample*)(_cppObj.pointerValue))->init(NULL);
}

- (void)dealloc
{
    delete ((OGLExample*)(_cppObj.pointerValue));
}

@end


@interface UIController () <NSTableViewDataSource,NSTableViewDelegate,OpenGLContextDelegate>
@property(strong,nonatomic) Exhibit* currentExhibit;
@end

#define NEW_EXHIBIT_OBJET_WITH_TYPE(A) [[Exhibit alloc] init:(new A())]

@implementation UIController

- (instancetype)init
{
    self = [super init];
    if (self) {
        /* This is the list of supported exhibits */
        exhibits = [NSArray arrayWithObjects:
                    NEW_EXHIBIT_OBJET_WITH_TYPE(OGLExampleColor),
                    NEW_EXHIBIT_OBJET_WITH_TYPE(OGLExampleTriangle),
                    NEW_EXHIBIT_OBJET_WITH_TYPE(OGLExampleTriangle2),
                    NEW_EXHIBIT_OBJET_WITH_TYPE(OGLExampleTriangle3),
                    NEW_EXHIBIT_OBJET_WITH_TYPE(OGLExampleTriangle4),
                    NEW_EXHIBIT_OBJET_WITH_TYPE(OGLExampleSquare),
                    NEW_EXHIBIT_OBJET_WITH_TYPE(OGLExampleSquare2),
                    NEW_EXHIBIT_OBJET_WITH_TYPE(OGLExampleTexture1),
                    NEW_EXHIBIT_OBJET_WITH_TYPE(OGLExampleTexture2),
                    NEW_EXHIBIT_OBJET_WITH_TYPE(OGLExampleTexture3),
                    NEW_EXHIBIT_OBJET_WITH_TYPE(OGLExampleTexture4),
                    nil];

        // Select the first exhibit object by default
        self.currentExhibit = [exhibits objectAtIndex:0];
    }
    return self;
}

- (void) dealloc
{
    
}

- (void) awakeFromNib
{
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        // Creates the OpenGLContext
        [openglview createOpenGLContextWithDelegate:self];
        

    });
//    [openglview setExhibit: exhibit];
//    [text_view  readRTFDFromFile: [exhibit descriptionFilename]];
}

#pragma mark - NSTableViewDelegate


- (NSInteger)numberOfRowsInTableView:(NSTableView *)tableView
{
    return [exhibits count];
}

-               (id)tableView:(NSTableView *)tableView
    objectValueForTableColumn:(NSTableColumn *)tableColumn
                          row:(NSInteger)row
{
    return [[exhibits objectAtIndex:row] name];
}

- (void)tableViewSelectionDidChange:(NSNotification *)aNotification
{
    NSInteger rowindex;
    Exhibit  *exhibit;

    /* Get the symbol that was selected */
    rowindex = [table_view selectedRow];
    if ((rowindex < 0) || (rowindex >= [exhibits count])) {
        return;
    }
    exhibit = [exhibits objectAtIndex: rowindex];
    
    // the new exhibit object might erase previous config
//    [_currentExhibit setInitialised:NO];
    
//
//    [openglview setExhibit: exhibit];
//    
//    if ([exhibit descriptionFilename])
//        [text_view readRTFDFromFile: [exhibit descriptionFilename]];
//    else
//        [text_view setString: @""];
    
    // Forward the view size in the new exhibit object
    [exhibit didUpdateWindowRect:openglview.bounds];
    
    _currentExhibit = exhibit;
}

#pragma mark - OpenGL Delegate

- (void)didCreateOpenGLContext:(id)userInfo
{
    
}

- (void)renderForTime:(const CVTimeStamp*)outputTime
{
    [_currentExhibit renderForTime:outputTime];
}

- (void)didUpdateWindowRect:(NSRect)rect
{
    NSLog(@"W=%f",rect.size.width);
    [self.currentExhibit didUpdateWindowRect:rect];
}

- (void)windowWillClose:(NSNotification*)notification
{
    _currentExhibit = nil;
    exhibits = nil;
}

#pragma mark - User Action

- (void)keyDown
{
    
}

@end