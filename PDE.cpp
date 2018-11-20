#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cmath>

using namespace std;


#define d 103 //101 puntos de placa y 2 posiciones de borde

bool estaEnEquilibrio(double xy[d][d], double xyNew[d][d],double tamb,bool m);
void actualiza(double xy[d][d], double xyNew[d][d]);
void barra(double xy[d][d], double T, double l2, double l, int m);
float promedioPlato(double xy[d][d], double T, int m);
void limpia(double xy[d][d]);
void inciales(double xy[d][d], double tamb);
void reiniciar(double xy[d][d], double xyNew[d][d], double T, double tamb, double l, double l2, int m);
void intera(double xy[d][d], double xyNew[d][d], double v, double dx, double dt, double T, int m,double l2, double l, double tamb);
void condiciones(double xy[d][d], double tamb);
int Ninteracciones(double xy[d][d], double xyNew[d][d], double v, double dx, double dt, double T, int p, double tamb,double l2, double l);
void imprimir(double xy[d][d], FILE *D);
void interacciones(double xy[d][d], double xyNew[d][d], double v, double dx, double dt, double T, int p, double tamb, int N, FILE *D,double l2, double l,FILE *D2);
void TodasInteracciones(double xy[d][d], double xyNew[d][d], double v, double dx, double dt, double T, int p, double tamb, int N, FILE *D,double l2, double l);

int main()
{
 double l = 0.5;//tamaño lateral de la roca [m]
 double l2 = 0.1;//Diametro de la barra [m]
 double cp = 820; // cp en [J/ kg K]
 double k = 1.62;// k [m2/s]
 double ro = 2.71;// ro [g/cm3]
 double T= 100.0+273.15; //Temperatura de la barra
 double tamb=10.0+273.15;//temperatura ambiente
 
 ro=ro*pow(100.0,3)/1000.0; //ro [kg/m3]

 double v= k/(cp*ro);
 
 double dx=l/(d-2);

 double dt=pow(dx,2)/(v*4.0);


 double xy[d][d];
 double xyNew[d][d];
 

 reiniciar(xy,xyNew,T,tamb,l,l2,1);
 FILE *output;
 FILE *output1t;
 output = fopen("caso1.txt", "w");
 output1t =fopen("Caso1T.txt", "w");
 int N = Ninteracciones(xy,xyNew,v,dx,dt,T,1,tamb,l2,l);
 reiniciar(xy,xyNew,T,tamb,l,l2,1);
 interacciones(xy,xyNew,v,dx,dt,T,1,tamb,N,output,l2,l,output1t);
 fclose(output);
 fclose(output1t);
 
 reiniciar(xy,xyNew,T,tamb,l,l2,1);
 FILE *output11;
 output11 = fopen("caso11.txt", "w");
 TodasInteracciones(xy,xyNew,v,dx,dt,T,1,tamb,N,output11,l2,l);
 fclose(output11);
 
 dx=l/d;
 dt=pow(dx,2)/(v*4.0);

 reiniciar(xy,xyNew,T,tamb,l,l2,2);
 FILE *output2;
 FILE *output2t;
 output2 = fopen("caso2.txt", "w");
 output2t =fopen("Caso2T.txt", "w");
 int N2 = Ninteracciones(xy,xyNew,v,dx,dt,T,2,tamb,l2,l);
 reiniciar(xy,xyNew,T,tamb,l,l2,2);
 interacciones(xy,xyNew,v,dx,dt,T,2,tamb,N2,output2,l2,l,output2t);
 fclose(output2);
 fclose(output2t);
 
 reiniciar(xy,xyNew,T,tamb,l,l2,2);
 FILE *output22;
 output22 = fopen("caso22.txt", "w");
 TodasInteracciones(xy,xyNew,v,dx,dt,T,2,tamb,N2,output22,l2,l);
 fclose(output22);

 reiniciar(xy,xyNew,T,tamb,l,l2,3);
 FILE *output3;
 FILE *output3t;
 output3 = fopen("caso3.txt", "w");
 output3t =fopen("Caso3T.txt", "w");
 int N3 = Ninteracciones(xy,xyNew,v,dx,dt,T,3,tamb,l2,l);
 reiniciar(xy,xyNew,T,tamb,l,l2,3);
 interacciones(xy,xyNew,v,dx,dt,T,3,tamb,N3,output3,l2,l,output3t);
 fclose(output3);
 fclose(output3t);
 
 reiniciar(xy,xyNew,T,tamb,l,l2,3);
 FILE *output33;
 output33 = fopen("caso33.txt", "w");
 TodasInteracciones(xy,xyNew,v,dx,dt,T,3,tamb,N3,output33,l2,l);
 fclose(output33);
 return 0;
}

/*Verifica que todo el plano este en equilibrio*/
bool estaEnEquilibrio(double xy[d][d], double xyNew[d][d],double tamb,bool m){
 //m true tiene en cuenta los bordes, m false no tiene en cuenta los bordes
 //si todas las posiciones estan a temperatura T retorna true
 if(m==true){
  int n=0;
  for(int i = 1; i<d-1; i++){
   for(int j = 1; j<d-1; j++){
    double f = xyNew[i][j]-xy[i][j];
    /*Inicialmente pense en que para el equilibrio las matices xy y xyNew tenia que ser excatamete iguales.
    pero esto debido a la resolucion de un double genera que las interacciones se hagan muy grande alrededor
    56000 para una matriz 103*103 pero de nInteraciones/2 para adelante los cambios son muy poco significativos, 
    asi que para acelerar la ejecucion decidi mejor ajustar la la resolucion que queria tener en mis resultados.
    De manera empirica despues de ejecutar la diferencia entre las temperaturas finales de 24569 interacciones y
    2994 interaciones con f<=0.01 es de tan solo 0.000513.*/
    if(f<=0.001){
     n=n+1;
    }
   }
  }
  if(n==((d-2)*(d-2))){
   return true;
  }
  return false;
 }
 else{
    int n=0;
  for(int i = 0; i<d; i++){
   for(int j = 0; j<d; j++){
    double f = xyNew[i][j]-xy[i][j];
    if(f<=0.001){
     n=n+1;
    }
   }
  }
  if(n==(d*d)){
   return true;
  }
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
void barra(double xy[d][d], double T, double l2, double l, int m){
 if(m==1){
  int h=((d-3)/2)+1;
  int r=(l2*(d-2))/(2*l);
  for(int x = -r; x <=r ; x++){
   for(int y = -r; y <=r ; y++){
    int rr= pow((x),2) + pow((y),2);
    if( rr <= pow(r,2)){
     xy[x+h][y+h]=T;
    }
   }
  }
 }
  if(m==2 or m==3){
  int h=((d-1)/2)+1;
  int r=(l2*(d))/(2*l);
  for(int x = -r; x <=r ; x++){
   for(int y = -r; y <=r ; y++){
    int rr= pow((x),2) + pow((y),2);
    if( rr <= pow(r,2)){
     xy[x+h][y+h]=T;
    }
   }
  }
 }

}
float promedioPlato(double xy[d][d], double T, int m){
 if(m==1){
  int n=0;
  float Tprom=0;
  for(int i = 1; i<d-1; i++){
   for(int j =1; j<d-1; j++){
    Tprom = Tprom + xy[i][j];
    n=n+1;
    if(xy[i][j]==T){
     n=n-1;
     Tprom = Tprom - xy[i][j];
    }
   }
  }
  Tprom=Tprom/n;
  return Tprom;
 }
 if(m==2 or m ==3){
  int n=0;
  float Tprom=0;
  for(int i = 0; i<d; i++){
   for(int j =0; j<d; j++){
    Tprom = Tprom + xy[i][j];
    n=n+1;
    if(xy[i][j]==T){
     n=n-1;
     Tprom = Tprom - xy[i][j];
    }
   }
  }
  Tprom=Tprom/n;
  return Tprom;
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

/*Reinicia las matriz a condiciones iniciales*/
void reiniciar(double xy[d][d], double xyNew[d][d], double T, double tamb, double l, double l2, int m){
 limpia(xy);
 limpia(xyNew);
 inciales(xy,tamb);
 inciales(xyNew,tamb);
 barra(xy, T,l2,l,m);
 barra(xyNew, T,l2,l,m);
 condiciones(xy,tamb);
 condiciones(xyNew,tamb);
}

/* Realiza una interacion*/
void intera(double xy[d][d], double xyNew[d][d], double v, double dx, double dt, double T, int m,double l2, double l, double tamb){
 float g=(dt*v)/pow(dx,2);
 //m==1 intera para el caso 1
 if(m==1){
  for(int i = 1; i<(d-1); i++){
   for(int j =1; j<(d-1); j++){
   xyNew[i][j]= ((1.0-4.0*g)*xy[i][j]) + (dt*v/pow(dx,2))*(xy[i+1][j]+xy[i-1][j]+xy[i][j+1]+xy[i][j-1]);
   }
  }
  barra(xyNew,T,l2,l,1);
 }
 // intera caso 2
 if(m==2){
  for(int i = 0; i<d; i++){
   for(int j =0; j<d; j++){
    if(i==0 and j==0){
     xyNew[i][j]= ((1.0-4.0*g)*xy[i][j]) + (dt*v/pow(dx,2))*(xy[i+1][j]+tamb+xy[i][j+1]+tamb);
    }
    else if(i==(d-1) and j==(d-1)){
     xyNew[i][j]= ((1.0-4.0*g)*xy[i][j]) + (dt*v/pow(dx,2))*(tamb+xy[i-1][j]+tamb+xy[i][j-1]);
    }
    else if(i==0){
     xyNew[i][j]= ((1.0-4.0*g)*xy[i][j]) + (dt*v/pow(dx,2))*(xy[i+1][j]+tamb+xy[i][j+1]+xy[i][j-1]);
    }
    else if(i==(d-1)){
     xyNew[i][j]= ((1.0-4.0*g)*xy[i][j]) + (dt*v/pow(dx,2))*(tamb+xy[i-1][j]+xy[i][j+1]+xy[i][j-1]);
    }
    else if(j==0){
     xyNew[i][j]= ((1.0-4.0*g)*xy[i][j]) + (dt*v/pow(dx,2))*(xy[i+1][j]+xy[i-1][j]+xy[i][j+1]+tamb);
    }
    else if(j==(d-1)){
     xyNew[i][j]= ((1.0-4.0*g)*xy[i][j]) + (dt*v/pow(dx,2))*(xy[i+1][j]+xy[i-1][j]+tamb+xy[i][j-1]);
    }
    else{
     xyNew[i][j]= ((1.0-4.0*g)*xy[i][j]) + (dt*v/pow(dx,2))*(xy[i+1][j]+xy[i-1][j]+xy[i][j+1]+xy[i][j-1]);
    }
   }
  }
  barra(xyNew,T,l2,l,2);
 }
 //intera caso 3
 if(m==3){
  for(int i = 0; i<d; i++){
   for(int j =0; j<d; j++){
    if(i==0 and j==0){
     xyNew[i][j]= ((1.0-4.0*g)*xy[i][j]) + (dt*v/pow(dx,2))*(xy[i+1][j]+xy[d-1][j]+xy[i][j+1]+xy[i][d-1]);
    }
    else if(i==(d-1) and j==(d-1)){
     xyNew[i][j]= ((1.0-4.0*g)*xy[i][j]) + (dt*v/pow(dx,2))*(xy[0][j]+xy[i-1][j]+xy[i][0]+xy[i][j-1]);
    }
    else if(i==0){
     xyNew[i][j]= ((1.0-4.0*g)*xy[i][j]) + (dt*v/pow(dx,2))*(xy[i+1][j]+xy[d-1][j]+xy[i][j+1]+xy[i][j-1]);
    }
    else if(i==(d-1)){
     xyNew[i][j]= ((1.0-4.0*g)*xy[i][j]) + (dt*v/pow(dx,2))*(xy[0][j]+xy[i-1][j]+xy[i][j+1]+xy[i][j-1]);
    }
    else if(j==0){
     xyNew[i][j]= ((1.0-4.0*g)*xy[i][j]) + (dt*v/pow(dx,2))*(xy[i+1][j]+xy[i-1][j]+xy[i][j+1]+xy[i][d-1]);
    }
    else if(j==(d-1)){
     xyNew[i][j]= ((1.0-4.0*g)*xy[i][j]) + (dt*v/pow(dx,2))*(xy[i+1][j]+xy[i-1][j]+xy[i][0]+xy[i][j-1]);
    }
    else{
     xyNew[i][j]= ((1.0-4.0*g)*xy[i][j]) + (dt*v/pow(dx,2))*(xy[i+1][j]+xy[i-1][j]+xy[i][j+1]+xy[i][j-1]);
    }
   }
  }
  barra(xyNew,T,l2,l,3);
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
int Ninteracciones(double xy[d][d], double xyNew[d][d], double v, double dx, double dt, double T, int p, double tamb,double l2, double l){
 bool indicador= true;
 if(p==1){
  int n=0;
  while(indicador){
   intera(xy, xyNew,v, dx, dt, T, 1,l2,l,tamb);
   if(estaEnEquilibrio(xy, xyNew, tamb,true)){
    indicador = false;
   }
   else{
    actualiza(xy,xyNew);
    n=n+1;
    }
  }
  return n;
 }
 if(p==2){
  int n=0;
  while(indicador){
   intera(xy, xyNew,v, dx, dt, T, 2,l2,l,tamb);
   if(estaEnEquilibrio(xy, xyNew, tamb,false)){
    indicador = false;
   }
   else{
    actualiza(xy,xyNew);
    n=n+1;
    }
  }
  return n;
 }
 if(p==3){
  int n=0;
  while(indicador){
   intera(xy, xyNew,v, dx, dt, T, 3,l2,l,tamb);
   if(estaEnEquilibrio(xy, xyNew, tamb,false)){
    indicador = false;
   }
   else{
    actualiza(xy,xyNew);
    n=n+1;
    }
  }
  return n;
 }
}

/*Imprime la matiz de datos*/
void imprimir(double xy[d][d], FILE *D){
 for(int i=0;i<d;i++){
  for(int j=0;j<d;j++){
   fprintf(D,"%f", xy[i][j]);
   fprintf(D," ");
  }
  fprintf(D, "\n");
 }
}

/*Intera e imprime los datos iniciales uno a 1/4 interacciones, 2/4 interrraciones y final */
void interacciones(double xy[d][d], double xyNew[d][d], double v, double dx, double dt, double T, int p, double tamb, int N, FILE *D,double l2, double l,FILE *D2){
 int t13=N/4;
 int t24=N*3/4;
 if(p==1){
  int n=0;
  imprimir(xy,D);
  fprintf(D2, "%f %f\n", n*dt, promedioPlato(xy, T,1));
  while(n<=N){
   intera(xy, xyNew,v, dx, dt, T, 1,l2,l,tamb);
   actualiza(xy,xyNew);
   n=n+1;
   fprintf(D2, "%f %f\n", n*dt, promedioPlato(xy, T,1));
    if(n==t13 or n==t24 or n==N){
     imprimir(xy,D);
    } 
  }
 }
  if(p==2){
  int n=0;
  imprimir(xy,D);
  fprintf(D2, "%f %f\n", n*dt, promedioPlato(xy, T,2));
  while(n<=N){
   intera(xy, xyNew,v, dx, dt, T, 2,l2,l,tamb);
   actualiza(xy,xyNew);
   n=n+1;
   fprintf(D2, "%f %f\n", n*dt, promedioPlato(xy, T,2));
    if(n==t13 or n==t24 or n==N){
     imprimir(xy,D);
    } 
  }
 }
  if(p==3){
  int n=0;
  imprimir(xy,D);
  fprintf(D2, "%f %f\n", n*dt, promedioPlato(xy, T,3));
  while(n<=N){
   intera(xy, xyNew,v, dx, dt, T, 3,l2,l,tamb);
   actualiza(xy,xyNew);
   n=n+1;
   fprintf(D2, "%f %f\n", n*dt, promedioPlato(xy, T,3));
    if(n==t13 or n==t24 or n==N){
     imprimir(xy,D);
    } 
  }
 }
}


/*Imprime en documento la matriz para cada actualizacion*/
void TodasInteracciones(double xy[d][d], double xyNew[d][d], double v, double dx, double dt, double T, int p, double tamb, int N, FILE *D,double l2, double l){
 if(p==1){
  int n=0;
  int n2=0;
  imprimir(xy,D);
  while(n<=N){
   intera(xy, xyNew,v, dx, dt, T, 1,l2,l,tamb);
   actualiza(xy,xyNew);
    if(n2==100 or n==N){
     imprimir(xy,D); 
     n2=0;
    }
   n=n+1;
   n2=n2+1;
  }
 }
  if(p==2){
  int n=0;
  int n2=0;
  imprimir(xy,D);
  while(n<=N){
   intera(xy, xyNew,v, dx, dt, T, 2,l2,l,tamb);
   actualiza(xy,xyNew);
    if(n2==100 or n==N){
     imprimir(xy,D); 
     n2=0;
    }
   n=n+1;
   n2=n2+1;
  }
 }
  if(p==3){
  int n=0;
  int n2=0;
  imprimir(xy,D);
  while(n<=N){
   intera(xy, xyNew,v, dx, dt, T, 3,l2,l,tamb);
   actualiza(xy,xyNew);
    if(n2==500 or n==N){
     imprimir(xy,D); 
      n2=0;
    }
   n=n+1;
   n2=n2+1;
  }
 }
}
