//
// Created by aisha on 20/11/2026.
//

#ifndef RIELESMUERTOS_ARMA_H
#define RIELESMUERTOS_ARMA_H



#include "Objeto.h"
#include <vector>
#include <iostream>
#include <string>
using namespace std;
class Arma : public Objeto {
private:
    int dano;
    int municion;
    int durabilidad;
    int capacidadMunicion;
    bool usaMunicion;
    string tipoMunicion;
public:
    Arma(string nombre,double precio ,int cantidad, double precioVenta, bool acumulable,int dano,int durabilidad,int municion,int capacidadMunicion, bool usaMunicion,string tipoMunicion);
    ~Arma();
    int atacar();
    int getDano();
    string getTipoMunicion();
    bool usar() ;
    bool recargar(int cantidad, string tipoMunicion);
    int getDurabilidad();
    int getMunicion();
    void perderDurabilidad(int cantidad);
    bool esArma() override;
    int getCapacidadMunicion();
    bool getUsaMunicion();
};
#endif //RIELESMUERTOS_ARMA_H