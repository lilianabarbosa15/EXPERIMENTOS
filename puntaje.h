#ifndef PUNTAJE_H
#define PUNTAJE_H

#include <QFont>
#include <QPainterPath>
#include <QBrush>
#define INFINITO

#include <iostream>
using namespace std;

#include "informacion.h"
#define INFINITO 40000000

class Puntaje
{
public:
    struct infoUsuario
    {
    /*
    */
        string nombre;
        long int puntaje;
    };

    Puntaje();
    void calculoPuntajes();
    void calculoM_Puntajes();
    void dibujarPuntajes();

private:
    QFont font;
    QPainterPath contenido, path;

    long int Maxi = INFINITO, Mini = -1;
    int aux = -1;

    QVector<infoArchivo> infoArchivoUsuarios = {};

    infoUsuario Persona, formatoPuntaje;
    QVector<infoUsuario> TodosPuntajes = {};
    QVector<infoUsuario> MaxPuntajes = {};

private:
    QVector<int> Indicador ={};
    bool evaluarIndicador(int n);

    void ordenarPuntajes();
};

#endif // PUNTAJE_H
