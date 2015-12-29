    //
//  main.cpp
//  StereoRendering
//
//  Created by Jose Maria Benito on 02/12/13.
//  Copyright (c) 2013 Jose Maria. All rights reserved.
//

#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "GLInclude.h"
#include "math3d.h"
#include "camera.h"
#include "shapes.h"

void Display(void);
void Init(void);
void Render(void);
void Lighting(void);
void InitCamera(int);
void HandleKeyboard(unsigned char key,int x, int y);
void HandleReshape(int,int);
void HandleIdle(void);

int fullscreen = FALSE;

int currentbutton = -1;
double rotatespeed = 3;
double tSpeed = 0.05;
float t = 0;

CAMERA camera;
FRUSTUM centerFrustum;


double rotateangle = 0;

int main(int argc,char **argv)
{
    camera.screenwidth = 600;
    camera.screenheight = 400;

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutCreateWindow("Stereo Rendering");
    if (fullscreen)
        glutFullScreen();
    glutDisplayFunc( Display);
    glutReshapeFunc(HandleReshape);
    glutReshapeWindow(camera.screenwidth,camera.screenheight);
    glutIdleFunc(HandleIdle);
    glutKeyboardFunc(HandleKeyboard);
    Init();
    InitCamera(0);
    Lighting();
	
    glutMainLoop();
    return(0);
}

void Init(void)
{
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_POINT_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glShadeModel(GL_SMOOTH);
    glDisable(GL_DITHER);
    glDisable(GL_CULL_FACE);
    
    glLineWidth(1.0);
    glPointSize(1.0);
    
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glFrontFace(GL_CW);
    glClearColor(0.0,0.0,0.0,0.0);         /* Background colour */
    glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
}

void Display(void)
{
    glDrawBuffer(GL_BACK_LEFT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    
    glDrawBuffer(GL_BACK);
    
    double near=0.1,far=10000;
    
    double aspectRatio  = camera.screenwidth / (double)camera.screenheight;
    FRUSTUM centerFrustum = makeFrustum(camera.aperture, aspectRatio, near, far);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(centerFrustum.left, centerFrustum.right, centerFrustum.bottom, centerFrustum.top, centerFrustum.near, centerFrustum.far);
    
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();
    VECTOR3D target = Add(camera.position, camera.direction);
   //gluLookAt(camera.position.x,camera.position.y,camera.position.z, target.x , target.y, target.z, camera.up.x,camera.up.y,camera.up.z);

    // TODO
	//camera 0,0,0
	//target 0,0,-1
	/*VECTOR3D myCam = { 0, 0, -1 };
	VECTOR3D myTarg = { 0, 0, 0 };
	MATRIX4 lookAtMatrix = lookAt(myCam, myTarg, camera.up);*/
	MATRIX4 lookAtMatrix = lookAt(camera.position, target, camera.up);
    glLoadMatrixf(lookAtMatrix.m);

    glViewport(0,0,camera.screenwidth,camera.screenheight);
    
    Render();
    
    glutSwapBuffers();
}


void Render(void)
{
    GLfloat specular[4] = {1.0,1.0,1.0,1.0};
    GLfloat shiny[1] = {5.0};
    
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,specular);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
    
    glPushMatrix();
    glRotatef(rotateangle,0.0,1.0,0.0);

    drawAxis();
    
    // add
    {
        VECTOR3D a = {3,2,0};
        VECTOR3D b = {2,1,0};
        
        drawDot(a,0.25, green);
        drawDot(b,0.25, red);
        
        VECTOR3D p = Add(a,b);
        drawDot(p, 0.25);
    }
    
    // substract
//    {
//        VECTOR3D a = {3,2,0};
//        VECTOR3D b = {2,1,0};
//        
//        drawDot(a,0.25, green);
//        drawDot(b,0.25, red);
//        
//        VECTOR3D p = Substract(a,b);
//        drawDot(p, 0.25);
//    }

    // multiply
//    {
//        VECTOR3D a = {3,2,0};
//        VECTOR3D b = {1,0.5,1};
//        
//        drawDot(a,0.25, green);
//        drawDot(b,0.25, red);
//        
//        VECTOR3D p = Multiply(a,b);
//        drawDot(p, 0.25);
//    }
    
//    // magnitude
//    {
//        VECTOR3D a = {3,2,0};
//        VECTOR3D b = {2,2,0};
//
//        drawDot(a,0.25, green);
//        drawDot(b,0.25, red);
//
//        VECTOR3D p = Substract(a,b);
//        drawDot(p, 0.25);
//        
//        double magnitudeOfP = Magnitude(p);
//        printf("magnitude: %f\n", magnitudeOfP);
//    }
    
    // normalize
//    {
//        VECTOR3D a = {2,3,0};
//        VECTOR3D b = Normalize(a);
//        drawDot(a,0.25, red);
//        drawDot(b,0.25, darkred);
//    }
    
    glPopMatrix();
}

void Lighting(void)
{
    GLfloat fullambient[4] = {1.0,1.0,1.0,1.0};
    GLfloat position[4] = {0.0,0.0,0.0,0.0};
    GLfloat ambient[4]  = {0.2,0.2,0.2,1.0};
    GLfloat diffuse[4]  = {1.0,1.0,1.0,1.0};
    GLfloat specular[4] = {0.0,0.0,0.0,1.0};
    
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHT1);
    glDisable(GL_LIGHT2);
    glDisable(GL_LIGHT3);
    glDisable(GL_LIGHT4);
    glDisable(GL_LIGHT5);
    glDisable(GL_LIGHT6);
    glDisable(GL_LIGHT7);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_FALSE);
    
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,fullambient);
    glLightfv(GL_LIGHT0,GL_POSITION,position);
    glLightfv(GL_LIGHT0,GL_AMBIENT,ambient);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuse);
    glLightfv(GL_LIGHT0,GL_SPECULAR,specular);
    glEnable(GL_LIGHT0);
    
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
}

void HandleKeyboard(unsigned char key,int x, int y)
{
    switch (key) {
        case ESC:
        case 'Q':
        case 'q':
            exit(0);
            break;
        case 'R':
        case 'r':
            rotateangle += rotatespeed;
            break;
            
        case '+':
            t += tSpeed;
            t = t > 1 ? 1:t;
            break;

        case '-':
            t -= tSpeed;
            t = t <0 ? 0:t;
            break;

        case 'h':
        case 'H':
            InitCamera(0);
            break;
    }
}

void HandleIdle(void)
{
//    rotateangle += rotatespeed;
    glutPostRedisplay();
}

void HandleReshape(int w,int h)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    camera.screenwidth = w;
    camera.screenheight = h;
}


void InitCamera(int mode)
{
    camera.aperture = 45;

    camera.position.x = 0;
    camera.position.y = 0;
    camera.position.z = 20;
    
    camera.direction.x = -camera.position.x;
    camera.direction.y = -camera.position.y;
    camera.direction.z = -camera.position.z;
    
    camera.up.x = 0;
    camera.up.y = 1;
    camera.up.z = 0;
}

