#ifndef __ACCELERATOR_H_INCLUDED__
#define __ACCELERATOR_H_INCLUDED__

#include "../Vector3/Vector3.h"
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


        Vector3<short> getAccelerometerVector3();
        short getAccelerometerRange_G();

        virtual void readAccelerometer() = 0;
        virtual void readAccelerometerOffset(Vector3<short> &t_offset) = 0;
        virtual void writeAccelerometerOffset (Vector3<short> &t_offset) = 0;

    protected:
        Vector3<short> accelerometerVector3;
        Vector3<double> meanAccelerometerVector3;

        short AccelerometerRange_G, AccelerometerOffsetRange_G; // in G

    private:
        int calibrationMeanIterations, calibrationMeanDelay, calibrationMaxError;

        bool adjustAccelerometerOffset(Vector3<short> &r_offset);
};

#endif // __ACCELERATOR_H_INCLUDED__
