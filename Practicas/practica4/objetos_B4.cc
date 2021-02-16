//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include "objetos_B4.h"
#include "file_ply_stl.hpp"
#include <algorithm>




//enum Objeto { Piramide, Cubo, Objeto_ply, Rotacion};
//Objeto obj = Piramide;
//enum Modo { Puntos, Lineas, Solido, Ajedrez};
//Modo mod = Lineas;

//*************************************************************************
// _textura
//*************************************************************************
_textura::_textura(GLuint textura_id, char const *archivoJPG){
	vector<unsigned char> data;
	id_textura = textura_id;
   imagen.load(archivoJPG);	// Imagen que se va a leer

   // empaquetamos bien los datos
   for (long y = 0; y < imagen.height(); y ++)
      for (long x = 0; x < imagen.width(); x ++)
      {
	 unsigned char *r = imagen.data(x, y, 0, 0);
	 unsigned char *g = imagen.data(x, y, 0, 1);
	 unsigned char *b = imagen.data(x, y, 0, 2);
	 data.push_back(*r);
	 data.push_back(*g);
	 data.push_back(*b);
      }

   glGenTextures(1, &id_textura);
   glBindTexture(GL_TEXTURE_2D, id_textura);

   glActiveTexture(GL_TEXTURE0);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

   // TRASFIERE LOS DATOS A GPU
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imagen.width(), imagen.height(),
		0, GL_RGB, GL_UNSIGNED_BYTE, &data[0]);
}


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

glEnableClientState(GL_VERTEX_ARRAY);
glVertexPointer(3,GL_FLOAT,0,&vertices[0]);
glDrawArrays(GL_POINTS,0,vertices.size());

}



//*************************************************************************
// _triangulos3D
//*************************************************************************

_triangulos3D::_triangulos3D()
{

	b_normales_caras = false;
	b_normales_vertices = false;
	b_textura_coord = false;

	ambiente = _vertex4f(1,1,1,1);
	difusa = _vertex4f(1,1,1,1);
	especular = _vertex4f(1,1,1,1);
	brillo = 30;


	ambiente_oro ={ 0.24725f, 0.1995f, 0.0745f, 1.0f };
	difusa_oro = {0.75164f, 0.60648f, 0.22648f, 1.0f };
	especular_oro ={0.628281f, 0.555802f, 0.366065f, 1.0f };
	brillo_oro = 51.2f;

	ambiente_esm = { 0.0215f, 0.1745f, 0.0215f, 0.55f };
	difusa_esm = {0.07568f, 0.61424f, 0.07568f, 0.55f };
	especular_esm = {0.633f, 0.727811f, 0.633f, 0.55f };
	brillo_esm =  76.8f;
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


glEnableClientState(GL_VERTEX_ARRAY);
glVertexPointer(3,GL_FLOAT,0,&vertices[0]);
glDrawElements(GL_TRIANGLES,caras.size()*3,GL_UNSIGNED_INT,&caras[0]);

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
// calcular vectores normales de las caras
//*************************************************************************
void _triangulos3D::calcular_normales_caras(){
	normales_caras.resize(caras.size());

	for(int i=0; i<caras.size(); i++){
		_vertex3f a = vertices[caras[i]._1] - vertices[caras[i]._0];
		_vertex3f b = vertices[caras[i]._2] - vertices[caras[i]._0];
		_vertex3f normal = a.cross_product(b);

		normales_caras[i] = normal.normalize();
	}

	b_normales_caras = true;
}

//*************************************************************************
// calcular vectores normales de los vertices
//*************************************************************************
void _triangulos3D::calcular_normales_vertices(){

	if(!b_normales_vertices){
		if(!b_normales_caras)
			calcular_normales_caras();
	}

	normales_vertices.resize(vertices.size());

	_vertex3f normal;

	for(int i = 0; i < vertices.size(); ++i){
		normales_vertices[i] = _vertex3f(0.0,0.0,0.0);
	}

	for(int i = 0; i < caras.size(); ++i){
		normales_vertices[caras[i]._0] += normales_caras[i];
		normales_vertices[caras[i]._1] += normales_caras[i];
		normales_vertices[caras[i]._2] += normales_caras[i];
	}

	for(int i= 0; i < vertices.size(); ++i)
			normales_vertices[i].normalize();

	b_normales_vertices = true;

}
//*************************************************************************
// dibujar con iluminacion plana
//*************************************************************************
void  _triangulos3D::draw_iluminacion_plana(Material mat){
	if(!b_normales_caras)
		calcular_normales_caras();	

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);

	glShadeModel(GL_FLAT);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);

	// Si ponemos el material aquí, se aplicará a todas las caras
	if(mat == Esmeralda){
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,(GLfloat *)&ambiente_esm);
		glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,(GLfloat *)&difusa_esm);
  		glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(GLfloat *)&especular_esm);
		glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,(GLfloat *)&brillo_esm);
	}
	else if(mat == Oro){
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,(GLfloat *)&ambiente_oro);
		glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,(GLfloat *)&difusa_oro);
  		glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(GLfloat *)&especular_oro);
		glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,(GLfloat *)&brillo_oro);
	}
	else{
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,(GLfloat *)&ambiente);
		glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,(GLfloat *)&difusa);
  		glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(GLfloat *)&especular);
		glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,(GLfloat *)&brillo);
	}

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);
	for(int i =0; i < caras.size(); ++i){

		glNormal3fv((GLfloat*) &normales_caras[i]);
		glVertex3fv((GLfloat*) &vertices[caras[i]._0]);
		glVertex3fv((GLfloat*) &vertices[caras[i]._1]);
		glVertex3fv((GLfloat*) &vertices[caras[i]._2]);
	}

	glEnd();
	glDisable(GL_LIGHTING);
}


//*************************************************************************
// dibujar con iluminacion suave
//*************************************************************************

void  _triangulos3D::draw_iluminacion_suave(Material mat){
	if(!b_normales_vertices)
		calcular_normales_vertices();

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);

	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);

	if(mat == Esmeralda){
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,(GLfloat *)&ambiente_esm);
		glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,(GLfloat *)&difusa_esm);
  		glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(GLfloat *)&especular_esm);
		glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,(GLfloat *)&brillo_esm);
	}
	else if(mat == Oro){
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,(GLfloat *)&ambiente_oro);
		glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,(GLfloat *)&difusa_oro);
  		glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(GLfloat *)&especular_oro);
		glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,(GLfloat *)&brillo_oro);
	}
	else{
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,(GLfloat *)&ambiente);
		glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,(GLfloat *)&difusa);
  		glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(GLfloat *)&especular);
		glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,(GLfloat *)&brillo);
	}

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);
	for(int i =0; i < caras.size(); ++i){
		glNormal3fv((GLfloat*) &normales_vertices[caras[i]._0]);
		glVertex3fv((GLfloat*) &vertices[caras[i]._0]);
		glNormal3fv((GLfloat*) &normales_vertices[caras[i]._1]);
		glVertex3fv((GLfloat*) &vertices[caras[i]._1]);
		glNormal3fv((GLfloat*) &normales_vertices[caras[i]._2]);
		glVertex3fv((GLfloat*) &vertices[caras[i]._2]);
	}

	glEnd();
	glDisable(GL_LIGHTING);
}

void _triangulos3D::draw_textura(){
	draw_textura();
}

void _cubo::draw_textura(){

	_textura textura(1, "caja.jpg");
						// cara 1
	GLfloat caras[] = {vertices[7].x, vertices[7].y, vertices[7].z,
					vertices[3].x, vertices[3].y, vertices[3].z,
					vertices[2].x, vertices[2].y, vertices[2].z,
					vertices[6].x, vertices[6].y, vertices[6].z,
						// cara 2
					vertices[4].x, vertices[4].y, vertices[4].z,
					vertices[7].x, vertices[7].y, vertices[7].z,
					vertices[3].x, vertices[3].y, vertices[3].z,
					vertices[0].x, vertices[0].y, vertices[0].z,
						// cara 3
					vertices[4].x, vertices[4].y, vertices[4].z,
					vertices[0].x, vertices[0].y, vertices[0].z,
					vertices[1].x, vertices[1].y, vertices[1].z,
					vertices[5].x, vertices[5].y, vertices[5].z,
						// cara 4
					vertices[2].x, vertices[2].y, vertices[2].z,
					vertices[1].x, vertices[1].y, vertices[1].z,
					vertices[5].x, vertices[5].y, vertices[5].z,
					vertices[6].x, vertices[6].y, vertices[6].z,
						// cara 5
					vertices[3].x, vertices[3].y, vertices[3].z,
					vertices[0].x, vertices[0].y, vertices[0].z,
					vertices[1].x, vertices[1].y, vertices[1].z,
					vertices[2].x, vertices[2].y, vertices[2].z,
						// cara 6
					vertices[6].x, vertices[6].y, vertices[6].z,
					vertices[7].x, vertices[7].y, vertices[7].z,
					vertices[4].x, vertices[4].y, vertices[4].z,
					vertices[5].x, vertices[5].y, vertices[5].z
				};

	GLfloat vertices_texturas[] = {

								 1.0,0.0,
								 0.5,0.0,
								 0.5,0.5,
								 1,0.5,

								 0.0,0.5,
								 0.5,0.5,
								 0.5,1.0,
								 0,1,

								 1.0,0.0,
								 0.5,0.0,
								 0.5,0.5,
								 1,0.5,
								 
									////
								 
								 0.5,1.0,
								 0,1,
								 0.0,0.5,
								 0.5,0.5,
								 

								 0.5,0,
								 0,0.0,
								 0,0.5,
								 0.5,0.5,

								 1.0,0.5,  //6
								 1,1,      //7
								 0.5,1.0,  //4
								 0.5,0.5,  //5
								 
								};

	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState (GL_TEXTURE_COORD_ARRAY_EXT);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textura.id_textura);

	glVertexPointer(3, GL_FLOAT, 0, caras);
	glTexCoordPointer(2, GL_FLOAT, 0, vertices_texturas);

	glDrawArrays(GL_QUADS, 0, 24);	// 24 porque tiene que dibujar 6 caras por 4 arrays en cada cara

	glDisableClientState(GL_VERTEX_ARRAY);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}

void  _tablero::draw_textura(){
	_textura textura(1, "puente_rio.jpg");

	GLfloat caras[] = {vertices[0].x, vertices[0].z,
					vertices[4].x, vertices[4].z,
					vertices[5].x, vertices[5].z,
					vertices[1].x, vertices[1].z,

					vertices[1].x, vertices[1].z,
					vertices[5].x, vertices[5].z,
					vertices[6].x, vertices[6].z,
					vertices[2].x, vertices[2].z,

					vertices[2].x, vertices[2].z,
					vertices[6].x, vertices[6].z,
					vertices[7].x, vertices[7].z,
					vertices[3].x, vertices[3].z,

					vertices[4].x, vertices[4].z,
					vertices[8].x, vertices[8].z,
					vertices[9].x, vertices[9].z,
					vertices[5].x, vertices[5].z,

					vertices[5].x, vertices[5].z,
					vertices[9].x, vertices[9].z,
					vertices[10].x, vertices[10].z,
					vertices[6].x, vertices[6].z,

					vertices[6].x, vertices[6].z,
					vertices[10].x, vertices[10].z,
					vertices[11].x, vertices[11].z,
					vertices[7].x, vertices[7].z,

					vertices[8].x, vertices[8].z,
					vertices[12].x, vertices[12].z,
					vertices[13].x, vertices[13].z,
					vertices[9].x, vertices[9].z,

					vertices[9].x, vertices[9].z,
					vertices[13].x, vertices[13].z,
					vertices[14].x, vertices[14].z,
					vertices[10].x, vertices[10].z,

					vertices[10].x, vertices[10].z,
					vertices[14].x, vertices[14].z,
					vertices[15].x, vertices[15].z,
					vertices[11].x, vertices[11].z
					};

	GLfloat vertices_texturas[] = {
									//
								 0.0,0.0,
								 0.0,0.33,
								 0.33,0.33,
								 0.33,0,
									//
								 0.33,0.0,
								 0.33,0.33,
								 0.66,0.33,
								 0.66,0.0,
									// *************
								 0.66,0.0,
								 0.66,0.33,
								 1,0.33,
								 1,0,

								 0.0,0.33,
								 0.0,0.66,
								 0.33,0.66,
								 0.33,0.33,

								 0.33,0.33,
								 0.33,0.66,
								 0.66,0.66,
								 0.66,0.33,
									//**************
								 0.66,0.33,
								 0.66,0.66,
								 1,0.66,
								 1,0.33,

								 0.0,0.66,
								 0.0,1,
								 0.33,1,
								 0.33,0.66,
	
								 0.33,0.66,
								 0.33,1,
								 0.66,1,
								 0.66,0.66,
									// *************
								 0.66,0.66,
								 0.66,1,
								 1,1,
								 1,0.66
								};

	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState (GL_TEXTURE_COORD_ARRAY_EXT);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textura.id_textura);

	glVertexPointer(2, GL_FLOAT, 0, caras);
	glTexCoordPointer(2, GL_FLOAT, 0, vertices_texturas);

	glDrawArrays(GL_QUADS, 0, 36);

	glDisableClientState(GL_VERTEX_ARRAY);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}

void  _piramide::draw_textura(){ };
void  _objeto_ply::draw_textura(){ };
void  _rotacion::draw_textura(){  };


//*************************************************************************
// dibujar con distintos modos
//*************************************************************************


void _triangulos3D::draw(Modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Material mat)
{
switch (modo){
	case Puntos:draw_puntos(r1, g1, b1, grosor);break;
	case Lineas:draw_aristas(r1, g1, b1, grosor);break;
	case Ajedrez:draw_solido_ajedrez(r1, g1, b1, r2, g2, b2);break;
	case Solido:draw_solido(r1, g1, b1);break;
	case Solido_Iluminado_Plano:draw_iluminacion_plana(mat);break;
	case Solido_Iluminado_Gouraud:draw_iluminacion_suave(mat);break;
	case Texturas:draw_textura();break;
	}
}

//*************************************************************************
// clase tablero
//*************************************************************************

_tablero::_tablero(int filas, int columnas, float tam, float al)
{

float anchura_cada_cuadrado = tam/columnas;
float altura_cada_cuadrado = al/filas;

_vertex3f vertice_aux;
_vertex3i cara_aux;

//vertices 
vertices.resize((filas+1)*(columnas+1)); 

float vertice_x = -tam/2;
float vertice_z = al/2;

int n_vertice = 0;

for(int i = 0; i < filas+1; ++i){
	for(int j = 0; j < columnas+1; ++j){
		vertice_aux.x = vertice_x;
		vertice_aux.y = 0;
		vertice_aux.z = vertice_z;
		vertices[n_vertice] = vertice_aux;

		n_vertice++;
		vertice_x += anchura_cada_cuadrado;
	}

	vertice_x = -tam/2;
	vertice_z -= altura_cada_cuadrado;
}

caras.resize(filas*columnas*2);

for(int i = 0; i < filas; ++i){
	for(int j = 0; j < columnas; ++j){
		cara_aux._0 = (columnas+1)*i + j;
		cara_aux._1 = (columnas+1)*(i+1) + j;
		cara_aux._2 = (columnas+1)*(i+1) + (j+1);
		caras.push_back(cara_aux);

		cara_aux._0 = (columnas+1)*(i+1) + (j+1);
		cara_aux._1 = (columnas+1)*i + (j+1);
		cara_aux._2 = (columnas+1)*i + j;
		caras.push_back(cara_aux);
	}
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

_chasis::_chasis(){
	base = _cubo(0.5);
	rodamientos = _cilindro(0.30,2,25,3);
	altura = 0.6;
}

void _chasis::draw(Modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Material mat){

glPushMatrix();
glScalef(1,0.3,1);
base.draw(modo,r1,g1,b1,r2,g2,b2,grosor, mat);
glPopMatrix();

glPushMatrix();
glTranslatef(-1,0.3,-1);
glRotatef(90,1,0,0);
rodamientos.draw(modo,r1,g1,b1,r2,g2,b2,grosor, mat);
glPopMatrix();


glPushMatrix();
glTranslatef(1,0.3,-1);
glRotatef(90,1,0,0);
rodamientos.draw(modo,r1,g1,b1,r2,g2,b2,grosor, mat);
glPopMatrix();


}

_cabina::_cabina(){
	base = _cilindro(0.7,0.25,25,3);
	cabina = _cubo(0.25);
	techo = _piramide(0.5,0.5);

	altura = 0.2;
	anchura = 0.65;

}

void _cabina::draw(Modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor,  Material mat){
base.draw(modo,r1,g1,b1,r2,g2,b2,grosor, mat);

glPushMatrix();
glTranslatef(0,0.25,0);
cabina.draw(modo,r1,g1,b1,r2,g2,b2,grosor, mat);
glPopMatrix();


glPushMatrix();
glTranslatef(0,1.25,0);
techo.draw(modo,r1,g1,b1,r2,g2,b2,grosor, mat);
glPopMatrix();

}

_brazo::_brazo(){
	barras = _cono(0.1,2.5,25,2);
	altura = 2;
	anchura = 1.77;
}

void _brazo::draw(Modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor,  Material mat){
glPushMatrix();
glTranslatef(0,0,-0.25);
glRotatef(-45,0,0,1);
glRotatef(6,1,0,0);
barras.draw(modo,r1,g1,b1,r2,g2,b2,grosor, mat);
glPopMatrix();


glPushMatrix();
glTranslatef(0,0,+0.25);
glRotatef(-45,0,0,1);
glRotatef(-6,1,0,0);
barras.draw(modo,r1,g1,b1,r2,g2,b2,grosor, mat);
glPopMatrix();

}

_cuerda::_cuerda(){
	barra = _cilindro(0.01,2,25,3);
	altura =  2;
}

void _cuerda::draw(Modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor,  Material mat){
glPushMatrix();
glTranslatef(0,-2,0);
glPushMatrix();
barra.draw(modo,r1,g1,b1,r2,g2,b2,grosor,mat);
glPopMatrix();
glPopMatrix();
}

_bola::_bola(){
	b = _esfera(0.25,20,20,3);
}

void _bola::draw(Modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor ,Material mat){
glPushMatrix();
glTranslatef(0,-0.25,0);
glPushMatrix();
b.draw(modo,r1,g1,b1,r2,g2,b2,grosor, mat);
glPopMatrix();
glPopMatrix();
}

_demoledor::_demoledor(){
	giro_cabina = 0;
	giro_brazo = 0;
	giro_brazo_min = 0;
	giro_brazo_max = 10;
	giro_cuerda = 0;
	giro_cuerda_max = 20;
	giro_cuerda_min = -10;
	giro_bola = 0;
	giro_bola_min = -20;
	giro_bola_max = 20;
}

void _demoledor::draw(Modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor, Material mat){
glPushMatrix();
chasis.draw(modo,r1,g1,b1,r2,g2,b2,grosor, mat);


glRotatef(giro_cabina,0,1,0);
glPushMatrix();
glTranslatef(0,chasis.altura,0);
cabina.draw(modo,r1,g1,b1,r2,g2,b2,grosor, mat);
glPopMatrix();

glRotatef(giro_brazo,0,0,1);
glPushMatrix();
glTranslatef(cabina.anchura,cabina.altura+chasis.altura,0);
brazo.draw(modo,r1,g1,b1,r2,g2,b2,grosor, mat);
glPopMatrix();


glPushMatrix();
glTranslatef(brazo.anchura+cabina.anchura,chasis.altura+brazo.altura,0);
glRotatef(giro_cuerda,0,0,1);
cuerda.draw(modo,r1,g1,b1,r2,g2,b2,grosor, mat);



glPushMatrix();
glTranslatef(0,-brazo.altura,0);
glRotatef(giro_bola,0,0,1);
bola.draw(modo,r1,g1,b1,r2,g2,b2,grosor, mat);
glPopMatrix();

glPopMatrix();


glPopMatrix();
}

_luz::_luz(GLenum indice_luz, _vertex4f punto_luz, _vertex4f luz_ambiente, _vertex4f luz_difusa, _vertex4f luz_especular){
	this->indice_luz = indice_luz;
	this->punto_luz = punto_luz;
	this->luz_ambiente = luz_ambiente;
	this->luz_difusa = luz_difusa;
	this->luz_especular = luz_especular;

	pos_x = punto_luz[0];
	pos_y = punto_luz[1];
	pos_z = punto_luz[2];
	angx = 0;
	angy = 0;
	angz = 0;
	a = 0;
	b = 0;
	c = 0;
}

//************************************************************************
// Objeto luz
//************************************************************************

void _luz::activar(){
	glEnable(GL_LIGHTING);
	glEnable(indice_luz);
	
	glLightfv(indice_luz, GL_AMBIENT, (GLfloat*) &luz_ambiente);
	glLightfv(indice_luz, GL_DIFFUSE, (GLfloat*) &luz_difusa);
	glLightfv(indice_luz, GL_SPECULAR, (GLfloat*) &luz_especular);
	glLightfv(indice_luz, GL_POSITION, (GLfloat*) &punto_luz);
}

void _luz::desactivar(){
	glDisable(indice_luz);
	glDisable(GL_LIGHTING);	
}

void _luz::transformar(GLenum indice_luz, int a, int b, int c, float ang, float x, float y, float z){
	glPushMatrix();
	glTranslatef(x,y,z);
	glRotatef(ang,a,b,c);
	glLightfv(indice_luz, GL_POSITION, (GLfloat*) &punto_luz);
	glPopMatrix();

	cout << "Posición: " << "(" << x << "," << y << "," << z << ")" << endl;
	cout << "Rotación eje x: " << angx << endl;
	cout << "Rotación eje y: " << angy << endl;
	cout << "Rotación eje z: " << angz << endl;
	cout << endl;
}
