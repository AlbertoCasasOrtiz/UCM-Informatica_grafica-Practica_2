#ifndef VERTICENORMAL_H
#define VERTICENORMAL_H

class VerticeNormal {
private:
	/*Indice del vertice y su normal asociada.*/
	GLint indiceVertice, indiceNormal;

public:
	/*Constructora de la clase verticeNormal.*/
	VerticeNormal(GLint v, GLint n) {
		this->indiceVertice = v;
		this->indiceNormal = n;
	}
	

	/*Getters*/

	/*Devuelve el indice del punto del vértice.*/
	GLint getIndiceVertice(){
		return this->indiceVertice;
	}

	/*Devuelve el indice de la normal del vértice.*/
	GLint getIndiceNormal(){
		return this->indiceNormal;
	}

};

#endif