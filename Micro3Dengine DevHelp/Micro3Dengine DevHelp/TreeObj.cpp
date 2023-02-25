#include "TreeObj.h"

#include <fstream>
#include <sstream>
#include <string>

template class TreeObj<NUMBERTYPE>;

static void splitFaceLine(std::string& line, std::vector<std::string>& tokens)
{
	unsigned previous = 1;
	for (unsigned i = 2; i < line.size(); i++) {
		if (line[i] == '/' || line[i] == ' ') {
			tokens.push_back(line.substr(previous + 1, i - previous - 1));
			previous = i;
		}
	}
}


template<class numT>
TreeObj<numT>::TreeObj() : Object3D<numT>(nullptr, 0, nullptr, 0) {
	try {

		if (faces.size() == 0) {
			std::ifstream file;

			file.open("c:\\temp\\Tree.obj");

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
				} else	
				if (line[0] == 'f') {
					std::vector<std::string> tokens;
					splitFaceLine(line, tokens);
					unsigned i1 = stoi(tokens[0]) - 1;
					unsigned i2 = stoi(tokens[3]) - 1;
					unsigned i3 = stoi(tokens[6]) - 1;
					faces.push_back(Face(i1, i2, i3));

					if (tokens.size() >= 9) {
						unsigned i4 = stoi(tokens[9]) - 1;
						faces.push_back(Face(i4, i1, i3));
					}
				}

			}
		}

		this->faceN = faces.size();
		Object3D<numT>::faces = &faces[0];

		this->vertN = verts.size();
		Object3D<numT>::verts = &verts[0];

		Renderable<numT>::SetColor(Color(50, 200, 50));
		Renderable<numT>::SetScale(5, 5, 5);
		Renderable<numT>::SetRotation(0, 0, 0);
	}
	catch (std::exception ex) {
		// TODO
	}
}

template<class numT>
std::vector<Vector3D<numT>> TreeObj<numT>::verts;

template<class numT>
std::vector<Face> TreeObj<numT>::faces;
