Commit History
==============
## Java interface is functional
As of this commit the Java interface is functional and tested. Though the inherent C++ code is still lacking 
two major functions: path-loss model and trilateration function.
1. Updates
   - Entire C++ code was cleaned and tailored. beacon_sim.h and beacon_sim.cpp was deleted. Only the necessary 
   C++ files are included now.
   - sim/BeaconSim.java was created to simulate the asynchronous callbacks from realtime beacons.
   - Real Beacon Scanning was commented out in the MainActivity. Instead Simulated Scanning was setup.
   - Changes were made in almost every Cpp file but most notably inside resolver.h, active_beacon.h(cpp),
   configured_beacon.h(cpp), ble_recorder.cpp and filter.h and global.h.
   - All the cout statements were replaced with LOGI(...).
   - Inside jni_models only ConfiguredBeacon.java was changed viz. the setId() method.
2. TODOs
   - Add distance estimation and trilateration function when ready.
   - Add the matrix c++ libraries.
   - Add the Dead Reckoning logic.
   
## Java interface for native code is complete
As of this commit the java interface for the native code is complete though its not tested.
1. Updates
   - The Java interface consists of 6 models(as of now): BeaconCallback.java, ConfiguredBeacon.java,
   Filter.java, MeanFilter.java, Position.java and Trilateration.java.
   - All the necessary cpp source files were added to CMakeLists.txt.
   - Cpp-Framework.cpp and Cpp-Framework.h were renamed to cpp_framework.cpp and cpp_framework.h respectively.
   - Much of the C++ code was tailored.
2. TODOs
   - The native side of some java functions is not yet complete viz. BeaconCallback.resolve(...) and
     Position Update Callback("Name Dependent Code").
   - The cout statements in C++ need to be replaced with log statements.
   - Testing the java native interface.
   
## JNI Initialized
This commit is not functional. It just sets up the idea as to how the integration is supposed
to take place.
1. Updates
   - A class ConfiguredBeacon(java) is set. It should have a Builder(for builder pattern) and
   the functions corresponding to the ConfiguredBeacon(c++) class and its builder.
   - All the C++ backend files are added except for matrix.h.
2. TODOs
   - The c++ files need to be tailored. As of now they are set as if they were stand-alone.
   - Complete the JNI layer.
   - Complete the C++ backend once its stand-alone variant is finished.
   
## Minimal Scanning is set
The app just runs one iteration of BLE scanning under the right state (user has already given
location permission and  turned on bluetooth before the activity starts).
1. Updates
    - scanLeDevice() performs a BLE scan once for a specified  SCAN_PERIOD in ms.
    - Asks user to give location permission.
    - Asks user to turn on their bluetooth.
2. TODOs
    - Lots of bugs and errors to be corrected.
    - Making the app more functional.