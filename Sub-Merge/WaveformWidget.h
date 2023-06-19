/* --------------------------------------------------------------------------------------
* Author : Gabriel Wulveryck.
* Year : 2023
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
    This is a widget made to display an audiowaveform.
    This one is "generic". The WaveformWidget is instanciated once for each
    audio channel in the file currently focused on, and visualized.
    Each instance will then display the waveform of his own channel.
*/

#ifndef WAVEFORM_WIDGET_H
#define WAVEFORM_WIDGET_H

#include "DebugMacro.h"
#include <QWidget>
#include <QPainter>
#include <QPen>
#include <qaudiodecoder.h>
#include <vector>

#include "AudioFileProperties.h"


class WaveformWidget :
    public QWidget
{
    Q_OBJECT

public:
    WaveformWidget(QWidget* parent = (QWidget*)nullptr);
    ~WaveformWidget();

    

protected:
    virtual void paintEvent(QPaintEvent* event);


private:
    int samplesPerPixels;        // How many samples per pixels, understandable as "resolution on X axis"

    FOR_DEBUG(QPen centralLinePen;)

    std::vector<QRect> m_WaveBars;
    
};



#endif // !WAVEFORM_WIDGET_H