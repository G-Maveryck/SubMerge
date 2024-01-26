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
#include <qmessagebox.h>


TimelineFrame::TimelineFrame(QWidget* parent)
	: QFrame(parent)
	, m_layout(new QVBoxLayout)
	, m_selecBox(0, 0, -1, -1)
	, m_channelsWidget(0)
	, m_Cursor(0, 0, 0, height())		// Playhead position initialized at 0
	
	, m_Duration(-1)
	, m_scaleXFactor(-1.0f)				// Scale Factor set to -1, as default value (-1 = invalid)
	, m_channelsNumber(0)

	, hasSelection(false)
{
	m_layout->setContentsMargins(0, 0, 0, 0);
	m_layout->setSpacing(0);
	setLayout(m_layout);
}

TimelineFrame::~TimelineFrame(){}



void TimelineFrame::setCursorPosition(int positionMilisec)
{
		// Security check, to avoid moving before the scale if correctly determined.
	if (m_scaleXFactor == -1) {
		QLOG("Scale invalid, return");
		return;
	}

	int newXPos = milisecToPixel(positionMilisec);

	m_Cursor.setLine(
		newXPos, 0,				/* P1 : Start point coordinates */
		newXPos, height() );	/* P2 : End point coordinates */

	QLOG("new position : " << positionMilisec);
	QLOG("new P1 : " << m_Cursor.p1());

		// Update view, call paintEvent and redraw the line with new coordinates.
	update();
	QLOG("View updated");
}

void TimelineFrame::on_DurationChanged(int duration)
{
	if (duration != -1) {
		m_scaleXFactor = (duration / width());
		m_Duration = duration;

		QLOG("*** Duration Changed method ***");
		QLOG("Width : " << width());
		QLOG("new duration : " << duration);
		QLOG("new scaleXFactor : " << m_scaleXFactor);
		QLOG("*** Duration Changed Ended ***");
	}
}

void TimelineFrame::setNewProperties(int channelNmb)
{
	m_channelsNumber = channelNmb;

		// Check for the first call of this method.
		// Clear the vector and free the memory if previous widgets were instensiated.
	if (!m_channelsWidget.empty()) {
		for (int i = 0; i < m_channelsWidget.size(); i++) {
			delete m_channelsWidget.at(i);
		}

		m_channelsWidget.clear();
	}

		// Create one Widget per channel, and add it in the Timeline layout.
	for (int i = 0; i < m_channelsNumber; i++) {
		m_channelsWidget.push_back(new WaveformWidget(this));
		m_layout->addWidget(m_channelsWidget.at(i));
	}
}



	// Implementation of event handler.

	// PaintEvent will draw the "playhead / Cursor" at his current position,
	// and, if a selection is made by the user, it will draw the selected area.
void TimelineFrame::paintEvent(QPaintEvent* event)
{
	QPainter framePainter(this);
	
		// Draw a bounding rectangle in Debug config to visualize the size of the frame.
	FOR_DEBUG(	
		framePainter.setPen(QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap)); 
		framePainter.drawRect(0, 0, width()-1, height()-1); 
		)

		// Set a specific pen for drawing.
	framePainter.setPen(QPen(TOGGLE_ARG(Qt::red, Qt::cyan), 3, Qt::SolidLine, Qt::RoundCap));
	
		// If a selection is made, the m_selecBox will be valid, and we draw a 
		// rectangle corresponding to the selection.
	if (hasSelection == true) {
		FOR_DEBUG( framePainter.drawRect(m_selecBox); )

		framePainter.fillRect(m_selecBox, QColor(Qt::gray));
		QLOG("valid rect");
	}

		//draw the cursor with it's actual coordinates.
	framePainter.drawLine(m_Cursor);


	QLOG("Rectangle isEmpty() : " << m_selecBox.isEmpty() );

	QLOG("*** Paint Event Called ***");
}

void TimelineFrame::resizeEvent(QResizeEvent* event)
{
		int newWidth = event->size().width();
		
	// Check for a valid duration. We want to update the scaleFactor only
	// if a valid duration is set.
	if (m_Duration != -1) {
		m_scaleXFactor = (newWidth / m_Duration);
		QLOG("m_Duration : " << m_Duration);
		QLOG("event new Size : " << newWidth);
		QLOG("New ScaleFactor : " << m_scaleXFactor);
	}

	QLine tmpLine(m_Cursor);

	m_Cursor.setP1(QPoint(tmpLine.x1(), 0) );
	m_Cursor.setP2(QPoint(tmpLine.x2(), newWidth) );

		// Set the selection box height. It'll always be the height of the timeline.
	m_selecBox.setHeight(this->height());

	event->accept();
}


void TimelineFrame::mousePressEvent(QMouseEvent* event)
{
		// When the mouse leftMouseButton is pressed, we set the cursor where 
		// the user clicked, set the selection start point equally,
		// and emit signal to notify there is a change in position.

	if (event->button() == Qt::LeftButton) {
		int newPosX = event->pos().x();
	
			// Set cursor to the new X Coordinate : where the user clicked.
		setCursorPixelPos(newPosX);

		if (hasSelection == true && 
			// Check if the click happened outside of the selection.
			newPosX < m_selecBox.left() || newPosX > m_selecBox.right() ) 
		{
			resetSelection();
			m_selecBox.setLeft(newPosX);
		}
		// Set the selection start point.

		event->accept();
		emit userSetPosition(pixelToMilisec(newPosX));
	}
}

void TimelineFrame::mouseMoveEvent(QMouseEvent* event)
{
		// set the XCoordinate of the mouse while it's moving to set 
		// the end point of the selection.
	m_selecBox.setRight(event->position().x() );
	hasSelection = true;

	event->accept();
	update();
}

void TimelineFrame::mouseReleaseEvent(QMouseEvent* event)
{
	if (hasSelection == true) {
		// A Qpoint is used to represent the selection on one axis.
		// the X Coordinate of the QPoint represent the start point of the selection.
		// the Y Coordinate represent the end point of the selection.
		
		// left() method return x coordinate of the rectangle left edge.
		// right() method return x coordinate of the rectangle right edge.

		emit userSetSelection(QPoint(m_selecBox.left(), m_selecBox.right()) );
		QLOG("selection set and emited");
	}
}


inline void TimelineFrame::setCursorPixelPos(int xCoordinate)
{
		// Check if we stay inside the Frame bounding.
	if (xCoordinate >= width()) {
		return;
	}

		// Set the Cursor line to the new X coordinate, and update the view.
	m_Cursor.setLine(
		xCoordinate, 0,
		xCoordinate, height() );

	update();
}

inline void TimelineFrame::resetSelection()
{
		// Reset the selection to default parameters.
	m_selecBox.setLeft(0);
	m_selecBox.setWidth(-1);
	hasSelection = false;
}


	// Helper functions for convertions
inline int TimelineFrame::milisecToPixel(int _milisec)
{
	return (_milisec / m_scaleXFactor);
}

inline int TimelineFrame::pixelToMilisec(int _pixels)
{
	return (_pixels * m_scaleXFactor);
}

