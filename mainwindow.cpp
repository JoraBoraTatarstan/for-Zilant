#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , drawing(false)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        startPoint = event->pos(); // Начальная точка линии
        endPoint = startPoint;     // Конечная точка линии (пока совпадает с начальной)
        drawing = true;
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && drawing)
    {
        endPoint = event->pos(); // Обновляем конечную точку линии
        lines.append(QLine(startPoint, endPoint)); // Сохраняем линию
        drawing = false;
        update(); // Перерисовываем виджет
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (drawing)
    {
        endPoint = event->pos(); // Обновляем конечную точку линии
        snapToNearestLine(endPoint); // Проверяем и корректируем конечную точку
        update(); // Перерисовываем виджет
    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen pen(Qt::black, 2); // Настройка цвета и толщины линии
    painter.setPen(pen);

    drawLines(painter); // Рисуем все сохраненные линии

    if (drawing)
    {
        painter.drawLine(startPoint, endPoint); // Рисуем текущую линию
    }
}

void MainWindow::drawLines(QPainter &painter)
{
    for (const QLine &line : lines)
    {
        painter.drawLine(line); // Рисуем каждую линию из сохраненных
    }
}

bool MainWindow::isNearPoint(const QPoint &point, const QPoint &snapPoint) const
{
    return (QPointF(point).distanceToPoint(QPointF(snapPoint)) <= SNAP_DISTANCE);
}

void MainWindow::snapToNearestLine(QPoint &point)
{
    QPoint nearestPoint;
    bool found = false;

    // Проверяем близость к конечным точкам всех сохраненных линий
    for (const QLine &line : lines)
    {
        if (isNearPoint(point, line.p1()))
        {
            nearestPoint = line.p1();
            found = true;
        }
        else if (isNearPoint(point, line.p2()))
        {
            nearestPoint = line.p2();
            found = true;
        }
    }

    // Если найден близкий конечный пункт, обновляем координаты
    if (found)
    {
        point = nearestPoint;
    }
}
