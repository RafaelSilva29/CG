
#ifndef __main__main__
#define __main__main__

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include "tinyxml/tinyxml.h"
#include "tinyxml/tinystr.h"

using namespace std;

class Ponto {
public:
	float coordx;
	float coordy;
	float coordz;

};

class Modelo{
	public: 
	string ficheiro; 
	list<Ponto> pontos ; 
	Modelo(){ this->ficheiro = "untitled" ; this->pontos = list<Ponto>() ; }
	Modelo( const string& ficheiro, list<Ponto> pontos){
		this->ficheiro = ficheiro ; 
		this->pontos = pontos ; 
	}
} ; 

class Figura {
public:
	list<Modelo> modelos;
	Figura() { this->modelos = list<Modelo>(); }
	Figura(list<Modelo> modelos) { this->modelos = modelos; }
	void load(const char* pFilename) ; 
};

void Figura :: load(const char* pFilename) {
	TiXmlDocument doc(pFilename) ; 
	if(!doc.LoadFile()) return ; 
	TiXmlElement* root = doc.RootElement() ; 

	for(TiXmlElement* pModeloNode = root->FirstChild("model")->ToElement() ; pModeloNode ; pModeloNode= pModeloNode->NextSiblingElement()){
		Modelo m ; 
		const char* ficheiro = pModeloNode->Attribute("file") ; 
		if(ficheiro) m.ficheiro = ficheiro ; 

		fstream f ; 
		f.open(m.ficheiro.c_str()) ; 

		if(f.is_open()){
			string line ; 
			while(getline(f,line)){
				float coordx,coordy,coordz ; 
				sscanf(line.c_str() , "%f %f %f\n" , &coordx,&coordy,&coordz) ; 
				Ponto p ; 
				p.coordx = coordx ; p.coordy=coordy ; p.coordz=coordz ; 
				m.pontos.push_back(p) ; 
			}
			f.close() ;
		}
			modelos.push_back(m) ; 
	}

}
#endif 
