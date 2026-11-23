//
// Created by aisha on 20/11/2026.
//
#include "Objeto.h"
#include "Personaje.h"
#include <string>
#include <iostream>
using namespace std;
Objeto::Objeto(string nombre, double precio, int cantidad, double precioVenta, bool acumulable) {
    this->nombre = nombre;
    this->precio = precio;
    this->precioVenta = precioVenta;
    this->cantidad = cantidad;
    this->acumulable = acumulable;
}
Objeto::~Objeto() {

}
string Objeto::getNombre() {
    return this->nombre;
}
double Objeto::getPrecio() {
    return this->precio;
}
int Objeto::getCantidad() {
    return this->cantidad;
}
double Objeto::getPrecioVenta() {
    return this->precioVenta;
}
bool Objeto::esAcumulable() {
    return this->acumulable;
}
bool Objeto::esArma() {
    return false;
}
bool Objeto::usar(Personaje& personaje) {

    if (nombre == "Vendaje") {

        personaje.curarse(1000);
        return true;
    }

    else if (nombre == "Aceite de serpiente") {

        if (personaje.getVida() >= 80) {
            return false;
        }

        personaje.curarse(80 - personaje.getVida());
        return true;
    }

    return false;
}
void Objeto::aumentarCantidad(int cantidad) {
    this->cantidad += cantidad;
}
void Objeto::disminuirCantidad(int cantidad) {
    if (this->cantidad  < cantidad) {
        cout << "No tienes suficientes unidades de este objeto." << endl;
    }
    else {
        this->cantidad -= cantidad;
    }
}
bool Objeto::esArmadura() {
    return false;
}