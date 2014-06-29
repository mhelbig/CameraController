void initializeSplines(void)
{
  int selectedMotionProfile = motionProfileList[selectedMotionProfileIndex].value;
  
  XmotorSpline.setPoints(frameNumber,XmotorSplinePoints_y,numberOfTransitions + 2);
  YmotorSpline.setPoints(frameNumber,YmotorSplinePoints_y,numberOfTransitions + 2);

  XmotorSpline.setDegree(selectedMotionProfile);
  YmotorSpline.setDegree(selectedMotionProfile);
 
 // update the first and last index of the spline arrays for the Catmull tangent points 
  XmotorSplinePoints_y[0] = XmotorSplinePoints_y[1];
  YmotorSplinePoints_y[0] = YmotorSplinePoints_y[1];

  XmotorSplinePoints_y[numberOfTransitions+1] = XmotorSplinePoints_y[numberOfTransitions];
  YmotorSplinePoints_y[numberOfTransitions+1] = YmotorSplinePoints_y[numberOfTransitions];
  frameNumber[numberOfTransitions+1]          = frameNumber[numberOfTransitions];
 
//  Serial.println("Spline functions initialized");
}
