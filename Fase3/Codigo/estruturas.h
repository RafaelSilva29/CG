
#include <GL/glew.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include "./tinyxml/tinyxml.h"
#include "./tinyxml/tinystr.h"

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
    GLuint buffers[2];
};

class Group{
public:
    string type; // planeta ou orbita
    Translation translation;
    Rotation rotation;
    Scale scale;
    Color color;
    Orbit orbit;
    list<Model> models;
    list<Group> groups;
};


//Função que vai carregar os grupos.
void GRload(TiXmlNode *currentNode, list<Group> *groups){
    //percorre os grupos
    for(TiXmlNode* gNode = currentNode->FirstChild("group") ; gNode; gNode = gNode->NextSiblingElement()){
        Group g;

        //Translacao
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

        //Rotacao
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
        
        //Orbita
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
        else { o.radiusX = 0; o.radiusZ = 0; o.nControl = 4; g.type = "planet"; }
        g.orbit = o;
        
        //Models
        TiXmlNode* mNode = gNode->FirstChild("models");
        if(mNode){
            TiXmlElement* mElem = mNode->ToElement();
            TiXmlNode* testNode = mElem->FirstChild("model");
            if(testNode){
                for(TiXmlElement* modElem = mElem->FirstChild("model")->ToElement(); modElem; modElem = modElem->NextSiblingElement()){
                    Model m;
                    const char *file = modElem->Attribute("file");
                    if(file) m.file = file;
                    fstream f;
                    f.open(m.file.c_str());
                    if(f.is_open()){
                        string line;
                        int nPoints=0, j=0;
                        float *verticeB = NULL;
                        
                        if(getline(f,line)){
                            sscanf(line.c_str(),"%d\n",&nPoints);
                            m.points = nPoints;
                        }
                        
                        verticeB = (float*) malloc(nPoints*sizeof(float));
                        glEnableClientState(GL_VERTEX_ARRAY);
                        
                        while(getline(f,line)){
                            float x,y,z;
                            sscanf(line.c_str(),"%f %f %f\n",&x,&y,&z);
                            verticeB[j++] = x; verticeB[j++] = y; verticeB[j++] = z;
                        }
                        
                        glGenBuffers(1,m.buffers);
                        glBindBuffer(GL_ARRAY_BUFFER,m.buffers[0]);
                        glBufferData(GL_ARRAY_BUFFER,m.points*sizeof(float),verticeB,GL_STATIC_DRAW);
                        free(verticeB);
                        
                        f.close();
                    }
                    g.models.push_back(m);
                }
            }
        }

        //Recursividade sobre grupos
        if(gNode) GRload(gNode,&g.groups);
        groups->push_back(g);
    }
}

//Reunião dos Grupos
class Figure{
public:
    list<Group> groups;  
    void load(const char* pFilename);
};

void Figure::load(const char* pFilename){
    TiXmlDocument doc(pFilename);
    if (!doc.LoadFile()) return;
    TiXmlNode* nRoot = TiXmlHandle(doc.RootElement()).ToNode();
    
    GRload(nRoot,&this->groups);
}


