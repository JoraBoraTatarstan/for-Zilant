#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPainter>
#include <QPen>
#include <QPoint>
#include <QLine>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::MainWindow *ui;
    QPoint startPoint;
    QPoint endPoint;
    bool drawing;

    QVector<QLine> lines; // Хранит все нарисованные линии

    static constexpr int SNAP_DISTANCE = 10; // Порог близости для прилипания

    void drawLines(QPainter &painter); // Рисует все сохраненные линии
    bool isNearPoint(const QPoint &point, const QPoint &snapPoint) const; // Проверяет близость точки к другой точке
    void snapToNearestLine(QPoint &point); // Прилипает к ближайшей линии
};

#endif // MAINWINDOW_H
