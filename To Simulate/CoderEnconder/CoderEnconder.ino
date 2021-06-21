#include <Wire.h>
#include "DFRobot_LCD.h"

const int colorR = 255;
const int colorG = 0;
const int colorB = 0;


DFRobot_LCD lcd(16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

//#include "DFRobot_LCD.h"
//DFRobot_LCD lcd(16,2); //16 characters and 2 lines of show

//const int colorR = 255;
//const int colorG = 0;
//const int colorB = 0;

/*----MATRICES DEFINIDAS----*/
//Matriz de posibles mensajes
int M[8][3] = {{0, 0, 0}, {0, 0, 1}, {0, 1, 0}, {0, 1, 1}, {1, 0, 0}, {1, 0, 1}, {1, 1, 0}, {1, 1, 1}};
//Matriz generadora
int G[3][6] = {{1 , 0 , 0, 1, 0, 1}, {0 , 1 , 0 , 0 , 1 , 1}, {0 , 0, 1, 1 , 1 , 0}};
//Matriz identidad
int I[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
//matriz de paridad
int P[3][3] = {{1, 0, 1}, {0, 1, 1}, {1, 1, 0}};
/*----CODER----*/
int U[8][6] = {{0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}};
int u[6] = {0, 0, 0, 0, 0, 0};
int u_second[6] = {0, 0, 0, 0, 0, 0};
//Mensaje prueba
int m[3] = {0, 0, 0};
/*----CANAL----*/
int e[10][6] = {{0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 1} , {0, 0, 0, 0, 1, 0}, {0, 0, 0, 1, 0, 0}, {0, 0, 1, 0, 0, 0}, {0, 1, 0, 0, 0 , 0}, {1, 0, 0, 0, 0, 0}, {1, 0, 0, 0, 1, 0}, {0, 0, 1, 0, 0, 1}, {0, 1, 0, 1, 0, 0}};
int Ptran[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
int H[3][6] = {{0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}};
int Htran[6][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
int U_Htran[3] = {0, 0, 0};
int VP[8][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
int VP2[3] = {0, 0, 0};
int S[10][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

/*----TABLA DE ARREGLO ESTANDAR----*/
int  SA000[8][6] = {{0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}};
int  SA001[8][6] = {{0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}};
int  SA010[8][6] = {{0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}};
int  SA011[8][6] = {{0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}};
int  SA100[8][6] = {{0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}};
int  SA101[8][6] = {{0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}};
int  SA110[8][6] = {{0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}};
int  SA111a[8][6] = {{0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}};
int  SA111b[8][6] = {{0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}};
int  SA111c[8][6] = {{0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}};

/*---DECODER----*/
//Sindrome erroneo comparador
int Sx_vp[3] = {0, 0, 0};
int y[6] = {0, 0, 0, 0, 0, 0};
int ex[6] = {0, 0, 0, 0, 0, 0};
int Udecod[6]={0,0,0,0,0,0};
int UHtran2[3]={0,0,0};

/*----VARIABLES GLOBALES----*/
int i = 0;
int contador = 0, k = 0, row = 0, col = 0, aux = 0;
int valor = 0, valor2 = 0, res = 0, suma = 0;
int b = 0, c = 0;
int comprobacion = 0;
int Suma_FilaU[3] = {0, 0, 0};
int Suma_Filau[3] = {0, 0, 0};
int Suma_Filau_second[3] = {0, 0, 0};
int Suma_Filau_Htran[6] = {0, 0, 0, 0, 0, 0};
int Suma_FilaU_Htran[6] = {0, 0, 0, 0, 0, 0};
int Suma_FilaVP2Htran[6] = {0, 0, 0, 0, 0, 0};
int Suma_FilaS[6] = {0, 0, 0, 0, 0, 0};
int Suma_FilaUHtran2[6] = {0, 0, 0,0,0,0};

void setup() {
  lcd.init();
//  lcd.backlight();
}

void loop() {
  

  m[0]=digitalRead(9);
  m[1]=digitalRead(10);
  m[2]=digitalRead(2);

  y[0]=digitalRead(3);
  y[1]=digitalRead(4);
  y[2]=digitalRead(5);
  y[3]=digitalRead(6);
  y[4]=digitalRead(7);
  y[5]=digitalRead(8);

  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  
  
  //Serial.begin(9600);
  //----CODER----//
  //--Modulo 2 de matriz U Multiplicacion de M * G--//
  for (i = 0; i < 8; i++)
  {
    k = 0;
    while (k < 6)
    {
      if (contador < 3)
      {
        valor = M[i][contador];
        valor2 = G[contador][k];
        res = valor * valor2;
        Suma_FilaU[contador] = res;
        contador++;
      }
      else
      {
        suma = Suma_FilaU[0] + Suma_FilaU[1] + Suma_FilaU[2];
        suma = suma % 2;
        U[i][k] = suma;
        contador = 0;
        k++;
      }

    }
  }

  //--Modulo 2 de matriz u Multiplicacion de m * G--//
  for (i = 0; i < 1; i++)
  {
    k = 0;
    while (k < 6)
    {
      if (contador < 3)
      {
        valor = m[contador];
        valor2 = G[contador][k];
        res = valor * valor2;
        Suma_Filau[contador] = res;
        contador++;
      }
      else
      {
        suma = Suma_Filau[0] + Suma_Filau[1] + Suma_Filau[2];
        suma = suma % 2;
        u[k] = suma;
        contador = 0;
        k++;
      }

    }
  }
  //----CANAL----//
  //Transponer matriz P
  col = 0, valor = 0, row = 0, aux = 0;
  //Numero de Filas matriz 1
  while (row < 3)
  {
    col = 0;
    //Numero de columnas matriz 2
    while (col < 3)
    {
      //Numero de columnas Matriz 1 y filas Matriz 2 /*Aux*/
      if (aux < 3)
      {
        valor = P[row][aux];
        Ptran[aux][col] = valor;
        aux++;
      }
      else
      {
        aux = 0;
        row++;
        col++;
      }
    }
  }
  //Concatenacion para obtener matriz H

  int a = 3, n = 3;
  for (int i = 0; i < a; i++) {
    for (int j = 0; j < n; j++) {
      H[i][j] = Ptran[i][j];
    }
  }
  for (int i = 0 ; i < a ; i++) {
    for (int j = n; j < (2 * n) ; j++) {
      H[i][j] = I[i][j - n];
    }
  }
  //Transponer matriz H
  col = 0, valor = 0, row = 0, aux = 0;
  //Numero de Filas matriz 1
  while (row < 3)
  {
    col = 0;
    //Numero de columnas matriz 2
    while (col < 3)
    {
      //Numero de columnas Matriz 1 y filas Matriz 2 /*Aux*/
      if (aux < 6)
      {
        valor = H[row][aux];
        Htran[aux][col] = valor;
        aux++;
      }
      else
      {
        aux = 0;
        row++;
        col++;
      }
    }
  }

  //Verificacion de Paridad (Mensaje)
  suma = 0, valor2 = 0;
  for (i = 0; i < 1; i++)
  {
    k = 0;
    while (k < 6)
    {
      if (contador < 3)
      {
        valor = m[contador];
        valor2 = G[contador][k];
        res = valor * valor2;
        Suma_Filau_second[contador] = res;
        contador++;
      }
      else
      {
        suma = Suma_Filau_second[0] + Suma_Filau_second[1] + Suma_Filau_second[2];
        suma = suma % 2;
        u_second[k] = suma;
        contador = 0;
        k++;
      }
    }
  }
  //Segunda multiplicacion
  for (i = 0; i < 1; i++)
  {
    k = 0;
    while (k < 3)
    {
      if (contador < 6)
      {
        valor = u_second[contador];
        valor2 = Htran[contador][k];
        res = valor * valor2;
        Suma_Filau_Htran[contador] = res;
        contador++;
      }
      else
      {
        suma = Suma_Filau_Htran[0] + Suma_Filau_Htran[1] + Suma_Filau_Htran[2] + Suma_Filau_Htran[3] + Suma_Filau_Htran[4] + Suma_Filau_Htran[5];
        suma = suma % 2;
        U_Htran[k] = suma;
        contador = 0;
        k++;
      }

    }
  }
  //Verificacion de Paridad (Palabra de codigo - Matriz)
  i = 0, suma = 0, valor = 0, valor2 = 0, contador = 0;
  for (i = 0; i < 8; i++)
  {
    k = 0;
    while (k < 6)
    {
      if (contador < 3)
      {
        valor = U[i][k];
        valor2 = Htran[k][contador];
        res = valor * valor2;
        Suma_FilaU_Htran[contador] = res;
        contador++;
      }
      else
      {
        suma = Suma_FilaU_Htran[0] + Suma_FilaU_Htran[1] + Suma_FilaU_Htran[2] + Suma_FilaU_Htran[3] + Suma_FilaU_Htran[4] + Suma_FilaU_Htran[5];
        suma = suma % 2;
        VP[i][k] = suma;
        contador = 0;
        k++;
      }
    }
  }
  //Verificacion de Paridad (Palabra de codigo - Vector)
  i = 0, suma = 0, valor = 0, valor2 = 0;
  for (i = 0; i < 1; i++)
  {
    k = 0;
    while (k < 3)
    {
      if (contador < 6)
      {
        valor = u[contador];
        valor2 = Htran[contador][k];
        res = valor * valor2;
        Suma_FilaVP2Htran[contador] = res;
        contador++;
      }
      else
      {
        suma = Suma_FilaVP2Htran[0] + Suma_FilaVP2Htran[1] + Suma_FilaVP2Htran[2] + Suma_FilaVP2Htran[3] + Suma_FilaVP2Htran[4] + Suma_FilaVP2Htran[5];
        suma = suma % 2;
        VP2[k] = suma;
        contador = 0;
        k++;
      }
    }
  }

  //Declaracion del sindrome
  i = 0, suma = 0, valor = 0, valor2 = 0;
  for (i = 0; i < 10; i++)
  {
    k = 0;
    while (k < 3)
    {
      if (contador < 6)
      {
        valor = e[i][contador];
        valor2 = Htran[contador][k];
        res = valor * valor2;
        Suma_FilaS[contador] = res;
        contador++;
      }
      else
      {
        suma = Suma_FilaS[0] + Suma_FilaS[1] + Suma_FilaS[2] + Suma_FilaS[3] + Suma_FilaS[4] + Suma_FilaS[5];
        suma = suma % 2;
        S[i][k] = suma;
        contador = 0;
        k++;
      }
    }
  }

  //----ARREGLO ESTANDAR----
  //SA000

  contador = 0, valor = 0, valor2 = 0, res = 0;
  for (i = 0; i < 8; i++) {
    contador = 0;
    while (contador < 6) {
      valor = U[i][contador];
      valor2 = e[0][contador];
      res = valor + valor2;
      SA000[i][contador] = res % 2;
      contador++;
    }
  }

  //SA001
  contador = 0, valor = 0, valor2 = 0, res = 0;
  for (i = 0; i < 8; i++) {
    contador = 0;
    while (contador < 6) {
      valor = U[i][contador];
      valor2 = e[1][contador];
      res = valor + valor2;
      SA001[i][contador] = res % 2;
      contador++;
    }
  }
  //SA010
  contador = 0, valor = 0, valor2 = 0, res = 0;
  for (i = 0; i < 8; i++) {
    contador = 0;
    while (contador < 6) {
      valor = U[i][contador];
      valor2 = e[2][contador];
      res = valor + valor2;
      SA010[i][contador] = res % 2;
      contador++;
    }
  }  
  //SA100
  contador = 0, valor = 0, valor2 = 0, res = 0;
  for (i = 0; i < 8; i++) {
    contador = 0;
    while (contador < 6) {
      valor = U[i][contador];
      valor2 = e[3][contador];
      res = valor + valor2;
      SA100[i][contador] = res % 2;
      contador++;
    }
  }
  //SA110
  contador = 0, valor = 0, valor2 = 0, res = 0;
  for (i = 0; i < 8; i++) {
    contador = 0;
    while (contador < 6) {
      valor = U[i][contador];
      valor2 = e[4][contador];
      res = valor + valor2;
      SA110[i][contador] = res % 2;
      contador++;
    }
  }
  //SA011
  contador = 0, valor = 0, valor2 = 0, res = 0;
  for (i = 0; i < 8; i++) {
    contador = 0;
    while (contador < 6) {
      valor = U[i][contador];
      valor2 = e[5][contador];
      res = valor + valor2;
      SA011[i][contador] = res % 2;
      contador++;
    }
  }
  //SA101
  contador = 0, valor = 0, valor2 = 0, res = 0;
  for (i = 0; i < 8; i++) {
    contador = 0;
    while (contador < 6) {
      valor = U[i][contador];
      valor2 = e[6][contador];
      res = valor + valor2;
      SA101[i][contador] = res % 2;
      contador++;
    }
  }
  
  //SA111a
  contador = 0, valor = 0, valor2 = 0, res = 0;
  for (i = 0; i < 8; i++) {
    contador = 0;
    while (contador < 6) {
      valor = U[i][contador];
      valor2 = e[7][contador];
      res = valor + valor2;
      SA111a[i][contador] = res % 2;
      contador++;
    }
  }
  //SA111b
  contador = 0, valor = 0, valor2 = 0, res = 0;
  for (i = 0; i < 8; i++) {
    contador = 0;
    while (contador < 6) {
      valor = U[i][contador];
      valor2 = e[8][contador];
      res = valor + valor2;
      SA111b[i][contador] = res % 2;
      contador++;
    }
  }
  //SA111c
  contador = 0, valor = 0, valor2 = 0, res = 0;
  for (i = 0; i < 8; i++) {
    contador = 0;
    while (contador < 6) {
      valor = U[i][contador];
      valor2 = e[9][contador];
      res = valor + valor2;
      SA111c[i][contador] = res % 2;
      contador++;
    }
  }

  //---ERROR ALEATORIO---
  /*verificacion de paridad (Error aleatorio)*/
  /*if(y==u){
    //lcd.print("Led off");//Led apagado no existe error
    }
    else{
      //lcd.print("Led on");//Led encendido existe error
    }*/

  //----DECODER----//
  //--Modulo 2 de matriz U Multiplicacion de M * G--//
  for (i = 0; i < 1; i++) {
    k =0;
    contador = 0;
    while (k < 3) {
      if (contador < 6)
      {
        valor = y[contador];
        valor2 = Htran[contador][k];
        res = valor * valor2;
        Suma_FilaUHtran2[contador] = res;
        contador++;
      }
      else
      {
        suma = Suma_FilaUHtran2[0] + Suma_FilaUHtran2[1] + Suma_FilaUHtran2[2]+ Suma_FilaUHtran2[3]+ Suma_FilaUHtran2[4]+ Suma_FilaUHtran2[5];
        suma = suma % 2;
        Sx_vp[k] = suma;
        contador = 0;
        k++;
      }
    }
  }

/*
  Sx_vp[0]=1;
  Sx_vp[1]=1;
  Sx_vp[2]=1;
  u[0]=1;
  u[1]=0;
  u[2]=1;
  u[3]=0;
  u[4]=1;
  u[5]=1;
*/  

//CASOS DE DECODIFICACION
  if(Sx_vp[0] == S[1][0] && Sx_vp[1] == S[1][1] && Sx_vp[2] == S[1][2]){
     for(i=0;i<6;i++){
        ex[i] = SA001[0][i];
     }  
  }else if(Sx_vp[0] == S[2][0] && Sx_vp[1] == S[2][1] && Sx_vp[2] == S[2][2]){
      for(i=0;i<6;i++){
      ex[i] = SA010[0][i];
    }  
  }else if(Sx_vp[0] == S[3][0] && Sx_vp[1] == S[3][1] && Sx_vp[2] == S[3][2]){
    for(i=0;i<6;i++){
      ex[i] = SA100[0][i];
   }  
  }else if(Sx_vp[0] == S[4][0] && Sx_vp[1] == S[4][1] && Sx_vp[2] == S[4][2]){
    for(i=0;i<6;i++){
      ex[i] = SA110[0][i];
   }  
  }else if(Sx_vp[0] == S[5][0] && Sx_vp[1] == S[5][1] && Sx_vp[2] == S[5][2]){
    for(i=0;i<6;i++){
      ex[i] = SA011[0][i];
   }  
  }else if(Sx_vp[0] == S[6][0] && Sx_vp[1] == S[6][1] && Sx_vp[2] == S[6][2]){
    for(i=0;i<6;i++){
      ex[i] = SA101[0][i];
   }  
  }else if(Sx_vp[0] == S[7][0] && Sx_vp[1] == S[7][1] && Sx_vp[2] == S[7][2]){
    if(u[0] != y[0] && u[4] != y[4] ){
        for(i=0;i<6;i++){
          ex[i] = SA111a[0][i];
        }
      }else if(u[2] != y[2] && u[5] != y[5] ){
        for(i=0;i<6;i++){
          ex[i] = SA111b[0][i];
        }
      }else if(u[1] != y[1] && u[3] != y[3] ){
        for(i=0;i<6;i++){
          ex[i] = SA111c[0][i];
        }
      }   
  }

  //PALABRA (u) DECODIFICADA
  contador = 0, valor = 0, valor2 = 0;
  for (i = 0; i < 8; i++) {
      valor = y[i];
      valor2 =  ex[i];
      res = valor + valor2;
      Udecod[i]= res % 2;
    }
  //Verificacion de Paridad (palabra decodificada)
  for (i = 0; i < 1; i++)
  {
    k = 0,contador=0;
    while (k < 3)
    {
      if (contador < 6)
      {
        valor = Udecod[contador];
        valor2 = Htran[contador][k];
        res = valor * valor2;
        Suma_FilaS[contador] = res;
        contador++;
      }
      else
      {
        suma = Suma_FilaS[0] + Suma_FilaS[1] + Suma_FilaS[2] + Suma_FilaS[3] + Suma_FilaS[4] + Suma_FilaS[5];
        suma = suma % 2;
        UHtran2[k] = suma;
        contador = 0;
        k++;
      }
    }
  }
  



lcd.clear();
     lcd.print("u=");
   lcd.setCursor(0,0);
  for (c = 0; c < 6; c++)  {
      comprobacion = u[c];
        lcd.setCursor(c+3,0);
       
        lcd.print(comprobacion);
  }
  
lcd.setCursor(0,1);
 lcd.print("Sind=");
  
  for (c = 0; c < 3; c++)  {
      comprobacion = Sx_vp[c];
    
        lcd.setCursor(c+5,1);
       
        lcd.print(comprobacion);
  }
     delay(2000);

lcd.clear();

        lcd.print("Udec=");
   lcd.setCursor(0,0);
  for (c = 0; c < 6; c++)  {
      comprobacion = Udecod[c];
        lcd.setCursor(c+5,0);
       
        lcd.print(comprobacion);
  }

  delay(2000);
  
  /*lcd.setCursor(0,0);
  for(i=0;i<6;i++){
    
  lcd.print(y[i]);
  }
  delay(1000);
  lcd.clear();
 */
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
}
