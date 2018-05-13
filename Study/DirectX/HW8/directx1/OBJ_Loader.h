#pragma once
#ifndef OBJLOADER_H
#define OBJLOADER_H
// OBJ_Loader.h - A Single Header OBJ Model Loader
#include <d3d11.h>
#include <D3DX11tex.h>
#include<D3DX10math.h>
// Iostream - STD I/O Library
//#include <iostream>

// Vector - STD Vector/Array Library
#include <vector>

// String - STD String Library
#include <string>

// fStream - STD File I/O Library
#include <fstream>

// Math.h - STD math Library
//#include <math.h>

// Print progress to console while loading (large models)
//#define OBJL_CONSOLE_OUTPUT

// Namespace: OBJL
//
// Description: The namespace that holds eveyrthing that
//	is needed and used for the OBJ Model Loader
namespace objl
{
	// Structure: Vector2
	//
	// Description: A 2D Vector that Holds Positional Data
	class Vector2
	{
	public:
		// Default Constructor
		Vector2();

		// Variable Set Constructor
		Vector2(float X_, float Y_);
		// Bool Equals Operator Overload
		bool operator==(const Vector2& other) const;
		// Bool Not Equals Operator Overload
		bool operator!=(const Vector2& other) const;
		// Addition Operator Overload
		Vector2 operator+(const Vector2& right) const;
		// Subtraction Operator Overload
		Vector2 operator-(const Vector2& right) const;
		// Float Multiplication Operator Overload
		Vector2 operator*(const float& other) const;

		// Positional Variables
		float X;
		float Y;
	};

	// Structure: ObjVector3
	//
	// Description: A 3D Vector that Holds Positional Data
	class ObjVector3
	{
	public:
		// Default Constructor
		ObjVector3();
		// Variable Set Constructor
		ObjVector3(float X_, float Y_, float Z_);
		// Bool Equals Operator Overload
		bool operator==(const ObjVector3& other) const;
		// Bool Not Equals Operator Overload
		bool operator!=(const ObjVector3& other) const;
		// Addition Operator Overload
		ObjVector3 operator+(const ObjVector3& right) const;
		// Subtraction Operator Overload
		ObjVector3 operator-(const ObjVector3& right) const;
		// Float Multiplication Operator Overload
		ObjVector3 operator*(const float& other) const;

		// Positional Variables
		float X;
		float Y;
		float Z;
	};

	// Structure: Vertex
	//
	// Description: Model Vertex object that holds
	//	a Position, Normal, and Texture Coordinate
	struct Vertex
	{
	/*	D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
		D3DXVECTOR3 normal;*/
		// Position Vector
		ObjVector3 Position;

		// Normal Vector
		ObjVector3 Normal;

		// Texture Coordinate Vector
		Vector2 TextureCoordinate;
	};
	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
		D3DXVECTOR3 normal;
	};
	struct Material
	{
		Material()
		{
			name;
			Ns = 0.0f;
			Ni = 0.0f;
			d = 0.0f;
			illum = 0;
		}

		// Material Name
		std::string name;
		// Ambient Color
		ObjVector3 Ka;
		// Diffuse Color
		ObjVector3 Kd;
		// Specular Color
		ObjVector3 Ks;
		// Specular Exponent
		float Ns;
		// Optical Density
		float Ni;
		// Dissolve
		float d;
		// Illumination
		int illum;
		// Ambient Texture Map
		std::string map_Ka;
		// Diffuse Texture Map
		std::string map_Kd;
		// Specular Texture Map
		std::string map_Ks;
		// Specular Hightlight Map
		std::string map_Ns;
		// Alpha Texture Map
		std::string map_d;
		// Bump Map
		std::string map_bump;
	};

	// Structure: Mesh
	//
	// Description: A Simple Mesh Object that holds
	//	a name, a vertex list, and an index list
	class Mesh
	{
	public:
		// Default Constructor
		Mesh();
		// Variable Set Constructor
		Mesh(std::vector<Vertex>& _Vertices, std::vector<unsigned int>& _Indices);
		// Mesh Name
		std::string MeshName;
		// Vertex List
		std::vector<Vertex> Vertices;
		// Index List
		std::vector<unsigned int> Indices;
		void Render(ID3D11DeviceContext* deviceContext);
		void RenderBuffers(ID3D11DeviceContext* deviceContext);
		ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
		ID3D11ShaderResourceView* m_dtexture;
		WCHAR* dtexture_addr;
		bool LoadTexture(ID3D11Device* device, WCHAR* filename);
		void Shutdown();
		int m_vertexCount, m_indexCount;
		// Material
		Material MeshMaterial;
	};

	// Namespace: Math
	//
	// Description: The namespace that holds all of the math
	//	functions need for OBJL
	namespace objmath
	{
		// ObjVector3 Cross Product
		extern ObjVector3 CrossV3(const ObjVector3 a, const ObjVector3 b);

		// ObjVector3 Magnitude Calculation
		extern float obj_ManitudeV3(const ObjVector3 in);

		// ObjVector3 DotProduct
		extern float DotV3(const ObjVector3 a, const ObjVector3 b);

		// Angle between 2 ObjVector3 Objects
		extern float AngleBetweenV3(const ObjVector3 a, const ObjVector3 b);
	}

	// Namespace: Algorithm
	//
	// Description: The namespace that holds all of the
	// Algorithms needed for OBJL
	namespace objalgorithm
	{
		// ObjVector3 Multiplication Opertor Overload
		extern ObjVector3 operator*(const float& left, const ObjVector3& right);

		// Check to see if a ObjVector3 Point is within a 3 ObjVector3 Triangle
		extern bool inTriangle(ObjVector3 point, ObjVector3 tri1, ObjVector3 tri2, ObjVector3 tri3);

		// Split a String into a string array at a given token
		extern void split(const std::string &in,
			std::vector<std::string> &out,
			std::string token);


		// Get tail of string after first token and possibly following spaces
		extern std::string tail(const std::string &in);

		// Get first token of string
		extern  std::string firstToken(const std::string &in);

		// Get element at given index position
		template <class T>
		extern const T & getElement(const std::vector<T> &elements, std::string &index);
	}

	// Class: Loader
	//
	// Description: The OBJ Model Loader
	class Loader
	{
	public:
		// Default Constructor
		Loader();
		~Loader();

		// Load a file into the loader
		//
		// If file is loaded return true
		//
		// If the file is unable to be found
		// or unable to be loaded return false
		bool LoadFile(std::string Path);

		// Loaded Mesh Objects
		std::vector<Mesh> LoadedMeshes;
		// Loaded Vertex Objects
		std::vector<Vertex> LoadedVertices;
		// Loaded Index Positions
		std::vector<unsigned int> LoadedIndices;
		// Loaded Material Objects
		std::vector<Material> LoadedMaterials;

	private:
		// Generate vertices from a list of positions, 
		//	tcoords, normals and a face line
		void GenVerticesFromRawOBJ(std::vector<Vertex>& oVerts,
			const std::vector<ObjVector3>& iPositions,
			const std::vector<Vector2>& iTCoords,
			const std::vector<ObjVector3>& iNormals,
			std::string icurline);

		// Triangulate a list of vertices into a face by printing
		//	inducies corresponding with triangles within it
		void VertexTriangluation(std::vector<unsigned int>& oIndices,
			const std::vector<Vertex>& iVerts);

		// Load Materials from .mtl file
		bool LoadMaterials(std::string path);
	};
}
#endif