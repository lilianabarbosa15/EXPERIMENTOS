#ifndef CUERPOANIM_H
#define CUERPOANIM_H


#include <QObject>
#include <QGraphicsEllipseItem>
#include <QGraphicsPixmapItem>
#include <QList>

class CuerpoAnim:public QObject,public QGraphicsPixmapItem
{
public:
    CuerpoAnim(double _masa,double _PX,double _PY,double _VX,double _VY);
    double getMasa() const;
    void setMasa2(double value);
    double getPX() const;

    double getPY() const;

    void setPlanetas(const QList<CuerpoAnim *> &value);

private:
    QList<CuerpoAnim *> planetas;
    double distancia,masa,angulo,AX,AY,PX,PY,DT=1,VX,VY;
    double masa2,PX2,PY2,G;
public slots:
    void actualizar();
};

#endif // CUERPOANIM_H
