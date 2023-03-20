// Usuario: Willy Mosquera
//  Codigo     Tipo Arsenal Bélico
//  a          Aeronaves
//  b          Bombarderos
//  c          Convoy   
//  d          Drones 
//  t          Tanques

// TipoBomba        AFD
// BOMB-II          a*b+c
// BOMB-IP          ab*c+
// BOMB-IPI         a+bc*

#include <iostream>
#include <unistd.h>
#include <fstream>
#include <vector>
#include "../lib/ppIOUtility.h"
#include "../lib/wmcolor.h"
using namespace std;

const string WMCEDULA = "1754217899";
const string WMNOMBRE = "WILLY DAMIAN MOSQUERA GALEANO";

struct wmCoordenada{
     int capacidadBelica;       
     string geolocalizacion;       
     string detalleArsenal;     
     struct wmCoordenada *izq, *der;
};
typedef struct wmCoordenada *ABB;
ABB arbol           = NULL;        // creado Arbol Binario de Coordenadas
int arbolNroNodos   = 0;           // numero de nodos del arbol
int arbolCapBelica  = 0;           // suma de la capcidad bélica
string arbolSecCarga= "";           // secuencia de nodos ingresados en el arbol sin repeticion
int const TKError   =-1;           // Token de Error
int const TKBomba   =-2;           // Token de Bomba 
string const ALFA = "abc.";        // Tipo Arsenal
/*  Automata finito determinista

    [q0]      --- b  --->   [q2] (c)
     |-- a -->  [q1] -- b -->|
                 (a)
     _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ __ _ _ _ _ _ _ _ 
     Q     |  { a           b           c           ' '     \t  }
     _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ __ _ _ _ _ _ _ _ 
     0     |    1           2           r           er
     1     |    1           2           r           er
     2     |    er          er          q2          ok1
     _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ __ _ _ _ _ _ _ _ 

*/
int mtBOMBIA_I[3][4]=    {// matriz de transicion
                         {1,         2,         TKError,     TKError},
                         {1,         2,         TKError,     TKError},
                         {TKError,   TKError,   2,           TKBomba}
                         }; 
int getIndexAlfabeto(char c)
{
    int index = ALFA.find(c);
    if(index < ALFA.length())
        return index;
    return TKError;    
}
string aplicaBOMBIA_I(string tipoArsenal) 
{        
    int q=0, l=0;
    for (auto &&c : tipoArsenal+"." ) // caracter de fin de cadena
    {
          l = getIndexAlfabeto(c);
          q = mtBOMBIA_I[q][l];
          //cout<< c << " " << q <<","<< l <<endl;
          if(q == TKError || q > 3)
               return "";
          if(q == TKBomba)
               return "BOMBIA_II";
    }
    return "";
}

ABB crearNodo(const string data)  
{
     try
     {
          vector<string> splitData;
          ppSplitStr(data,',',splitData);
          ABB nuevaCoor = new(struct wmCoordenada);
          nuevaCoor->capacidadBelica    = stoi(splitData[0]); 
          nuevaCoor->geolocalizacion    = ppTrim(splitData[1]);
          nuevaCoor->detalleArsenal     = ppTrim(splitData[2]);
          nuevaCoor->izq = NULL;
          nuevaCoor->der = NULL;
          return nuevaCoor;
     }
     catch(const exception& e)
     {
          setTextColor(textColorRed);
          cout << ">> Error: "<< data << " -> " << e.what() << endl;
          setTextColor(textColorGreen);
     }
     return NULL;
}
void insertar(ABB &arbol, ABB coord) 
{
     if(arbol==NULL)
     {
          arbol = coord; 
          arbolNroNodos++;
          arbolCapBelica += coord->capacidadBelica;
          arbolSecCarga  += to_string(coord->capacidadBelica) + " ";
     }
     else if(coord->capacidadBelica < arbol->capacidadBelica)
          insertar(arbol->izq, coord);
     else if(coord->capacidadBelica > arbol->capacidadBelica)
          insertar(arbol->der, coord);
}
void preOrden(ABB arbol)
{
     if(arbol!=NULL)
     {
          cout << arbol->capacidadBelica <<" ";
          preOrden(arbol->izq);
          preOrden(arbol->der);
     }
}
void enOrden(ABB arbol)
{
     if(arbol!=NULL)
     {
          enOrden(arbol->izq);
          cout << arbol->capacidadBelica << " ";
          enOrden(arbol->der);
     }
}
void postOrden(ABB arbol)
{
     if(arbol!=NULL)
     {
          postOrden(arbol->izq);
          postOrden(arbol->der);
          cout << arbol->capacidadBelica << " ";
     }
}
void verArbol(ABB arbol, int n)
{
     if(arbol==NULL)
          return;
     verArbol(arbol->der, n+1);

     for(int i=0; i<n; i++)
         cout<<"\t";

     setTextColor(textColorBlue);
     cout << " "  << arbol->geolocalizacion
          << "."  << arbol->capacidadBelica;
     setTextColor(textColorWhite);
     cout << " { " << arbol->detalleArsenal;
     setTextColor(textColorRed);
     cout << "  " << aplicaBOMBIA_I(arbol->detalleArsenal);
     setTextColor(textColorWhite);
     cout << " }"<< endl;

     verArbol(arbol->izq, n+1);
}

void Loading(string str)

{ 
    string c= "(PUSH)"; 
    for(int i=0; i<= 100; i++)
    {   
        cout<< "\r " << c[i % 4] << " " << i << "%  ";
        usleep(5000);
    }
    cout << str  << endl;
}
/**
 * getCoordenadas : es un métdpo que permite leer la coordenadas desde un archivo
*/
void getCoordenadas() 
{
    string str;
    fstream f;
    cout << "[+]APILA coordenadas ..." << endl;
    f.open("../coordenadas.txt", ios_base::in); 
    if ( f.is_open() ) 
          while( !f.eof() )
          {
               getline( f, str );
               ABB coord  = crearNodo(str);
               if(coord != NULL)
               {
                    insertar(arbol , coord);
                    Loading(str);

               }
          }
    else
          cout << "Error de abrir el archivo de coordenadas" << endl;
    f.close();
}

int main(void)
{
     setTextColor(textColorGreen);
     getCoordenadas();
     
     setTextColor(textColorCyan);
     cout << endl << "\n\n[+]Informacion Arbol Binario de capacidad belica Ucrania";
     cout << endl << "   Developer-Nombre : "  << WMNOMBRE
          << endl << "   Developer-Cedula : "  << WMCEDULA
          << endl << "   Capacidad Belica : "  << arbolCapBelica
          << endl << "   Coordenada-Total : "  << arbolNroNodos
          << endl << "   Coordenada-SecCarga: " << arbolSecCarga;
     //     << endl << "   Coordenada-Arbol: "; preOrden(arbol);   //postOrden(arbol);   //enOrden(arbol); //
     setTextColor(textColorWhite);
     cout << "\n\n[+]ARBOL BINARIO DE COORDENADAS & BOMBA  \n\n";
     verArbol( arbol, 0);
}