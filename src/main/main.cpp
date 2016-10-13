#include <iostream>
#include <stdio.h>
#include <string>
#include "../GPIO/IGpio/IGpio.h"
#include "../FlightController/FlightController.h"
#include "../sensor/MPU6050/MPU6050.h"
#include "../sensor/filter/Kalman/gyroAngle/KalmanGyroAngleFilter.h"


int main() {
    IGpio IGpioInstance;

    FlightController flightCtrl(IGpioInstance);
    //flightCtrl.programMotors();
    MPU6050 mpu6050(2, 250, IGpioInstance);
    mpu6050.wakeUp();

    mpu6050.calibrateAccelerometer();
    mpu6050.calibrateGyrometer();



    // filter
    KalmanGyroAngleFilter angleFilter_X = KalmanGyroAngleFilter(0, 0.001, 0.003, 0.03);
    KalmanGyroAngleFilter angleFilter_Y = KalmanGyroAngleFilter(0, 0.001, 0.003, 0.03);
    KalmanGyroAngleFilter angleFilter_Z = KalmanGyroAngleFilter(0, 0.001, 0.003, 0.03);

    struct timespec spec;
    clock_gettime(CLOCK_REALTIME, &spec);
    long start_ns = (long) (spec.tv_nsec);
    long end_ns = 0;
    long dt_ns = 0;

    int i = 0;
    for (;;) {
        // < LOOP

        mpu6050.readAccelerometer();
        mpu6050.readGyrometer();

        Vector3<double> curDegSec = mpu6050.getGyrometerVector3_deg_s();

        clock_gettime(CLOCK_REALTIME, &spec);
        end_ns = (long) (spec.tv_nsec);
        dt_ns = end_ns - start_ns;

        angleFilter_X.applyFilter(curDegSec.X, (double) dt_ns / (double) 1e9);

        i++;

        // > LOOP
        if (i % 1000 == 0) {
            std::cout << "Accel: ";
            std::cout << "X " << (mpu6050.getAccelerometerVector3()).X << ", ";
            std::cout << "Y " << (mpu6050.getAccelerometerVector3()).Y << ", ";
            std::cout << "Z " << (mpu6050.getAccelerometerVector3()).Z << " >";

            std::cout << "< Gyro: ";
            std::cout << "X " << (mpu6050.getGyrometerVector3()).X << " " << curDegSec.X << " @ "
                      << angleFilter_X.getAngle() << ", ";
            std::cout << "Y " << curDegSec.Y << ", ";
            std::cout << "Z " << curDegSec.Z << " >";

            std::cout << "loop Hz: " << ((1e9) / (dt_ns)) << "Hz \n";
        }
        clock_gettime(CLOCK_REALTIME, &spec);
        start_ns = (long) (spec.tv_nsec);
    }

    return 0;
}