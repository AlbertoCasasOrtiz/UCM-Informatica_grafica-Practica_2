#ifndef CONSTANT_H
#define CONSTANT_H

/*Constante PI.*/
const static double PI = 3.14159265359;

/*Constante PHI.*/
const static double PHI = 1.61803398874;

/*Función para pasar de grados a radianes.*/
static GLdouble toRadian(GLdouble a) {
	return  2 * PI*a / 360;
}

#endif