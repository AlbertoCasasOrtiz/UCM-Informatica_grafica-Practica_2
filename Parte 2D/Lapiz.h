#ifndef LAPIZ_H
#define LAPIZ_H

#include<GL\GL.h>
#include"PV2D.h"
#include<math.h>
#include "constant.h"
#include "Color.h"

class Lapiz {
private:
	/*Coordnadas del punto.*/
	PV2D*pos;

	/*Direcci�n del lapiz.*/
	GLdouble dir;

public:

	/*Constructoras.*/

	/*Constructora por defecto del l�piz.*/
	Lapiz() {
		this->pos = new PV2D(0, 0);
		this->dir = 0;
	}

	/*Constructora del l�piz pas�ndole las coordenadas de inicio y la direcci�n.*/
	Lapiz(GLfloat x, GLfloat y, GLdouble dir) {
		this->pos = new PV2D(100, 100);
		this->dir = toRadian(dir);
	}

	/*Constructora del l�piz pas�ndole las coordenadas de inicio y la direcci�n.*/
	Lapiz(PV2D*p, GLdouble dir) {
		this->pos = p->clona();
		this->dir = toRadian(dir);
	}

	


	/*M�todos de la clase l�piz.*/

	/*Mueve la posici�n del l�piz hasta otro punto y si draw es true dibuja.*/
	void moveTo(PV2D* p, GLboolean draw, Color *color) {
		if (draw) {
			glColor3f(color->getR(), color->getG(), color->getB());
			glBegin(GL_LINES);
				glVertex2d(this->pos->getX(), this->pos->getY());
				glVertex2d(p->getX(), p->getY());
			glEnd();
		}
		this->pos = p->clona();
	}

	/*Mueve la posici�n del l�piz hasta otro punto y si draw es true dibuja.*/
	void moveTo(PV2D* p, GLboolean draw) {
		if (draw) {
			glBegin(GL_LINES);
			glVertex2d(this->pos->getX(), this->pos->getY());
			glVertex2d(p->getX(), p->getY());
			glEnd();
		}
		this->pos = p->clona();
	}

	/*Cambia la direcci�n del l�piz.*/
	void turnTo(GLdouble a) {
		this->dir += toRadian(a);
	}

	/*Mueve la posici�n del l�piz hacia la direcci�n de dir y si draw es true dibuja.*/
	void forward(GLdouble dist, bool draw, Color *color) {
		GLfloat newX = this->pos->getX() + dist*cos(dir);
		GLfloat newY = this->pos->getY() + dist*sin(dir);
		if (draw) {
			glColor3f(color->getR(), color->getG(), color->getB());
			glBegin(GL_LINES);
				glVertex2d(this->pos->getX(), this->pos->getY());
				glVertex2d(newX, newY);
			glEnd();
		}
		this->pos = new PV2D(newX, newY);
	}

	/*Mueve la posici�n del l�piz hacia la direcci�n de dir y si draw es true dibuja.*/
	void forward(GLdouble dist, bool draw) {
		GLfloat newX = this->pos->getX() + dist*cos(dir);
		GLfloat newY = this->pos->getY() + dist*sin(dir);
		if (draw) {
			glBegin(GL_LINES);
			glVertex2d(this->pos->getX(), this->pos->getY());
			glVertex2d(newX, newY);
			glEnd();
		}
		this->pos = new PV2D(newX, newY);
	}




	/*Getters.*/

	/*Devuelve la posici�n del l�piz.*/
	PV2D* getPos() {
		return new PV2D(this->pos->getX(), this->pos->getY());
	}

	/*Devuelve la direcci�n del l�piz.*/
	GLdouble getDir() {
		return this->dir;
	}




	/*Setters.*/

	/*Establece una direcci�n para el l�piz.*/
	void setDir(GLdouble dir) {
		this->dir = toRadian(dir);
	}




	/*Destructras.*/

	/*Destructora de la clase l�piz.*/
	~Lapiz() {
		delete pos;
	}
};


#endif