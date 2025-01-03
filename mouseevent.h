#ifndef MOUSEEVENT_H
#define MOUSEEVENT_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QStatusBar>
#include <QLabel>

class MouseEvent : public QMainWindow
{
    Q_OBJECT
public:
    MouseEvent(QWidget *parent = 0);
    ~MouseEvent();
protected:
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private:
    QLabel *statusLabel;
    QLabel *MousePosLabel;
    QLabel *ColorLabel;
    QPixmap image;
};

#endif // MOUSEEVENT_H
