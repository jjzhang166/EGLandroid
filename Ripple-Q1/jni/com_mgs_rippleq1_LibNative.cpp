/*
 * com_mgs_rippleq1_LibNative.cpp
 *
 *  Created on: Jan 27, 2014
 *      Author: Hassam
 */
#include<com_mgs_rippleq1_LibNative.h>
#include <Native.h>
JNIEXPORT void JNICALL Java_com_mgs_rippleq1_LibNative_init
  (JNIEnv *, jclass){
	InitializeOpenGL();
}

/*
 * Class:     com_mgs_rippleq1_LibNative
 * Method:    resize
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_com_mgs_rippleq1_LibNative_resize
  (JNIEnv *, jclass, jint width, jint height){
		resizeViewport(width,height);
}

/*
 * Class:     com_mgs_rippleq1_LibNative
 * Method:    render
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_mgs_rippleq1_LibNative_render
  (JNIEnv *, jclass){

	renderFrame();
}



