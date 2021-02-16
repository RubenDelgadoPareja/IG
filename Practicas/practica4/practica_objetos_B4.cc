//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <GL/glut.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include "objetos_B4.h"



using namespace std;

// tipos
/*typedef enum{CUBO, PIRAMIDE, OBJETO_PLY, ROTACION} _tipo_objeto;
_tipo_objeto t_objeto=CUBO;
_modo   modo=POINTS; */
Objeto obj = Piramide;
Modo mod = Lineas;
Material mat = Null;




// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Size_x,Size_y,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int Window_x=50,Window_y=50,Window_width=450,Window_high=450;

//variables 
bool animacion = false;
bool a_brazo = true;
bool a_cuerda = true;
bool a_bola = true;
bool oro = false;
bool esm = false;

double vel_cabina = 5;
double vel_brazo = 5;
double vel_cuerda = 5;
double vel_bola = 5;


// objetos
bool direccional_activada = false;
bool focal_activada = false;
_cubo cubo(0.2);
_piramide piramide(0.85,1.3);
_cilindro cilindro;
_cono cono;
_esfera esfera;
_objeto_ply  ply; 
_rotacion rotacion; 
_rotacion_ply rotacion_ply;
_extra extra;
_chasis chasis;
_cabina cabina;
_brazo brazo;
_bola bola;
_demoledor demoledor;
_luz direccional(GL_LIGHT0, _vertex4f(0,10,0,0), _vertex4f(0.0,0.0,0.0,1), _vertex4f(1.0,1.0,0.0,1), _vertex4f(1.0,1.0,1.0,1));
_luz focal(GL_LIGHT1, _vertex4f(2,0,1,1), _vertex4f(0.1,0.0,0.0,1), _vertex4f(1.0,0,1,1), _vertex4f(1.0,1.4,0.4,1));
_tablero tablero;



// _objeto_ply *ply1;


//**************************************************************************
//
//***************************************************************************
void animacion_luces(){
	focal.b = 1;
	focal.angy += 0.005;
	glutPostRedisplay();
	
}
void funcion_idle(){}
void funcion_animacion(){
	demoledor.giro_cabina+=0.005;

	if(a_brazo)
		demoledor.giro_brazo+=0.005;
	else
		demoledor.giro_brazo-=0.005;

	if(demoledor.giro_brazo >= demoledor.giro_brazo_max){
		demoledor.giro_brazo = demoledor.giro_brazo_max;
		a_brazo = false;
	}
	else if(demoledor.giro_brazo <= demoledor.giro_brazo_min){
		demoledor.giro_brazo = demoledor.giro_brazo_min;
		a_brazo = true;
	}

	if(a_cuerda)
		demoledor.giro_cuerda+=0.005;
	else
		demoledor.giro_cuerda-=0.005;

	if(demoledor.giro_cuerda >= demoledor.giro_cuerda_max){
		demoledor.giro_cuerda = demoledor.giro_cuerda_max;
		a_cuerda = false;
	}
	else if(demoledor.giro_cuerda <= demoledor.giro_cuerda_min){
		demoledor.giro_cuerda = demoledor.giro_cuerda_min;
		a_cuerda = true;
	}

	if(a_bola)
		demoledor.giro_bola+=0.005;
	else
		demoledor.giro_bola-=0.005;
	
	if(demoledor.giro_bola >= demoledor.giro_bola_max){
		demoledor.giro_bola = demoledor.giro_bola_max;
		a_bola = false;
	}
	else if(demoledor.giro_bola <= demoledor.giro_bola_min){
		demoledor.giro_bola = demoledor.giro_bola_min;
		a_bola = true;
	}
	glutPostRedisplay();
}

void clean_window()
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

glMatrixMode(GL_PROJECTION);
glLoadIdentity();

// formato(x_minimo,x_maximo, y_minimo, y_maximo,plano_delantero, plano_traser)
//  plano_delantero>0  plano_trasero>PlanoDelantero)
glFrustum(-Size_x,Size_x,-Size_y,Size_y,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación*ply1 de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
	
glDisable(GL_LIGHTING);
glLineWidth(2);
glBegin(GL_LINES);
// eje X, color rojo
glColor3f(1,0,0);
glVertex3f(-AXIS_SIZE,0,0);
glVertex3f(AXIS_SIZE,0,0);
// eje Y, color verde
glColor3f(0,1,0);
glVertex3f(0,-AXIS_SIZE,0);
glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
glColor3f(0,0,1);
glVertex3f(0,0,-AXIS_SIZE);
glVertex3f(0,0,AXIS_SIZE);
glEnd();
}


//**************************************************************************
// Funcion que dibuja los objetos
//****************************2***********************************************

void draw_objects()
{
switch (obj){
	case Cubo: cubo.draw(mod,1.0,0.0,0.0,0.0,1.0,0.0,2, mat);break;
	case Piramide: piramide.draw(mod,1.0,0.0,0.0,0.0,1.0,0.0,2, mat);break;
    case Objeto_ply: ply.draw(mod,1.0,0.6,0.0,0.0,1.0,0.3,2, mat);break;
    case Rotacion: rotacion.draw(mod,1.0,0.0,0.0,0.0,1.0,0.0,2, mat);break;
	case Cilindro: cilindro.draw(mod,1.0,0.0,0.0,0.0,1.0,0.0,2, mat);break;
	case Cono: cono.draw(mod,1.0,0.0,0.0,0.0,1.0,0.0,2, mat);break;
	case Esfera: esfera.draw(mod,1.0,0.0,0.0,0.0,1.0,0.0,2,mat);break;
	case RotacionPly: rotacion_ply.draw(mod,1.0,0.0,0.0,0.0,1.0,0.0,2, mat);break;
	case Extra: extra.draw(mod,1.0,0.0,0.0,0.0,1.0,0.0,2, mat);break;
	case Articulado: demoledor.draw(mod,1.0,0.0,0.0,0.0,1.0,0.0,2, mat);break;
	case Tablero: tablero.draw(mod,1.0,0.0,0.0,0.0,1.0,0.0,2, mat);break;
	}

	if(focal_activada && direccional_activada && animacion)
		glutIdleFunc(animacion_luces);
	else if(animacion)
		glutIdleFunc(funcion_animacion);
	
	else
		glutIdleFunc(funcion_idle);

}


//**************************************************************************
//
//***************************************************************************

void draw(void)
{

clean_window();
if(direccional_activada)
	direccional.activar();
if(focal_activada){
	focal.transformar(focal.indice_luz, focal.a, focal.b, focal.c, focal.angy, focal.pos_x, focal.pos_y, focal.pos_z);
}

change_observer();
draw_axis();
draw_objects();
glutSwapBuffers();
}



//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
float Aspect_ratio;

Aspect_ratio=(float) Alto1/(float )Ancho1;
Size_y=Size_x*Aspect_ratio;
change_projection();
glViewport(0,0,Ancho1,Alto1);
glutPostRedisplay();
}


//**********-o*****************************************************************
// Funcion llamada cuando se aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_key(unsigned char Tecla1,int x,int y)
{
switch (toupper(Tecla1)){
	case 'Q':exit(0);
	case '1':obj=Piramide;break;
	case '2':obj=Cubo;break;
	case '3':obj=Cono;break;
	case '4':obj=Cilindro;break;
    case '5':obj=Esfera;break;
	case '6':obj=Objeto_ply;break;
	case '7':obj=Rotacion;break;
	case '8':obj=RotacionPly;break;
	case '9':obj=Extra;break;
	case '0':obj=Articulado;break;
	case 'D':obj=Tablero;break;
    case 'P':mod=Puntos;break;
    case 'L':mod=Lineas;break;	
    case 'F':mod=Solido;break;
	case 'C':mod=Ajedrez;break;
	case 'W':mod=Solido_Iluminado_Plano;break;
	case 'O':mod=Solido_Iluminado_Gouraud;break;
	case 'J':if(!esm){ mat=Esmeralda; esm = true;}else{ mat=Null; esm=false;}break;
	case 'K':if(!oro){ mat=Oro; oro = true;}else{ mat=Null; oro=false;}break;
	case 'S':mod=Texturas;break;
	case 'Z':direccional.activar();direccional_activada=true;break;
	case 'X':direccional.desactivar();direccional_activada=false;break;
	case 'N':focal.activar();focal_activada=true;break;
	case 'M':focal.desactivar();focal_activada=false;break;
	case 'E': vel_cabina += 1;break;
	case 'R': vel_cabina -= 1;break;
	case 'T': vel_brazo += 1;break;
	case 'Y': vel_brazo -= 1;break;
	case 'U': vel_cuerda +=1;break;
	case 'I': vel_cuerda -=1;break;
	case 'G': vel_bola += 1;break;
	case 'H': vel_bola -= 1;break;
	case 'A': if(!animacion){
				animacion =true;
			}
			else{
				animacion = false;
			}
			break;
	}
glutPostRedisplay();
}

//***************************************************************************
// Funcion l-olamada cuando se aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_key(int Tecla1,int x,int y)
{

switch (Tecla1){
	case GLUT_KEY_LEFT:Observer_angle_y--;break;
	case GLUT_KEY_RIGHT:Observer_angle_y++;break;
	case GLUT_KEY_UP:Observer_angle_x--;break;
	case GLUT_KEY_DOWN:Observer_angle_x++;break;
	case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
	case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
	case GLUT_KEY_F1:demoledor.giro_cabina+=vel_cabina;break;
	case GLUT_KEY_F2:demoledor.giro_cabina-=vel_cabina;break;
	case GLUT_KEY_F3:demoledor.giro_brazo+=vel_brazo;
		if(demoledor.giro_brazo > demoledor.giro_brazo_max) demoledor.giro_brazo= demoledor.giro_brazo_max;
		break;
	case GLUT_KEY_F4:demoledor.giro_brazo-=vel_brazo;
		if(demoledor.giro_brazo < demoledor.giro_brazo_min) demoledor.giro_brazo= demoledor.giro_brazo_min;
		break;	
	case GLUT_KEY_F5:demoledor.giro_cuerda+=vel_cuerda;
		if(demoledor.giro_cuerda > demoledor.giro_cuerda_max) demoledor.giro_cuerda= demoledor.giro_cuerda_max;
		break;
	case GLUT_KEY_F6:demoledor.giro_cuerda-=vel_cuerda;
		if(demoledor.giro_cuerda < demoledor.giro_cuerda_min) demoledor.giro_cuerda= demoledor.giro_cuerda_min;
		break;
	case GLUT_KEY_F7:demoledor.giro_bola+=vel_bola;
		if(demoledor.giro_bola > demoledor.giro_bola_max) demoledor.giro_bola = demoledor.giro_bola_max;
		break;
	case GLUT_KEY_F8:demoledor.giro_bola-=vel_bola;
		if(demoledor.giro_bola < demoledor.giro_bola_min) demoledor.giro_bola = demoledor.giro_bola_min;
		break;	
	}
glutPostRedisplay();
}



//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{

// se inicalizan la ventana y los planos de corte
Size_x=0.5;
Size_y=0.5;
Front_plane=1;
Back_plane=1000;

// se incia la posicion del observador, en el eje z
Observer_distance=4*Front_plane;
Observer_angle_x=0;
Observer_angle_y=0;

// se indica cua*ply1l sera el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClearColor(1,1,1,1);

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
change_projection();
glViewport(0,0,Window_width,Window_high);



}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************


int main(int argc, char *argv[] )
{
 



// perfil 

vector<_vertex3f> perfil2;
_vertex3f aux;
//Perfil de un peon

aux.x=0.5; aux.y=2; aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.4; aux.y=1.75; aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.35; aux.y=1.5; aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.4; aux.y=1.25; aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.75; aux.y=1; aux.z=0.0;
perfil2.push_back(aux);
aux.x=1; aux.y=0.75; aux.z=0.0;
perfil2.push_back(aux);
aux.x=1.1; aux.y=0.5; aux.z=0.0;
perfil2.push_back(aux);
aux.x=1; aux.y=0.25; aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.5; aux.y=0.0; aux.z=0.0;
perfil2.push_back(aux);




rotacion.parametros(perfil2,6,2);

rotacion_ply.parametros(argv[2]);

extra.parametros(1,20);

//cilindro.rotacion();

// generamos el cono

//cono.rotacion();

// generamos la esfera

//esfera.rotacion();



// se llama a la inicialización de glut
glutInit(&argc, argv);

// se indica las caracteristicas que se desean para la visualización con OpenGL
// Las posibilidades son:
// GLUT_SIMPLE -> memoria de imagen simple
// GLUT_DOUBLE -> memoria de imagen doble
// GLUT_INDEX -> memoria de imagen con color indizado
// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
// GLUT_DEPTH -> memoria de profundidad o z-bufer
// GLUT_STENCIL -> memoria de estarcido_rotation Rotation;
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

// posicion de la esquina inferior izquierdad de la ventana
glutInitWindowPosition(Window_x,Window_y);

// tamaño de la ventana (ancho y alto)
glutInitWindowSize(Window_width,Window_high);

// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
// al bucle de eventos)
glutCreateWindow("PRACTICA - 2");

// asignación de la funcion llamada "dibujar" al evento de dibujo
glutDisplayFunc(draw);
// asignación de la funcion llamada "change_window_size" al evento correspondiente
glutReshapeFunc(change_window_size);
// asignación de la funcion llamada "normal_key" al evento correspondiente
glutKeyboardFunc(normal_key);
// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
glutSpecialFunc(special_key);


// funcion de inicialización
initialize();

// creación del objeto ply
ply.parametros(argv[1]);

//ply1 = new _objeto_ply(argv[1]);




// inicio del bucle de eventos
glutMainLoop();
return 0;
}
