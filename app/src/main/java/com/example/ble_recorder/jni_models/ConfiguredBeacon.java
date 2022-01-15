package com.example.ble_recorder.jni_models;

public class ConfiguredBeacon {

    private long cnfg_beacon_ptr;

    public static class Builder{

        private long builder_ptr;

        private static native long jni_allocate();
        private static native void jni_free(long pointer);

        /**
         * Get the pointer to underlying Builder object.
         * @return
         */
        private native long jni_create(long pointer);

        private native long jni_setId(long pointer, int id);
        private native long jni_setPos(long pointer, int x, int y, int z);
        private native long jni_setRssiD0(long pointer, int rssi);
        private native long jni_setD0(long pointer, int d0);
        private native long jni_setBeaconCoeff(long pointer, float coeff);
        private native long jni_setXSigma(long pointer, float x_sig);
        private native long jni_registerFilter(long pointer, long filter_ptr);
        private native long jni_removeFilter(long pointer, long filter_ptr);
        private native int newFunction(long pointer);

        private native long build(long pointer);

        private Builder(){
            this.builder_ptr = jni_allocate();
        }

        public static Builder allocate(){
            return new Builder();
        }

        public static void free(Builder builder){
            jni_free(builder.builder_ptr);
        }

        public Builder setId(int id){}

        public Builder setPos(int x, int y, int z){
            //C++ function called
        }

        public Builder setRssiD0(int rssi){}

        public Builder setD0(int d0){}

        public Builder setBeaconCoeff(float coeff){}

        public Builder setXSigma(float X_sig){}

        public Builder registerFilter(long filter_ptr){}

        public Builder removeFilter(long filter_ptr){}


    }
}
