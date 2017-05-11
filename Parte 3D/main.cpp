#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include <GL/freeglut.h>
//#include <GL/glut.h>

#include "MontañaRusa.h"
#include "Coche.h"
#include "Camara.h"

#include <iostream>

using namespace std;

// Freeglut parameters
// Flag telling us to keep processing events
// bool continue_in_main_loop= true; //(**)

// Viewport size
int WIDTH= 500, HEIGHT= 500;

// Viewing frustum parameters
GLdouble xRight = 10, xLeft = -xRight, yTop = 10, yBot = -yTop, N = 1, F = 1000;
GLdouble xRightIni = 10, xLeftIni = -xRightIni, yTopIni = 10, yBotIni = -yTop, NIni = 1, FIni = 1000;

// Camera parameters
GLdouble eyeX= 25.0, eyeY=25.0, eyeZ= 25.0;
GLdouble lookX=0.0, lookY=0.0, lookZ=0.0;
GLdouble upX=0, upY=1, upZ=0;

/*Variables globales para control por teclado.*/
GLfloat girox = 0.0;
GLfloat giroy = 0.0;
GLfloat giroz = 0.0;
GLfloat gradoGiro = 2.0;

GLfloat cocheMueve = 0.0;
GLfloat avanceCoche = 0.05;

GLdouble incDesp = 0.25;

GLdouble factorMas = 1.2;
GLdouble factorMenos = 0.8;

GLboolean muestraNormal = false;
GLboolean baldosas = false;
GLboolean dibujaMon = true, dibujaCoche = false;
GLboolean inCar = false;

/*Definimos los objetos.*/
MontañaRusa *mon;
//Coche *coche;
Camara* camara;


/*Llamamos a la constructoras de los objetos.*/
void buildSceneObjects() {
	mon = new MontañaRusa(100, 20, 1, 3, new Color("white"));
	cout << "Montaña Rusa: " << endl;
	cout << "Num vértices: " << mon->getNumVertices() << endl;
	cout << "Num caras: " << mon->getNumCaras() << endl;
	cout << "Num normales: " << mon->getNumNormales() << endl;
	cout << endl;

	/*coche = new Coche(0.5, 0.7, 0.7, new Color("purple"), new Color("blue"));
	cout << "Coche: " << endl;
	cout << "Num vértices: " << coche->getNumVertices() << endl;
	cout << "Num caras: " << coche->getNumCaras() << endl;
	cout << "Num normales: " << coche->getNumNormales() << endl;
	cout << endl;*/
}

//Dibuja los ejes de coordenadas.
void drawAxes() {
// Drawing axes
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0, 0, 0);
	glVertex3f(20, 0, 0);

	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 20, 0);

	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 20);
	glEnd();
}

//Método que dibuja los elementos de la escena.
void drawScene() {
	//Dibuja los ejes de la escena.
	drawAxes();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glRotatef(girox, 1.0, 0.0, 0.0);
	glRotatef(giroy, 0.0, 1.0, 0.0);
	glRotatef(giroz, 0.0, 0.0, 1.0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		if (dibujaMon)mon->dibuja();

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		GLfloat *m;
		/*if (dibujaCoche) {
			glPushMatrix();
			m = Curva::getFrenetVector(cocheMueve, 3);
			glMultMatrixf(m);

			coche->dibuja();
			glPopMatrix();
		}*/



	glPopMatrix();

}

//Metodo que gira los elementos de la vista de 4 perspectivas.
void gira(GLint i) {
	if (i == 0) {
		glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glRotatef(0 , 1.0, 0.0, 0.0);
			glRotatef(-45, 0.0, 1.0, 0.0);
			glRotatef(35, 0.0, 0.0, 1.0);
	}
	else if (i == 1) {
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glRotatef(-45, 1.0, 0.0, 0.0);
			glRotatef(35, 0.0, 1.0, 0.0);
			glRotatef(30, 0.0, 0.0, 1.0);

	}
	else if (i == 3) {
		glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glRotatef(180, 1.0, 0.0, 0.0);
			glRotatef(45, 0.0, 1.0, 0.0);
			glRotatef(235, 0.0, 0.0, 1.0);
	}
	else {
		glPushMatrix();
	}
	drawScene(); //Dibuja la escena
	glPopMatrix();
}

//Embaldosa la escena mostrando las vistas frontal, lateral, cenital y esquina.
void embaldosarCuatroVistas() {
	GLint nCol = 2;
	GLdouble SVAratio = (xRight - xLeft) / (yTop - yBot);
	GLdouble w = (GLdouble)WIDTH / (GLdouble)nCol;
	//La altura de cada puerto se calcula proporcionalmente
	GLdouble h = w / SVAratio;
	GLint cont = 0;
	for (GLint c = 0; c < nCol; c++) {
		GLdouble currentH = 0;
		while ((currentH) <= HEIGHT) {
			glViewport((GLint)(c*w), (GLint)currentH, (GLint)w, (GLint)h);
			gira(cont);
			currentH += h;
			cont++;
		}
	}
}

//Metodo que gira los elementos de la vista de 4 perspectivas.
void estereoscopica(GLint i) {
	if (i == 0) {
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
	}
	else if (i == 1) {
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(0.0, 0.0, 0.25);
	}
	drawScene(); //Dibuja la escena
	glPopMatrix();
}

//Embaldosa la escena mostrando las vistas frontal, lateral, cenital y esquina.
void embaldosarDosVistas() {
	GLint nCol = 2;
	GLdouble SVAratio = (xRight - xLeft) / (yTop - yBot);
	GLdouble w = (GLdouble)WIDTH / (GLdouble)nCol;
	//La altura de cada puerto se calcula proporcionalmente
	GLdouble h = w / SVAratio;
	GLint cont = 0;
	for (GLint c = 0; c < nCol; c++) {
		glViewport((GLint)(c*w), (GLint)yTop - yBot, (GLint)w, (GLint)HEIGHT);
		estereoscopica(cont);
		cont++;
	}
}


//Desembaldosa la escena.
void desembaldosar() {
	glViewport(0, 0, WIDTH, HEIGHT);
	drawScene();
}

/*Establece la luz.*/
void setLight() {
	// Light0
	glEnable(GL_LIGHT0);
	GLfloat d[] = { 1.0,1.0,1.0,1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, d);
	GLfloat a[] = { 0.3f,0.3f,0.3f,1.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, a);
	GLfloat p[] = { -25.0, 25.0, 25.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, p);
}

void initGL() {	 		 
	glClearColor(0.6f,0.7f,0.8f,1.0);
    glEnable(GL_LIGHTING);    

	glEnable(GL_COLOR_MATERIAL);
	glMaterialf(GL_FRONT, GL_SHININESS, 0.1f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);

	buildSceneObjects();

	// Camera set up
	PV3D* eye = new PV3D(eyeX, eyeY, eyeZ, 1);
	PV3D* look = new PV3D(lookX, lookY, lookZ, 0);
	PV3D* up = new PV3D(upX, upY, upZ, 0);

	camara = new Camara(eye, look, up, xLeft, xRight, yBot, yTop, N, F);
	// Viewport set up
    glViewport(0, 0, WIDTH, HEIGHT);  

	setLight();
	glDisable(GL_CULL_FACE);
 }

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
	
	/*Espacio de trabajo.*/
	
	if (baldosas) embaldosarCuatroVistas();
	else desembaldosar();

	/*Fin de espacio de trabajo.*/

	glFlush();
	glutSwapBuffers();
}

/*Zoom progresiuvo.*/
void zoomProgresivo(GLint nIter, GLfloat f) {
	/*Calculamos los puntos medios de cada eje.*/
	GLdouble yMiddle = (yBot + yTop) / 2.0;
	GLdouble xMiddle = (xLeft + xRight) / 2.0;
	/*Calculamos el incremento de cada iteración.*/
	GLdouble fIncr = (f - 1) / (GLdouble)nIter;
	/*Calculamos altura y anchura del puerto de vista.*/
	GLdouble SVAWidth = xRight - xLeft;
	GLdouble SVAHeight = yTop - yBot;
	/*Calculamos el zoom gradualmente.*/
	for (int i = 0; i <= nIter; i++) {
		GLdouble fAux = 1 + fIncr*i;
		GLdouble newWidth = SVAWidth / fAux;
		GLdouble newHeight = SVAHeight / fAux;
		yTop = yMiddle + newHeight / 2.0;
		yBot = yMiddle - newHeight / 2.0;
		xRight = xMiddle + newWidth / 2.0;
		xLeft = xMiddle - newWidth / 2.0;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		if(!camara->isPerspectiva())
			glOrtho(xMiddle - newWidth / 2.0, xMiddle + newWidth / 2.0, yMiddle - newHeight / 2.0, yMiddle + newHeight / 2.0, N, F);
		else
			glFrustum(xMiddle - newWidth / 2.0, xMiddle + newWidth / 2.0, yMiddle - newHeight / 2.0, yMiddle + newHeight / 2.0, N, F);
		display(); //glutPostRedisplay(); no funciona!
		/*Solo dormimos al final, para que no pare al mantener el botón pulsado.*/
		if(nIter != i) Sleep(50);
	}
}

void resize(int newWidth, int newHeight) {
	WIDTH= newWidth;
	HEIGHT= newHeight;
	GLdouble RatioViewPort= (float)WIDTH/(float)HEIGHT;
	glViewport (0, 0, WIDTH, HEIGHT) ;
   
	GLdouble SVAWidth= xRight-xLeft;
	GLdouble SVAHeight= yTop-yBot;
	GLdouble SVARatio= SVAWidth/SVAHeight;
	if (SVARatio >= RatioViewPort) {		 
		GLdouble newHeight= SVAWidth/RatioViewPort;
		GLdouble yMiddle= ( yBot+yTop )/2.0;
		yTop= yMiddle + newHeight/2.0;
		yBot= yMiddle - newHeight/2.0;
    }
	else {      
		GLdouble newWidth= SVAHeight*RatioViewPort;
		GLdouble xMiddle= ( xLeft+xRight )/2.0;
		xRight= xMiddle + newWidth/2.0;
		xLeft=  xMiddle - newWidth/2.0;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();   
	if (!camara->isPerspectiva())
		glOrtho(xLeft, xRight, yBot, yTop, N, F);
	else
		glFrustum(xLeft, xRight, yBot, yTop, N, F);
}

/*Método key para teclas normales.*/ 
void key(unsigned char key, int x, int y) {
	bool need_redisplay = true;
	switch (key) {
	case 27:  /* Escape key */
			  //continue_in_main_loop = false; // (**)
			  //Freeglut's sentence for stopping glut's main loop (*)
		glutLeaveMainLoop();
		break;

	case 'a':
		girox += gradoGiro;
		break;
	case 'z':
		girox -= gradoGiro;
		break;
	case 's':
		giroy += gradoGiro;
		break;
	case 'x':
		giroy -= gradoGiro;
		break;
	case 'd':
		giroz += gradoGiro;
		break;
	case 'c':
		giroz -= gradoGiro;
		break;
	case 'l':
		camara->updateFrustumValues(xLeft, xRight, yBot, yTop, N, F);
		camara->cambioProyeccion();
		setLight();
		break;
	case 'u':
		if (!baldosas) {
			camara->roll("neg");
			setLight();
		}
		break;
	case 'i':
		if (!baldosas) {
			camara->roll("pos");
			setLight();
		}
		break;
	case 'j':
		if (!baldosas) {
			camara->yaw("neg");
			setLight();
		}
		break;
	case 'k':
		if (!baldosas) {
			camara->yaw("pos");
			setLight();
		}
		break;
	case 'n':
		if (!baldosas) {
			camara->pitch("neg");
			setLight();
		}
		break;
	case 'm':
		if (!baldosas) {
			camara->pitch("pos");
			setLight();
		}
		break;
	case 'o':
		baldosas = false;
		break;
	case 'p':
		baldosas = true;
		camara->vistaEsquina();
		setLight();
		break;
	case 't':
		zoomProgresivo(3, factorMenos);
		break;
	case 'y':
		zoomProgresivo(3, factorMas);
		break;
	case 'e':
		if (!baldosas) {
			camara->translateX("neg");
			setLight();
		}
		break;
	case 'r':
		if (!baldosas) {
			camara->translateX("pos");
			setLight();
		}
		break;
	case 'f':
		if (!baldosas) {
			camara->translateY("neg");
			setLight();
		}
		break;
	case 'g':
		if (!baldosas) {
			camara->translateY("pos");
			setLight();
		}
		break;
	case 'v':
		if (!baldosas) {
			camara->translateZ("neg");
			setLight();
		}
		break;
	case 'b':
		if (!baldosas) {
				camara->translateZ("pos");
				setLight();
		}
		break;

	case 'q':
		camara->mueveConCoche(cocheMueve, 3);
		if(!inCar) {
			zoomProgresivo(3, factorMas*12);
			inCar = true;
		}
		setLight();

		cocheMueve += avanceCoche;
		if (cocheMueve >= 2 * PI)
			cocheMueve = 0;
		break;
	case 'w':
		camara->mueveConCoche(cocheMueve, 3);
		setLight();
		cocheMueve -= avanceCoche / 2;
		if (cocheMueve <= -2 * PI)
			cocheMueve = 0;
		break;
	case '1':
		if (!baldosas) {
			camara->giraX("pos");
			setLight();
		}
		break;
	case '2':
		if (!baldosas) {
			camara->giraY("pos");
			setLight();
		}
		break;
	case '3':
		if (!baldosas) {
			camara->giraZ("pos");
			setLight();
		}
		break;

	case '4':
		if (!baldosas) {
			camara->vistaLateral();
			setLight();
		}
		break;
	case '5':
		if (!baldosas) {
			camara->vistaFrontal();
			setLight();
		}
		break;
	case '6':
		if (!baldosas) {
			camara->vistaCenital();
			setLight();
		}
		break;
	case '7':
		if (!baldosas) {
			camara->vistaEsquina();
			setLight();
		}
		break;

	default:
		need_redisplay = false;
		break;
	}
	if (need_redisplay)
		glutPostRedisplay();
}

/*Metodo key para teclas especiales.*/
void key(int key, int x, int y){
	bool need_redisplay = true;
	switch (key) {
		case 27:  /* Escape key */
			//continue_in_main_loop = false; // (**)
			//Freeglut's sentence for stopping glut's main loop (*)
			glutLeaveMainLoop (); 
			break;
		case GLUT_KEY_UP:
			yTop -= incDesp;
			yBot -= incDesp;
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			if (!camara->isPerspectiva())
				glOrtho(xLeft, xRight, yBot, yTop, N, F);
			else
				glFrustum(xLeft, xRight, yBot, yTop, N, F);
			break;
		case GLUT_KEY_DOWN:
			yTop += incDesp;
			yBot += incDesp;
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			if (!camara->isPerspectiva())
				glOrtho(xLeft, xRight, yBot, yTop, N, F);
			else
				glFrustum(xLeft, xRight, yBot, yTop, N, F);
			break;
		case GLUT_KEY_LEFT:
			xLeft += incDesp;
			xRight += incDesp;
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			if (!camara->isPerspectiva())
				glOrtho(xLeft, xRight, yBot, yTop, N, F);
			else
				glFrustum(xLeft, xRight, yBot, yTop, N, F);
			break;
		case GLUT_KEY_RIGHT:
			xLeft -= incDesp;
			xRight -= incDesp;
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			if (!camara->isPerspectiva())
				glOrtho(xLeft, xRight, yBot, yTop, N, F);
			else
				glFrustum(xLeft, xRight, yBot, yTop, N, F);
			break;
		default:
			need_redisplay = false;
			break;
	}

	if (need_redisplay)
		glutPostRedisplay();
}

int main(int argc, char *argv[]){
	cout<< "Starting console..." << endl;

	int my_window; // my window's identifier

	// Initialization
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition (140, 140);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInit(&argc, argv);

	// Window construction
	my_window = glutCreateWindow("Freeglut 3D-project");
    
	// Callback registration
	glutReshapeFunc(resize);
	glutSpecialFunc(key);
	glutKeyboardFunc(key);
	glutDisplayFunc(display);

	// OpenGL basic setting
	initGL();

	// Freeglut's main loop can be stopped executing (**)
	// while (continue_in_main_loop) glutMainLoopEvent();

	// Classic glut's main loop can be stopped after X-closing the window,
	// using the following freeglut's setting (*)
	glutSetOption (GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION) ;

	// Classic glut's main loop can be stopped in freeglut using (*)
	glutMainLoop(); 

	// We would never reach this point using classic glut
	system("PAUSE"); 
   
	return 0;
}
