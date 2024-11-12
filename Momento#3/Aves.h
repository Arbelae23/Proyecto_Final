#ifndef AVES_H
#define AVES_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QTimer>
#include <QVector>
#include <QRandomGenerator>

class Aves : public QGraphicsItem
{
public:
    Aves(qreal initialX, qreal initialY, const QString &imagePath, int movementType);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void updatePosition();

private:
    QPixmap m_pixmap; // Para almacenar la imagen del ave
    qreal m_velocityX;
    qreal m_velocityY;
    int m_movementType; // Tipo de movimiento: 0 para diagonal, 1 para parabólico

    // Limites de la pantalla
    qreal minX;
    qreal maxX;
    qreal minY;
    qreal maxY;
};

#endif // AVES_H
