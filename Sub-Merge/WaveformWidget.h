/*

*/


#ifndef WAVEFORM_WIDGET_H
#define WAVEFORM_WIDGET_H


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
    QPen* linePen;

};

#endif // !WAVEFORM_WIDGET_H