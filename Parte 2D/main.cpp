#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include <GL/freeglut.h>
//#include <GL/glut.h>

#include "RectanguloAureo.h"
#include "Color.h"
#include "Pentagono.h"

#include <iostream>
using namespace std;

// Freeglut parameters
// Flag telling us to keep processing events
// bool continue_in_main_loop= true; //(**)

// Viewport size
int WIDTH= 500, HEIGHT= 250;

// Scene visible area size
GLdouble xLeft= 0.0, xRight= 500.0, yBot= 0.0, yTop= 250.0;

// Scene variables
//GLdouble xTriangle= 100.0, yTriangle= 100.0;
//GLdouble triangleWidth= 100.0, triangleHeight= 50.0;


//Variables de objetos y condiciones.
Pentagono* pentagono;
GLboolean embaldosa = false;
GLdouble incDesp = 1;

void buildSceneObjects();
void drawScene();
void changeCenter(PV2D* newCenter, GLfloat nuevaAltura);
void embaldosar();
void desembaldosar();
void display(void);
void zoomProgresivo(GLint nIter, GLfloat f);
void intitGL();
void resize(int newWidth, int newHeight);

/*Método que construye los objetos.*/
void buildSceneObjects() {
	pentagono = new Pentagono(100, new PV2D(xLeft + 0.42*(xRight - xLeft), yBot + 0.85*(yTop - yBot)));
	changeCenter(pentagono->getCentro(), 2*pentagono->getRadio() + 0.1*pentagono->getRadio());
}

/*Método que dibuja la escena.*/
void drawScene() {
	pentagono->dibuja();
}

/*Método que establece un nuevo centro.*/
void changeCenter(PV2D* newCenter, GLfloat nuevaAltura) {
	/*Calculamos la nueva anchura, a partir de la nueva altura.*/
	GLdouble nuevaAnchura = (xRight - xLeft) * nuevaAltura / (yTop - yBot);
	/*Modificamos los parámetros para que sea centrado.*/
	yTop = newCenter->getY() + nuevaAltura / 2;
	yBot = newCenter->getY() - nuevaAltura / 2;
	xRight = newCenter->getX() + nuevaAnchura / 2;
	xLeft = newCenter->getX() - nuevaAnchura / 2;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(xLeft, xRight, yBot, yTop);
}





//Embaldosa la escena mostrando las vistas frontal, lateral, cenital y esquina.
void embaldosar() {
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
			drawScene();
			currentH += h;
			cont++;
		}
	}
}

//Desembaldosa la escena.
void desembaldosar() {
	glViewport(0, 0, WIDTH, HEIGHT);
	drawScene();
}




void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	// Scene rendering
	/*glBegin ( GL_TRIANGLES ) ;
	glVertex2d( xTriangle, yTriangle );
	glVertex2d( xTriangle + triangleWidth, yTriangle );
	glVertex2d( xTriangle + triangleWidth, yTriangle + triangleHeight );
	glEnd () ;*/

	if (embaldosa)embaldosar();
	else desembaldosar();

	glFlush();
	glutSwapBuffers();
}

/*Hace un zoom de manera progresiva, mas suave.*/
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
		gluOrtho2D(xMiddle - newWidth / 2.0, xMiddle + newWidth / 2.0, yMiddle - newHeight / 2.0, yMiddle + newHeight / 2.0);
		display(); //glutPostRedisplay(); no funciona!
		/*Solo dormimos al final, para que no pare al mantener el botón pulsado.*/
		if (nIter != i) Sleep(50);
	}
}





/*Método init.*/
void intitGL(){

	glClearColor(1.0,1.0,1.0,1.0);
	glColor3f(1.0,0.0,0.0); 

	glPointSize(4.0);
	glLineWidth(2.0);

	buildSceneObjects();

	// Viewport
    glViewport(0, 0, WIDTH, HEIGHT);
    
	// Model transformation
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Scene Visible Area
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(xLeft, xRight, yBot, yTop); 
 }

/*Método resize.*/
void resize(int newWidth, int newHeight){
  //Resize Viewport
  WIDTH= newWidth;
  HEIGHT= newHeight;
  GLdouble RatioViewPort= (float)WIDTH/(float)HEIGHT;
  glViewport ( 0, 0, WIDTH, HEIGHT ) ;
  
  //Resize Scene Visible Area 
  //Se actualiza el área visible de la escena
  //para que su ratio coincida con ratioViewPort
  GLdouble SVAWidth= xRight-xLeft;
  GLdouble SVAHeight= yTop-yBot;
  GLdouble SVARatio= SVAWidth/SVAHeight;
  if (SVARatio >= RatioViewPort) {
	 // Increase SVAHeight
     GLdouble newHeight= SVAWidth/RatioViewPort;
	 GLdouble yMiddle= ( yBot+yTop )/2.0;
     yTop= yMiddle + newHeight/2.0;
     yBot= yMiddle - newHeight/2.0;
     }
  else {
     //Increase SVAWidth
     GLdouble newWidth= SVAHeight*RatioViewPort;
     GLdouble xMiddle= ( xLeft+xRight )/2.0;
	 xRight= xMiddle + newWidth/2.0;
     xLeft=  xMiddle - newWidth/2.0;
  }

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(xLeft, xRight, yBot, yTop);
}





/*Método key.*/
void key(unsigned char key, int x, int y){
 
  bool need_redisplay = true;

  switch (key) {
  case 27:  /* Escape key */
    //continue_in_main_loop = false; // (**)
	glutLeaveMainLoop (); //Freeglut's sentence for stopping glut's main loop (*)
    break;
  case 'a':
	  pentagono->nuevaEstrella();
	  break;
  case 'b':
	  pentagono->quitaEstrella();
	  break;
  case'f':
	  embaldosa = true;
	  break;
  case'v':
	  embaldosa = false;
	  break;
  case't':
	  zoomProgresivo(3, 0.8);
	  break;
  case'y':
	  zoomProgresivo(3, 1.2);
	  break;
  default:
    need_redisplay = false;
    break;
  }//switch

  if (need_redisplay)
    glutPostRedisplay();
}

/*Metodo key para teclas especiales.*/
void key(int key, int x, int y) {
	bool need_redisplay = true;
	switch (key) {
	case 27:  /* Escape key */
			  //continue_in_main_loop = false; // (**)
			  //Freeglut's sentence for stopping glut's main loop (*)
		glutLeaveMainLoop();
		break;
	case GLUT_KEY_UP:
		yTop -= incDesp;
		yBot -= incDesp;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(xLeft, xRight, yBot, yTop);
		break;
	case GLUT_KEY_DOWN:
		yTop += incDesp;
		yBot += incDesp;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(xLeft, xRight, yBot, yTop);
		break;
	case GLUT_KEY_LEFT:
		xLeft += incDesp;
		xRight += incDesp;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(xLeft, xRight, yBot, yTop);
		break;
	case GLUT_KEY_RIGHT:
		xLeft -= incDesp;
		xRight -= incDesp;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(xLeft, xRight, yBot, yTop);
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

  int my_window; //my window's identifier

  //Initialization
  glutInitWindowSize(WIDTH, HEIGHT);
  glutInitWindowPosition (140, 140);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE );
  glutInit(&argc, argv);

  //Window construction
  my_window = glutCreateWindow( "Freeglut 2D-project" );
    
  // Callback registration
  glutReshapeFunc(resize);
  glutSpecialFunc(key);
  glutKeyboardFunc(key);
  glutDisplayFunc(display);

  //OpenGL basic setting
  intitGL();


  // Freeglut's main loop can be stopped executing (**)
  //while ( continue_in_main_loop )
  //  glutMainLoopEvent();

  // Classic glut's main loop can be stopped after X-closing the window,
  // using the following freeglut's setting (*)
  glutSetOption ( GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION ) ;
    
  // Classic glut's main loop can be stopped in freeglut using (*)
  glutMainLoop(); 
  
  // We would never reach this point using classic glut
  system("PAUSE"); 
   
  return 0;
}
