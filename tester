void adjuster(void)
{
int curt = micros();//start to track time in order to make one adjust every 1000us
readSensor();
setLeftPwm((2900- LFSensor));//set left motor speed
setRightPwm((2500 – RFSensor));//set right motor speed
TIM2->CNT=25000;//keep resetting encoder counts prevent overflow
TIM3->CNT=25000;
elapseMicros(1000, curt);//elapse 1000 micro seconds
}
