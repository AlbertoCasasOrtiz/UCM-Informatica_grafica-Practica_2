#ifndef PV2D_H
#define PV2D_H

#include<GL\GL.h>
#include <math.h>
#include <GL/freeglut.h>
#include "Color.h"

class PV2D {
private:
	/*Coordenadas del punto.*/
	GLfloat x, y;

public:

	/*Constructoras.*/

	/*Constructora de la clase PV2D.*/
	PV2D(GLfloat x, GLfloat y) {
		this->x = x;
		this->y = y;
	}




	/*Métodos de la clase.*/

	/*Devuelve un clon de este PV3D.*/
	PV2D* clona() {
		return new PV2D(this->getX(), this->getY());
	}

	/*Devuelve la distancia entre este punto y otro dado.*/
	GLfloat distancia(PV2D * punto){
		return sqrt(pow((punto->getX() - this->x), 2) + pow((punto->getY() - this->y), 2));
	}

	PV2D * sumaPunto(PV2D * punto) {
		return new PV2D(this->getX()+punto->getX(), this->getY()+punto->getY());
	}

	PV2D * multiplicaEscalar(GLfloat e) {
		return new PV2D(this->getX()*e, this->getY()*e);
	}

	PV2D * divideEscalar(GLfloat e) {
		return new PV2D(this->getX()/e, this->getY()/e);
	}

	/*Método que dibuja el punto.*/
	void dibuja(Color *color) {
		glColor3f(color->getR(), color->getG(), color->getB());
		glBegin(GL_POINTS);
		glVertex2d(this->x, this->y);
		glEnd();
	}




	/*Getters.*/

	/*Devuelve las componentes del PV3D dependiendo del i que insertes.*/
	GLfloat get(GLint i) {
		switch (i) {
		case 0:
			return this->x;
		case 1:
			return this->y;
		default:
			return -0;
		}
	}

	/*Devuelve el valor x del punto.*/
	GLfloat getX() {
		return this->x;
	}

	/*Devuelve el valor y del punto.*/
	GLfloat getY() {
		return this->y;
	}




	/*Setters*/

	/*Establece las componentes del PV3D dependiendo del i que insertes.*/
	void set(GLint i, GLfloat value) {
		switch (i) {
		case 0:
			this->x = value;
			break;
		case 1:
			this->y = value;
			break;
		}
	}

	/*Establece el valor x del punto.*/
	void setX(GLfloat x) {
		this->x = x;
	}

	/*Establece el valor y del punto.*/
	void setY(GLfloat y) {
		this->y = y;
	}


};


#endif