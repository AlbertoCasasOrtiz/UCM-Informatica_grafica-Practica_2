#ifndef COLOR_H
#define COLOR_H

#include <GL/GL.h>
#include<string>

using namespace std;

/*
Clase color. Define un color en RGB en decimal.
*/
class Color {
private:
	/*Valores rgb para los colores.*/
	GLfloat r, g, b;

public:
	/*
	Constructora de la clase color, dado un string con el nombre de un color, devuelve ese color.
	color = nombre del color. Si no existe, por defecto será negro.
	*/
	Color(string color) {
		if (color.compare("red") == 0) {
			this->r = 1.0;
			this->g = 0.0;
			this->b = 0.0;
		}
		else if (color.compare("green") == 0) {
			this->r = 0.0;
			this->g = 1.0;
			this->b = 0.0;
		}
		else if (color.compare("blue") == 0) {
			this->r = 0.0;
			this->g = 0.0;
			this->b = 1.0;
		}
		else if (color.compare("cyan") == 0) {
			this->r = 0.0;
			this->g = 1.0;
			this->b = 1.0;
		}
		else if (color.compare("yellow") == 0) {
			this->r = 1.0;
			this->g = 1.0;
			this->b = 0.0;
		}
		else if (color.compare("magenta") == 0) {
			this->r = 1.0;
			this->g = 0.0;
			this->b = 1.0;
		}
		else if (color.compare("white") == 0) {
			this->r = 1.0;
			this->g = 1.0;
			this->b = 1.0;
		}
		else if (color.compare("purple") == 0) {
			this->r = 0.5;
			this->g = 0.0;
			this->b = 1.0;
		}
		else if (color.compare("orange") == 0) {
			this->r = 0.9019;
			this->g = 0.3725;
			this->b = 0.0;
		}
		else if (color.compare("brown") == 0) {
			this->r = 0.5529;
			this->g = 0.2862;
			this->b = 0.1451;
		}
		else if (color.compare("bondiBlue") == 0) {
			this->r = 0.0;
			this->g = 0.5843;
			this->b = 0.7137;
		}
		else {
			this->r = 0.0;
			this->g = 0.0;
			this->b = 0.0;
		}
	}

	/*
	Constructora de la clase color.
	r = cantidad de color rojo.
	g = cantidad de color verde.
	b = cantidad de color azul.
	*/
	Color(GLfloat r, GLfloat g, GLfloat b){
		this->r = r;
		this->g = g;
		this->b = b;
	}

	/*Getters*/

	/*Devuelve el valor r de color.*/
	GLfloat getR() {
		return this->r;
	}

	/*Devuelve el valor g de color.*/
	GLfloat getG() {
		return this->g;
	}

	/*Devuelve el valor b de color.*/
	GLfloat getB() {
		return this->b;
	}

};

#endif