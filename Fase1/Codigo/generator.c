#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

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
	Function main of generator, that uses the outhers auxiliars functions define above
*/
int main(int argc , char* argv[]) {

  if(argc <=1) { 
  	printf("Missing Parameters...Please check your input...\n"); 
  } else{
  		if(!strcmp("plane",argv[1])){
  			if(argc != 5){
  				printf("Missing Parameters... \"plane <length> <height> <file_name>\n");
  			} else{
  				float length = atof(argv[2]); 
  				float width = atof(argv[3]); 
  			
  				char* filename = (char*)malloc(sizeof(char)*64); 
  				filename = strdup(argv[4]);
  				filename = strcat(filename, argv[2]); 
  				filename = strcat(filename, argv[3]); 
  				createXML(filename);  
  				drawPlane(length,width,filename); 
  			}
  		} else if (!strcmp("box",argv[1])){
  			if(argc != 6) { 
  				printf("Missing Parameters... \"box <length> <height> <width> <file_name>\n");
  			} else {
  				float length = atof(argv[2]); 
  				float height = atof(argv[3]); 
  				float width = atof(argv[4]);  

  				char* filename = (char*)malloc(sizeof(char)*64); 
  				filename = strdup(argv[5]); 
  				filename = strcat(filename, argv[2]); 
  				filename = strcat(filename, argv[3]); 
  				filename = strcat(filename, argv[4]); 

  				createXML(filename);  
  				drawBox(length,height,width,filename);
  			}
  		} else if (!strcmp("sphere",argv[1])){
  			if(argc != 6) { 
  				printf("Missing Parameters... \"sphere <radius> <slices> <stacks> <file_name>\n");
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

  				createXML(filename);  
  				drawCone(radius, height,  slices, stacks, filename);
  			}
  		} else{
  			printf("Please insert a valid figure... [plane, box, sphere, cone]\n");
  		}					
 	}

	return 0;   
  }



