Commit History
==============
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