package com.mgs.rippleq1;

public class LibNative {
	
		static 
	{
			System.loadLibrary("Native");
		}

		public static native void init();
		public static native void resize(int width, int height);
		public static native void render();
	
}
