//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>
#include "file_ply_stl.hpp"

using namespace std;





//typedef enum{POINTS,EDGES,SOLID_CHESS,SOLID} _modo;

enum Objeto { Piramide, Cubo, Objeto_ply, Rotacion, Cilindro, Cono, Esfera, RotacionPly, Extra, Articulado, Tablero};
enum Modo { Puntos, Lineas, Solido,Solido_Iluminado_Plano, Solido_Iluminado_Gouraud, Ajedrez, Texturas};
enum Material { Null, Esmeralda, Oro};

//**************************************************************************
// estructuras de datos para los modelos
//**************************************************************************

struct vertices
{
float coord[3];
};


struct caras
{
int ind_c[3];
};

struct solido{
int n_v;
int n_c;
vertices *ver;
caras    *car;
float r;
float g;
float b;
};


void construir_cubo(float tam, solido *cubo);
void construir_piramide(float tam, float al, solido *piramide);
void construir_ply(char *file, solido *ply);
void construir_rotacion(vector<_vertex3f> perfil, int num, int tapas, solido *rotacion);
void construir_cilindro(float r,float h,int n, int tapas, solido *cilindro);
void construir_cono(float r, float h, int n, int tapas, solido *cono);
void construir_esfera(float r, int lat, int lon, int tapas, solido *esfera);

void draw_puntos(vertices *ver, int n_v);
void draw_solido(solido *malla, float r, float g, float b, int modo);
void draw_solido_ajedrez(solido *malla, float r1, float g1, float b1, float r2, float g2, float b2);

// Función para pintar en el buffer y hacer la selección posteriormente
void draw_seleccion_color(solido *malla, int r, int g, int b);


//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:

  
	_puntos3D();
void 	draw_puntos(float r, float g, float b, int grosor);

vector<_vertex3f> vertices;
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D
{
public:

	_triangulos3D();
void 	draw_aristas(float r, float g, float b, int grosor);
void    draw_solido(float r, float g, float b);
void 	draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);
void 	draw(Modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Material mat);

vector<_vertex3i> caras;


};

//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo: public _triangulos3D
{
public:

	_cubo(float tam=0.5);

};


//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide: public _triangulos3D
{
public:

	_piramide(float tam=0.5, float al=0.75);

};

//*************************************************************************
// clase objeto ply
//*************************************************************************

class _objeto_ply: public _triangulos3D
{
public:
   _objeto_ply();

int   parametros(char *archivo);

};

//************************************************************************
// objeto por revolución
//************************************************************************

class _rotacion: public _triangulos3D
{
public:
       _rotacion();
void  parametros(vector<_vertex3f> perfil1, int num1, int tapas);

vector<_vertex3f> perfil; 
int num;
int tapas;
};
//************************************************************************
// Cilindro
//************************************************************************


class _cilindro: public _rotacion{

	public:
	_cilindro(float r=0.5, float h=1, int num=25, int tapas=3);


};

//************************************************************************
// Cono
//************************************************************************


 class _cono: public _rotacion{
	 public:

	 _cono(float r=1, float h=2, int num=19, int tapas=2);



 };

 //************************************************************************
// Esfera
//************************************************************************


 class _esfera: public _rotacion{
	 public:

	 _esfera(float r=1, int lat=20, int lon=20, int tapas = 3);


 };

 //************************************************************************
// objeto por revolución desde un fichero ply
//************************************************************************


class _rotacion_ply: public _rotacion
{
	public:
	_rotacion_ply();
	void parametros(char *archivo, int num=25, int tapas=3);


};

//************************************************************************
// Objeto extra
//************************************************************************


class _extra: public _rotacion
{
	public:
		_extra();
		void parametros(int radio, int num);
};

class _chasis: public _triangulos3D
{
public:
	_chasis();
void draw(Modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Material mat);

double altura;

protected:
_cilindro rodamientos;
_cubo base;
};

class _cabina: public _triangulos3D
{
public:
	_cabina();
void draw(Modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Material mat);
double altura, anchura;

protected:
_cilindro base;
_cubo cabina;
_piramide techo;
};

class _brazo: public _triangulos3D
{
public:
	_brazo();
void draw(Modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor,  Material mat);
double altura;
double anchura;
protected:
	_cono barras;
};

class _cuerda: public _triangulos3D 
{
public:
	_cuerda();
void draw(Modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Material mat);
double altura;

protected:
_cilindro barra;

};

class _bola: public _triangulos3D
{
public:	
	_bola();
void draw(Modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Material mat);

protected:
_esfera b;

};


class _demoledor: public _triangulos3D
{
public:
	_demoledor();
void draw(Modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Material mat);

float giro_cabina;
float giro_brazo;
float giro_cuerda;
float giro_bola;


float giro_brazo_min;
float giro_brazo_max;
float giro_cuerda_min;
float giro_cuerda_max;
float giro_bola_min;
float giro_bola_max;


protected:
_chasis chasis;
_cabina cabina;
_brazo brazo;
_cuerda cuerda;
_bola bola;
};


//************************************************************************
// Clase luz
//************************************************************************

class _luz
{
public:

  float pos_x, pos_y, pos_z, angx, angy, angz;
  int a, b, c;
  GLenum indice_luz;

  _luz(GLenum indice_luz, _vertex4f punto_luz, _vertex4f luz_ambiente, _vertex4f luz_difusa, _vertex4f luz_especular);

  void activar();
  void transformar(GLenum indice_luz, int a, int b, int c, float ang, float x, float y, float z);
  void desactivar();

protected:
  
  _vertex4f punto_luz;
  _vertex4f luz_ambiente;
  _vertex4f luz_difusa;
  _vertex4f luz_especular;
};