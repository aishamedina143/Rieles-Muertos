//
// Created by aisha on 20/11/2026.
//
#include "Armadura.h"
#include <iostream>
using namespace std;

Armadura::Armadura(string nombre, double precio, int cantidad,double precioVenta, bool acumulable,int defensa, int durabilidad):Objeto(nombre,precio,cantidad,precioVenta,acumulable) {
    this->durabilidad = durabilidad;
    this->defensa = defensa;
}
Armadura::~Armadura() {

}

int Armadura::reducirDano(int cantidad) {
    if (cantidad <= 0) {
        return 0;
    }
    if (durabilidad <= 0) {
        return cantidad;
    }
    int danoFinal = cantidad - defensa;
    if (danoFinal < 0) {
        danoFinal = 0;
    }
    durabilidad--;
    return danoFinal;
}
bool Armadura::usar() {
    if (durabilidad <= 0) {
        return false;
    }

    return true;
}
bool Armadura::esArmadura() {
    return true;
}
int Armadura::getDefensa() {
    return defensa;
}

int Armadura::getDurabilidad() {
    return durabilidad;
}