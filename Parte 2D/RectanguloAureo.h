#ifndef RECTANGULOAUREO_H
#define RECTANGULOAUREO_H

#include "PV2D.h"
#include "Lapiz.h"

class RectanguloAureo : Lapiz{
private:
	/*Lapiz que dibujar� las figuras.*/
	Lapiz * lapiz;

	/*Punto inicial del l�piz.*/
	PV2D* ini;

	/*Variables del rect�ngulo.*/
	GLfloat base, altura, nuevaAltura;

	/*N�mero de rect�ngulos generados.*/
	GLint numRectangulos;

	/*N�mero de lados de cada arco.*/
	GLint numLadosArco;

	/*M�todo que crea el arco.*/
	void creaArco(GLint N) {
		/*Por cuatro para que el arco sea de N segmentos y no de N/4.*/
		N = N * 4;
		/*Calculamos �ngulos.*/
		GLfloat alpha = 360.0f / N;
		GLfloat beta = (180 - alpha) / 2.0f;
		GLfloat gamma = (180 - beta);
		/*Calculamos l, el tama�o de cada segmento.*/
		GLfloat l = nuevaAltura*(sqrt(2 * (1 - cos(toRadian(alpha)))));
		/*Nos posicionamos en la esquina dirigidos hacia donde se empezar� a dibujar.*/
		lapiz->forward(nuevaAltura, false);
		lapiz->turnTo(-90);
		lapiz->forward(nuevaAltura, false);
		lapiz->turnTo(-gamma);
		/*Dibujamos cada segmento.*/
		for (GLint i = 0; i < N / 4; i++) {
			lapiz->forward(l, true);
			if (i <= N / 4 - 1)
				lapiz->turnTo(-180 + 2 * beta);
		}
		/*Nos posicionamos para hacer otro rect�ngulo.*/
		lapiz->turnTo(-gamma + alpha);
	}

public:

	/*Constructoras.*/

	/*Constructora de la clase RectanguloAureo.*/
	RectanguloAureo(PV2D* inicio, GLfloat base, GLint N) {
		this->ini = inicio->clona();
		this->lapiz = new Lapiz(inicio->getX(), inicio->getY(), 90);
		this->base = base;
		/*Calculamos la altura de manera que sea proporcional a phi.*/
		this->altura = base / PHI;
		this->nuevaAltura = this->altura;
		this->numRectangulos = 1;
		this->numLadosArco = N;
	}

	


	/*M�todos de la clase.*/

	void dibuja() {
		/*Dibuja cuerpo inicial.*/
		lapiz->moveTo(ini, false);
		lapiz->setDir(90);
		lapiz->forward(altura, true, new Color("red"));
		lapiz->turnTo(-90);
		lapiz->forward(base, true, new Color("red"));
		lapiz->turnTo(-90);
		lapiz->forward(altura, true, new Color("red"));
		lapiz->turnTo(-90);
		lapiz->forward(base, true, new Color("red"));
		lapiz->turnTo(180);
		/*Dibujamos el resto de rect�ngulos.*/
		for (GLint i = 1; i < numRectangulos; i++) {
			lapiz->forward(nuevaAltura, false);
			lapiz->turnTo(90);
			/*Dibujamos la l�nea que divide el rect�ngulo en rect�ngulo y cuadrado.*/
			lapiz->forward(nuevaAltura, true, new Color("red"));
			lapiz->turnTo(180);
			/*Creamos el arco.*/
			creaArco(numLadosArco);
			nuevaAltura = nuevaAltura / PHI;
		}
		nuevaAltura = this->altura;
	}

	/*M�todo que dibuja el centro del rect�ngulo.*/
	void dibujaCentro() {
		GLfloat centroX = (this->ini->getX() + (this->ini->getX() + base)) / 2;
		GLfloat centroY = (this->ini->getY() + (this->ini->getY() + altura)) / 2;
		PV2D* centro = new PV2D(centroX, centroY);
		centro->dibuja(new Color("blue"));
	}

	/*M�todo que crea un nuevo rect�ngulo, avisa de que hay uno mas para hacer.*/
	void nuevoRectangulo() {
		this->numRectangulos++;
	}

	/*M�todo que borra nuevo rect�ngulo, avisa de que hay uno mas para quitar.*/
	void quitaRectangulo() {
		if (numRectangulos != 1)
			this->numRectangulos--;
	}




	/*Getters.*/

	/*M�todo que devuelve el tama�o de la base del rect�ngulo.*/
	GLfloat getBase() {
		return this->base;
	}

	/*M�todo que devuelve el tama�o de la altura del rect�ngulo.*/
	GLfloat getAltura() {
		return this->altura;
	}

	/*M�todo que devuelve el punto central del rect�ngulo.*/
	PV2D* getCentro() {
		GLfloat centroX = (this->ini->getX() + (this->ini->getX() + base)) / 2;
		GLfloat centroY = (this->ini->getY() + (this->ini->getY() + altura)) / 2;
		return new PV2D(centroX, centroY);
	}

	/*M�todo que devuelve el ojo de dios.*/
	PV2D* getOjoDios() {
		GLfloat alturaAux = this->altura;
		Lapiz *lapizAux = new Lapiz(this->ini, 90);
		/*Recorre cuerpo inicial.*/
		lapizAux->moveTo(ini, false);
		lapizAux->setDir(90);
		lapizAux->forward(altura, false);
		lapizAux->turnTo(-90);
		lapizAux->forward(base, false);
		lapizAux->turnTo(-90);
		lapizAux->forward(altura, false);
		lapizAux->turnTo(-90);
		lapizAux->forward(base, false);
		lapizAux->turnTo(180);
		/*Recorre el resto de rect�ngulos, 1000 para una buena aproximaci�n.*/
		for (GLint i = 1; i < 10000; i++) {
			lapizAux->forward(alturaAux, false);
			lapizAux->turnTo(90);
			/*Dibujamos la l�nea que divide el rect�ngulo en rect�ngulo y cuadrado.*/
			lapizAux->forward(alturaAux, false);
			lapizAux->turnTo(180);
			alturaAux = alturaAux / PHI;
		}
		return new PV2D(lapizAux->getPos()->getX(), lapizAux->getPos()->getY());

		/*PV2D* esquina = new PV2D(ini->getX() + base, ini->getY() + altura);
		GLfloat a = esquina->getX();
		GLfloat b = esquina->getY();
		return new PV2D(a*a / (2 * a - b), (a*b - b*b) / (2 * a - b));*/
	}

};

#endif