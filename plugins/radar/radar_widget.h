#pragma once
#include <QWidget>

class RadarWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RadarWidget(QWidget *parent=nullptr);
    ~RadarWidget();

    // Trigger radar display update (repaint)
    void updateRadarDisplay();

protected:
    // Override paint event to custom draw widget
    void paintEvent(QPaintEvent *event) override;

private:
    // Helper to draw radar background and sweep
    void drawRadarScreen(QPainter &painter);

    // Helper to draw all detected entities on radar
    void drawEntities(QPainter &painter);
};
