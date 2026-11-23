//
// Created by aisha on 20/11/2026.
//

#ifndef RIELESMUERTOS_JEFEFINAL_H
#define RIELESMUERTOS_JEFEFINAL_H
#include "Villano.h"
class JefeFinal : public Villano {
private:
    string habilidadEspecial;
    int danoEspecial;
public:
    JefeFinal(string nombre,int vida,string tipo,int dano,double recompensa,string habilidadEspecial, int danoEspecial);
    int usarHabilidadEspecial();
    int atacar() override;
};

#endif //RIELESMUERTOS_JEFEFINAL_H
