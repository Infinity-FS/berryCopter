//
// Created by Felix Sittenauer on 13.10.16.
//

#ifndef __KALMANGYROANGLEFILTER_H_INCLUDED__
#define __KALMANGYROANGLEFILTER_H_INCLUDED__


#include <stdio.h>


class KalmanGyroAngleFilter {
public:
    KalmanGyroAngleFilter(double t_startAngle, double t_Q_angle, double t_Q_bias, double t_R_noise);

    void applyFilter(double measuredRate, double dt);

    double getAngle();
private:
    // State matrix X
    double angle, bias;
    // angle
    // bias

    // Noise covariance m. Q
    double Q_angle, Q_bias;
    // Q_angle  0
    // 0        Q_bias

    // Error cov. m. P
    double P[2][2];
    // 0    0
    // 0    0

    // Dynamic m. F
    double F[2][2];
    // 1    -dt
    // 0    1

    // control input value u
    double u; // deg/s

    // Measure noise m. R
    double R_noise;
    // R_g
};

#endif //__KALMANGYROANGLEFILTER_H_INCLUDED__
