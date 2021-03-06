#include "ventanaseleccionjuego.h"
#include "ui_ventanaseleccionjuego.h"
#include "juego.h"
#include <QMediaPlayer>
#include <QDialog>

#include <escritor.h>
extern infoArchivo infoUsuario;
extern QVector<infoArchivo> informacionJuego;

#include <QMediaPlaylist>
#include <QUrl>
extern QMediaPlayer *musica;

extern QGraphicsScene *escena;  //Para dibujar la escena del juego en la que se encuentra el personaje
extern Juego *juego;

VentanaSeleccionJuego::VentanaSeleccionJuego(QWidget *parent) : QMainWindow(parent),  ui(new Ui::VentanaSeleccionJuego)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/iconos/Iconos/iconW_nave.png"));
}

VentanaSeleccionJuego::~VentanaSeleccionJuego()
{
    delete ui;
}

void VentanaSeleccionJuego::on_actionSobrePersonajes_triggered()
{
    QDialog *dialog = new QDialog();
    dialog->setWindowIcon(QIcon(":/iconos/Iconos/iconW_nave.png"));
    dialog->setWindowTitle("Players information");
    dialog->setGeometry(this->x(),this->y(),500,500);
    dialog->setFixedSize(500,500);
    dialog->setStyleSheet("background-color:black;");
    dialog->setWindowFlags(dialog->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    QLabel *label = new QLabel(dialog);
    label->setPixmap(QPixmap(":/info/Informacion/Personajes_Desc_.jpg").scaled(500,500));

    dialog->setModal(true);
    dialog->setVisible(true);
}

void VentanaSeleccionJuego::on_reiniciarJuego_clicked()
{
    infoUsuario.int1 = 0;
    infoUsuario.int2 = 0;

    if(infoUsuario.string1 == "<M>")
        informacionJuego.replace(0,infoUsuario);
    else
        informacionJuego.replace(1,infoUsuario);

    Escritor().guardarPartida(informacionJuego);
    cambiarVentana();
}

void VentanaSeleccionJuego::on_retomarJuego_clicked()
{
    if(infoUsuario.string1 == "<M>")
    {
        infoUsuario.int1 = informacionJuego.at(0).int1;
        infoUsuario.int2 = informacionJuego.at(0).int2;
    }
    else
    {
        infoUsuario.int1 = informacionJuego.at(1).int1;
        infoUsuario.int2 = informacionJuego.at(1).int2;
    }
    cambiarVentana();
}

void VentanaSeleccionJuego::cambiarVentana()
{
    for(unsigned short int n=0; n<informacionJuego.size(); n++)
    {
        qDebug() << informacionJuego.at(n).string1.c_str()          //Indica el modo de juego
                 << "\t" << informacionJuego.at(n).string2.c_str()  //Nombre del usuario
                 << "\t" << informacionJuego.at(n).int1             //Puntaje de la partida en curso
                 << "\t" << informacionJuego.at(n).int2;            //Nivel en el que se encuentra
    }
    wJ.setGeometry(this->geometry());
    this->close();                  //Cierra ventana de elección de la partida de juego
    wJ.setVisible(true);            //Muestra ventana de juego
    escena->setBackgroundBrush(Qt::lightGray);
    juego = new Juego();

    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/sonidos/Otros recursos/nocturnal.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);    //Se genera un loop con la musica de fondo que se desea
    musica->setPlaylist(playlist);
    //musica->play();   //Para inicializar la música del juego
}
