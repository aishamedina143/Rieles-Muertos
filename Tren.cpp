//
// Created by aisha on 21/11/2026.
//

#include "Tren.h"
#include <cstdlib>
#include <ctime>
void combatirVillano(Personaje& jugador, Villano& villano, Tren& tren);
Tren::Tren() {
    combustible = 0;
    velocidad = 10;
    distancia = 0;
    dia = 1;
    hora = 8;
    esDeNoche = false;
    tiempoTranscurrido = 0;
    estacionActual = 1;
    ubicacion = "Estacion Polvorienta";
    enMovimiento = false;
}
Tren::~Tren() {
    for (int i = 0; i < mejoras.size(); i++) {
        delete mejoras[i];
    }
}
void Tren::avanzar(double horas) {
    if (combustible <= 0) {
        cout << "No tienes carbon. El tren no puede avanzar." << endl;
        enMovimiento = false;
        return;
    }

    if (horas <= 0 || velocidad <= 0) {
        return;
    }

    enMovimiento = true;

    double distanciaRecorrida = velocidad * horas;

    if (distanciaRecorrida > combustible) {
        distanciaRecorrida = combustible;
    }

    distancia += distanciaRecorrida;
    tiempoTranscurrido += distanciaRecorrida / velocidad;

    consumirCombustible(distanciaRecorrida);

    cout << "El tren ha recorrido " << distanciaRecorrida << " km." << endl;
    cout << "Distancia total: " << distancia << " km." << endl;
}
void Tren::viajarSiguienteEstacion(Personaje& personaje) {

    if (estacionActual >= 5) {
        cout << "Ya has llegado a la estacion final." << endl;
        return;
    }

    if (combustible < 12) {
        cout << "No tienes suficiente carbon para llegar a la siguiente estacion." << endl;
        cout << "Necesitas 12 km de combustible." << endl;
        return;
    }

    cout << "\nEl tren comienza su viaje..." << endl;

    double horas = 12.0 / velocidad;

    avanzar(horas);
    actualizarTiempo();
    mostrarTiempo();
    encuentroAleatorio(personaje);
    detener();

    estacionActual++;

    string estaciones[5] = {
        "Estacion Polvorienta",
        "Estacion del Desierto",
        "Estacion Mina Sombria",
        "Estacion del Ultimo Refugio",
        "Estacion Terminal"
    };

    ubicacion = estaciones[estacionActual - 1];

    cout << "\nHas llegado a una nueva estacion!" << endl;
    cout << "Ubicacion: " << ubicacion << endl;
    cout << "Estacion: " << estacionActual << " de 5" << endl;

    if (estacionActual == 5) {
        cout << "\nHas llegado a la estacion del JEFE FINAL!" << endl;
    }
    buscarRecursos(personaje);

}

void Tren::detener() {
    enMovimiento = false;
    cout << "El tren se ha detenido." << endl;
}
void Tren::consumirCombustible(double cantidad) {
    if (cantidad <= 0) {
        return;
    }

    combustible -= cantidad;

    if (combustible <= 0) {
        combustible = 0;
        detener();
    }
}
void Tren::cargarCombustible(double cantidad) {
    if (cantidad <= 0) {
        return;
    }

    combustible += cantidad * 7;

    cout << "Has cargado carbon. Combustible disponible: "
         << combustible << " km." << endl;
}
void Tren::agregarMejora(Objeto* objeto) {
    if (objeto == nullptr) {
        return;
    }
    mejoras.push_back(objeto);

    cout << "Has agregado " << objeto->getNombre() << " al tren." << endl;
}
void Tren::recogerCarbon() {
    combustible += 7;

    cout << "Has encontrado una unidad de carbon." << endl;
    cout << "Combustible disponible: " << combustible << " km." << endl;
}
double Tren::getDistancia() {
    return distancia;
}

double Tren::getCombustible() {
    return combustible;
}

double Tren::getVelocidad() {
    return velocidad;
}

string Tren::getUbicacion() {
    return ubicacion;
}

bool Tren::getEnMovimiento() {
    return enMovimiento;
}
void Tren::setDistancia(double distancia) {
    this->distancia = distancia;
}

void Tren::setCombustible(double combustible) {
    this->combustible = combustible;
}

void Tren::setVelocidad(double velocidad) {
    this->velocidad = velocidad;
}

void Tren::setUbicacion(string ubicacion) {
    this->ubicacion = ubicacion;
}

void Tren::setTiempoTranscurrido(double tiempo) {
    this->tiempoTranscurrido = tiempo;
}

double Tren::getTiempoTranscurrido() {
    return tiempoTranscurrido;
}
void Tren::setDia(int dia) {
    this->dia = dia;
}

void Tren::setHora(int hora) {
    this->hora = hora;
}

void Tren::setEsDeNoche(bool noche) {
    this->esDeNoche = noche;
}

void Tren::setEstacionActual(int estacion) {
    this->estacionActual = estacion;
}

int Tren::getDia() {
    return dia;
}

int Tren::getHora() {
    return hora;
}

bool Tren::getEsDeNoche() {
    return esDeNoche;
}

int Tren::getEstacionActual() {
    return estacionActual;
}
void Tren::limpiarMejoras() {
    for (Objeto* mejora : mejoras) {
        delete mejora;
    }

    mejoras.clear();
}

vector<Objeto*> Tren::getMejoras() {
    return mejoras;
}
void Tren::buscarRecursos(Personaje& personaje) {

    int recurso = rand() % 4;

    Objeto* objeto = nullptr;

    if (recurso == 0) {
        objeto = new Objeto("Lingote de oro", 0, 1, 25, false);
    }
    else if (recurso == 1) {
        objeto = new Objeto("Lingote de plata", 0, 1, 15, false);
    }
    else if (recurso == 2) {
        objeto = new Objeto("Cuadro antiguo", 0, 1, 20, false);
    }
    else {
        objeto = new Objeto("Reliquia de vampiro", 0, 1, 35, false);
    }

    personaje.recogerObjeto(objeto);

    cout << "\nHas encontrado recursos durante el viaje!" << endl;
    cout << "Objeto encontrado: " << objeto->getNombre() << endl;
}
bool Tren::usarCarbon(Personaje& personaje) {

    vector<Objeto*> inventario = personaje.getInventario();

    for (int i = 0; i < inventario.size(); i++) {

        if (inventario[i] != nullptr &&
            inventario[i]->getNombre() == "Carbon") {

            if (inventario[i]->getCantidad() > 0) {

                if (personaje.consumirObjeto(*inventario[i], 1)) {

                    cargarCombustible(1);

                    cout << "Has utilizado una unidad de carbon." << endl;
                    cout << "Combustible actual: " << combustible << endl;

                    return true;
                }
            }
            }
    }

    cout << "No tienes carbon en tu inventario." << endl;
    return false;
}

void Tren::encuentroAleatorio(Personaje& personaje) {

    int enemigoElegido = rand() % 4;

    Villano enemigo("Zombie", 60, "Zombie", 10, 15);

    if (enemigoElegido == 0) {
        enemigo = Villano("Zombie", 60, "Zombie", 10, 15);
    }
    else if (enemigoElegido == 1) {
        enemigo = Villano("Vampiro", 100, "Vampiro", 15, 30);
    }
    else if (enemigoElegido == 2) {
        enemigo = Villano("Hombre lobo", 120, "Hombre lobo", 20, 40);
    }
    else {
        enemigo = Villano("Forajido", 80, "Forajido", 12, 25);
    }

    cout << "\nATENCION! UN ENEMIGO HA APARECIDO DURANTE EL VIAJE!" << endl;

    if (usarTrampa()) {
        int vidaReducida = enemigo.getVida() * 75 / 100;
        enemigo.setVida(vidaReducida);
        cout << "La trampa ha debilitado al enemigo!" << endl;
        cout << "Vida inicial del enemigo: " << enemigo.getVida() << endl;
    }

    combatirVillano(personaje, enemigo, *this);
}
void Tren::instalarMejora(Personaje& personaje) {

    cout << "\n========== INSTALAR MEJORAS ==========" << endl;

    cout << "\nTu inventario:" << endl;
    personaje.mostrarObjetos();

    vector<Objeto*> inventario = personaje.getInventario();

    int opcion;

    cout << "\nEscribe el numero del objeto que deseas instalar: ";
    cin >> opcion;

    if (opcion < 1 || opcion > inventario.size()) {
        cout << "Numero no valido." << endl;
        return;
    }

    Objeto* objeto = inventario[opcion - 1];

    string nombre = objeto->getNombre();

    if (nombre != "Periodico" && nombre != "Alambre de puas" && nombre != "Trampa para osos") {

        cout << "Ese objeto no se puede instalar." << endl;
        return;
        }

    objeto = personaje.retirarObjeto(nombre);

    if (objeto == nullptr) {
        cout << "No se pudo instalar la mejora." << endl;
        return;
    }

    agregarMejora(objeto);

    cout << "\n¡Mejora instalada correctamente!" << endl;
}
bool Tren::tieneMejora(string nombre) {
    for (int i = 0; i < mejoras.size(); i++) {
        if (mejoras[i]->getNombre() == nombre) {
            return true;
        }
    }

    return false;
}
bool Tren::usarTrampa() {
    for (int i = 0; i < mejoras.size(); i++) {
        if (mejoras[i]->getNombre() == "Trampa para osos") {
            delete mejoras[i];
            mejoras.erase(mejoras.begin() + i);

            cout << "\nHas preparado una trampa para el enemigo!" << endl;
            return true;
        }
    }

    return false;
}
void Tren::leerPeriodico() {
    bool encontrado = false;

    for (int i = 0; i < mejoras.size(); i++) {
        if (mejoras[i]->getNombre() == "Periodico") {

            encontrado = true;

            cout << "\n========== NOTICIAS DEL OESTE ==========" << endl;

            int noticia = rand() % 4;

            if (noticia == 0) {
                cout << "Se han visto vampiros cerca de las vias." << endl;
            }
            else if (noticia == 1) {
                cout << "Los habitantes advierten sobre hombres lobo." << endl;
            }
            else if (noticia == 2) {
                cout << "Se informa de movimientos sospechosos en el desierto." << endl;
            }
            else {
                cout << "Los viajeros recomiendan prepararse antes de continuar." << endl;
            }
            delete mejoras[i];
            mejoras.erase(mejoras.begin() + i);

            cout << "\nHas utilizado el periodico." << endl;
            break;
        }
    }

    if (!encontrado) {
        cout << "\nNo tienes ningun periodico instalado." << endl;
    }
}
void Tren::actualizarTiempo() {
    hora += 2;

    if (hora >= 24) {
        hora -= 24;
        dia++;
    }

    esDeNoche = (hora >= 20 || hora < 6);
}
void Tren::mostrarTiempo() {
    cout << "\nDia: " << dia << endl;
    cout << "Hora: " << hora << ":00" << endl;

    if (esDeNoche) {
        cout << "Momento del dia: NOCHE" << endl;
    }
    else {
        cout << "Momento del dia: DIA" << endl;
    }
}