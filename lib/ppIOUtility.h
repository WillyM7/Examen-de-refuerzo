/**
 * ©2023 pat_mic, All Rights Reserved.
 * @author: pat_mic
 * @date : 2022.08.24
 * libreria de utilitarios para fines académicos de programación I - EPN
 **/

#include <iostream>
#include <sstream>
#include <string>
#include <string.h>
#include <vector>
#include <conio.h>
using namespace std;

const string WHITESPACE = " \n\r\t\f\v";

/**
 * trimLeft: retorna una cadena eliminando espacios en blanco por la izquierda
 * @param s   : cadena de caracteres
*/
string ppTrimLeft(const string &s)
{
    size_t start = s.find_first_not_of(WHITESPACE); //     "   pepep"
    return (start == string::npos) ? "" : s.substr(start);
}
/**
 * trimRight: retorna una cadena eliminando espacios en blanco por la derecha
 * @param s   : cadena de caracteres
*/
string ppTrimRight(const string &s)
{
    size_t end = s.find_last_not_of(WHITESPACE); //      "pepe 		"
    return (end == string::npos) ? "" : s.substr(0, end + 1);
}
/**
 * trim: retorna una cadena eliminando espacios en blanco por la derecha e izquierda
 * @param s   : cadena de caracteres
*/
string ppTrim(const string &s)
{
    return ppTrimRight(ppTrimLeft(s));		// " loro 	"  -> "loro"
}
/**
 * tolowerStr: retorna una cadena en minusculas
 * @param str   : cadena de caracteres
*/
string ppToLowerStr(string str)
{
    for (int x=0; x < str.length(); x++)
        str[x] = tolower(str[x]);
    return str;
}
/**
 * toupperStr: retorna una cadena en mayusculas
 * @param str   : cadena de caracteres
*/
string ppToUpperStr(string str)
{
    for (int x=0; x < str.length(); x++)
        str[x] = toupper(str[x]);
    return str;
}
/**
 * toCapitalStr: retorna una cadena con la 1ra letra en mayusculas
 * @param str   : cadena de caracteres
*/
string ppToCapitalStr(string str)
{
    for (int x=0; x < str.length(); x++)
         str[x] = (x==0) ? toupper(str[x]) : tolower(str[x]);
    return str;
}
/**
 * getString :divide una cadena de caracteres segun un caracter
 * @param str   : cadena de caracteres
 * @param delim : carater para segmentar
 * @param outlst: lista de cadenas obtenidas de la division
*/
void ppSplitStr( const string  str, const char delim,  vector<string> &outlst )
{
    string strDiv;
    stringstream s(str);
    while ( getline(s, strDiv, delim) )
        outlst.push_back(strDiv);
}
/**
 * getString : Obtiene una cadena desde la consola
 * @param etiqueta  : Nombre de la etiqueta del campo a obtener
 * @param respuesta : int, valor a leer de tipo entero
 */
void ppGetString(string etiqueta, string &respuesta)
{
 	cout << etiqueta;
    //getline(cin, respuesta);
    cin>>respuesta;
    cin.get();
	cin.clear();
    fflush(stdin);
}
/**
 * getNumber : Obtiene un numero entero desde la consola
 * @param etiqueta  : Nombre de la etiqueta del campo a obtener
 * @param respuesta : int, valor a leer de tipo entero
 */
void ppGetNumber(string etiqueta, int &respuesta)
{
	cout<< etiqueta;
	cin >> respuesta ;
	cin.clear();
    fflush(stdin);
}
/**
 * getNumber : Obtiene un numero decimal desde la consola
 * @param etiqueta  : Nombre de la etiqueta del campo a obtener
 * @param respuesta : float,  valor a leer de tipo entero
 */
void ppGetNumber(string etiqueta, float &respuesta)
{
	cout<< etiqueta;
	cin >> respuesta;
	cin.clear();
    fflush(stdin);
}
/**
 * getNumberPosi : Obtiene un numero entero positivo desde la consola
 * @param etiqueta  : Nombre de la etiqueta del campo a obtener
 * @param respuesta : int que referencia a memoria del numero a leer
 */
void ppGetNumberPosi(string etiqueta, int &respuesta)
{
    string str;
    do {
        cout<<etiqueta;
        getline (cin,str);
        
        cin.clear();
        fflush(stdin);
        try
        {
            respuesta = stoi(str);
        }
        catch(const exception& e)
        {
            respuesta =-1;
            //cout << " :( Valor no valido... " << endl;
        }
    } while (respuesta<0);
}
/**
 * ppGetNumberBetween : Obtiene un numero entero entre min y max desde la consola
 * @param etiqueta  : Nombre de la etiqueta del campo a obtener
 * @param respuesta : int que referencia a memoria del numero a leer
 */
int ppGetNumberBetween(string etiqueta, int min, int max)
{
    int num;
    string str;
    bool numValido = false;
    do {
        cout<<etiqueta;
        getline (cin,str);

        numValido = false;
        cin.clear();
        fflush(stdin);
        try
        {
            num = stoi(str);
            if ((num >= min) && (num <= max))
                numValido = true;
        }
        catch(const exception& e)
        {
            num =min-1;
        }
    } while (!numValido);
    return num;
}
/**
 * procedimiento obtiene dato char
 **/
void ppGetCharArray(string etiqueta, char* dato )
{
    string str;
    cout << etiqueta;
    getline(cin, str);    //      pepe

    //cleaning data : space, tab, ret,....
    str = ppTrim(str);
    strcpy(dato ,str.c_str());

    cin.clear();
    fflush(stdin);
}

string ppGetPassword(string etiqueta)
{
    int i=0;
    char s[10] = { 0 };
    cout<<etiqueta;
	while ((s[i] = _getch()) && int(s[i++])!= 13)
		_putch('*');
	s[--i] ='\0';
	cin.clear();
    fflush(stdin);
	cout<<"\n";
	return s;
}

string ppGetStringTrim(string etiqueta)
{
    string str;
    do {
        cout<<etiqueta;
        getline (cin,str);
        cin.clear();
        fflush(stdin);
        try
        {
            str = ppTrim(str);
            if (str == "")
                throw 100;
        }
        catch(const exception& e)
        {
            cout << " :( Valor no valido... " << endl;
        }
    } while (str.length()<=0);
    return str;
}

void ppClearTerminal()
{
    // system ("cls");
    // system ("clear");
    cout << "\033[H\033[2J\033[3J" ;
    cin.clear();
    fflush(stdin);
}