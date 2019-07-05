#include "estruturas.h"

#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "tinyxml/tinyxml.h"
#include "tinyxml/tinystr.h"


#define FILL 1 
#define LINE 2 
#define POINT 3

using namespace std;


Figure figure ; 

float angleAplha = 0.5 , angleBeta = 0.5 , radius = 10 ; 
float xOrigin = -1 ; 
float yOrigin = -1 ;  
float xr = 0;
float zr = 0;

int times , timebase , frame=0 , fps=0 ; 
char print[20] = "" ; 

void changeSize(int w, int h) {
	// --- Prevent a divide by zero, when window is too short --- //
    // (you cant make a window with zero width).
	if (h == 0) h = 1;

	// --- compute window's aspect ratio --- //
	float ratio = w * 1.0 / h;

	// --- Set the projection matrix as current --- //
	glMatrixMode(GL_PROJECTION);

	// --- Load Identity Matrix --- //
	glLoadIdentity();

	// --- Set the viewport to be the entire window --- //
	glViewport(0, 0, w, h);

	// --- Set perspective --- //
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// --- return to the model view matrix mode --- //
	glMatrixMode(GL_MODELVIEW);
}

// --- Draw Eliptic Orbit  --- //
void drawOrbit(float radiusX, float radiusZ, int nControl){
    float res[3];
    float p[nControl][3];
    float t;
    int index, indices[4];
    
    float doisPi = 2*M_PI, slice = doisPi/nControl;
    for(int i=0; i<nControl ; i++){
        p[i][0] = cos(i*slice)*radiusX;
        p[i][1] = 0;
        p[i][2] = sin(i*slice)*radiusZ;
    }
    glBegin(GL_LINE_LOOP);
    for(float a=0; a<1; a+=0.01){
        t = a*nControl;
        index = floor(t);
        t = t - index;
        
        indices[0] = (index + nControl-1)%nControl;
        indices[1] = (indices[0]+1)%nControl;
        indices[2] = (indices[1]+1)%nControl;
        indices[3] = (indices[2]+1)%nControl;
        
        res[0] = (-0.5*p[indices[0]][0] +1.5*p[indices[1]][0] -1.5*p[indices[2]][0] +0.5*p[indices[3]][0])*t*t*t + (p[indices[0]][0] -2.5*p[indices[1]][0] +2*p[indices[2]][0] -0.5*p[indices[3]][0])*t*t + (-0.5*p[indices[0]][0] +0.5*p[indices[2]][0])*t + p[indices[1]][0]; 
        res[1] = (-0.5*p[indices[0]][1] +1.5*p[indices[1]][1] -1.5*p[indices[2]][1] +0.5*p[indices[3]][1])*t*t*t + (p[indices[0]][1] -2.5*p[indices[1]][1] +2*p[indices[2]][1] -0.5*p[indices[3]][1])*t*t + (-0.5*p[indices[0]][1] +0.5*p[indices[2]][1])*t + p[indices[1]][1];
        res[2] = (-0.5*p[indices[0]][2] +1.5*p[indices[1]][2] -1.5*p[indices[2]][2] +0.5*p[indices[3]][2])*t*t*t + (p[indices[0]][2] -2.5*p[indices[1]][2] +2*p[indices[2]][2] -0.5*p[indices[3]][2])*t*t + (-0.5*p[indices[0]][2] +0.5*p[indices[2]][2])*t + p[indices[1]][2];
        
        glVertex3f(res[0],res[1],res[2]);
    }
    glEnd();
}

// --- Get a Rotation  --- //
void getRotation(float time , float axisx , float axisy , float axisz){
	float angle = 360/(time*1000);
	int t = glutGet(GLUT_ELAPSED_TIME);
	glRotatef(t*angle, axisx, axisy, axisz);
}

// --- Get a Translation --- //
void getTranslation(float time , list<Point> points){
	int nControl = (int) points.size();
	float res[3];
	float p[nControl][3];
	float t,a;
	int index, indices[4], i=0;

	for(list<Point>::iterator itp = points.begin() ; itp!=points.end() ; itp++){
		p[i][0] = itp->coordX ;
		p[i][1] = itp->coordY ;
		p[i][2] = itp->coordZ ;
		i++ ;  
	}

	float tempo = glutGet(GLUT_ELAPSED_TIME)%(int)(time*1000);
	a = tempo/(time*1000);

	t=a*nControl;
	index = floor(t);
	t=t-index;

	indices[0] = (index + nControl-1)%nControl;
	indices[1] = (indices[0]+1)%nControl;
	indices[2] = (indices[1]+1)%nControl;
	indices[3] = (indices[2]+1)%nControl;

	res[0] = (-0.5*p[indices[0]][0] +1.5*p[indices[1]][0] -1.5*p[indices[2]][0]
	 +0.5*p[indices[3]][0])*t*t*t + (p[indices[0]][0] -2.5*p[indices[1]][0]
	  +2*p[indices[2]][0] -0.5*p[indices[3]][0])*t*t + (-0.5*p[indices[0]][0] 
	  +0.5*p[indices[2]][0])*t + p[indices[1]][0];

	 res[1] = (-0.5*p[indices[0]][1] +1.5*p[indices[1]][1] -1.5*p[indices[2]][1] +0.5*p[indices[3]][1])*t*t*t 
	 + (p[indices[0]][1] -2.5*p[indices[1]][1] +2*p[indices[2]][1] -0.5*p[indices[3]][1])*t*t 
	 + (-0.5*p[indices[0]][1] +0.5*p[indices[2]][1])*t + p[indices[1]][1];
    
    res[2] = (-0.5*p[indices[0]][2] +1.5*p[indices[1]][2] -1.5*p[indices[2]][2]
     +0.5*p[indices[3]][2])*t*t*t + (p[indices[0]][2] -2.5*p[indices[1]][2] +2*p[indices[2]][2] -0.5*p[indices[3]][2])*t*t 
    + (-0.5*p[indices[0]][2] +0.5*p[indices[2]][2])*t + p[indices[1]][2];

    glTranslatef(res[0], res[1], res[2]);
}

void renderGroup(list<Group>::iterator g){
	// --- pushes original matrix orientation --- //
	glPushMatrix();

	if(!strcmp(g->type.c_str(),"orbit")){
        glRotatef(g->rotation.angle, g->rotation.axisX, g->rotation.axisY, g->rotation.axisZ);
        glTranslatef(g->translation.coordX, g->translation.coordY, g->translation.coordZ);
    }
    else{
        if(g->translation.time == -1) glTranslatef(g->translation.coordX, g->translation.coordY, g->translation.coordZ);
        	else getTranslation(g->translation.time,g->translation.points);
        
        if(g->rotation.time == -1) glRotatef(g->rotation.angle, g->rotation.axisX, g->rotation.axisY, g->rotation.axisZ);
        	else getRotation(g->rotation.time,g->rotation.axisX,g->rotation.axisY,g->rotation.axisZ);
    }
    
    glScalef(g->scale.scale_x, g->scale.scale_y, g->scale.scale_z);
    glColor3f(g->color.r,g->color.g,g->color.b);
    drawOrbit(g->orbit.radiusX,g->orbit.radiusZ , g->orbit.nControl);
    
    for(list<Model>::iterator itm = g->models.begin(); itm != g->models.end(); itm++){
   	    glBindBuffer(GL_ARRAY_BUFFER,itm->buffers[0]);
        glVertexPointer(3,GL_FLOAT,0,0);
        glDrawArrays(GL_TRIANGLES,0,itm->points);

    }
    for(list<Group>::iterator itg = g->groups.begin(); itg != g->groups.end(); itg++)
        renderGroup(itg);

    // --- returns to original matrix orientation --- //
	glPopMatrix();
}

// --- RenderScene --- //
void renderScene(void) {
	srand(0)  ; 

	// --- clear buffers --- //
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// --- set the camera --- //
	glLoadIdentity();
	gluLookAt(cos(angleBeta)*sin(angleAplha)*radius, sin(angleBeta)*radius, cos(angleBeta)*cos(angleAplha)*radius,
		0.0, 0.0, -1.0,
		0.0f, 1.0f, 0.0f);

	glTranslatef(xr, 0, zr);

	// put drawing instructions here
	for(list<Group>::iterator itg = figure.groups.begin(); itg != figure.groups.end(); itg++)
        renderGroup(itg);
    frame++ ; 
    times = glutGet(GLUT_ELAPSED_TIME) ; 
    
    if(times -timebase >1000){
    	fps = frame*1000.0/(times-timebase) ; 
    	timebase = times ; 
    	frame = 0 ; 
    }

    sprintf(print,"CG@DI-UM - Fase 3 - Grupo 14 <-> FPS: %d - Time: %d " , fps , times/1000) ;  	
    glutSetWindowTitle(print) ; 

    // --- End of frame --- //
	glutPostRedisplay() ; 
	glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y){
	switch(key){
        case 27: exit(0); 
        	     break;
		case('w') : radius -= 10; 
		             		break;
		case('W') : radius -= 10; 
		             		break;
		case('s') : radius += 10; 
		             		break;
		case('S') : radius += 10; 
		             		break;
		case('g'): xr=xr+1; 
		            		break;
		case('G'): xr=xr+1; 
		            		break;
		case('j'): xr=xr-1; 
		            		break;
		case('J'): xr=xr-1; 
		            		break;
		case('y'): zr=zr-1; 
		           			break;
		case('Y'): zr=zr-1; 
		           			break;
		case('h'): zr=zr+1; 
		           			break;
		case('H'): zr=zr+1; 
		           			break;

    }
    // --- Every time we press a key --- //
    glutPostRedisplay();  
}

void processSpecialKeys(int key, int x1, int y1){
	switch (key){
		case GLUT_KEY_LEFT : angleAplha -= 0.1; 
							 break;
		case GLUT_KEY_RIGHT : angleAplha += 0.1; 
							  break;
		case GLUT_KEY_UP : if(angleBeta < M_PI/2) angleBeta += 0.1; 
						   break;
		case GLUT_KEY_DOWN : if(angleBeta > -M_PI/2) angleBeta -= 0.1; 
						     break;
	}

}

void mouseButton(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON){
        if(state == GLUT_UP) { xOrigin = -1; yOrigin = -1; }
		else { xOrigin = x; yOrigin = y; }
	}
}

void mouseMove(int x, int y){
	if(xOrigin >= 0){
        angleAplha = (x + xOrigin) * 0.01;
        if(angleBeta < M_PI/2) angleBeta = (y - yOrigin) * 0.01;
        if(angleBeta > -M_PI/2) angleBeta = (y - yOrigin) * 0.01;
    }
    glutPostRedisplay();
}

void processFillMenu(int option){
	switch (option){
		case FILL: glPolygonMode(GL_FRONT, GL_FILL); break;
		case LINE: glPolygonMode(GL_FRONT, GL_LINE); break;
        case POINT: glPolygonMode(GL_FRONT, GL_POINT); break;
	}
}

void createGLUTMenus(){
    int menu;
    menu = glutCreateMenu(processFillMenu);
    
    glutAddMenuEntry("Fill",FILL);
	glutAddMenuEntry("Line",LINE);
    glutAddMenuEntry("Point",POINT);
    
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}


int main(int argc, char **argv) {
	
	// put GLUT init here
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(400, 100);
	glutInitWindowSize(1200, 800);
	glutCreateWindow("CG@DI-UM - Fase 3 - Grupo 14");

	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

	// put callback registration here

	glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);
    glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);


	createGLUTMenus();
	glewInit();

	figure.load(argv[1]);

	// OpenGL settings 
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// enter GLUT's main loop
	glutMainLoop();

	return 0;
}
