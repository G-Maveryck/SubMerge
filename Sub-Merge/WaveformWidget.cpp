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
	See the "WaveformWidget.h" file for more information.
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

WaveformWidget::~WaveformWidget() {}



void WaveformWidget::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);

	FOR_DEBUG(
		painter.setPen(QPen(Qt::red, 1, Qt::SolidLine, Qt::RoundCap) );
		painter.drawLine(0, (height() / 2), width(), (height() / 2));	// Draw central line for debug
		painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap) );
		painter.drawRect(0, 0, width() - 1, height() - 1);		// Draw bounding rect for debug
		)
	

}

