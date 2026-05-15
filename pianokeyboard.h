#ifndef PIANOKEYBOARD_H
#define PIANOKEYBOARD_H

#include <QGraphicsView>
#include <QGraphicsRectItem>

class QPianoKey : public QGraphicsObject
{
    Q_OBJECT

public:
    explicit QPianoKey(QGraphicsItem *parent = nullptr, uint8_t key = 255);

    bool isBlack();
    void setPressed(bool pressed);
    void setPressedColor(QColor c);

    void setRect(QRectF rect);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    uint8_t m_key = 255;
    QRectF m_rect;

    bool m_pressed = false;
    QColor m_pressedColor;

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent*) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent*) override;
    void mousePressEvent(QGraphicsSceneMouseEvent*) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*) override;

signals:
    void pressed(uint8_t key);
    void released(uint8_t key);
};

class QPianoKeyboard : public QGraphicsView
{
    Q_OBJECT
    Q_PROPERTY(QColor keyPressedColor READ getKeyPressedColor WRITE setKeyPressedColor DESIGNABLE true)

public:
    explicit QPianoKeyboard(QWidget *parent = nullptr);
    ~QPianoKeyboard();

    QColor getKeyPressedColor() const;
    void setKeyPressedColor(QColor c);

    static constexpr uint8_t KEYS_NUMBER = 128;

public slots:
    void setKeyPressed(uint8_t key, bool pressed);

private:
    QList<QPianoKey*> keys;
    QGraphicsRectItem* foreground;
    QColor keyPressedColor;

protected:
    void resizeEvent(QResizeEvent* e);

signals:
    void keyPressed(uint8_t key);
    void keyReleased(uint8_t key);
};

#endif // PIANOKEYBOARD_H
