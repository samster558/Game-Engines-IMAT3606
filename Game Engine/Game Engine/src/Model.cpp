#include "Model.h"

Model::Model(float tx, float ty, float tz, float rx, float ry, float rz, float sx, float sy, float sz, float aix, float aiy, float aiz) //set all values to the correct attributes
{
	// Set the default parameters for a model

	xTranslate = tx;	  
	xRotate = rx;
	xScale = sx;

	yTranslate = ty;
	yRotate = ry;
	yScale = sy;

 	zTranslate = tz;
	zRotate = rz;
	zScale = sz;

	angleIncrementX = aix;
	angleIncrementY = aiy;
	angleIncrementZ = aiz;

	totalAngleIncrementX = 0;
	totalAngleIncrementY = 0;
	totalAngleIncrementZ = 0;
}

bool Model::loadModel(string fileName) // Load model function
{
	ifstream objectFile;

	enum lineType{unknown,v,f,vn, vt};
	string inputLine;
	lineType thisline;
	size_t found;
	thisline = unknown;

	stringstream ss;
	float Vx, Vy, Vz;
	float f1, f2, f3;
	float Vn1, Vn2, Vn3;
	float Vt1, Vt2;
	int fV, fVt, fVn;

	// Open the specified file
	objectFile.open(fileName);
	
	// Output error message if the file could not open
	if(!objectFile.is_open())
	{
		cout<<"file not found"<<endl<<endl;
		return false;
	}

	// Push back dummy values into the vectors
	verticesFile.push_back(0.f);
	verticesFile.push_back(0.f);
	verticesFile.push_back(0.f);
	vertexTexturesFile.push_back(0.f);
	vertexTexturesFile.push_back(0.f);
	vertexNormalsFile.push_back(0.f);
	vertexNormalsFile.push_back(0.f);
	vertexNormalsFile.push_back(0.f);

	// While file has not reached the end
	while(!objectFile.eof())
	{
		getline(objectFile, inputLine);
		ss.str("");
		ss.clear();
		// Checks for lines starting with v
		found = inputLine.find("v ");
		if(found!=string::npos)
		{
			thisline = v;
			
			ss.str(inputLine);
			ss.ignore(1);
			
			ss>>Vx>>Vy>>Vz;
			verticesFile.push_back(Vx);
			verticesFile.push_back(Vy);
			verticesFile.push_back(Vz);
		}

		found = inputLine.find("vn");
		if(found!=string::npos)
		{
			thisline = vn;
			
			ss.str(inputLine);
			ss.ignore(2);

			ss>>Vn1>>Vn2>>Vn3;
		
			vertexNormalsFile.push_back(Vn1);
			vertexNormalsFile.push_back(Vn2);
			vertexNormalsFile.push_back(Vn3);
		}

		found = inputLine.find("vt");
		if(found!=string::npos)
		{
			thisline = vt;
			
			ss.str(inputLine);
			ss.ignore(2);

			ss>>Vt1>>Vt2;
		
			vertexTexturesFile.push_back(Vt1);
			vertexTexturesFile.push_back(Vt2);
		}

		// Checks for lines starting with f
		found = inputLine.find("f ");
		if(found!=string::npos)
		{
			thisline = f;
			ss.str(inputLine);
			ss.ignore(1);

			for(int i = 0; i < 3; ++i)
			{
				ss>>fV;
				indices.push_back(fV);
				fV = fV * 3;
				vertices.push_back(verticesFile[fV]);
				vertices.push_back(verticesFile[fV+1]);
				vertices.push_back(verticesFile[fV+2]);
			 
				if(ss.peek() == '/')
				{
					ss.ignore(1);
					if(ss.peek() == '/')
					{
						ss.ignore(1);
						ss>>fVn;
						fNormal.push_back(fVn);
						fVn = fVn *3;
						normals.push_back(vertexNormalsFile[fVn]);
						normals.push_back(vertexNormalsFile[fVn+1]);
						normals.push_back(vertexNormalsFile[fVn+2]);

					}else{

						ss>>fVt;
						fTexture.push_back(fVt);
						fVt = fVt*2;
						textures.push_back(vertexTexturesFile[fVt]);
						textures.push_back(vertexTexturesFile[fVt+1]);

						if(ss.peek() == '/')
						{
							ss.ignore(1);
							ss>>fVn;
							fNormal.push_back(fVn);
							fVn = fVn *3;
							normals.push_back(vertexNormalsFile[fVn]);
							normals.push_back(vertexNormalsFile[fVn+1]);
							normals.push_back(vertexNormalsFile[fVn+2]);
						}
					}
				}
			}
		}
	}return true;
}

bool Model::loadTexture(string fileName) // Load texture from file
{
	ifstream textureFile;

	// Read in first texture
	textureFile.open(fileName,ios::binary);
	if (!textureFile)
	{
		cout<< "error opening texture: "<<fileName<<endl<<endl;
		return false;
	}
	
	textureFile.read(textureData,256*256*3);
	textureFile.close();
		
	glGenTextures(1, textureID);

	return true;
}

void Model::draw()
{
	glPushMatrix();
	
	glVertexPointer(3, GL_FLOAT, 0, &vertices[0]); 
	glNormalPointer(GL_FLOAT,0,&normals[0]);
	glTexCoordPointer(2, GL_FLOAT, 0, &textures[0]);
	
	glBindTexture(GL_TEXTURE_2D,textureID[0]);
	glTexImage2D(GL_TEXTURE_2D,0,3,256,256,0,GL_RGB,GL_UNSIGNED_BYTE,textureData);
		
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_CLAMP);

	glTranslatef(xTranslate, yTranslate, zTranslate);

	glRotatef(xRotate, 1.0f, 0.0f, 0.0f);
	glRotatef(yRotate, 0.0f, 1.0f, 0.0f);
	glRotatef(zRotate, 0.0f, 0.0f, 1.0f);

	// Update the totalAngleIncrement values

	totalAngleIncrementX += angleIncrementX;
	totalAngleIncrementY += angleIncrementY;
	totalAngleIncrementZ += angleIncrementZ;

	// Clamp the angle between 0 and 360 to stop it from reaching massive values

	if(totalAngleIncrementX > 360)
	{
		totalAngleIncrementX = 0;
	}
	if(totalAngleIncrementY > 360)
	{
		totalAngleIncrementY = 0;
	}
	if(totalAngleIncrementX > 360)
	{
		totalAngleIncrementZ = 0;
	}

	// Apply the constantly updating rotations

	glRotatef(totalAngleIncrementX, 1.0f, 0.0f, 0.0f);
	glRotatef(totalAngleIncrementY, 0.0f, 1.0f, 0.0f);
	glRotatef(totalAngleIncrementZ, 0.0f, 0.0f, 1.0f);

	if(xScale > 0) glScalef(xScale, 1, 1);
	if(yScale > 0) glScalef(1, yScale, 1);
	if(zScale > 0) glScalef(1, 1, zScale);

	glDrawArrays(GL_TRIANGLES,0,(GLsizei) (vertices.size()/3));

	glPopMatrix();
}