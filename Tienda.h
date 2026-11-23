//
// Created by aisha on 20/11/2026.
//

#ifndef RIELESMUERTOS_TIENDA_H
#define RIELESMUERTOS_TIENDA_H
#include "Objeto.h"
#include "Personaje.h"
#include <vector>
#include <string>
using namespace std;
class Tienda {
private:
    string nombre;
    vector<Objeto*> inventario;
public:
    Tienda(string nombre);
    ~Tienda();
    void mostrarProductos();
    bool venderProducto(Objeto* objeto, Personaje& personaje);
    bool comprarObjeto(Objeto* objeto, Personaje& personaje);
    bool venderMunicion(Personaje& personaje,  string tipoMunicion);
    Objeto* getProducto(int posicion);


};
#endif //RIELESMUERTOS_TIENDA_H
