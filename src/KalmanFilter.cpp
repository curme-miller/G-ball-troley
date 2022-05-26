#include <KalmanFilter.h>

void KalmanFilter::init(float errorEst, float currentResult, float errorMeasure)
{
    this->setErrorEst(errorEst);
    this->setErrorMeasure(errorMeasure);
    this->setCurrentResult(currentResult);
}

void KalmanFilter::setErrorEst(float errorEst)
{
    this->error_est = errorEst;
}

void KalmanFilter::setErrorMeasure(float errorMeasure)
{
    this->error_measure = errorMeasure;
}

void KalmanFilter::setCurrentResult(float currentMeasure)
{
    this->current_measure = currentMeasure;
}

void KalmanFilter::updateKalmanFilter()
{
    this->kalman_gain = this->error_est / (this->error_est + this->error_measure);
    this->error_est = (1 - this->kalman_gain) * this->error_est;
    this->current_result = this->current_result + this->kalman_gain * (this->current_measure - this->current_result);
}
void KalmanFilter::setCurrentMeasure(float currentMeasure)
{
    this->current_measure = currentMeasure;
}
float KalmanFilter::getCurrentResult()
{
    return this->current_result;
}