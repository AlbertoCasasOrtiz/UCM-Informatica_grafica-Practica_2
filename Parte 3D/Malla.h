#ifndef MALLA_H
#define MALLA_H

#include <gl/GL.h>

#include "PV3D.h"
#include "Cara.h"
#include "Color.h"

const double PI = 3.14159265359;

class Malla {
protected:
	/*N�mero de v�rtices de la malla.*/
	GLint numVertices;
	/*Array con los v�rtices de la malla.*/
	PV3D** vertice;
	/*N�mero de normales en la malla.*/
	GLint numNormales;
	/*Array con las normales en la malla.*/
	PV3D** normal;
	/*N�mero de caras en la malla.*/
	GLint numCaras;
	/*Array de caras en la malla.*/
	Cara** cara;

	/*Para color.*/
	/*N�mero de colores en la malla.*/
	GLint numColores;
	/*Array con los colores en la malla.*/
	Color** color;

	/*Para abstraer los arrays.*/
	GLint tamVertice;
	GLint tamNormal;
	GLint tamCara;
	GLint tamColor;

	/*Redimensiona el array vertice al meter nuevos miembros.*/
	void resizeVertice() {
		PV3D** verticeAux = new PV3D*[this->tamVertice + 15];
		for (GLint i = 0; i < this->numVertices; i++)
			verticeAux[i] = vertice[i];
		this->tamVertice += 15;
		delete vertice;
		vertice = verticeAux;
	}

	/*Redimensiona el array normal al meter nuevos miembros.*/
	void resizeNormal() {
		PV3D** normalAux = new PV3D*[this->tamNormal + 5];
		for (GLint i = 0; i < this->numNormales; i++)
			normalAux[i] = normal[i];
		this->tamNormal += 5;
		delete normal;
		normal = normalAux;
	}

	/*Redimensiona el array cara al meter nuevos miembros.*/
	void resizeCara() {
		Cara** caraAux = new Cara*[this->tamCara + 5];
		for (GLint i = 0; i < this->numCaras; i++)
			caraAux[i] = cara[i];
		this->tamCara += 5;
		delete cara;
		cara = caraAux;
	}

	/*Redimensiona el array color al meter nuevos miembros.*/
	void resizeColor() {
		Color** colorAux = new Color*[this->tamColor + 5];
		for (GLint i = 0; i < this->numColores; i++)
			colorAux[i] = color[i];
		this->tamColor += 5;
		delete color;
		color = colorAux;
	}

public:
	/*Constructura de la clase malla.*/
	Malla() {
		/*Tama�o de los arrays.*/
		this->tamVertice = 2;
		this->tamNormal = 2;
		this->tamCara = 2;
		this->tamColor = 2;

		/*N�mero de elementos dentro de los arrays.*/
		this->numVertices = 0;
		this->numNormales = 0;
		this->numCaras = 0;
		this->numColores = 0;

		/*Inicializaci�n de los arrays.*/
		this->vertice = new PV3D*[this->tamVertice];
		this->normal = new PV3D*[this->tamNormal];
		this->cara = new Cara*[this->tamCara];
		this->color = new Color*[this->tamColor];
	}

	/*Destructora de la clase malla.*/
	~Malla() {
		/*Destruir contenido del array vertice y array vertice.*/
		for (GLint i = 0; i < this->numVertices; i++)
			delete vertice[i];
		delete vertice;
		/*Destruir contenido del array normal y array normal.*/
		for (GLint i = 0; i < this->numNormales; i++)
			delete normal[i];
		delete normal;
		/*Destruir contenido del array cara y array cara.*/
		for (GLint i = 0; i < this->numCaras; i++)
			delete cara[i];
		delete cara;
		/*Destruir contenido del array color y array color.*/
		for (GLint i = 0; i < this->numColores; i++)
			delete color[i];
		delete color;
	}


	/*M�todos de la clase.*/

	/*Calcula el vector normal a una cara por el m�todo de Newell.*/
	PV3D* CalculoVectorNormalPorNewell(Cara *cara) {
		PV3D *n = new PV3D(0.0, 0.0, 0.0, 0);
		PV3D *verticeActual, *verticeSiguiente;
		for (GLint i = 0; i < cara->getNumVertices(); i++) {
			verticeActual = vertice[cara->getIndiceVertice(i)];
			verticeSiguiente = vertice[cara->getIndiceVertice((i + 1) % cara->getNumVertices())];
			n->setX(n->getX() + ((verticeActual->getY() - verticeSiguiente->getY()) * (verticeActual->getZ() + verticeSiguiente->getZ())));
			n->setY(n->getY() + ((verticeActual->getZ() - verticeSiguiente->getZ()) * (verticeActual->getX() + verticeSiguiente->getX())));
			n->setZ(n->getZ() + ((verticeActual->getX() - verticeSiguiente->getX()) * (verticeActual->getY() + verticeSiguiente->getY())));
		}
		verticeActual = NULL;
		verticeSiguiente = NULL;
		n->normaliza();
		return n;
	}

	/*Crea, a partir de  perfil, una figura por revoluci�n generando sus v�rtices y sus caras.*/
	void revoluci�n(PV3D ** perfil, GLint numVerticesPerfil, GLint nQ, GLint radio, GLint altura, GLfloat rotY, GLfloat amplitud, Color *color) {
		/*Sumamos al �ndice de v�rtices esto para no sobreescribir v�rtices anteriores.*/
		GLint numVerticesAnt = this->numVertices;
		
		/*Obtenemos los v�rtices de la malla.*/
		for (GLint i = 0; i <= nQ; i++) {
			double theta = i * amplitud / (double)nQ + rotY;
			double c = cos(theta);
			double s = sin(theta);
			for (GLint j = 0; j < numVerticesPerfil; j++) {
				GLint indice = numVerticesAnt + i*numVerticesPerfil + j;
				GLfloat x = c*perfil[j]->getX() + s*perfil[j]->getZ();
				GLfloat z = -s*perfil[j]->getX() + c*perfil[j]->getZ();
				PV3D* p = new PV3D(x, perfil[j]->getY(), z, 1);
				this->insertaVertice(p, indice);
			}
		}

		/*Creamos las caras.*/

		/*El �ndice de la cara ser� inicializado al n�mero de caras actual para no sobreescribir caras anteriores.*/
		GLint indiceCara = this->getNumCaras();

		for (GLint i = 0; i < nQ; i++) {
			for (GLint j = 0; j < numVerticesPerfil - 1; j++) {
				GLint indice = numVerticesAnt + i*(numVerticesPerfil)+j;
				VerticeNormal** vn = new VerticeNormal*[4];
				vn[0] = new VerticeNormal(indice, indiceCara);
				vn[1] = new VerticeNormal((indice + numVerticesPerfil) % this->numVertices, indiceCara);
				vn[2] = new VerticeNormal((indice + 1 + numVerticesPerfil) % this->numVertices, indiceCara);
				vn[3] = new VerticeNormal(indice + 1, indiceCara);
				this->insertaCara(4, vn);

				PV3D* v = this->CalculoVectorNormalPorNewell(this->getCara(indiceCara));
				this->insertaNormal(v->getX(), v->getY(), v->getZ());
				this->insertaColor(color->getR(), color->getG(), color->getB());
				indiceCara++;
			}
		}

	}

	/*Obtiene el centro de una cara.*/
	PV3D *centroCara(Cara* cara) {
		GLint *indices = new GLint[cara->getNumVertices()];
		PV3D **vertices = new PV3D*[cara->getNumVertices()];
		GLfloat x = 0, y = 0, z = 0;

		/*Obtenemos los �ndices de los v�rtices de las caras.*/
		for (GLint i = 0; i < cara->getNumVertices(); i++) {
			indices[i] = cara->getIndiceVertice(i);
		}

		/*Obtenemos los v�rtices de las caras.*/
		for (GLint i = 0; i < cara->getNumVertices(); i++) {
			vertices[i] = this->vertice[indices[i]];
		}

		/*Obtenemos los valores x, y e z del punto central.*/
		for (int i = 0; i < cara->getNumVertices(); i++) {
			x += vertices[i]->getX();
			y += vertices[i]->getY();
			z += vertices[i]->getZ();
		}
		x /= cara->getNumVertices();
		y /= cara->getNumVertices();
		z /= cara->getNumVertices();

		return new PV3D(x, y, z, 1);
	}

	/*Obtiene el centro de un pol�gono formado por num puntos*/
	PV3D *centroPuntos(GLint * indices, GLint num) {
		PV3D ** puntos = new PV3D*[num];

		/*Obtenemos los puntos a los que apuntan los �ndices.*/
		for (GLint i = 0; i < num; i++) {
			puntos[i] = this->getVertice(indices[i]);
		}

		/*Obtenemos los valores nuevos de x, y e z.*/
		GLfloat x = 0, y = 0, z = 0;
		for (int i = 0; i < num; i++) {
			x += puntos[i]->getX();
			y += puntos[i]->getY();
			z += puntos[i]->getZ();
		}
		x /= num;
		y /= num;
		z /= num;
		return new PV3D(x, y, z, 1);
	}

	/*Dada una cara, aplica extrusi�n sobre ella sobre el plano XZ.*/
	void extrudir(GLfloat altura, GLint numVertPerfil, Color* color) {
		GLint vertInicio = this->numVertices;

		/*Generamos los v�rtices nuevos.*/
		for (GLint i = vertInicio - numVertPerfil; i < vertInicio; i++) {
			this->insertaVertice(this->vertice[i]->getX(), this->vertice[i]->getY() + altura, this->vertice[i]->getZ());
		}


		/*Crea caras laterales.*/
		for (GLint i = vertInicio - numVertPerfil; i < vertInicio; i++) {
			creaCara(4);
			insertaVerticeEnCara(this->getNumCaras() - 1, i + numVertPerfil, this->getNumNormales());
			insertaVerticeEnCara(this->getNumCaras() - 1, ((i + 1) % (vertInicio) + (numVertPerfil)), this->getNumNormales());
			insertaVerticeEnCara(this->getNumCaras() - 1, (i + 1) % (vertInicio), this->getNumNormales());
			insertaVerticeEnCara(this->getNumCaras() - 1, i, this->getNumNormales());
			this->insertaColor(color);
			this->insertaNormal(this->CalculoVectorNormalPorNewell(this->cara[this->getNumCaras() - 1]));
		}

		/*Crea cara inferior.*/
		creaCara(numVertPerfil);
		for (GLint i = vertInicio - numVertPerfil; i < vertInicio; i++) {
			insertaVerticeEnCara(this->numCaras - 1, i, this->numNormales);
		}
		this->insertaColor(color);
		this->insertaNormal(this->CalculoVectorNormalPorNewell(this->cara[this->numCaras - 1]));

		/*Crea cara superior.*/
		creaCara(numVertPerfil);
		for (GLint i = vertInicio - 1; i >= vertInicio - numVertPerfil; i--) {
			insertaVerticeEnCara(this->numCaras - 1, numVertPerfil + i, this->numNormales);
		}
		this->insertaColor(color);
		this->insertaNormal(this->CalculoVectorNormalPorNewell(this->cara[this->numCaras - 1]));
	}

	/*Dibuja los elementos especificados con las funciones anteriores.*/
	void dibuja() {
		for (GLint i = 0; i < numCaras; i++) {
			glLineWidth(1.0);
			glColor3f(this->color[i]->getR(), this->color[i]->getG(), this->color[i]->getB());
			glBegin(GL_POLYGON); //o glBegin(GL_LINE_LOOP);
			for (GLint j = 0; j < cara[i]->getNumVertices(); j++) {
				GLint iN = cara[i]->getIndiceNormal(j);
				GLint iV = cara[i]->getIndiceVertice(j);
				glNormal3f(normal[iN]->getX(), normal[iN]->getY(), normal[iN]->getZ());
				//Si hubiera coordenadas de textura, aqu� se suministrar�an
				//las coordenadas de textura del v�rtice j con glTexCoor2f(�);
				glVertex3f(vertice[iV]->getX(), vertice[iV]->getY(), vertice[iV]->getZ());
			}
			glEnd();
		}
	}

	/*Dibuja las normales a las caras de la malla.*/
	void dibujaNormales() {
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
	}

	/*Setters*/

	void setArrVertices(PV3D**arr) {
		this->vertice = arr;
	}

	/*Crea un v�rtice.*/
	void insertaVertice(GLfloat x, GLfloat y, GLfloat z) {
		if (this->numVertices >= this->tamVertice)
			this->resizeVertice();
		//El cuarto par�metro siemptre ser� 1 por que es un punto.
		this->vertice[this->numVertices] = new PV3D(x, y, z, 1);
		this->numVertices++;
	}

	/*Crea un v�rtice.*/
	void insertaVertice(PV3D* vert, GLint pos) {
		while (pos >= this->tamVertice)
			this->resizeVertice();
		//El cuarto par�metro siemptre ser� 1 por que es un punto.
		this->vertice[pos] = vert->clona();
		if(pos >= this->numVertices)
			this->numVertices++;
	}

	/*Crea un vector normal.*/
	void insertaNormal(GLfloat x, GLfloat y, GLfloat z) {
		if (this->numNormales >= this->tamNormal)
			this->resizeNormal();
		//El cuarto par�metro siemptre ser� 0 por que es un vector.
		this->normal[this->numNormales] = new PV3D(x, y, z, 0);
		this->numNormales++;
	}

	/*Establece una normal nueva en el array de normales.*/
	void insertaNormal(PV3D * normal) {
		if (this->numNormales >= this->tamNormal)
			this->resizeNormal();
		//El cuarto par�metro siemptre ser� 0 por que es un vector.
		this->normal[this->numNormales] = normal;
		this->numNormales++;
	}

	/*Crea una cara con un n�mero de v�rtices igual a numVertices.*/
	void creaCara(GLint numVertices) {
		if (this->numCaras >= this->tamCara)
			this->resizeCara();
		this->cara[this->numCaras] = new Cara(numVertices);
		this->numCaras++;
	}

	/*Inserta un v�rtice numVertice en la cara numCara con su normal numNormal.*/
	void insertaVerticeEnCara(GLint numCara, GLint numVertice, GLint numNormal) {
		cara[numCara]->setIndiceVerticeNormal(cara[numCara]->getVerticesDentro(), numVertice, numNormal);
	}

	/*Inserta una cara dados un n�mero de v�rtices y un array de VerticeNormal.*/
	void insertaCara(GLint numVert, VerticeNormal** vn) {
		this->creaCara(numVert);
		for (GLint i = 0; i < numVert; i++) {
			this->insertaVerticeEnCara(this->numCaras - 1, vn[i]->getIndiceVertice(), vn[i]->getIndiceNormal());
		}
	}

	/*A�ade un color para una cara.*/
	void insertaColor(GLfloat x, GLfloat y, GLfloat z) {
		if (this->numColores >= this->tamColor)
			this->resizeColor();
		this->color[this->numColores] = new Color(x, y, z);
		this->numColores++;
	}

	/*A�ade un color para una cara.*/
	void insertaColor(Color *color) {
		if (this->numColores >= this->tamColor)
			this->resizeColor();
		this->color[this->numColores] = color;
		this->numColores++;
	}


	/*Getters*/

	PV3D ** getArrVertices() {
		return this->vertice;
	}

	/*Devuelve la cara con �ndice i.*/
	Cara* getCara(GLint i) {
		return this->cara[i];
	}

	/*Devuelve el v�rtice con �ndice i*/
	PV3D* getVertice(GLint i) {
		return this->vertice[i];
	}

	/*Devuelve el n�mero de caras creadas.*/
	GLint getNumCaras() {
		return this->numCaras;
	}

	/*Devuelve el n�mero de v�rtices creadas.*/
	GLint getNumVertices() {
		return this->numVertices;
	}

	/*Devuelve el n�mero de normales creadas.*/
	GLint getNumNormales() {
		return this->numNormales;
	}

};
#endif