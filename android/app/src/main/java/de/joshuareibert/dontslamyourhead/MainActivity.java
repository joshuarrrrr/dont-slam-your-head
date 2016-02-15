package de.joshuareibert.dontslamyourhead;

import android.Manifest;
import android.app.ActionBar;
import android.app.Activity;
import android.content.pm.PackageManager;
import android.hardware.Camera;
import android.os.Bundle;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.SurfaceView;
import android.view.WindowManager;
import android.widget.FrameLayout;
import android.widget.LinearLayout;
import android.widget.Toast;

import org.opencv.android.CameraBridgeViewBase;
import org.opencv.android.CameraBridgeViewBase.CvCameraViewListener2;
import org.opencv.android.JavaCameraView;
import org.opencv.core.Mat;

import com.unity3d.player.UnityPlayer;
import com.unity3d.player.UnityPlayerActivity;

public class MainActivity extends UnityPlayerActivity implements CvCameraViewListener2 {

    private CameraView mCameraView;
    private final int mCameraPermissionRequestCode = 0;
    private Mat mRgba;
    private Mat mGray;
    private Mat mDepth;
    private int width = 320;
    private int height = 240;
    private float translation[] = {0.0f, 0.0f, 0.0f};
    private float rotation[] = {0.0f, 0.0f, 0.0f, 0.0f};
    private float idepth[] = null;

    static {
        System.loadLibrary("lsd-jni");
    }

    // native functions
    public native void initSLAM(int width, int height);
    public native void updateSLAM(long grayImgAddress, long rgbaImgAddress, long depthImgAddress, float[] depthMap);
    public native void resetSLAM();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        initSLAM(width, height);
        idepth = new float[width * height];
        //getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
        //getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
        //        WindowManager.LayoutParams.FLAG_FULLSCREEN);
        //setContentView(R.layout.activity_main);
    }

    @Override
    public void onResume() {
        super.onResume();
        /*if (ContextCompat.checkSelfPermission(this, Manifest.permission.CAMERA) !=
                PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(this,
                    new String[]{Manifest.permission.CAMERA},
                    mCameraPermissionRequestCode);
        } else*/
        initCameraView();
    }

    @Override
    public void onPause() {
        super.onPause();
        if (mCameraView != null)
            mCameraView.disableView();
    }

    public void onDestroy() {
        super.onDestroy();
        if (mCameraView != null)
            mCameraView.disableView();
    }

    public void setTranslation(float x, float y, float z) {
        translation[0] = x;
        translation[1] = y;
        translation[2] = z;
        Log.d("DSYH_TRANSLATION",
                String.valueOf(x) + ", " + String.valueOf(y) + ", " + String.valueOf(z));
    }

    public void setRotation(float x, float y, float z, float w) {
        rotation[0] = x;
        rotation[1] = y;
        rotation[2] = z;
        rotation[3] = w;
    }

    public float getTranslationX() {
        return translation[0];
    }

    public float getTranslationY() {
        return translation[1];
    }

    public float getTranslationZ() {
        return translation[2];
    }

    public float getRotationX() {
        return rotation[0];
    }

    public float getRotationY() {
        return rotation[1];
    }

    public float getRotationZ() {
        return rotation[2];
    }

    public float getRotationW() {
        return rotation[3];
    }

    public float[] getIDepth() {
        return idepth;
    }

    /*@Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_reset) {
            //resetSLAM();
            return true;
        }

        return super.onOptionsItemSelected(item);
    }*/

    /*@Override
    public void onRequestPermissionsResult(int requestCode,
                                           String permissions[], int[] grantResults) {
        switch (requestCode) {
            case mCameraPermissionRequestCode: {
                // If request is cancelled, the result arrays are empty.
                if (grantResults.length > 0
                        && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                    initCameraView();
                } else {
                    Toast.makeText(
                            this,
                            R.string.camera_permission_denied_msg,
                            Toast.LENGTH_LONG
                    ).show();
                    this.finish();
                }
                break;
            }
        }
    }*/

    public void onCameraViewStarted(int width, int height) {
        mGray = new Mat();
        mRgba = new Mat();
        mDepth = new Mat();
        mCameraView.setFixedFocus();
    }

    public void onCameraViewStopped() {
        mGray.release();
        mRgba.release();
    }

    @Override
    public Mat onCameraFrame(CameraBridgeViewBase.CvCameraViewFrame inputFrame) {
        mRgba = inputFrame.rgba();
        mGray = inputFrame.gray();
        updateSLAM(mGray.getNativeObjAddr(), mRgba.getNativeObjAddr(), mDepth.getNativeObjAddr(),
                idepth);
        return mRgba;
    }

    private void initCameraView() {
        if (mCameraView == null) {
            //mCameraView = (CameraView) findViewById(R.id.cameraView);
            mCameraView = new CameraView(getApplicationContext(), 0);
            mCameraView.setVisibility(SurfaceView.VISIBLE);
            mCameraView.setCvCameraViewListener(this);
            mCameraView.setResolution(1280, 720);
            LinearLayout.LayoutParams layoutParams = new LinearLayout.LayoutParams(
                    LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.MATCH_PARENT);
            UnityPlayer.currentActivity.addContentView(mCameraView, layoutParams);
        }
        mCameraView.enableView();
    }
}
