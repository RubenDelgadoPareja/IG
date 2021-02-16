//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include "objetos_B5.h"
#include "file_ply_stl.hpp"
#include <algorithm>




//enum Objeto { Piramide, Cubo, Objeto_ply, Rotacion};
//Objeto obj = Piramide;
//enum Modo { Puntos, Lineas, Solido, Ajedrez};
//Modo mod = Lineas;


//**************************************************************************
// Funcciones para construir modelos sólidos poligonales
//**************************************************************************

void construir_cubo(float tam, solido *cubo)
{

cubo->n_v=8;
cubo->n_c=12;
cubo->ver=(vertices *)malloc(8*sizeof(vertices));
cubo->car=(caras *)malloc(12*sizeof(caras));

cubo->r=0.9;cubo->g=0.6;cubo->b=0.2;

cubo->ver[0].coord[0]=-tam;cubo->ver[0].coord[1]=-tam;cubo->ver[0].coord[2]=tam;
cubo->ver[1].coord[0]=tam;cubo->ver[1].coord[1]=-tam;cubo->ver[1].coord[2]=tam;
cubo->ver[2].coord[0]=tam;cubo->ver[2].coord[1]=tam;cubo->ver[2].coord[2]=tam;
cubo->ver[3].coord[0]=-tam;cubo->ver[3].coord[1]=tam;cubo->ver[3].coord[2]=tam;
cubo->ver[4].coord[0]=-tam;cubo->ver[4].coord[1]=-tam;cubo->ver[4].coord[2]=-tam;
cubo->ver[5].coord[0]=tam;cubo->ver[5].coord[1]=-tam;cubo->ver[5].coord[2]=-tam;
cubo->ver[6].coord[0]=tam;cubo->ver[6].coord[1]=tam;cubo->ver[6].coord[2]=-tam;
cubo->ver[7].coord[0]=-tam;cubo->ver[7].coord[1]=tam;cubo->ver[7].coord[2]=-tam;

cubo->car[0].ind_c[0]=0;cubo->car[0].ind_c[1]=1;cubo->car[0].ind_c[2]=3;
cubo->car[1].ind_c[0]=3;cubo->car[1].ind_c[1]=1;cubo->car[1].ind_c[2]=2;
cubo->car[2].ind_c[0]=1;cubo->car[2].ind_c[1]=5;cubo->car[2].ind_c[2]=2;
cubo->car[3].ind_c[0]=5;cubo->car[3].ind_c[1]=6;cubo->car[3].ind_c[2]=2;
cubo->car[4].ind_c[0]=5;cubo->car[4].ind_c[1]=4;cubo->car[4].ind_c[2]=6;
cubo->car[5].ind_c[0]=4;cubo->car[5].ind_c[1]=7;cubo->car[5].ind_c[2]=6;
cubo->car[6].ind_c[0]=0;cubo->car[6].ind_c[1]=7;cubo->car[6].ind_c[2]=4;
cubo->car[7].ind_c[0]=0;cubo->car[7].ind_c[1]=3;cubo->car[7].ind_c[2]=7;
cubo->car[8].ind_c[0]=3;cubo->car[8].ind_c[1]=2;cubo->car[8].ind_c[2]=7;
cubo->car[9].ind_c[0]=2;cubo->car[9].ind_c[1]=6;cubo->car[9].ind_c[2]=7;
cubo->car[10].ind_c[0]=0;cubo->car[10].ind_c[1]=1;cubo->car[10].ind_c[2]=4;
cubo->car[11].ind_c[0]=1;cubo->car[11].ind_c[1]=5;cubo->car[11].ind_c[2]=4;  

}


void construir_piramide(float tam, float al, solido *piramide)
{
piramide->n_v=5;
piramide->n_c=6;
piramide->ver=(vertices *)malloc(5*sizeof(vertices));
piramide->car=(caras *)malloc(6*sizeof(caras));

piramide->r=0.9;piramide->g=0.6;piramide->b=0.2;

// asignar puntos y caras  
piramide->ver[0].coord[0]=-tam;piramide->ver[0].coord[1]=0;piramide->ver[0].coord[2]=tam;
piramide->ver[1].coord[0]=tam;piramide->ver[1].coord[1]=0;piramide->ver[1].coord[2]=tam;
piramide->ver[2].coord[0]=tam;piramide->ver[2].coord[1]=0;piramide->ver[2].coord[2]=-tam;
piramide->ver[3].coord[0]=-tam;piramide->ver[3].coord[1]=0;piramide->ver[3].coord[2]=-tam;
piramide->ver[4].coord[0]=0;piramide->ver[4].coord[1]=al;piramide->ver[4].coord[2]=0;

piramide->car[0].ind_c[0]=0;piramide->car[0].ind_c[1]=1;piramide->car[0].ind_c[2]=4;
piramide->car[1].ind_c[0]=1;piramide->car[1].ind_c[1]=2;piramide->car[1].ind_c[2]=4;
piramide->car[2].ind_c[0]=2;piramide->car[2].ind_c[1]=3;piramide->car[2].ind_c[2]=4;
piramide->car[3].ind_c[0]=3;piramide->car[3].ind_c[1]=0;piramide->car[3].ind_c[2]=4;
piramide->car[4].ind_c[0]=3;piramide->car[4].ind_c[1]=1;piramide->car[4].ind_c[2]=0;
piramide->car[5].ind_c[0]=3;piramide->car[5].ind_c[1]=2;piramide->car[5].ind_c[2]=1;
  
}


void construir_ply(char *file, solido *ply){

}

void construir_rotacion(vector<_vertex3f> perfil, int num, int tapas, solido *rotacion){
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
	rotacion->n_v = num_aux * num + 2;
	rotacion->n_c= num * perfil.size()* 4;
	rotacion->ver = new vertices[rotacion->n_v*sizeof(vertices)];
	rotacion->car = new caras[rotacion->n_c*sizeof(caras)];
	rotacion->r = 0.9; rotacion->g = 0.6; rotacion->b = 0.2;  

	for (j=0;j<num;j++){
		for (i=0;i<num_aux;i++){
	      vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
	                    perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
	      vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
	                    perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
	      vertice_aux.y=perfil[i].y;

	      //vertices[i+j*num_aux]=vertice_aux;
		  rotacion->ver[i+j*num_aux].coord[0] = vertice_aux.x;
		  rotacion->ver[i+j*num_aux].coord[1] = vertice_aux.y;
		  rotacion->ver[i+j*num_aux].coord[2] = vertice_aux.z;
	     }
	  }

	int numero_caras = 0;

	// tratamiento de las caras  
	for (j=0;j<num;j++){
		for (i=0;i<num_aux-1;i++){
	  		if(rotacion->ver[i+1+j*num_aux].coord!=rotacion->ver[i+1+((j+1)%num)*num_aux].coord){
	  			cara_aux._0=i+((j+1)%num)*num_aux;
      			cara_aux._1=i+1+((j+1)%num)*num_aux;
      			cara_aux._2=i+1+j*num_aux;
      			
				rotacion->car[numero_caras].ind_c[0] = cara_aux._0;
				rotacion->car[numero_caras].ind_c[1] = cara_aux._1;
				rotacion->car[numero_caras].ind_c[2] = cara_aux._2;

				numero_caras++;
	 		 }
      
      		cara_aux._0=i+1+j*num_aux;
      		cara_aux._1=i+j*num_aux;
      		cara_aux._2=i+((j+1)%num)*num_aux;
      		//caras.push_back(cara_aux);
			
			rotacion->car[numero_caras].ind_c[0] = cara_aux._0;
			rotacion->car[numero_caras].ind_c[1] = cara_aux._1;
			rotacion->car[numero_caras].ind_c[2] = cara_aux._2;
			
			numero_caras++;
     }
  }


  	//Tapa superior 
  	if (fabs(perfil[num_aux-1].x)>0.0 && (tapas == 1 || tapas== 3)){ 
		vertice_aux.x=0;
		vertice_aux.y=perfil[num_aux-1].y;
		vertice_aux.z=0;
		rotacion->ver[rotacion->n_v-2].coord[0] = vertice_aux.x;
		rotacion->ver[rotacion->n_v-2].coord[1] = vertice_aux.y;
		rotacion->ver[rotacion->n_v-2].coord[2] = vertice_aux.z;

		for(i=0;i<num-1;i++){
      		cara_aux.x=num_aux-1+i*num_aux;
      		cara_aux.y=num_aux-1+(i+1)*num_aux;
      		cara_aux.z=rotacion->n_v-2;
      		//caras.push_back(cara_aux);

			rotacion->car[numero_caras].ind_c[0]=cara_aux._0;
			rotacion->car[numero_caras].ind_c[1]=cara_aux._1;
			rotacion->car[numero_caras].ind_c[2]=cara_aux._2;
			numero_caras++;
   		}
    		cara_aux.x=num_aux-1+(num-1)*num_aux;
    		cara_aux.y=num_aux-1;
    		cara_aux.z=rotacion->n_v-2;
			rotacion->car[numero_caras].ind_c[0]=cara_aux._0;
			rotacion->car[numero_caras].ind_c[1]=cara_aux._1;
			rotacion->car[numero_caras].ind_c[2]=cara_aux._2;
			numero_caras++;
    		//caras.push_back(cara_aux);
  	}
	//Tapa inferior

	if (fabs(perfil[0].x)>0.0  && (tapas == 2 || tapas== 3) )
	{
		vertice_aux.x=0;
		vertice_aux.y=perfil[0].y;
		vertice_aux.z=0;
		//vertices.push_back(vertice_aux);

		rotacion->ver[rotacion->n_v-1].coord[0] = vertice_aux.x;
		rotacion->ver[rotacion->n_v-1].coord[1] = vertice_aux.y;
		rotacion->ver[rotacion->n_v-1].coord[2] = vertice_aux.z;


	 	for(i=0;i<num-1;i++){
      		cara_aux.x=i*num_aux;
      		cara_aux.y=(i+1)*num_aux;
      		cara_aux.z=rotacion->n_v-1;
      		//caras.push_back(cara_aux);

			rotacion->car[numero_caras].ind_c[0]=cara_aux._0;
			rotacion->car[numero_caras].ind_c[1]=cara_aux._1;
			rotacion->car[numero_caras].ind_c[2]=cara_aux._2;
			numero_caras++;  
    	}
    	cara_aux.x=(num-1)*num_aux;
    	cara_aux.y=0;
    	cara_aux.z=rotacion->n_v-1;

			rotacion->car[numero_caras].ind_c[0]=cara_aux._0;
			rotacion->car[numero_caras].ind_c[1]=cara_aux._1;
			rotacion->car[numero_caras].ind_c[2]=cara_aux._2;
			numero_caras++;
    	//caras.push_back(cara_aux);
	} 
 


}


void construir_cilindro(float radio,float altura, int num_caras, int tapas, solido *cilindro){
	int num = num_caras;
	int t = tapas;
	_vertex3f aux;
	vector<_vertex3f> perfil;

	aux.x = radio ; aux.y = altura; aux.z = 0.0;
	perfil.push_back(aux);
	aux.x = radio ; aux.y = 0.0; aux.z = 0.0;
	perfil.push_back(aux);

	construir_rotacion(perfil,num_caras,tapas,cilindro);
}

void construir_cono(float radio,float altura, int num_caras, int tapas, solido *cono){
	int num = num_caras;
	int t = tapas;
	_vertex3f aux;
	vector<_vertex3f> perfil;

	aux.x = radio ; aux.y = 0.0; aux.z = 0.0;
	perfil.push_back(aux);
	aux.x = 0.0 ; aux.y = altura; aux.z = 0.0;
	perfil.push_back(aux);

	construir_rotacion(perfil,num_caras,tapas,cono);
}

void construir_esfera(float radio,int lat, int lon, int tapas, solido *esfera){
	int num = lon;
	int t = tapas;
	_vertex3f aux;
	vector<_vertex3f> perfil;


	float increRad = M_PI/lat;
	float angulo = 0;

	aux.x=0.0; aux.y=radio; aux.z=0.0;
	perfil.push_back(aux);

	for(int i=0; i < lat-1; ++i){
		angulo += increRad;

		aux.x = radio*sin(angulo);
		aux.y = radio*cos(angulo);
		aux.z = 0.0;

		perfil.push_back(aux);
	}

	aux.x=0.0; aux.y=-radio; aux.z=0.0;
	perfil.push_back(aux);

	construir_rotacion(perfil,num,tapas,esfera);
}


//**************************************************************************
// Funciones de visualización
//**************************************************************************


void draw_puntos(vertices *ver, int n_v)
{
   
    glColor3f(0,0,0);
    glPointSize(10);

    glBegin(GL_POINTS);
    for (unsigned i=0;i<n_v;i++){
        glVertex3f(ver[i].coord[0],ver[i].coord[1],ver[i].coord[2]);
        }
    glEnd();q
}


void draw_solido(solido *malla, float r, float g, float b, int modo)
{
  
  int n_c,n_v,i;
  n_c=malla->n_c;
  if (modo==1) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glColor3f(r,g,b);
  glLineWidth(3);
  glBegin(GL_TRIANGLES);
  for (i=0;i<n_c;i++)
      { n_v=malla->car[i].ind_c[0];
        glVertex3f(malla->ver[n_v].coord[0], malla->ver[n_v].coord[1], malla->ver[n_v].coord[2]);
	n_v=malla->car[i].ind_c[1];
        glVertex3f(malla->ver[n_v].coord[0], malla->ver[n_v].coord[1], malla->ver[n_v].coord[2]);
	n_v=malla->car[i].ind_c[2];
        glVertex3f(malla->ver[n_v].coord[0], malla->ver[n_v].coord[1], malla->ver[n_v].coord[2]);
    }
   glEnd();
  
}

void draw_solido_ajedrez(solido *malla, float r1, float g1, float b1, float r2, float g2, float b2)
{
  
  int n_c,n_v,i;
  n_c=malla->n_c;
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  glBegin(GL_TRIANGLES);
  for (i=0;i<n_c;i++)
      { if (i%2==0)  glColor3f(r1,g1,b1);
         else glColor3f(r2,g2,b2);  
	n_v=malla->car[i].ind_c[0];
        glVertex3f(malla->ver[n_v].coord[0], malla->ver[n_v].coord[1], malla->ver[n_v].coord[2]);
	n_v=malla->car[i].ind_c[1];
        glVertex3f(malla->ver[n_v].coord[0], malla->ver[n_v].coord[1], malla->ver[n_v].coord[2]);
	n_v=malla->car[i].ind_c[2];
        glVertex3f(malla->ver[n_v].coord[0], malla->ver[n_v].coord[1], malla->ver[n_v].coord[2]);
    }
   glEnd();
  
}


void draw_seleccion_color(solido *malla, int r, int g, int b)
{
  
  int n_c,n_v,i;
  n_c=malla->n_c;
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glColor3ub(r,g,b);
  glBegin(GL_TRIANGLES);
 
  for (i=0;i<n_c;i++)
      { n_v=malla->car[i].ind_c[0];
        glVertex3f(malla->ver[n_v].coord[0], malla->ver[n_v].coord[1], malla->ver[n_v].coord[2]);
	n_v=malla->car[i].ind_c[1];
        glVertex3f(malla->ver[n_v].coord[0], malla->ver[n_v].coord[1], malla->ver[n_v].coord[2]);
	n_v=malla->car[i].ind_c[2];
        glVertex3f(malla->ver[n_v].coord[0], malla->ver[n_v].coord[1], malla->ver[n_v].coord[2]);
    }
   glEnd();
}

