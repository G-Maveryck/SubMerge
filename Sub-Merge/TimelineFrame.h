/*

*/

#ifndef TIMELINE_FRAME_H
#define TIMELINE_FRAME_H



#include <qframe.h>
#include <qboxlayout.h>
#include <qline.h>
#include <vector>

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
    void setChannelsNumber(int newChannelsNumber);

protected:
    virtual void paintEvent(QPaintEvent* event);
    virtual void resizeEvent(QResizeEvent* event);


private:
    int m_scaleXFactor;       // Scale factor for positionning the playhead correctly
    int m_channelsNumber;     // Number of channels of the current audio file played

    QVBoxLayout* m_layout;
    WaveformWidget* m_testWidget;   // test
    std::vector<WaveformWidget> m_vectChannelWaveform;
    
    QLine m_playHead;
};

#endif