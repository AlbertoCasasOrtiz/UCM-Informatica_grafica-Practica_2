#ifndef MATRIX_H
#define MATRIX_H

#include <gl/GL.h>
#include <math.h>
#include "PV3D.h"

class SquareMatrix {
private:
	/*Matriz representada como un array de arrays.*/
	GLfloat **matrix;
	PV3D *v1, *v2, *v3, *v4;

	/*Tamaño de la matriz.*/
	const GLint TAM = 4;
public:

	SquareMatrix() {
		/*Inicialización de las variables.*/
		this->matrix = new GLfloat*[TAM];
		for (GLint i = 0; i < TAM; i++) {
			this->matrix[i] = new GLfloat[TAM];
		}
		this->v1 = new PV3D(0, 0, 0, 0);
		this->v2 = new PV3D(0, 0, 0, 0);
		this->v3 = new PV3D(0, 0, 0, 0);
		this->v4 = new PV3D(0, 0, 0, 1);

		/*Inserción de las variables en la matrix.*/
		this->matrix[0][0] = 0;
		this->matrix[1][0] = 0;
		this->matrix[2][0] = 0;
		this->matrix[3][0] = 0;
		this->matrix[0][1] = 0;
		this->matrix[1][1] = 0;
		this->matrix[2][1] = 0;
		this->matrix[3][1] = 0;
		this->matrix[0][2] = 0;
		this->matrix[1][2] = 0;
		this->matrix[2][2] = 0;
		this->matrix[3][2] = 0;
		this->matrix[0][3] = 0;
		this->matrix[1][3] = 0;
		this->matrix[2][3] = 0;
		this->matrix[3][3] = 0;
	}

	/*Crea una matriz a partir de los puntos y vectores dados.*/
	SquareMatrix(PV3D* v1, PV3D* v2, PV3D *v3, PV3D *v4) {
		/*Inicialización de las variables.*/
		this->matrix = new GLfloat*[TAM];
		for (GLint i = 0; i < TAM; i++) {
			this->matrix[i] = new GLfloat[TAM];
		}
		this->v1 = v1->clona();
		this->v2 = v2->clona();
		this->v3 = v3->clona();
		this->v4 = v4->clona();

		/*Inserción de las variables en la matrix.*/
		this->matrix[0][0] = v1->getX();
		this->matrix[1][0] = v1->getY();
		this->matrix[2][0] = v1->getZ();
		this->matrix[3][0] = v1->isVectorOrNormal();
		this->matrix[0][1] = v2->getX();
		this->matrix[1][1] = v2->getY();
		this->matrix[2][1] = v2->getZ();
		this->matrix[3][1] = v2->isVectorOrNormal();
		this->matrix[0][2] = v3->getX();
		this->matrix[1][2] = v3->getY();
		this->matrix[2][2] = v3->getZ();
		this->matrix[3][2] = v3->isVectorOrNormal();
		this->matrix[0][3] = v4->getX();
		this->matrix[1][3] = v4->getY();
		this->matrix[2][3] = v4->getZ();
		this->matrix[3][3] = v4->isVectorOrNormal();
	}

	/*Destructora de la clase SquareMatrix.*/
	~SquareMatrix() {
		for (GLint i = 0; i < this->TAM; i++) {
			delete this->matrix[i];
		}
		delete this->matrix;
	}

	/*Métodos de la clase.*/

	/*Multiplica esta matriz por un punto.*/
	PV3D* multiplica(PV3D* p) {
		PV3D * res = new PV3D(0, 0, 0, 0);
		GLfloat value;
		for (GLint i = 0; i < TAM; i++) {
			value = 0;
			for (GLint j = 0; j < TAM; j++) {
				value += this->matrix[i][j] * p->get(j);
			}
			res->set(i, value);
		}
		return res;
	}

	SquareMatrix *inversa() {
		v4 = new PV3D(v4->getX(), v4->getY(), v4->getZ(), 0);
		SquareMatrix* matrixInv = new SquareMatrix();
		matrixInv->setElem(0, 0, this->matrix[0][0]);
		matrixInv->setElem(1, 0, this->matrix[0][1]);
		matrixInv->setElem(2, 0, this->matrix[0][2]);
		matrixInv->setElem(3, 0, 0);
		matrixInv->setElem(0, 1, this->matrix[1][0]);
		matrixInv->setElem(1, 1, this->matrix[1][1]);
		matrixInv->setElem(2, 1, this->matrix[1][2]);
		matrixInv->setElem(3, 1, 0);
		matrixInv->setElem(0, 2, this->matrix[2][0]);
		matrixInv->setElem(1, 2, this->matrix[2][1]);
		matrixInv->setElem(2, 2, this->matrix[2][2]);
		matrixInv->setElem(3, 2, 0);
		matrixInv->setElem(0, 3, -v4->productoEscalar(v1));
		matrixInv->setElem(1, 3, -v4->productoEscalar(v2));
		matrixInv->setElem(2, 3, -v4->productoEscalar(v3));
		matrixInv->setElem(3, 3, 1);
		return matrixInv;
	}

	GLfloat getElem(GLint x, GLint y) {
		return this->matrix[x][y];
	}

	void setElem(GLint x, GLint y, GLfloat elem) {
		this->matrix[x][y] = elem;
	}

	GLfloat* getVector() {
		GLfloat *vector = new GLfloat[16];
		GLint cont = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				vector[cont] = getElem(j, i);
				cont++;
			}
		}
		return vector;
	}
};


#endif