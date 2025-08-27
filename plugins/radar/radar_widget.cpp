#include "radar_widget.h"
#include <QPainter>
#include <QPaintEvent>

RadarWidget::RadarWidget(QWidget *parent):QWidget(parent)
{
    setMinimumSize(400, 400); // As per design requirements
}

RadarWidget::~RadarWidget(){}

void RadarWidget::updateRadarDisplay()
{
    update(); // Request paint event
}

void  RadarWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event); // Avoid unused warning

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    drawRadarScreen(painter);
    drawEntities(painter);
}


void RadarWidget::drawRadarScreen(QPainter &painter)
{
    // Draw background circle - radar sweep area
    int radius = std::min(width(), height())/2-10;
    QPoint center=rect().center();

    painter.setBrush(QColor(0, 0, 0)); // Black background
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(center, radius, radius);

    // Draw concentric circles for range marks
    painter.setPen(QPen(Qt::green, 1));
    for (int i=1; i<=4; ++i)
    {
        int r=(radius/4)*i;
        painter.drawEllipse(center, r, r);
    }

    // Draw radar sweep line (example static line at 0 degrees)
    painter.setPen(QPen(Qt::green, 2));
    painter.drawLine(center, QPoint(center.x(), center.y()-radius));
}

void RadarWidget::drawEntities(QPainter &painter)
{
    // Example drawing - you should replace with actual entity positions and colors

    // Draw blue (PX4) entities
    painter.setBrush(Qt::blue);
    painter.setPen(Qt::NoPen);
    QPoint center=rect().center();

    // Example: Draw a blue blip 100 px above center
    painter.drawEllipse(center+QPoint(0, -100), 5, 5);

    // Draw red (External) entities

    painter.setBrush(Qt::red);

    // Example: Draw a red blip 100 px to the right
    painter.drawEllipse(center+QPoint(100, 0), 5, 5);
}


