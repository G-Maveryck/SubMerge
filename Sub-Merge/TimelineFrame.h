/* --------------------------------------------------------------------------------------
* Author : Gabriel Wulveryck.
* Year : 2024
* for any information, please contact : wulveryck.gabriel@gmail.com
*
* This file is a part of the SubMerge project.
*
* SubMerge is a free software, and is published under the terms of the GNU General Public Licence, version 3.
* You can redistribute it and/or modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 3 of the License,
* or (at your option) any later version.
* You should have recived a copy of the licence with the project.
*
* SubMerge is distributed as a contribution to the open-source and free software community,
* in the hope it'll be usefull.
* SubMerge is distributed without ANY WARRANTY, without even the implied warranty
* of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* See the GNU General Public License for more details.
*
*-------------------------------------------------------------------------------------- */

/*
    This class inherit for the QFrame class.
    This is a graphical container for the WaveformWidgets.
    The TimelineFrame Class is meant to represent a Timeline, with a playhead,
    and displaying the Waveform of each audio channels underneath.
*/

#ifndef TIMELINE_FRAME_H
#define TIMELINE_FRAME_H

#include <qframe.h>
#include <qboxlayout.h>
#include <qline.h>
#include <qaudiodecoder.h>
#include <qfileinfo.h>
#include <vector>

#include "WaveformWidget.h"


class TimelineFrame : public QFrame
{
    Q_OBJECT

public:
    TimelineFrame(QWidget* parent = nullptr);
    ~TimelineFrame();

    void setPlayHeadPosition(int position);
    void on_DurationChanged(int duration);
    void setNewProperties(int channelNmb);
    int getWaveformWidth();

protected:
    virtual void paintEvent(QPaintEvent* event);
    virtual void resizeEvent(QResizeEvent* event);
    virtual void mousePressEvent(QMouseEvent* event);

signals:
    void userChangedPosition(int);

private:
    int m_Duration;
    int m_scaleXFactor;       // Scale factor for positionning the playhead correctly
    int m_channelsNumber;     // Number of channels of the current audio file played
    
    QVBoxLayout* m_layout;
    QLine m_playHead;
    
    std::vector<WaveformWidget*> m_channelsWidget;

    //WaveformWidget* m_testWidget;   // test
};

#endif
