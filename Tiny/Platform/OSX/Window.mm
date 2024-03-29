//
//  Window.cpp
//  MiniOSX
//
//  Created by Jeppe Nielsen on 04/01/2019.
//  Copyright © 2019 Jeppe Nielsen. All rights reserved.
//

#include "Window.hpp"
#import <Cocoa/Cocoa.h>
#include <OpenGL/gl.h>
#include "OSXView.h"
#include <iostream>

using namespace Tiny;

static Tiny::Window* engineWindow;
static int globalWindowWidth;
static int globalWindowHeight;
static OSXView* staticView;

@implementation OSXView

+(OSXView*) getInstance {
    return staticView;
}

-(void) drawRect: (NSRect) bounds {
    if (engineWindow->mainLoopData.Update()) {
        exit(0);
    }
}

-(void) setWindow:(NSWindow *)_window {
    window = _window;
}

static CVReturn MyDisplayLinkCallback(CVDisplayLinkRef displayLink, const CVTimeStamp* now, const CVTimeStamp* outputTime, CVOptionFlags flagsIn, CVOptionFlags* flagsOut, void* displayLinkContext)
{
    return [(__bridge OSXView*)displayLinkContext getFrameForTime:outputTime];
}

- (void)prepareOpenGL {
    [super prepareOpenGL];
    
    GLint swapInt = 1;
    [[self openGLContext] setValues:&swapInt forParameter:NSOpenGLCPSwapInterval];
    
    CVDisplayLinkCreateWithActiveCGDisplays(&displayLink);
    CVDisplayLinkSetOutputCallback(displayLink, &MyDisplayLinkCallback, (__bridge void*)self);
    
    CGLContextObj cglContext = [[self openGLContext] CGLContextObj];
    CGLPixelFormatObj cglPixelFormat = [[self pixelFormat] CGLPixelFormatObj];
    CVDisplayLinkSetCurrentCGDisplayFromOpenGLContext(displayLink, cglContext, cglPixelFormat);
                                              
    GLint defaultFBO;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &defaultFBO);
    
    //Window::Framebuffer = (uint)defaultFBO;
    
    NSApplication* app = [NSApplication sharedApplication];
    NSMenu* menu = [[NSMenu alloc] initWithTitle: @""];

    {
        [menu addItemWithTitle:@"" action:nil keyEquivalent:@""];
    }

    [app setMainMenu:menu];
    
    [self setWantsLayer:YES];

    staticView = self;
    engineWindow->mainLoopData.Initialize();
    
    CVDisplayLinkStart(displayLink);
}

- (CVReturn)getFrameForTime:(const CVTimeStamp*)outputTime
{
    // Need to dispatch to main thread as CVDisplayLink uses it's own thread.
    dispatch_async(dispatch_get_main_queue(), ^{
        [self setNeedsDisplay:YES];
    });
    return kCVReturnSuccess;
}

-(NSPoint) convertViewLocationToWorldPoint: (NSPoint) point {
    NSPoint p = [self convertPoint:point toView:nil];
    NSRect rect;
    rect.origin.x = p.x;
    rect.origin.y = p.y;
    
    rect = [window convertRectToScreen:rect];
    return rect.origin;
}

- (void) mouseDown:(NSEvent*)theEvent {
    NSPoint location = [self convertLocation:theEvent.locationInWindow];
    engineWindow->inputDevice.SetTouch(0, true, ivec2(location.x, location.y));
}

-(void) mouseUp:(NSEvent *)theEvent {
    NSPoint location = [self convertLocation:theEvent.locationInWindow];
    engineWindow->inputDevice.SetTouch(0, false, ivec2(location.x, location.y));
}

-(void) mouseDragged:(NSEvent *)theEvent {
    NSPoint location = [self convertLocation:theEvent.locationInWindow];
    //OSXWindowCreator::Instance()->Move(0, location.x, location.y);
    engineWindow->inputDevice.SetTouchPosition(0, ivec2(location.x, location.y));
}

-(void)mouseMoved:(NSEvent *)theEvent {
    NSPoint location = [self convertLocation:theEvent.locationInWindow];
    
    engineWindow->inputDevice.SetTouch(0, false, ivec2(location.x, location.y));
    engineWindow->inputDevice.SetTouch(1, false, ivec2(location.x, location.y));
    engineWindow->inputDevice.SetTouch(2, false, ivec2(location.x, location.y));
}

- (void)scrollWheel:(NSEvent *)theEvent {
    engineWindow->inputDevice.SetScroll(theEvent.scrollingDeltaY);
}

-(NSPoint) convertLocation: (NSPoint) point {
    return point;
}

-(void)rightMouseDown:(NSEvent *)theEvent {
    NSPoint location = [self convertLocation:theEvent.locationInWindow];
    engineWindow->inputDevice.SetTouch(1, true, ivec2(location.x, location.y));
}

-(void)rightMouseUp:(NSEvent *)theEvent {
    NSPoint location = [self convertLocation:theEvent.locationInWindow];
    engineWindow->inputDevice.SetTouch(1, false, ivec2(location.x, location.y));
}

-(void)rightMouseDragged:(NSEvent *)theEvent {
    NSPoint location = [self convertLocation:theEvent.locationInWindow];
    engineWindow->inputDevice.SetTouchPosition(1, ivec2(location.x, location.y));
}

-(void)otherMouseDown:(NSEvent *)theEvent {
    if (theEvent.type == NSOtherMouseDown) {
        NSPoint location = [self convertLocation:theEvent.locationInWindow];
        engineWindow->inputDevice.SetTouch(2, true, ivec2(location.x, location.y));
    }
}

-(void)otherMouseUp:(NSEvent *)theEvent {
    if (theEvent.type == NSOtherMouseUp) {
        NSPoint location = [self convertLocation:theEvent.locationInWindow];
        engineWindow->inputDevice.SetTouch(2, false, ivec2(location.x, location.y));
    }
}

-(void)otherMouseDragged:(NSEvent *)theEvent {
    if (theEvent.type == NSOtherMouseDragged) {
        NSPoint location = [self convertLocation:theEvent.locationInWindow];
        engineWindow->inputDevice.SetTouchPosition(2, ivec2(location.x, location.y));
    }
}

-(void)keyDown:(NSEvent *)theEvent {
    ModifierKey modifierKey = ModifierKey::None;

    NSUInteger flags = [[NSApp currentEvent] modifierFlags];
    if ((flags & NSShiftKeyMask)) {
        modifierKey = ModifierKey::Shift;
    } else if ((flags & NSCommandKeyMask)) {
        modifierKey = ModifierKey::Command;
    } else if ((flags & NSAlternateKeyMask)) {
        modifierKey = ModifierKey::Alt;
    } else if ((flags & NSControlKeyMask)) {
        modifierKey = ModifierKey::Ctrl;
    }

    unichar cd = [[theEvent characters] characterAtIndex:0];
    NSString* str = [NSString stringWithCharacters:&cd length:1];
    engineWindow->inputDevice.SetButton([str UTF8String], true, modifierKey);
}

-(void)keyUp:(NSEvent *)theEvent {
    unichar cd = [[theEvent characters] characterAtIndex:0];
    NSString* str = [NSString stringWithCharacters:&cd length:1];
    engineWindow->inputDevice.SetButton([str UTF8String], false, ModifierKey::None);
}

- (void)viewDidChangeBackingProperties {
    NSScreen* scr = [[self window] screen];
    float scalingFactor = [scr backingScaleFactor];
    engineWindow->mainLoopData.ScreenScalingFactor(scalingFactor);
}

@end

@interface AppDelegate : NSResponder <NSApplicationDelegate, NSWindowDelegate>
{
    NSTimer* renderTimer;
    NSWindow* window;
    OSXView* view;
}

@end


@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    int windowWidth = 1280;//OSXWindowCreator::Instance()->Width;
    int windowHeight = 920;// OSXWindowCreator::Instance()->Height;
    bool isFullScreen = false;//OSXWindowCreator::Instance()->FullScreen;
    
    NSRect mainScreenSize = [[NSScreen mainScreen] frame];
    
    CGFloat xPos = mainScreenSize.size.width/2 - windowWidth/2;
    CGFloat yPos = mainScreenSize.size.height/2 - windowHeight/2;
    
    if (isFullScreen) {
        //windowWidth = mainScreenSize.size.width + [[[NSScreen screens] objectAtIndex:1] frame].size.width;
        //windowHeight = mainScreenSize.size.height;
        xPos = 0;
        yPos = 0;
        //OSXWindowCreator::Instance()->Width = windowWidth;
        //OSXWindowCreator::Instance()->Height = windowHeight;
    }
    
    NSRect frame = NSMakeRect(xPos, yPos, windowWidth, windowHeight);
    NSUInteger styleMask = NSTitledWindowMask | NSClosableWindowMask | NSResizableWindowMask | NSMiniaturizableWindowMask;
    if (isFullScreen) {
        styleMask |=NSFullScreenWindowMask;
    }
    NSRect rect = [NSWindow contentRectForFrameRect:frame styleMask:styleMask];
    window =  [[NSWindow alloc] initWithContentRect:rect styleMask:styleMask backing: NSBackingStoreBuffered    defer:false];
    [window setDelegate:self];
    [window setAcceptsMouseMovedEvents:YES];
    
    [ NSApp setDelegate:self ];
    renderTimer = nil;
    
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
    

    view = [[OSXView alloc]init];
    [view setWindow: window];
    [view setWantsBestResolutionOpenGLSurface:YES];
    
    float scalingFactor = [[NSScreen mainScreen] backingScaleFactor];
    engineWindow->mainLoopData.ScreenScalingFactor(scalingFactor);
    
    [window setContentView:view ];
    
    [window makeFirstResponder:view];
    
    [view setPixelFormat:fmt];

    NSTrackingAreaOptions options = (NSTrackingActiveAlways | NSTrackingInVisibleRect |
                         NSTrackingMouseEnteredAndExited | NSTrackingMouseMoved | NSOtherMouseDownMask | NSOtherMouseUpMask);

    NSTrackingArea *area = [[NSTrackingArea alloc] initWithRect:[view bounds]
                                                    options:options
                                                      owner:window
                                                   userInfo:nil];
    [view addTrackingArea:area];
    
    [window makeKeyAndOrderFront: window];
    
    [window orderFront:window];
    
    [self windowDidResize:[NSNotification alloc]];
}

- (void)windowWillClose:(NSNotification *)notification
{
    exit(0);
}

- (void)windowDidResize:(NSNotification *)notification {
    globalWindowWidth = view.bounds.size.width;
    globalWindowHeight = view.bounds.size.height;
    engineWindow->mainLoopData.ScreenSize(globalWindowWidth, globalWindowHeight);
}

- (void)windowWillMove:(NSNotification *)notification {
    
    std::cout << "Window will move"<<std::endl;
    
}

@end

void Window::StartLoop(MainLoopData mainLoopData) {

    inputDevice.Initialize(3);
    engineWindow = this;

    this->mainLoopData = mainLoopData;
    
    [NSApplication sharedApplication];
    AppDelegate *appDelegate = [[AppDelegate alloc] init];
    [NSApp setDelegate:appDelegate];
    [NSApp run];
}

void Window::PreRender() {
    NSScreen* scr = [[staticView window] screen];
    float scalingFactor = [scr backingScaleFactor];

    glViewport(0, 0, globalWindowWidth * scalingFactor, globalWindowHeight * scalingFactor);
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_CULL_FACE);
}

void Window::PostRender() {
    glFlush();
}
