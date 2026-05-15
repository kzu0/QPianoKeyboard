#include "pianokey.h"

#include <QApplication>
#include <QStyleOptionGraphicsItem>
#include <QPainter>

QPianoKey::QPianoKey(QGraphicsItem *parent, uint8_t key) : QGraphicsObject(parent), index(key)
{
    pressedColor = qApp->palette().color(QPalette::Highlight);

    setAcceptHoverEvents(true);

    // Connect. Spezzare in due? Una per l'update e una per i segnali ausiliari?
    connect(this, &QPianoKey::downChanged, this, [this](bool status){

        update();

        if (status)
            emit pressed();
        else
            emit released();
    });
}

bool QPianoKey::isPressed() const
{
    return down;
}

void QPianoKey::setPressed(bool pressed)
{
    if (pressed == down)
        return;

    down = pressed;

    emit downChanged(down);
}

QColor QPianoKey::getPressedColor() const
{
    return pressedColor;
}

void QPianoKey::setPressedColor(QColor c)
{
    if (pressedColor == c)
        return;

    pressedColor = c;

    update();
}

bool QPianoKey::isNatural() const
{
    switch (index%12) {
    case 1:
    case 3:
    case 6:
    case 8:
    case 10:
        return false;
    default:
        return true;
    }
}

uint8_t QPianoKey::getIndex() const
{
    return index;
}

void QPianoKey::setRect(QRectF rect)
{
    this->rect = rect;

    update();
}

QRectF QPianoKey::boundingRect() const
{
    return rect;
}

void QPianoKey::hoverEnterEvent(QGraphicsSceneHoverEvent*)
{
    update();
}

void QPianoKey::hoverLeaveEvent(QGraphicsSceneHoverEvent*)
{
    update();
}

void QPianoKey::mousePressEvent(QGraphicsSceneMouseEvent*)
{
    setPressed(true);
}
void QPianoKey::mouseReleaseEvent(QGraphicsSceneMouseEvent*)
{
    setPressed(false);
}

void QPianoKey::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QColor color;
    if (down || option->state & QStyle::State_Sunken)
        color = pressedColor;
    else if (option->state & QStyle::State_MouseOver)
        color = pressedColor.lighter();
    else
        color = isNatural() ? Qt::white : Qt::black;

    painter->setBrush(color);
    painter->setPen(Qt::black);
    painter->drawRect(rect);

    Q_UNUSED(widget);
}
