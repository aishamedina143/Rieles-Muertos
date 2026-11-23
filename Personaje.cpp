//
// Created by aisha on 20/11/2026.
//
#include "Personaje.h"
#include "PersonajeBase.h"
#include <vector>
#include <string>
using namespace std;

Personaje::Personaje(string nombre,int vida) : PersonajeBase(nombre,vida) {
    dinero = 20;
    nivel = 1;
    experiencia = 0;
    experienciaNecesaria = 100;
    armaEquipada = nullptr;

}
Personaje::~Personaje() {
    for (int i = 0; i < inventario.size(); i++) {
        delete inventario[i];
    }
}
double Personaje::getDinero() {
    return dinero;
}
int Personaje::getNivel() {
    return nivel;
}
int Personaje::getExperiencia() {
    return experiencia;
}
void Personaje:: ganarExperiencia(int cantidad) {
    if (cantidad > 0) {
        experiencia += cantidad;
    }
}

void Personaje:: subirNivel() {
    while (experiencia >= experienciaNecesaria) {
        nivel++;
        experiencia -= experienciaNecesaria;
        experienciaNecesaria += 50;
        mejorarEstadisticas();
    }
}
void Personaje::mejorarEstadisticas() {
    vida += 10;
    dano += 2;
}

bool Personaje::comprar(Objeto* objeto) {

        if (objeto == nullptr) {
            return false;
        }

        if (dinero < objeto->getPrecio()) {
            return false;
        }

        if (objeto->esAcumulable()) {
            for (int i = 0; i < inventario.size(); i++) {
                if (inventario[i]->getNombre() == objeto->getNombre()
                    && inventario[i]->esAcumulable()) {

                    dinero -= objeto->getPrecio();
                    inventario[i]->aumentarCantidad(objeto->getCantidad());

                    delete objeto;
                    return true;
                    }
            }
        }

        dinero -= objeto->getPrecio();
        inventario.push_back(objeto);
        return true;
    }
bool Personaje::vender(Objeto* objeto) {

        if (objeto == nullptr) {
            return false;
        }

        for (int i = 0; i < inventario.size(); i++) {
            if (inventario[i] == objeto) {

                if (armaEquipada == objeto) {
                    armaEquipada = nullptr;
                }

                dinero += inventario[i]->getPrecioVenta();
                inventario.erase(inventario.begin() + i);
                return true;
            }
        }

        return false;

}
bool Personaje::equiparArma(Arma& arma) {
    for (int i = 0; i < inventario.size(); i++) {
        if (inventario[i] == &arma) {
            armaEquipada = &arma;
            return true;
        }
    }

    return false;
}

int Personaje::atacar(Villano &enemigo) {
    if (armaEquipada==nullptr) {
        return 0;
    }
    else {
        int ataque = armaEquipada->atacar();
        enemigo.recibirDano(ataque);
        return ataque;
    }
}
bool Personaje::recogerObjeto(Objeto* objeto) {
    if (objeto == nullptr) {
        return false;
    }

    for (int i = 0; i < inventario.size(); i++) {
        if (inventario[i] == objeto) {
            return false;
        }
    }

    inventario.push_back(objeto);
    return true;
}

bool Personaje::usarObjeto(Objeto& objeto) {

    for (int i = 0; i < inventario.size(); i++) {

        if (inventario[i] == &objeto) {

            if (inventario[i]->usar(*this)) {

                inventario[i]->disminuirCantidad(1);

                if (inventario[i]->getCantidad() == 0) {

                    if (armaEquipada == inventario[i]) {
                        armaEquipada = nullptr;
                    }

                    delete inventario[i];
                    inventario.erase(inventario.begin() + i);
                }

                return true;
            }

            return false;
        }
    }

    return false;
}

bool Personaje::comprarMunicion(int cantidad, string tipoMunicion, double precio) {
    if (armaEquipada == nullptr) {
        return false;
    }

    if (precio <= 0 || dinero < precio) {
        return false;
    }

    if (armaEquipada->recargar(cantidad, tipoMunicion)) {
        dinero -= precio;
        return true;
    }

    return false;
}
void Personaje::curarse(int cantidad) {

    if (cantidad <= 0) {
        return;
    }

    vida += cantidad;

    if (vida > 100) {
        vida = 100;
    }
}
void Personaje::mostrarInventario() {
    int opcion = -1;

    do {
        cout << "\n========== INVENTARIO ==========" << endl;
        cout << "1. Ver objetos" << endl;
        cout << "2. Equipar arma" << endl;
        cout << "0. Volver" << endl;
        cout << "Elige una opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            if (inventario.empty()) {
                cout << "Tu inventario esta vacio." << endl;
            } else {
                for (int i = 0; i < inventario.size(); i++) {
                    cout << i + 1 << ". " << inventario[i]->getNombre()
                         << " - Cantidad: " << inventario[i]->getCantidad() << endl;
                }
            }
        }
        else if (opcion == 2) {

            int numeroArmas = 0;

            for (int i = 0; i < inventario.size(); i++) {
                if (inventario[i]->esArma()) {
                    numeroArmas++;
                }
            }

            if (numeroArmas == 0) {
                cout << "\nNo tienes armas en tu inventario." << endl;
            }
            else {
                mostrarArmas();

                int armaElegida;

                cout << "Escribe el numero del arma que deseas equipar: ";
                cin >> armaElegida;

                if (equiparArmaPorPosicion(armaElegida - 1)) {
                    cout << "Arma equipada correctamente." << endl;
                }
                else {
                    cout << "No se pudo equipar esa arma." << endl;
                }
            }
        }
        else if (opcion != 0) {
            cout << "Opcion no valida." << endl;
        }

    } while (opcion != 0);
}
void Personaje::mostrarObjetos() {

    cout << "\n========== TUS OBJETOS ==========" << endl;

    if (inventario.empty()) {
        cout << "Tu inventario esta vacio." << endl;
        return;
    }

    for (int i = 0; i < inventario.size(); i++) {

        cout << i + 1 << ". "
             << inventario[i]->getNombre()
             << " - Cantidad: "
             << inventario[i]->getCantidad()
             << endl;
    }
}
void Personaje::mostrarArmas() {

    cout << "\n========== TUS ARMAS ==========" << endl;

    int numeroArmas = 0;

    for (int i = 0; i < inventario.size(); i++) {

        if (inventario[i]->esArma()) {

            cout << i + 1 << ". "
                 << inventario[i]->getNombre() << endl;

            numeroArmas++;
        }
    }

    if (numeroArmas == 0) {
        cout << "No tienes armas en tu inventario." << endl;
    }
}

bool Personaje::equiparArmaPorPosicion(int posicion) {

    if (posicion < 0 || posicion >= inventario.size()) {
        return false;
    }

    if (!inventario[posicion]->esArma()) {
        return false;
    }

    armaEquipada = (Arma*) inventario[posicion];

    return true;
}
string Personaje::getArmaEquipada() {
    if (armaEquipada == nullptr) {
        return "Ninguna";
    }

    return armaEquipada->getNombre();
}
int Personaje::getMunicionArma() {
    if (armaEquipada == nullptr) {
        return 0;
    }

    return armaEquipada->getMunicion();
}
void Personaje::setDinero(double dinero) {
    this->dinero = dinero;
}

void Personaje::setNivel(int nivel) {
    this->nivel = nivel;
}

void Personaje::setExperiencia(int experiencia) {
    this->experiencia = experiencia;
}
vector<Objeto*> Personaje::getInventario() {
    return inventario;
}
void Personaje::limpiarInventario() {
    for (Objeto* objeto : inventario) {
        delete objeto;
    }

    inventario.clear();
    armaEquipada = nullptr;
}
bool Personaje::consumirObjeto(Objeto& objeto, int cantidad) {

    if (cantidad <= 0) {
        return false;
    }

    for (int i = 0; i < inventario.size(); i++) {

        if (inventario[i] == &objeto) {

            if (inventario[i]->getCantidad() < cantidad) {
                return false;
            }

            inventario[i]->disminuirCantidad(cantidad);

            if (inventario[i]->getCantidad() == 0) {
                delete inventario[i];
                inventario.erase(inventario.begin() + i);
            }

            return true;
        }
    }

    return false;
}
bool Personaje::puedeAtacar() {
    if (armaEquipada == nullptr) {
        return false;
    }

    if (armaEquipada->getUsaMunicion() && armaEquipada->getMunicion() <= 0) {
        return false;
    }

    return true;
}
Objeto* Personaje::retirarObjeto(string nombre) {
    for (int i = 0; i < inventario.size(); i++) {
        if (inventario[i] != nullptr && inventario[i]->getNombre() == nombre) {

            Objeto* objeto = inventario[i];
            inventario.erase(inventario.begin() + i);

            return objeto;
            }
    }

    return nullptr;
}