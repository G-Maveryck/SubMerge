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
	, m_selecBox(1, 1, -1, (height() - 1))
	, m_channelsWidget(0)
	, m_Cursor(0, 0, 0, (height()-1) )		// Playhead position initialized at 0
	
	, m_Duration(-1)
	, m_scaleXFactor(-1.0f)				// Scale Factor set to -1, as default value (-1 = invalid)
	, m_channelsNumber(0)

	, hasSelection(false)
	, selectionSent(false)
	, selecFirstPoint(-1)
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

	setCursorPixelPos(milisecToPixel(positionMilisec));

	QLOG("new position : " << positionMilisec);
	QLOG("new P1 : " << m_Cursor.p1());
	update();
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

void TimelineFrame::paintEvent(QPaintEvent* event)
	// PaintEvent will draw the "playhead / Cursor" at his current position,
	// and, if a selection is made by the user, it will draw the selected area.
{
	QLOG("*** Paint Event Called ***");
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
		QLOG("Selection is made.");
		FOR_DEBUG( framePainter.drawRect(m_selecBox); )

		framePainter.fillRect(m_selecBox, QColor(Qt::gray));
	}

		//draw the cursor with it's actual coordinates.
	framePainter.drawLine(m_Cursor);

	QLOG("Rectangle isEmpty() : " << m_selecBox.isEmpty() );

	QLOG("*** Paint Event Returned ***");
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
	m_selecBox.setHeight( this->height() - 1 );

	event->accept();
	update();
}


void TimelineFrame::mousePressEvent(QMouseEvent* event)
{
	// When the leftMouseButton is pressed, we set the cursor where 
	// the user clicked, set the selection first point equally,
	// and emit signal to notify there is a change in position.

	if (event->button() == Qt::LeftButton) {
		int newPosX = event->pos().x();		// store position on the stack for readability
	
			// Set cursor to the new X Coordinate : where the user clicked.
		setCursorPixelPos(newPosX);

		selecFirstPoint = newPosX;
			// Check if a selection already exist AND
			// if the click happened outside of the selection.
		if (hasSelection == true	&& 
			newPosX < m_selecBox.left() || newPosX > m_selecBox.right() ) 
		{
			resetSelection();
		}

		event->accept();
		emit userSetPosition(pixelToMilisec(newPosX));
		update();
	}
}	// !mousePressEvent

void TimelineFrame::mouseMoveEvent(QMouseEvent* event)
{
		// set the XCoordinate of the mouse while it's moving to set 
		// the end point of the selection.

	int mousePosX = event->pos().x();
	if ( 1 < mousePosX > width()-1 ) {
		return;
	}

		// Check if the mouse is moving left to right. ( -> )
		// If so, we set the right edge of the selection box to the mouse position.
	if (mousePosX >= (selecFirstPoint+10) ) {
		m_selecBox.setLeft(selecFirstPoint);
		m_selecBox.setRight(mousePosX);
	}
		// Check if the mouse is moving right to left ( <- ).
		// if so, we move the Left edge of the selection box.
	else if (mousePosX <= (selecFirstPoint-10) )
	{
		m_selecBox.setRight(selecFirstPoint);
		m_selecBox.setLeft(mousePosX);
		setCursorPixelPos(mousePosX);
	}
	
	hasSelection = true;
	selectionSent = false;

	event->accept();
	update();
}

void TimelineFrame::mouseReleaseEvent(QMouseEvent* event)
{
		// A Qpoint is used to represent the selection on one axis.
		// the X Coordinate of the QPoint represent the start point of the selection.
		// the Y Coordinate represent the end point of the selection.
		
		// left() method return x coordinate of the rectangle left edge.
		// right() method return x coordinate of the rectangle right edge.
	
	if (event->button() != Qt::LeftButton) {
		return;
	}

	if (hasSelection == true && selectionSent == false) {
		emit userSetSelection(QPoint(
			pixelToMilisec(m_selecBox.left()), pixelToMilisec(m_selecBox.right()) 
			) 
		);

		selectionSent = true;
		QLOG("selection set and emited");
	}
}


inline void TimelineFrame::setCursorPixelPos(int xCoordinate)
{
		// Check if we stay inside the Frame bounding.
	if (xCoordinate >= width()) {
		QLOG("Cursor outside widget bounding, return");
		return;
	}

		// Set the Cursor line to the new X coordinate, and update the view.
	m_Cursor.setLine(
		xCoordinate, 0,
		xCoordinate, this->height() );

	
}

inline void TimelineFrame::resetSelection()
{
		// Reset the selection to default parameters.
	m_selecBox.setLeft(0);
	m_selecBox.setWidth(-1);
	hasSelection = false;
	selectionSent = false;
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

