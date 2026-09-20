const int WIDTH = 350;
const int HEIGHT = 250;

#include <stdatomic.h>
#ifdef __cplusplus
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_metal.h>
extern "C" {
#else
#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>
#import <QuartzCore/QuartzCore.h>
#endif

bool ObjCShouldClose();
void ObjCPollEvents();
CAMetalLayer *ObjCInitWindowAndGetMetalLayer();
void ObjCDestroyWindow();
void ObjCGetFramebufferSize(int *width, int *height);
bool ObjCSwapchainNeedsRecreation();
void ObjCRunApplication();
#ifdef __cplusplus
};
#endif
