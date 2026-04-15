#include <string>
#include <map>   // para std::map
#include <list>  // para std::list
using namespace std; // o poner std::string, std::map, etc.s
class Cooperativista{
    private:
        int Ci;
        string Nombre;
        int Edad;
        int Aportado;
    public:
        /*hacer setters para todos los elementos asi puedo crear un tipo directiva*/
        Cooperativista(int ci, string name, int age, int aport);
        int GetCi();
        string getNombre();
        int getEdad();
        int getAportado();
};
class Directiva : public Cooperativista{
    private:
        string Cargo;
    public:
        Directiva(int ci, string name, int age, int aport, string cargo);
        string getCargo();
}; 



