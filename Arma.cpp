//
// Created by aisha on 20/11/2026.
//
#include "Arma.h"
#include "Objeto.h"
#include <iostream>
#include <string>
using namespace std;

Arma::Arma(string nombre,double precio ,int cantidad, double precioVenta, bool acumulable,int dano,int durabilidad,int municion,int capacidadMunicion, bool usaMunicion,string tipoMunicion): Objeto (nombre, precio, cantidad,precioVenta, acumulable) {
    this->dano = dano;
    this->municion = municion;
    this->durabilidad = durabilidad;
    this->capacidadMunicion = capacidadMunicion;
    this->usaMunicion = usaMunicion;
    this->tipoMunicion = tipoMunicion;
}
Arma::~Arma() {

}
int Arma::getDano() {
    return this->dano;
}
int Arma::getDurabilidad() {
    return this->durabilidad;
}
int Arma::getMunicion() {
    return this->municion;
}
string Arma::getTipoMunicion() {
    return tipoMunicion;
}
int Arma::atacar() {
    if (this->usar() == true) {
        return this->dano;
    }
    else {
        return 0;
    }
}

bool  Arma::usar(){
    if (this->usaMunicion  == true) {
        if (this->municion > 0) {
            municion--;
            return true;
        }
        else {
            cout<<"Necesitas recargar"<<endl;
            return false;
        }
    }
    else {
          return true;
        }
    }
bool Arma::recargar(int cantidad, string tipoMunicion) {
    if (this->usaMunicion == false) {
        return false;
    }

    if (cantidad <= 0) {
        return false;
    }

    if (this->tipoMunicion != tipoMunicion) {
        return false;
    }


    this->municion += cantidad;
    return true;



}

void Arma::perderDurabilidad(int cantidad) {
    if (cantidad > 0) {
        this->durabilidad -=cantidad;
        if (durabilidad <= 0) {
            this->durabilidad = 0;

        }
    }
}
bool Arma::esArma() {
    return true;
}
int Arma::getCapacidadMunicion() {
    return capacidadMunicion;
}

bool Arma::getUsaMunicion() {
    return usaMunicion;
}