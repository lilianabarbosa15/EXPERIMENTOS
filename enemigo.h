#ifndef ENEMIGO_H
#define ENEMIGO_H


#include <QGraphicsRectItem>
#include "cuerpo.h"
#include "meteorito.h"
#include "bala.h"

class Enemigo: public cuerpo, public QGraphicsPixmapItem //public QGraphicsRectItem
{
public:
    Enemigo(unsigned int tipo, unsigned short int tipo_b, unsigned short int life, int posX, int posY, int posX_arma, int posY_arma, int pos_inicialX, int pos_inicialY, float vel, float a, float theta_disparo, int radio_bala, float vel_bala);
    bool ActualizarPosicion();

    void dibujarItem() override;
    void disparar() override;

    bool ColisionBala(unsigned int balajugador);
    void actualizarVida(unsigned int balajugador, unsigned short int tipoenemigo);

    int getPosicion_x() const;
    int getPosicion_y() const;

public:
    bool vivo = true;

private:
    unsigned short int enemigo;
    unsigned short int disparo;
    unsigned short int vidas;
    int ancho = 60, alto = 60;

    int posicion_x, posicioninicial_x;
    int posicion_y, posicioninicial_y;
    int posX=0,posY=0;
    float velocidad;
    float aceleracion;

    float angulo_b;
    int radio_b;
    float velocidad_b;
    int posicionX_arma;
    int posicionY_arma;

    Meteorito *bala;
    QPixmap apariencia;

};

#endif // ENEMIGO_H
