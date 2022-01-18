package com.example.ble_recorder.sim;

import android.util.Log;

import androidx.annotation.NonNull;

import com.example.ble_recorder.jni_models.BeaconCallback;

import java.util.Random;

/**
 * A class that simulates beacon callback responses.
 * Made for the purpose of unit-testing Java-C++ interface.
 */
public class BeaconSim {

    private static final String TAG = BeaconSim.class.getName();

    private String uuid = "b2dd3555ea394f08862a00fb026a800b".toUpperCase();
    private final int major;
    private final int minor;

    @SuppressWarnings("FieldCanBeLocal")
    private final int callback_frequency = 300;     //in ms
    private final Random generator = new Random();
    private final int mean;
    private final int deviance;
    private boolean isRunning = false;

    public BeaconSim(int major, int minor, int mean, int deviance){
        this.major = major;
        this.minor = minor;
        this.mean = mean;
        this.deviance = deviance;
        generator.setSeed(System.nanoTime());
    }

    @SuppressWarnings("unused")
    public BeaconSim(String uuid, int major, int minor, int mean, int deviance){
        this(major,minor,mean,deviance);
        this.uuid = uuid;
    }

    private void generateCallbacks(int iterations){
        for(int i=0; i<iterations; i++){
            int current_rssi = (int) (generator.nextGaussian()*deviance+mean);
            Log.d(TAG, "Callback produced("+System.currentTimeMillis()+") : "+toString()+" : "+current_rssi);
            BeaconCallback.resolve(uuid, major, minor, current_rssi);
            try {
                Thread.sleep(callback_frequency);
            } catch (InterruptedException e) {
                Log.w(TAG, e.toString());
            }
        }
        isRunning = false;
    }

    public void begin(int iterations){

        if(!isRunning) {
            isRunning = true;
            Log.d(TAG, "Simulation started for: "+toString());
            new Thread(() -> generateCallbacks(iterations)).start();
        }
        else{
            Log.w(TAG, "begin() called on a simulator that was already" +
                    "running");
        }
    }

    @NonNull
    @Override
    public String toString(){
        return "BeaconSim {"+uuid+" , "+major+" , "+minor+"}";
    }
}
