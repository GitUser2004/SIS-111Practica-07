// Materia: Programación I, Paralelo 1

// Autor: *******

// Fecha creación: 16/10/2023

// Fecha modificación: 17/10/2023

// Número de ejericio: 1

/* Problema planteado: Escribe un programa que tenga un menú de tres opciones:

·	Ingreso de datos de los equipo de la LPFB.
·	Ingreso los resultados de los partidos.
·	Reporte de la tabla de posiciones
·	Salir
La primera opción debe ingresar los datos de los nombres de los equipos de la ligade acuerdo con la siguiente estructura y estos sean almacenados en un archivo binario llamado “EquiposLPFB.bin”, se debe considerar en no duplicar los equipos de futbol por el Nombre del Equipo
struct structEquiposLPFB
{
    char nombreEquipo[50];
    char colorCamiseta[50];
    char departamento[30];
    int anioCreacion;
};
La segunda opción debe ingresar los resultados de los partidos, que debe almacenarse en el archivo “ResultadosLPFB.bin” de acuerdo a la siguiente estructura, se debe considerer que solo se debe colocar resultados de los equipos ingresados en el archive “EquiposLPFB.bin”:
struct structResultadosLPFB
{
    char nombreEquipoLocal[50];
    char nombreEquipoVisitante[50];
    int golesEquipoLocal;
    Int golesEquipoVisitante;
    char fechaPartido[10]
};
La tercera opción debe dar un reporte de la tabla de posiciones*/

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const char* NOMBRE_ARCHIVO_EQUIPOS = "EquiposLPFB.bin";
const char* NOMBRE_ARCHIVO_RESULTADOS = "ResultadosLPFB.bin";

struct EquiposLPFB {
    char nombreEquipo[50];
    char colorCamiseta[50];
    char departamento[30];
    int anioCreacion;
};

struct ResultadosLPFB {
    char nombreEquipoLocal[50];
    char nombreEquipoVisitante[50];
    int golesEquipoLocal;
    int golesEquipoVisitante;
    char fechaPartido[10];
};

void ingresoDatosEquipos();
void ingresoResultados();
void generarReporte();

int main() {
    int opcion;
    do {
        cout << "\nMenu" << endl;
        cout << "====" << endl;
        cout << "1. Ingreso de datos de los equipos de la LPFB." << endl;
        cout << "2. Ingreso de los resultados de los partidos." << endl;
        cout << "3. Reporte de la tabla de posiciones." << endl;
        cout << "4. Salir" << endl;
        cout << "Ingrese la opcion deseada: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                ingresoDatosEquipos();
                break;
            case 2:
                ingresoResultados();
                break;
            case 3:
                generarReporte();
                break;
            case 4:
                cout << "Saliendo del programa." << endl;
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo." << endl;
        }
    } while (opcion != 4);

    return 0;
}

void ingresoDatosEquipos() {
    EquiposLPFB equipo;
    cout << "Ingreso de datos de los equipos de la LPFB" << endl;
    cout << "=========================================" << endl;
    cout << "Nombre del equipo: ";
    cin.ignore();
    cin.getline(equipo.nombreEquipo, 50);
    cout << "Color de la camiseta: ";
    cin.getline(equipo.colorCamiseta, 50);
    cout << "Departamento: ";
    cin.getline(equipo.departamento, 30);
    cout << "Año de creacion: ";
    cin >> equipo.anioCreacion;

    ifstream archivoEquipos(NOMBRE_ARCHIVO_EQUIPOS, ios::binary);
    EquiposLPFB temp;
    bool existe = false;
    while (archivoEquipos.read((char*)&temp, sizeof(EquiposLPFB))) {
        if (strcmp(equipo.nombreEquipo, temp.nombreEquipo) == 0) {
            existe = true;
            break;
        }
    }
    archivoEquipos.close();

    if (existe) {
        cout << "El equipo ya existe." << endl;
    } else {
        ofstream archivoEquiposSalida(NOMBRE_ARCHIVO_EQUIPOS, ios::app | ios::binary);
        archivoEquiposSalida.write((char*)&equipo, sizeof(EquiposLPFB));
        archivoEquiposSalida.close();
        cout << "Equipo ingresado exitosamente." << endl;
    }
}

void ingresoResultados() {
    ResultadosLPFB resultado;
    cout << "Ingreso de resultados de los partidos" << endl;
    cout << "=====================================" << endl;
    cout << "Nombre del equipo local: ";
    cin.ignore();
    cin.getline(resultado.nombreEquipoLocal, 50);
    cout << "Nombre del equipo visitante: ";
    cin.getline(resultado.nombreEquipoVisitante, 50);
    cout << "Goles del equipo local: ";
    cin >> resultado.golesEquipoLocal;
    cout << "Goles del equipo visitante: ";
    cin >> resultado.golesEquipoVisitante;
    cout << "Fecha del partido (Formato DD/MM/AAAA): ";
    cin >> resultado.fechaPartido;

    ifstream archivoEquipos(NOMBRE_ARCHIVO_EQUIPOS, ios::binary);
    EquiposLPFB tempLocal, tempVisitante;
    bool existeLocal = false, existeVisitante = false;

    while (archivoEquipos.read((char*)&tempLocal, sizeof(EquiposLPFB))) {
        if (strcmp(resultado.nombreEquipoLocal, tempLocal.nombreEquipo) == 0) {
            existeLocal = true;
            break;
        }
    }

    archivoEquipos.clear();
    archivoEquipos.seekg(0, ios::beg);

    while (archivoEquipos.read((char*)&tempVisitante, sizeof(EquiposLPFB))) {
        if (strcmp(resultado.nombreEquipoVisitante, tempVisitante.nombreEquipo) == 0) {
            existeVisitante = true;
            break;
        }
    }

    archivoEquipos.close();

    if (!existeLocal || !existeVisitante) {
        cout << "Al menos uno de los equipos no existe." << endl;
    } else {
        ofstream archivoResultados(NOMBRE_ARCHIVO_RESULTADOS, ios::app | ios::binary);
        archivoResultados.write((char*)&resultado, sizeof(ResultadosLPFB));
        archivoResultados.close();
        cout << "Resultado ingresado exitosamente." << endl;
    }
}

void generarReporte() {
    ifstream archivoEquipos(NOMBRE_ARCHIVO_EQUIPOS, ios::binary);
    ifstream archivoResultados(NOMBRE_ARCHIVO_RESULTADOS, ios::binary);

    EquiposLPFB equipo;
    ResultadosLPFB resultado;

    cout << "\nReporte de la tabla de posiciones" << endl;
    cout << "=================================" << endl;

    while (archivoEquipos.read((char*)&equipo, sizeof(EquiposLPFB))) {
        cout << "Equipo: " << equipo.nombreEquipo << endl;

        int partidosJugados = 0, partidosGanados = 0, partidosEmpatados = 0, partidosPerdidos = 0;
        int golesFavor = 0, golesContra = 0, diferenciaGoles = 0, puntos = 0;

        archivoResultados.clear();
        archivoResultados.seekg(0, ios::beg);

        while (archivoResultados.read((char*)&resultado, sizeof(ResultadosLPFB))) {
            if (strcmp(equipo.nombreEquipo, resultado.nombreEquipoLocal) == 0 ||
                strcmp(equipo.nombreEquipo, resultado.nombreEquipoVisitante) == 0) {

                partidosJugados++;

                if (strcmp(equipo.nombreEquipo, resultado.nombreEquipoLocal) == 0) {
                    golesFavor += resultado.golesEquipoLocal;
                    golesContra += resultado.golesEquipoVisitante;

                    if (resultado.golesEquipoLocal > resultado.golesEquipoVisitante) {
                        partidosGanados++;
                        puntos += 3;
                    } else if (resultado.golesEquipoLocal == resultado.golesEquipoVisitante) {
                        partidosEmpatados++;
                        puntos += 1;
                    } else {
                        partidosPerdidos++;
                    }
                } else {
                    golesFavor += resultado.golesEquipoVisitante;
                    golesContra += resultado.golesEquipoLocal;

                    if (resultado.golesEquipoVisitante > resultado.golesEquipoLocal) {
                        partidosGanados++;
                        puntos += 3;
                    } else if (resultado.golesEquipoVisitante == resultado.golesEquipoLocal) {
                        partidosEmpatados++;
                        puntos += 1;
                    } else {
                        partidosPerdidos++;
                    }
                }
            }
        }

        diferenciaGoles = golesFavor - golesContra;

        cout << "Partidos jugados (PJ): " << partidosJugados << endl;
        cout << "Partidos ganados (G): " << partidosGanados << endl;
        cout << "Partidos empatados (E): " << partidosEmpatados << endl;
        cout << "Partidos perdidos (P): " << partidosPerdidos << endl;
        cout << "Goles a favor (GF): " << golesFavor << endl;
        cout << "Goles en contra (GC): " << golesContra << endl;
        cout << "Diferencia de goles (DG): " << diferenciaGoles << endl;
        cout << "Puntos: " << puntos << endl;

        cout << "-----------------------------------------" << endl;
    }

    archivoEquipos.close();
    archivoResultados.close();
}
