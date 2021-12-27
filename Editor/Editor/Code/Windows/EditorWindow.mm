//
//  EditorWindow.cpp
//  TestWindows
//
//  Created by Jeppe Nielsen on 15/09/2020.
//  Copyright © 2020 Jeppe Nielsen. All rights reserved.
//

#include "EditorWindow.hpp"
#import <Cocoa/Cocoa.h>
#include <iostream>
#include "Window.hpp"
#include "OpenGL.hpp"

using namespace TinyEditor;

@interface OSXView : NSOpenGLView <NSWindowDelegate>
{
    @public
    EditorWindow* editorWindow;
}
- (void) prepareOpenGL;
- (void) drawRect: (NSRect) bounds;

@end


@implementation OSXView

- (void)prepareOpenGL {
    [super prepareOpenGL];
    
    GLint swapInt = 1;
    [[self openGLContext] setValues:&swapInt forParameter:NSOpenGLCPSwapInterval];
    
    //CGLContextObj cglContext = [[self openGLContext] CGLContextObj];
    //CGLPixelFormatObj cglPixelFormat = [[self pixelFormat] CGLPixelFormatObj];
    
    [self setWantsLayer:YES];
    
}

- (void) drawRect: (NSRect) bounds {
    editorWindow->Render({bounds.size.width, bounds.size.height});
}

@end


static NSOpenGLContext* sharedContext = nullptr;

@interface WindowDelegate : NSResponder <NSWindowDelegate>
{
    @public
    NSWindow* nsWindow;
    EditorWindow* editorWindow;
    bool isFromSetFrame;
}

@end
@implementation WindowDelegate

- (void) windowDidResize:(NSNotification *)notification {
    if (isFromSetFrame) return;
    editorWindow->needsUpdate = true;
    editorWindow->position = ivec2( nsWindow.frame.origin.x,  nsWindow.frame.origin.y);
    editorWindow->size = ivec2( nsWindow.frame.size.width,  nsWindow.frame.size.height);
}

- (void) windowWillClose:(NSNotification *)notification {
    editorWindow->isDead = true;
}

@end

void EditorWindow::CreateMain(const std::string& title, int width, int height) {
    
    NSWindow *myWindow = [[NSWindow alloc] init];

    myWindow.title = [[NSString alloc]initWithUTF8String:title.c_str()];

    NSUInteger masks = NSWindowStyleMaskTitled |
    NSWindowStyleMaskClosable |
    NSWindowStyleMaskTexturedBackground |
    NSWindowStyleMaskResizable;
    [myWindow setStyleMask:masks];
    [myWindow setBackgroundColor:[NSColor blackColor]];

    NSRect frame = NSMakeRect(0, 0, width, height);
    [myWindow  setFrame:frame display:NO];
    
    [myWindow makeKeyAndOrderFront: myWindow];
    [myWindow setDelegate:(id <NSWindowDelegate>)[NSApplication sharedApplication].delegate];
    [myWindow makeFirstResponder:(NSResponder*)[NSApplication sharedApplication].delegate];
    [myWindow makeMainWindow];
    
       
    GLuint attributes[] = {
        NSOpenGLPFANoRecovery,
        NSOpenGLPFAWindow,
       // NSOpenGLPFAAccelerated,
        //NSOpenGLPFADoubleBuffer,
        NSOpenGLPFAColorSize, 24,
        NSOpenGLPFAAlphaSize, 8,
        NSOpenGLPFADepthSize, 16,
        NSOpenGLPFAStencilSize, 8,
        NSOpenGLPFAAccumSize, 0,
        0
    };
    
    NSOpenGLPixelFormat* fmt = [[NSOpenGLPixelFormat alloc] initWithAttributes:(NSOpenGLPixelFormatAttribute*) attributes];
    if (!fmt)
        NSLog(@"No OpenGL pixel format");
    
    sharedContext = [[NSOpenGLContext alloc]initWithFormat:fmt shareContext:NULL];
    [sharedContext makeCurrentContext];

    [NSApp activateIgnoringOtherApps: true];

    window = myWindow;
}

void EditorWindow::CreateTool(EditorWindow::WindowHandle mainWindow, const std::string& title) {
    
    NSWindow *myWindow = [[NSWindow alloc] init];
    myWindow.title = [[NSString alloc]initWithUTF8String:title.c_str()];

    [myWindow setStyleMask:NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable | NSWindowStyleMaskBorderless];
    [myWindow setBackgroundColor:[NSColor whiteColor]];

    NSRect frame = NSMakeRect(0, 0, 100, 100);
    [myWindow  setFrame:frame display:NO];

    NSWindow* mainWindowPtr = (__bridge NSWindow*)mainWindow;

    [mainWindowPtr addChildWindow:myWindow ordered:NSWindowAbove];
    [myWindow setMovable:false];
    
    window = (__bridge WindowHandle)myWindow;
    
    WindowDelegate* delegate = [[WindowDelegate alloc]init];
    delegate->editorWindow = this;
    delegate->nsWindow = myWindow;
    
    [myWindow setDelegate:delegate];
    
    windowDelegate = (__bridge WindowHandle)delegate;
    
    [myWindow makeFirstResponder:(NSResponder*)[NSApplication sharedApplication].delegate];
    
    
    
    
    GLuint attributes[] = {
        NSOpenGLPFANoRecovery,
        NSOpenGLPFAWindow,
       // NSOpenGLPFAAccelerated,
        //NSOpenGLPFADoubleBuffer,
        NSOpenGLPFAColorSize, 24,
        NSOpenGLPFAAlphaSize, 8,
        NSOpenGLPFADepthSize, 16,
        NSOpenGLPFAStencilSize, 8,
        NSOpenGLPFAAccumSize, 0,
        0
    };
    
    //NSOpenGLPixelFormat* fmt = [[NSOpenGLPixelFormat alloc] initWithAttributes:(NSOpenGLPixelFormatAttribute*) attributes];
    //if (!fmt)
    //    NSLog(@"No OpenGL pixel format");
    

    OSXView* openGlView = [[OSXView alloc]init];
    openGlView->editorWindow = this;
     
    
    //[openGlView retain];
    
    [openGlView setWantsBestResolutionOpenGLSurface:YES];
    
    [openGlView setOpenGLContext:sharedContext];
    [myWindow setContentView:openGlView ];
    
    view = (__bridge WindowHandle)openGlView;
    
    
}

void EditorWindow::Close() {
    if (!isDead) {
        NSWindow* myWindow = (__bridge NSWindow*)window;
        [myWindow close];
    }
    isDead = true;
    
    //delete editorScene;
    //editorScene = nullptr;
}

bool EditorWindow::IsCreated() {
    return window != nullptr;
}

void EditorWindow::SetFrame(ivec2 position, ivec2 size) {
    WindowDelegate* delegate = (__bridge WindowDelegate*)windowDelegate;
    delegate->isFromSetFrame = true;
    NSWindow* myWindow = (__bridge NSWindow*)window;
    NSRect frame = NSMakeRect(position.x, position.y, size.x, size.y);
    [myWindow  setFrame:frame display:NO];
    delegate->isFromSetFrame = false;
}

void EditorWindow::Update() {
    //editorScene->Update();
    
    
    dispatch_async(dispatch_get_main_queue(), ^{
        OSXView* osXView = (__bridge OSXView*)view;
        [osXView setNeedsDisplay: YES];
    //    [self setNeedsDisplay:YES];
    });
}

void EditorWindow::Render(ivec2 viewport) {
    glViewport(0, 0, viewport.x, viewport.y);
    glClearColor(color.r,color.g, 1, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    //editorScene->Render(viewport);
    
    glFlush();
}

EditorWindow::WindowHandle EditorWindow::GetHandle() {
    return window;
}
