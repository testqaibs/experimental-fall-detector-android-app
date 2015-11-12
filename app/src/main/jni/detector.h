/*
This code is free  software: you can redistribute it and/or  modify it under the
terms of the GNU Lesser General Public License as published by the Free Software
Foundation,  either version  3 of  the License,  or (at  your option)  any later
version.

This code  is distributed in the  hope that it  will be useful, but  WITHOUT ANY
WARRANTY; without even the implied warranty  of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU Lesser  General Public License for more details.

You should have  received a copy of the GNU  Lesser General Public License along
with code. If not, see http://www.gnu.org/licenses/.
*/

#ifndef GUARDIAN_DETECTOR_H
#define GUARDIAN_DETECTOR_H

#include <android/log.h>
#include <android/sensor.h>
#include <pthread.h>

#define LOG(level, ...) __android_log_print(level, "DETECTOR", __VA_ARGS__)

#define INTERVAL_MS guardian_Detector_INTERVAL_MS
#define N guardian_Detector_N
#define SIZE_BUFFER guardian_Detector_SIZE
#define SPAN_MAXMIN (100 / INTERVAL_MS)
#define SPAN_FALLING (1000 / INTERVAL_MS)
#define SPAN_IMPACT (2000 / INTERVAL_MS)
#define SPAN_AVERAGING (400 / INTERVAL_MS)

#define FILTER_NZEROS 2
#define FILTER_NPOLES 2
#define FILTER_LPF_GAIN 4.143204922e+03
#define FILTER_HPF_GAIN 1.022463023e+00
#define FILTER_FACTOR_0 -0.9565436765
#define FILTER_FACTOR_1 +1.9555782403

#define G 1.0

#define FALLING_WAIST_SV_TOT guardian_Detector_FALLING_WAIST_SV_TOT
#define IMPACT_WAIST_SV_TOT guardian_Detector_IMPACT_WAIST_SV_TOT
#define IMPACT_WAIST_SV_D guardian_Detector_IMPACT_WAIST_SV_D
#define IMPACT_WAIST_SV_MAXMIN guardian_Detector_IMPACT_WAIST_SV_MAXMIN
#define IMPACT_WAIST_Z_2 guardian_Detector_IMPACT_WAIST_Z_2
#define LYING_AVERAGE_Z_LPF 0.5

typedef struct {
    JNIEnv *JNI;
    jobject Context;
    jclass AlarmClass;
    jmethodID AlarmCall;
    jdoubleArray BufferArray;
    jdouble *Buffer;
    jint TimeoutFalling;
    jint TimeoutImpact;
    jint Position;
    jdouble *X;
    jdouble *Y;
    jdouble *Z;
    jdouble *X_LPF;
    jdouble *Y_LPF;
    jdouble *Z_LPF;
    jdouble *X_HPF;
    jdouble *Y_HPF;
    jdouble *Z_HPF;
    jdouble *X_MAXMIN;
    jdouble *Y_MAXMIN;
    jdouble *Z_MAXMIN;
    jdouble *SV_TOT;
    jdouble *SV_D;
    jdouble *SV_MAXMIN;
    jdouble *Z_2;
    jdouble *Falling;
    jdouble *Impact;
    jdouble *Lying;
    jdouble XLPFXV[FILTER_NZEROS + 1];
    jdouble XLPFYV[FILTER_NPOLES + 1];
    jdouble YLPFXV[FILTER_NZEROS + 1];
    jdouble YLPFYV[FILTER_NPOLES + 1];
    jdouble ZLPFXV[FILTER_NZEROS + 1];
    jdouble ZLPFYV[FILTER_NPOLES + 1];
    jdouble XHPFXV[FILTER_NZEROS + 1];
    jdouble XHPFYV[FILTER_NPOLES + 1];
    jdouble YHPFXV[FILTER_NZEROS + 1];
    jdouble YHPFYV[FILTER_NPOLES + 1];
    jdouble ZHPFXV[FILTER_NZEROS + 1];
    jdouble ZHPFYV[FILTER_NPOLES + 1];
    jdouble AnteX;
    jdouble AnteY;
    jdouble AnteZ;
    jlong AnteTime;
    jlong Regular;
    pthread_mutex_t Lock;
    ASensorEventQueue *Queue;
} StateStructure;

#endif //GUARDIAN_DETECTOR_H