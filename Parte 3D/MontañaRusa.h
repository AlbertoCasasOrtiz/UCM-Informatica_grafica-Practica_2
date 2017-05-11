#ifndef MONTAÑARUSA_H
#define MONTAÑARUSA_H

#include "Malla.h"
#include "SquareMatrix.h"
#include "Curva.h"

class MontañaRusa : public Malla{
private:
	/*Número de vértices en el perfil.*/
	GLint numVerticesPerfil;

	/*Perfil.*/
	PV3D** perfil;

	/*Método que crea el perfil, el perfil será un poligono regular de nP caras y radio r.*/
	void creaPerfil(GLint nP, GLfloat r) {
		GLfloat inc = (2 * PI / nP);
		this->perfil = new PV3D*[nP];
		for (int i = 0; i < nP; i++)
			perfil[i] = new PV3D(r*cos(2 * PI - i*inc), r*sin(2 * PI - i*inc), 0, 1);
	}

public:
	/*Constructora de la clase MontañaRusa.
	    nQ = número de segmentos.
		nP = número de lados del perfil.
		r = radio del perfil.
		R = radio de la montaña rusa.
		color = Color de la montaña rusa.
	*/
	MontañaRusa(GLint nQ, GLint nP, GLfloat r, GLfloat R, Color *color) {
		/*Llamamos a la constructora de la malla.*/
		Malla();

		/*Inicializamos los elementos.*/
		this->numVerticesPerfil = nP;
		this->creaPerfil(nP, r);

		PV3D ** generado = new PV3D*[nP];

		GLint cont = 0;
		for (GLfloat i = 0; i < 2 * PI; i+=2*PI/nQ) {
			/*Generamos nuevos vértices.*/
			for (GLint j = 0; j < nP; j++) {
				generado[j] = Curva::multiplica(this->perfil[j], i, R);
			}

			/*Los insertamos en la malla.*/
			for (GLint j = 0; j < nP; j++) {
				this->insertaVertice(generado[j]->getX(), generado[j]->getY(), generado[j]->getZ());
			}

			/*Creamos las caras que representan los polígonos, solo para debug.
			this->malla->creaCara(nP);
			for (GLint j = cont*nP; j < (cont +1)*nP; j++) {
				this->malla->insertaVerticeEnCara(cont, j, cont);
			}
			PV3D* v = this->malla->CalculoVectorNormalPorNewell(this->malla->getCara(i));
			this->malla->insertaNormal(v);
			this->malla->insertaColor(new Color("yellow"));
			*/
			cont++;
		}

		/*Aquí creamos las caras del tubo de la curva.*/
		GLint indiceCara = 0;
		GLint indice;
		GLint numVertices = this->getNumVertices();
		GLint indices[4];
		PV3D *puntoCentral;
		for (GLint i = 0; i < nQ; i++) {
			/*Creamos las nP-1 primeras caras.*/
			for (int j = 0; j < nP-1; j++) {
				indice = i*(nP)+j;
				
				/*Guardamos los índices de los vértices de la cara cuadrangular en el array de indices.*/
				indices[0] = (indice + nP + 1) % numVertices;
				indices[1] = (indice + 1) % numVertices;
				indices[2] = indice;
				indices[3] = (indice + nP) % numVertices;

				/*Obtenemos el nuevo punto y lo insertamos.*/
				puntoCentral = this->centroPuntos(indices, 4);
				this->insertaVertice(puntoCentral->getX(), puntoCentral->getY(), puntoCentral->getZ());

				/*Creamos la primera cara.*/
				this->creaCara(3);
				this->insertaVerticeEnCara(indiceCara, (indice + nP + 1) % numVertices, indiceCara);
				this->insertaVerticeEnCara(indiceCara, (indice + 1) % numVertices, indiceCara);
				this->insertaVerticeEnCara(indiceCara, this->getNumVertices() - 1, indiceCara);
				PV3D* v = this->CalculoVectorNormalPorNewell(this->getCara(indiceCara));
				this->insertaNormal(v);
				this->insertaColor(color);
				indiceCara++;

				/*Creamos la segunda cara.*/
				this->creaCara(3);
				this->insertaVerticeEnCara(indiceCara, (indice + 1) % numVertices, indiceCara);
				this->insertaVerticeEnCara(indiceCara, indice, indiceCara);
				this->insertaVerticeEnCara(indiceCara, this->getNumVertices() - 1, indiceCara);
				v = this->CalculoVectorNormalPorNewell(this->getCara(indiceCara));
				this->insertaNormal(v);
				this->insertaColor(color);
				indiceCara++;

				/*Creamos la tercera cara.*/
				this->creaCara(3);
				this->insertaVerticeEnCara(indiceCara, indice, indiceCara);
				this->insertaVerticeEnCara(indiceCara, (indice + nP) % numVertices, indiceCara);
				this->insertaVerticeEnCara(indiceCara, this->getNumVertices() - 1, indiceCara);
				v = this->CalculoVectorNormalPorNewell(this->getCara(indiceCara));
				this->insertaNormal(v);
				this->insertaColor(color);
				indiceCara++;

				/*Creamos la cuarta cara.*/
				this->creaCara(3);
				this->insertaVerticeEnCara(indiceCara, (indice + nP) % numVertices, indiceCara);
				this->insertaVerticeEnCara(indiceCara, (indice + nP + 1) % numVertices, indiceCara);
				this->insertaVerticeEnCara(indiceCara, this->getNumVertices() - 1, indiceCara);
				v = this->CalculoVectorNormalPorNewell(this->getCara(indiceCara));
				this->insertaNormal(v);
				this->insertaColor(color);
				indiceCara++;

			}
			/*La cara nP, que es un poco diferente, la creamos aparte.*/
			indice++;

			/*Guardamos los índices de los vértices de la cara cuadrangular en el array de indices.*/
			indices[0] = indice;
			indices[1] = (indice + nP) % numVertices;
			indices[2] = (indice + 1) % numVertices;
			indices[3] = (indice + nP + 1 - 2 * nP) % numVertices;

			/*Obtenemos el nuevo punto y lo insertamos.*/
			puntoCentral = this->centroPuntos(indices, 4);
			this->insertaVertice(puntoCentral->getX(), puntoCentral->getY(), puntoCentral->getZ());

			/*Creamos la primera cara.*/
			this->creaCara(3);
			this->insertaVerticeEnCara(indiceCara, indice, indiceCara);
			this->insertaVerticeEnCara(indiceCara, (indice + nP) % numVertices, indiceCara);
			this->insertaVerticeEnCara(indiceCara, this->getNumVertices() - 1, indiceCara);
			PV3D* v = this->CalculoVectorNormalPorNewell(this->getCara(indiceCara));
			this->insertaNormal(v);
			this->insertaColor(color);
			indiceCara++;

			/*Creamos la segunda cara.*/
			this->creaCara(3);
			this->insertaVerticeEnCara(indiceCara, (indice + nP) % numVertices, indiceCara);
			this->insertaVerticeEnCara(indiceCara, (indice + 1) % numVertices, indiceCara);
			this->insertaVerticeEnCara(indiceCara, this->getNumVertices() - 1, indiceCara);
			v = this->CalculoVectorNormalPorNewell(this->getCara(indiceCara));
			this->insertaNormal(v);
			this->insertaColor(color);
			indiceCara++;

			/*Creamos la tercera cara.*/
			this->creaCara(3);
			this->insertaVerticeEnCara(indiceCara, (indice + 1) % numVertices, indiceCara);
			this->insertaVerticeEnCara(indiceCara, (indice + nP + 1 - 2 * nP) % numVertices, indiceCara);
			this->insertaVerticeEnCara(indiceCara, this->getNumVertices() - 1, indiceCara);
			v = this->CalculoVectorNormalPorNewell(this->getCara(indiceCara));
			this->insertaNormal(v);
			this->insertaColor(color);
			indiceCara++;

			/*Creamos la cuarta cara.*/
			this->creaCara(3);
			this->insertaVerticeEnCara(indiceCara, (indice + nP + 1 - 2 * nP) % numVertices, indiceCara);
			this->insertaVerticeEnCara(indiceCara, indice, indiceCara);
			this->insertaVerticeEnCara(indiceCara, this->getNumVertices() - 1, indiceCara);
			v = this->CalculoVectorNormalPorNewell(this->getCara(indiceCara));
			this->insertaNormal(v);
			this->insertaColor(color);
			indiceCara++;
			
		}

	}
	

	/*Destructora de la clase MontañaRusa.*/
	~MontañaRusa() {
		for (int i = 0; i < this->numVerticesPerfil; i++) {
			delete this->perfil[i];
		}
		delete this->perfil;
	}
};
#endif