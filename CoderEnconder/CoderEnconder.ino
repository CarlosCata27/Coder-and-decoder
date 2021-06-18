#include <Wire.h>
#include "DFRobot_LCD.h"
DFRobot_LCD lcd(16,2);  //16 characters and 2 lines of show

const int colorR = 255;
const int colorG = 0;
const int colorB = 0;

/*----MATRICES DEFINIDAS----*/
//Matriz de posibles mensajes
int M[8][3] = {{0,0,0},{0,0,1},{0,1,0},{0,1,1},{1,0,0},{1,0,1},{1,1,0},{1,1,1}};
//Matriz generadora
int G[3][6] = {{1 ,0 ,0, 1, 0, 1},{0 ,1 ,0 ,0 ,1 ,1},{0 ,0, 1, 1 ,1 ,0}};
//Matriz identidad
int I[3][3]={{1,0,0},{0,1,0},{0,0,1}};
//matriz de paridad
int P[3][3]={{1,0,1},{0,1,1},{1,1,0}}; 
/*----CODER----*/
int U[8][6] ={{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0}};
int u[6]={0,0,0,0,0,0};
int u_second[6]={0,0,0,0,0,0};
//Mensaje prueba
int m[3] = {0,0,1};
/*----CANAL----*/
int e[10][6] = {{0,0,0,0,0,0},{0,0,0,0,0,1} ,{0,0,0,0,1,0},{0,0,0,1,0,0},{0,0,1,0,0,0},{0,1,0,0,0,0},{1,0,0,0,0,0},{1,0,0,0,1,0}, {0,0,1,0,0,1},{0,1,0,1,0,0}};
int Ptran[3][3] ={{0,0,0},{0,0,0},{0,0,0}}; 
int H[3][6]={{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0}};
int Htran[6][3]={{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}};
int U_Htran[3]={0,0,0};
int VP[8][3] ={{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}};
int VP2[3] ={0,0,0};
int S[10][3]={{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}};

/*----VARIABLES GLOBALES----*/
int i =0;
int contador = 0, k=0,row=0,col=0,aux=0;
int valor =0, valor2=0, res=0, suma= 0;
int b=0, c=0;
int comprobacion=0;
int Suma_FilaU[3]={0,0,0};
int Suma_Filau[3]={0,0,0};
int Suma_Filau_second[3]={0,0,0};
int Suma_Filau_Htran[6]={0,0,0,0,0,0};
int Suma_FilaU_Htran[6]={0,0,0,0,0,0};
int Suma_FilaVP2Htran[6]={0,0,0,0,0,0};
int Suma_FilaS[6]={0,0,0,0,0,0};


void setup() {
    lcd.init();
    lcd.setRGB(colorR, colorG, colorB);//If the module is a monochrome screen, you need to shield it  
    //Serial.begin(9600);
    //----CODER----//
    //--Modulo 2 de matriz U Multiplicacion de M * G--//
    for(i = 0; i<8; i++)
    {
      k = 0;
      while(k<6)
      {
        if(contador<3)
        {
          valor = M[i][contador];
          valor2 = G[contador][k];       
          res = valor*valor2;
          Suma_FilaU[contador] = res;
          contador++;
        }
        else
        {
           suma = Suma_FilaU[0] + Suma_FilaU[1] + Suma_FilaU[2];
           suma = suma%2;
           U[i][k] = suma;
           contador =0;  
           k++;         
        }
                     
      }     
    }

    //--Modulo 2 de matriz u Multiplicacion de m * G--//
     for(i = 0; i<1; i++)
      {
        k = 0;
        while(k<6)
        {
          if(contador<3)
          {
            valor = m[contador];
            valor2 = G[contador][k];       
            res = valor*valor2;
            Suma_Filau[contador] = res;
            contador++;
          }
          else
          {
             suma = Suma_Filau[0] + Suma_Filau[1] + Suma_Filau[2];
             suma = suma%2;
             u[k] = suma;
             contador =0;  
             k++;         
          }
                       
        }
      }
    //----CANAL----//
    //Transponer matriz P     
    col=0,valor=0,row=0,aux=0;
    //Numero de Filas matriz 1
    while(row<3)
      {
        col = 0;
        //Numero de columnas matriz 2
        while(col<3)
        {
          //Numero de columnas Matriz 1 y filas Matriz 2 /*Aux*/
          if(aux<3)
          {
            valor = P[row][aux];
            Ptran[aux][col] = valor;                              
            aux++;
          }
          else
          {
             aux =0;  
             row++;
             col++;
          }
         }     
      }
      //Concatenacion para obtener matriz H

      int a = 3,n=3;
      for(int i = 0; i < a; i++){for(int j = 0; j < n;j++) { H[i][j] = Ptran[i][j];}}
      for(int i = 0 ; i < a ; i++){for(int j = n; j < (2*n) ; j++){ H[i][j] = I[i][j-n];}}
    //Transponer matriz H
    col=0,valor=0,row=0,aux=0;
    //Numero de Filas matriz 1
    while(row<3)
      {
        col = 0;
        //Numero de columnas matriz 2
        while(col<3)
        {
          //Numero de columnas Matriz 1 y filas Matriz 2 /*Aux*/
          if(aux<6)
          {
            valor = H[row][aux];
            Htran[aux][col] = valor;                              
            aux++;
          }
          else
          {
             aux =0;  
             row++;
             col++;
          }
         }     
      }

    //Verificacion de Paridad (Mensaje)
    suma=0,valor2=0;
    for(i = 0; i<1; i++)
      {
        k = 0;
        while(k<6)
        {
          if(contador<3)
          {
            valor = m[contador];
            valor2 = G[contador][k];       
            res = valor*valor2;
            Suma_Filau_second[contador] = res;
            contador++;
          }
          else
          {
             suma = Suma_Filau_second[0] + Suma_Filau_second[1] + Suma_Filau_second[2];
             suma = suma%2;
             u_second[k] = suma;
             contador =0;  
             k++;         
          }
        }
      }
      //Segunda multiplicacion
      for(i = 0; i<1; i++)
      {
        k = 0;
        while(k<3)
        {
          if(contador<6)
          {
            valor = u_second[contador];
            valor2 = Htran[contador][k];       
            res = valor*valor2;
            Suma_Filau_Htran[contador] = res;
            contador++;
          }
          else
          {
             suma = Suma_Filau_Htran[0] + Suma_Filau_Htran[1] + Suma_Filau_Htran[2]+ Suma_Filau_Htran[3]+ Suma_Filau_Htran[4]+ Suma_Filau_Htran[5];
             suma = suma%2;
             U_Htran[k] = suma;
             contador =0;  
             k++;         
          }
                       
        }
      }
     //Verificacion de Paridad (Palabra de codigo - Matriz)
     i=0,suma=0,valor=0,valor2=0,contador=0;
     for(i = 0; i<8; i++)
      {
        k = 0;
        while(k<6)
        {
          if(contador<3)
          {
            valor = U[i][k];
            valor2 = Htran[k][contador];       
            res = valor*valor2;
            Suma_FilaU_Htran[contador] = res;
            contador++;
          }
          else
          {
             suma = Suma_FilaU_Htran[0] + Suma_FilaU_Htran[1] + Suma_FilaU_Htran[2]+ Suma_FilaU_Htran[3]+ Suma_FilaU_Htran[4]+ Suma_FilaU_Htran[5];
             suma = suma%2;
             VP[i][k] = suma;
             contador =0;  
             k++; 
          }
        }
      }
      //Verificacion de Paridad (Palabra de codigo - Vector)
      i=0,suma=0,valor=0,valor2=0;
      for(i = 0; i<1; i++)
      {
        k = 0;
        while(k<3)
        {
          if(contador<6)
          {
            valor = u[contador];
            valor2 = Htran[contador][k];       
            res = valor*valor2;
            Suma_FilaVP2Htran[contador] = res;
            contador++;
          }
          else
          {
             suma = Suma_FilaVP2Htran[0] + Suma_FilaVP2Htran[1] + Suma_FilaVP2Htran[2]+ Suma_FilaVP2Htran[3]+ Suma_FilaVP2Htran[4]+ Suma_FilaVP2Htran[5];
             suma = suma%2;
             VP2[k] = suma;
             contador =0;  
             k++;         
          }
        }
      }

      //No se que sea S xD
      i=0,suma=0,valor=0,valor2=0;
      for(i = 0; i<10; i++)
      {
        k = 0;
        while(k<3)
        {
          if(contador<6)
          {
            valor = e[i][contador];
            valor2 = Htran[contador][k];       
            res = valor*valor2;
            Suma_FilaS[contador] = res;
            contador++;
          }
          else
          {
             suma = Suma_FilaS[0] + Suma_FilaS[1] + Suma_FilaS[2]+ Suma_FilaS[3]+ Suma_FilaS[4]+ Suma_FilaS[5];
             suma = suma%2;
             S[i][k] = suma;
             contador =0;  
             k++;         
          }
        }
      }


for(i=0; i<10; i++)  {
  for(c=0; c<3; c++)  
      {
        comprobacion = S[i][c];
        lcd.print(comprobacion);
      }
      delay(1500);
      lcd.clear();
}

/*    
for(i=0; i<8; i++)  {
  for(c=0; c<3; c++)  
      {
        comprobacion = VP[i][c];
        lcd.print(comprobacion);                        
      }
      delay(1500);
      lcd.clear();
}*/
      
    
    
    lcd.setCursor(0, 1);
    delay(100);
}

void loop() {
    // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
}
