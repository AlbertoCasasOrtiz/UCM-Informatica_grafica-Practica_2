#ifndef CILINDRO_H
#define CILINDRO_H

#include "Malla.h"

/*Clase cilindro. Crea un cilindro  de altura h a partir de un perfil dado, el cual es un polígono regular de nP lados.*/
class Cilindro : public Malla {
private:
	/*Método que crea el perfil, el perfil será un poligono regular de nP caras y radio r.*/
	void creaPerfil(GLint nP, GLfloat r) {
		PV3D** perfil;
		GLfloat inc = (2 * PI / nP);
		perfil = new PV3D*[nP];
		for (int i = nP-1; i >= 0; i--) {
			perfil[i] = new PV3D(r*cos(2 * PI - i*inc), 0, r*sin(2 * PI - i*inc), 1);
			this->insertaVertice(perfil[i]->getX(), perfil[i]->getY(), perfil[i]->getZ());
		}
	}

public:
	/*
	Constructora de la clase cilindro.
	nP = número de lados del polígono del perfil.
	r = radio del polígono del perfil.
	altura = altura que tendrá el cilindro.
	color = color del cilindro.
	*/
	Cilindro(GLint nP, GLfloat r, GLfloat altura, Color *color) {
		/*Definimos una nueva malla.*/
		Malla();
		/*Parte superior.*/
		/*Creamos el perfil.*/
		this->creaPerfil(nP, r);

		/*Extrudimos los vértices.*/
		this->extrudir(altura, nP, color);
	}

	/*Destructora de la clase cilindro.*/
	~Cilindro() {
		delete this;
	}
};

#endif