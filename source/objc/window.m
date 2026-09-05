#import "../headers/window_objc.h"
#import <AppKit/AppKit.h>

NSWindow *window;

void ObjCGetFramebufferSize(int *width, int *height) {
  NSRect frame = [window.contentView bounds];
  NSSize backingSize = [window.contentView convertSizeToBacking:frame.size];

  *width = (int)backingSize.width;
  *height = (int)backingSize.height;
}

NSApplication * ObjCGetWindowUserPointer() {
    return NSApp;
}

void ObjCPollEvents()
{
    @autoreleasepool {
        NSEvent *event;

        while ((event = [NSApp nextEventMatchingMask:NSEventMaskAny
                                           untilDate:[NSDate distantPast]
                                              inMode:NSDefaultRunLoopMode
                                             dequeue:YES])) {
            [NSApp sendEvent:event];
        }

        [NSApp updateWindows];
    }
}

bool ObjCShouldClose() {
  @autoreleasepool {
      if ([NSApp.delegate applicationShouldTerminate:NSApp] == NO){
        return false;
      } else {
        return true;
      }
    }
}

CAMetalLayer *ObjCInitWindowAndGetMetalLayer() {
  @autoreleasepool {
      [NSApplication sharedApplication];

      [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];

      NSRect frame = NSMakeRect(0, 0, 350, 250);
      NSWindowStyleMask stylemask = NSWindowStyleMaskTitled | NSWindowStyleMaskResizable | NSWindowStyleMaskResizable | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable | NSWindowStyleMaskMiniaturizable;
      NSBackingStoreType backing = NSBackingStoreBuffered;
        window = [[NSWindow alloc] initWithContentRect:frame
                             styleMask:stylemask
                             backing:backing
                             defer:NO];

        [window setTitle:(@"Hello Triangle")];
        [window.contentView setWantsLayer:YES];
        CAMetalLayer *metalLayer = [CAMetalLayer layer];
        [window.contentView setLayer:metalLayer];
        [window makeKeyAndOrderFront:NSApp];
        [NSApp activate];
        return metalLayer;
  }
}
