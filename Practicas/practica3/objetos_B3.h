//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>


const float AXIS_SIZE=5000;
//typedef enum{POINTS,EDGES,SOLID_CHESS,SOLID} _modo;

enum Objeto { Piramide, Cubo, Objeto_ply, Rotacion, Cilindro, Cono, Esfera, RotacionPly, Extra, Articulado};
enum Modo { Puntos, Lineas, Solido, Ajedrez};


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
void 	draw(Modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

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
void draw(Modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

double altura;

protected:
_cilindro rodamientos;
_cubo base;
};

class _cabina: public _triangulos3D
{
public:
	_cabina();
void draw(Modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
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
void draw(Modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
double altura;
double anchura;
protected:
	_cono barras;
};

class _cuerda: public _triangulos3D 
{
public:
	_cuerda();
void draw(Modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
double altura;

protected:
_cilindro barra;

};

class _bola: public _triangulos3D
{
public:	
	_bola();
void draw(Modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

protected:
_esfera b;

};


class _demoledor: public _triangulos3D
{
public:
	_demoledor();
void draw(Modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

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