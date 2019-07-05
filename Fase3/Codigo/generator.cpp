#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <fstream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//Classe Point
class Point{
	public: float x,y,z;
};

/* 
	Function that create XML File
*/
void createXML(char* filename){
	FILE* fd;
	char* temp = (char*)malloc(sizeof(char)*64);
	strcpy(temp, filename);

	char *file = strdup("XML/");

	file = strcat(file,temp);
	file = strcat(file,".xml");

	fd = fopen(file,"w"); 

	if(fd != NULL){
		char* ss = (char*)malloc(sizeof(char)*1024); 
		ss = strcat(ss, "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n<scene>\n");
		ss = strcat(ss,"<model file=\"3D/"); 
		ss = strcat(ss,temp); 
		ss = strcat(ss , ".3d\" />\n");
		ss= strcat(ss,"</scene>\n" );

		fprintf(fd,"%s",ss); 	

	} else{
		printf("Error creating XML file...\n");
	}
	
	fclose(fd); 
} 

/*
	Funtion that create figure Plane, save the figure in a *.3d file
*/
void drawPlane(float length, float width, char* filename){
	FILE* fd; 
	char* temp = (char*)malloc(sizeof(char)*64);
	strcpy(temp, filename);

	char *file = strdup("3D/");

	file = strcat(file,temp);
	file = strcat(file,".3d");

	fd = fopen(file,"w"); 

	if(fd != NULL){
		fprintf(fd, "%f %d %f \n", -length/2, 0, -width/2); 
		fprintf(fd, "%f %d %f \n", -length/2, 0, width/2);
		fprintf(fd, "%f %d %f \n", length/2, 0, width/2);  
	
		fprintf(fd, "%f %d %f \n", length/2, 0, width/2);
		fprintf(fd, "%f %d %f \n", length/2, 0, -width/2);
		fprintf(fd, "%f %d %f \n", -length/2, 0, -width/2); 

		fprintf(fd, "%f %d %f \n", -length/2, 0, -width/2); 
    	fprintf(fd, "%f %d %f \n", length/2, 0, width/2);
    	fprintf(fd, "%f %d %f \n", -length/2, 0, width/2);

    	fprintf(fd, "%f %d %f \n", length/2, 0, width/2);
    	fprintf(fd, "%f %d %f \n", -length/2, 0, -width/2); 
    	fprintf(fd, "%f %d %f \n", length/2, 0, -width/2);

	} else{
		printf("Error creating 3D file...\n");
	}

	fclose(fd) ; 
}

/*
	Funtion that create figure Box, save the figure in a *.3d file
*/
void drawBox(float length, float height, float width, char* filename){
	FILE* fd; 
	char* temp = (char*)malloc(sizeof(char)*64);
	strcpy(temp, filename);

	char *file = strdup("3D/");

	file = strcat(file,temp);
	file = strcat(file,".3d");

	fd = fopen(file,"w"); 

	if(fd != NULL){
		fprintf(fd, "%f %f %f \n", length/2, -height/2, -width/2); 
		fprintf(fd, "%f %f %f \n", -length/2, -height/2,  width/2);
		fprintf(fd, "%f %f %f \n", -length/2, -height/2, -width/2);  
	
		fprintf(fd, "%f %f %f \n", -length/2, -height/2, width/2); 
		fprintf(fd, "%f %f %f \n", length/2, -height/2, -width/2);
		fprintf(fd, "%f %f %f \n", length/2, -height/2, width/2);

		fprintf(fd, "%f %f %f \n", length/2, height/2, -width/2); 
		fprintf(fd, "%f %f %f \n", -length/2, height/2, -width/2);
		fprintf(fd, "%f %f %f \n", -length/2, height/2, width/2); 

		fprintf(fd, "%f %f %f \n", -length/2, height/2, width/2); 
		fprintf(fd, "%f %f %f \n", length/2, height/2, width/2);
		fprintf(fd, "%f %f %f \n", length/2, height/2, -width/2);

		fprintf(fd, "%f %f %f \n", -length/2, -height/2, width/2); 
		fprintf(fd, "%f %f %f \n", length/2, -height/2, width/2);
		fprintf(fd, "%f %f %f \n", -length/2, height/2, width/2);

		fprintf(fd, "%f %f %f \n", length/2, -height/2, width/2); 
		fprintf(fd, "%f %f %f \n", length/2, height/2, width/2);
		fprintf(fd, "%f %f %f \n", -length/2, height/2, width/2);

		fprintf(fd, "%f %f %f \n", length/2, -height/2, width/2); 
		fprintf(fd, "%f %f %f \n", length/2, -height/2, -width/2);
		fprintf(fd, "%f %f %f \n", length/2, height/2, width/2) ;

		fprintf(fd, "%f %f %f \n", length/2, -height/2, -width/2); 
		fprintf(fd, "%f %f %f \n", length/2, height/2, -width/2);
		fprintf(fd, "%f %f %f \n", length/2, height/2, width/2);

		fprintf(fd, "%f %f %f \n", length/2, -height/2, -width/2); 
		fprintf(fd, "%f %f %f \n", -length/2, -height/2, -width/2);
		fprintf(fd, "%f %f %f \n", length/2, height/2, -width/2);

		fprintf(fd, "%f %f %f \n", -length/2, -height/2, -width/2); 
		fprintf(fd, "%f %f %f \n", -length/2, height/2, -width/2);
		fprintf(fd, "%f %f %f \n", length/2, height/2, -width/2);

		fprintf(fd, "%f %f %f \n", -length/2, -height/2, -width/2); 
		fprintf(fd, "%f %f %f \n", -length/2, -height/2, width/2);
		fprintf(fd, "%f %f %f \n", -length/2, height/2, -width/2);

		fprintf(fd, "%f %f %f \n", -length/2, -height/2, width/2); 
		fprintf(fd, "%f %f %f \n", -length/2, height/2, width/2);
		fprintf(fd, "%f %f %f \n", -length/2, height/2, -width/2);
	} else{
		printf("Error creating 3D file...\n");
	}

	fclose(fd); 	
}

/*
	Funtion that create figure Sphere, save the figure in a *.3d file
*/
void drawSphere(float radius, int slices, int stacks, char* filename){
	FILE* fd; 
	char* temp = (char*)malloc(sizeof(char)*64);
	strcpy(temp, filename);

	char *file = strdup("3D/");

	file = strcat(file,temp);
	file = strcat(file,".3d");

	fd = fopen(file,"w"); 

	float slice = (360/slices)*(M_PI/180); 
	float stack = (180/stacks)*(M_PI/180);
	float piMeios = M_PI/2; 
	float doisPI = M_PI*2;  

	if(fd != NULL){
		for(float j = -piMeios; j < piMeios; j+=stack){
			for(float i = 0; i < doisPI; i+=slice){
				fprintf(fd, "%f %f %f \n", cos(j+stack)*sin(i)*radius, sin(j+stack)*radius, cos(j+stack)*cos(i)*radius); 
				fprintf(fd, "%f %f %f \n", cos(j)*sin(i)*radius, sin(j)*radius, cos(j)*cos(i)*radius); 
				fprintf(fd, "%f %f %f \n", cos(j)*sin(i+slice)*radius, sin(j)*radius, cos(j)*cos(i+slice)*radius); 
	
				fprintf(fd, "%f %f %f \n", cos(j+stack)*sin(i)*radius, sin(j+stack)*radius, cos(j+stack)*cos(i)*radius); 
				fprintf(fd, "%f %f %f \n", cos(j)*sin(i+slice)*radius, sin(j)*radius, cos(j)*cos(i+slice)*radius); 
				fprintf(fd, "%f %f %f \n", cos(j+stack)*sin(i+slice)*radius, sin(j+stack)*radius, cos(j+stack)*cos(i+slice)*radius); 
			}
		}
	} else{
		printf("Error creating 3D file...\n");
	}

	fclose(fd); 
}

/*
	Funtion that create figure Cone, save the figure in a *.3d file
*/
void drawCone(float radius, float height,  int slices, int stacks, char* filename){
	FILE* fd; 
	char* temp = (char*)malloc(sizeof(char)*64);
	strcpy(temp, filename);

	char *file = strdup("3D/");

	file = strcat(file,temp);
	file = strcat(file,".3d");

	fd = fopen(file,"w"); 

	float slice = (360/slices)*(M_PI/180); 
	float stack = height/stacks;
	float raio = radius/stacks; 
	float doisPI = M_PI*2;  

	if(fd != NULL){
		for(float i = 0 ; i < doisPI ; i+=slice){
			fprintf(fd, "%d %f %d \n", 0, -height/3, 0); 
			fprintf(fd, "%f %f %f \n", sin(i+slice)*radius, -height/3, cos(i+slice)*radius); 
			fprintf(fd, "%f %f %f \n", sin(i)*radius, -height/3, cos(i)*radius); 
		}
		float r = 0; 
		for(float j = -height/3; j < (height-height/3); j+=stack){
			for(float i = 0; i < doisPI; i+=slice){
				fprintf(fd, "%f %f %f \n", sin(i)*(radius-(r+raio)), j+stack, cos(i)*(radius-(r+raio))); 
				fprintf(fd, "%f %f %f \n", sin(i)*(radius-r), j, cos(i)*(radius-r)); 
				fprintf(fd, "%f %f %f \n", sin(i+slice)*(radius-r), j, cos(i+slice)*(radius-r)); 
			}
			r+=raio ; 	
		}
		r=0 ; 
		for(float k = -height/3; k < (height-height/3)-stack; k+=stack){
			for(float i = 0; i< doisPI; i+=slice){
				fprintf(fd, "%f %f %f \n", sin(i)*(radius-(r+raio)), k+stack, cos(i)*(radius-(r+raio)) ) ; 
				fprintf(fd, "%f %f %f \n", sin(i+slice)*(radius-r), k, cos(i+slice)*(radius-r)) ; 
				fprintf(fd, "%f %f %f \n", sin(i+slice)*(radius-(r+raio)),k+stack, cos(i+slice)*(radius-(r+raio))) ; 
			}
			r+=raio ; 
		}
	} else{
		printf("Error creating 3D file...\n");
	}

	fclose(fd); 
}

/*
	Funtion that create figure Ring, save the figure in a *.3d file
*/
void drawRing(float in_r , float out_r ,int slices, char* filename){
	FILE* fd; 
	char* temp = (char*)malloc(sizeof(char)*64);
	strcpy(temp, filename);

	char *file = strdup("3D/");

	file = strcat(file,temp);
	file = strcat(file,".3d");

	fd = fopen(file,"w");  

	float slice = (360/slices)*(M_PI/180);
	float doisPi = 2*M_PI;

	if (fd!=NULL){
		for (float i = 0; i < doisPi; i += slice){
			fprintf(fd , "%f %f %f \n" ,sin(i)*in_r, 0.0, cos(i)*in_r);
			fprintf(fd , "%f %f %f \n" ,sin(i)*out_r, 0.0, cos(i)*out_r);
			fprintf(fd , "%f %f %f \n" ,sin(i+slice)*in_r, 0.0, cos(i+slice)*in_r);
			fprintf(fd , "%f %f %f \n" ,sin(i)*out_r, 0.0, cos(i)*out_r);
			fprintf(fd , "%f %f %f \n" ,sin(i+slice)*out_r, 0.0, cos(i+slice)*out_r);
			fprintf(fd , "%f %f %f \n" ,sin(i+slice)*in_r, 0.0, cos(i+slice)*in_r);
			fprintf(fd , "%f %f %f \n" ,sin(i)*out_r, 0.0, cos(i)*out_r);
			fprintf(fd , "%f %f %f \n" ,sin(i)*in_r, 0.0, cos(i)*in_r);
			fprintf(fd , "%f %f %f \n" ,sin(i+slice)*in_r, 0.0, cos(i+slice)*in_r);
			fprintf(fd , "%f %f %f \n" ,sin(i+slice)*out_r, 0.0, cos(i+slice)*out_r);
			fprintf(fd , "%f %f %f \n" ,sin(i)*out_r, 0.0, cos(i)*out_r);
			fprintf(fd , "%f %f %f \n" ,sin(i+slice)*in_r, 0.0, cos(i+slice)*in_r);
		}
 	}else{
		printf("Error creating 3D file...\n");
	}

	fclose(fd); 
}


void drawPatch(const char* patchfilename, int tesselation, const char* savefilename){
    //--- PARSING PATCH ---//
    std::fstream f;
    f.open(patchfilename,std::ios::in);
    int patches=0;
    int vertices=0;
    std::vector<std::vector<int> > indicesPatch;
    std::vector<Point> vertixs;
    
    if(f.is_open()){
        std::string line;
        if(getline(f,line)) sscanf(line.c_str(),"%d\n",&patches);
        for(int i=0; i<patches ;i++){
             std::vector<int> aux;
            if(getline(f,line)){
                int n1=0,n2=0,n3=0,n4=0,n5=0,n6=0,n7=0,n8=0,n9=0,n10=0,n11=0,n12=0,n13=0,n14=0,n15=0,n16=0;
                sscanf(line.c_str(),"%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d\n",&n1,&n2,&n3,&n4,&n5,&n6,&n7,&n8,&n9,&n10,&n11,&n12,&n13,&n14,&n15,&n16);
                aux.push_back(n1);
                aux.push_back(n2);
                aux.push_back(n3);
                aux.push_back(n4);
                aux.push_back(n5);
                aux.push_back(n6);
                aux.push_back(n7);
                aux.push_back(n8);
                aux.push_back(n9);
                aux.push_back(n10);
                aux.push_back(n11);
                aux.push_back(n12);
                aux.push_back(n13);
                aux.push_back(n14);
                aux.push_back(n15);
                aux.push_back(n16);
            }
            
            indicesPatch.push_back(aux);
        }
        if(getline(f,line)) sscanf(line.c_str(),"%d\n",&vertices);
        for(int i=0; i<vertices ;i++){
            float x=0,y=0,z=0;
            if(getline(f,line)) sscanf(line.c_str(),"%f, %f, %f\n",&x,&y,&z);
  
            Point p;
            p.x = x; p.y = y; p.z = z;
            
            vertixs.push_back(p);
        }
        
        f.close();
    }
    else { printf("Error: Not possible acess patch file..."); exit(0); }
    
    //--- DESENHAR PATCHES ---//
    float res[3];
    float t;
    int index, indices[4];
    float q[4][tesselation][3],r[tesselation][tesselation][3],tess = 1/((float)tesselation-1);
    float pontos = patches*(tesselation)*2*(tesselation)*3*3;
    
    std::fstream g;
    g.open(savefilename,std::ios::out);
    
    if(g.is_open()){   //numero de pontos
        g << pontos; g << '\n';
        for(int n=0; n<patches; n++){
            //recolher os vértices do array vertixs para o x y e z
            float p[16][3];
            for(int m=0; m<16; m++){
                p[m][0] = vertixs[indicesPatch[n][m]].x;
                p[m][1] = vertixs[indicesPatch[n][m]].y;
                p[m][2] = vertixs[indicesPatch[n][m]].z;
            }
            int j=0,k=0;
            //desenhar as 4 curvas
            for(int i=0; i<15; i+=4){
                indices[0] = i;
                indices[1] = i+1;
                indices[2] = i+2;
                indices[3] = i+3;
                //calcular a curva
                for(int a=0; a<tesselation-1; a++){
                    t = a*tess;
                    index = floor(t);
                    t = t - index;
                    res[0] = (-p[indices[0]][0] +3*p[indices[1]][0] -3*p[indices[2]][0] +p[indices[3]][0])*t*t*t + (3*p[indices[0]][0] -6*p[indices[1]][0] +3*p[indices[2]][0])*t*t + (-3*p[indices[0]][0] +3*p[indices[1]][0])*t + p[indices[0]][0];
                    res[1] = (-p[indices[0]][1] +3*p[indices[1]][1] -3*p[indices[2]][1] +p[indices[3]][1])*t*t*t + (3*p[indices[0]][1] -6*p[indices[1]][1] +3*p[indices[2]][1])*t*t + (-3*p[indices[0]][1] +3*p[indices[1]][1])*t + p[indices[0]][1];
                    res[2] = (-p[indices[0]][2] +3*p[indices[1]][2] -3*p[indices[2]][2] +p[indices[3]][2])*t*t*t + (3*p[indices[0]][2] -6*p[indices[1]][2] +3*p[indices[2]][2])*t*t + (-3*p[indices[0]][2] +3*p[indices[1]][2])*t + p[indices[0]][2];
                    q[j][k][0] = res[0];
                    q[j][k][1] = res[1];
                    q[j][k][2] = res[2];
                    k++;
                }
                
                t = 1;
                
                res[0] = (-p[indices[0]][0] +3*p[indices[1]][0] -3*p[indices[2]][0] +p[indices[3]][0])*t*t*t + (3*p[indices[0]][0] -6*p[indices[1]][0] +3*p[indices[2]][0])*t*t + (-3*p[indices[0]][0] +3*p[indices[1]][0])*t + p[indices[0]][0];
                res[1] = (-p[indices[0]][1] +3*p[indices[1]][1] -3*p[indices[2]][1] +p[indices[3]][1])*t*t*t + (3*p[indices[0]][1] -6*p[indices[1]][1] +3*p[indices[2]][1])*t*t + (-3*p[indices[0]][1] +3*p[indices[1]][1])*t + p[indices[0]][1];
                res[2] = (-p[indices[0]][2] +3*p[indices[1]][2] -3*p[indices[2]][2] +p[indices[3]][2])*t*t*t + (3*p[indices[0]][2] -6*p[indices[1]][2] +3*p[indices[2]][2])*t*t + (-3*p[indices[0]][2] +3*p[indices[1]][2])*t + p[indices[0]][2];
                
                q[j][k][0] = res[0];
                q[j][k][1] = res[1];
                q[j][k][2] = res[2];
                j++;
                k=0;
            }
            
            for(int j=0; j<tesselation; j++){
                for(int a=0; a<tesselation-1; a++){
                    t = a*tess;;
                    index = floor(t);
                    t = t - index;
                    
                    res[0] = (-q[0][j][0] +3*q[1][j][0] -3*q[2][j][0] +q[3][j][0])*t*t*t + (3*q[0][j][0] -6*q[1][j][0] +3*q[2][j][0])*t*t + (-3*q[0][j][0] +3*q[1][j][0])*t + q[0][j][0];
                    res[1] = (-q[0][j][1] +3*q[1][j][1] -3*q[2][j][1] +q[3][j][1])*t*t*t + (3*q[0][j][1] -6*q[1][j][1] +3*q[2][j][1])*t*t + (-3*q[0][j][1] +3*q[1][j][1])*t + q[0][j][1];
                    res[2] = (-q[0][j][2] +3*q[1][j][2] -3*q[2][j][2] +q[3][j][2])*t*t*t + (3*q[0][j][2] -6*q[1][j][2] +3*q[2][j][2])*t*t + (-3*q[0][j][2] +3*q[1][j][2])*t + q[0][j][2];
                    r[j][k][0] = res[0];
                    r[j][k][1] = res[1];
                    r[j][k][2] = res[2];
                    k++;
                }
                
                t = 1;
                
                res[0] = (-q[0][j][0] +3*q[1][j][0] -3*q[2][j][0] +q[3][j][0])*t*t*t + (3*q[0][j][0] -6*q[1][j][0] +3*q[2][j][0])*t*t + (-3*q[0][j][0] +3*q[1][j][0])*t + q[0][j][0];
                res[1] = (-q[0][j][1] +3*q[1][j][1] -3*q[2][j][1] +q[3][j][1])*t*t*t + (3*q[0][j][1] -6*q[1][j][1] +3*q[2][j][1])*t*t + (-3*q[0][j][1] +3*q[1][j][1])*t + q[0][j][1];
                res[2] = (-q[0][j][2] +3*q[1][j][2] -3*q[2][j][2] +q[3][j][2])*t*t*t + (3*q[0][j][2] -6*q[1][j][2] +3*q[2][j][2])*t*t + (-3*q[0][j][2] +3*q[1][j][2])*t + q[0][j][2];
                
                r[j][k][0] = res[0];
                r[j][k][1] = res[1];
                r[j][k][2] = res[2];
                k=0;
            }
            
            for(int i=0; i<tesselation-1; i++)
                for(int j=0; j<tesselation-1; j++){
                    g << r[i][j][0];   g << ' '; g << r[i][j][1];   g << ' '; g << r[i][j][2];   g << '\n';
                    g << r[i+1][j][0]; g << ' '; g << r[i+1][j][1]; g << ' '; g <<r[i+1][j][2];  g << '\n';
                    g << r[i][j+1][0]; g << ' '; g << r[i][j+1][1]; g << ' '; g << r[i][j+1][2]; g << '\n';
                    
                    g << r[i+1][j][0];   g << ' '; g << r[i+1][j][1];   g << ' '; g << r[i+1][j][2];   g << '\n';
                    g << r[i+1][j+1][0]; g << ' '; g << r[i+1][j+1][1]; g << ' '; g << r[i+1][j+1][2]; g << '\n';
                    g << r[i][j+1][0];   g << ' '; g << r[i][j+1][1];   g << ' '; g << r[i][j+1][2];   g << '\n';
                }
        }
        g.close();
    }
    else { printf("Error: Cannot open file...\n"); exit(0); }
}

/*
	Function main of generator, that uses the outhers auxiliars functions define above
*/
int main(int argc , char* argv[]) {

  if(argc <=1) { 
  	printf("Missing Parameters...Please check your input...\n"); 
  } else{
  		if(!strcmp("plane",argv[1])){
  			if(argc != 5){
  				printf("Missing Parameters... \"plane <length> <height> <file_name>\n");
  				exit(0); 
  			} else{
  				float length = atof(argv[2]); 
  				float width = atof(argv[3]); 
  			
  				char* filename = (char*)malloc(sizeof(char)*64); 
  				filename = strdup(argv[4]);
  				filename = strcat(filename, argv[2]); 
  				filename = strcat(filename, argv[3]); 

  				//createXML(filename);  
  				drawPlane(length,width,filename); 
  			}
  		} else if (!strcmp("box",argv[1])){
  			if(argc != 6) { 
  				printf("Missing Parameters... \"box <length> <height> <width> <file_name>\n");
  				exit(0); 
  			} else {
  				float length = atof(argv[2]); 
  				float height = atof(argv[3]); 
  				float width = atof(argv[4]);  

  				char* filename = (char*)malloc(sizeof(char)*64); 
  				filename = strdup(argv[5]); 
  				filename = strcat(filename, argv[2]); 
  				filename = strcat(filename, argv[3]); 
  				filename = strcat(filename, argv[4]); 

  				//createXML(filename);  
  				drawBox(length,height,width,filename);
  			}
  		} else if (!strcmp("sphere",argv[1])){
  			if(argc != 6) { 
  				printf("Missing Parameters... \"sphere <radius> <slices> <stacks> <file_name>\n");
  				exit(0); 
  			} else{
  				float radius = atof(argv[2]); 
  				int slices = atoi(argv[3]); 
  				float stacks = atoi(argv[4]);

  				char* filename = (char*)malloc(sizeof(char)*64); 
  				filename = strdup(argv[5]); 
  				filename = strcat(filename, argv[2]); 
  				filename = strcat(filename, argv[3]); 
  				filename = strcat(filename, argv[4]); 

  				createXML(filename);  
  				drawSphere(radius, slices, stacks, filename);
  			}
  		}else if (!strcmp("cone",argv[1])){
			if(argc != 7) { 
				printf("Missing Parameters... \"cone <radius> <height> <slices> <stacks> <file_name>\n" );
				exit(0); 
			} else{
  				float radius = atof(argv[2]);
  				float height = atof(argv[3]);  
  				int slices = atoi(argv[4]); 
  				float stacks = atoi(argv[5]);  

  				char* filename = (char*)malloc(sizeof(char)*64); 
  				filename = strdup(argv[6]); 
  				filename = strcat(filename, argv[2]); 
  				filename = strcat(filename, argv[3]); 
  				filename = strcat(filename, argv[4]);
  				filename = strcat(filename, argv[5]); 

  				//createXML(filename);  
  				drawCone(radius, height,  slices, stacks, filename);
  			}
  		} else if (!strcmp("ring",argv[1])){
			if(argc!=6) { 
				printf("Missing Parameters... \"ring <interior_radius> <exterior_radius> <slices> <file_name>\n" );
				exit(0); 
			} else {
  				float in_r = atof(argv[2]) ;
  				float out_r = atof(argv[3]) ;  
  				int slices = atoi(argv[4]) ;  

  				char* filename = (char*)malloc(sizeof(char)*64) ; 
  				filename = strdup(argv[5]); 
  				filename = strcat(filename, argv[2]) ; 
  				filename = strcat(filename, argv[3]) ; 
  				filename = strcat(filename, argv[4]) ;
  			 
  			 	//createXML(filename); 
  				drawRing(in_r, out_r, slices , filename) ;
  			}
	  } else if (!strcmp(argv[1],"patch")){
        	if(argc!=5) { 
        		printf("Missing Parameters... \" Format: 'patch' <.patch> <tesselation> <file_name>\n"); 
        		exit(0); 
        	} else{
           	 	int tesselation = atoi(argv[3]);
            	drawPatch(argv[2],tesselation,argv[4]);
        	}
    } else{
  		printf("Please insert a valid figure... [plane, box, sphere, cone, ring, patch]\n");
  	}					
	}
	return 0;   
  }



