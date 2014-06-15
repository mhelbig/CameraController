void initializeSplines(void)
{
  XmotorSpline.setPoints(frameNumber,XmotorSplinePoints_y,numberOfTransitions + 2);
  XmotorSpline.setDegree(selectedMotionProfile);
 
  YmotorSpline.setPoints(frameNumber,YmotorSplinePoints_y,numberOfTransitions + 2);
  YmotorSpline.setDegree(selectedMotionProfile);
  
  Serial.println("Spline functions initialized");
}
