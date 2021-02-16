//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>


const float AXIS_SIZE=5000;
//typedef enum{POINTS,EDGES,SOLID_CHESS,SOLID} _modo;

typedef enum Objeto { Piramide, Cubo, Objeto_ply, Rotacion, Cilindro, Cono, Esfera, RotacionPly, Extra};
typedef enum Modo { Puntos, Lineas, Solido, Ajedrez};


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