const int WIDTH = 800;
const int HEIGHT = 600;

#ifdef __cplusplus
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_metal.h>
extern "C++" {
auto ObjCGetWindowUserPointer();
}
extern "C" {
#else
#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>
#import <QuartzCore/QuartzCore.h>
NSApplication *ObjCGetWindowUserPointer();
#endif
void ObjCPollEvents();
bool ObjCShouldClose();
CAMetalLayer *ObjCInitWindowAndGetMetalLayer();

#ifdef __cplusplus
}
#endif
