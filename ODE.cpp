#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cmath>

float norma(float x[2]);
void ProductoPorComponentes(float c,float x[2], float r[2]);
void SumaVectores(float x[2], float y[2], float r[2]);
void RestaVectores(float x[2], float y[2], float r[2]);
void a(float v[2], float g[2], float m, float k, float r[2]);
void rk4(float t1,float x1[2],float v1[2],float h,float g[2],float m,float k, float v[2], float x[2]);
void rk4TMax(float xi[2], float vi[2], float ti, float h, float m, float g[2], float k, FILE *d);

int main()
{
 /* Constantes del movimiento
 Despues de haber sido definidas no cambia en la ejecución*/
 
 float gy =10.0; //Valor de Gravedad
 float m =0.2;  //Masa del proyectil en Kg
 float k = 0.2;  //Factor de friccion
 float dt =0.001; //saltos de tiempo valor seleccionado por el usuario
 float PI = 3.141592654; // Para convertir de grados a radianes
 float theta; //angulo de la velocidad
 float g[2]; //vector de velocidad
 
 g[0]=0;//Componente de la gravedad x
 g[1]=-gy;//Componente de gravedad y

 //Variables del movimiento
 float x[2];
 float v[2];
 float t=0;
 float tMax;
  
 //Primera parte x(t=0)=(0,0)
 //Theta 30 grados
 //v=300 m/s
 x[0]=0;
 x[1]=0;

 theta=45.0*PI/180.0;
 v[0]=300.0*cos(theta);
 v[1]=300.0*sin(theta);
 
 FILE *output;
 output = fopen("45grados.txt","w");

 rk4TMax(x,v,t,dt,m,g,k,output);
 
 fclose(output);
 
 return 0;
}

/*Norma de un vector en 2D*/
float norma(float x[2]){
 float r2 = pow(x[0],2) + pow(x[1],2);
 float r= sqrt(r2);
 return r;
}
/*En un arreglo de 2D guarda el producto de una constante por un vector*/
void ProductoPorComponentes(float c,float x[2], float r[2]){
 r[0]=c*x[0];
 r[1]=c*x[1];
}

/*En un arreglo de 2D guarda la suma de 2 vectores 2D*/
void SumaVectores(float x[2], float y[2], float r[2]){
 r[0]=x[0]+y[0];
 r[1]=x[1]+y[1];
}

/*En un arreglo de 2D guarda la suma de 2 vectores 2D*/
void RestaVectores(float x[2], float y[2], float r[2]){
 r[0]=x[0]-y[0];
 r[1]=x[1]-y[1];
}

/*Calcula la aceleracion del movimiento */
void a(float v[2], float g[2], float m, float k, float r[2]){
 float kmv=-k/norma(v)*m;
 ProductoPorComponentes(kmv, v, r);
 RestaVectores(g, r, r);
}

/*Rellena dos arreglos de 2D de x y v, utlizando el metodo runge kutta para hallar el siguiente en un t1.*/
void rk4(float t1,float x1[2],float v1[2],float h,float g[2],float m,float k, float v[2], float x[2]){
 // Calcula k1 en t1
 float k1[2];
 a(v1,g,m,k,k1);
 
 //Halla v1 + k1*h/2
 float vk2[2];
 ProductoPorComponentes(h/2, k1, vk2);
 SumaVectores(v1, vk2,vk2);
 //Halla k2 t1 + h/2 con vk2
 float k2[2];
 a(vk2,g,m,k,k2);
 
 //Halla v1 + k2*h/2
 float vk3[2];
 ProductoPorComponentes(h/2, k2, vk3);
 SumaVectores(v1, vk3,vk3);
 //Halla k3 t1 + h/2 con vk2
 float k3[2];
 a(vk3,g,m,k,k3);
 
 //Halla v1 + k3*h
 float vk4[2];
 ProductoPorComponentes(h, k3, vk4);
 SumaVectores(v1, vk4,vk4);
 //Halla k3 t1 + h con vk2
 float k4[2];
 a(vk4,g,m,k,k4);

 //velocidad en el metodo rk4 equivaldra a v = v1 +(k1 + 2*k2 +   2*k3 + k4)*h/6
 float Vnew[2];
 // multiplicacion 2*k2
 float Dosk2[2];
 ProductoPorComponentes(2, k2, Dosk2);
 // multiplicacion 2*k3
 float Dosk3[2];
 ProductoPorComponentes(2, k3, Dosk3);
 //Suma de k1 + Dosk2 + Dosk3 + k4
 float sumak [2];
 SumaVectores(k1,Dosk2,sumak);
 SumaVectores(sumak,Dosk3,sumak);
 SumaVectores(sumak,k4,sumak);
 // suma por h/6
 ProductoPorComponentes(h/6, sumak, Vnew);
 // lo anterior mas v1
 SumaVectores(v1,Vnew,Vnew);
 // Vnew es igual a la velocidad en t
 
 /////////////////////////////////////////////////

 //calcular k1 para x en t
 float xk1[2];
 xk1[0]=v1[0];
 xk1[1]=v1[1];

 //Calcular k2 para x en t + h/2
 float xk2[2];
 ProductoPorComponentes(h/2, xk1, xk2);
 SumaVectores(v1,xk2,xk2);

 //calcular k3 para x en t + h/2
 float xk3[2];
 ProductoPorComponentes(h/2, xk2, xk3);
 SumaVectores(v1,xk3,xk3);
 
 //calcular k4 para x en t + h
 float xk4[2];
 ProductoPorComponentes(h, xk3, xk4);
 SumaVectores(v1,xk4,xk4);

 //Calcula x sera igual a x=x1+(xk1+2*xk2+2*xk3+xk4)*(h/6)
 float Xnew[2];
 // multiplicacion 2*xk2
 float Dosxk2[2];
 ProductoPorComponentes(2, xk2, Dosxk2);
 // multiplicacion 2*xk3
 float Dosxk3[2];
 ProductoPorComponentes(2, xk3, Dosxk3);
 //Suma de xk1 + Dosxk2 + Dosxk3 + xk4
 float sumaxk[2];
 SumaVectores(xk1,Dosxk2,sumaxk);
 SumaVectores(sumaxk,Dosxk3,sumaxk);
 SumaVectores(sumaxk,xk4,sumaxk);
 // suma por h/6
 ProductoPorComponentes(h/6, sumaxk, Xnew);
 // lo anterior mas x1
 SumaVectores(x1,Xnew,Xnew);
 // Xnew es igual a la velocidad en t

 x[0]=Xnew[0];
 x[1]=Xnew[1];
 v[0]=Vnew[0];
 v[1]=Vnew[1];
}

/*Ejecuta runge kutta 4 hasta t max e imprime los resultados en un archivo de texto*/
void rk4TMax(float xi[2], float vi[2], float ti, float h, float m, float g[2], float k, FILE *d){
 float x[2];
 x[0]=xi[0];
 x[1]=xi[1];
 float v[2];
 v[0]=vi[0];
 v[1]=vi[1];
 float t = ti;
 fprintf(d, "%f %f %f %f %f\n",t,x[0],x[1],v[0],v[1]);
 bool sigue=true;
 while(t<1000){
  rk4(t,x,v,h,g,m,k,v,x);
  t = t + h;
  fprintf(d, "%f %f %f %f %f\n",t,x[0],x[1],v[0],v[1]);
  if(x[1] == 0){
  sigue = false;
  }
 } 
}
