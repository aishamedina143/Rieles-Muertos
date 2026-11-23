
#include <iostream>
#include "Tienda.h"
#include "Personaje.h"
#include "JefeFinal.h"
#include "Tren.h"
#include "GestorPartida.h"
#include "Villano.h"
#include <cstdlib>
#include <filesystem>
#include <ctime>
using namespace std;

void combatirJefe(Personaje& jugador, JefeFinal& jefe) {
    int turno = 1;

    while (jugador.estaVivo() && jefe.estaVivo()) {

        if (!jugador.puedeAtacar()) {
            cout << "\nNo tienes arma o municion suficiente." << endl;
            break;
        }
        cout << "\n========== TURNO " << turno << " ==========" << endl;
        cout << "\nVida del jugador: " << jugador.getVida() << endl;
        cout << "Vida del jefe: " << jefe.getVida() << endl;
        cout << "\nEs tu turno de atacar" << endl;

        if (jugador.puedeAtacar()) {
            int danoJugador = jugador.atacar(jefe);
            cout << "Has causado " << danoJugador << " puntos de dano." << endl;
            cout << "Municion restante: " << jugador.getMunicionArma() << endl;
        }
        if (jefe.estaVivo()) {

            cout << "\nEl jefe se prepara para atacar" << endl;
            int danoJefe;
            if (turno % 3 == 0) {
                danoJefe = jefe.usarHabilidadEspecial();
            }
            else {
                danoJefe = jefe.atacar();
                cout << "El jefe realiza un ataque normal." << endl;
                cout << "Inflige " << danoJefe << " puntos de dano." << endl;
            }

            jugador.recibirDano(danoJefe);

            cout << "Vida restante del jugador: "<< jugador.getVida() << endl;
        }
        turno++;
    }
    if (!jefe.estaVivo()) {

        cout << "\n================================" << endl;
        cout << "FELICIDADES, HAS DERROTADO AL JEFE!" << endl;
        cout << "================================" << endl;

        cout << "Has ganado la recompensa de "<< jefe.getRecompensa() << " monedas." << endl;

        jugador.setDinero(
            jugador.getDinero() + jefe.getRecompensa()
        );

        jugador.ganarExperiencia(100);
        jugador.subirNivel();

    }
    else if (!jugador.estaVivo()) {
        cout << "\nHAS SIDO DERROTADO..." << endl;
    }
    else {
        cout << "\nNo has podido terminar el combate." << endl;
    }
}
void combatirVillano(Personaje& jugador, Villano& villano, Tren& tren) {
    int turno = 1;

    villano.aparecer();

    while (jugador.estaVivo() && villano.estaVivo()) {

        if (!jugador.puedeAtacar()) {
            cout << "\nNo tienes arma o municion suficiente." << endl;
            cout << "El combate ha sido interrumpido." << endl;
            break;
        }

        cout << "\n========== TURNO " << turno << " ==========" << endl;
        cout << "Vida del jugador: " << jugador.getVida() << endl;
        cout << "Vida del enemigo: " << villano.getVida() << endl;

        int danoJugador = jugador.atacar(villano);

        cout << "\nHas causado " << danoJugador << " puntos de dano." << endl;
        cout << "Municion restante: " << jugador.getMunicionArma() << endl;

        if (villano.estaVivo()) {
            int danoVillano = villano.atacar();
            if (tren.tieneMejora("Alambre de puas")) {
                danoVillano = danoVillano / 2;
                cout << "\n¡El alambre de puas ha reducido el dano!" << endl;
            }

            jugador.recibirDano(danoVillano);

            cout << "\nEl villano te ha causado "
                 << danoVillano << " puntos de dano." << endl;

            cout << "Vida restante: " << jugador.getVida() << endl;
        }

        turno++;
    }

    if (!villano.estaVivo()) {
        cout << "\n¡HAS DERROTADO AL VILLANO!" << endl;

        cout << "Has ganado "
             << villano.getRecompensa() << " monedas." << endl;

        jugador.setDinero(
            jugador.getDinero() + villano.getRecompensa()
        );

        jugador.ganarExperiencia(25);
        jugador.subirNivel();
    }
    else if (!jugador.estaVivo()) {
        cout << "\nHAS SIDO DERROTADO..." << endl;
    }
    else {
        cout << "\nEl combate ha sido interrumpido." << endl;
    }
}
int main() {
    srand(time(0));

    string nombre;
    int opcionInicio;

    cout << "\n========== RIELES MUERTOS ==========" << endl;
    cout << "1. Nueva partida" << endl;
    cout << "2. Cargar partida" << endl;
    cout << "0. Salir del juego" << endl;
    cout << "Elige una opcion: ";
    cin >> opcionInicio;

    if (opcionInicio == 0) {
        cout << "\nHasta pronto, viajero." << endl;
        return 0;
    }

    if (opcionInicio != 1 && opcionInicio != 2) {
        cout << "\nOpcion no valida." << endl;
        return 0;
    }

    if (opcionInicio == 1) {
        cout << "Como te llamas, viajero? ";
        cin >> nombre;
    } else {
        nombre = "Viajero";
    }

    Personaje jugador(nombre, 100);
    Objeto* lingote = new Objeto("Lingote de oro", 0, 1, 25, false);
    jugador.recogerObjeto(lingote);

    Tienda tiendaGeneral("Tienda General");
    Tienda armeria("Armeria");
    Tienda doctor("Doctor");
    Tren tren;
    GestorPartida gestor;
    cout << "Carpeta de ejecucion: "<< filesystem::current_path() << endl;
    if (opcionInicio == 2) {
        if (!gestor.cargarPartida(jugador, tren)) {
            cout << "\nNo se pudo cargar la partida. Cerrando el juego." << endl;
            return 0;
        }
    }
    JefeFinal jefe("El Forajido", 150, "Humano", 15, 100, "Disparo mortal", 25);
    bool jefeDerrotado = false;
    Tienda puestoComercio("Puesto de comercio");

    int respuesta = -1;

    do {

        cout << "\n========== MENU PRINCIPAL ==========" << endl;
        cout << "Ubicacion actual: " << tren.getUbicacion() << endl;
        cout << "1. Visitar tiendas de la estacion" << endl;
        cout << "2. Ver inventario" << endl;
        cout << "3. Ver informacion del jugador" << endl;
        cout << "4. Viajar en tren" << endl;
        cout << "5. Guardar partida" << endl;
        cout << "0. Salir del juego" << endl;

        cout << "Elige una opcion: ";
        cin >> respuesta;

        if (respuesta == 1) {

            int tiendaElegida = -1;

            while (tiendaElegida != 0) {

                cout << "\n========== PUEBLO DEL OESTE ==========" << endl;
                cout << "A que establecimiento deseas entrar?" << endl;
                cout << "1. Tienda General" << endl;
                cout << "2. Armeria" << endl;
                cout << "3. Doctor" << endl;
                cout << "4. Puesto de Comercio" << endl;
                cout << "0. Salir del pueblo" << endl;

                cout << "Elige una opcion: ";
                cin >> tiendaElegida;

                if (tiendaElegida == 1) {

                    int productoElegido = -1;

                    while (productoElegido != 0) {

                        cout << "\n--- TIENDA GENERAL ---" << endl;
                        tiendaGeneral.mostrarProductos();

                        cout << "0. Salir de la tienda" << endl;
                        cout << "Elige un producto: ";
                        cin >> productoElegido;

                        if (productoElegido > 0) {

                            Objeto* producto = tiendaGeneral.getProducto(productoElegido - 1);

                            if (producto != nullptr) {

                                string nombreProducto = producto->getNombre();

                                if (tiendaGeneral.venderProducto(producto, jugador)) {
                                    cout << "Has comprado " << nombreProducto << "!" << endl;
                                }
                                else {
                                    cout << "No tienes suficiente dinero." << endl;
                                }
                            }
                            else {
                                cout << "Opcion no valida." << endl;
                            }
                        }
                    }
                }

                else if (tiendaElegida == 2) {

                    int productoElegido = -1;

                    while (productoElegido != 0) {

                        cout << "\n--- ARMERIA ---" << endl;
                        armeria.mostrarProductos();

                        cout << "6. Comprar municion" << endl;
                        cout << "0. Salir de la armeria" << endl;

                        cout << "Elige una opcion: ";
                        cin >> productoElegido;

                        if (productoElegido >= 1 && productoElegido <= 5) {

                            Objeto* producto = armeria.getProducto(productoElegido - 1);

                            string nombreProducto = producto->getNombre();

                            if (armeria.venderProducto(producto, jugador)) {
                                cout << "Has comprado " << nombreProducto << "!" << endl;
                            }
                            else {
                                cout << "No tienes suficiente dinero." << endl;
                            }
                        }

                        else if (productoElegido == 6) {

                            int municionElegida = 1;
                            string tipoMunicion;

                            while (municionElegida != 0) {

                                cout << "\n========== MUNICION ==========" << endl;
                                cout << "1. Municion ligera - 15 monedas" << endl;
                                cout << "2. Municion mediana - 15 monedas" << endl;
                                cout << "3. Municion de escopeta - 15 monedas" << endl;
                                cout << "4. Municion de rifle - 15 monedas" << endl;
                                cout << "5. Municion de ametralladora - 30 monedas" << endl;
                                cout << "0. Volver a la armeria" << endl;

                                cout << "Elige la municion: ";
                                cin >> municionElegida;

                                if (municionElegida == 1) {
                                    tipoMunicion = "Ligera";
                                }
                                else if (municionElegida == 2) {
                                    tipoMunicion = "Mediana";
                                }
                                else if (municionElegida == 3) {
                                    tipoMunicion = "Escopeta";
                                }
                                else if (municionElegida == 4) {
                                    tipoMunicion = "Rifle";
                                }
                                else if (municionElegida == 5) {
                                    tipoMunicion = "Ametralladora";
                                }

                                if (municionElegida >= 1 && municionElegida <= 5) {

                                    if (armeria.venderMunicion(jugador, tipoMunicion)) {
                                        cout << "\nHas comprado municion!" << endl;
                                        cout << "Dinero restante: " << jugador.getDinero() << endl;
                                    }
                                    else {
                                        cout << "\nNo se pudo comprar la municion." << endl;
                                        cout << "Comprueba que tienes un arma equipada compatible y dinero suficiente." << endl;
                                    }
                                }
                                else if (municionElegida != 0) {
                                    cout << "Opcion no valida." << endl;
                                }
                            }
                        }

                        else if (productoElegido != 0) {
                            cout << "Opcion no valida." << endl;
                        }
                    }
                }

                else if (tiendaElegida == 3) {

                    int productoElegido = -1;

                    while (productoElegido != 0) {

                        cout << "\n--- DOCTOR ---" << endl;
                        doctor.mostrarProductos();

                        cout << "0. Volver al pueblo" << endl;
                        cout << "Elige un producto: ";
                        cin >> productoElegido;

                        if (productoElegido > 0) {

                            Objeto* producto = doctor.getProducto(productoElegido - 1);

                            if (producto != nullptr) {

                                string nombreProducto = producto->getNombre();

                                if (doctor.venderProducto(producto, jugador)) {
                                    cout << "Has comprado " << nombreProducto << "!" << endl;
                                }
                                else {
                                    cout << "No tienes suficiente dinero." << endl;
                                }
                            }
                            else {
                                cout << "Opcion no valida." << endl;
                            }
                        }
                    }
                }

                else if (tiendaElegida == 4) {

                    int opcionVenta = -1;

                    while (opcionVenta != 0) {

                        cout << "\n========== PUESTO DE COMERCIO ==========" << endl;
                        cout << "Dinero disponible: " << jugador.getDinero() << endl;
                        cout << "1. Vender objetos" << endl;
                        cout << "2. Ver inventario" << endl;
                        cout << "0. Salir del puesto" << endl;

                        cout << "Elige una opcion: ";
                        cin >> opcionVenta;

                        if (opcionVenta == 1) {

                            jugador.mostrarObjetos();

                            int objetoElegido;

                            cout << "\nEscribe el numero del objeto que deseas vender." << endl;
                            cout << "0. Cancelar venta" << endl;
                            cin >> objetoElegido;

                            if (objetoElegido > 0) {

                                vector<Objeto*> inventarioJugador = jugador.getInventario();

                                if (objetoElegido <= inventarioJugador.size()) {

                                    Objeto* objeto = inventarioJugador[objetoElegido - 1];

                                    if (puestoComercio.comprarObjeto(objeto, jugador)) {
                                        cout << "\nVenta realizada correctamente!" << endl;
                                        cout << "Dinero actual: " << jugador.getDinero() << " monedas." << endl;
                                    }
                                    else {
                                        cout << "\nEste objeto no se puede vender aqui." << endl;
                                    }
                                }
                                else {
                                    cout << "Numero de objeto no valido." << endl;
                                }
                            }
                        }

                        else if (opcionVenta == 2) {
                            jugador.mostrarInventario();
                        }

                        else if (opcionVenta != 0) {
                            cout << "Opcion no valida." << endl;
                        }
                    }
                }

                else if (tiendaElegida != 0) {
                    cout << "Opcion no valida." << endl;
                }
            }

            cout << "\nHas salido del pueblo." << endl;
        }

        else if (respuesta == 2) {
            jugador.mostrarInventario();
        }

        else if (respuesta == 3) {

            cout << "\n--- INFORMACION DEL JUGADOR ---" << endl;
            cout << "Nombre: " << jugador.getNombre() << endl;
            cout << "Vida: " << jugador.getVida() << endl;
            cout << "Dinero: " << jugador.getDinero() << " monedas" << endl;
            cout << "Nivel: " << jugador.getNivel() << endl;
            cout << "Experiencia: " << jugador.getExperiencia() << endl;
        }

        else if (respuesta == 4) {
            int opcionTren = -1;

                do {

                    cout << "\n========== MENU DEL TREN ==========" << endl;
                    cout << "Estacion actual: " << tren.getUbicacion() << endl;
                    cout << "1. Viajar" << endl;
                    cout << "2. Cargar carbon" << endl;
                    cout << "3. Ver estado del tren" << endl;
                    cout << "4. Instalar mejoras" << endl;
                    cout << "5. Leer periodico" << endl;
                    cout << "0. Volver" << endl;
                    cout << "Elige una opcion: ";
                    cin >> opcionTren;

                    if (opcionTren == 1) {
                        tren.viajarSiguienteEstacion(jugador);

                        if (!jugador.estaVivo()) {
                            cout << "\nFIN DEL JUEGO. Tu aventura ha terminado." << endl;
                            respuesta = 0;
                            opcionTren = 0;
                        }

                        else if (tren.getUbicacion() == "Estacion Terminal" && !jefeDerrotado) {
                            cout << "\n¡EL JEFE FINAL HA APARECIDO!" << endl;

                            combatirJefe(jugador, jefe);

                            jefeDerrotado = true;

                            if (!jugador.estaVivo()) {
                                cout << "\nFIN DEL JUEGO. Tu aventura ha terminado." << endl;
                                respuesta = 0;
                                opcionTren = 0;
                            }
                        }
                    }
                    else if (opcionTren == 2) {
                        tren.usarCarbon(jugador);
                    }
                    else if (opcionTren == 3) {

                        cout << "\n========== ESTADO DEL TREN ==========" << endl;
                        cout << "Combustible: " << tren.getCombustible() << " km" << endl;
                        cout << "Distancia recorrida: " << tren.getDistancia() << " km" << endl;
                        cout << "Velocidad: " << tren.getVelocidad() << " km/h" << endl;
                        cout << "Ubicacion: " << tren.getUbicacion() << endl;

                    }
                    else if (opcionTren == 4) {
                        tren.instalarMejora(jugador);
                    }
                    else if (opcionTren == 5) {
                        tren.leerPeriodico();
                    }
                    else if (opcionTren != 0) {
                        cout << "Opcion no valida." << endl;
                    }
                } while (opcionTren != 0);
            }
        else if (respuesta == 5) {
            gestor.guardarPartida(jugador, tren);
        }
        else if (respuesta != 0) {
            cout << "Opcion no valida." << endl;
        }

    } while (respuesta != 0);
    cout << "\nGracias por jugar Rieles Muertos, viajero." << endl;
    return 0;
}
