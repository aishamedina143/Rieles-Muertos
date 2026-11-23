//
// Created by aisha on 21/11/2026.
//

#ifndef RIELESMUERTOS_TREN_H
#define RIELESMUERTOS_TREN_H
#include <iostream>
#include <string>
#include "Villano.h"
#include <vector>
#include "Objeto.h"
#include "Personaje.h"

using namespace std;

class Tren {
private:
    double combustible;
    double velocidad;
    double distancia;
    int dia;
    int hora;
    bool esDeNoche;
    double tiempoTranscurrido;
    string ubicacion;
    int estacionActual;
    bool enMovimiento;
    vector<Objeto*> mejoras;

public:
    Tren();
    ~Tren();

    void avanzar(double horas);
    void detener();
    void consumirCombustible(double cantidad);
    void cargarCombustible(double cantidad);
    void viajarSiguienteEstacion(Personaje& personaje);
    void agregarMejora(Objeto* objeto);
    void recogerCarbon();
    void buscarRecursos(Personaje& personaje);
    double getDistancia();
    double getCombustible();
    double getVelocidad();
    string getUbicacion();
    bool getEnMovimiento();
    void setDistancia(double distancia);
    void setCombustible(double combustible);
    void setVelocidad(double velocidad);
    void setUbicacion(string ubicacion);
    void setTiempoTranscurrido(double tiempo);
    void encuentroAleatorio(Personaje& personaje);
    double getTiempoTranscurrido();
    void instalarMejora(Personaje& personaje);
    bool tieneMejora(string nombre);
    bool usarTrampa();
    void leerPeriodico();
    void actualizarTiempo();
    void mostrarTiempo();
    bool usarCarbon(Personaje& personaje);
    void setDia(int dia);
    void setHora(int hora);
    void setEsDeNoche(bool noche);
    void setEstacionActual(int estacion);
    int getDia();
    int getHora();
    bool getEsDeNoche();
    int getEstacionActual();
    void limpiarMejoras();
    vector<Objeto*> getMejoras();
};
#endif //RIELESMUERTOS_TREN_H
