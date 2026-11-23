//
// Created by aisha on 20/11/2026.
//
#pragma once
#ifndef RIELESMUERTOS_PERSONAJE_H
#define RIELESMUERTOS_PERSONAJE_H


#include <iostream>
#include "PersonajeBase.h"
#include "Objeto.h"
#include "Villano.h"
#include "Arma.h"
#include <string>
#include <vector>
using namespace std;
class Personaje : public PersonajeBase {
private:
    double dinero;
    int nivel;
    int experiencia;
    int experienciaNecesaria;
    vector <Objeto*> inventario;
    Arma* armaEquipada;
public:
    Personaje(string nombre, int vida);
    ~Personaje();
    bool comprar(Objeto* objeto);
    bool vender(Objeto* objeto);
    bool equiparArma(Arma& arma);
    void curarse(int cantidad);
    bool recogerObjeto(Objeto* objeto);
    bool usarObjeto(Objeto& objeto);
    void ganarExperiencia(int cantidad);
    void subirNivel();
    bool comprarMunicion(int cantidad, string tipoMunicion,double precio);
    void mejorarEstadisticas();
    int atacar(Villano& enemigo);
    double getDinero();
    void mostrarInventario();
    void mostrarArmas();
    bool equiparArmaPorPosicion(int posicion);
    int getNivel();
    int getExperiencia();
    void setDinero(double dinero);
    void setNivel(int nivel);
    void limpiarInventario();
    void setExperiencia(int experiencia);
    vector<Objeto*> getInventario();
    string getArmaEquipada();
    int getMunicionArma();
    void mostrarObjetos();
    bool puedeAtacar();
    Objeto* retirarObjeto(string nombre);
    bool consumirObjeto(Objeto& objeto, int cantidad);
};
#endif //RIELESMUERTOS_PERSONAJE_H