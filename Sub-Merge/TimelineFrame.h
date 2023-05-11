/*

*/

#ifndef TIMELINE_FRAME_H
#define TIMELINE_FRAME_H



#include <QFrame>
#include <QBoxLayout>
#include <qline.h>

#include "WaveformWidget.h"


class TimelineFrame :
    public QFrame
{
    Q_OBJECT

public:
    TimelineFrame(QWidget* parent = nullptr);
    ~TimelineFrame();

    void setPlayHeadPosition(int position);
    void on_DurationChange(int duration);

protected:
    virtual void paintEvent(QPaintEvent* event);
    virtual void resizeEvent(QResizeEvent* event);


private:
    int scaleXFactor;     // Scale factor for positionning the playhead correctly

    QVBoxLayout* m_layout;
    WaveformWidget* m_testWidget;   // test
    
    QLine playHead;
};

#endif