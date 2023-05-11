/*

*/


#include "WaveformWidget.h"
#include <QPainter>
#include <QSizePolicy>


WaveformWidget::WaveformWidget(QWidget* parent) :
	QWidget(parent)
{
	setBaseSize(50, 20);
	setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

	linePen = new QPen(Qt::red, 1, Qt::SolidLine, Qt::RoundCap);
	//linePen->setWidth(2);

}

WaveformWidget::~WaveformWidget(){}




void WaveformWidget::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);

	painter.setPen(*linePen);
	painter.drawLine(0, (height() / 2), width(), (height() / 2));

}