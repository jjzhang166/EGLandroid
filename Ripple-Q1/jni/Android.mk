LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := Native
LOCAL_SRC_FILES := Native.cpp\
				   com_mgs_rippleq1_LibNative.cpp
LOCAL_C_INCLUDES +=glm\
# Static libraries to link with
LOCAL_LDLIBS := -llog  -lGLESv2 -landroid -fopenmp


include $(BUILD_SHARED_LIBRARY)
