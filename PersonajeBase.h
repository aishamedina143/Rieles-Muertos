//
// Created by aisha on 20/11/2026.
//
#pragma once
#ifndef RIELESMUERTOS_PERSONAJEBASE_H
#define RIELESMUERTOS_PERSONAJEBASE_H


#include <string>
using namespace std;

class PersonajeBase {
protected:
    string nombre;
    int vida;
    int dano;
    public:
    PersonajeBase(string nombre,int vida);
    string getNombre();
    int getVida();
    void setVida(int vida);
    void setNombre(string nombre);
    void recibirDano(int cantidad);
    bool estaVivo();
    virtual int atacar();
};
#endif //RIELESMUERTOS_PERSONAJEBASE_H