#ifndef PIANOKEY_H
#define PIANOKEY_H

#include <QGraphicsView>
#include <QGraphicsRectItem>

class QPianoKey : public QGraphicsObject
{
    Q_OBJECT
    Q_PROPERTY(bool down READ isPressed WRITE setPressed DESIGNABLE true NOTIFY downChanged USER true)

public:
    explicit QPianoKey(QGraphicsItem *parent = nullptr, uint8_t key = UINT8_MAX);

    bool isPressed() const;
    void setPressed(bool pressed);

    QColor getPressedColor() const;
    void setPressedColor(QColor c);

    bool isNatural() const;
    uint8_t getIndex() const;

    // For deriving QGraphicsObject
    void setRect(QRectF rect);
    QRectF boundingRect() const override;

private:
    bool down = false;
    QColor pressedColor;

    uint8_t index = UINT8_MAX;
    QRectF rect;

signals:
    void pressed();
    void released();
    void downChanged(bool down);

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent*) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent*) override;
    void mousePressEvent(QGraphicsSceneMouseEvent*) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};
#endif // PIANOKEY_H
