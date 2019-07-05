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


Figura figura;

//angçes and radius
float angleAlpha = 0.5 , angleBeta = 0.5 , radius = 10 ;
//Rotate variables
float xOrigin = -1 ;
float yOrigin = -1 ;
float lx = 0.0f;
float lz = 0.0f;
float ly = 0.0f;
float rx = 0.0f;
float rz = 0.0f;
float ry = 0.0f;

void changeSize(int w, int h) {
    
    // Prevent a divide by zero, when window is too short
    // (you cant make a window with zero width).
    if(h == 0)
    h = 1;
    
    // compute window's aspect ratio
    float ratio = w * 1.0 / h;
    
    // Set the projection matrix as current
    glMatrixMode(GL_PROJECTION);
    // Load Identity Matrix
    glLoadIdentity();
    
    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);
    
    // Set perspective
    gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);
    
    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
    
    
}


//Função que gera floats aleatorios
float RandomFloat(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

void renderScene(void)
{
    srand(0)  ;
    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // set the camera
    glLoadIdentity();
    gluLookAt(cos(angleBeta)*sin(angleAlpha)*radius, sin(angleBeta)*radius, cos(angleBeta)*cos(angleAlpha)*radius,
              0.0, 0.0, -1.0,
              0.0f, 1.0f, 0.0f);
    
    // put drawing instructions here
    
    glTranslatef(lx, ly, lz);
    glScalef(1+rx, 1+ry, 1+rz);
    
    glBegin(GL_TRIANGLES) ; // where we design the triangles acording to the sepecifications we were given
    for(list<Modelo>::iterator it = figura.modelos.begin(); it != figura.modelos.end() ; it++){
        for(list<Ponto>::iterator it2 = it->pontos.begin() ; it2!=it->pontos.end(); it2++){
            // random floats to generate triangle colours
            float r , g , b ;
            r = RandomFloat(0,1);
            g = RandomFloat(0,1);
            b = RandomFloat(0,1);
            glColor3f(r, g, b);
            glVertex3f(it2->coordx,it2->coordy , it2->coordz) ;
            
        }
    }
    
    glEnd() ;
    
    // End of frame
    glutPostRedisplay() ;
    glutSwapBuffers();
}

//Funcionalidades para os rotates
void normal_keys(unsigned char key, int x, int y){
    switch(key){
        case 's':
        lz += 0.2f;
        break;
        case 'w':
        lz -= 0.2f;
        break;
        case 'd':
        lx += 0.2f;
        break;
        case 'a':
        lx -= 0.2f;
        break;
        case 'u':
        ly += 0.2f;
        break;
        case 'i':
        ly -= 0.2f;
        break;
        case 'r':
        ry -= 0.2f; rx -= 0.2f; rz -= 0.2f;
        break;
        case 'g':
        ry += 0.2f;rx += 0.2f; rz += 0.2f;
        break;
    }  glutPostRedisplay();
    
}


//Função que permite mover o objeto para cima/baixo, esquerda/direita
void keyboard_movement(int key_code, int x1, int y1){
    switch (key_code){
        case GLUT_KEY_LEFT :
        angleAlpha -= 0.1;
        break;
        case GLUT_KEY_RIGHT :
        angleAlpha += 0.1;
        break;
        case GLUT_KEY_UP :
        if(angleBeta < M_PI/2)
        angleBeta += 0.1;
        break;
        case GLUT_KEY_DOWN :
        if(angleBeta > -M_PI/2)
        angleBeta -= 0.1;
        break;
    }
    glutPostRedisplay();
}

//Função que permite selecionar o objeto através do touchpad
void mouseButton(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON){
        if(state == GLUT_UP) { xOrigin = -1; yOrigin = -1; }
        else { xOrigin = x; yOrigin = y; }
    }
}

//Função que permite mexer na camera através do touchpad
void mouseMove(int x, int y){
    
    if(xOrigin >= 0){
        angleAlpha = (x + xOrigin) * 0.01;
        if( angleBeta < M_PI/2) angleBeta = (y - yOrigin) * 0.01;
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
    
    figura.load(argv[1]) ;
    
    // put GLUT init here
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);// devemos por isso para garantir que o comportamento e o mesmo em todas as maquinas --  define propriedades da janela
    glutInitWindowPosition(400, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("CG@DI-UM - Fase 1 - Grupo 14");
    
    // glutDisplayFunc(<#void (*func)()#>);
    glutDisplayFunc(renderScene);
    // glutReshapeFunc(<#void (*func)(int, int)#>); // permite determinar o que acontece a medida que mexemos na medida de janela (aparece uma vez no arranque)
    glutReshapeFunc(changeSize);
    
    
    glutKeyboardFunc(normal_keys);
    glutSpecialFunc(keyboard_movement);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);
    
    
    createGLUTMenus();
    
    // some OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    
    // enter GLUT's main loop
    glutMainLoop();
    
    return 1 ;// 0?;
}
