#include <jni.h>
#include "./src/cpp_framework.h"
#include "./src/resolver.h"

/**
 * This method must allocate a ConfiguredBeacon::Builder object dynamically and return a pointer to it.
 */
extern "C"
JNIEXPORT jlong JNICALL
Java_com_example_ble_1recorder_jni_1models_ConfiguredBeacon_00024Builder_jni_1allocate([[maybe_unused]] JNIEnv *env, [[maybe_unused]] jclass clazz) {
    auto* builder_ptr = new ConfiguredBeacon::Builder();
    return (long)builder_ptr;
}

/**
 * This method must free the space allocated to ConfiguredBeacon::Builder object.
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_example_ble_1recorder_jni_1models_ConfiguredBeacon_00024Builder_jni_1free([[maybe_unused]] JNIEnv *env, [[maybe_unused]] jclass clazz, jlong pointer) {
    auto* builder_ptr = (ConfiguredBeacon::Builder*)pointer;
    delete builder_ptr;
}

/**
 * This method must call the create() method of the underlying ConfiguredBeacon::Builder object
 * and return a pointer to it.
 */
extern "C"
JNIEXPORT jlong JNICALL
Java_com_example_ble_1recorder_jni_1models_ConfiguredBeacon_00024Builder_jni_1create([[maybe_unused]] JNIEnv *env, [[maybe_unused]] jobject thiz, jlong pointer) {
    auto* builder_ptr = (ConfiguredBeacon::Builder*)pointer;
    return (long)(builder_ptr->create());
}

/**
 * This method must call the setId() method of the underlying ConfiguredBeacon::Builder object
 * and return a pointer to it.
 */
extern "C"
JNIEXPORT jlong JNICALL
Java_com_example_ble_1recorder_jni_1models_ConfiguredBeacon_00024Builder_jni_1setId(
        [[maybe_unused]] JNIEnv *env, [[maybe_unused]] jobject thiz, jlong pointer,
                                                                                    jstring uuid, jint major, jint minor) {
    auto* builder_ptr = (ConfiguredBeacon::Builder*)pointer;
    const char* str = env->GetStringUTFChars(uuid,nullptr);
    string id = str;
    env->ReleaseStringUTFChars(uuid,str);
    return (long)(builder_ptr->setId(id,major,minor));
}

/**
 * This method must call the setPos() method of the underlying ConfiguredBeacon::Builder object
 * and return a pointer to it.
 */
extern "C"
JNIEXPORT jlong JNICALL
Java_com_example_ble_1recorder_jni_1models_ConfiguredBeacon_00024Builder_jni_1setPos([[maybe_unused]] JNIEnv *env, [[maybe_unused]] jobject thiz, jlong pointer,
                                                                                     jint x, jint y, jint z) {
    auto* builder_ptr = (ConfiguredBeacon::Builder*)pointer;
    return (long)(builder_ptr->setPos(x,y,z));
}

/**
 * This method must call the setRssiD0() method of the underlying ConfiguredBeacon::Builder object
 * and return a pointer to it.
 */
extern "C"
JNIEXPORT jlong JNICALL
Java_com_example_ble_1recorder_jni_1models_ConfiguredBeacon_00024Builder_jni_1setRssiD0([[maybe_unused]] JNIEnv *env, [[maybe_unused]] jobject thiz, jlong pointer,
                                                                                        jint rssi) {
    auto* builder_ptr = (ConfiguredBeacon::Builder*)pointer;
    return (long)(builder_ptr->setRssiD0(rssi));
}

/**
 * This method must call the setD0() method of the underlying ConfiguredBeacon::Builder object
 * and return a pointer to it.
 */
extern "C"
JNIEXPORT jlong JNICALL
Java_com_example_ble_1recorder_jni_1models_ConfiguredBeacon_00024Builder_jni_1setD0([[maybe_unused]] JNIEnv *env, [[maybe_unused]] jobject thiz, jlong pointer,
                                                                                    jint d0) {
    auto* builder_ptr = (ConfiguredBeacon::Builder*)pointer;
    return (long)(builder_ptr->setD0(d0));
}

/**
 * This method must call the setBeaconCoeff() method of the underlying ConfiguredBeacon::Builder object
 * and return a pointer to it.
 */
extern "C"
JNIEXPORT jlong JNICALL
Java_com_example_ble_1recorder_jni_1models_ConfiguredBeacon_00024Builder_jni_1setBeaconCoeff(
        [[maybe_unused]] JNIEnv *env, [[maybe_unused]] jobject thiz, jlong pointer, jfloat coeff) {
    auto* builder_ptr = (ConfiguredBeacon::Builder*)pointer;
    return (long)(builder_ptr->setBeaconCoeff(coeff));
}

/**
 * This method must call the setXSigma() method of the underlying ConfiguredBeacon::Builder object
 * and return a pointer to it.
 */
extern "C"
JNIEXPORT jlong JNICALL
Java_com_example_ble_1recorder_jni_1models_ConfiguredBeacon_00024Builder_jni_1setXSigma([[maybe_unused]] JNIEnv *env, [[maybe_unused]] jobject thiz, jlong pointer,
                                                                                        jfloat x_sig) {
    auto* builder_ptr = (ConfiguredBeacon::Builder*)pointer;
    return (long)(builder_ptr->setXSigma(x_sig));
}

/**
 * This method must call the registerFilter() method of the underlying ConfiguredBeacon::Builder object
 * and return a pointer to it.
 */
extern "C"
JNIEXPORT jlong JNICALL
Java_com_example_ble_1recorder_jni_1models_ConfiguredBeacon_00024Builder_jni_1registerFilter(
        [[maybe_unused]] JNIEnv *env, [[maybe_unused]] jobject thiz, jlong pointer, jlong filter_ptr) {
    auto* builder_ptr = (ConfiguredBeacon::Builder*)pointer;
    auto* filter_pointer = (Filter*)filter_ptr;
    return (long)(builder_ptr->registerFilter(filter_pointer));
}

/**
 * This method must call the removeFilter() method of the underlying ConfiguredBeacon::Builder object
 * and return a pointer to it.
 */
extern "C"
JNIEXPORT jlong JNICALL
Java_com_example_ble_1recorder_jni_1models_ConfiguredBeacon_00024Builder_jni_1removeFilter(
        [[maybe_unused]] JNIEnv *env, [[maybe_unused]] jobject thiz, jlong pointer, jlong filter_ptr) {
    auto* builder_ptr = (ConfiguredBeacon::Builder*)pointer;
    auto* filter_pointer = (Filter*)filter_ptr;
    return (long)(builder_ptr->removeFilter(filter_pointer));
}

/**
 * This method must call the build() method of the underlying ConfiguredBeacon::Builder object
 * and return a pointer to the ConfiguredBeacon object. This can then be passed to addToConfiguredBeacons(...).
 */
extern "C"
JNIEXPORT jlong JNICALL
Java_com_example_ble_1recorder_jni_1models_ConfiguredBeacon_00024Builder_jni_1build([[maybe_unused]] JNIEnv *env, [[maybe_unused]] jobject thiz, jlong pointer) {
    auto* builder_ptr = (ConfiguredBeacon::Builder*)pointer;
    //build() would return a reference to the dynamically allocated ConfigureBeacon object
    //and this function would return the memory address of that object.
    return (long)(&builder_ptr->build());
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_example_ble_1recorder_jni_1models_ConfiguredBeacon_addToConfiguredBeacons([[maybe_unused]] JNIEnv *env, [[maybe_unused]] jclass clazz, jlong beacon_ptr) {
    auto* configured_beacon_ptr = (ConfiguredBeacon*)beacon_ptr;
    return addToConfiguredBeacons(*configured_beacon_ptr);
}

extern "C"
JNIEXPORT jlong JNICALL
Java_com_example_ble_1recorder_jni_1models_MeanFilter_jni_1allocate([[maybe_unused]] JNIEnv *env, [[maybe_unused]] jclass clazz,
                                                                    jint window_size) {
    auto* mean_filter_ptr = new MeanFilter(window_size);
    return (long)mean_filter_ptr;
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_ble_1recorder_jni_1models_MeanFilter_jni_1free([[maybe_unused]] JNIEnv *env, [[maybe_unused]] jclass clazz,
                                                                jlong pointer) {
    auto* mean_filter_ptr = (MeanFilter*)pointer;
    delete mean_filter_ptr;
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_ble_1recorder_jni_1models_Trilateration_jni_1startTrilateration([[maybe_unused]] JNIEnv *env, [[maybe_unused]] jclass clazz) {
    startTrilateration();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_ble_1recorder_jni_1models_Trilateration_jni_1stopTrilateration([[maybe_unused]] JNIEnv *env, [[maybe_unused]] jclass clazz) {
    stopTrilateration();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_ble_1recorder_jni_1models_BeaconCallback_jni_1resolve(JNIEnv *env, [[maybe_unused]] jclass clazz,
                                                                       jstring uuid, jint major,
                                                                       jint minor, jint rssi) {

    const char *str = env->GetStringUTFChars(uuid , nullptr);
    string id = str;
    pool.post([id,major,minor,rssi]{
        resolve(id,major,minor,rssi);
    });
    env->ReleaseStringUTFChars(uuid, str);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_ble_1recorder_jni_1models_DRListener_onStepDetected(JNIEnv *env, [[ maybe_unused ]] jobject thiz,
                                                                     jfloatArray rot_array) {
    int len = env-> GetArrayLength(rot_array);
    float carray[len];
    env->GetFloatArrayRegion(rot_array,0,len,carray);
    onStepDetected(carray);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_ble_1recorder_jni_1models_DRListener_jni_1initializeDR([[ maybe_unused ]] JNIEnv *env, [[ maybe_unused ]] jclass clazz,
                                                                        jint x, jint y, jint z) {
    initializeDeadReckoning(x,y,z);
}
