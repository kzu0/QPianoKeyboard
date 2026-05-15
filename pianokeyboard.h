#ifndef PIANOKEYBOARD_H
#define PIANOKEYBOARD_H

#include <QGraphicsView>
#include <QGraphicsRectItem>
#include "pianokey.h"

class QPianoKeyboard : public QGraphicsView
{
    Q_OBJECT
    Q_PROPERTY(QColor keyPressedColor READ getKeyPressedColor WRITE setKeyPressedColor DESIGNABLE true NOTIFY keyPressedColorChanged)

public:
    explicit QPianoKeyboard(QWidget *parent = nullptr);
    ~QPianoKeyboard();

    QColor getKeyPressedColor() const;
    void setKeyPressedColor(QColor c);

    static constexpr uint8_t KEYS_NUMBER = 128;

public slots:
    void setKeyPressed(uint8_t key, bool pressed);

private:
    QGraphicsRectItem* foreground;
    QList<QPianoKey*> keys;
    QColor keyPressedColor;

protected:
    void resizeEvent(QResizeEvent* e);

signals:
    void keyPressed(uint8_t key);
    void keyReleased(uint8_t key);
    void keyPressedColorChanged(QColor c);
};

#endif // PIANOKEYBOARD_H
