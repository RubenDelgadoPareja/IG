//**************************************************************************
// Práctica 1
//
//
// GPL
//**************************************************************************

#include "stdlib.h"
#include "stdio.h"
#include <GL/glut.h>
#include <ctype.h>
#include "objetos_B5.h"

// tamaño de los ejes
const int AXIS_SIZE=5000;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width,Window_height,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int UI_window_pos_x=50,UI_window_pos_y=50,UI_window_width=450,UI_window_height=450;

int estadoRaton[3], xc, yc, modo[10], cambio=0;

enum Camara{Normal, Ortogonal};
Camara cam = Normal;

solido *cilindro1, *cilindro2, *cubo1, *cilindro3, *cubo2, *triangulo1, *cono1, *cono2, *cuerda, *bola;

int Ancho=450, Alto=450;
float factor=1.0;


double vel_cabina = 5;
double vel_brazo = 5;
double vel_cuerda = 5;
double vel_bola = 5;
float   giro_cabina = 0;
float 	giro_brazo = 0;
float 	giro_brazo_min = 0;
float 	giro_brazo_max = 10;
float 	giro_cuerda = 0;
float 	giro_cuerda_max = 20;
float 	giro_cuerda_min = -10;
float 	giro_bola = 0;
float 	giro_bola_min = -20;
float 	giro_bola_max = 20;


float last_xn ;

void pick_color(int x, int y);

//**************************************************************************
//
//***************************************************************************

void clear_window()
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

// formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
//  Front_plane>0  Back_plane>PlanoDelantero)
glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

// posicion del observador
change_projection();
glViewport(0,0,Ancho,Alto);
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
glLineWidth(1);
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
//***************************************************************************

void draw_objects()
{

  glPushMatrix();
	  //MATRIZ DEL CHASIS
  	glPushMatrix();
		 glPushMatrix();
		 glScalef(1,0.3,1);
		 glTranslatef(0,1,0);
		 draw_solido(cubo1,0.1,0.1,0.1,1);
  	   draw_solido(cubo1,cubo1->r,cubo1->g,cubo1->b,2);
		 glPopMatrix();

  	   glPushMatrix(); 
  	   glTranslatef(-1,0.3,-1);
		 glRotatef(90,1,0,0);
  	   draw_solido(cilindro1,0.1,0.1,0.1,1);
  	   draw_solido(cilindro1,cilindro1->r,cilindro1->g,cilindro1->b,2);
  	   glPopMatrix();         

  	   glPushMatrix(); 
  	   glTranslatef(1,0.3,-1);
		 glRotatef(90,1,0,0);
  	   draw_solido(cilindro2,0.1,0.1,0.1,1);
  	   draw_solido(cilindro2,cilindro2->r,cilindro2->g,cilindro2->b,2);
  	   glPopMatrix(); 
  	 glPopMatrix();   

	//MATRIZ DE LA CABINA
	glPushMatrix();
		glRotatef(giro_cabina,0,1,0);
		glPushMatrix();
			glTranslatef(0,0.6,0);
			glPushMatrix();
				draw_solido(cilindro3,0.1,0.1,0.1,1);
  		  	 	draw_solido(cilindro3,cilindro3->r,cilindro3->g,cilindro3->b,2);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0,0.75,0);
				draw_solido(cubo2,0.1,0.1,0.1,1);
  		   		draw_solido(cubo2,cubo2->r,cubo2->g,cubo2->b,2);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0,1.25,0);
				draw_solido(triangulo1,0.1,0.1,0.1,1);
  		   		draw_solido(triangulo1,triangulo1->r,triangulo1->g,triangulo1->b,2);
			glPopMatrix();
		glPopMatrix();

		//MATRIZ DE LOS BRAZOS
		glPushMatrix();
			glRotatef(giro_brazo,0,0,1);
			glPushMatrix();
				glTranslatef(0.5,0.6,0);
				glPushMatrix();
					glTranslatef(0,0,-0.25);
					glRotatef(-45,0,0,1);
					glRotatef(6,1,0,0);
					draw_solido(cono1,0.1,0.1,0.1,1);
					draw_solido(cono1,cono1->r,cono1->g,cono1->b,2);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(0,0,+0.25);
					glRotatef(-45,0,0,1);
					glRotatef(-6,1,0,0);
					draw_solido(cono2,0.1,0.1,0.1,1);
					draw_solido(cono2,cono2->r,cono2->g,cono2->b,2);
				glPopMatrix();
			glPopMatrix();

			//MATRIZ DE LA CUERDA Y LA BOLa
			glPushMatrix();
				glTranslatef(2.15,2.3,0);
				glPushMatrix();
					glRotatef(giro_cuerda,0,0,1);
					glPushMatrix();
						glTranslatef(0,-2,0);
						draw_solido(cuerda,0.1,0.1,0.1,1);
						draw_solido(cuerda,cuerda->r,cuerda->g,cuerda->b,2);
					glPopMatrix();
					glPushMatrix();
						glTranslatef(0,-1.75,0);
						glPushMatrix();
							glRotatef(giro_bola,0,0,1);
							glTranslatef(0,-0.25,0);
							draw_solido(bola,0.1,0.1,0.1,1);
							draw_solido(bola,bola->r,bola->g,bola->b,2);
						glPopMatrix();
					glPopMatrix();
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
   glPopMatrix();

}

//**************************************************************************
// Funcion que dibuja los objetos en el buffer trasero
//**********************************************************q****************


void draw_objects_seleccion()
{
int inc=0;

		// CHASIS
   		glPushMatrix();    
			 glPushMatrix();
			 glScalef(1,0.3,1);
			 glTranslatef(0,1,0);
   		 	 draw_seleccion_color(cubo1,100,100,100);
			 inc+=10;
			 glPopMatrix();
   		  glPushMatrix(); 
   		  glTranslatef(-1,0.3,-1);
			 glRotatef(90,1,0,0);
   		  	draw_seleccion_color(cilindro1,100+inc,100+inc,100+inc);
			 inc+=10;  
   		  glPopMatrix(); 
			       

   		  glPushMatrix(); 
   		  glTranslatef(1,0.3,-1);
			 glRotatef(90,1,0,0);
   		  	 draw_seleccion_color(cilindro2,100+inc,100+inc,100+inc);
			 inc+=10;
   		  glPopMatrix(); 
			 
   		glPopMatrix();
		// CABINA
		glPushMatrix();
			glRotatef(giro_cabina,0,1,0);
			glPushMatrix();
				glTranslatef(0,0.6,0);
				glPushMatrix();
  	  			 	draw_seleccion_color(cilindro3,100+inc,100+inc,100+inc);
					inc+=10;
				glPopMatrix();
				
				glPushMatrix();
					glTranslatef(0,0.75,0);
  	   				draw_seleccion_color(cubo2,100+inc,100+inc,100+inc);
					inc+=10;
				glPopMatrix();
				
				glPushMatrix();
					glTranslatef(0,1.25,0);
  	   				draw_seleccion_color(triangulo1,100+inc,100+inc,100+inc);
					inc+=10;
				glPopMatrix();
			glPopMatrix();
			

			//MATRIZ DE LOS BRAZOS
			glPushMatrix();
				glRotatef(giro_brazo,0,0,1);
				glPushMatrix();
					glTranslatef(0.5,0.6,0);
					glPushMatrix();
						glTranslatef(0,0,-0.25);
						glRotatef(-45,0,0,1);
						glRotatef(6,1,0,0);
						draw_seleccion_color(cono1,100+inc,100+inc,100+inc);
						inc+=10;
					glPopMatrix();
					
					glPushMatrix();
						glTranslatef(0,0,+0.25);
						glRotatef(-45,0,0,1);
						glRotatef(-6,1,0,0);
						draw_seleccion_color(cono2,100+inc,100+inc,100+inc);
						inc+=10;
					glPopMatrix();
					

				glPopMatrix();

				//MATRIZ DE LA CUERDA Y LA BOLA
				glPushMatrix();
					glTranslatef(2.15,2.3,0);
					glPushMatrix();
						glRotatef(giro_cuerda,0,0,1);
						glPushMatrix();
							glTranslatef(0,-2,0);
							draw_seleccion_color(cuerda,100+inc,100+inc,100+inc);
							inc+=10;
						glPopMatrix();
						
						glPushMatrix();
							glTranslatef(0,-1.75,0);
							glPushMatrix();
								glRotatef(giro_bola,0,0,1);
								glTranslatef(0,-0.25,0);
								draw_seleccion_color(bola,100+inc,100+inc,100+inc);
								inc+=10;
							glPopMatrix();
						glPopMatrix();

					glPopMatrix();
				glPopMatrix();

			glPopMatrix();
		glPopMatrix();

}


//**************************************************************************
//
//***************************************************************************

void draw_scene(void)
{
if(cam==Normal){
	
	clear_window();
	change_observer();
	draw_axis();
	draw_objects();


	glDrawBuffer(GL_BACK);
	clear_window();
	change_observer();
	draw_objects_seleccion();
	glDrawBuffer(GL_FRONT);
	glFlush();
}
else if(cam==Ortogonal){
	clear_window();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(Observer_distance*1, Observer_distance*-1, Observer_distance*1,Observer_distance*-1 ,2.5,-2.5);
	glViewport(0,0,Ancho,Alto);
	glRotatef(-90,1,0,0);
	glScalef(factor,factor,1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	draw_axis();
	draw_objects();

	glFlush();
}

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
change_projection();
Ancho=Ancho1;
Alto=Alto1;
draw_scene();
}  


/*************************************************************************/

void getCamara (GLfloat *x, GLfloat *y)
{
*y=Observer_angle_x;
*x=Observer_angle_y;
}

/*************************************************************************/

void setCamara (GLfloat x, GLfloat y)
{
Observer_angle_x=y;
Observer_angle_y=x;
}



//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_keys(unsigned char Tecla1,int x,int y)
{

if (toupper(Tecla1)=='Q') exit(0);
if (Tecla1=='+') 
   {factor*=0.9;
    glutPostRedisplay();}
if (Tecla1=='-') 
   {factor*=1.1;
    glutPostRedisplay();}
}

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_keys(int Tecla1,int x,int y)
{

switch (Tecla1){
	case GLUT_KEY_LEFT:Observer_angle_y--;break;
	case GLUT_KEY_RIGHT:Observer_angle_y++;break;
	case GLUT_KEY_UP:Observer_angle_x--;break;
	case GLUT_KEY_DOWN:Observer_angle_x++;break;
	case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
	case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
	case GLUT_KEY_F1:giro_cabina+=vel_cabina;break;
	case GLUT_KEY_F2:giro_cabina-=vel_cabina;break;
	case GLUT_KEY_F3:giro_brazo+=vel_brazo;
		if(giro_brazo > giro_brazo_max) giro_brazo= giro_brazo_max;
		break;
	case GLUT_KEY_F4:giro_brazo-=vel_brazo;
		if(giro_brazo < giro_brazo_min) giro_brazo= giro_brazo_min;
		break;	
	case GLUT_KEY_F5:giro_cuerda+=vel_cuerda;
		if(giro_cuerda > giro_cuerda_max) giro_cuerda= giro_cuerda_max;
		break;
	case GLUT_KEY_F6:giro_cuerda-=vel_cuerda;
		if(giro_cuerda < giro_cuerda_min) giro_cuerda= giro_cuerda_min;
		break;
	case GLUT_KEY_F7:giro_bola+=vel_bola;
		if(giro_bola > giro_bola_max) giro_bola = giro_bola_max;
		break;
	case GLUT_KEY_F8:giro_bola-=vel_bola;
		if(giro_bola < giro_bola_min) giro_bola = giro_bola_min;
		break;
	case GLUT_KEY_F9: cam=Ortogonal; break;
	case GLUT_KEY_F10: cam=Normal; break;
	}
glutPostRedisplay();
}


//***************************************************************************
// Funciones para manejo de eventos del ratón
//***************************************************************************

void clickRaton( int boton, int estado, int x, int y )
{
if(boton== GLUT_RIGHT_BUTTON) {
   if( estado == GLUT_DOWN) {
      estadoRaton[2] = 1;
      xc=x;
      yc=y;
	  float x0, y0;
	  getCamara(&x0,&y0);
	  last_xn = x0 - (x-xc);
     } 
   else estadoRaton[2] = 1;
   }
if(boton== GLUT_LEFT_BUTTON) {
  if( estado == GLUT_DOWN) {
      estadoRaton[2] = 2;
      xc=x;
      yc=y;
	  if(cam==Normal)
      	pick_color(xc, yc);
    } 
  }
  if( boton == 3 || boton == 4){
	  if(estado == GLUT_DOWN){
		  if(boton==3)
		  	Observer_distance-=0.5;
		
		  if(boton == 4)
		  	Observer_distance+=0.5;

		glutPostRedisplay();
	  }
  }
}



/*************************************************************************/

void RatonMovido( int x, int y )
{
float x0, y0, xn, yn; 
if(estadoRaton[2]==1){
	if(cam==Normal){
     getCamara(&x0,&y0);
     yn=y0+(y-yc);
     xn=x0-(x-xc);
     setCamara(xn,yn);
     xc=x;
     yc=y;
     glutPostRedisplay();
	}
	else{
		getCamara(&x0,&y0);
		xn=x0-(x-xc);
		if(last_xn >= xn){
			Observer_distance+=0.05;
		}
		else{
			Observer_distance-=0.05;
		}
		last_xn = xn;
		glutPostRedisplay();
	}
    
}
}


//***************************************************************************
// Funciones para la seleccion
//************************************************************************


void procesar_color(unsigned char color[3])
{
 int i;
 solido *obj;

 obj=(solido *)malloc(sizeof(solido));
 
 switch (color[0])
      {case 100: obj=cubo1;
                 if (modo[0]==0) 
                      {modo[0]=1;
                       cambio=1;
                      }
                  else 
                      {modo[0]=0;
                       cambio=0;
                      }
                  break; 
        case 110: obj=cilindro1;
                  if (modo[1]==0) 
                       {modo[1]=1;
                        cambio=1;
                       }
                  else 
                       {modo[1]=0;
                        cambio=0;
                       } 
                  break;
       case 120: obj=cilindro2;
                  if (modo[2]==0) 
                       {modo[2]=1;
                        cambio=1;
                       }
                  else 
                       {modo[2]=0;
                        cambio=0;
                       }
                  break;
		case 130: obj=cilindro3;
                  if (modo[3]==0) 
                       {modo[3]=1;
                        cambio=1;
                       }
                  else 
                       {modo[3]=0;
                        cambio=0;
                       }
                  break; 
		case 140: obj=cubo2;
                  if (modo[4]==0) 
                       {modo[4]=1;
                        cambio=1;
                       }
                  else 
                       {modo[4]=0;
                        cambio=0;
                       }
                  break;
		case 150: obj=triangulo1;
                  if (modo[5]==0) 
                       {modo[5]=1;
                        cambio=1;
                       }
                  else 
                       {modo[5]=0;
                        cambio=0;
                       }
                  break; 
		case 160: obj=cono1;
                  if (modo[6]==0) 
                       {modo[6]=1;
                        cambio=1;
                       }
                  else 
                       {modo[6]=0;
                        cambio=0;
                       }
                  break;
		case 170: obj=cono2;
                  if (modo[7]==0) 
                       {modo[7]=1;
                        cambio=1;
                       }
                  else 
                       {modo[7]=0;
                        cambio=0;
                       }
                  break;
		case 180: obj=cuerda;
                  if (modo[8]==0) 
                       {modo[8]=1;
                        cambio=1;
                       }
                  else 
                       {modo[8]=0;
                        cambio=0;
                       }
                  break; 
		case 190: obj=bola;
                  if (modo[9]==0) 
                       {modo[9]=1;
                        cambio=1;
                       }
                  else 
                       {modo[9]=0;
                        cambio=0;
                       }
                  break;  		  
	  }     
        if (cambio==1) 
                  {obj->r=0.3;
                   obj->g=0.9;
                   obj->b=0.3;
                  }
        if (cambio==0)
                  {obj->r=0.9;
                   obj->g=0.6;
                   obj->b=0.2;
                  }
                 
 }



void pick_color(int x, int y)
{
GLint viewport[4];
unsigned char pixel[3];

glGetIntegerv(GL_VIEWPORT, viewport);
glReadBuffer(GL_BACK);
glReadPixels(x,viewport[3]-y,1,1,GL_RGB,GL_UNSIGNED_BYTE,(GLubyte *) &pixel[0]);
int r = pixel[0];
int g = pixel[1];
int b = pixel[2];
printf(" valor x %d, valor y %d, color %d, %d, %d \n",x,y,pixel[0],pixel[1],pixel[2]);

procesar_color(pixel);
glutPostRedisplay();
}


//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{
// se inicalizan la ventana y los planos de corte
Window_width=.5;
Window_height=.5;
Front_plane=1;
Back_plane=1000;

// se inicia la posicion del observador, en el eje z
Observer_distance=3*Front_plane;
Observer_angle_x=0;
Observer_angle_y=0;

// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClearColor(1,1,1,1);

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
change_projection();
glViewport(0,0,UI_window_width,UI_window_height);

for (int i=0;i<10;i++) modo[i]=0;
}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

int main(int argc, char **argv)
{
    // se llama a la inicialización de glut
    
	//Componenetes del chasis
    cilindro1=(solido*)malloc(sizeof(solido));
    construir_cilindro(0.3,2,25,3,cilindro1);

	cilindro2=(solido*)malloc(sizeof(solido));
    construir_cilindro(0.3,2,25,3,cilindro2);

	cubo1=(solido*)malloc(sizeof(solido));
	construir_cubo(1, cubo1);

	//componentes de la cabina
	cilindro3=(solido*)malloc(sizeof(solido));
    construir_cilindro(0.7,0.25,25,3,cilindro3);

	cubo2=(solido*)malloc(sizeof(solido));
	construir_cubo(0.5, cubo2);

	triangulo1=(solido*)malloc(sizeof(solido));
	construir_piramide(0.5, 0.5, triangulo1);

	//Componente de los brazos
	cono1=(solido*)malloc(sizeof(solido));
	construir_cono(0.1,2.5,25,2,cono1);

	cono2=(solido*)malloc(sizeof(solido));
	construir_cono(0.1,2.5,25,2,cono2);
	// Componente de la cuerda
	cuerda=(solido*)malloc(sizeof(solido));
	construir_cilindro(0.01,2,25,3,cuerda);
	//Componente de la cuerda
	bola=(solido*)malloc(sizeof(solido));
	construir_esfera(0.25,20,20,3,bola);

    
    glutInit(&argc, argv);

    // se indica las caracteristicas que se desean para la visualización con OpenGL
    // Las posibilidades son:
    // GLUT_SIMPLE -> memoria de imagen simple
    // GLUT_DOUBLE -> memoria de imagen doble
    // GLUT_INDEX -> memoria de imagen con color indizado
    // GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
    // GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
    // GLUT_DEPTH -> memoria de profundidad o z-bufer
    // GLUT_STENCIL -> memoria de estarcido
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    // posicion de la esquina inferior izquierdad de la ventana
    glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);

    // tamaño de la ventana (ancho y alto)
    glutInitWindowSize(UI_window_width,UI_window_height);

    // llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
    // al bucle de eventos)
    glutCreateWindow("Practica 5");

    // asignación de la funcion llamada "dibujar" al evento de dibujo
    glutDisplayFunc(draw_scene);
    // asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
    glutReshapeFunc(change_window_size);
    // asignación de la funcion llamada "tecla_normal" al evento correspondiente
    glutKeyboardFunc(normal_keys);
    // asignación de la funcion llamada "tecla_Especial" al evento correspondiente
    glutSpecialFunc(special_keys);

    // eventos ratón
    glutMouseFunc( clickRaton );
    glutMotionFunc( RatonMovido );


    // funcion de inicialización
    initialize();

    // inicio del bucle de eventos
    glutMainLoop();
    return 0;
}
