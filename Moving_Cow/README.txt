--- ../SimpleSceneOriginal.cpp	2017-05-26 19:04:20.000000000 +0900
+++ SimpleScene.cpp	2017-06-20 22:01:55.000000000 +0900
@@ -69,6 +69,14 @@
 
 enum { H_DRAG=1, V_DRAG=2};
 static int isDrag=0;
+
+int cowCount = 0;
+int xPositionInWindow;
+Plane tmpPlane;
+matrix4 cowMatrix[6];
+vector3 cowVector[6];
+bool rotate = false;
+vector3 tmpPos = vector3(0, 0, 0);
 //------------------------------------------------------------------------------
 
 Plane makePlane(vector3 const& a, vector3 const& b, vector3 const& n)
@@ -270,6 +278,68 @@
 }
 
 
+vector3 catmullRom(vector3 p[4], double t)
+{
+  double t2 = t * t;
+  double t3 = t2 * t;
+
+  vector3 ret = 0.5f * ((2.0f * p[1]) + (p[2] - p[0]) * t 
+      + (2.0f * p[0] - 5.0f * p[1] + 4.0f * p[2] - p[3]) * t2 
+      + (3.0f * p[1] - 3.0f * p[2] + p[3] - p[0]) * t3);
+  
+  return ret;
+}
+
+void getCowState(double time)
+{
+  int position = (int)time % 6;
+  vector3 p[4];
+  
+  for (int i = 0 ; i < 4 ; i ++){
+    int pos = position - 1 + i;
+    pos < 0 ? pos = 5 : pos > 6 ? pos = 1 : pos > 5 ? pos = 0 : pos; 
+
+    p[i] = cowVector[pos];
+  }
+
+  double t = time - (int)time;
+
+  vector3 catmullRomPos = catmullRom(p, t);
+
+  matrix4 cow;
+  cow.setTranslation(catmullRomPos, false);
+  
+  double dx =   catmullRomPos.x - tmpPos.x;
+  double dy =   catmullRomPos.y - tmpPos.y;
+  double dz = -(catmullRomPos.z - tmpPos.z);
+  double angle;
+
+  angle = atan(dz/dx);
+  if (dx < 0){
+    dz > 0 ? angle += M_PI : angle -= M_PI;
+  }
+  
+  tmpPos = catmullRomPos;
+
+  matrix4 rotateY;
+  rotateY.setRotation(vector3(0, 1, 0), angle, false);
+  cow.mult(cow, rotateY);
+  
+  double ds = sqrt(dx * dx + dz * dz);
+  double angleY = atan(dy / ds);
+  if (ds < 0){
+    dy > 0 ? angle += M_PI : angle -= M_PI;
+  }
+  
+  matrix4 rotateZ;
+  rotateZ.setRotation(vector3(0, 0, 1), angleY, false);
+  cow.mult(cow, rotateZ);
+  
+  drawCow(cow, false);
+  
+}
+
+
 /*********************************************************************************
 * Call this part whenever display events are needed. 
 * Display events are called in case of re-rendering by OS. ex) screen movement, screen maximization, etc.
@@ -288,9 +358,31 @@
 	// update cow2wld here to animate the cow.
 	//double animTime=glfwGetTime()-animStartTime;
 	//you need to modify both the translation and rotation parts of the cow2wld matrix.
-
-	drawCow(cow2wld, cursorOnCowBoundingBox);														// Draw cow.
-	//drawBet();
+  if (cowCount < 6){
+    for (int i = 0 ; i < cowCount ; i ++){
+      drawCow(cowMatrix[i], false);
+    }
+    drawCow(cow2wld, cursorOnCowBoundingBox);
+  }
+
+  if (cowCount == 6) {
+    cursorOnCowBoundingBox = false;
+    double currentTime;
+    if (rotate == false) {
+      animStartTime = glfwGetTime();
+      currentTime = glfwGetTime() - animStartTime;
+      rotate = true;
+      getCowState(currentTime);
+    }
+    else if (rotate == true && currentTime < 18) {
+      currentTime = glfwGetTime() - animStartTime;
+      getCowState(currentTime);
+    }
+    else {
+      cowCount = 0;
+      rotate = false;
+    }
+  }
 
 	glFlush();
 
@@ -444,7 +536,7 @@
 {
 	const int GLFW_DOWN=1;
 	const int GLFW_UP=0;
-   	int x, y;
+   	int x, y, z;
 
 #if GLFW_VERSION_MAJOR==3
 	double xpos, ypos;
@@ -462,6 +554,22 @@
 			printf( "Left mouse down-click at (%d, %d)\n", x, y );
 			// start vertical dragging
 			// TODO: you probably need a state variable.
+      if (cowCount < 6){
+
+			  if (!cursorOnCowBoundingBox){
+          cursorOnCowBoundingBox = true;
+        }
+        //Rotating
+        Ray ray;
+        screenCoordToRay(x, y, ray);
+        xPositionInWindow = x;
+        PickInfo &pp=pickInfo;
+				Plane p(vector3(0,1,0), pp.cowPickPosition);
+				std::pair<bool, double> c=ray.intersects(p);
+        vector3 currentPos = ray.getPoint(c.second);
+        tmpPlane = Plane(vector3(0,0,1), currentPos);
+      }
+      
 
 		}
 		else if(state == GLFW_UP)
@@ -469,6 +577,14 @@
 			isDrag=H_DRAG;
 			printf( "Left mouse up\n");
 			// start horizontal dragging using mouse-move events.
+		
+      if (cowCount < 6){
+        cowMatrix[cowCount] = cow2wld;
+        cowVector[cowCount] = vector3(cow2wld._14, cow2wld._24, cow2wld._34);
+        cowCount ++;
+      }else {
+        cursorOnCowBoundingBox = false;
+      }
 		}
 	}
 	else if (button == GLFW_MOUSE_BUTTON_RIGHT)
@@ -498,6 +614,20 @@
 		printf( "in drag mode %d\n", isDrag);
 		if (isDrag==V_DRAG)
 		{
+			if(cursorOnCowBoundingBox)
+			{
+				Ray ray;
+				screenCoordToRay(xPositionInWindow, y, ray);
+				PickInfo &pp=pickInfo;
+				std::pair<bool, double> c=ray.intersects(tmpPlane);
+
+
+				vector3 currentPos=ray.getPoint(c.second);	
+
+				matrix4 T;
+				T.setTranslation(currentPos-pp.cowPickPosition, false);
+				cow2wld.mult(T, pp.cowPickConfiguration);
+			}
 			// vertical dragging
 			// TODO:
 			// create a dragging plane perpendicular to the ray direction, 
