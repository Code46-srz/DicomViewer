#include "canvasview.h"
#include "dcmtk/dcmdata/dcdeftag.h"
#include "qevent.h"
#include <QWheelEvent>
#include <dcmtk/dcmimgle/dcmimage.h>
#include <dcmtk/dcmdata/dcfilefo.h>
#include <QPanGesture>
#include <QGestureEvent>
#include <QScrollBar>
#include "qgraphicsitem.h"
#include "QFile.h"
CanvasView::CanvasView(QWidget *parent) : QGraphicsView(parent), scene(new QGraphicsScene(this))
{
    //QGraphicsScene *scene = new QGraphicsScene(this);
    scale(qreal(0.8), qreal(0.8));
    setMinimumSize(512, 512);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setTransformationAnchor(AnchorUnderMouse);
    setScene(scene);
    setBackgroundBrush(QColorConstants::Black);
    //set a image as the defualt background for the scene

}

void CanvasView::zoomIn()
{
    scaleView(qreal(1.2));
}

void CanvasView::zoomOut()
{
    scaleView(1 / qreal(1.2));
}

void CanvasView::pan()
{
    if (dragMode() == QGraphicsView::ScrollHandDrag)
        setDragMode(QGraphicsView::NoDrag);
    else
        setDragMode(QGraphicsView::ScrollHandDrag);
}

void CanvasView::wheelEvent(QWheelEvent *event)
{

    scaleView(pow(2., -event->angleDelta().y() / 240.0));
}

void CanvasView::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}

void CanvasView::loadImage(const QString &filePath)
{
    qDebug() << "Loading image..." << filePath;
    DicomImage image(filePath.toLocal8Bit().constData());

    if (image.getStatus() == EIS_Normal && image.isMonochrome()) {
        image.setMinMaxWindow();

        Uint8 *pixelData = (Uint8 *)(image.getOutputData(8 /* bits */));
        if (pixelData != nullptr) {

            QImage qImage(pixelData, image.getWidth(), image.getHeight(), QImage::Format_Grayscale8);

             QPixmap pixmap = QPixmap::fromImage(qImage);



             scene->addPixmap(pixmap);//->setZValue(1);

            qDebug() << "Image loaded successfully.";
        } else {
            qDebug() << "Error: Unable to load pixel data.";
        }
    } else {
        qDebug() << "Error: Unable to load DICOM image (" << DicomImage::getString(image.getStatus()) << ")";
    }
}

void CanvasView::loadData(const QString &filePath)
{
    DcmFileFormat fileformat;
    OFCondition status = fileformat.loadFile(filePath.toLocal8Bit().constData());
    if (status.good())
    {
        OFString patientName;
        if (fileformat.getDataset()->findAndGetOFString(DCM_PatientName, patientName).good())
        {
            qCritical() << "Error: cannot read DICOM file (" << QString::fromStdString(status.text()) << ")";

        } else
             qCritical()  << "Error: cannot access Patient's Name!";

    } else
        qCritical() << "Error: cannot read DICOM file (" << status.text() << ")";
}

bool CanvasView::event(QEvent *event)
{
    if (event->type() == QEvent::Gesture)
    {
        qDebug() << "Gesture event";
        QGestureEvent *gestureEvent = static_cast<QGestureEvent *>(event); //a pointer that points to the address of a pointer
        if (QPanGesture *panGesture = static_cast<QPanGesture *>(gestureEvent->gesture(Qt::PanGesture))) {
             // Extract the delta movement from the pan gesture
             QPointF delta = panGesture->delta();
             // Use the delta to update the view, for example, by panning the scene
             translate(delta.x(), delta.y());
             return true; // Indicate that the event was handled
        }
    }
    return QGraphicsView::event(event); // Call the base class implementation for any unhandled events
}

