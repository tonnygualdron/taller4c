#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cmath>

using namespace std;

float norma(float x, float y);
float ax(float c, float m,float vx, float vy, float g);
float ay(float c, float m,float vx, float vy, float g);
void imprimir(float t,float x, float y,float vx, float vy, FILE *d);
float rk4(float c, float m,float vx, float vy, float g, float x,float y,float h, float t, FILE *d);
void variosTheta(float c, float m,float v, float g, float x,float y,float h, float t,float thetai, float thetaf, FILE *d);

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

 //condiciones iniciales del movimiento
 theta=45.0*PI/180.0;
 float x0=0;
 float y0=0;
 float v0=300;
 float vx0=v0*cos(theta);
 float vy0=v0*sin(theta);;
 float t0=0;
 
 //Datos del movimiento x,y,vx,vy
 float x;
 float y;
 float vx;
 float vy;
 float t;
 
 //Se inicializan las variables en las condiciones iniciales
 x=x0;
 y=y0;
 vx=vx0;
 vy=vy0;
 t=t0;

  
 //Se ejecuta runge kutta 4 para estas condiciones iniciales
 //Se generara un documento de 5 columnas con los datos del movimiento
 //El orden de las columnas es: t x y vx vy
 FILE *output;
 output=fopen("45grados.txt", "w");
 float xf = rk4(c,m,vx,vy,g,x,y,dt,t,output);
 
 //Se imprime la distancia reccorida
 cout << "La distancia recorrida fue " << xf << " m." << endl;
 
 //Se cierra el documento
 fclose(output);
 
 //Ahora se probara este metodo para theta entre 10 hasta 70 grados
 FILE *output2;
 output2=fopen("10-70grados.txt", "w");
 variosTheta(c,m,v0,g,x,y,dt,t,10,70,output2);
 fclose(output2);

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

/*Imprime los parametros de entrada en el mismo orden en un archivo d */
void imprimir(float t,float x, float y,float vx, float vy, FILE *d){
 fprintf(d, "%f %f %f %f %f\n", t,x,y,vx,vy);
}


/*Ejecuta el metodo runge kutta de orden 4 para un tiro parabolico, halla las posiciones x/y y las velocidades vx/vy las imprime en un documeto d.*/
float rk4(float c, float m,float vx, float vy, float g, float x,float y,float h, float t, FILE *d){
 //El indicador funciona como controlador que frena rk4 cuando vx<=0 o/y y<=0
 bool indicador = true;
 //imprime las condiciones iniciales
 imprimir(t,x,y,vx, vy,d);
 while(indicador){
  // los runge kutta. K1-2-3-4, genrados por la velociadad por componetes
  float k1x=0.0;
  float k2x=0.0;
  float k3x=0.0;
  float k4x=0.0;
  float k1y=0.0;
  float k2y=0.0;
  float k3y=0.0;
  float k4y=0.0;
  
  // los runge kutta. K1-2-3-4, genrados para las posiciones
  float k1xi=0.0;
  float k2xi=0.0;
  float k3xi=0.0;
  float k4xi=0.0;
  float k1yi=0.0;
  float k2yi=0.0;
  float k3yi=0.0;
  float k4yi=0.0;

  //Posiciones y velocidades actuales calculadas
  float xActual=0.0;
  float yActual=0.0;
  float vxActual=0.0;
  float vyActual=0.0;

  // Cacula K1-2-3-4 para la velociad por componentes
  k1x = ax(c,m,vx,vy,g);
  k1y = ay(c,m,vx,vy,g);

  k2x = ax(c,m,vx+0.5*h*k1x,vy+0.5*h*k1y,g);
  k2y = ay(c,m,vx+0.5*h*k1x,vy+0.5*h*k1y,g);

  k3x = ax(c,m,vx+0.5*h*k2x,vy+0.5*h*k2y,g);
  k3y = ay(c,m,vx+0.5*h*k2x,vy+0.5*h*k2y,g);

  k4x = ax(c,m,vx+h*k3x,vy+h*k3y,g);
  k4y = ay(c,m,vx+h*k3x,vy+h*k3y,g);
  
  //Halla cada conponente de la velociada en base runge kutta orden 4.
  // Utiliza k1-2-3-4 de la velocidad
  vxActual= vx + ((1.0/6.0)*(k1x+2*k2x+2*k3x+k4x)*h);
  vyActual= vy + ((1.0/6.0)*(k1y+2*k2y+2*k3y+k4y)*h);

  //Calcula los k1-2-3-4 para las posicion por componentes
  k1xi = vx;
  k1yi = vy;

  k2xi = vx + k1xi*h*0.5;
  k2yi = vy + k1yi*h*0.5;

  k3xi = vx + k2xi*h*0.5;
  k3yi = vy + k2yi*h*0.5;

  k4xi = vx + k3xi*h;
  k4yi = vy + k3yi*h;

  //Calcila por componentes la posicion  
  xActual= x + ((1.0/6.0)*(k1xi+2*k2xi+2*k3xi+k4xi)*h);
  yActual= y + ((1.0/6.0)*(k1yi+2*k2yi+2*k3yi+k4yi)*h);

  //Actualiza los valores de x,y,vx,vy,t
  x=xActual;
  y=yActual;
  vx=vxActual;
  vy=vyActual;
  t=t+h;

  //verifica c ondiciones de frenado del movimiento
  if(y>=0 and vx>=0){
   imprimir(t,x,y,vx,vy,d);
  }
  else{
   indicador = false;
  }
 }
 //retorna la distancia recorrida en x
 return x;
}

/*Ejecutara rk4 para thetha entre thetai hasta thethaf, guardadara los datos para cada theta e informara en consola el angulo con mayor distancia recorrida */
void variosTheta(float c, float m,float v, float g, float x,float y,float h, float t,float thetai, float thetaf, FILE *d){
 float PI = 3.141592654;
 float thetaActual=thetai;
 float rx[7];
 int i = 0;

 //Ejecuta rk4 para cada theta guarda las distancias recorridas
 while(thetaActual<=thetaf){
  float thetaRad=thetaActual*PI/180.0;
  float vx=v*cos(thetaRad);
  float vy=v*sin(thetaRad);
  rx[i]=rk4(c,m,vx,vy,g,x,y,h,t,d);
  fprintf(d, ","); 
  fprintf(d, "\n"); 
  thetaActual=thetaActual+10.0;
  i=i+1;
 }

 //Recorre rx para hallar el mayor x recorrido
 int k=0;
 float xi=0;
 for(int j = 0; j<7; j++){
  if(rx[j] > xi){
   xi=rx[j];
   k=j;
  }
 }
 
 float thetak= (k+1)*10;
 float r= xi;
 cout << "para angulos entre 10 y 70 grados la mayor distancia recorrida es " << r << " m que corresponde a un angulo de " << thetak << " grados." << endl;
}
