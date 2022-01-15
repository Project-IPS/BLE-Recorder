#include <jni.h>
#include "./src/Cpp-Framework.h"

// Write C++ code here.
//
// Do not forget to dynamically load the C++ library into your application.
//
// For instance,
//
// In MainActivity.java:
//    static {
//       System.loadLibrary("ble_recorder");
//    }
//
// Or, in MainActivity.kt:
//    companion object {
//      init {
//         System.loadLibrary("ble_recorder")
//      }
//    }

/**
 * This method must allocate a ConfiguredBeacon::Builder object dynamically and return a pointer to it.
 */
extern "C"
JNIEXPORT jlong JNICALL
Java_com_example_ble_1recorder_jni_1models_ConfiguredBeacon_00024Builder_jni_1allocate(JNIEnv *env,
                                                                                       jclass clazz) {
    auto* builder_ptr = new ConfiguredBeacon::Builder();
    return (long)builder_ptr;
}

/**
 * This method must free the space allocated to ConfiguredBeacon::Builder object.
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_example_ble_1recorder_jni_1models_ConfiguredBeacon_00024Builder_jni_1free(JNIEnv *env,
                                                                                   jclass clazz,
                                                                                   jlong pointer) {
    auto* builder_ptr = (ConfiguredBeacon::Builder*)pointer;
    delete builder_ptr;
}

/**
 * This method must call the create() method of the underlying ConfiguredBeacon::Builder object
 * and return a pointer to it.
 */
extern "C"
JNIEXPORT jlong JNICALL
Java_com_example_ble_1recorder_jni_1models_ConfiguredBeacon_00024Builder_jni_1create(JNIEnv *env,
                                                                                     jobject thiz,
                                                                                     jlong pointer) {
    auto* builder_ptr = (ConfiguredBeacon::Builder*)pointer;
    return (long)(builder_ptr->create());
}

/**
 * This method must call the setId() method of the underlying ConfiguredBeacon::Builder object
 * and return a pointer to it.
 */
extern "C"
JNIEXPORT jlong JNICALL
Java_com_example_ble_1recorder_jni_1models_ConfiguredBeacon_00024Builder_jni_1setId(JNIEnv *env,
                                                                                    jobject thiz,
                                                                                    jlong pointer,
                                                                                    jint id) {
    auto* builder_ptr = (ConfiguredBeacon::Builder*)pointer;
    return (long)(builder_ptr->setId(id));
}

/**
 * This method must call the setPos() method of the underlying ConfiguredBeacon::Builder object
 * and return a pointer to it.
 */
extern "C"
JNIEXPORT jlong JNICALL
Java_com_example_ble_1recorder_jni_1models_ConfiguredBeacon_00024Builder_jni_1setPos(JNIEnv *env,
                                                                                     jobject thiz,
                                                                                     jlong pointer,
                                                                                     jint x, jint y,
                                                                                     jint z) {
    auto* builder_ptr = (ConfiguredBeacon::Builder*)pointer;
    return (long)(builder_ptr->setPos(x,y,z));
}

/**
 * This method must call the setRssiD0() method of the underlying ConfiguredBeacon::Builder object
 * and return a pointer to it.
 */
extern "C"
JNIEXPORT jlong JNICALL
Java_com_example_ble_1recorder_jni_1models_ConfiguredBeacon_00024Builder_jni_1setRssiD0(JNIEnv *env,
                                                                                        jobject thiz,
                                                                                        jlong pointer,
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
Java_com_example_ble_1recorder_jni_1models_ConfiguredBeacon_00024Builder_jni_1setD0(JNIEnv *env,
                                                                                    jobject thiz,
                                                                                    jlong pointer,
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
        JNIEnv *env, jobject thiz, jlong pointer, jfloat coeff) {
    auto* builder_ptr = (ConfiguredBeacon::Builder*)pointer;
    return (long)(builder_ptr->setBeaconCoeff(coeff));
}

/**
 * This method must call the setXSigma() method of the underlying ConfiguredBeacon::Builder object
 * and return a pointer to it.
 */
extern "C"
JNIEXPORT jlong JNICALL
Java_com_example_ble_1recorder_jni_1models_ConfiguredBeacon_00024Builder_jni_1setXSigma(JNIEnv *env,
                                                                                        jobject thiz,
                                                                                        jlong pointer,
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
        JNIEnv *env, jobject thiz, jlong pointer, jlong filter_ptr) {
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
        JNIEnv *env, jobject thiz, jlong pointer, jlong filter_ptr) {
    auto* builder_ptr = (ConfiguredBeacon::Builder*)pointer;
    auto* filter_pointer = (Filter*)filter_ptr;
    return (long)(builder_ptr->registerFilter(filter_pointer));
}

/**
 * This method must call the build() method of the underlying ConfiguredBeacon::Builder object
 * and return a pointer to the ConfiguredBeacon object. This can then be passed to addToConfiguredBeacons(...).
 */
extern "C"
JNIEXPORT jlong JNICALL
Java_com_example_ble_1recorder_jni_1models_ConfiguredBeacon_00024Builder_build(JNIEnv *env,
                                                                               jobject thiz,
                                                                               jlong pointer) {
    auto* builder_ptr = (ConfiguredBeacon::Builder*)pointer;
    return (long)(&builder_ptr->build());
}
extern "C"
JNIEXPORT jint JNICALL
Java_com_example_ble_1recorder_jni_1models_ConfiguredBeacon_00024Builder_newFunction(JNIEnv *env,
                                                                                     jobject thiz,
                                                                                     jlong pointer) {
    // TODO: implement newFunction()
}