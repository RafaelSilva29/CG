
#include <stdio.h>
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
    float coordx;
    float coordy;
    float coordz;
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
};

//Define uma lista de pontos
class Model{
public:
    string file;
    list<Point> points;
};

//Transformações necessárias para o Sistema Solar: Translação, Rotação e Escala
class Specs{
public:
    float coordx, coordy, coordz;
    float angle, axisx, axisy, axisz;
    float scale_x, scale_y, scale_z;
};

//Reunião de todas as estruturas anteriores
class Group{
public:
    string type; // planeta ou orbita
    Specs specs;
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
        //specs
        Specs t;
        TiXmlNode* tNode = gNode->FirstChild("specs");
        if(tNode){
            TiXmlElement* tElem = tNode->ToElement();
            const char *tX = tElem->Attribute("X"), *tY = tElem->Attribute("Y"), *tZ = tElem->Attribute("Z");
            const char *angle = tElem->Attribute("angle") , *axisX = tElem->Attribute("axisX"), *axisY = tElem->Attribute("axisY"), *axisZ = tElem->Attribute("axisZ");
            const char *eX = tElem->Attribute("scale_x"), *eY = tElem->Attribute("scale_y"), *eZ = tElem->Attribute("scale_z");
            if(tX) t.coordx = atof(tX); else t.coordx = 0;
            if(tY) t.coordy = atof(tY); else t.coordy = 0;
            if(tZ) t.coordz = atof(tZ); else t.coordz = 0;
            if(angle) t.angle = atof(angle); else t.angle = 0;
            if(axisX) t.axisx = atof(axisX); else t.axisx = 0;
            if(axisY) t.axisy = atof(axisY); else t.axisy = 0;
            if(axisZ) t.axisz = atof(axisZ); else t.axisz = 0;
            if(eX) t.scale_x = atof(eX); else t.scale_x = 1;
            if(eY) t.scale_y = atof(eY); else t.scale_y = 1;
            if(eZ) t.scale_z = atof(eZ); else t.scale_z = 1;
        }
        else { t.coordx = 0; t.coordy = 0; t.coordz = 0; t.angle=0; t.axisx=0; t.axisy=0; t.axisz=0; t.scale_x=1; t.scale_y=1; t.scale_z=1; }
        g.specs = t;
        
        //cor
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
        
        //orbita
        Orbit o;
        TiXmlNode* oNode = gNode->FirstChild("orbit");
        if(oNode){
            TiXmlElement* oElem = oNode->ToElement();
            const char *rX = oElem->Attribute("radiusX"), *rZ = oElem->Attribute("radiusZ");
            if(rX) o.radiusX = atof(rX); else o.radiusX = 0;
            if(rZ) o.radiusZ = atof(rZ); else o.radiusZ = 0;
            
            g.type = "orbit";
        }
        else { o.radiusX = 0; o.radiusZ = 0; g.type = "planet"; }
        g.orbit = o;
        
        //modelos
        TiXmlNode* mNode = gNode->FirstChild("models");
        if(mNode){
            TiXmlElement* mElem = mNode->ToElement();
            TiXmlNode* testNode = mElem->FirstChild("model");
            if(testNode){
                for(TiXmlElement* modElem = mElem->FirstChild("model")->ToElement() ; modElem; modElem = modElem->NextSiblingElement()){
                    Model m;
                    const char *file = modElem->Attribute("file");
                    if(file) m.file = file;
                    
                    fstream f;
                    f.open(m.file.c_str());            
                    if(f.is_open()){
                        string line;
                        while (getline(f,line)){
                            float coordx,coordy,coordz;
                            sscanf(line.c_str(),"%f %f %f\n",&coordx,&coordy,&coordz);
                            Point p;
                            p.coordx = coordx; p.coordy = coordy; p.coordz = coordz;
                            m.points.push_back(p);
                        } 
                        f.close();
                    }
                    g.models.push_back(m);
                }
            }
        }
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


