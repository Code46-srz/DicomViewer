#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <dcmtk/dcmimgle/dcmimage.h>
#include <QGraphicsScene>
#include "canvasview.h"
#include <QWheelEvent>
#include <QGridLayout>
#include <QPushButton>
#include <QGraphicsPixmapItem>
#include <QLabel>
#include <QDebug>
#include <QMainWindow>
#include <QActionGroup>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , canvas(new CanvasView(this))
{
    setMenu();
    //test();
    //ui->setupUi(this);
    //central widget MAIN SCREEN WIDGET
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    //layout
    QGridLayout *layout = new QGridLayout(centralWidget);
    //canvas to display the images and data
    //CanvasView *canvas = new CanvasView(this);
    // sidebar buttons
    QVBoxLayout *sidebarLayout = new QVBoxLayout(this);
    QPushButton *zoomButton = new QPushButton( this);
    QPushButton *zoomOutButton = new QPushButton( this);
    QPushButton *panButton = new QPushButton( this);
    QLabel *logo = new QLabel(this);
    //button styles
    QPixmap logoX(":/assets/LOGODicom.png");
     QPixmap scaledPixmap = logoX.scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    logo->setPixmap(scaledPixmap);
    zoomButton->setIcon(QIcon(":/icon/sidebar/zoom-in.png"));
    zoomOutButton->setIcon(QIcon(":/icon/sidebar/zoom-out.png"));
    //if pan button clicked idsplay pan icon if clicked again display no pan icon

    panButton->setIcon(QIcon(":/icon/sidebar/pan.png"));

    //label for displaying patient data
    QLabel *patientData = new QLabel(this);
    patientData->setText("Patient Data");
    //setMenu();
    // Connect the signals and slots
    connect(zoomButton, &QPushButton::clicked, canvas, &CanvasView::zoomIn);
    connect(zoomOutButton, &QPushButton::clicked, canvas, &CanvasView::zoomOut);
    connect(panButton, &QPushButton::clicked, canvas, &CanvasView::pan);



    //Add widgets to the sidebar layout
    //sidebarLayout->addWidget(logo);
    sidebarLayout->addWidget(zoomButton);
    sidebarLayout->addWidget(zoomOutButton);
    sidebarLayout->addWidget(panButton);
    sidebarLayout->addWidget(patientData);


    // Add the widgets to the main layout
    layout->addWidget(logo, 0, 0);
    layout->addWidget(canvas, 1, 0);
    layout->addLayout(sidebarLayout, 1, 1);






}


void MainWindow::setMenu()
{
    //menu
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    QMenu *editMenu = menuBar()->addMenu(tr("&Edit"));
    QMenu *viewMenu = menuBar()->addMenu(tr("&View"));
    //QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));

    //file menu
    QAction *openAct = new QAction(tr("&Open"), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open a new file"));
    fileMenu->addAction(openAct);
    connect(openAct, &QAction::triggered, this, &MainWindow::open);

    QAction *saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the file"));
    fileMenu->addAction(saveAct);
    QAction *exitAct = new QAction(tr("&Exit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Exit the application"));
    fileMenu->addAction(exitAct);

    //edit menu
    QAction *undoAct = new QAction(tr("&Undo"), this);
    undoAct->setShortcuts(QKeySequence::Undo);
    undoAct->setStatusTip(tr("Undo the last action"));
    editMenu->addAction(undoAct);

    QAction *redoAct = new QAction(tr("&Redo"), this);
    redoAct->setShortcuts(QKeySequence::Redo);
    redoAct->setStatusTip(tr("Redo the last action"));
    editMenu->addAction(redoAct);

    //view menu
    QActionGroup *viewGroup = new QActionGroup(this);
    QAction *zoomInAct = new QAction(tr("&Zoom In"), this);
    zoomInAct->setShortcuts(QKeySequence::ZoomIn);
    zoomInAct->setStatusTip(tr("Zoom in the image"));
    viewGroup->addAction(zoomInAct);
    viewMenu->addAction(zoomInAct);

    QAction *zoomOutAct = new QAction(tr("&Zoom Out"), this);
    zoomOutAct->setShortcuts(QKeySequence::ZoomOut);
    zoomOutAct->setStatusTip(tr("Zoom out the image"));
    viewGroup->addAction(zoomOutAct);
    viewMenu->addAction(zoomOutAct);

    QAction *panAct = new QAction(tr("&Pan"), this);
    panAct->setShortcuts(QKeySequence::MoveToNextPage);
}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(), tr("All Files (*);;Text Files (*.txt)"));
    qDebug() << "the test one" << fileName;
    if (!fileName.isEmpty()) {
        // Open the file using QFile or any other file handling mechanism
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::warning(this, tr("Error"), tr("Could not open file"));
            return;
        }

        canvas->loadImage(fileName);


    }
     //canvas->loadImage("C:/Users/bgele/Desktop/democases/case1/case1_036.dcm");
}


MainWindow::~MainWindow()
{
    //delete ui;
}
