//
//  MainWindow.cpp
//  TinyEditor
//
//  Created by Jeppe Nielsen on 16/09/2020.
//  Copyright © 2020 Jeppe Nielsen. All rights reserved.
//

#include "Window.hpp"
#import <Cocoa/Cocoa.h>
#include <OpenGL/gl.h>
#include <iostream>

using namespace Tiny;

static Tiny::Window* engineWindow;

@interface AppDelegate : NSResponder <NSApplicationDelegate, NSWindowDelegate>
{
    @public
    Window::MainLoopData* mainLoopData;
    CVDisplayLinkRef displayLink;
}

@end

static CVReturn MyDisplayLinkCallback(CVDisplayLinkRef displayLink, const CVTimeStamp* now, const CVTimeStamp* outputTime, CVOptionFlags flagsIn, CVOptionFlags* flagsOut, void* displayLinkContext)
{
    dispatch_async(dispatch_get_main_queue(), ^{
        AppDelegate* appDelegate = (__bridge AppDelegate*)displayLinkContext;
        
        bool isAppFocused = ([NSApp mainWindow].isKeyWindow);
        
        NSPoint location = [NSEvent mouseLocation];
        NSUInteger buttonsDown = [NSEvent pressedMouseButtons];
        
        engineWindow->inputDevice.SetTouch(0, (buttonsDown & 1) == 1 && isAppFocused, ivec2(location.x, location.y));
        engineWindow->inputDevice.SetTouch(1, (buttonsDown & 2) == 2 && isAppFocused, ivec2(location.x, location.y));
        engineWindow->inputDevice.SetTouch(2, (buttonsDown & 4) == 4 && isAppFocused, ivec2(location.x, location.y));
        
        appDelegate->mainLoopData->Update();
        //std::cout << [NSEvent mouseLocation].x << std::endl;
    });
    
    return kCVReturnSuccess;
}



@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    CVDisplayLinkCreateWithActiveCGDisplays(&displayLink);
    CVDisplayLinkSetOutputCallback(displayLink, &MyDisplayLinkCallback, (__bridge void*)self);
    
    NSRect visibleFrame = [NSScreen mainScreen].visibleFrame;
    mainLoopData->ScreenSize(visibleFrame.size.width, visibleFrame.size.height);
    
    mainLoopData->Initialize();
    
    CVDisplayLinkStart(displayLink);
}

- (void)windowWillMove:(NSNotification *)notification {
    
    NSWindow* window = [notification object];
    std::cout << "Will move : " << std::string([window.title UTF8String])  << std::endl;
    
    [window orderFront:window];
    [window orderFrontRegardless];
    
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

- (void) windowWillClose:(NSNotification *)notification {
    NSWindow* window = [notification object];
    std::cout << "Will close :" << std::string([window.title UTF8String])  << std::endl;
    //[window close];
    //[window orderOut:[NSApplication sharedApplication]];
    //[window close];
}

- (void) mouseDown:(NSEvent*)theEvent {
    NSPoint location = [NSEvent mouseLocation];
    engineWindow->inputDevice.SetTouch(0, true, ivec2(location.x, location.y));
}

-(void) mouseUp:(NSEvent *)theEvent {
    NSPoint location = [NSEvent mouseLocation];
    engineWindow->inputDevice.SetTouch(0, false, ivec2(location.x, location.y));
}

-(void) mouseDragged:(NSEvent *)theEvent {
    NSPoint location = [NSEvent mouseLocation];
    engineWindow->inputDevice.SetTouchPosition(0, ivec2(location.x, location.y));
}

-(void)mouseMoved:(NSEvent *)theEvent {
    NSPoint location = [NSEvent mouseLocation];
    
    engineWindow->inputDevice.SetTouch(0, false, ivec2(location.x, location.y));
    engineWindow->inputDevice.SetTouch(1, false, ivec2(location.x, location.y));
    engineWindow->inputDevice.SetTouch(2, false, ivec2(location.x, location.y));
}


@end



void Window::StartLoop(MainLoopData mainLoopData) {

    engineWindow = this;
    
    inputDevice.Initialize(3);
    
    this->mainLoopData = mainLoopData;
    
    [NSApplication sharedApplication];
    AppDelegate *appDelegate = [[AppDelegate alloc] init];
    appDelegate->mainLoopData = &this->mainLoopData;
    [NSApp setDelegate:appDelegate];
    [NSApp run];
}

void Window::PreRender() {
    
    /*glViewport(0, 0, globalWindowWidth * 2, globalWindowHeight * 2);
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_CULL_FACE);
     */
}

void Window::PostRender() {
    //glFlush();
}
