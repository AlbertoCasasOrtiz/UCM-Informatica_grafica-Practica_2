#ifndef PENTAGONO_H
#define PENTAGONO_H

#include "Lapiz.h"
#include "Color.h"

class Pentagono {
private:
	/*Lapiz que dibujará las figuras.*/
	Lapiz *lapiz;

	/*Punto inicial.*/
	PV2D* ini;
	PV2D* centro;

	/*Parámetros del pentágono.*/
	GLdouble lado, radioIni;
	GLdouble alpha, beta, gama;
	GLdouble longPentagrama;

	/*Añadir/quitar estrellas*/
	GLint numEstrellas;

	/*Array de puntos.*/
	PV2D** puntos;

	/*Método que crea el arco.*/
	void creaPentagono(Color *color, GLdouble radio) {
		/*Por cuatro para que el arco sea de N segmentos y no de N/4.*/
		GLint N = 5;
		/*Calculamos ángulos.*/
		this->alpha = 360.0f / N;
		this->beta = (180 - alpha) / 2.0f;
		this->gama = (180 - beta);
		/*Calculamos l, el tamaño de cada segmento.*/
		this->lado = radio*(sqrt(2 * (1 - cos(toRadian(alpha)))));
		/*Dibujamos cada segmento.*/
		this->puntos[0] = this->lapiz->getPos();
		for (GLint i = 0; i < N; i++) {
			lapiz->forward(lado, true, color);
			lapiz->turnTo(-180 + 2 * beta);
			if (i != N - 1) {
				this->puntos[i + 1] = this->lapiz->getPos();
			}
		}
	}

	void creaEstrella(Color * color, GLdouble radio){
		/*Calculamos la mitad de la distania entre los puntos que tienen un punto entre medias
		  mediante trigonometría: dist = 2 * Cateto opuesto = cos(a) * hipotenusa * 2 */
		GLdouble coseno = cos(2 * toRadian(beta) / 3);
		GLdouble dist = coseno * this->lado * 2;
		lapiz->turnTo(-2 * beta / 3);
		for (GLint i = 0; i < 5; i++) {
			lapiz->forward(dist, true, color);
			lapiz->turnTo(2*(-180 + 2 * beta) );
		}
		/*El punto inicial del pentágono interior lo obtengo multiplicando la distancia entre
		  los puntos que tienen un punto entre medias por 1/PHI, y restando esto a la propia distancia.*/
		lapiz->forward(dist - (dist * 1 / PHI), false);
	}



public:
	/*Constructora de la clase Pentagono.*/
	Pentagono(GLdouble radio, PV2D* init) {
		this->lapiz = new Lapiz(init, 0);
		this->puntos = new PV2D*[5];
		this->ini = init->clona();
		this->lado = 0;
		this->longPentagrama = 0;
		this->radioIni = radio;
		this->numEstrellas = 0;
		this->calculaCentro();
	}


	/*Metodo que dibuja el pentágono.*/
	void dibuja(){
		this->lapiz = new Lapiz(this->ini, 0);
		GLfloat radio = radioIni;
		creaPentagono(new Color("bondiBlue"), radio);
		for (int i = 0; i < numEstrellas; i++) {
			creaEstrella(new Color(i), radio);
			radio = this->lapiz->getPos()->distancia(this->getCentro());
			this->lado = radio*(sqrt(2 * (1 - cos(toRadian(alpha)))));
		}
	}

	void nuevaEstrella() {
		this->numEstrellas++;
	}

	void quitaEstrella() {
		if (this->numEstrellas > 0)
			this->numEstrellas--;
	}

	void calculaCentro() {
		Lapiz *lapizAux = new Lapiz(this->ini, 0.0);
		/*Por cuatro para que el arco sea de N segmentos y no de N/4.*/
		GLint N = 5;
		/*Calculamos ángulos.*/
		this->alpha = 360.0f / N;
		this->beta = (180 - alpha) / 2.0f;
		this->gama = (180 - beta);
		/*Calculamos l, el tamaño de cada segmento.*/
		this->lado = radioIni*(sqrt(2 * (1 - cos(toRadian(alpha)))));
		/*Dibujamos cada segmento.*/
		this->puntos[0] = lapizAux->getPos();
		for (GLint i = 0; i < N; i++) {
			lapizAux->forward(lado, false);
			if (i != N - 1) {
				this->puntos[i + 1] = lapizAux->getPos();
				lapizAux->turnTo(-180 + 2 * beta);
			}
		}
		this->centro = new PV2D(0.0, 0.0);
		for (int i = 0; i < 5; i++) {
			centro = centro->sumaPunto(puntos[i]);
		}
		this->centro = centro->divideEscalar(5);
	}

	PV2D* getCentro() {
		return this->centro;
	}

	GLdouble getRadio() {
		return this->radioIni;
	}
};



#endif