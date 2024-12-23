#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include "imagetransform.h"
#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QToolBar>
#include <QImage>
#include <QLabel>

class ImageProcessor : public QMainWindow
{
    Q_OBJECT

public:
    ImageProcessor(QWidget *parent = nullptr);
    ~ImageProcessor();
    void createActions();
    void createMenus();
    void createToolBars();
    void loadFile(QString filename);
private slots:
    void showGeometryTransfrom();
    void showOpenFile();
    void zoomIn();
    void zoomOut();
private:
    ImageTransform *gWin;
    QWidget *central;
    QMenu *fileMenu;
    QMenu *toolsMenu;
    QToolBar *fileTool;
    QImage img;
    QString filename;
    QLabel *imgWin;
    QAction *openFileAction;
    QAction *exitAction;
    QAction *zoomInAction;
    QAction *zoomOutAction;
    QAction *geometryAction;
};
#endif // IMAGEPROCESSOR_H
