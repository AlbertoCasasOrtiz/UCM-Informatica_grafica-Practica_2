#ifndef PV3D_H
#define PV3D_H

#include <gl/GL.h>
#include <math.h>

class PV3D {
private:
	/*Coordenadas del punto.*/
	GLfloat x, y, z;

	/*Indica si es punto o vector.*/
	GLint pv;

	/*Eleva el número al cuadrado.*/
	GLfloat pow2(GLfloat num) {
		return (GLfloat)pow(num, 2);
	}

	/*Eleva un número a otro número n dado.*/
	GLfloat pown(GLfloat num, GLint n) {
		return (GLfloat)pow(num, 1.0f / n);
	}

public:
	/*Constructora de la clase PV3D.*/
	PV3D(GLfloat x, GLfloat y, GLfloat z, GLint pv){
		this->x = x;
		this->y = y;
		this->z = z;
		this->pv = pv;
	}


	/*Métodos de la clase*/

	/*Calcula el producto vectorial entre este vector y otro.*/
	PV3D* productoVectorial(PV3D *v) {
		GLfloat i = this->getY()*v->getZ()-v->getY()*this->getZ();
		GLfloat j = -(this->getX()*v->getZ()-this->getZ()*v->getX());
		GLfloat k = this->getX()*v->getY()-this->getY()*v->getX();
		return new PV3D(i, j, k, 0);
	}

	/*Calcula el modulo de un vector.*/
	GLfloat modulo(PV3D* v) {
		return pown((pow2(v->getX()) + pow2(v->getY()) + pow2(v->getZ())), 2);
	}

	/*Calcula el producto escalar de dos vectores.*/
	GLfloat productoEscalar(PV3D* v) {
		return this->x*v->getX() + this->y*v->getY() + this->z*v->getZ();
	}

	/*Normaliza los parámetros del vector dado.*/
	void normaliza() {
		PV3D *res = new PV3D(0.0, 0.0, 0.0, 0);
		GLfloat modV = modulo(this);
		this->setX(x / modV);
		this->setY(y / modV);
		this->setZ(z / modV);
	}

	/*Devuelve un clon de este PV3D.*/
	PV3D* clona() {
		return new PV3D(this->getX(), this->getY(), this->getZ(), this->pv);
	}

	/*Devuelve el punto medio entre este punto y uno dado.*/
	PV3D *puntoMedio(PV3D* puntoAux) {
		int x = (this->getX() + puntoAux->getY()) / 2;
		int y = (this->getY() + puntoAux->getY()) / 2;
		int z = (this->getZ() + puntoAux->getZ()) / 2;
		return new PV3D(x, y, z, 1);
	}

	/*Devuelve la longitud de la recta que hay entre este punto y uno dado.*/
	GLfloat longitud(PV3D* puntoAux) {
		return sqrtf(pow(this->getX() - puntoAux->getX(), 2) + pow(this->getY() - puntoAux->getY(), 2) + pow(this->getZ() - puntoAux->getZ(), 2));
	}


	/*Getters*/

	/*Devuelve las componentes del PV3D dependiendo del i que insertes.*/
	GLfloat get(GLint i) {
		switch (i) {
		case 0:
			return this->x;
		case 1:
			return this->y;
		case 2:
			return this->z;
		case 3:
			return this->pv;
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

	/*Devuelve el valor x del punto.*/
	GLfloat getZ() {
		return this->z;
	}

	/*Devuelve 1 si es un vector y 0 si es un punto.*/
	GLint isVectorOrNormal(){
		return this->pv;
	}


	/*Setters*/

	/*Establece las componentes del PV3D dependiendo del i que insertes.*/
	void set(GLint i, GLfloat value) {
		switch (i) {
		case 0:
			this->x = value;
		case 1:
			this->y = value;
		case 2:
			this->z = value;
		case 3:
			this->pv = value;
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

	/*Establece el valor x del punto.*/
	void setZ(GLfloat z) {
		this->z = z;
	}

};

#endif