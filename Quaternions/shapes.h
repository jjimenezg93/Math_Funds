//
//  shapes.h
//  interpolation
//
//  Created by Jose Maria Benito on 28/10/14.
//  Copyright (c) 2014 Jose Maria. All rights reserved.
//

#ifndef interpolation_shapes_h
#define interpolation_shapes_h

#include "GLInclude.h"
#include <vector>


void drawDot(VECTOR3D position, float sradius = 1, COLOUR color = grey)
{
    glPushMatrix();
    glTranslatef(position.x, position.y, position.z);

    
    VECTOR3D p[4],n[4];
    int STEP = 30;
    for (int i=0;i<360;i+=STEP) {
        for (int j=-90;j<90;j+=STEP) {
            
            p[0].x = sradius * cos(j*DTOR) * cos(i*DTOR);
            p[0].y = sradius * sin(j*DTOR);
            p[0].z = sradius * cos(j*DTOR) * sin(i*DTOR);
            n[0] = p[0];
            
            p[1].x = sradius * cos((j+STEP)*DTOR) * cos(i*DTOR);
            p[1].y = sradius * sin((j+STEP)*DTOR);
            p[1].z = sradius * cos((j+STEP)*DTOR) * sin(i*DTOR);
            n[1] = p[1];
            
            p[2].x = sradius * cos((j+STEP)*DTOR) * cos((i+STEP)*DTOR);
            p[2].y = sradius * sin((j+STEP)*DTOR);
            p[2].z = sradius * cos((j+STEP)*DTOR) * sin((i+STEP)*DTOR);
            n[2] = p[2];
            
            p[3].x = sradius * cos(j*DTOR) * cos((i+STEP)*DTOR);
            p[3].y = sradius * sin(j*DTOR);
            p[3].z = sradius * cos(j*DTOR) * sin((i+STEP)*DTOR);
            n[3] = p[3];
            
            glBegin(GL_POLYGON);
            if (i % (STEP*4) == 0)
                glColor3f(color.r,color.g,color.b);
            else
                glColor3f(color.r*0.5,color.g*0.5,color.b*0.5);
            for (int k=0;k<4;k++) {
                glNormal3f(n[k].x,n[k].y,n[k].z);
                glVertex3f(p[k].x,p[k].y,p[k].z);
            }
            glEnd();
        }
    }
    
    glPopMatrix();
}

typedef struct {
    std::vector<VECTOR3D> P;
} LINE;


void drawLine(LINE line, COLOUR color = grey, bool doDrawDots = false)
{
	glColor3f(color.r, color.g, color.b);
	// usa GL_LINE_STRIP en modo inmediato (glBegin/glEnd)
	// enviar puntos a OpenGL usando glVertex3f
	std::vector<VECTOR3D>::iterator it = line.P.begin();
	glBegin(GL_LINE_STRIP);
	for (; it != line.P.end(); it++)
		glVertex3f((*it).x, (*it).y, (*it).z);
	glEnd();
}

void drawAxis()
{
	VECTOR3D vO;
	vO.x = 0;
	vO.y = 0;
	vO.z = 0;

	VECTOR3D vX;
	vX.x = 1;
	vX.y = 0;
	vX.z = 0;

	VECTOR3D vY;
	vY.x = 0;
	vY.y = 1;
	vY.z = 0;

	VECTOR3D vZ;
	vZ.x = 0;
	vZ.y = 0;
	vZ.z = -1;

	std::vector<VECTOR3D> stdX;
	stdX.push_back(vO);
	stdX.push_back(vX);

	std::vector<VECTOR3D> stdY;
	stdY.push_back(vO);
	stdY.push_back(vY);

	std::vector<VECTOR3D> stdZ;
	stdZ.push_back(vO);
	stdZ.push_back(vZ);

	LINE lineX;
	LINE lineY;
	LINE lineZ;
	lineX.P = stdX;
	lineY.P = stdY;
	lineZ.P = stdZ;
	drawLine(lineX, red);
	drawLine(lineY, green);
	drawLine(lineZ, blue);
}



#endif
