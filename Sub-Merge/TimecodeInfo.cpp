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



#include "TimecodeInfo.h"

#include <qsizepolicy.h>
#include <qpainter.h>


	// Helper macro to avoid boilerplate.
#define TC_ZERO_VALUE "00:00.00"
#define TC_DEFAULT_VALUE "-"


TimecodeInfo::TimecodeInfo(QWidget* parent = (QWidget*)nullptr)
	: QWidget(parent)
	, mainLayout(new QGridLayout(this))

	, l_Format(new QLabel(this))
	, l_Duration(new QLabel(this))
	, l_Position(new QLabel(this))

	, l_SelecStart(new QLabel(this))
	, l_SelecLenght(new QLabel(this))
	, l_SelecEnd(new QLabel(this))
{
	l_Format->setAlignment(Qt::AlignCenter);
	l_Format->setText("|");
	l_Format->setToolTip("Audio format : Sample rate | Bit rate");

	l_Duration->setAlignment(Qt::AlignCenter);
	l_Duration->setText(TC_ZERO_VALUE);
	l_Duration->setToolTip("Duration of the current selected audio");

	l_Position->setAlignment(Qt::AlignCenter);
	l_Position->setText(TC_ZERO_VALUE);
	l_Position->setToolTip("Current position of the playhead");


	l_SelecStart->setAlignment(Qt::AlignCenter);
	l_SelecStart->setText(TC_DEFAULT_VALUE);
	l_SelecStart->setToolTip("Start Timecode of the selection");

	l_SelecLenght->setAlignment(Qt::AlignCenter);
	l_SelecLenght->setText(TC_ZERO_VALUE);
	l_SelecLenght->setToolTip("Total lenght of the selection");

	l_SelecEnd->setAlignment(Qt::AlignCenter);
	l_SelecEnd->setText(TC_DEFAULT_VALUE);
	l_SelecEnd->setToolTip("End Timecode of the selection");
	

	mainLayout->addWidget(l_Format, 0, 0);
	mainLayout->addWidget(l_Duration, 0, 1);
	mainLayout->addWidget(l_Position, 0, 2);

	mainLayout->addWidget(l_SelecStart, 1, 0);
	mainLayout->addWidget(l_SelecLenght, 1, 1);
	mainLayout->addWidget(l_SelecEnd, 1, 2);

	mainLayout->setContentsMargins(3, 3, 3, 3);
	setContentsMargins(0, 0, 0, 0);

	setLayout(mainLayout);
	
}

TimecodeInfo::~TimecodeInfo()
{
}

void TimecodeInfo::resetPositionInfo()
{
	// Reset all "cursor related" info to zero. 
	// Usefull when a new file is selected.

	l_Position->setText(TC_DEFAULT_VALUE);
	l_SelecLenght->setText(TC_DEFAULT_VALUE);
	l_SelecEnd->setText(TC_DEFAULT_VALUE);
}

void TimecodeInfo::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	
	painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap));
	painter.drawRect(0, 0, width() - 1, height() - 1);	//Bounding Rect

	painter.setPen(QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap));
	
	const int yMidPoint = height() / 2;
	painter.drawLine( 0, yMidPoint,		// Central Horizontal line
			width() - 1, yMidPoint );

		// Draw 2 vertical lines at 1/3 each
	const int rectDivisions(3);
	for (int i = 0; i < rectDivisions; i++) 
	{
		int xCoord = i * (width() / rectDivisions);
		painter.drawLine(xCoord, 0,
			xCoord, height() - 1
		);
	}

}
