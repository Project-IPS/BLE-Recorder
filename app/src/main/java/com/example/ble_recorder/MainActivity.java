package com.example.ble_recorder;

import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.util.Log;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import com.example.ble_recorder.jni_models.ConfiguredBeacon;
import com.example.ble_recorder.jni_models.DRListener;
import com.example.ble_recorder.jni_models.MeanFilter;
import com.example.ble_recorder.jni_models.Trilateration;
import com.example.ble_recorder.sim.BeaconSim;

import java.util.Vector;

public class MainActivity extends AppCompatActivity {

    static {
       System.loadLibrary("ble_recorder");
    }

    private static final String TAG = MainActivity.class.getName();
    private SensorManager sensorManager;
    private Sensor gravitySensor;
    private Sensor magnetometerSensor;
    private Sensor stepDetectorSensor;
    Vector<BeaconSim> beaconSims = new Vector<>();
    DRListener drListener;

//    //For Real Scanning
//    BluetoothAdapter bluetoothAdapter = null;
//    BluetoothLeScanner bluetoothLeScanner = null;
//    ScanCallback bleScanCallback = null;
//    private static final long SCAN_PERIOD = 100000;     //in ms
//    private boolean scanning = false;
//    Handler handler = new Handler();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.dr_view);

        Log.d(TAG, "onCreate()");
//        initializeConfiguredBeacons();
//        initializeBeaconSims();
//        startSimulating(3);

        initializeDeadReckoning();
//        //For Real Scanning
//        checkPermissions();
//        boolean result = setupBluetooth();
//
//        if(result){
//            setScanCallback();
//            scanLeDevice();
//        }
    }

    @Override
    protected void onResume() {
        super.onResume();
        registerSensorListeners();
    }

    @Override
    protected void onPause(){
        super.onPause();
        unregisterListeners();
    }

    @Override
    protected void onStart() {
        super.onStart();
    }

    @Override
    protected void onStop() {
//        //For Real Scanning
//        scanLeDevice();
        super.onStop();
    }

//    //For Real Scanning
//    /**
//     * Checks for location permission.
//     */
//    public void checkPermissions(){
//        Log.d(TAG, "Checking Permissions");
//        if(ContextCompat.checkSelfPermission(this, Manifest.permission.ACCESS_FINE_LOCATION)== PackageManager.PERMISSION_DENIED){
//            ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.ACCESS_FINE_LOCATION},1);
//        }
//        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.S) {
//            checkSelfPermission(Manifest.permission.BLUETOOTH_SCAN);
//        }
//    }
//
//    /**
//     * 1. Checks if device has bluetooth adapter.
//     * 2. Asks user to enable bluetooth, if not already.
//     * 3. Checks if BLE is present.
//     * @return true if all the checks above are fulfilled.
//     */
//    public boolean setupBluetooth(){
//
//        bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
//
//        //Check if the device has bluetooth.
//        if(bluetoothAdapter == null){
//            Log.d(TAG,"Bluetooth Not Present on Device");
//            showLongToast("Bluetooth Not Present on Device");
//            return false;
//        }
//
//        //enable bluetooth if it is not already enabled.
//        if(!bluetoothAdapter.isEnabled()){
//            registerForActivityResult(new ActivityResultContracts.StartActivityForResult(), result -> {
//                if(result.getResultCode() ==  RESULT_OK){
//                    Log.d(TAG, "Bluetooth Setup Successful");
//                }
//                else{
//                    Log.d(TAG,"Bluetooth Enable Request denied");
//                    showShortToast("Request Denied. Cannot proceed with  scanning");
//                }
//            }).launch(new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE));
//        }
//
//        if(!bluetoothAdapter.isEnabled()){
//            return false;
//        }
//
//        bluetoothLeScanner = bluetoothAdapter.getBluetoothLeScanner();
//
//        if(bluetoothLeScanner == null){
//            Log.d(TAG,"BLE not present");
//            showShortToast("BLE not present on device");
//            return false;
//        }
//        Log.d(TAG, "Bluetooth Setup done" + bluetoothLeScanner.toString());
//
//        return true;
//    }
//
//    public void setScanCallback(){
//        Log.d(TAG,"Scan Callback set");
//        bleScanCallback = new ScanCallback() {
//            @Override
//            public void onScanResult(int callbackType, ScanResult result) {
//                super.onScanResult(callbackType, result);
//                Log.d(TAG,"Thread = "+ Thread.currentThread()+" Callback Type = "+callbackType);
//                Log.d(TAG,"Result = "+result.toString());
//            }
//
//            @Override
//            public void onBatchScanResults(List<ScanResult> results) {
//                super.onBatchScanResults(results);
//                Log.d(TAG,"Result = "+results.toString());
//            }
//
//            @Override
//            public void onScanFailed(int errorCode) {
//                super.onScanFailed(errorCode);
//                Log.d(TAG,"Error Code = "+errorCode);
//            }
//        };
//    }
//
//    public void scanLeDevice(){
//        if (!scanning) {
//            // Stops scanning after a predefined scan period.
//            handler.postDelayed(() -> {
//                scanning = false;
//                Log.d(TAG, "Scan stopped");
//                bluetoothLeScanner.stopScan(bleScanCallback);
//            }, SCAN_PERIOD);
//
//            scanning = true;
//            Log.d(TAG,"Scan started");
//            bluetoothLeScanner.startScan(bleScanCallback);
//        } else {
//            scanning = false;
//            Log.d(TAG, "Scan stopped");
//            bluetoothLeScanner.stopScan(bleScanCallback);
//        }
//    }

    public void initializeDeadReckoning(){
        sensorManager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);
        gravitySensor = sensorManager.getDefaultSensor(Sensor.TYPE_GRAVITY);
        magnetometerSensor = sensorManager.getDefaultSensor(Sensor.TYPE_MAGNETIC_FIELD);
        stepDetectorSensor = sensorManager.getDefaultSensor(Sensor.TYPE_STEP_DETECTOR);
        drListener = DRListener.initializeDR(this, 0,0,0);
    }

    public void registerSensorListeners(){
        sensorManager.registerListener(drListener,stepDetectorSensor,SensorManager.SENSOR_DELAY_NORMAL);
        sensorManager.registerListener(drListener, gravitySensor, SensorManager.SENSOR_DELAY_NORMAL);
        sensorManager.registerListener(drListener,magnetometerSensor,SensorManager.SENSOR_DELAY_NORMAL);
    }

    public void unregisterListeners(){
        sensorManager.unregisterListener(drListener);
    }

    public void initializeConfiguredBeacons(){
        for (int i = 0; i < 10; i++) {
            ConfiguredBeacon.Builder builder = ConfiguredBeacon.Builder.allocate();
            MeanFilter mf = MeanFilter.allocate(3);
            if(i%2==0){     //id would be odd
            builder.setId("b2dd3555ea394f08862a00fb026a800b".toUpperCase(),i+1,i+1).
                    setPos(660,-500-250*i,240).setRssiD0(-81).setD0(100).setBeaconCoeff(1).
                    setXSigma(0).registerFilter(mf);
            }
            else{
                builder.setId("b2dd3555ea394f08862a00fb026a800b".toUpperCase(),i+1,i+1).
                        setPos(0,-500-250*i,240).setRssiD0(-81).setD0(100).setBeaconCoeff(1).
                        setXSigma(0).registerFilter(mf);
            }
            ConfiguredBeacon.addToConfiguredBeacons(builder.build());
            MeanFilter.free(mf);
            ConfiguredBeacon.Builder.free(builder);
        }
    }

    public void initializeBeaconSims(){
        //Initialize the 9 beacons sims as per the test case.
        int[] mean_rssi_values = new int[]{-98, -96, -93, -91, -89, -91, -93, -96, -98};
        for(int i = 0; i<9; i++) {
            beaconSims.add(new BeaconSim(i+1,i+1,mean_rssi_values[i],5));
        }
    }

    public void startSimulating(int it){
        Trilateration.startTrilateration();
        for(BeaconSim sim : beaconSims){
            sim.begin(it);
        }
        Handler handler = new Handler(Looper.getMainLooper());
        handler.postDelayed(Trilateration::stopTrilateration, it* 350L);
    }

    public void showLongToast(String message){
        Toast.makeText(this, message, Toast.LENGTH_LONG).show();
    }

    public void showShortToast(String message){
        Toast.makeText(this, message, Toast.LENGTH_SHORT).show();
    }
}