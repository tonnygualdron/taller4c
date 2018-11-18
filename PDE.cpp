#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cmath>

using namespace std;

//Para un dx de 0.001 son 0.5/0.001 = 500
//Es decir 0.5 equivale 500 puntos

#define d 500

bool estaEnEquilibrio(double xy[d][d], double T, bool m);
void actualiza(double xy[d][d], double xyNew[d][d]);
void barra(double xy[d][d], double T);
void limpia(double xy[d][d]);
void inciales(double xy[d][d], double tamb);
void intera(double xy[d][d], double xyNew[d][d], double v, double dx, double dt, double T, bool m);
void condiciones(double xy[d][d], double tamb);
int Ninteracciones(double xy[d][d], double xyNew[d][d], double v, double dx, double dt, double T, int p, double tamb);
void imprimir(double xy[d][d], FILE *D);
void interacciones(double xy[d][d], double xyNew[d][d], double v, double dx, double dt, double T, int p, double tamb, int N, FILE *D);


int main()
{
 double l = 0.5;//tamaño lateral de la roca [m]
 double l2 = 0.1;//Diametro de la barra [m]
 double cp = 820; // cp en [J/ kg K]
 double k = 1.62;// k [m2/s]
 double ro = 2.71;// ro [g/cm3]
 double T= 100.0; //Temperatura de la barra
 double tamb=10.0;//temperatura ambiente
 
 ro=ro*pow(100.0,3)/1000.0; //ro [kg/m3]

 double v= k/(cp*ro);

 double dx=0.001;

 double dt=0.5*pow(dx,2)/v;

 double xy[d][d];
 double xyNew[d][d];

 limpia(xy);
 inciales(xy,tamb);
 barra(xy,T);
 condiciones(xy,tamb);

 FILE *output;
 output = fopen("caso1.txt", "W");
 
 int N = Ninteracciones(xy,xyNew,v,dx,dt,T,1,tamb);
 interacciones(xy,xyNew,v,dx,dt,T,1,tamb,N,output);
 
 fclose(output);
 
 return 0;
}

/*Verifica que todo el plano este en equilibrio*/
bool estaEnEquilibrio(double xy[d][d], double T, bool m){
 //cuenta el numero de posiciones a temperatura T
 int n=0;
 for(int i = 0; i<d; i++){
  for(int j =0; j<d; j++){
   if(xy[i][j]>=T){
    n=n+1;
   }
  }
 }

 //m true tiene en cuenta los bordes, m false no tiene en cuenta los bordes
 //si todas las posiciones estan a temperatura T retorna true
 if(n==(d*d) and m==true){
  return true;
 }
 else if(n==((d-1)*(d-1)) and m== false){
  return true;
 }
 else{
  return false;
 }
}

/*Actualiza los datos de una matriz dada otra matriz */
void actualiza(double xy[d][d], double xyNew[d][d]){
 for(int i = 0; i<d; i++){
  for(int j =0; j<d; j++){
   xy[i][j]=xyNew[i][j];
  }
 }
}

/*genera la barra en la matriz*/
void barra(double xy[d][d], double T){
 // ecuacion de un circulo (x-249)2 + (y-249)2 = (50)2
 int h=249;
 xy[h][h]=T;
 int r=50;
 while(r>0){
  for(int x = 0; x < d; x++){
   int y=sqrt(pow(r,2)-pow((x+h),2))-249;
   xy[x][y]=T;
  }
  r=r-1;
 }
}

/*Limpia un arreglo */
void limpia(double xy[d][d]){
 for(int i = 0; i<d; i++){
  for(int j =0; j<d; j++){
   xy[i][j]=0;
  }
 }
}

/*Inicializa todo el arreglo en una temperatura tamb*/ 
void inciales(double xy[d][d], double tamb){
 for(int i = 0; i<d; i++){
  for(int j =0; j<d; j++){
   xy[i][j]=tamb;
  }
 }
}

/* Realiza una interacion*/
void intera(double xy[d][d], double xyNew[d][d], double v, double dx, double dt, double T, bool m){
 double g=(v*dt)/(dx*dx);
 //m==true intera sin los bordes
 if(m==true){
  for(int i = 1; i<d-1; i++){
   for(int j =1; j<d-1; j++){
   xyNew[i][j]=xy[i][j] + (g*(xy[i+1][j]+xy[i-1][j]+xy[i][j+1]+xy[i][j-1]-(4*xy[i][j])));
   }
  }
  actualiza(xy,xyNew);
  barra(xy,T);
 }
 // intera con bordes
 else{
  for(int i = 0; i<d; i++){
   for(int j =0; j<d; j++){
    if(i==0 and j==0){
     xyNew[i][j]=xy[i][j] + (g*(xy[i+1][j]+10.0+xy[i][j+1]+10.0-(4*xy[i][j])));
    }
    else if(i==(d-1) and j==(d-1)){
     xyNew[i][j]=xy[i][j] + (g*(xy[i-1][j]+10.0+xy[i][j-1]+10.0-(4*xy[i][j])));
    }
    else if(i==0){
     xyNew[i][j]=xy[i][j] + (g*(xy[i+1][j]+10.0+xy[i][j+1]+xy[i][j-1]-(4*xy[i][j])));
    }
    else if(i==(d-1)){
     xyNew[i][j]=xy[i][j] + (g*(xy[i-1][j]+10.0+xy[i][j+1]+xy[i][j-1]-(4*xy[i][j])));
    }
    else if(j==0){
     xyNew[i][j]=xy[i][j] + (g*(xy[i+1][j]+xy[i-1][j]+xy[i][j+1]+10.0-(4*xy[i][j])));
    }
    else if(j==(d-1)){
     xyNew[i][j]=xy[i][j] + (g*(xy[i+1][j]+xy[i-1][j]+xy[i][j-1]+10.0-(4*xy[i][j])));
    }
    else{
     xyNew[i][j]=xy[i][j] + (g*(xy[i+1][j]+xy[i-1][j]+xy[i][j+1]+xy[i][j-1]-(4*xy[i][j])));
    }
   }
  }
  actualiza(xy,xyNew);
  barra(xy,T);
 }
}

/*condiciones de frontera*/
void condiciones(double xy[d][d], double tamb){
  for(int i = 0; i<d; i++){
   for(int j =0; j<d; j++){
    if(i==0){
     xy[i][j]=tamb;
    }
    else if(i==(d-1)){
     xy[i][j]=tamb;
    }
    else{
     xy[i][j]=tamb;
     j=d;
   }
  }
 }
}

/* Realizara las interacciones hasta equilibrio y retornara el numero de ineteraciones
 p==1 condiciones de frontera estaticas
 p==2 condiciones de frontera abiertas
 p==3 condiciones de frontera periodicas( con periodo 10*dt)
*/
int Ninteracciones(double xy[d][d], double xyNew[d][d], double v, double dx, double dt, double T, int p, double tamb){
 if(p==1){
  int n=0;
  while(estaEnEquilibrio(xy, T, false)){
   intera(xy, xyNew,v, dx, dt, T, true);
   n=n+1;
  }
  return n;
 }
 if(p==2){
  int n=0;
  while(estaEnEquilibrio(xy, T, true)){
   intera(xy, xyNew,v, dx, dt, T, false);
   n=n+1;
  }
  return n;
 }
 if(p==3){
  double t=0;
  int n=0;
  while(estaEnEquilibrio(xy, T, false)){
   intera(xy, xyNew,v, dx, dt, T, false);
    if(t==(10*dt)){
     condiciones(xy, tamb);
     t=0;
    }
   n=n+1;
  }
  return n;
 }
}

/*Imprime la matiz de datos*/
void imprimir(double xy[d][d], FILE *D){
 for(int i=0;i<d;i++){
  for(int j=0;j<d;j++){
   fprintf(D,"%f", xy[i][j]);
  }
 fprintf(D,"\n");
 }
}

/*Intera e imprime los datos iniciales uno a 1/4 interacciones, 3/4 interrraciones y final */
void interacciones(double xy[d][d], double xyNew[d][d], double v, double dx, double dt, double T, int p, double tamb, int N, FILE *D){
 int t13=N/4;
 int t34=N*3/4;
 if(p==1){
  int n=0;
  imprimir(xy,D);
  fprintf(D, ",");
  fprintf(D, "\n");
  while(n<=N){
   intera(xy, xyNew,v, dx, dt, T, true);
    if(n==t13 or n==t34){
     imprimir(xy,D);
     fprintf(D, ",");
     fprintf(D, "\n");
    } 
   n=n+1;
  }
 }
 if(p==2){
  int n=0;
  imprimir(xy,D);
  fprintf(D, ",");
  fprintf(D, "\n");
  while(n<=N){
   intera(xy, xyNew,v, dx, dt, T, false);
   if(n==t13 or n==t34){
    imprimir(xy,D);
    fprintf(D, ",");
    fprintf(D, "\n");
   } 
   n=n+1;
  }
 }
 if(p==3){
  double t=0;
  int n=0;
  imprimir(xy,D);
  fprintf(D, ",");
  fprintf(D, "\n");
  while(n<=N){
   intera(xy, xyNew,v, dx, dt, T, false);
    if(t==(10*dt)){
     condiciones(xy, tamb);
     t=0;
    }
    if(n==t13 or n==t34){
     imprimir(xy,D);
     fprintf(D, ",");
     fprintf(D, "\n");
    } 
   n=n+1;
  }
 }
}
