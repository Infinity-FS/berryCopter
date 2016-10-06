#ifndef __ACCELERATOR_H_INCLUDED__
#define __ACCELERATOR_H_INCLUDED__

#define ACCELERATOR_CALIBRATION_MEAN_ITERATIONS 1000
#define ACCELERATOR_CALIBRATION_MEAN_DELAY_MCS 2000 // mcs

#include "../AxisData/AxisData.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

class Accelerometer {
    public:
        Accelerometer(short t_AccelerometerRange_G, short t_offsetRange_G, int t_calibrationMeanIterations, int t_calibrationMeanDelay, int t_calibrationMaxError);
        virtual ~Accelerometer() {}

        void calibrateAccelerometer();
        void updateAccelerometerMean();


        axisData<short> getAccelerometerAxisData();
        short getAccelerometerRange_G();

        virtual void readAccelerometer() = 0;
        virtual void readAccelerometerOffset(axisData<short> &t_offset) = 0;
        virtual void writeAccelerometerOffset (axisData<short> &t_offset) = 0;

    protected:
        axisData<short> accelerometerAxisData;
        axisData<double> meanAccelerometerAxisData;

        short AccelerometerRange_G, AccelerometerOffsetRange_G; // in G

    private:
        int calibrationMeanIterations, calibrationMeanDelay, calibrationMaxError;

        bool adjustAccelerometerOffset(axisData<short> &r_offset) {
};

#endif // __ACCELERATOR_H_INCLUDED__
