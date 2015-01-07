/**
@file StereoCamera.h
*/

#ifndef STEREOCAMERA_H
#define STEREOCAMERA_H

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

class StereoCamera
{

private:

	float mConvergence;
	float mEyeSeparation;
	float mAspectRatio;
	float mFOV;
	float mNearClippingDistance;
	float mFarClippingDistance;

public:

	  StereoCamera(  
	     float Convergence,
	     float EyeSeparation,
	     float AspectRatio,
	     float FOV,
	     float NearClippingDistance,
	     float FarClippingDistance
	     )


	   {
       mConvergence            = Convergence;
       mEyeSeparation          = EyeSeparation;
	   mAspectRatio            = AspectRatio;
	   mFOV                    = FOV * 3.14 / 180.0f;
       mNearClippingDistance   = NearClippingDistance;
	   mFarClippingDistance    = FarClippingDistance;
	   }
	 
	   void ApplyLeftFrustum()
	   {
			float top, bottom, left, right;
	 
			top     = mNearClippingDistance * tan(mFOV/2);
			bottom  = -top;
	 
			float a = mAspectRatio * tan(mFOV/2) * mConvergence;
	 
			float b = a - mEyeSeparation/2;
			float c = a + mEyeSeparation/2;
	 
			left    = -b * mNearClippingDistance/mConvergence;
			right   =  c * mNearClippingDistance/mConvergence;
	 
			// Set the Projection Matrix
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();  
			glFrustum(left, right, bottom, top,
						mNearClippingDistance, mFarClippingDistance);
	 
			// Displace the world to right
			glMatrixMode(GL_MODELVIEW);                    
			glLoadIdentity();  
			glTranslatef(mEyeSeparation/2, 0.0f, 0.0f);
	   }
	 
	   void ApplyRightFrustum()
	   {
	        float top, bottom, left, right;
	 
	        top     = mNearClippingDistance * tan(mFOV/2);
	        bottom  = -top;
	 
	        float a = mAspectRatio * tan(mFOV/2) * mConvergence;
	 
	        float b = a - mEyeSeparation/2;
	        float c = a + mEyeSeparation/2;
	 
	        left    =  -c * mNearClippingDistance/mConvergence;
	        right   =   b * mNearClippingDistance/mConvergence;
	 
	        // Set the Projection Matrix
	        glMatrixMode(GL_PROJECTION);                       
	        glLoadIdentity();  
	        glFrustum(left, right, bottom, top,
	                  mNearClippingDistance, mFarClippingDistance);
	 
	        // Displace the world to left
	        glMatrixMode(GL_MODELVIEW);                    
	        glLoadIdentity();  
	        glTranslatef(-mEyeSeparation/2, 0.0f, 0.0f);
	   } 
};

#endif