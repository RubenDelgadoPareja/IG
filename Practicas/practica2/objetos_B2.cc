//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include "objetos_B2.h"
#include "file_ply_stl.hpp"
#include <algorithm>

//enum Objeto { Piramide, Cubo, Objeto_ply, Rotacion};
//Objeto obj = Piramide;
//enum Modo { Puntos, Lineas, Solido, Ajedrez};
//Modo mod = Lineas;


//*************************************************************************
// _puntos3D
//*************************************************************************

_puntos3D::_puntos3D()
{
}

//*************************************************************************
// dibujar puntos
//*************************************************************************

void _puntos3D::draw_puntos(float r, float g, float b, int grosor)
{
int i;
glPointSize(grosor);
glColor3f(r,g,b);
glBegin(GL_POINTS);
for (i=0;i<vertices.size();i++){
	glVertex3fv((GLfloat *) &vertices[i]);
	}
glEnd();
}


//*************************************************************************
// _triangulos3D
//*************************************************************************

_triangulos3D::_triangulos3D()
{
}


//*************************************************************************
// dibujar en modo arista
//*************************************************************************

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor)
{
int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
glLineWidth(grosor);
glColor3f(r,g,b);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();
}

//*************************************************************************
// dibujar en modo sólido
//*************************************************************************

void _triangulos3D::draw_solido(float r, float g, float b)
{

int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
// glLineWidth(grosor);
glColor3f(r,g,b);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();


}

//*************************************************************************
// dibujar en modo sólido con apariencia de ajedrez
//*************************************************************************

void _triangulos3D::draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2)
{

int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
// glLineWidth(grosor);

glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	if(i%2 == 0){
		glColor3f(r1,g1,b1);
		glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
	else{
		glColor3f(r2,g2,b2);
		glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
	}
glEnd();

}

//*************************************************************************
// dibujar con distintos modos
//*************************************************************************

void _triangulos3D::draw(Modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
switch (modo){
	case Puntos:draw_puntos(r1, g1, b1, grosor);break;
	case Lineas:draw_aristas(r1, g1, b1, grosor);break;
	case Ajedrez:draw_solido_ajedrez(r1, g1, b1, r2, g2, b2);break;
	case Solido:draw_solido(r1, g1, b1);break;
	}
}

//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam)
{
//vertices
tam = 2*tam;
vertices.resize(8);
vertices[0].x=+tam; vertices[0].y=+tam*2; vertices[0].z=+tam; 
vertices[1].x=-tam; vertices[1].y=+tam*2; vertices[1].z=+tam; 
vertices[2].x=-tam; vertices[2].y=+tam*2; vertices[2].z=-tam;
vertices[3].x=+tam; vertices[3].y=+tam*2; vertices[3].z=-tam;
vertices[4].x=+tam; vertices[4].y=0; vertices[4].z=+tam;
vertices[5].x=-tam; vertices[5].y=0; vertices[5].z=+tam; 
vertices[6].x=-tam; vertices[6].y=0; vertices[6].z=-tam;
vertices[7].x=+tam; vertices[7].y=0; vertices[7].z=-tam;

// triangulos
caras.resize(12);
caras[0]._0=7; caras[0]._1=3; caras[0]._2=0; 
caras[1]._0=4; caras[1]._1=7; caras[1]._2=0;
caras[2]._0=4; caras[2]._1=0; caras[2]._2=1; 
caras[3]._0=5; caras[3]._1=4; caras[3]._2=1; 
caras[4]._0=7; caras[4]._1=4; caras[4]._2=5; 
caras[5]._0=6; caras[5]._1=7; caras[5]._2=5; 
caras[6]._0=5; caras[6]._1=1; caras[6]._2=2; 
caras[7]._0=6; caras[7]._1=5; caras[7]._2=2; 
caras[8]._0=6; caras[8]._1=3; caras[8]._2=2;
caras[9]._0=7; caras[9]._1=6; caras[9]._2=3;
caras[10]._0=0; caras[10]._1=3; caras[10]._2=2;
caras[11]._0=1; caras[11]._1=0; caras[11]._2=2;    

}


//*************************************************************************
// clase piramide
//*************************************************************************

_piramide::_piramide(float tam, float al)
{

//vertices 
vertices.resize(5); 
vertices[0].x=-tam;vertices[0].y=0;vertices[0].z=tam;
vertices[1].x=tam;vertices[1].y=0;vertices[1].z=tam;
vertices[2].x=tam;vertices[2].y=0;vertices[2].z=-tam;
vertices[3].x=-tam;vertices[3].y=0;vertices[3].z=-tam;
vertices[4].x=0;vertices[4].y=al;vertices[4].z=0;

caras.resize(6);
caras[0]._0=0;caras[0]._1=1;caras[0]._2=4;
caras[1]._0=1;caras[1]._1=2;caras[1]._2=4;
caras[2]._0=2;caras[2]._1=3;caras[2]._2=4;
caras[3]._0=3;caras[3]._1=0;caras[3]._2=4;
caras[4]._0=3;caras[4]._1=1;caras[4]._2=0;
caras[5]._0=3;caras[5]._1=2;caras[5]._2=1;
}

//*************************************************************************
// clase objeto ply
//*************************************************************************


_objeto_ply::_objeto_ply() 
{
int n_ver,n_car;

   // leer lista de coordenadas de vértices y lista de indices de vértices


}



int _objeto_ply::parametros(char *archivo)
{
int n_ver,n_car;

vector<float> ver_ply ;
vector<int>   car_ply ;
 
_file_ply::read(archivo, ver_ply, car_ply );

n_ver=ver_ply.size()/3;
n_car=car_ply.size()/3;

printf("Number of vertices=%d\nNumber of faces=%d\n", n_ver, n_car);

vertices.resize(n_ver);
caras.resize(n_car);

for(int i = 0; i < vertices.size() ; i++){
	vertices[i].x = ver_ply[3*i];	
	vertices[i].y = ver_ply[3*i+1];
	vertices[i].z = ver_ply[3*i+2];

}

for(int i= 0; i < caras.size() ; i++){
	caras[i]._0 = car_ply[3*i];
	caras[i]._1 = car_ply[3*i+1];
	caras[i]._2 = car_ply[3*i+2];
}




return(0);
}


//************************************************************************
// objeto por revolucion
//************************************************************************

_rotacion::_rotacion()
{

}


void _rotacion::parametros(vector<_vertex3f> perfil, int num, int tapas)
{
int i,j;
_vertex3f vertice_aux;
_vertex3i cara_aux;
int num_aux;

//Comprobamos el orden del perfil y lo cambiamos ** Generatriz inversa **

if(perfil.front().y > perfil.back().y){
  reverse(perfil.begin(),perfil.end());
}

// tratamiento de los vértice

num_aux=perfil.size();
vertices.resize(num_aux*num);
for (j=0;j<num;j++)
  {for (i=0;i<num_aux;i++)
     {
      vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
      vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
      vertice_aux.y=perfil[i].y;
      vertices[i+j*num_aux]=vertice_aux;
     }
  }
//Generamos las caras

for (j=0;j<num;j++)
  {for (i=0;i<num_aux-1;i++)
     {
	  if(vertices[i+1+j*num_aux]!=vertices[i+1+((j+1)%num)*num_aux]){
	  	cara_aux._0=i+((j+1)%num)*num_aux;
      	cara_aux._1=i+1+((j+1)%num)*num_aux;
      	cara_aux._2=i+1+j*num_aux;
      	caras.push_back(cara_aux);
	  }
      
      cara_aux._0=i+1+j*num_aux;
      cara_aux._1=i+j*num_aux;
      cara_aux._2=i+((j+1)%num)*num_aux;
      caras.push_back(cara_aux);
     }
  } 
	//Tapa superior 
  if (fabs(perfil[num_aux-1].x)>0.0 && (tapas == 1 || tapas== 3))
	{ 
		vertice_aux.x=0;
		vertice_aux.y=perfil[num_aux-1].y;
		vertice_aux.z=0;
		vertices.push_back(vertice_aux);

		for(i=0;i<num-1;i++){
      cara_aux.x=num_aux-1+i*num_aux;
      cara_aux.y=num_aux-1+(i+1)*num_aux;
      cara_aux.z=vertices.size()-1;
      caras.push_back(cara_aux);
    }
    cara_aux.x=num_aux-1+(num-1)*num_aux;
    cara_aux.y=num_aux-1;
    cara_aux.z=vertices.size()-1;
    caras.push_back(cara_aux);
  }
	//Tapa inferior

	if (fabs(perfil[0].x)>0.0  && (tapas == 2 || tapas== 3) )
	{
		vertice_aux.x=0;
		vertice_aux.y=perfil[0].y;
		vertice_aux.z=0;
		vertices.push_back(vertice_aux);


	 	for(i=0;i<num-1;i++){
      		cara_aux.x=i*num_aux;
      		cara_aux.y=(i+1)*num_aux;
      		cara_aux.z=vertices.size()-1;
      		caras.push_back(cara_aux);
    	}
    	cara_aux.x=(num-1)*num_aux;
    	cara_aux.y=0;
    	cara_aux.z=vertices.size()-1;
    	caras.push_back(cara_aux);
	} 


}

_cilindro::_cilindro(float r, float h, int num, int tapas){
	_vertex3f aux;
	this->num = num;
	this->tapas = tapas;

	aux.x=r; aux.y=h; aux.z=0.0;
	perfil.push_back(aux);
	aux.x=r; aux.y=0; aux.z=0.0;
	perfil.push_back(aux);

	parametros(perfil, num, tapas);
}



_cono::_cono(float r, float h, int num, int tapas){

	_vertex3f aux;
	this->num = num;
	this->tapas = tapas;

	aux.x=r; aux.y=0; aux.z=0.0;
	perfil.push_back(aux);
	aux.x=0.0; aux.y=h; aux.z=0.0;
	perfil.push_back(aux);
	

	parametros(perfil, num, tapas);

}



_esfera::_esfera(float r, int lat, int lon, int tapas){
	this->num = lon;
	this->tapas = tapas;

	_vertex3f aux;

	float increRad = M_PI/lat;
	float angulo = 0;

	aux.x=0.0; aux.y=r; aux.z=0.0;
	perfil.push_back(aux);

	for(int i=0; i < lat-1; ++i){
		angulo += increRad;

		aux.x = r*sin(angulo);
		aux.y = r*cos(angulo);
		aux.z = 0.0;

		perfil.push_back(aux);
	}

	aux.x=0.0; aux.y=-r; aux.z=0.0;
	perfil.push_back(aux);

	parametros(perfil, num, tapas);


}



_rotacion_ply::_rotacion_ply(){

}

void _rotacion_ply::parametros(char *archivo, int num, int tapas){
	int n_ver;

	vector<float> ver_ply ;
	vector<int>   car_ply ;
	_vertex3f aux;
	
	_file_ply::read(archivo, ver_ply, car_ply );
	
	n_ver=ver_ply.size()/3;
	
	printf("Number of vertices=%d\n", n_ver);
	
	vertices.resize(n_ver);

	for(int i=0; i<n_ver; i++){
		aux.x=ver_ply[3*i];
		aux.y=ver_ply[3*i+1];
		aux.z=ver_ply[3*i+2];
		perfil.push_back(aux);
	}

	_rotacion::parametros(perfil, num, tapas);
}


_extra::_extra(){

}

void _extra::parametros(int radio, int num){

  //Crea el perfil 2D (dos semicirculos que será nuestro perfil 3D)
  //Voy a crear un semicirculo al igual que en la esfera pero invertido , lo voy a duplicar y meterlo en nuestro perfil. 
  vector<_vertex3f> perfil;
  perfil.resize(2*num-1);
  _vertex3f aux;
    aux.x=0;
    aux.y=-radio;
    aux.z=0;
  perfil[0].x=aux.x+1.5*radio;
  perfil[0].y=aux.y-radio;
  perfil[0].z=aux.z;

  //Tras el primer punto del semicirculo, el resto los generamos por rotación sobre el eje Z
  for (int j=1;j<num;j++){
      aux.x=radio*cos(1.5*M_PI-j*M_PI/(num-1));
      aux.y=radio*sin(1.5*M_PI-j*M_PI/(num-1));
      perfil[j].x=aux.x+1.5*radio;
      perfil[j].y=aux.y-radio;
      perfil[j].z=aux.z;
      perfil[j+num-1].x=aux.x+1.5*radio;
      perfil[j+num-1].y=aux.y+radio;
      perfil[j+num-1].z=aux.z;
  }
	//Generamos las caras del objeto extra
  _rotacion::parametros(perfil,num, 3);
}
