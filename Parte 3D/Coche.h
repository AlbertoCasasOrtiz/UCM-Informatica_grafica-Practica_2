#ifndef QUESO_CPP
#define QUESO_CPP

#include "Malla.h"
#include "Cilindro.h"

/*
Clase coche. Crea un coche a partir de un marco dado y 4 cilindros.
*/
class Coche : public Malla{
private:
	/*Número de puntos del perfil del cuerpo del coche.*/
	const GLint NUM_PUNTOS_PERFIL_S = 6;

	/*Número de puntos del perfil de los cilindros.*/
	const GLint NUM_PUNTOS_PERFIL_C = 30;

	/*Número de ruedas.*/
	const GLint NUM_RUEDAS = 4;

	/*Parámetros de las posiciones de los puntos.*/
	GLfloat anchura, altura, profundidad, radio, R;

	/*Array que contiene las ruedas.*/
	Cilindro **ruedas;

	/*Método que crea el perfil del cuerpo del coche.*/
	void creaPerfilSuperior(GLfloat anchura, GLfloat altura, GLfloat profundidad) {
		/*Definición de vértices*/
		this->insertaVertice(0.0, 0, 0.0);
		this->insertaVertice(anchura, 0, 0.0);
		this->insertaVertice(anchura, 0, profundidad);
		this->insertaVertice(anchura, 0, profundidad + profundidad/1.5);
		this->insertaVertice(anchura/1.5, 0, profundidad + profundidad / 1.5);
		this->insertaVertice(0.0, 0, profundidad);
	}

public:
	/*Constructora de la clase coche.*/
	Coche(GLfloat anchura, GLfloat altura, GLfloat profundidad,  Color * color, Color * colorRuedas) {
		/*Definimos una nueva malla.*/
		Malla();

		/*Inicializamos las variables de la clase.*/
		this->anchura = anchura;
		this->altura = altura;
		this->profundidad = profundidad;
		this->radio = anchura / 3.0;
		this->R = R;

		/*Creamos el perfil del cuerpo.*/
		this->creaPerfilSuperior(anchura, altura, profundidad);

		/*Extrudimos los vértices para generar el cuerpo.*/
		this->extrudir(altura, NUM_PUNTOS_PERFIL_S, color);

		/*Hacemos las ruedas, serán cilindros.*/
		ruedas = new Cilindro*[NUM_RUEDAS];
		for (GLint i = 0; i < NUM_RUEDAS; i++) {
			ruedas[i] = new Cilindro(30, anchura / 3, altura / 3, colorRuedas);
		}
	}

	/*Método que dibuja el cuerpo del coche y los cilindros.*/
	void dibuja() {
		/*Dibujamos el cuerpo.*/
		for (GLint i = 0; i < numCaras; i++) {
			glLineWidth(1.0);
			glColor3f(this->color[i]->getR(), this->color[i]->getG(), this->color[i]->getB());
			glBegin(GL_POLYGON); //o glBegin(GL_LINE_LOOP);
			for (GLint j = 0; j < cara[i]->getNumVertices(); j++) {
				GLint iN = cara[i]->getIndiceNormal(j);
				GLint iV = cara[i]->getIndiceVertice(j);
				glNormal3f(normal[iN]->getX(), normal[iN]->getY(), normal[iN]->getZ());
				//Si hubiera coordenadas de textura, aquí se suministrarían
				//las coordenadas de textura del vértice j con glTexCoor2f(…);
				glVertex3f(vertice[iV]->getX(), vertice[iV]->getY(), vertice[iV]->getZ());
			}
			glEnd();
		}

		/*Dibujamos cada rueda colocada en su posición.*/
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(anchura, -altura/ 17.5, radio);
			this->ruedas[0]->dibuja();
		glPopMatrix();

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(anchura, altura-altura/3.5, radio);
			this->ruedas[1]->dibuja();
		glPopMatrix();

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(anchura, -altura / 17.5, profundidad + profundidad / 1.5 - radio);
			this->ruedas[2]->dibuja();
		glPopMatrix();

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(anchura, altura - altura / 3.5, profundidad + profundidad / 1.5 - radio);
			this->ruedas[3]->dibuja();
		glPopMatrix();
	}

	/*Método que dibuja las normales del coche y los cilindros.*/
	void dibujaNormales() {
		/*Dibujamos las normales del cuerpo del coche.*/
		Cara * cara;
		PV3D* puntoMedio;
		glBegin(GL_LINES);
		glColor3f(1.0, 0.0, 0.0);
		for (GLint i = 0; i < this->numCaras; i++) {
			cara = this->getCara(i);
			puntoMedio = this->centroCara(cara);
			glVertex3f(puntoMedio->getX(), puntoMedio->getY(), puntoMedio->getZ());
			glVertex3f(puntoMedio->getX() + this->normal[cara->getIndiceNormal(0)]->getX(), puntoMedio->getY() + this->normal[cara->getIndiceNormal(0)]->getY(), puntoMedio->getZ() + this->normal[cara->getIndiceNormal(0)]->getZ());
		}
		glEnd();

		/*Dibujamos las normales de cada rueda.*/
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(anchura, -altura / 10, radio);
			this->ruedas[0]->dibujaNormales();
		glPopMatrix();

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(anchura, altura - altura / 3.5, radio);
			this->ruedas[1]->dibujaNormales();
		glPopMatrix();

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(anchura, -altura / 10, profundidad + profundidad / 1.5 - radio);
			this->ruedas[2]->dibujaNormales();
		glPopMatrix();

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(anchura, altura - altura / 3.5, profundidad + profundidad / 1.5 - radio);
			this->ruedas[3]->dibujaNormales();
		glPopMatrix();
	}

	/*Devuelve el número de vértices del coche.*/
	GLint getNumVertices() {
		return this->numVertices + ruedas[0]->getNumVertices()*NUM_RUEDAS;
	}

	/*Devuelve el número de caras del coche.*/
	GLint getNumCaras() {
		return this->numCaras + ruedas[0]->getNumCaras()*NUM_RUEDAS;
	}

	/*Devuelve el número de normales del coche.*/
	GLint getNumNormales() {
		return this->numNormales + ruedas[0]->getNumNormales()*NUM_RUEDAS;
	}


	/*Destructora de la clase coche.*/
	~Coche() {
		delete this;
		for (GLint i = 0; i < NUM_RUEDAS; i++) {
			delete ruedas[i];
		}
	}

};


#endif