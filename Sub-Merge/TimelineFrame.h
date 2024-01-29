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
	This class inherit for the QFrame class.
	This is a graphical container for the WaveformWidgets.
	The TimelineFrame Class is meant to represent a Timeline, with a playhead,
	and displaying the Waveform of each audio channels underneath.
*/

#ifndef TIMELINE_FRAME_H
#define TIMELINE_FRAME_H

#include <qframe.h>
#include <qboxlayout.h>
#include <qline.h>
#include <qaudiodecoder.h>
#include <qfileinfo.h>
#include <vector>

#include "WaveformWidget.h"


class TimelineFrame : public QFrame
{
	Q_OBJECT

public:
	TimelineFrame(QWidget* parent = nullptr);
	~TimelineFrame();

	void setCursorPosition(int positionMilisec);// Set the playing cursor position. Position in millisec.
	void on_DurationChanged(int duration);		// set duration of new track 
	void setNewProperties(int channelNmb);


protected:
	virtual void paintEvent(QPaintEvent* event);
	virtual void resizeEvent(QResizeEvent* event);
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void mouseMoveEvent(QMouseEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* event);

	inline void setCursorPixelPos(int xCoordinate);	// Set the cursor position to a specific x coordinate, in pixels.
	inline void resetSelection();


		// Helper functions for managing convertion from/to pixels and milisec.
	inline int milisecToPixel(int _milisec);
	inline int pixelToMilisec(int _pixels);


signals:
	void userSetPosition(int newPostion);		// emitted when the user move the Cursor/playhead. Position emited is in milisec.
	void userSetSelection(QPoint newSlection);


private:
		// UI Elements
	QVBoxLayout* m_layout;
	std::vector<WaveformWidget*> m_channelsWidget;

	QLine m_Cursor;			// Line used to represent the Cursor/Playhead. It's draw in the paintEven.
	QRect m_selecBox;		// Rectangle used to draw visualy the selection on the timeline
							// Start position of the user selection in PIXELS
							// End position of the user selection in PIXELS


		// Attributes section
	int m_Duration;			// Duration of the current focused track in milisec.
	int m_channelsNumber;	// Number of channels of the current audio file played
	 
	int m_scaleXFactor;		// Scale factor for positionning the playhead correctly
	// understandable as "How many milisec per pixels" ?
	// Multiplying by this number, we convert pixel TO milisec.
	// Dividing by this number, we convert millisec TO pixel.
	// Iy's used by the two Helper function milisecToPixel and pixelToMilisec.
	

		//Selection parameters
	bool hasSelection;		// Flag for checking if the user has made a selection.
	bool selectionSent;		// Flag used to avoid emitting multiple signals for the same selection. 
							// Happend when user click inside the selection. 
	int selecFirstPoint;
	//WaveformWidget* m_testWidget;   // test
};

#endif
