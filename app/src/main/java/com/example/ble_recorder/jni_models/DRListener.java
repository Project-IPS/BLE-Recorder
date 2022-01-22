package com.example.ble_recorder.jni_models;

import android.app.Activity;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.util.Log;
import android.widget.TextView;

import com.example.ble_recorder.R;

import java.util.Arrays;

public class DRListener implements SensorEventListener {

    private final float[] gravityReading = new float[3];
    private final float[] magnetometerReading = new float[3];
    private final float[] rotationMatrix = new float[9];

    private static final String TAG = DRListener.class.getSimpleName();
    private final Activity activity;
    TextView gravityTV;
    TextView magnetometerTV;
    TextView rotationMatrixTV;

    private native void onStepDetected(float[] rotArray);

    /**
     * Initializes the starting position for the dead reckoning algorithm
     * @param x the x-coordinate in cm.
     * @param y the y-coordinate in cm.
     * @param z the z-coordinate in cm. It is not necessarily required.
     */
    private static native void jni_initializeDR(int x, int y, int z);

    public static DRListener initializeDR(Activity activity, int x, int y, int z){
        DRListener drListener = new DRListener(activity);
        jni_initializeDR(x, y, z);
        return drListener;
    }

    private DRListener(Activity activity){
        super();
        this.activity = activity;
        gravityTV = activity.findViewById(R.id.gravityView);
        magnetometerTV = activity.findViewById(R.id.magnetometerView);
        rotationMatrixTV = activity.findViewById(R.id.rotMatrixView);
    }

    @Override
    public void onSensorChanged(SensorEvent sensorEvent) {
        if(sensorEvent.sensor.getType() == Sensor.TYPE_GRAVITY){
            System.arraycopy(sensorEvent.values, 0, gravityReading, 0, gravityReading.length);
            Log.d(TAG, "Gravity update: "+ Arrays.toString(gravityReading));
            gravityTV.setText(Arrays.toString(gravityReading));
        }
        else if(sensorEvent.sensor.getType() == Sensor.TYPE_STEP_DETECTOR){
            SensorManager.getRotationMatrix(rotationMatrix, null, gravityReading, magnetometerReading);
            Log.d(TAG, "Step Detected: "+Arrays.toString(rotationMatrix));
            rotationMatrixTV.setText(Arrays.toString(rotationMatrix));
            onStepDetected(rotationMatrix);
        }
        else{
            //sensorEvent.sensor.getType() == Sensor.TYPE_MAGNETIC_FIELD;
            System.arraycopy(sensorEvent.values, 0, magnetometerReading,
                    0, magnetometerReading.length);
            Log.d(TAG, "Magnetometer Update: "+Arrays.toString(magnetometerReading));
            magnetometerTV.setText(Arrays.toString(magnetometerReading));
        }
    }

    @Override
    public void onAccuracyChanged(Sensor sensor, int i) {
        if(sensor.getType()==Sensor.TYPE_MAGNETIC_FIELD){
            switch(i){
                case SensorManager.SENSOR_STATUS_ACCURACY_HIGH:
                    //Good data
                    break;
                case SensorManager.SENSOR_STATUS_ACCURACY_MEDIUM:
                    //okay data.
                    break;
                case SensorManager.SENSOR_STATUS_ACCURACY_LOW:
                    //Needs Calibration
                case SensorManager.SENSOR_STATUS_UNRELIABLE:
                    //Needs Calibration
                    //TODO: Sensor calibration prompt
                    magnetometerTV.setText(R.string.calibrate_mag);
            }
        }
    }
}
