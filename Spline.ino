void initializeSplines(void)
{
  int selectedMotionProfile = motionProfileList[selectedMotionProfileIndex].value;
  
  XmotorSpline.setPoints(frameNumber,XmotorSplinePoints_y,numberOfTransitions + 2);
  YmotorSpline.setPoints(frameNumber,YmotorSplinePoints_y,numberOfTransitions + 2);

  XmotorSpline.setDegree(selectedMotionProfile);
  YmotorSpline.setDegree(selectedMotionProfile);
 
 // update the last index of the spline arrays for the Catmull tangent points 
  XmotorSplinePoints_y[numberOfTransitions+1] = XmotorSplinePoints_y[numberOfTransitions];
  YmotorSplinePoints_y[numberOfTransitions+1] = YmotorSplinePoints_y[numberOfTransitions];
  frameNumber[numberOfTransitions+1]          = frameNumber[numberOfTransitions];
 
//  Serial.println("Spline functions initialized");
}
