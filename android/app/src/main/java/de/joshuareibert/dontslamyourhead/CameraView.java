package de.joshuareibert.dontslamyourhead;

import android.content.Context;
import android.hardware.Camera;
import android.util.AttributeSet;

import org.opencv.android.JavaCameraView;

import java.util.List;

public class CameraView extends JavaCameraView {
    public CameraView(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    public void setResolution(int width, int height) {
        disconnectCamera();
        mMaxHeight = height;
        mMaxWidth = width;
        connectCamera(getWidth(), getHeight());
    }

    public List<Camera.Size> getResolutionList() {
        return mCamera.getParameters().getSupportedPreviewSizes();
    }
}
