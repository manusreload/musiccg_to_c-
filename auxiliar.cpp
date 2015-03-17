#include "auxiliar.h"

string toUpperCase(const string& _cadena)
{
    std::locale loc;
    string cadena;
    for (int i = 0; i < cadena.length(); ++i) 
    {
        cadena[i] = toupper(_cadena[i],loc);
    }
    return cadena;
}


