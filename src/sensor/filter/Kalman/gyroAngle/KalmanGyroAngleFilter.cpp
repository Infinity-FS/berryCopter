//
// Created by Felix Sittenauer on 13.10.16.
//

#include "KalmanGyroAngleFilter.h"

KalmanGyroAngleFilter::KalmanGyroAngleFilter(double t_startAngle, double t_Q_angle, double t_Q_bias, double t_R_noise):
    bias(0),
    u(0),
    angle(t_startAngle),
    Q_angle(t_Q_angle),
    Q_bias(t_Q_bias),
    R_noise(t_R_noise)
{
    this->P[0][0] = 0;
    this->P[0][1] = 0;
    this->P[1][0] = 0;
    this->P[1][1] = 0;

    this->F[0][0] = 0;
    this->F[0][1] = 0;
    this->F[1][0] = 0;
    this->F[1][1] = 0;
}

void KalmanGyroAngleFilter::applyFilter(double measuredRate, double dt){
    //  2D kalman filter

    // PREDICTION
    // (1) State Projection --> X(i+1) = F * X(i) + Bu
    this->angle += dt * (this->u - this->bias);

    // (2) Project err. cov. m. P --> P(i+1) = F * P(i) * F^T + Q
    this->P[0][0] += dt * (dt * this->P[1][1] - this->P[1][0] - this->P[0][1] + this->Q_angle);
    this->P[0][1] += -dt * this->P[1][1];
    this->P[1][0] += -dt * this->P[1][1];
    this->P[1][1] = this->P[1][1] + this->Q_bias;

    // i = i+1;

    // CORRECTION
    // (3) KALMAN GAIN K --> P(i) * H^T * (H * P(i) H^T + R)^-1
    double K[2] = {  this->P[0][0]/ (this->P[0][0]+ R_noise),
                    this->P[1][0]/ (this->P[0][0]+ R_noise)};

    // (4) update X with measurement --> X(i) = X(i) + K * (z - H * X(i))
    double innovation = measuredRate * dt;
    std::cout << measuredRate << "\n";
    this->angle += K[0] * innovation;
    this->bias += K[1] * innovation;

    // (5) update P --> P(i) = (I - K * H) * P(i)
    float P00_tmp = P[0][0];
    float P01_tmp = P[0][1];

    this->P[0][0] -= K[0] * P00_tmp;
    this->P[0][1] -= K[0] * P01_tmp;
    this->P[1][0] -= K[1] * P00_tmp;
    this->P[1][1] -= K[1] * P01_tmp;
}


double KalmanGyroAngleFilter::getAngle() {
    return this->angle;
}