#ifndef CARA_H
#define CARA_H

#include "VerticeNormal.h"

/*
Clase cara. Define una cara con un número de vértices.
*/
class Cara {
private:
	/*Número de vértices en la cara.*/
	GLint numVertices;
	
	/*Número de vértices ya insertados en la cara.*/
	GLint verticesDentro;

	/*Array de vértices en la cara.*/
	VerticeNormal** arrayVN;

	/*Suma en 1 el número de vértices dentro de la cara.*/
	void aumentaVerticesDentro() {
		this->verticesDentro++;
	}

public:

	/*
	Constructora de una cara con un número de vértices.
	numVertices = Número de vértices de la cara.
	*/
	Cara(GLint numVertices) {
		this->numVertices = numVertices;
		arrayVN = new VerticeNormal*[this->numVertices];
		this->verticesDentro = 0;
	}

	/*Destructora de la cara.*/
	~Cara() {
		/*Destruimos contenido del array arrayVN y el arrayVN.*/
		for (GLint i = 0; i < this->numVertices; i++)
			delete arrayVN[i];
		if (arrayVN != NULL)
			delete arrayVN;
	}


	/*Getters*/

	/*Devuelve el número de vértices de la cara.*/
	GLint getNumVertices() {
		return this->numVertices;
	}

	/*Devuelve el índice de la normal de la cara.*/
	GLint getIndiceNormal(GLint i){
		return this->arrayVN[i]->getIndiceNormal();
	}

	/*Devuelve el índice del vértice de la cara.*/
	GLint getIndiceVertice(GLint i){
		return this->arrayVN[i]->getIndiceVertice();
	}

	/*Devuelve el número de vértices que hay dentro de la cara.*/
	GLint getVerticesDentro() {
		return this->verticesDentro;
	}


	/*Setters*/

	/*Pone un número de vértices a la cara.*/
	void setNumVertice(GLint i) {
		this->numVertices = i;
	}

	/*Establece los índices de un vértice y su noral para la cara.*/
	void setIndiceVerticeNormal(GLint i, GLint v, GLint n) {
		this->arrayVN[i] = new VerticeNormal(v, n);
		this->aumentaVerticesDentro();
	}

};

#endif