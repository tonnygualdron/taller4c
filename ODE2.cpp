#include <iostream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cmath>

float norma(float x, float y);
float ax(float c, float m,float vx, float vy, float g);
float ay(float c, float m,float vx, float vy, float g);
float rk4(float c, float m,float vx, float vy, float g, float x,float y,float h, float t, FILE *d);
void imprimir(float t,float x, float y,float vx, float vy, FILE *d);

int main()
{
 /* Constantes del movimiento
 Despues de haber sido definidas no cambia en la ejecución*/
 
 float g =10.0; //Valor de Gravedad
 float m =0.2;  //Masa del proyectil en Kg
 float c = 0.2;  //Factor de friccion
 float dt =0.001; //saltos de tiempo valor seleccionado por el usuario
 float PI = 3.141592654; // Para convertir de grados a radianes
 float theta; //angulo de la velocidad

 //Variables del movimiento
 float x0;
 float y0;
 float vx0;
 float vy0;
 float t0=0;

  
 //Primera parte x(t=0)=(0,0)
 //Theta 45 grados
 //v=300 m/s
 x0=0;
 y0=0;

 theta=45.0*PI/180.0;
 vx0=300.0*cos(theta);
 vy0=300.0*sin(theta);
 
 //lista x,y,vx,vy
 float x;
 float y;
 float vx;
 float vy;
 float t;
 
 x=x0;
 y=y0;
 vx=vx0;
 vy=vy0;
 t=t0;
 
 FILE *output;
 output=fopen("45grados.txt", "w");
 
 float xf = rk4(c,m,vx, vy,g,x,y,dt, t, output);
 cout << "La distancia recorrida fue " << xf << " m." << endl;
 
fclose(output);

 
 return 0;
}

/*Norma de un vector componetes x y y*/
float norma(float x, float y){
 float r2 = pow(x,2) + pow(y,2);
 float r= sqrt(r2);
 return r;
}


/*Aceleracion en x*/
float ax(float c, float m,float vx, float vy, float g){
 float a = -(c*vx*norma(vx,vy))/m;
 return a;
}

/*Aceleracion en y*/
float ay(float c, float m,float vx, float vy, float g){
 float a = -g-((c*vx*norma(vx,vy))/m);
 return a;
}

void imprimir(float t,float x, float y,float vx, float vy, FILE *d){
 fprintf(d, "%f %f %f %f %f\n", t,x,y,vx,vy);
}

float rk4(float c, float m,float vx, float vy, float g, float x,float y,float h, float t, FILE *d){
 bool indicador = true;
 int i = 0;
 imprimir(t,x,y,vx, vy, d);
 while(indicador){
  float k1x=0.0;
  float k2x=0.0;
  float k3x=0.0;
  float k4x=0.0;

  float k1y=0.0;
  float k2y=0.0;
  float k3y=0.0;
  float k4y=0.0;
  
  float k1xi=0.0;
  float k2xi=0.0;
  float k3xi=0.0;
  float k4xi=0.0;

  float k1yi=0.0;
  float k2yi=0.0;
  float k3yi=0.0;
  float k4yi=0.0;

  float xActual=0.0;
  float yActual=0.0;
  float vxActual=0.0;
  float vyActual=0.0;

  k1x = ax(c,m,vx,vy,g);
  k1y = ay(c,m,vx,vy,g);

  k2x = ax(c,m,vx+0.5*h*k1x,vy+0.5*h*k1y,g);
  k2y = ay(c,m,vx+0.5*h*k1x,vy+0.5*h*k1y,g);

  k3x = ax(c,m,vx+0.5*h*k2x,vy+0.5*h*k2y,g);
  k3y = ay(c,m,vx+0.5*h*k2x,vy+0.5*h*k2y,g);

  k4x = ax(c,m,vx+h*k3x,vy+h*k3y,g);
  k4y = ay(c,m,vx+h*k3x,vy+h*k3y,g);
  

  vxActual= vx + ((1.0/6.0)*(k1x+2*k2x+2*k3x+k4x)*h);
  vyActual= vy + ((1.0/6.0)*(k1y+2*k2y+2*k3y+k4y)*h);

  
  k1xi = vx;
  k1yi = vy;

  k2xi = vx + k1xi*h*0.5;
  k2yi = vy + k1yi*h*0.5;

  k3xi = vx + k2xi*h*0.5;
  k3yi = vy + k2yi*h*0.5;

  k4xi = vx + k3xi*h;
  k4yi = vy + k3yi*h;
  
  xActual= x + ((1.0/6.0)*(k1xi+2*k2xi+2*k3xi+k4xi)*h);
  yActual= y + ((1.0/6.0)*(k1yi+2*k2yi+2*k3yi+k4yi)*h);

  x=xActual;
  y=yActual;
  vx=vxActual;
  vy=vyActual;
  t=t+h;
  if(y>=0){
   imprimir(t,x,y,vx, vy, d);
  }
  else{
   indicador = false;
  }
 }
 return x;
}
