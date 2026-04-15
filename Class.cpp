#include "Class.h"
#include <iostream>
#include <string>
#include <map>   // para std::map
#include <list>  // para std::list
using namespace std; // o poner std::string, std::map, etc.


Cooperativista :: Cooperativista(int ci, string name, int age, int aport){    
    Ci=ci;
    Nombre=name;
    Edad=age;
    Aportado=aport;
};
int Cooperativista :: GetCi(){
    return Ci;
};
string Cooperativista :: getNombre(){
    return Nombre;
};
int Cooperativista :: getEdad(){
    return Edad;
};
int Cooperativista :: getAportado(){
    return Aportado;
};
Directiva :: Directiva(int ci, string name, int age, int aport, string cargo) : Cooperativista(ci, name, age, aport){
    Cargo=cargo;
};
string Directiva :: getCargo(){
    return Cargo;
};



