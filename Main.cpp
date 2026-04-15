#include "Class.h"
#include <iostream>
#include <set>
#include <list>
#include <string>
#include <map>   // para std::map
using namespace std; // o poner std::string, std::map, etc
int main(){
    list<Cooperativista*> Lista;
    map<int, Cooperativista*> indxCooperativistas;
    map<int, Directiva*>indxDirectiva;
    int opcion = -1;
    while (opcion!=0){
        cout <<"\n============== MENU ==============\n";
        cout << "1 - Crear nuevo Coperativista\n";
        cout << "2 - Eliminar Cooperativista\n";
        cout << "3 - Mostrar Cooperativista\n";
        cout << "4 - Agregar a Directiva\n";
        cout << "5 - Ver Lista De Cooperativistas\n";
        cout << "6 - Liberar Memoria\n";
        cout << "0 - Salir\n";
        cout << "Ingrese una Opcion: ";
        cin >> opcion;
        switch (opcion){
            case 1:{
            int Cedula, age, Aport;
            string Name;
            cout << "\nIngrese CI: ";
            cin >> Cedula;
            cout << "\nIngrese Nombre: ";
            cin.ignore();
            getline(cin,Name);
            cout << "\nIngrese Edad: ";
            cin >> age;
            cout << "\nIngrese Dinero Aportado: ";
            cin >> Aport;
            Cooperativista* nuevo;
            nuevo=new Cooperativista(Cedula, Name, age, Aport);
            Lista.push_back(nuevo);
            indxCooperativistas[Cedula] = nuevo;
            cout << "\nCooperativista creado con exito\n";
            break;
            }
            case 2:{
                int cedula;
                cout << "\nIngrese la Cedula del Cooperativista a Eliminar: ";
                cin >> cedula;
                Cooperativista* Eliminar = indxCooperativistas[cedula];
                delete Eliminar; 
                Lista.remove(Eliminar);
                indxCooperativistas.erase(cedula);
                cout << "\nEl cooperativista fue Eliminado con Exito";
                break;
            }
            case 3:{
                int cedula;
                cout << "\nIngrese CI del cooperativista que quiere ver: ";
                cin >> cedula;
                Cooperativista* imprimir = indxCooperativistas[cedula];
                cout << "\nCI: " << imprimir->GetCi() << endl;
                cout << "Nombre: " << imprimir->getNombre() << endl;
                cout << "Edad: " << imprimir->getEdad() << endl;
                cout << "Dinero Aportado: " << imprimir->getAportado() << endl;
                break;
            }
            case 4:{
                int cedula;
                string cargo;
                cout << "\nIngrese la Cedula del Coperativista que Ingresa a Directiva: ";
                cin >> cedula;
                Cooperativista* este=indxCooperativistas[cedula];
                indxCooperativistas.erase(cedula);
                Lista.remove(este);
                cout << "\nIngrese el Cargo que Ocupara en Directiva: ";
                cin >> cargo;
                Directiva* nuevo=new Directiva(este->GetCi() ,este->getNombre() ,este->getEdad() ,este->getAportado(), cargo);
                delete este;
                indxDirectiva[cedula]=nuevo;
                Lista.push_back(nuevo);
                break;
            }
            case 5:{
                cout << "\n==========Lista de Miembros de la Cooperativa==========\n";
                for (Cooperativista* p : Lista){
                    if (indxDirectiva.count(p->GetCi())>0)
                    {
                        Directiva* imprimir = indxDirectiva[p->GetCi()];
                        cout << "\nCI: " << imprimir->GetCi() << endl;
                        cout << "Nombre: " << imprimir->getNombre() << endl;
                        cout << "Edad: " << imprimir->getEdad() << endl;
                        cout << "Dinero Aportado: " << imprimir->getAportado() << endl;
                        cout << "Cargo: " << imprimir->getCargo() << endl;
                        cout << "---------------------";
                    }
                    else{
                        Cooperativista* imprimir = indxCooperativistas[p->GetCi()];
                        cout << "\nCI: " << imprimir->GetCi() << endl;
                        cout << "Nombre: " << imprimir->getNombre() << endl;
                        cout << "Edad: " << imprimir->getEdad() << endl;
                        cout << "Dinero Aportado: " << imprimir->getAportado() << endl;
                        cout << "---------------------";                    
                    }
                }
                break;
            }
        }  
    }
return 0;
}

