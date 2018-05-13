#include"OBJ_Loader.h"
namespace objl
{
	// Structure: Vector2
	//
	// Description: A 2D Vector that Holds Positional Data

		// Default Constructor
		Vector2::Vector2()
		{
			X = 0.0f;
			Y = 0.0f;
		}
		// Variable Set Constructor
		Vector2::Vector2(float X_, float Y_)
		{
			X = X_;
			Y = Y_;
		}
		// Bool Equals Operator Overload
		bool Vector2::operator==(const Vector2& other) const
		{
			return (this->X == other.X && this->Y == other.Y);
		}
		// Bool Not Equals Operator Overload
		bool Vector2::operator!=(const Vector2& other) const
		{
			return !(this->X == other.X && this->Y == other.Y);
		}
		// Addition Operator Overload
		Vector2 Vector2::operator+(const Vector2& right) const
		{
			return Vector2(this->X + right.X, this->Y + right.Y);
		}
		// Subtraction Operator Overload
		Vector2 Vector2:: operator-(const Vector2& right) const
		{
			return Vector2(this->X - right.X, this->Y - right.Y);
		}
		// Float Multiplication Operator Overload
		Vector2 Vector2::operator*(const float& other) const
		{
			return Vector2(this->X *other, this->Y * other);
		}

	// Structure: ObjVector3
	//
	// Description: A 3D Vector that Holds Positional Data

		// Default Constructor
		ObjVector3::ObjVector3()
		{
			X = 0.0f;
			Y = 0.0f;
			Z = 0.0f;
		}
		// Variable Set Constructor
		ObjVector3::ObjVector3(float X_, float Y_, float Z_)
		{
			X = X_;
			Y = Y_;
			Z = Z_;
		}
		// Bool Equals Operator Overload
		bool ObjVector3::operator==(const ObjVector3& other) const
		{
			return (this->X == other.X && this->Y == other.Y && this->Z == other.Z);
		}
		// Bool Not Equals Operator Overload
		bool ObjVector3::operator!=(const ObjVector3& other) const
		{
			return !(this->X == other.X && this->Y == other.Y && this->Z == other.Z);
		}
		// Addition Operator Overload
		ObjVector3 ObjVector3::operator+(const ObjVector3& right) const
		{
			return ObjVector3(this->X + right.X, this->Y + right.Y, this->Z + right.Z);
		}
		// Subtraction Operator Overload
		ObjVector3 ObjVector3::operator-(const ObjVector3& right) const
		{
			return ObjVector3(this->X - right.X, this->Y - right.Y, this->Z - right.Z);
		}
		// Float Multiplication Operator Overload
		ObjVector3 ObjVector3::operator*(const float& other) const
		{
			return ObjVector3(this->X *other, this->Y * other, this->Z - other);
		}


	// Structure: Mesh
		Mesh::Mesh()
		{
			m_indexBuffer = 0;
			m_vertexBuffer = 0;
			m_vertexCount = 0;
			m_indexCount = 0;
			m_dtexture = nullptr;
		}
		// Variable Set Constructor
		Mesh::Mesh(std::vector<Vertex>& _Vertices, std::vector<unsigned int>& _Indices)
		{
			Vertices = _Vertices;
			Indices = _Indices;
			m_dtexture = nullptr;
		}
		void Mesh::Render(ID3D11DeviceContext* deviceContext)
		{
			// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
			RenderBuffers(deviceContext);
			return;
		}
		void Mesh::RenderBuffers(ID3D11DeviceContext* deviceContext)
		{
			unsigned int stride;
			unsigned int offset;
			// Set vertex buffer stride and offset.
			stride = sizeof(Vertex);
			offset = 0;

			// Set the vertex buffer to active in the input assembler so it can be rendered.
			deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
			// Set the index buffer to active in the input assembler so it can be rendered.
			deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
			// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
			deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			return;
		}
		bool Mesh::LoadTexture(ID3D11Device* device, WCHAR* filename)
		{
			HRESULT result;
			// Load the texture in.
			result = D3DX11CreateShaderResourceViewFromFile(device, filename, NULL, NULL, &m_dtexture, NULL);
			if (FAILED(result))
			{
				return false;
			}
			return true;
		}
		void Mesh::Shutdown()
		{
			// Release the texture resource.
			if (m_indexBuffer)
			{
				m_indexBuffer->Release();
				m_indexBuffer = 0;
			}
			if (m_vertexBuffer)
			{
				m_vertexBuffer->Release();
				m_vertexBuffer = 0;
			}
			if (m_dtexture)
			{
				m_dtexture->Release();
				m_dtexture = 0;
			}
			return;
		}
	// Namespace: Math
	//
	// Description: The namespace that holds all of the math
	//	functions need for OBJL

		ObjVector3 objmath::CrossV3(const ObjVector3 a, const ObjVector3 b)
		{
			return ObjVector3(a.Y * b.Z - a.Z * b.Y,
				a.Z * b.X - a.X * b.Z,
				a.X * b.Y - a.Y * b.X);
		}

		// ObjVector3 Magnitude Calculation
		float objmath::obj_ManitudeV3(const ObjVector3 in)
		{
			return (sqrtf(powf(in.X, 2) + powf(in.Y, 2) + powf(in.Z, 2)));
		}

		// ObjVector3 DotProduct
		float objmath::DotV3(const ObjVector3 a, const ObjVector3 b)
		{
			return (a.X * b.X) + (a.Y * b.Y) + (a.Z * b.Z);
		}

		// Angle between 2 ObjVector3 Objects
		float objmath::AngleBetweenV3(const ObjVector3 a, const ObjVector3 b)
		{
			float angle = DotV3(a, b);
			angle /= (obj_ManitudeV3(a) * obj_ManitudeV3(b));
			return angle = acosf(angle);
		}
	

	// Namespace: Algorithm
	//
	// Description: The namespace that holds all of the
	// Algorithms needed for OBJL
		// ObjVector3 Multiplication Opertor Overload
		ObjVector3 objalgorithm::operator*(const float& left, const ObjVector3& right)
		{
			return ObjVector3(right.X * left, right.Y * left, right.Z * left);
		}

		// Check to see if a ObjVector3 Point is within a 3 ObjVector3 Triangle
		bool objalgorithm::inTriangle(ObjVector3 point, ObjVector3 tri1, ObjVector3 tri2, ObjVector3 tri3)
		{
			// Starting vars
			ObjVector3 u = tri2 - tri1;
			ObjVector3 v = tri3 - tri1;
			ObjVector3 w = point - tri1;
			ObjVector3 n = objmath::CrossV3(u, v);

			float y = (objmath::DotV3(objmath::CrossV3(u, w), n) / objmath::DotV3(n, n));
			float b = (objmath::DotV3(objmath::CrossV3(u, w), n) / objmath::DotV3(n, n));
			float a = 1 - y - b;

			// Projected point
			ObjVector3  p = (a * tri1) + (b * tri2) + (y * tri3);

			if (a >= 0 && a <= 1
				&& b >= 0 && b <= 1
				&& y >= 0 && y <= 1)
			{
				return true;
			}
			else
				return false;
		}

		// Split a String into a string array at a given token
		void objalgorithm::split(const std::string &in,
			std::vector<std::string> &out,
			std::string token)
		{
			out.clear();

			std::string temp;

			for (int i = 0; i < int(in.size()); i++)
			{
				std::string test = in.substr(i, token.size());

				if (test == token)
				{
					if (!temp.empty())
					{
						out.push_back(temp);
						temp.clear();
						i += (int)token.size() - 1;
					}
					else
					{
						out.push_back("");
					}
				}
				else if (i + token.size() >= in.size())
				{
					temp += in.substr(i, token.size());
					out.push_back(temp);
					break;
				}
				else
				{
					temp += in[i];
				}
			}
		}

		// Get tail of string after first token and possibly following spaces
		std::string objalgorithm::tail(const std::string &in)
		{
			size_t token_start = in.find_first_not_of(" \t");
			size_t space_start = in.find_first_of(" \t", token_start);
			size_t tail_start = in.find_first_not_of(" \t", space_start);
			size_t tail_end = in.find_last_not_of(" \t");
			if (tail_start != std::string::npos && tail_end != std::string::npos)
			{
				return in.substr(tail_start, tail_end - tail_start + 1);
			}
			else if (tail_start != std::string::npos)
			{
				return in.substr(tail_start);
			}
			return "";
		}

		// Get first token of string
		std::string objalgorithm::firstToken(const std::string &in)
		{
			if (!in.empty())
			{
				size_t token_start = in.find_first_not_of(" \t");
				size_t token_end = in.find_first_of(" \t", token_start);
				if (token_start != std::string::npos && token_end != std::string::npos)
				{
					return in.substr(token_start, token_end - token_start);
				}
				else if (token_start != std::string::npos)
				{
					return in.substr(token_start);
				}
			}
			return "";
		}

		// Get element at given index position
		template <class T>
		const T & objalgorithm::getElement(const std::vector<T> &elements, std::string &index)
		{
			int idx = std::stoi(index);
			if (idx < 0)
				idx = int(elements.size()) + idx;
			else
				idx--;
			return elements[idx];
		}

	// Class: Loader
	//
	// Description: The OBJ Model Loader

		// Default Constructor
		Loader::Loader()
		{

		}
		Loader::~Loader()
		{
			LoadedMeshes.clear();
		}

		// Load a file into the loader
		//
		// If file is loaded return true
		//
		// If the file is unable to be found
		// or unable to be loaded return false
		bool Loader::LoadFile(std::string Path)
		{
			// If the file is not an .obj file return false
			if (Path.substr(Path.size() - 4, 4) != ".obj")
				return false;


			std::ifstream file(Path);

			if (!file.is_open())
				return false;

			LoadedMeshes.clear();
			LoadedVertices.clear();
			LoadedIndices.clear();

			std::vector<ObjVector3> Positions;
			std::vector<Vector2> TCoords;
			std::vector<ObjVector3> Normals;

			std::vector<Vertex> Vertices;
			std::vector<unsigned int> Indices;

			std::vector<std::string> MeshMatNames;

			bool listening = false;
			std::string meshname;

			Mesh tempMesh;

			/*		#ifdef OBJL_CONSOLE_OUTPUT
			const unsigned int outputEveryNth = 1000;
			unsigned int outputIndicator = outputEveryNth;
			#endif*/

			std::string curline;
			while (std::getline(file, curline))
			{
				//#ifdef OBJL_CONSOLE_OUTPUT
				//if ((outputIndicator = ((outputIndicator + 1) % outputEveryNth)) == 1)
				//{
				//	if (!meshname.empty())
				//	{
				//		std::cout
				//			<< "\r- " << meshname
				//			<< "\t| vertices > " << Positions.size()
				//			<< "\t| texcoords > " << TCoords.size()
				//			<< "\t| normals > " << Normals.size()
				//			<< "\t| triangles > " << (Vertices.size() / 3)
				//			<< (!MeshMatNames.empty() ? "\t| material: " + MeshMatNames.back() : "");
				//	}
				//}
				//#endif

				// Generate a Mesh Object or Prepare for an object to be created
				if (objalgorithm::firstToken(curline) == "o" || objalgorithm::firstToken(curline) == "g" || curline[0] == 'g')
				{
					if (!listening)
					{
						listening = true;

						if (objalgorithm::firstToken(curline) == "o" || objalgorithm::firstToken(curline) == "g")
						{
							meshname = objalgorithm::tail(curline);
						}
						else
						{
							meshname = "unnamed";
						}
					}
					else
					{
						// Generate the mesh to put into the array

						if (!Indices.empty() && !Vertices.empty())
						{
							// Create Mesh
							tempMesh = Mesh(Vertices, Indices);
							tempMesh.MeshName = meshname;

							// Insert Mesh
							LoadedMeshes.push_back(tempMesh);

							// Cleanup
							Vertices.clear();
							Indices.clear();
							meshname.clear();

							meshname = objalgorithm::tail(curline);
						}
						else
						{
							if (objalgorithm::firstToken(curline) == "o" || objalgorithm::firstToken(curline) == "g")
							{
								meshname = objalgorithm::tail(curline);
							}
							else
							{
								meshname = "unnamed";
							}
						}
					}
					/*			#ifdef OBJL_CONSOLE_OUTPUT
					std::cout << std::endl;
					outputIndicator = 0;
					#endif*/
				}
				// Generate a Vertex Position
				if (objalgorithm::firstToken(curline) == "v")
				{
					std::vector<std::string> spos;
					ObjVector3 vpos;
					objalgorithm::split(objalgorithm::tail(curline), spos, " ");

					vpos.X = std::stof(spos[0]);
					vpos.Y = std::stof(spos[1]);
					vpos.Z = std::stof(spos[2]);

					Positions.push_back(vpos);
				}
				// Generate a Vertex Texture Coordinate
				if (objalgorithm::firstToken(curline) == "vt")
				{
					std::vector<std::string> stex;
					Vector2 vtex;
					objalgorithm::split(objalgorithm::tail(curline), stex, " ");

					vtex.X = std::stof(stex[0]);
					vtex.Y = std::stof(stex[1]);

					TCoords.push_back(vtex);
				}
				// Generate a Vertex Normal;
				if (objalgorithm::firstToken(curline) == "vn")
				{
					std::vector<std::string> snor;
					ObjVector3 vnor;
					objalgorithm::split(objalgorithm::tail(curline), snor, " ");

					vnor.X = std::stof(snor[0]);
					vnor.Y = std::stof(snor[1]);
					vnor.Z = std::stof(snor[2]);

					Normals.push_back(vnor);
				}
				// Generate a Face (vertices & indices)
				if (objalgorithm::firstToken(curline) == "f")
				{
					// Generate the vertices
					std::vector<Vertex> vVerts;
					GenVerticesFromRawOBJ(vVerts, Positions, TCoords, Normals, curline);

					// Add Vertices
					for (int i = 0; i < int(vVerts.size()); i++)
					{
						Vertices.push_back(vVerts[i]);

						LoadedVertices.push_back(vVerts[i]);
					}

					std::vector<unsigned int> iIndices;

					VertexTriangluation(iIndices, vVerts);

					// Add Indices
					for (int i = 0; i < int(iIndices.size()); i++)
					{
						unsigned int indnum = (unsigned int)((Vertices.size()) - vVerts.size()) + iIndices[i];
						Indices.push_back(indnum);

						indnum = (unsigned int)((LoadedVertices.size()) - vVerts.size()) + iIndices[i];
						LoadedIndices.push_back(indnum);

					}
				}
				// Get Mesh Material Name
				if (objalgorithm::firstToken(curline) == "usemtl")
				{
					MeshMatNames.push_back(objalgorithm::tail(curline));

					// Create new Mesh, if Material changes within a group
					if (!Indices.empty() && !Vertices.empty())
					{
						// Create Mesh
						tempMesh = Mesh(Vertices, Indices);
						tempMesh.MeshName = meshname;
						int i = 2;
						while (1) {
							tempMesh.MeshName = meshname + "_" + std::to_string(i);

							for (auto &m : LoadedMeshes)
								if (m.MeshName == tempMesh.MeshName)
									continue;
							break;
						}

						// Insert Mesh
						LoadedMeshes.push_back(tempMesh);

						// Cleanup
						Vertices.clear();
						Indices.clear();
					}

#ifdef OBJL_CONSOLE_OUTPUT
					outputIndicator = 0;
#endif
				}
				// Load Materials
				if (objalgorithm::firstToken(curline) == "mtllib")
				{
					// Generate LoadedMaterial

					// Generate a path to the material file
					std::vector<std::string> temp;
					objalgorithm::split(Path, temp, "/");

					std::string pathtomat = "";

					if (temp.size() != 1)
					{
						for (int i = 0; i < (int)temp.size() - 1; i++)
						{
							pathtomat += temp[i] + "/";
						}
					}


					pathtomat += objalgorithm::tail(curline);

					/*	#ifdef OBJL_CONSOLE_OUTPUT
					std::cout << std::endl << "- find materials in: " << pathtomat << std::endl;
					#endif*/

					// Load Materials
					LoadMaterials(pathtomat);
				}
			}

			/*	#ifdef OBJL_CONSOLE_OUTPUT
			std::cout << std::endl;
			#endif*/

			// Deal with last mesh

			if (!Indices.empty() && !Vertices.empty())
			{
				// Create Mesh
				tempMesh = Mesh(Vertices, Indices);
				tempMesh.MeshName = meshname;

				// Insert Mesh
				LoadedMeshes.push_back(tempMesh);
			}

			file.close();

			// Set Materials for each Mesh
			for (int i = 0; i < (int)MeshMatNames.size(); i++)
			{
				std::string matname = MeshMatNames[i];

				// Find corresponding material name in loaded materials
				// when found copy material variables into mesh material
				for (int j = 0; j < (int)LoadedMaterials.size(); j++)
				{
					if (LoadedMaterials[j].name == matname)
					{
						LoadedMeshes[i].MeshMaterial = LoadedMaterials[j];
						break;
					}
				}
			}

			if (LoadedMeshes.empty() && LoadedVertices.empty() && LoadedIndices.empty())
			{
				return false;
			}
			else
			{
				return true;
			}
		}

		void Loader::GenVerticesFromRawOBJ(std::vector<Vertex>& oVerts,
			const std::vector<ObjVector3>& iPositions,
			const std::vector<Vector2>& iTCoords,
			const std::vector<ObjVector3>& iNormals,
			std::string icurline)
		{
			std::vector<std::string> sface, svert;
			Vertex vVert;
			objalgorithm::split(objalgorithm::tail(icurline), sface, " ");

			bool noNormal = false;

			// For every given vertex do this
			for (int i = 0; i < int(sface.size()); i++)
			{
				// See What type the vertex is.
				int vtype;

				objalgorithm::split(sface[i], svert, "/");

				// Check for just position - v1
				if (svert.size() == 1)
				{
					// Only position
					vtype = 1;
				}

				// Check for position & texture - v1/vt1
				if (svert.size() == 2)
				{
					// Position & Texture
					vtype = 2;
				}

				// Check for Position, Texture and Normal - v1/vt1/vn1
				// or if Position and Normal - v1//vn1
				if (svert.size() == 3)
				{
					if (svert[1] != "")
					{
						// Position, Texture, and Normal
						vtype = 4;
					}
					else
					{
						// Position & Normal
						vtype = 3;
					}
				}

				// Calculate and store the vertex
				switch (vtype)
				{
				case 1: // P
				{
					vVert.Position = objalgorithm::getElement(iPositions, svert[0]);
					vVert.TextureCoordinate = Vector2(0, 0);
					noNormal = true;
					oVerts.push_back(vVert);
					break;
				}
				case 2: // P/T
				{
					vVert.Position = objalgorithm::getElement(iPositions, svert[0]);
					vVert.TextureCoordinate = objalgorithm::getElement(iTCoords, svert[1]);
					noNormal = true;
					oVerts.push_back(vVert);
					break;
				}
				case 3: // P//N
				{
					vVert.Position = objalgorithm::getElement(iPositions, svert[0]);
					vVert.TextureCoordinate = Vector2(0, 0);
					vVert.Normal = objalgorithm::getElement(iNormals, svert[2]);
					oVerts.push_back(vVert);
					break;
				}
				case 4: // P/T/N
				{
					vVert.Position = objalgorithm::getElement(iPositions, svert[0]);
					vVert.TextureCoordinate = objalgorithm::getElement(iTCoords, svert[1]);
					vVert.Normal = objalgorithm::getElement(iNormals, svert[2]);
					oVerts.push_back(vVert);
					break;
				}
				default:
				{
					break;
				}
				}
			}

			// take care of missing normals
			// these may not be truly acurate but it is the 
			// best they get for not compiling a mesh with normals	
			if (noNormal)
			{
				ObjVector3 A = oVerts[0].Position - oVerts[1].Position;
				ObjVector3 B = oVerts[2].Position - oVerts[1].Position;

				ObjVector3 normal = objmath::CrossV3(A, B);

				for (int i = 0; i < int(oVerts.size()); i++)
				{
					oVerts[i].Normal = normal;
				}
			}
		}

		// Triangulate a list of vertices into a face by printing
		//	inducies corresponding with triangles within it
		void Loader::VertexTriangluation(std::vector<unsigned int>& oIndices,
			const std::vector<Vertex>& iVerts)
		{
			// If there are 2 or less verts,
			// no triangle can be created,
			// so exit
			if (iVerts.size() < 3)
			{
				return;
			}
			// If it is a triangle no need to calculate it
			if (iVerts.size() == 3)
			{
				oIndices.push_back(0);
				oIndices.push_back(1);
				oIndices.push_back(2);
				return;
			}

			// Create a list of vertices
			std::vector<Vertex> tVerts = iVerts;

			while (true)
			{
				// For every vertex
				for (int i = 0; i < int(tVerts.size()); i++)
				{
					// pPrev = the previous vertex in the list
					Vertex pPrev;
					if (i == 0)
					{
						pPrev = tVerts[tVerts.size() - 1];
					}
					else
					{
						pPrev = tVerts[i - 1];
					}

					// pCur = the current vertex;
					Vertex pCur = tVerts[i];

					// pNext = the next vertex in the list
					Vertex pNext;
					if (i == tVerts.size() - 1)
					{
						pNext = tVerts[0];
					}
					else
					{
						pNext = tVerts[i + 1];
					}

					// Check to see if there are only 3 verts left
					// if so this is the last triangle
					if (tVerts.size() == 3)
					{
						// Create a triangle from pCur, pPrev, pNext
						for (int j = 0; j < int(tVerts.size()); j++)
						{
							if (iVerts[j].Position == pCur.Position)
								oIndices.push_back(j);
							if (iVerts[j].Position == pPrev.Position)
								oIndices.push_back(j);
							if (iVerts[j].Position == pNext.Position)
								oIndices.push_back(j);
						}

						tVerts.clear();
						break;
					}
					if (tVerts.size() == 4)
					{
						// Create a triangle from pCur, pPrev, pNext
						for (int j = 0; j < int(iVerts.size()); j++)
						{
							if (iVerts[j].Position == pCur.Position)
								oIndices.push_back(j);
							if (iVerts[j].Position == pPrev.Position)
								oIndices.push_back(j);
							if (iVerts[j].Position == pNext.Position)
								oIndices.push_back(j);
						}

						ObjVector3 tempVec;
						for (int j = 0; j < int(tVerts.size()); j++)
						{
							if (tVerts[j].Position != pCur.Position
								&& tVerts[j].Position != pPrev.Position
								&& tVerts[j].Position != pNext.Position)
							{
								tempVec = tVerts[j].Position;
								break;
							}
						}

						// Create a triangle from pCur, pPrev, pNext
						for (int j = 0; j < int(iVerts.size()); j++)
						{
							if (iVerts[j].Position == pPrev.Position)
								oIndices.push_back(j);
							if (iVerts[j].Position == pNext.Position)
								oIndices.push_back(j);
							if (iVerts[j].Position == tempVec)
								oIndices.push_back(j);
						}

						tVerts.clear();
						break;
					}

					// If Vertex is not an interior vertex
					float angle = (float)(objmath::AngleBetweenV3(pPrev.Position - pCur.Position, pNext.Position - pCur.Position) * (180 / 3.14159265359));
					if (angle <= 0 && angle >= 180)
						continue;

					// If any vertices are within this triangle
					bool inTri = false;
					for (int j = 0; j < int(iVerts.size()); j++)
					{
						if (objalgorithm::inTriangle(iVerts[j].Position, pPrev.Position, pCur.Position, pNext.Position)
							&& iVerts[j].Position != pPrev.Position
							&& iVerts[j].Position != pCur.Position
							&& iVerts[j].Position != pNext.Position)
						{
							inTri = true;
							break;
						}
					}
					if (inTri)
						continue;

					// Create a triangle from pCur, pPrev, pNext
					for (int j = 0; j < int(iVerts.size()); j++)
					{
						if (iVerts[j].Position == pCur.Position)
							oIndices.push_back(j);
						if (iVerts[j].Position == pPrev.Position)
							oIndices.push_back(j);
						if (iVerts[j].Position == pNext.Position)
							oIndices.push_back(j);
					}

					// Delete pCur from the list
					for (int j = 0; j < int(tVerts.size()); j++)
					{
						if (tVerts[j].Position == pCur.Position)
						{
							tVerts.erase(tVerts.begin() + j);
							break;
						}
					}

					// reset i to the start
					// -1 since loop will add 1 to it
					i = -1;
				}

				// if no triangles were created
				if (oIndices.size() == 0)
					break;

				// if no more vertices
				if (tVerts.size() == 0)
					break;
			}
		}

		// Load Materials from .mtl file
		bool Loader::LoadMaterials(std::string path)
		{
			// If the file is not a material file return false
			if (path.substr(path.size() - 4, path.size()) != ".mtl")
				return false;

			std::ifstream file(path);

			// If the file is not found return false
			if (!file.is_open())
				return false;

			Material tempMaterial;

			bool listening = false;

			// Go through each line looking for material variables
			std::string curline;
			while (std::getline(file, curline))
			{
				// new material and material name
				if (objalgorithm::firstToken(curline) == "newmtl")
				{
					if (!listening)
					{
						listening = true;

						if (curline.size() > 7)
						{
							tempMaterial.name = objalgorithm::tail(curline);
						}
						else
						{
							tempMaterial.name = "none";
						}
					}
					else
					{
						// Generate the material

						// Push Back loaded Material
						LoadedMaterials.push_back(tempMaterial);

						// Clear Loaded Material
						tempMaterial = Material();

						if (curline.size() > 7)
						{
							tempMaterial.name = objalgorithm::tail(curline);
						}
						else
						{
							tempMaterial.name = "none";
						}
					}
				}
				// Ambient Color
				if (objalgorithm::firstToken(curline) == "Ka")
				{
					std::vector<std::string> temp;
					objalgorithm::split(objalgorithm::tail(curline), temp, " ");

					if (temp.size() != 3)
						continue;

					tempMaterial.Ka.X = std::stof(temp[0]);
					tempMaterial.Ka.Y = std::stof(temp[1]);
					tempMaterial.Ka.Z = std::stof(temp[2]);
				}
				// Diffuse Color
				if (objalgorithm::firstToken(curline) == "Kd")
				{
					std::vector<std::string> temp;
					objalgorithm::split(objalgorithm::tail(curline), temp, " ");

					if (temp.size() != 3)
						continue;

					tempMaterial.Kd.X = std::stof(temp[0]);
					tempMaterial.Kd.Y = std::stof(temp[1]);
					tempMaterial.Kd.Z = std::stof(temp[2]);
				}
				// Specular Color
				if (objalgorithm::firstToken(curline) == "Ks")
				{
					std::vector<std::string> temp;
					objalgorithm::split(objalgorithm::tail(curline), temp, " ");

					if (temp.size() != 3)
						continue;

					tempMaterial.Ks.X = std::stof(temp[0]);
					tempMaterial.Ks.Y = std::stof(temp[1]);
					tempMaterial.Ks.Z = std::stof(temp[2]);
				}
				// Specular Exponent
				if (objalgorithm::firstToken(curline) == "Ns")
				{
					tempMaterial.Ns = std::stof(objalgorithm::tail(curline));
				}
				// Optical Density
				if (objalgorithm::firstToken(curline) == "Ni")
				{
					tempMaterial.Ni = std::stof(objalgorithm::tail(curline));
				}
				// Dissolve
				if (objalgorithm::firstToken(curline) == "d")
				{
					tempMaterial.d = std::stof(objalgorithm::tail(curline));
				}
				// Illumination
				if (objalgorithm::firstToken(curline) == "illum")
				{
					tempMaterial.illum = std::stoi(objalgorithm::tail(curline));
				}
				// Ambient Texture Map
				if (objalgorithm::firstToken(curline) == "map_Ka")
				{
					tempMaterial.map_Ka = objalgorithm::tail(curline);
				}
				// Diffuse Texture Map
				if (objalgorithm::firstToken(curline) == "map_Kd")
				{
					tempMaterial.map_Kd = objalgorithm::tail(curline);
				}
				// Specular Texture Map
				if (objalgorithm::firstToken(curline) == "map_Ks")
				{
					tempMaterial.map_Ks = objalgorithm::tail(curline);
				}
				// Specular Hightlight Map
				if (objalgorithm::firstToken(curline) == "map_Ns")
				{
					tempMaterial.map_Ns = objalgorithm::tail(curline);
				}
				// Alpha Texture Map
				if (objalgorithm::firstToken(curline) == "map_d")
				{
					tempMaterial.map_d = objalgorithm::tail(curline);
				}
				// Bump Map
				if (objalgorithm::firstToken(curline) == "map_Bump" || objalgorithm::firstToken(curline) == "map_bump" || objalgorithm::firstToken(curline) == "bump")
				{
					tempMaterial.map_bump = objalgorithm::tail(curline);
				}
			}

			// Deal with last material

			// Push Back loaded Material
			LoadedMaterials.push_back(tempMaterial);

			// Test to see if anything was loaded
			// If not return false
			if (LoadedMaterials.empty())
				return false;
			// If so return true
			else
				return true;
		}
}
