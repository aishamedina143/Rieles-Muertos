//
// Created by aisha on 20/11/2026.
//
#include "Villano.h"
#include <iostream>
#include <string>
using namespace std;

Villano::Villano(string nombre, int vida, string tipo, int dano, double recompensa)
    : PersonajeBase(nombre, vida) {

    this->tipo = tipo;
    this->dano = dano;
    this->recompensa = recompensa;
}
Villano::~Villano() {

}

int Villano::atacar() {
    return dano;
    
}

void Villano::perseguir() {
    cout << "El villano esta persiguiendo al jugador." << endl;

}

void Villano::aparecer() {
    cout << "Ha aparecido un " << tipo << "!" << endl;
}
double Villano::getRecompensa() {
    return recompensa;
}
