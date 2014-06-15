#FileName:Android.mk
#Description:makefile of Helloworld
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := HelloWorld 
LOCAL_SRC_FILES := HelloWorld.c
  
include $(BUILD_SHARED_LIBRARY)
