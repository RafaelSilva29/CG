#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>

#include "./Libraries/devil/IL/il.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h> 
#include <GL/glut.h>
#endif

#include <iostream>
#include <fstream>
#include <string>
#include <list>

#include "./Libraries/tinyxml/tinyxml.h"
#include "./Libraries/tinyxml/tinystr.h"

using namespace std;

//Define um ponto no espaço 3d
class Point{
public:
    float coordX;
    float coordY;
    float coordZ;
};

//Define uma translação
class Translation{
public:
    float coordX,coordY,coordZ,time;
    list<Point> points;
};

//Define uma Rotacao
class Rotation{
public:
    float angle,axisX,axisY,axisZ,time;
};

class Scale{
public:
    float scale_x,scale_y,scale_z;
};

//Define a cor do objeto
class Color{
public:
    float r,g,b;
};

//Define os raios da orbita
class Orbit{
public:
    float radiusX,radiusZ;
    int nControl;
};

//Define uma lista de pontos
class Model{
public:
    string file;
    int points;
    float ambR,ambG,ambB;
    float diffR,diffG,diffB;
    float specR,specG,specB;
    float emiR,emiG,emiB;
    string texture;
    unsigned int t,width,height,texID;
    unsigned char *texData;
    GLuint buffers[3];
};

//Reunião de todas as estruturas anteriores
class Group{
public:
    string type; // planet ou orbit
    Translation translation;
    Rotation rotation;
    Scale scale;
    Color color;
    Orbit orbit;
    list<Model> models;
    list<Group> groups;
};

//Função que vai carregar os grupos
void GRload(TiXmlNode *currentNode, list<Group> *groups){
     //percorre os grupos
    for(TiXmlNode* gNode = currentNode->FirstChild("group") ; gNode; gNode = gNode->NextSiblingElement()){
        Group g;

        //Translation
        Translation t;
        TiXmlNode* tNode = gNode->FirstChild("translation");
        if(tNode){
            TiXmlElement* tElem = tNode->ToElement();
            const char *tTime = tElem->Attribute("time");
            if(tTime) t.time = atof(tTime); else t.time = -1;
            
            if(t.time == -1){
            const char *tX = tElem->Attribute("X"), *tY = tElem->Attribute("Y"), *tZ = tElem->Attribute("Z");
            if(tX) t.coordX = atof(tX); else t.coordX = 0;
            if(tY) t.coordY = atof(tY); else t.coordY = 0;
            if(tZ) t.coordZ = atof(tZ); else t.coordZ = 0;
            }
        else {
            TiXmlNode* testNode = tElem->FirstChild("point");
            if(testNode){
                for(TiXmlElement* ptElem = tElem->FirstChild("point")->ToElement() ; ptElem; ptElem = ptElem->NextSiblingElement()){
                    Point point;
                    const char *tX = ptElem->Attribute("X"), *tY = ptElem->Attribute("Y"), *tZ = ptElem->Attribute("Z");
                    if(tX) point.coordX = atof(tX); else point.coordX = 0;
                    if(tY) point.coordY = atof(tY); else point.coordY = 0;
                    if(tZ) point.coordZ = atof(tZ); else point.coordZ = 0;
                    t.points.push_back(point);
                }
            }
            else t.time = -1;
            }
        }
        else { t.time = -1; t.coordX = 0; t.coordY = 0; t.coordZ = 0; }
        g.translation = t;

        //Rotation
        Rotation r;
        TiXmlNode* rNode = gNode->FirstChild("rotation");
        if(rNode){
            TiXmlElement* rElem = rNode->ToElement();
            const char *angle = rElem->Attribute("angle") , *axisX = rElem->Attribute("axisX"), *axisY = rElem->Attribute("axisY"), *axisZ = rElem->Attribute("axisZ"), *rTime = rElem->Attribute("time");
            if(angle) r.angle = atof(angle); else r.angle = 0;
            if(axisX) r.axisX = atof(axisX); else r.axisX = 0;
            if(axisY) r.axisY = atof(axisY); else r.axisY = 0;
            if(axisZ) r.axisZ = atof(axisZ); else r.axisX = 0;
            if(rTime) r.time = atof(rTime); else r.time = -1;
        }
        else { r.angle = 0; r.axisX = 0; r.axisY = 0; r.axisZ = 0; r.time = -1; }
        g.rotation = r;

        //Scale
        Scale s;
        TiXmlNode* eNode = gNode->FirstChild("scale");
        if(eNode){
            TiXmlElement* eElem = eNode->ToElement();
            const char *eX = eElem->Attribute("X"), *eY = eElem->Attribute("Y"), *eZ = eElem->Attribute("Z");
            if(eX) s.scale_x = atof(eX); else s.scale_x = 1;
            if(eY) s.scale_y = atof(eY); else s.scale_y = 1;
            if(eZ) s.scale_z = atof(eZ); else s.scale_z = 1;
        }
        else { s.scale_x = 1; s.scale_y = 1; s.scale_z = 1; }
        g.scale = s;
        
        //Color
        Color c;
        TiXmlNode* cNode = gNode->FirstChild("color");
        if(cNode){
            TiXmlElement* cElem = cNode->ToElement();
            const char *R = cElem->Attribute("R"), *G = cElem->Attribute("G"), *B = cElem->Attribute("B");
            if(R) c.r = atof(R); else c.r = 1;
            if(G) c.g = atof(G); else c.g = 1;
            if(B) c.b = atof(B); else c.b = 1;
        }
        else { c.r = 1; c.g = 1; c.b = 1; }
        g.color = c;
        
        //Orbit
        Orbit o;
        TiXmlNode* oNode = gNode->FirstChild("orbit");
        if(oNode){
            TiXmlElement* oElem = oNode->ToElement();
            const char *rX = oElem->Attribute("radiusX"), *rZ = oElem->Attribute("radiusZ"), *nControl = oElem->Attribute("nControl");
            if(rX) o.radiusX = atof(rX); else o.radiusX = 0;
            if(rZ) o.radiusZ = atof(rZ); else o.radiusZ = 0;
            if(nControl) o.nControl = atoi(nControl); else o.nControl = 4;
            
            if(o.nControl<4) o.nControl = 4;
            g.type = "orbit";
        }
        else { o.radiusX = 0; o.radiusZ = 0; o.nControl = 4; g.type = "planeta"; }
        g.orbit = o;
        
        //Models
        TiXmlNode* mNode = gNode->FirstChild("models");
        if(mNode){
            TiXmlElement* mElem = mNode->ToElement();
            TiXmlNode* testNode = mElem->FirstChild("model");
            if(testNode){
                for(TiXmlElement* modElem = mElem->FirstChild("model")->ToElement() ; modElem; modElem = modElem->NextSiblingElement()){
                    Model m;
                    const char *file = modElem->Attribute("file");
                    if(file) m.file = file;
                    
                    const char *ambR = modElem->Attribute("ambR"), *ambG = modElem->Attribute("ambG"), *ambB = modElem->Attribute("ambB");
                    if(ambR) m.ambR = atof(ambR); else m.ambR = 0;
                    if(ambG) m.ambG = atof(ambG); else m.ambG = 0;
                    if(ambB) m.ambB = atof(ambB); else m.ambB = 0;
                    
                    const char *diffR = modElem->Attribute("diffR"), *diffG = modElem->Attribute("diffG"), *diffB = modElem->Attribute("diffB");
                    if(diffR) m.diffR = atof(diffR); else m.diffR = 0;
                    if(diffG) m.diffG = atof(diffG); else m.diffG = 0;
                    if(diffB) m.diffB = atof(diffB); else m.diffB = 0;
                    
                    const char *specR = modElem->Attribute("specR"), *specG = modElem->Attribute("specG"), *specB = modElem->Attribute("specB");
                    if(specR) m.specR = atof(specR); else m.specR = 0;
                    if(specG) m.specG = atof(specG); else m.specG = 0;
                    if(specB) m.specB = atof(specB); else m.specB = 0;
                    
                    const char *emiR = modElem->Attribute("emiR"), *emiG = modElem->Attribute("emiG"), *emiB = modElem->Attribute("emiB");
                    if(emiR) m.emiR = atof(emiR); else m.emiR = 0;
                    if(emiG) m.emiG = atof(emiG); else m.emiG = 0;
                    if(emiB) m.emiB = atof(emiB); else m.emiB = 0;
                    
                    const char *texture = modElem->Attribute("texture");
                    if(texture) m.texture = texture;
                    
                    ilInit();
                    ilGenImages(1,&m.t);
                    ilBindImage(m.t);
                    ilLoadImage((ILstring)m.texture.c_str());
                    ilConvertImage(IL_RGBA,IL_UNSIGNED_BYTE);
                    
                    m.width = ilGetInteger(IL_IMAGE_WIDTH);
                    m.height = ilGetInteger(IL_IMAGE_HEIGHT);
                    m.texData = ilGetData();
                    
                    glGenTextures(1,&m.texID);
                    glBindTexture(GL_TEXTURE_2D,m.texID);
                    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
                    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
                    
                    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,m.width,m.height,0,GL_RGBA,GL_UNSIGNED_BYTE,m.texData);
                    
                    fstream f;
                    
                    f.open(m.file.c_str());
                    
                    if(f.is_open()){
                        string line;
                        int nPoints=0,j=0,k=0,l=0;
                        float *vertexB = NULL, *normalB = NULL, *textureB=NULL;
                        
                        if(getline(f,line)){
                            sscanf(line.c_str(),"%d\n",&nPoints);
                            m.points = nPoints;
                        }
                        
                        vertexB = (float*) malloc(3*nPoints*sizeof(float));
                        normalB = (float*) malloc(3*nPoints*sizeof(float));
                        textureB = (float*) malloc(2*nPoints*sizeof(float));
                        
                        glEnableClientState(GL_VERTEX_ARRAY);
                        glEnableClientState(GL_NORMAL_ARRAY);
                        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                   
                        
                        while(getline(f,line)){
                            float x,y,z,xIl,yIl,zIl,xText,yText;
                            sscanf(line.c_str(),"%f %f %f %f %f %f %f %f\n",&x,&y,&z,&xIl,&yIl,&zIl,&xText,&yText);
                            vertexB[j++] = x; vertexB[j++] = y; vertexB[j++] = z;
                            normalB[k++] = xIl; normalB[k++] = yIl; normalB[k++] = zIl;
                            textureB[l++] = xText; textureB[l++] = yText;
                        }
                        
                        glGenBuffers(3,m.buffers);
                        
                        glBindBuffer(GL_ARRAY_BUFFER,m.buffers[0]);
                        glBufferData(GL_ARRAY_BUFFER,3*m.points*sizeof(float),vertexB,GL_STATIC_DRAW);
                        
                        glBindBuffer(GL_ARRAY_BUFFER,m.buffers[1]);
                        glBufferData(GL_ARRAY_BUFFER,3*m.points*sizeof(float),normalB,GL_STATIC_DRAW);

                        glBindBuffer(GL_ARRAY_BUFFER,m.buffers[2]);
                        glBufferData(GL_ARRAY_BUFFER,2*m.points*sizeof(float),textureB,GL_STATIC_DRAW);
                        
                       
                        free(vertexB);
                        free(normalB);
                        free(textureB);
                        
                        f.close();
                    }
                    g.models.push_back(m);
                }
            }
        }
        
        // Recursividade sobre groups
        if(gNode) GRload(gNode,&g.groups);
        groups->push_back(g);
    }
}

// Class Light
class Light
{ public:
    float type; //0->point, 1->direction, 2->spot
    float posX,posY,posZ;
    float ambR,ambG,ambB;
    float diffR,diffG,diffB;
};

//Reunion of Groups
class Figure{
public:
    list<Group> groups;
    list<Light> lights;  
    void load(const char* pFilename);
};

void Figure::load(const char* pFilename){
    TiXmlDocument doc(pFilename);
    if (!doc.LoadFile()) return;
    TiXmlNode* nRoot = TiXmlHandle(doc.RootElement()).ToNode();

    TiXmlNode* lNode = nRoot->FirstChild("lights");
    if(lNode){
        TiXmlElement* lElem = lNode->ToElement();
        TiXmlNode* testNode = lElem->FirstChild("light");
        if(testNode)
            for(TiXmlElement* luzElem = lElem->FirstChild("light")->ToElement() ; luzElem; luzElem = luzElem->NextSiblingElement()){
                Light l;
                const char *type = luzElem->Attribute("type"), *posX = luzElem->Attribute("posX"), *posY = luzElem->Attribute("posY"), *posZ = luzElem->Attribute("posZ");
                const char *ambR = luzElem->Attribute("ambR"), *ambG = luzElem->Attribute("ambG"), *ambB = luzElem->Attribute("ambB");
                const char *diffR = luzElem->Attribute("diffR"), *diffG = luzElem->Attribute("diffG"), *diffB = luzElem->Attribute("diffB");
                if(type) l.type = atof(type); else l.type = 0;
                if(posX) l.posX = atof(posX); else l.posX = 0;
                if(posY) l.posY = atof(posY); else l.posY = 0;
                if(posZ) l.posZ = atof(posZ); else l.posZ = 0;
                if(ambR) l.ambR = atof(ambR); else l.ambR = 0;
                if(ambG) l.ambG = atof(ambG); else l.ambG = 0;
                if(ambB) l.ambB = atof(ambB); else l.ambB = 0;
                if(diffR) l.diffR = atof(diffR); else l.diffR = 0;
                if(diffG) l.diffG = atof(diffG); else l.diffG = 0;
                if(diffB) l.diffB = atof(diffB); else l.diffB = 0;
                this->lights.push_back(l);
            }
    }
    GRload(nRoot,&this->groups);
}


