
#include "EngineConfig.h"
#include "AirplaneObj.h"
#include "EngineConfig.h"

#include <fstream>
#include <sstream>
#include <string>

template class AirplaneObj<NUMBERTYPE>;

static void splitFaceLine(std::string& line, std::vector<std::string> & tokens) 
{
	unsigned previous = 1;
	for (unsigned i = 2; i < line.size(); i++) {
		if (line[i] == '/' || line[i] == ' ') {
			tokens.push_back(line.substr(previous+1, i - previous-1)); 
			previous = i;
		}
	}
}

template<class numT>
AirplaneObj<numT>::AirplaneObj() : Object3D<numT>(nullptr, 0, nullptr, 0){
	try {

		std::ifstream file;

		file.open("c:\\temp\\Airplane.obj");
	
		std::string line;
		while (std::getline(file, line)) 
		{
			std::stringstream ss;
			ss << line;
			char junk;

			if (line[0] == 'v') 
			{
				Vector3D<numT> temp;
				ss >> junk;
				ss >> temp.X >> temp.Y >> temp.Z;
				verts.push_back(temp);
			}

			if (line[0] == 'f') {
				std::vector<std::string> tokens;
				splitFaceLine(line, tokens);
				unsigned i1 = stoi(tokens[0]) - 1;
				unsigned i2 = stoi(tokens[3]) - 1;
				unsigned i3 = stoi(tokens[6]) - 1;
				faces.push_back(Face(i1, i2, i3));
			}
		}

		this->faceN = faces.size();
		Object3D<numT>::faces = &faces[0];

		this->vertN = verts.size();
		Object3D<numT>::verts = &verts[0];

		Renderable<numT>:: SetColor(Color(150, 150, 250));
	}
	catch (std::exception ex) {
		// TODO
	}
}

template<class numT>
void AirplaneObj<numT>::ObjectToWorld(Camera<numT>* camera, Vector3D<numT>* rotatedVerts,
	unsigned int& num, Face3D<numT>* facesOut, unsigned int& facesNum, bool backfaceCulling)
{
	Object3D<numT>::ObjectToWorld(nullptr, rotatedVerts, num, facesOut, facesNum, backfaceCulling);
}

template<class numT>
void AirplaneObj<numT>::UpdateModellToWorldMatrix()
{
	Object3D<numT>::UpdateModellToWorldMatrix();
}
