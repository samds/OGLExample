//
//  MyWindow.m
//  OpenGLExampleGUI
//
//  Created by samuel de santis on 26/08/2014.
//  Copyright (c) 2014 Samuel DE SANTIS. All rights reserved.
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

#define TEXTURE_1               @"Texture Basic"
#define TEXTURE_2               @"Texture Wrong"
#define TEXTURE_3               @"Texture Corrected"
#define TEXTURE_4               @"Texture GLKit"

@interface MyWindow () <NSOutlineViewDelegate,
                        NSOutlineViewDataSource,
                        OpenGLDynamicViewDelegate>
@property(strong,nonatomic) NSArray *dataSource;
@property(strong,nonatomic) NSArray *dataSourceTexture;
@property(assign,nonatomic) OGLExample *openGLForm;
@property(strong,nonatomic) NSArray *topLevelItems;
@end

/*
 * The NSOutlineView was inspired by the code found in the Apple(c) 
 * sample "SideBarDemo".
 */
@implementation MyWindow

- (void)awakeFromNib
{
//    NSLog(@"%s",__FUNCTION__);
    [self.openGLView setViewDelegate:self];
    
    // NSTableViewRowSizeStyleDefault should be used, unless the user has picked
    // an explicit size. In that case, it should be stored out and re-used.
    [self.outlineView setRowSizeStyle:NSTableViewRowSizeStyleDefault];
    
    // Expand all the root items; disable the expansion animation that
    // normally happens
//    [NSAnimationContext beginGrouping];
//    [[NSAnimationContext currentContext] setDuration:0];
    [self.outlineView beginUpdates];
    [self.outlineView expandItem:nil expandChildren:YES];
    [self.outlineView endUpdates];
//    [NSAnimationContext endGrouping];
}

- (instancetype)initWithContentRect:(NSRect)contentRect
                          styleMask:(NSUInteger)aStyle
                            backing:(NSBackingStoreType)bufferingType
                              defer:(BOOL)flag
{
    NSLog(@"%s",__FUNCTION__);

    self = [super initWithContentRect:contentRect
                            styleMask:aStyle
                              backing:bufferingType
                                defer:flag];
    if (self) {
        _topLevelItems = @[@"Basic",@"Texture"];
        _dataSource = @[BASIC_CLEAR_COLOR,
                        BASIC_TRIANGLE,
                        BASIC_COLORED_TRIANGLE,
                        BASIC_TRIANGLE_UNIFORM,
                        BASIC_TRIANGLE_MLCOLOR,
                        BASIC_SQUARE,
                        BASIC_SQUARE_EBO,
                        BASIC_SCISSOR];
        _dataSourceTexture = @[TEXTURE_1,
                               TEXTURE_2,
                               TEXTURE_3,
                               TEXTURE_4
                               ];
        _openGLForm = new OGLExampleColor();
    }
    return self;
}

#pragma mark - OpenGLDynamicViewDelegate

- (void)didCreateOpenGLContext:(id)userInfo
{
    _openGLForm->init(NULL);
}

- (void)renderForTime:(const CVTimeStamp *)outputTime
{
//    NSLog(@"render");
    if (_openGLForm != NULL) {
//        NSLog(@"%lld",(outputTime==NULL)?0:outputTime->videoTime);
        _openGLForm->renderForTime(outputTime);
    }
}

- (void)windowWillClose:(NSNotification *)notification
{
    delete _openGLForm;
    _openGLForm = NULL;
}

- (void)didUpdateWindowRect:(NSRect)rect
{
    if (_openGLForm!=NULL) {
        _openGLForm->didUpdateWindowRect(rect);
    }
}

#pragma mark - NSOutlineViewDataSource

- (NSInteger)outlineView:(NSOutlineView *)outlineView
  numberOfChildrenOfItem:(id)item
{
    if (item==nil) {
        return [_topLevelItems count];
    }
    else if ([item isEqualToString:@"Basic"]) {
        return [_dataSource count];
    }
    else if ([item isEqualToString:@"Texture"]) {
        return [_dataSourceTexture count];
    }
    else {
        return 0;
    }
}


- (NSArray *)_childrenForItem:(id)item {
    NSArray *children;
    if (item == nil) {
        children = _topLevelItems;
    }
    else if ([item isEqualToString:@"Basic"]) {
        children = _dataSource;
    }
    else if ([item isEqualToString:@"Texture"]) {
        children = _dataSourceTexture;
    }
    else {
        children = [NSArray array];
    }
    return children;
}

- (id)outlineView:(NSOutlineView *)outlineView
            child:(NSInteger)index
           ofItem:(id)item
{
    return [[self _childrenForItem:item] objectAtIndex:index];
}

- (BOOL)outlineView:(NSOutlineView *)outlineView isItemExpandable:(id)item
{
    if ([outlineView parentForItem:item] == nil) {
        return YES;
    } else {
        return NO;
    }
}

- (id)              outlineView:(NSOutlineView *)outlineView
      objectValueForTableColumn:(NSTableColumn *)tableColumn
                         byItem:(id)item
{
    return item;
}

- (id)              outlineView:(NSOutlineView *)outlineView
             viewForTableColumn:(NSTableColumn *)tableColumn
                           item:(id)item
{
    if ([_topLevelItems containsObject:item])
    {
        NSAssert([item isKindOfClass:[NSString class]],
                 @"item must be a NSString"
                 );
        
        NSTableCellView *cell =
                [outlineView makeViewWithIdentifier:@"HeaderCell" owner:self];
        [cell.textField setStringValue:[item uppercaseString]];
        return cell;
    }
    else
    {
        NSAssert([item isKindOfClass:[NSString class]],
                 @"item must be a NSString"
                 );
        
        NSTableCellView *cell = [outlineView makeViewWithIdentifier:@"DataCell"
                                                              owner:self];
        [cell.textField setStringValue:item];
        return cell;
    }
}

- (BOOL)outlineView:(NSOutlineView *)outlineView isGroupItem:(id)item
{
    return [_topLevelItems containsObject:item];
}

- (BOOL)splitView:(NSSplitView *)splitView canCollapseSubview:(NSView *)subview
{
    return NO;
}

#pragma mark - NSOutlineViewDelegate

- (NSIndexSet *)outlineView:(NSOutlineView *)outlineView
    selectionIndexesForProposedSelection:(NSIndexSet *)proposedSelectionIndexes
{
//    NSLog(@"==> %@",[proposedSelectionIndexes debugDescription]);

    id item = [outlineView itemAtRow:[proposedSelectionIndexes firstIndex]];
    if ([_topLevelItems containsObject:item]) {
        return nil;
    }
    
    if (_openGLForm != NULL) {
        delete _openGLForm;
        _openGLForm = NULL;
    }

    NSAssert([item isKindOfClass:[NSString class]], @"item must be a NSString");
  
    // Set the window's title as the cell
    [self setTitle:item];
    
    if ([item isEqualToString:BASIC_CLEAR_COLOR]) {
        _openGLForm = new OGLExampleColor;
        ((OGLExampleColor*)_openGLForm)->setColor(1.0f, 0.0f, 0.0f, 1.0f);
    }
    else if ([item isEqualToString:BASIC_TRIANGLE]) {
        _openGLForm = new OGLExampleTriangle;
    }
    else if ([item isEqualToString:BASIC_COLORED_TRIANGLE]) {
        _openGLForm = new OGLExampleTriangle2;
    }
    else if ([item isEqualToString:BASIC_TRIANGLE_UNIFORM]) {
        _openGLForm = new OGLExampleTriangle3;
    }
    else if ([item isEqualToString:BASIC_TRIANGLE_MLCOLOR]) {
        _openGLForm = new OGLExampleTriangle4;
    }
    else if ([item isEqualToString:BASIC_SQUARE]) {
        _openGLForm = new OGLExampleSquare;
    }
    else if ([item isEqualToString:BASIC_SQUARE_EBO]) {
        _openGLForm = new OGLExampleSquare2;
    }
    else if ([item isEqualToString:BASIC_SCISSOR]) {
        _openGLForm = new OGLExampleScissor;
        
        // Pass the View size to our OpenGl shape
        [self didUpdateWindowRect:[self.openGLView bounds]];
    }
    
    if ([item isEqualToString:TEXTURE_2]) {
        _openGLForm = new OGLExampleTexture2;
        
        // Pass the View size to our OpenGl shape
        [self didUpdateWindowRect:[self.openGLView bounds]];
    }
    else if ([item isEqualToString:TEXTURE_3]) {
        _openGLForm = new OGLExampleTexture3;
        
        // Pass the View size to our OpenGl shape
        [self didUpdateWindowRect:[self.openGLView bounds]];
    }
    else if ([item isEqualToString:TEXTURE_4]) {
        _openGLForm = new OGLExampleTexture4;
        
        // Pass the View size to our OpenGl shape
        [self didUpdateWindowRect:[self.openGLView bounds]];
    }
    else if ([item isEqualToString:TEXTURE_1]) {
        _openGLForm = new OGLExampleTexture1;
        
        // Pass the View size to our OpenGl shape
        [self didUpdateWindowRect:[self.openGLView bounds]];
    }
    
    // The variable _openGLForm can't be NULL .
    // if it does, we've forgotten to handle a case just above
    //
    // During the initialization of our shape we don't want any rendering.
    // By example, if we try to compile a shader during rendering
    // we get a GL_INVALID_OPERATION .
	CGLLockContext((CGLContextObj)[[_openGLView openGLContext] CGLContextObj]);
    _openGLForm->init(NULL);
	CGLUnlockContext(
                     (CGLContextObj)[[_openGLView openGLContext] CGLContextObj]
                     );

    return proposedSelectionIndexes;
}

@end