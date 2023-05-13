/*

*/

#include "TimelineFrame.h"
#include "DebugMacro.h"

#include <qsizepolicy.h>
#include <qpen.h>
#include <qpainter.h>
#include <qevent.h>
#include <qline.h>

#include <qdebug.h>


TimelineFrame::TimelineFrame(QWidget* parent) :
		QFrame(parent),
		m_playHead(0, 0, 0, height()),	// Playhead position set to 0.
		m_scaleXFactor(1),				// Scale Factor set to 1, as default value
		m_channelsNumber(0)
{
	m_layout = new QVBoxLayout;
	m_layout->setContentsMargins(0, 0, 0, 0);
	setLayout(m_layout);
	
	setBaseSize(QSize(200, 200));
	setMinimumSize(QSize(600, 200));
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);


	m_testWidget = new WaveformWidget(this);
	m_layout->addWidget(m_testWidget);
	
}

TimelineFrame::~TimelineFrame(){}



void TimelineFrame::setPlayHeadPosition(int position)
{
	int newXPos = (position / m_scaleXFactor);
	m_playHead.setLine(newXPos, 0,		/* P1 : Start point coordinates */
					newXPos, height());	/* P2 : End point coordinates */

	QLOG("new position : " << position);
	QLOG("new P1 : " << m_playHead.p1());
	QLOG("new P2 : " << m_playHead.p2());

		// Update view, call the paintEvent and redraw the line with new coordinates.
	update();
	QLOG("View updated");
}

void TimelineFrame::on_DurationChange(int duration)
{
	m_scaleXFactor = (duration / width());

	QLOG("*** Duration Changed method ***");
	QLOG("Width : " << width());
	QLOG("new duration : " << duration);
	QLOG("new scaleXFactor : " << m_scaleXFactor);
	QLOG("*** Duration Changed Ended ***");
	

}

void TimelineFrame::setChannelsNumber(int newChannelsNumber)
{
	m_channelsNumber = newChannelsNumber;


}


void TimelineFrame::resizeEvent(QResizeEvent* event)
{
	m_playHead.setP2( QPoint(0, height()) );
	
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
	framePainter.drawLine(m_playHead);

	QLOG("*** Paint Event Called ***");
}

