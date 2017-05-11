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

	/*Dirección del lapiz.*/
	GLdouble dir;

public:

	/*Constructoras.*/

	/*Constructora por defecto del lápiz.*/
	Lapiz() {
		this->pos = new PV2D(0, 0);
		this->dir = 0;
	}

	/*Constructora del lápiz pasándole las coordenadas de inicio y la dirección.*/
	Lapiz(GLfloat x, GLfloat y, GLdouble dir) {
		this->pos = new PV2D(100, 100);
		this->dir = toRadian(dir);
	}

	/*Constructora del lápiz pasándole las coordenadas de inicio y la dirección.*/
	Lapiz(PV2D*p, GLdouble dir) {
		this->pos = p->clona();
		this->dir = toRadian(dir);
	}

	


	/*Métodos de la clase lápiz.*/

	/*Mueve la posición del lápiz hasta otro punto y si draw es true dibuja.*/
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

	/*Mueve la posición del lápiz hasta otro punto y si draw es true dibuja.*/
	void moveTo(PV2D* p, GLboolean draw) {
		if (draw) {
			glBegin(GL_LINES);
			glVertex2d(this->pos->getX(), this->pos->getY());
			glVertex2d(p->getX(), p->getY());
			glEnd();
		}
		this->pos = p->clona();
	}

	/*Cambia la dirección del lápiz.*/
	void turnTo(GLdouble a) {
		this->dir += toRadian(a);
	}

	/*Mueve la posición del lápiz hacia la dirección de dir y si draw es true dibuja.*/
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

	/*Mueve la posición del lápiz hacia la dirección de dir y si draw es true dibuja.*/
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

	/*Devuelve la posición del lápiz.*/
	PV2D* getPos() {
		return new PV2D(this->pos->getX(), this->pos->getY());
	}

	/*Devuelve la dirección del lápiz.*/
	GLdouble getDir() {
		return this->dir;
	}




	/*Setters.*/

	/*Establece una dirección para el lápiz.*/
	void setDir(GLdouble dir) {
		this->dir = toRadian(dir);
	}




	/*Destructras.*/

	/*Destructora de la clase lápiz.*/
	~Lapiz() {
		delete pos;
	}
};


#endif