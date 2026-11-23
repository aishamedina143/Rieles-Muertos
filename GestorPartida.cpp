//
// Created by aisha on 21/11/2026.
//
#include "GestorPartida.h"
#include "Arma.h"
#include "Armadura.h"

GestorPartida::GestorPartida() {
    nombreArchivo = "partida.txt";
}
void GestorPartida::guardarPartida(Personaje& personaje, Tren& tren) {
    ofstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cout << "No se pudo guardar la partida." << endl;
        return;
    }

    archivo << personaje.getNombre() << endl;
    archivo << personaje.getVida() << endl;
    archivo << personaje.getDinero() << endl;
    archivo << personaje.getNivel() << endl;
    archivo << personaje.getExperiencia() << endl;

    archivo << tren.getDistancia() << endl;
    archivo << tren.getCombustible() << endl;
    archivo << tren.getVelocidad() << endl;
    archivo << tren.getUbicacion() << endl;
    archivo << tren.getTiempoTranscurrido() << endl;
    archivo << tren.getDia() << endl;
    archivo << tren.getHora() << endl;
    archivo << tren.getEsDeNoche() << endl;
    archivo << tren.getEstacionActual() << endl;

    vector<Objeto*> inventario = personaje.getInventario();
    archivo << inventario.size() << endl;
    for (Objeto* objeto : inventario) {
        archivo << objeto->getNombre() << endl;
        archivo << objeto->getPrecio() << endl;
        archivo << objeto->getCantidad() << endl;
        archivo << objeto->getPrecioVenta() << endl;
        archivo << objeto->esAcumulable() << endl;
        if (objeto->esArma()) {
            archivo << "ARMA" << endl;

            Arma* arma = (Arma*) objeto;

            archivo << arma->getDano() << endl;
            archivo << arma->getMunicion() << endl;
            archivo << arma->getDurabilidad() << endl;
            archivo << arma->getCapacidadMunicion() << endl;
            archivo << arma->getUsaMunicion() << endl;
            archivo << arma->getTipoMunicion() << endl;
        }
        else if (objeto->esArmadura()) {
            archivo << "ARMADURA" << endl;

            Armadura* armadura = (Armadura*) objeto;

            archivo << armadura->getDefensa() << endl;
            archivo << armadura->getDurabilidad() << endl;
        }

        else {
            archivo << "OBJETO" << endl;
        }
    }

    vector<Objeto*> mejoras = tren.getMejoras();

    archivo << mejoras.size() << endl;

    for (Objeto* mejora : mejoras) {
        archivo << mejora->getNombre() << endl;
        archivo << mejora->getPrecio() << endl;
        archivo << mejora->getCantidad() << endl;
        archivo << mejora->getPrecioVenta() << endl;
        archivo << mejora->esAcumulable() << endl;
    }
    archivo.close();
    cout << "Partida guardada correctamente." << endl;
}
bool GestorPartida::cargarPartida(Personaje& personaje, Tren& tren) {
    ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cout << "No se encontro ninguna partida guardada." << endl;
        return false;
    }
    tren.limpiarMejoras();

    string nombre;
    int vida;
    double dinero;
    int nivel;
    int experiencia;
    double distancia;
    double combustible;
    double velocidad;
    string ubicacion;
    double tiempo;
    int dia;
    int hora;
    bool esDeNoche;
    int estacion;

    getline(archivo, nombre);
    archivo >> vida;
    archivo >> dinero;
    archivo >> nivel;
    archivo >> experiencia;
    archivo >> distancia;
    archivo >> combustible;
    archivo >> velocidad;
    archivo.ignore();
    getline(archivo, ubicacion);
    archivo >> tiempo;
    archivo >> dia;
    archivo >> hora;
    archivo >> esDeNoche;
    archivo >> estacion;
    int cantidadObjetos;
    archivo >> cantidadObjetos;
    personaje.limpiarInventario();
    for (int i = 0; i < cantidadObjetos; i++) {
        string nombreObjeto;
        double precio;
        int cantidad;
        double precioVenta;
        bool acumulable;

        archivo >> ws;
        getline(archivo, nombreObjeto);
        archivo >> precio;
        archivo >> cantidad;
        archivo >> precioVenta;
        archivo >> acumulable;

        string tipoObjeto;
        archivo >> tipoObjeto;
        if (tipoObjeto == "ARMA") {
            int dano;
            int municion;
            int durabilidad;
            int capacidadMunicion;
            bool usaMunicion;
            string tipoMunicion;

            archivo >> dano;
            archivo >> municion;
            archivo >> durabilidad;
            archivo >> capacidadMunicion;
            archivo >> usaMunicion;
            archivo >> ws;
            getline(archivo, tipoMunicion);
            Arma* arma = new Arma(
            nombreObjeto,
            precio,
            cantidad,
            precioVenta,
            acumulable,
            dano,
            durabilidad,
            municion,
            capacidadMunicion,
            usaMunicion,
            tipoMunicion
        );

            personaje.recogerObjeto(arma);
        }
        else if (tipoObjeto == "ARMADURA") {
            int defensa;
            int durabilidad;

            archivo >> defensa;
            archivo >> durabilidad;
            Armadura* armadura = new Armadura(
            nombreObjeto,
            precio,
            cantidad,
            precioVenta,
            acumulable,
            defensa,
            durabilidad
        );

            personaje.recogerObjeto(armadura);
        }
        else if (tipoObjeto == "OBJETO") {
            Objeto* objeto = new Objeto(
            nombreObjeto,
            precio,
            cantidad,
            precioVenta,
            acumulable
        );

            personaje.recogerObjeto(objeto);
        }
    }
    int cantidadMejoras;
    archivo >> cantidadMejoras;
    if (archivo.fail() || cantidadMejoras < 0 || cantidadMejoras > 50) {
        cout << "Error: cantidad de mejoras no valida." << endl;
        archivo.close();
        return false;
    }
    cout << "Mejoras encontradas en el archivo: "<< cantidadMejoras << endl;

    for (int i = 0; i < cantidadMejoras; i++) {

        string nombreMejora;
        double precio;
        int cantidad;
        double precioVenta;
        bool acumulable;

        archivo >> ws;
        getline(archivo, nombreMejora);

        archivo >> precio;
        archivo >> cantidad;
        archivo >> precioVenta;
        archivo >> acumulable;

        Objeto* mejora = new Objeto(
            nombreMejora,
            precio,
            cantidad,
            precioVenta,
            acumulable
        );
        cout << "Cargando mejora: " << nombreMejora << endl;
        tren.agregarMejora(mejora);
    }

    if (archivo.fail()) {
        cout << "El archivo de partida esta incompleto o danado." << endl;
        archivo.close();
        return false;
    }

    personaje.setNombre(nombre);
    personaje.setVida(vida);
    personaje.setDinero(dinero);
    personaje.setNivel(nivel);
    personaje.setExperiencia(experiencia);

    tren.setDistancia(distancia);
    tren.setCombustible(combustible);
    tren.setVelocidad(velocidad);
    tren.setUbicacion(ubicacion);
    tren.setTiempoTranscurrido(tiempo);
    tren.setDia(dia);
    tren.setHora(hora);
    tren.setEsDeNoche(esDeNoche);
    tren.setEstacionActual(estacion);

    archivo.close();

    cout << "Partida cargada correctamente." << endl;
    return true;
}