//
// Created by aisha on 20/11/2026.
//
#include "Tienda.h"
#include "Arma.h"
#include "Armadura.h"
#include "Personaje.h"
#include <iostream>
using namespace std;

Tienda::Tienda(string nombre) {
    this->nombre = nombre;

    if (nombre == "Tienda General") {
        inventario.push_back(new Objeto("Barril de polvora",25,2,12,true));
        inventario.push_back(new Objeto("Municion de ballesta",15,1,7,true));
        inventario.push_back(new Objeto("Ballesta",20,1,10,false));
        inventario.push_back(new Objeto("Trampa para osos",30,4,15,true));
        inventario.push_back(new Objeto("Pico",30,1,1,false));
        inventario.push_back(new Objeto("Balas de canon",30,3,15,true));
        inventario.push_back(new Objeto("Casco de minero",25,1,12,false));
        inventario.push_back(new Objeto("Alambre de puas",15,10,7,true));
        inventario.push_back(new Objeto("Carbon",20,100,10,true));
        inventario.push_back(new Objeto("Periodico", 0, 3, 0, true));
        inventario.push_back(new Armadura("Armadura",20,1,10,false,15,100));
    }
    else if (nombre == "Armeria") {
        inventario.push_back(new Arma("Revolver normal", 25, 1, 12, false, 10, 100, 0, 0, true, "Ligera"));
        inventario.push_back(new Arma("Revolver mediano", 20, 1, 10, false, 12, 100, 0, 0, true, "Mediana"));
        inventario.push_back(new Arma("Escopeta", 40, 1, 20, false, 20, 100, 0, 0, true, "Escopeta"));
        inventario.push_back(new Arma("Rifle", 40, 1, 20, false, 18, 100, 0, 0, true, "Rifle"));
        inventario.push_back(new Arma("Ametralladora", 40, 1, 20, false, 8, 100, 0, 0, true, "Ametralladora"));
    }
    else if (nombre == "Doctor") {
        inventario.push_back(new Objeto("Vendaje", 10, 20, 5, true));
        inventario.push_back(new Objeto("Aceite de serpiente", 15, 20, 7, true));
    }
    else if (nombre == "Puesto de comercio") {
        inventario.push_back(new Objeto("Lingote de oro", 0, 10, 25, false));
        inventario.push_back(new Objeto("Lingote de plata", 0, 10, 15, false));
        inventario.push_back(new Objeto("Cuadro antiguo", 0, 10, 20, false));
        inventario.push_back(new Objeto("Reliquia de vampiro", 0, 10, 35, false));
    }
}
Tienda::~Tienda() {
    for (int i = 0; i < inventario.size(); i++) {
        delete inventario[i];
    }
}

void Tienda::mostrarProductos() {
    cout << "Productos disponibles en " << nombre << ":" << endl;

    if (inventario.empty()) {
        cout << "No hay productos disponibles." << endl;
        return;
    }

    for (int i = 0; i < inventario.size(); i++) {
        cout << i + 1 << ". "
             << inventario[i]->getNombre()
             << " - "
             << inventario[i]->getPrecio()
             << " monedas" << endl;
    }
}
bool Tienda::venderProducto(Objeto* objeto, Personaje& personaje) {

    for (int i = 0; i < inventario.size(); i++) {

        if (inventario[i] == objeto) {

            if (personaje.getDinero() < objeto->getPrecio()) {
                return false;
            }

            if (objeto->esAcumulable()) {

                Objeto* copia = new Objeto(
                    objeto->getNombre(),
                    objeto->getPrecio(),
                    1,
                    objeto->getPrecioVenta(),
                    objeto->esAcumulable()
                );

                if (personaje.comprar(copia)) {

                    objeto->disminuirCantidad(1);

                    if (objeto->getCantidad() == 0) {
                        delete objeto;
                        inventario.erase(inventario.begin() + i);
                    }

                    return true;
                }

                delete copia;
                return false;
            }

            if (personaje.comprar(objeto)) {
                inventario.erase(inventario.begin() + i);
                return true;
            }

            return false;
        }
    }

    return false;
}
bool Tienda::comprarObjeto(Objeto* objeto, Personaje& personaje) {

    if (objeto == nullptr) {
        return false;
    }

    if (nombre != "Puesto de comercio") {
        return false;
    }

    string nombreObjeto = objeto->getNombre();

    if (nombreObjeto != "Lingote de oro" &&
        nombreObjeto != "Lingote de plata" &&
        nombreObjeto != "Cuadro antiguo" &&
        nombreObjeto != "Reliquia de vampiro") {

        cout << "El comerciante no acepta este objeto." << endl;
        return false;
        }

    if (personaje.vender(objeto)) {
        inventario.push_back(objeto);
        cout << "Has vendido " << nombreObjeto << " por "
             << objeto->getPrecioVenta() << " monedas." << endl;
        return true;
    }

    return false;
}
bool Tienda::venderMunicion(Personaje& personaje, string tipoMunicion) {

    if (tipoMunicion == "Ligera") {
        return personaje.comprarMunicion(10, "Ligera", 15);
    }

    else if (tipoMunicion == "Mediana") {
        return personaje.comprarMunicion(10, "Mediana", 15);
    }

    else if (tipoMunicion == "Escopeta") {
        return personaje.comprarMunicion(5, "Escopeta", 15);
    }

    else if (tipoMunicion == "Rifle") {
        return personaje.comprarMunicion(10, "Rifle", 15);
    }

    else if (tipoMunicion == "Ametralladora") {
        return personaje.comprarMunicion(30, "Ametralladora", 30);
    }

    return false;
}
Objeto* Tienda::getProducto(int posicion) {
    if (posicion < 0 || posicion >= inventario.size()) {
        return nullptr;
    }

    return inventario[posicion];
}