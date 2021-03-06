#include "escritor.h"
#include <fstream>
#include <QIcon>

extern infoArchivo infoUsuario;

#include <QDebug>   //
#include "juego.h"
extern Juego *juego;

QVector<infoArchivo> Escritor::leerArchivo(string nombre_archivo)
{
    QVector<infoArchivo> infoLista = {};
    ifstream fichero;                                                     //Abre el archivo en modo lectura
    fichero.open("../ProyectoFinal/PARTIDAS/"+nombre_archivo+".txt");     //USUARIOS.txt almacena el nombre y la contraseña de los usuarios
    if(!fichero.is_open()){                                     //Comprueba que el archivo fue abierto exitosamente
        msgBox.setWindowTitle(" ");
        msgBox.setWindowIcon(QIcon(":/iconos/iconW_nave.png"));
        msgBox.setText("ERROR");
        msgBox.exec();
        exit(1);
    }
    while(!fichero.eof()){                                       //Itera mientras que no se haya llegado al final del archivo
        fichero >> infoUsuario.string1;
        fichero >> infoUsuario.string2;
        fichero >> infoUsuario.int1;
        fichero >> infoUsuario.int2;
        infoLista.append(infoUsuario);
    }
    fichero.close();                                             //Se cierra el archivo
    return infoLista;
}

void Escritor::registrarUsuario(string name_ingresado, string password_ingresado)
{
    //Guarda los datos ingresados en el archivo predeterminado de usuarios
    ofstream fichero;
    fichero.open("../ProyectoFinal/PARTIDAS/USUARIOS.txt",ios::app);
    fichero << endl << name_ingresado << "\t" << password_ingresado << "\t" << 0 << "\t" << 0;
    fichero.close();

    //Genera un archivo nuevo para el usuario
    ofstream streamEscritura("../ProyectoFinal/PARTIDAS/"+name_ingresado+"_usu.txt");
    streamEscritura << endl << "<M>" << "\t" << name_ingresado << "\t" << 0 << "\t" << 0;
    streamEscritura << endl << "<I>" << "\t" << name_ingresado << "\t" << 0 << "\t" << 0;
    streamEscritura.close();
}

void Escritor::guardarPartida(QVector<infoArchivo> infoJuego)
{
    ofstream fichero;                                                               //Abre el archivo en modo lectura
    fichero.open("../ProyectoFinal/PARTIDAS/"+infoJuego.at(0).string2+"_usu.txt");
    if(!fichero.is_open()){                                                         //Comprueba que el archivo fue abierto exitosamente
        msgBox.setWindowTitle(" ");
        msgBox.setWindowIcon(QIcon(":/iconos/iconW_nave.png"));
        msgBox.setText("ERROR");
        msgBox.exec();
        exit(1);
    }
    for(unsigned short int i=0; i<infoJuego.size(); i++)
    {
        fichero << endl << infoJuego.at(i).string1  //Indica el modo de juego
                << "\t" << infoJuego.at(i).string2  //Nombre del usuario
                << "\t" << infoJuego.at(i).int1     //Puntaje de la partida en curso
                << "\t" << infoJuego.at(i).int2;    //Nivel en el que se encuentra
    }
    fichero.close();                                             //Se cierra el archivo
}

void Escritor::actualizarInformacion(QVector<infoArchivo> infoNueva)
{
    ofstream fichero;                                                               //Abre el archivo en modo lectura
    fichero.open("../ProyectoFinal/PARTIDAS/USUARIOS.txt");
    if(!fichero.is_open()){                                                         //Comprueba que el archivo fue abierto exitosamente
        msgBox.setWindowTitle(" ");
        msgBox.setWindowIcon(QIcon(":/iconos/iconW_nave.png"));
        msgBox.setText("ERROR");
        msgBox.exec();
        exit(1);
    }
    for(unsigned short int i=0; i<infoNueva.size(); i++)
    {
        fichero << endl << infoNueva.at(i).string1  //Indica el nombre del usuario
                << "\t" << infoNueva.at(i).string2  //La contraseña del usuario
                << "\t" << infoNueva.at(i).int1     //Puntaje máximo en modo multijugador
                << "\t" << infoNueva.at(i).int2;    //Puntaje máximo en modo individual
    }
    fichero.close();                                             //Se cierra el archivo
}

void Escritor::actualizarInfoLocal()
{
    if(juego->multijugador==true){
        infoUsuario.string1 = "<M>";
        informacionJuego.replace(0,infoUsuario);
    }
    else{
        infoUsuario.string1 = "<I>";
        informacionJuego.replace(1,infoUsuario);
    }
    Escritor().guardarPartida(informacionJuego);
}

void Escritor::actualizarInfoGeneral()
{
    NuevainformacionU = Escritor().leerArchivo("USUARIOS");  //Se pasan los datos de las contraseñas y los nombres a un vector
    infoArchivo nuevaInfo = {};
    for(int i=0; i<NuevainformacionU.size(); i++){
        if( NuevainformacionU.at(i).string1 == informacionJuego.at(0).string2 ){
            qDebug() << "posicion (" << i << "): " << QString::fromStdString(NuevainformacionU.at(i).string1)
                     << "MULTIJUGADOR: " << juego->multijugador;

            qDebug() << "NUEVA INFORMACIÓN: " << QString::fromStdString(NuevainformacionU.at(i).string1)
                                              << QString::fromStdString(NuevainformacionU.at(i).string2)
                                              << (NuevainformacionU.at(i).int1)
                                              << (NuevainformacionU.at(i).int2);

            qDebug() << "MULTIJUGADOR INFORMACIÓN: " << QString::fromStdString(informacionJuego.at(0).string1)
                                                     << QString::fromStdString(informacionJuego.at(0).string2)
                                                     << (informacionJuego.at(0).int1)
                                                     << (informacionJuego.at(0).int2);

            qDebug() << "INDIVIDUAL INFORMACIÓN: "   << QString::fromStdString(informacionJuego.at(1).string1)
                                                     << QString::fromStdString(informacionJuego.at(1).string2)
                                                     << (informacionJuego.at(1).int1)
                                                     << (informacionJuego.at(1).int2);


            nuevaInfo.string1 = NuevainformacionU.at(i).string1;        //Nombre del usuario
            nuevaInfo.string2 = NuevainformacionU.at(i).string2;        //Contraseña del usuario
            if(juego->multijugador==true){
                if( NuevainformacionU.at(i).int1 < informacionJuego.at(0).int1){
                    nuevaInfo.int1 = informacionJuego.at(0).int1;               //Nuevo mayor puntaje en modo multijugador
                    nuevaInfo.int2 = NuevainformacionU.at(i).int2;              //Puntaje en modo individual
                    NuevainformacionU.replace(i, nuevaInfo);
                }
            }else{
                if( NuevainformacionU.at(i).int2 < informacionJuego.at(1).int1){
                    nuevaInfo.int1 = NuevainformacionU.at(i).int1;              //Puntaje en modo individual
                    nuevaInfo.int2 = informacionJuego.at(1).int1;               //Nuevo mayor puntaje en modo multijugador
                    NuevainformacionU.replace(i, nuevaInfo);
                }
            }
            Escritor().actualizarInformacion(NuevainformacionU);
            break;
        }
    }
}
