#ifndef CANVASVIEW_H
#define CANVASVIEW_H

#include <QGraphicsView>

class CanvasView : public QGraphicsView
{
    Q_OBJECT
public:
    CanvasView(QWidget *parent = nullptr);

public slots:
    void zoomIn();
    void zoomOut();
    void pan();
    void loadImage(const QString &filePath);
    void loadData(const QString &filePath);

protected:
bool event(QEvent *event);
void wheelEvent(QWheelEvent *event);
void scaleView(qreal scaleFactor);

private:
 QGraphicsScene *scene;
};

#endif // CANVASVIEW_H
