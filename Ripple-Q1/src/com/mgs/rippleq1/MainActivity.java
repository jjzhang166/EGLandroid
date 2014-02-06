package com.mgs.rippleq1;

import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.view.Window;
import android.view.WindowManager;

public class MainActivity extends Activity {
private GLSurfaceView view;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, 
                      		WindowManager.LayoutParams.FLAG_FULLSCREEN);
        view=new GLSurfaceView(this);
    	view.setEGLContextClientVersion(2);
        view.setRenderer(new GLRenderer());
        setContentView(view);
    }


    @Override
	protected void onPause() {
		// TODO Auto-generated method stub
		super.onPause();
		view.onPause();
	}


	@Override
	protected void onResume() {
		// TODO Auto-generated method stub
		super.onResume();
		view.onResume();
	}


	@Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }
    
}
