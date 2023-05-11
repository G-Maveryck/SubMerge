/*

*/

#include "TimelineFrame.h"

#include <QSizePolicy>
#include <QPen>
#include <qpainter.h>
#include <qevent.h>
#include <qline.h>

#include <qdebug.h>
#include "DebugMacro.h"





TimelineFrame::TimelineFrame(QWidget* parent) :
		QFrame(parent),
		playHead(0, 0, 0, height()),
		scaleXFactor(1)
{
	m_layout = new QVBoxLayout;
	setLayout(m_layout);
	
	//setFixedSize(QSize(200, 200));
	setBaseSize(QSize(200, 200));
	setMinimumHeight(200);
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

	m_testWidget = new WaveformWidget(this);
	m_layout->addWidget(m_testWidget);


	// playHead = new QLine(0, 0, 0, height());

}

TimelineFrame::~TimelineFrame(){}



void TimelineFrame::setPlayHeadPosition(int position)
{
		int newXPos = (position / scaleXFactor);
		playHead.setP1(QPoint(newXPos, 0) );			/* Start point coordinates */
		playHead.setP2(QPoint(newXPos, height()) ); /* End point coordinates */

		QLOG("new position : " << position);
		QLOG("new P1 : " << playHead.p1());
		QLOG("new P2 : " << playHead.p2());

		update();
		QLOG("View updated");

	
}

void TimelineFrame::on_DurationChange(int duration)
{
		scaleXFactor = (duration / width());

		QLOG("*** Duration Changed method ***");
		QLOG("Width : " << width());
		QLOG("new duration : " << duration);
		QLOG("new scaleXFactor : " << scaleXFactor);
	
}



void TimelineFrame::resizeEvent(QResizeEvent* event)
{
	// (event->size());
	playHead.setP2( QPoint(0, height()) );
	
}


void TimelineFrame::paintEvent(QPaintEvent* event)
{
	QPainter framePainter(this);
	
		// Draw a bounding rectangle in Debug config to visualize the size of the frame.
	FOR_DEBUG(	
		framePainter.setPen(QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap)); 
		framePainter.drawRect(0, 0, width()-1, height()-1); 
		)

		// Set a specific pen and draw the playhead line, with the good coordinates.
	framePainter.setPen(QPen(Qt::red, 5, Qt::SolidLine, Qt::RoundCap));
	framePainter.drawLine(playHead);

	QLOG("***Paint Event Called***");
}

