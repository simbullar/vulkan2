const int WIDTH = 800;
const int HEIGHT = 600;

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
void ObjCDestroyWindow();
void ObjCGetFramebufferSize(int *width, int *height);
bool ObjCSwapchainNeedsRecreation();

#ifdef __cplusplus
};
#endif
