#include "pianokeyboard.h"

QPianoKeyboard::QPianoKeyboard(QWidget *parent) : QGraphicsView(parent)
{
    QGraphicsScene* scene = new QGraphicsScene(this);
    setScene(scene);

    setDragMode(QGraphicsView::NoDrag);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    for (uint8_t i = 0; i < KEYS_NUMBER; i ++)
    {
        QPianoKey* key = new QPianoKey(nullptr, i);
        key->setZValue(key->isNatural() ? 1 : 2);
        scene->addItem(key);
        keys.append(key);

        connect(key, &QPianoKey::downChanged, this, [this, key](bool down){
            uint8_t index = key->getIndex();
            if (down)
                emit keyPressed(index);
            else
                emit keyReleased(index);
        });
    }

    QLinearGradient gradient(QPoint(0, 0), QPoint(0, 15));
    gradient.setColorAt(0, QColor::fromRgbF(0, 0, 0, 1));
    gradient.setColorAt(1, QColor::fromRgbF(0, 0, 0, 0));
    foreground = scene->addRect(0,0,width(),height(),QPen(Qt::transparent),QBrush(gradient));
    foreground->setZValue(3);
}

QPianoKeyboard::~QPianoKeyboard()
{
    scene()->clear();
}

QColor QPianoKeyboard::getKeyPressedColor() const
{
    return keyPressedColor;
}

void QPianoKeyboard::setKeyPressedColor(QColor c)
{
    keyPressedColor = c;

    for (uint8_t i = 0; i < keys.count(); i ++)
    {
        keys.at(i)->setPressedColor(c);
    }
}

void QPianoKeyboard::setKeyPressed(uint8_t key, bool pressed)
{
    if (key >= keys.count()) return;

    keys.at(key)->setPressed(pressed);
}

void QPianoKeyboard::resizeEvent(QResizeEvent *e)
{
    QGraphicsView::resizeEvent(e);

    qreal w = (qreal)(width()-4)/75; // 75 = numero di tasti bianchi
    qreal h = height()-4;

    uint8_t cc = 0;

    foreground->setRect(0, 0, width()-4, height()-4);

    for (uint8_t i = 0; i < keys.count(); i ++)
    {
        if (!keys.at(i)->isNatural())
        {
            keys.at(i)->setRect(QRectF(cc*w-w/4, 0, w/2, h-h/3));
        }
        else
        {
            keys.at(i)->setRect(QRectF(w*cc, 0, w, h));
            cc++;
        }
    }

    scene()->setSceneRect(QRectF(0, 0, width()-2, height()-2));
}
