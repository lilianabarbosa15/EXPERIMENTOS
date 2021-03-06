#ifndef ANIMACION_H
#define ANIMACION_H


/*
 Recordar cambiar dirección y datos de los cuerpos. Así como poner pixmap en la clase
 cuerpoAnim.
*/

#include<QVector>
#include<QString>
#include<QKeyEvent>
#include<QTimer>
#include<QObject>
#include<QGraphicsScene>
#include<QDebug>
#include "cuerpoanim.h"
#include "puntaje.h"

class Animacion: public QObject
{
     Q_OBJECT
private:
    QString Direccion=":/comic/Comic/"; //"../ProyectoFinal/Comic/"; //Dirección común de los cuerpos //        :/comic/Comic/
    //Vectores con los nombres de las imágenes. Nota: cambiar según necesidad
    QVector<QString>Nivel1={"N1_1.png","N1_2.png","N1_3.png","N1_5.png","N1_6.png","N1_7.png",
                           "N1_8.png","N1_8_2.png", "N1_8_2_2.png" ,"N1_8_3.png","N1_8_4.png",
                           "N1_9.png","N1_11.png","N1_12.png","N1_13.png",
                            "N1_14.png", "N1_15.png"};

    QVector<QString>Nivel2={"N2_1.png","N2_2.png","N2_3.png","N2_5.png","N2_6.png","N2_7.png",
                            "N2_8.png","N2_9.png","N2_10.png","N2_11.png"};

    QVector<QString>Nivel3={"N3_1.png","N3_2.png","N3_3.png","N3_4.png", "cuerpos","N3_6.png","N3_7.png",
                            "N3_8.png","N3_9.png","N3_10.png","N3_11.png"};

    QVector<QString>Final={"N4_1.png","N4_2.png","N4_3.png","N4_4.png", "N4_5.png","N4_6.png","N4_7.png",
                           "N4_8.png","N4_9.png"};
     QPixmap slide; //qpixmap que almacena la imágen
     QGraphicsPixmapItem *item;
     /*intervalo:intervalo de tiempo que se animará la gravitación si usuario no
      presiona la tecla.
     progreso: posición en el QVector actual.
     inicioTimer: milisegundos tras los cuales se actualiza el timer.
    */
     int intervalo=25, cont=0, progreso=0, nivel=0, inicioTimer=5;
     //posición en X y Y del QPixmap. alto y ancho de los valores de la escala para
     //ajustarlo a la escena.
     int posX=70, posY=50, escalaW=680,escalaH=400;
     //Activar animación: en ventana de juego colocar si la animación esta activada como parte
     //de la condición de QKeysEvent para la tecla seleccionada.
     bool activado=false;
     //Atributos para animación gravitacional:
     QTimer *timer;
     int dt=1;   //Velocidad de los cuerpos en orbita
     //Cuerpos a animar: Revisar datos para mejor animación.
     //QVector<CuerpoAnim *>Cuerpos={cuerpo1, cuerpo2};

public:
     Animacion(QObject *parent=nullptr);
     bool getActivado() const;
     void setActivado(bool value);
     int getNivel() const;
     void setNivel(int value);
     void AnimacionNivel1();
     void AnimacionNivel2();
     void AnimacionNivel3();
     void AnimacionFinal();
     void Presentar();



public slots:
    void actualizar();

private:
    QList<CuerpoAnim *> planetas;
    CuerpoAnim * uno;
    CuerpoAnim * dos;

};








/*
Nota: código usado en ventana principal:
Colocar en constructor de ventana principal tras crear el puntero como atributo (Animacion *A)
    A=new Animacion;
    A->setScene(Scene); //primer paso siempre debe ser pasar escena sobre la que se animará.
    A->setActivado(true); //Para que se pasen las diapositivas
    A->setNivel(3); //Definir nivel. Cambia durante el código de la ventana principal
    A->Presentar(); //Presentar la primera diapositiva
Para cambio con la tecla en el método keyPressEvent se coloca esta condición con la tecla
elegida (X en este caso:)
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_X && A->getActivado()){
      A->Presentar();
    }
}
*/

#endif // ANIMACION_H
