#import "../headers/window_objc.h"
#import <AppKit/AppKit.h>

static NSWindow *window;
static bool framebufferResized = false;
static bool shouldClose = false;

@interface VulkanWindowDelegate : NSObject <NSWindowDelegate>
@end

@implementation VulkanWindowDelegate

- (void)windowDidResize:(NSNotification *)notification {
  framebufferResized = true;
}

- (BOOL)windowShouldClose:(NSWindow *)sender
{
    shouldClose = true;
    return NO;
}
@end

static VulkanWindowDelegate *windowDelegate;

void ObjCGetFramebufferSize(int *width, int *height) {
  NSRect frame = [window.contentView bounds];
  NSSize backingSize = [window.contentView convertSizeToBacking:frame.size];

  *width = (int)backingSize.width;
  *height = (int)backingSize.height;
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

bool ObjCSwapchainNeedsRecreation() {
  if (framebufferResized) {
    framebufferResized = false;
    return true;
  }
  return false;
}

bool ObjCShouldClose() {
    return shouldClose;
}

void ObjCDestroyWindow()
{
    [window orderOut:nil];

    [window setDelegate:nil];

    windowDelegate = nil;
    window = nil;
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
        windowDelegate = [[VulkanWindowDelegate alloc] init];
        [window setDelegate:windowDelegate];

        [window.contentView setWantsLayer:YES];
        CAMetalLayer *metalLayer = [CAMetalLayer layer];


        metalLayer.delegate = window.contentView;

        metalLayer.frame = window.contentView.bounds;
        metalLayer.autoresizingMask =
            kCALayerWidthSizable | kCALayerHeightSizable;


        metalLayer.contentsScale = window.contentView.window.backingScaleFactor;

        metalLayer.drawableSize =[window.contentView convertSizeToBacking:window.contentView.bounds.size];

        [window.contentView setLayer:metalLayer];
        [window makeKeyAndOrderFront:NSApp];
        [NSApp activate];
        return metalLayer;
  }
}
