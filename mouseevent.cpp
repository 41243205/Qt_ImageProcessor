#include "mouseevent.h"

MouseEvent::MouseEvent(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(QStringLiteral("測試滑鼠事件"));
    statusLabel = new QLabel;
    statusLabel->setText(QStringLiteral("指標位置"));
    statusLabel->setFixedWidth(100);
    MousePosLabel = new QLabel;
    MousePosLabel->setText(tr(" "));
    MousePosLabel->setFixedWidth(100);
    QStatusBar().addPermanentWidget(statusLabel);
    QStatusBar().addPermanentWidget(MousePosLabel);
    setMouseTracking(true);
    resize(400,300);
}

MouseEvent::~MouseEvent()
{}

void MouseEvent::mouseMoveEvent(QMouseEvent *event)
{
    QString str = "(" + QString::number(event->x()) + ", " +
                  QString::number(event->y()) + ")";
    MousePosLabel->setText(str);
}

void MouseEvent::mousePressEvent(QMouseEvent *event)
{
    QString str = "(" + QString::number(event->x()) + ", " +
                  QString::number(event->y()) + ")";
    if(event->button() == Qt::LeftButton)
    {
        QStatusBar().showMessage(QStringLiteral("左鍵:")+str);
    }
    else if(event->button() == Qt::RightButton)
    {
        QStatusBar().showMessage(QStringLiteral("右鍵:")+str);
    }
    else if(event->button() == Qt::MiddleButton)
    {
        QStatusBar().showMessage(QStringLiteral("中鍵:")+str);
    }
}

void MouseEvent::mouseReleaseEvent(QMouseEvent *event)
{
    QString str = "(" + QString::number(event->x()) + ", " +
                  QString::number(event->y()) + ")";
    QStatusBar().showMessage(QStringLiteral("釋放:")+str);
}

void MouseEvent::mouseDoubleClickEvent(QMouseEvent *event)
{

}
