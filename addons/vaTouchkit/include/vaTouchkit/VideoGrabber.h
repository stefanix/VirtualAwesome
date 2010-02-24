#ifndef VATOUCHKIT_VIDEO_GRABBER
#define VATOUCHKIT_VIDEO_GRABBER


#if defined( TARGET_OSX ) || defined( TARGET_LINUX )
#include <vaTouchkit/VideoGrabberDc1394.h>
#elif defined( TARGET_WIN32 )
#include <vaTouchkit/VideoGrabberFlyCapture.h>
#endif


#endif

