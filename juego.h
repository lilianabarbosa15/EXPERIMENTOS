#ifndef JUEGO_H
#define JUEGO_H


#include <QGraphicsRectItem>

#include "animacion.h"
#include "aliado.h"
#include "meteorito.h"
#include "plataforma.h"
#include "moneda.h"
#include "enemigo.h"
#include "bala.h"
#include "escritor.h"
extern infoArchivo infoUsuario;
extern QVector<infoArchivo> informacionJuego;

class Juego: public QObject
{
    Q_OBJECT
private:
    void ActualizarCountdown();
    QString TimeAsSting();

    void actualizarDisparos();
    void evaluarNivel();

public:
    Juego(QObject *parent=nullptr);
    void actualizar();
    void Trackers();
    void DisparosEnemigos();
    void DisminuirVidas();
    void AumentarPuntaje();

    void NuevosPuntos();
    void NuevosObstaculos();
    void ActualizarPuntos();

    int getNivel();
    void ReiniciarNivel();
    void CambiarLocalizacion();
    bool getModoJuego() { return multijugador; }
    QVector<Plataforma *> getPlataformas() { return plataformas; }

private:
    Puntaje *p;

    unsigned short int vidas=1;
    bool estado;
    unsigned long int contTime=0, duracion=3900;
    string nombreUsuario;

    QGraphicsTextItem *Score = new QGraphicsTextItem;   //Puntaje que se va llevando en el nivel
    QGraphicsTextItem *Lives1 = new QGraphicsTextItem;  //Vidas del personaje 1 en el nivel
    QGraphicsTextItem *Lives2 = new QGraphicsTextItem;  //Vidas del personaje 2 en el nivel
    QGraphicsTextItem *Time = new QGraphicsTextItem;    //Tiempo que le queda al usuario para completar el nivel

    QVector<Plataforma *> plataformas = {};
    int y_nE, cantidadMonedas = 1;

public:
    unsigned short int localizacion = 0;    //Historia/Juego

    QVector<Aliado *> jugadores = {};
    QVector<Enemigo*> Enemigos = {};
    QList<Enemigo*> EnemEstaticos = {};
    QVector<Meteorito*> disparosEnemigos = {};
    QVector<Bala*> disparosAliados = {};
    QVector<Meteorito *> meteoritos = {};
    QVector<Moneda *> estrellas = {};

    int puntajeNivel = 0;
    bool multijugador = false;

    QTimer *timer;                                      //Crea el timer
    bool estado_juego = false;                          //Determina si se leen las letras presionadas o no

    bool J_vivo[2]={true,false};

};

#endif // JUEGO_H
