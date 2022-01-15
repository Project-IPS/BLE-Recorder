Commit History
==============
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