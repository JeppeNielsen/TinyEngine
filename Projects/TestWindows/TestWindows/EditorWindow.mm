//
//  EditorWindow.cpp
//  TestWindows
//
//  Created by Jeppe Nielsen on 15/09/2020.
//  Copyright © 2020 Jeppe Nielsen. All rights reserved.
//

#include "EditorWindow.hpp"
#import <Cocoa/Cocoa.h>

using namespace Editor;

EditorWindow::EditorWindow(const std::string& title, int width, int height) {
    
    NSWindow *myWindow = [[NSWindow alloc] init];

    NSUInteger masks = NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskTexturedBackground | NSWindowStyleMaskUtilityWindow;
    [myWindow setStyleMask:masks];
    [myWindow setBackgroundColor:[NSColor grayColor]];

    NSRect frame = NSMakeRect(0, 0, width, height);
    [myWindow  setFrame:frame display:NO];

    [[NSApp mainWindow] addChildWindow:myWindow ordered:NSWindowAbove];

    window = (__bridge WindowHandle)myWindow;
}

EditorWindow::~EditorWindow() {
    NSWindow* myWindow = (__bridge NSWindow*)window;
    [myWindow close];
}
