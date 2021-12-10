package com.example.ble_recorder;

import android.Manifest;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.le.BluetoothLeScanner;
import android.bluetooth.le.ScanCallback;
import android.bluetooth.le.ScanResult;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.widget.Toast;

import androidx.activity.result.contract.ActivityResultContracts;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;

import java.util.List;

public class MainActivity extends AppCompatActivity {

    private static final String TAG = MainActivity.class.getName();

    BluetoothAdapter bluetoothAdapter = null;
    BluetoothLeScanner bluetoothLeScanner = null;
    ScanCallback bleScanCallback = null;
    private static final long SCAN_PERIOD = 100000;
    private boolean scanning = false;
    Handler handler = new Handler();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        checkPermissions();
        boolean result = setupBluetooth();

        if(result){
            setScanCallback();
            scanLeDevice();
        }
    }

    @Override
    protected void onStop() {
        scanLeDevice();
        super.onStop();
    }

    /**
     * Checks for location permission.
     */
    public void checkPermissions(){
        Log.d(TAG, "Checking Permissions");
        if(ContextCompat.checkSelfPermission(this, Manifest.permission.ACCESS_FINE_LOCATION)== PackageManager.PERMISSION_DENIED){
            ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.ACCESS_FINE_LOCATION},1);
        }
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.S) {
            checkSelfPermission(Manifest.permission.BLUETOOTH_SCAN);
        }
    }

    /**
     * 1. Checks if device has bluetooth adapter.
     * 2. Asks user to enable bluetooth, if not already.
     * 3. Checks if BLE is present.
     * @return true if all the checks above are fulfilled.
     */
    public boolean setupBluetooth(){

        bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();

        //Check if the device has bluetooth.
        if(bluetoothAdapter == null){
            Log.d(TAG,"Bluetooth Not Present on Device");
            showLongToast("Bluetooth Not Present on Device");
            return false;
        }

        //enable bluetooth if it is not already enabled.
        if(!bluetoothAdapter.isEnabled()){
            registerForActivityResult(new ActivityResultContracts.StartActivityForResult(), result -> {
                if(result.getResultCode() ==  RESULT_OK){
                    Log.d(TAG, "Bluetooth Setup Successful");
                }
                else{
                    Log.d(TAG,"Bluetooth Enable Request denied");
                    showShortToast("Request Denied. Cannot proceed with  scanning");
                }
            }).launch(new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE));
        }

        if(!bluetoothAdapter.isEnabled()){
            return false;
        }

        bluetoothLeScanner = bluetoothAdapter.getBluetoothLeScanner();

        if(bluetoothLeScanner == null){
            Log.d(TAG,"BLE not present");
            showShortToast("BLE not present on device");
            return false;
        }
        Log.d(TAG, "Bluetooth Setup done" + bluetoothLeScanner.toString());

        return true;
    }

    public void setScanCallback(){
        Log.d(TAG,"Scan Callback set");
        bleScanCallback = new ScanCallback() {
            @Override
            public void onScanResult(int callbackType, ScanResult result) {
                super.onScanResult(callbackType, result);
                Log.d(TAG,"Thread = "+ Thread.currentThread()+" Callback Type = "+callbackType);
                Log.d(TAG,"Result = "+result.toString());
            }

            @Override
            public void onBatchScanResults(List<ScanResult> results) {
                super.onBatchScanResults(results);
                Log.d(TAG,"Result = "+results.toString());
            }

            @Override
            public void onScanFailed(int errorCode) {
                super.onScanFailed(errorCode);
                Log.d(TAG,"Error Code = "+errorCode);
            }
        };
    }

    public void scanLeDevice(){
        if (!scanning) {
            // Stops scanning after a predefined scan period.
            handler.postDelayed(() -> {
                scanning = false;
                Log.d(TAG, "Scan stopped");
                bluetoothLeScanner.stopScan(bleScanCallback);
            }, SCAN_PERIOD);

            scanning = true;
            Log.d(TAG,"Scan started");
            bluetoothLeScanner.startScan(bleScanCallback);
        } else {
            scanning = false;
            Log.d(TAG, "Scan stopped");
            bluetoothLeScanner.stopScan(bleScanCallback);
        }
    }

    public void showLongToast(String message){
        Toast.makeText(this, message, Toast.LENGTH_LONG).show();
    }

    public void showShortToast(String message){
        Toast.makeText(this, message, Toast.LENGTH_SHORT).show();
    }

}