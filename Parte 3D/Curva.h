#ifndef CURVA_H
#define CURVA_H

/*
Clase curva. Clase estática que permite calcular marcos de frenet para la curva r*cos(t), r*sin(2 * t), r * sin(t) 
y devuelve sus valores en forma de matriz o de vector. También permite multiplicar sus valores por un punto
y devolver sus coordenadas nuevas globales.
*/
static class Curva {
private:
	/*Ecuación de la curva.*/
	static PV3D *C(GLfloat t, GLfloat r) {
		return new PV3D(r*cos(t), r*sin(2 * t), r * sin(t), 1);
	}

	/*Primera derivada de la curva.*/
	static PV3D *C1(GLfloat t, GLfloat r) {
		return new PV3D(-r*sin(t), 2 * r*cos(2 * t), r*cos(t), 0);
	}

	/*Segunda derivada de la curva.*/
	static PV3D *C2(GLfloat t, GLfloat r) {
		return new PV3D(-r*cos(t), -4 * r*sin(2 * t), -r*sin(t), 0);
	}

	/*Vector T de la curva.*/
	static PV3D *T(GLfloat t, GLfloat r) {
		PV3D *v = C1(t, r);
		v->normaliza();
		return v;
	}

	/*Vector B de la curva.*/
	static PV3D *B(GLfloat t, GLfloat r) {
		PV3D *v = C1(t, r)->productoVectorial(C2(t, r));
		v->normaliza();
		return v;
	}

	/*Vector N de la curva.*/
	static PV3D *N(GLfloat t, GLfloat r) {
		return B(t, r)->productoVectorial(T(t, r));
	}

public:
	/*Devuelve el marco de frenet para unos ciertos valores t (tiempo) y R (radio) en forma de matriz SquareMatrix.*/
	static SquareMatrix * getFrenetMatrix(GLfloat t, GLfloat R) {
		SquareMatrix *frenetMatrix = new SquareMatrix(N(t, R), B(t, R), T(t, R), C(t, R));
		return frenetMatrix;
	}

	/*Devuelve el marco de frenet para unos ciertos valores t (tiempo) y R (radio) en forma de vector.*/
	static GLfloat * getFrenetVector(GLfloat t, GLfloat R) {
		SquareMatrix *frenetMatrix = new SquareMatrix(N(t, R), B(t, R), T(t, R), C(t, R));
		return frenetMatrix->getVector();
	}

	/*Multiplica el marco de frenet para unos ciertos valores t (tiempo) y R (radio) por un punto.*/
	static PV3D* multiplica(PV3D * pv, GLfloat t, GLfloat R) {
		SquareMatrix *frenetMatrix = new SquareMatrix(N(t, R), B(t, R), T(t, R), C(t, R));
		return frenetMatrix->multiplica(pv);
	}


};


#endif