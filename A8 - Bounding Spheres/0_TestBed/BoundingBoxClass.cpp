#include "BoundingBoxClass.h"
//  BoundingBoxClass
void BoundingBoxClass::Init(void)
{
	m_bInitialized = false;
	m_fRadius = 0.0f;
	m_v3Centroid = vector3(0.0f);
	m_sName = "NULL";
	minX = minY = minZ = maxX = maxY = maxZ = 0;
}
void BoundingBoxClass::Swap(BoundingBoxClass& other)
{
	std::swap(m_bInitialized, other.m_bInitialized);
	std::swap(m_v3Centroid, other.m_v3Centroid);
	std::swap(m_sName, other.m_sName);
}
void BoundingBoxClass::Release(void)
{
	//No pointers to release
}
//The big 3
BoundingBoxClass::BoundingBoxClass(){Init();}
BoundingBoxClass::BoundingBoxClass(BoundingBoxClass const& other)
{
	m_bInitialized = other.m_bInitialized;
	m_v3Centroid = other.m_v3Centroid;
	m_sName = other.m_sName;
}
BoundingBoxClass& BoundingBoxClass::operator=(BoundingBoxClass const& other)
{
	if(this != &other)
	{
		Release();
		Init();
		BoundingBoxClass temp(other);
		Swap(temp);
	}
	return *this;
}
BoundingBoxClass::~BoundingBoxClass(){Release();};
//Accessors
bool BoundingBoxClass::IsInitialized(void){ return m_bInitialized; }
vector3 BoundingBoxClass::GetCentroid(void){ return m_v3Centroid; }
String BoundingBoxClass::GetName(void){return m_sName;}
//Methods
void BoundingBoxClass::GenerateBoundingBox(String a_sInstanceName)
{
	//If this has already been initialized there is nothing to do here
	if(m_bInitialized)
		return;
	MeshManagerSingleton* pMeshMngr = MeshManagerSingleton::GetInstance();
	if(pMeshMngr->IsInstanceCreated(a_sInstanceName))
	{
		m_sName = a_sInstanceName;
		
		std::vector<vector3> lVertices = pMeshMngr->GetVertices(m_sName);
		unsigned int nVertices = lVertices.size();
		m_v3Centroid = lVertices[0];
		minX = (lVertices[0].x);
		minY = (lVertices[0].y);
		minZ = (lVertices[0].z);
		maxX = (lVertices[0].x);
		maxY = (lVertices[0].y);
		maxZ = (lVertices[0].z);
		for(unsigned int nVertex = 1; nVertex < nVertices; nVertex++)
		{
			//m_v3Centroid += lVertices[nVertex];
			if(minX > lVertices[nVertex].x)
				minX = lVertices[nVertex].x;
			else if(maxX < lVertices[nVertex].x)
				maxX = lVertices[nVertex].x;
			
			if(minY > lVertices[nVertex].y)
				minY = lVertices[nVertex].y;
			else if(maxY < lVertices[nVertex].y)
				maxY = lVertices[nVertex].y;

			if(minZ > lVertices[nVertex].z)
				minZ = lVertices[nVertex].z;
			else if(maxZ < lVertices[nVertex].z)
				maxZ = lVertices[nVertex].z;
		}
		vector3 v3Min = vector3(minX, minY, minZ);
		vector3 v3Max = vector3(maxX, maxY, maxZ);
		m_v3Centroid = (v3Min + v3Max) / 2.0f;

		m_bInitialized = true;
	}
}
void BoundingBoxClass::AddBoxToRenderList(matrix4 a_mModelToWorld, vector3 a_vColor, bool a_bRenderCentroid)
{
	if(!m_bInitialized)
		return;
	MeshManagerSingleton* pMeshMngr = MeshManagerSingleton::GetInstance();
	if(a_bRenderCentroid)
		pMeshMngr->AddAxisToQueue(a_mModelToWorld * glm::translate(m_v3Centroid));
	pMeshMngr->AddSphereToQueue(a_mModelToWorld * glm::translate(m_v3Centroid) * glm::scale(vector3(m_fRadius * 2.0f)), a_vColor, MERENDER::WIRE);
}