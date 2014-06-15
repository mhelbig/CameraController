void initializeSplines(void)
{
  XmotorSpline.setPoints(frameNumber,XmotorSplinePoints_y,MAX_NUMBER_OF_TRANSITIONS + 2);
  XmotorSpline.setDegree(selectedMotionProfile);
 
  YmotorSpline.setPoints(frameNumber,YmotorSplinePoints_y,MAX_NUMBER_OF_TRANSITIONS + 2);
  YmotorSpline.setDegree(selectedMotionProfile);
  
  Serial.println("Spline functions initialized");
}
