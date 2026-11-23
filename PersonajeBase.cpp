
//
// Created by aisha on 20/11/2026.
//
#include "PersonajeBase.h"
#include <iostream>

using namespace std;
PersonajeBase::PersonajeBase(string nombre,int vida) {
    this->nombre = nombre;
    this->vida = vida;
}
string PersonajeBase::getNombre() {
    return this->nombre;
}
int PersonajeBase::getVida() {
    return this->vida;
}
void PersonajeBase::recibirDano(int cantidad) {
    vida = vida - cantidad;
    if (vida < 0) {
        vida = 0;
    }
}
bool PersonajeBase::estaVivo() {
    return (vida > 0)?  true : false;
}
int PersonajeBase::atacar() {
   cout <<"El personaje realiza un ataque"<<endl;
    return dano;
}
void PersonajeBase::setVida(int vida) {
    this->vida = vida;
}
void PersonajeBase::setNombre(string nombre) {
    this->nombre = nombre;
}