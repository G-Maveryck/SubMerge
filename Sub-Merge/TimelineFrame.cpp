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
	See the "TimelineFrame.h" file for more information.
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
		m_channelsNumber(0),
		m_Duration(1),

		m_layout(new QVBoxLayout),
		//m_testWidget(new WaveformWidget(this)),
		m_channelsWidget(0)
{
	m_layout->setContentsMargins(0, 0, 0, 0);
	m_layout->setSpacing(0);
	setLayout(m_layout);
	
	setBaseSize(QSize(200, 200));
	setMinimumSize(QSize(600, 200));
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);


	//m_layout->addWidget(m_testWidget);

}

TimelineFrame::~TimelineFrame(){}



void TimelineFrame::setPlayHeadPosition(int position)
{
	int newXPos = (position / m_scaleXFactor);

	m_playHead.setLine(
		newXPos, 0,		/* P1 : Start point coordinates */
		newXPos, height() );	/* P2 : End point coordinates */

	QLOG("new position : " << position);
	QLOG("new P1 : " << m_playHead.p1());
	QLOG("new P2 : " << m_playHead.p2());

		// Update view, call paintEvent and redraw the line with new coordinates.
	update();
	QLOG("View updated");
}

void TimelineFrame::on_DurationChanged(int duration)
{
		m_scaleXFactor = (duration / width());
		m_Duration = duration;

	QLOG("*** Duration Changed method ***");
	QLOG("Width : " << width());
	QLOG("new duration : " << duration);
	QLOG("new scaleXFactor : " << m_scaleXFactor);
	QLOG("*** Duration Changed Ended ***");
	QLOG(" ");

}

void TimelineFrame::setNewProperties(int channelNmb)
{
	m_channelsNumber = channelNmb;

	for (int i = 0; i < m_channelsNumber; i++)
	{
		m_channelsWidget.push_back(new WaveformWidget(this));
		m_layout->addWidget(m_channelsWidget.at(i));
	}
}


	// Implementation of event handling methods.

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

void TimelineFrame::resizeEvent(QResizeEvent* event)
{
	int newWidth = event->size().width();

	m_scaleXFactor = (m_Duration / newWidth);
	QLOG("m_Duration : " << m_Duration);
	QLOG("event new Size : " << newWidth);
	QLOG("New ScaleFactor" << m_scaleXFactor);

	if (m_scaleXFactor <= 0)
	{
		m_scaleXFactor = 1;		// Silly, but working...
	}

	QLine tmpLine(m_playHead);

	m_playHead.setP1(QPoint(tmpLine.x1(), 0) );
	m_playHead.setP2(QPoint(tmpLine.x2(), newWidth) );

	event->accept();
}

void TimelineFrame::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		int newPos = event->pos().x();
		setPlayHeadPosition(newPos);
		event->accept();

		emit userChangedPosition(newPos*m_scaleXFactor);
	}

}
