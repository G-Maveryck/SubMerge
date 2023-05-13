/*

*/


#ifndef WAVEFORM_WIDGET_H
#define WAVEFORM_WIDGET_H

#include "DebugMacro.h"
#include <QWidget>
#include <QPainter>
#include <QPen>


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
    FOR_DEBUG( QPen centralLinePen;)

};



#endif // !WAVEFORM_WIDGET_H