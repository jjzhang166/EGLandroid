package com.mgs.rippleq1;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.opengl.GLSurfaceView;

public class GLRenderer implements GLSurfaceView.Renderer {

	@Override
	public void onDrawFrame(GL10 gl) {
		// TODO Auto-generated method stub
		//gl.glClear(gl.GL_COLOR_BUFFER_BIT);
		LibNative.render();
	}

	@Override
	public void onSurfaceChanged(GL10 gl, int width, int height) {
		// TODO Auto-generated method stub
		//gl.glViewport(0, 0, width, height);
		LibNative.resize(width, height);
	}

	@Override
	public void onSurfaceCreated(GL10 gl, EGLConfig config) {
		// TODO Auto-generated method stub
		//gl.glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		LibNative.init();
	}

}
