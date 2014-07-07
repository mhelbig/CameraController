void initializeSplines(void)
{
  int selectedMotionProfile = motionProfileList[selectedMotionProfileIndex].value;
  
  XmotorSpline.setPoints(frameNumber,XmotorSplinePoints_y,numberOfTransitions + 2);
  YmotorSpline.setPoints(frameNumber,YmotorSplinePoints_y,numberOfTransitions + 2);
  ZmotorSpline.setPoints(frameNumber,ZmotorSplinePoints_y,numberOfTransitions + 2);
  DmotorSpline.setPoints(frameNumber,DmotorSplinePoints_y,numberOfTransitions + 2);

  XmotorSpline.setDegree(selectedMotionProfile);
  YmotorSpline.setDegree(selectedMotionProfile);
  ZmotorSpline.setDegree(selectedMotionProfile);
  DmotorSpline.setDegree(selectedMotionProfile);
 
 // update the first and last index of the spline arrays for the Catmull tangent points 
  XmotorSplinePoints_y[0] = XmotorSplinePoints_y[1];
  YmotorSplinePoints_y[0] = YmotorSplinePoints_y[1];
  ZmotorSplinePoints_y[0] = ZmotorSplinePoints_y[1];
  DmotorSplinePoints_y[0] = DmotorSplinePoints_y[1];

  XmotorSplinePoints_y[numberOfTransitions+1] = XmotorSplinePoints_y[numberOfTransitions];
  YmotorSplinePoints_y[numberOfTransitions+1] = YmotorSplinePoints_y[numberOfTransitions];
  ZmotorSplinePoints_y[numberOfTransitions+1] = ZmotorSplinePoints_y[numberOfTransitions];
  DmotorSplinePoints_y[numberOfTransitions+1] = DmotorSplinePoints_y[numberOfTransitions];

  frameNumber[numberOfTransitions+1]          = frameNumber[numberOfTransitions];
 
//  Serial.println("Spline functions initialized");
}
