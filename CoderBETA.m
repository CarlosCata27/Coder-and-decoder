clear all;
close all;
%Posibles mensajes de entrada
M = [0 0 0; 
     0 0 1;
     0 1 0;
     0 1 1;
     1 0 0;
     1 0 1;
     1 1 0;
     1 1 1]
%Mensaje a codificar
m = [0 1 1];
%Matriz Generadora
G = [1 0 0 1 0 1;
     0 1 0 0 1 1;
     0 0 1 1 1 0];
%Matriz Identidad
I = [1 0 0;
     0 1 0;
     0 0 1];
%Matriz de Paridad
P = [1 0 1;
     0 1 1;
     1 1 0];
%===== Coder =====%

%Matriz de codigo Mod2
U = mod(M*G,2)
%Vector de codigo Mod2
u = mod(m*G,2)

%===== Canal =====%
%Verificacion de Paridad
Ptran = P.';
H = [Ptran,I];
Htran = H.'
%Verificacion de Paridad (Mensaje)
UHtran = mod(m*G*Htran,2)
%Verificacion de Paridad (Palabra de codigo - Matriz)
VP = mod(U*Htran,2);
%Verificacion de Paridad (Palabra de codigo - Vector)
VP2 = mod(u*Htran,2);
%Corroborando
%Sindrome = mod(G*Htran,2)

%Secuencias de error
e = [0 0 0 0 0 0;
     0 0 0 0 0 1;
     0 0 0 0 1 0;
     0 0 0 1 0 0;
     0 0 1 0 0 0;
     0 1 0 0 0 0;
     1 0 0 0 0 0;
     1 0 0 0 1 0;
     0 0 1 0 0 1;
     0 1 0 1 0 0]
 
S = mod(e*Htran,2)
%Arreglo Standar 
SA000 = [mod(U(1,:)+e(1,:),2);
         mod(U(2,:)+e(1,:),2);
         mod(U(3,:)+e(1,:),2);
         mod(U(4,:)+e(1,:),2);
         mod(U(5,:)+e(1,:),2);
         mod(U(6,:)+e(1,:),2);
         mod(U(7,:)+e(1,:),2);
         mod(U(8,:)+e(1,:),2)]; 
     
SA001 = [mod(U(1,:)+e(2,:),2);
         mod(U(2,:)+e(2,:),2);
         mod(U(3,:)+e(2,:),2);
         mod(U(4,:)+e(2,:),2);
         mod(U(5,:)+e(2,:),2);
         mod(U(6,:)+e(2,:),2);
         mod(U(7,:)+e(2,:),2);
         mod(U(8,:)+e(2,:),2)]; 
     
SA010 = [mod(U(1,:)+e(3,:),2);
         mod(U(2,:)+e(3,:),2);
         mod(U(3,:)+e(3,:),2);
         mod(U(4,:)+e(3,:),2);
         mod(U(5,:)+e(3,:),2);
         mod(U(6,:)+e(3,:),2);
         mod(U(7,:)+e(3,:),2);
         mod(U(8,:)+e(3,:),2)];
     
SA100 = [mod(U(1,:)+e(4,:),2);
         mod(U(2,:)+e(4,:),2);
         mod(U(3,:)+e(4,:),2);
         mod(U(4,:)+e(4,:),2);
         mod(U(5,:)+e(4,:),2);
         mod(U(6,:)+e(4,:),2);
         mod(U(7,:)+e(4,:),2);
         mod(U(8,:)+e(4,:),2)];
     
SA110 = [mod(U(1,:)+e(5,:),2);
         mod(U(2,:)+e(5,:),2);
         mod(U(3,:)+e(5,:),2);
         mod(U(4,:)+e(5,:),2);
         mod(U(5,:)+e(5,:),2);
         mod(U(6,:)+e(5,:),2);
         mod(U(7,:)+e(5,:),2);
         mod(U(8,:)+e(5,:),2)]; 
     
SA011 = [mod(U(1,:)+e(6,:),2);
         mod(U(2,:)+e(6,:),2);
         mod(U(3,:)+e(6,:),2);
         mod(U(4,:)+e(6,:),2);
         mod(U(5,:)+e(6,:),2);
         mod(U(6,:)+e(6,:),2);
         mod(U(7,:)+e(6,:),2);
         mod(U(8,:)+e(6,:),2)];
     
SA101 = [mod(U(1,:)+e(7,:),2);
         mod(U(2,:)+e(7,:),2);
         mod(U(3,:)+e(7,:),2);
         mod(U(4,:)+e(7,:),2);
         mod(U(5,:)+e(7,:),2);
         mod(U(6,:)+e(7,:),2);
         mod(U(7,:)+e(7,:),2);
         mod(U(8,:)+e(7,:),2)];
     
SA111a = [mod(U(1,:)+e(8,:),2);
         mod(U(2,:)+e(8,:),2);
         mod(U(3,:)+e(8,:),2);
         mod(U(4,:)+e(8,:),2);
         mod(U(5,:)+e(8,:),2);
         mod(U(6,:)+e(8,:),2);
         mod(U(7,:)+e(8,:),2);
         mod(U(8,:)+e(8,:),2)];
     
SA111b = [mod(U(1,:)+e(9,:),2);
         mod(U(2,:)+e(9,:),2);
         mod(U(3,:)+e(9,:),2);
         mod(U(4,:)+e(9,:),2);
         mod(U(5,:)+e(9,:),2);
         mod(U(6,:)+e(9,:),2);
         mod(U(7,:)+e(9,:),2);
         mod(U(8,:)+e(9,:),2)];
     
SA111c = [mod(U(1,:)+e(10,:),2);
         mod(U(2,:)+e(10,:),2);
         mod(U(3,:)+e(10,:),2);
         mod(U(4,:)+e(10,:),2);
         mod(U(5,:)+e(10,:),2);
         mod(U(6,:)+e(10,:),2);
         mod(U(7,:)+e(10,:),2);
         mod(U(8,:)+e(10,:),2)];   

%msgPrueba = [0     0     1     1     1     0];
y = [0     0     0     0    0     1];

%DECODER========

%Error aleatorio
%y = [1 0 1 1 0 0]
%Verificacion de Paridad (palabra decodificad)
%UHtran2 = mod(y*Htran,2)
errorDoble = 0; %para indicar que se encontró error doble en arreglo

Sx = mod(y*Htran,2)

if Sx == S(2,:)
    ex = SA001(1,:)
elseif Sx == S(3,:)
    ex = SA010(1,:)
elseif Sx == S(4,:)
    ex = SA100(1,:)
elseif Sx == S(5,:)
    ex = SA110(1,:)
elseif Sx == S(6,:)
    ex = SA011(1,:)
elseif Sx == S(7,:)
    ex = SA101(1,:)
elseif Sx == S(8,:)   
%Primer error doble
    if u(1,1) ~= y(1, 1) && u(1,5) ~= y(1, 5)
        ex = SA111a(1,:)
    end
    %Segundo error doble
    if u(1,3) ~= y(1, 3) && u(1,6) ~= y(1, 6)
        ex = SA111b(1,:)
    end
    if u(1,2) ~= y(1, 2) && u(1,4) ~= y(1, 4)
        ex = SA111c(1,:)
    end
end
Udecod = mod(y+ex,2)

%Verificacion de Paridad (palabra decodificad)
UHtran2 = mod(Udecod*Htran,2)