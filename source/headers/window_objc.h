
#ifdef __cplusplus
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_metal.h>
extern "C" {
#else
#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>
#import <QuartzCore/QuartzCore.h>
#endif
void ObjCPollEvents();
bool ObjCShouldClose();
CAMetalLayer *ObjCInitWindowAndGetMetalLayer();

#ifdef __cplusplus
}
#endif
