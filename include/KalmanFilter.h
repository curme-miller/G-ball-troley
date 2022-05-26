#ifndef KALMAN_FILTER_H
#define KALMAN_FILTER_H

class KalmanFilter
{

public:
    void init(float errorEst,float currentResult,float errorMeasure);
    void setErrorMeasure(float currentMeasure);
    void setErrorEst(float errorEst);
    void setCurrentResult(float currentResult);

    void setCurrentMeasure(float currentMeasure);
    void updateKalmanFilter();
    float getCurrentResult();

private:
    float error_est;
    float error_measure;
    float current_measure;
    float kalman_gain;
    float current_result;
};


#endif