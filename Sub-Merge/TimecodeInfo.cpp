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
#define SET_LABEL_PROPERTIES(name) name->setSizePolicy(labelsPolicy); name->setAlignment(Qt::AlignCenter);
#define TC_ZERO_VALUE "00:00.00"


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
	QSizePolicy labelsPolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

	SET_LABEL_PROPERTIES(l_Format)
	l_Format->setText("|");
	SET_LABEL_PROPERTIES(l_Duration)
	l_Duration->setText(TC_ZERO_VALUE);
	SET_LABEL_PROPERTIES(l_Position);
	l_Position->setText(TC_ZERO_VALUE);

	SET_LABEL_PROPERTIES(l_SelecStart);
	l_SelecStart->setText(TC_ZERO_VALUE);
	SET_LABEL_PROPERTIES(l_SelecLenght);
	l_SelecLenght->setText(TC_ZERO_VALUE);
	SET_LABEL_PROPERTIES(l_SelecEnd);
	l_SelecEnd->setText(TC_ZERO_VALUE);
	
	mainLayout->addWidget(l_Format, 0, 0);
	mainLayout->addWidget(l_Duration, 0, 1);
	mainLayout->addWidget(l_Position, 0, 2);

	mainLayout->addWidget(l_SelecStart, 1, 0);
	mainLayout->addWidget(l_SelecLenght, 1, 1);
	mainLayout->addWidget(l_SelecEnd, 1, 2);

	mainLayout->setContentsMargins(2, 2, 2, 2);
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

	l_Position->setText(TC_ZERO_VALUE);
	l_SelecLenght->setText(TC_ZERO_VALUE);
	l_SelecEnd->setText(TC_ZERO_VALUE);
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
