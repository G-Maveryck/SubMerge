/*

*/


#include "WaveformWidget.h"
#include <QPainter>
#include <QSizePolicy>

#include "DebugMacro.h"


WaveformWidget::WaveformWidget(QWidget* parent) :
	QWidget(parent)
{
	setBaseSize(50, 20);
	setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

	

}

WaveformWidget::~WaveformWidget(){}




void WaveformWidget::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);

	FOR_DEBUG(
		painter.setPen(QPen(Qt::red, 1, Qt::SolidLine, Qt::RoundCap) );
		painter.drawLine(0, (height() / 2), width(), (height() / 2));	// Draw central line for debug
		painter.drawRect(0, 0, width() - 1, height() - 1);		// Draw bounding rect for debug
		)
	

}