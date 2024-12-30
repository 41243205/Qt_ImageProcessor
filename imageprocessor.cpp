#include "imageprocessor.h"
#include "imagetransform.h"
#include "mouseevent.h"
#include <QHBoxLayout>
#include <QMenuBar>
#include <QFileDialog>
#include <QDebug>

ImageProcessor::ImageProcessor(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(QStringLiteral("影像處理"));
    central = new QWidget();
    QHBoxLayout *mainLayout = new QHBoxLayout(central);
    imgWin = new QLabel();
    QPixmap *initPixmap = new QPixmap(300,200);
    gWin = new ImageTransform();
    initPixmap->fill(QColor(255,255,255));
    imgWin->resize(300,200);
    imgWin->setScaledContents(true);
    imgWin->setPixmap(*initPixmap);
    mainLayout->addWidget(imgWin);
    setCentralWidget(central);
    createActions();
    createMenus();
    createToolBars();
}

ImageProcessor::~ImageProcessor() {}

void ImageProcessor::createActions()
{
    openFileAction = new QAction(QStringLiteral("開啟檔案(&O)"),this);
    openFileAction->setShortcut(tr("Ctrl+O"));
    openFileAction->setStatusTip(QStringLiteral("開啟影像檔案"));
    connect(openFileAction,SIGNAL(triggered()),this,SLOT(showOpenFile()));

    exitAction = new QAction(QStringLiteral("結束(&Q)"),this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(QStringLiteral("退出程式"));
    connect(exitAction,SIGNAL(triggered()),this,SLOT(close()));

    zoomInAction = new QAction(QStringLiteral("放大(&L)"), this);
    zoomInAction->setShortcut(tr("Ctrl+L"));
    zoomInAction->setStatusTip(QStringLiteral("放大影像"));
    connect(zoomInAction, SIGNAL(triggered()), this, SLOT(zoomIn()));

    zoomOutAction = new QAction(QStringLiteral("縮小(&T)"), this);
    zoomOutAction->setShortcut(tr("Ctrl+T"));
    zoomOutAction->setStatusTip(QStringLiteral("縮小影像"));
    connect(zoomOutAction, SIGNAL(triggered()), this, SLOT(zoomOut()));

    geometryAction = new QAction(QStringLiteral("幾何轉換"),this);
    geometryAction->setShortcut(tr("Ctrl+G"));
    geometryAction->setStatusTip(QStringLiteral("影像幾何轉換"));
    connect(geometryAction,SIGNAL(triggered()),this,SLOT(showGeometryTransfrom()));
    connect(exitAction,SIGNAL(triggered()),gWin,SLOT(close()));
}

void ImageProcessor::createMenus()
{
    fileMenu = menuBar()->addMenu(QStringLiteral("檔案(&F)"));
    fileMenu->addAction(openFileAction);
    fileMenu->addAction(geometryAction);
    fileMenu->addAction(exitAction);

    toolsMenu = menuBar()->addMenu(QStringLiteral("工具(&T)"));
    toolsMenu->addAction(zoomInAction);
    toolsMenu->addAction(zoomOutAction);
}

void ImageProcessor::createToolBars()
{
    fileTool = addToolBar("file");
    fileTool->addAction(openFileAction);
    fileTool->addAction(geometryAction);
    fileTool->addAction(zoomInAction);
    fileTool->addAction(zoomOutAction);
}

void ImageProcessor::loadFile(QString filename)
{
    qDebug()<<QString("file name:%1").arg(filename);
    QByteArray ba = filename.toLatin1();
    printf("FN:%s\n",(char *) ba.data());
    img.load(filename);
    imgWin->setPixmap(QPixmap::fromImage(img));
}

void ImageProcessor::showOpenFile()
{
    filename = QFileDialog::getOpenFileName(this,QStringLiteral("開啟影像"),tr("."),"bmp(*.bmp);;png(*.png)"";;Jpeg(*.jpg)");
    if(!filename.isEmpty())
    {
        if(img.isNull())
        {
            loadFile(filename);
        }
        else
        {
            ImageProcessor *newIPWin = new ImageProcessor();
            newIPWin->show();
            newIPWin->loadFile(filename);
        }
    }
}

void ImageProcessor::zoomIn()
{
    if (!img.isNull()) {
        QImage zoomedImg = img.scaled(img.width() * 2, img.height() * 2, Qt::KeepAspectRatio);
        QLabel *zoomWindow = new QLabel;
        zoomWindow->setPixmap(QPixmap::fromImage(zoomedImg));
        zoomWindow->setWindowTitle(QStringLiteral("放大影像"));
        zoomWindow->resize(zoomedImg.size());
        zoomWindow->show();
    }
}

void ImageProcessor::zoomOut()
{
    if (!img.isNull()) {
        QImage zoomedImg = img.scaled(img.width() * 0.5, img.height() * 0.5, Qt::KeepAspectRatio);
        QLabel *zoomWindow = new QLabel;
        zoomWindow->setPixmap(QPixmap::fromImage(zoomedImg));
        zoomWindow->setWindowTitle(QStringLiteral("縮小影像"));
        zoomWindow->resize(zoomedImg.size());
        zoomWindow->show();
    }
}

void ImageProcessor::showGeometryTransfrom()
{
    if(!img.isNull())
        gWin->srcImg = img;
    gWin->inWin->setPixmap(QPixmap::fromImage(gWin->srcImg));
    gWin->show();
}
