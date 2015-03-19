/*
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/03
*/
#ifndef __BoundingBoxClass_H_
#define __BoundingBoxClass_H_

#include "MyEngine.h"

//System Class
class BoundingBoxClass
{
	bool m_bInitialized; //Has the elements of this object been initialized before?
	float m_fRadius;//Radius of the collision Box
	vector3 m_v3Centroid;//Center point of the model, the origin in GSpace in which the Box is going to be located
	String m_sName;//Name of the BoundingBox (to relate to the instance)
	//float minX, maxX, minY, maxY, minZ, maxZ; // Min and Max points on the object, used for collisions

public:
	float minX, maxX, minY, maxY, minZ, maxZ; // Min and Max points on the object, used for collisions

	/* Constructor */
	BoundingBoxClass(void);
	/* Copy Constructor */
	BoundingBoxClass(BoundingBoxClass const& other);
	/* Copy Assignment Operator*/
	BoundingBoxClass& operator=(BoundingBoxClass const& other);
	/* Destructor */
	~BoundingBoxClass(void);

	/* Swaps the contents of the object with another object's content */
	void Swap(BoundingBoxClass& other);

	/*
	IsInitialized
		Returns information about whether or not the object has been initialized
	*/
	bool IsInitialized(void);

	/*
	GetRadius
		Returns the radius of the Box
	*/
	float GetRadius(void);

	/*
	GetCentroid
		Returns the origin of the Cartesian Coordinate System in which the Box is drawn in GSpace
	*/
	vector3 GetCentroid(void);

	/*
	GetName
		Returns the name of the Box to associate it with an instance
	*/
	String GetName(void);

	/*
	ConstructBox
		Creates the Box in local space of the model specified in the instance name
	*/
	void GenerateBoundingBox(String a_sInstanceName);

	/*
	AddBoxToRenderList
		Adds the Box to the render list specifying also if rendering the centroid is necessary
	*/
	void AddBoxToRenderList(matrix4 a_mModelToWorld, vector3 a_vColor, bool a_bRenderCentroid = false);

	
private:
	/* Releases the object from memory */
	void Release(void);

	/* Initialize the object's fields */
	void Init(void);
};


#endif //__BoundingBoxClass_H__