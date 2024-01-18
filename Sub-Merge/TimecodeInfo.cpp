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


TimecodeInfo::TimecodeInfo(QWidget* parent = (QWidget*)nullptr)
	: QWidget(parent)
	, mainLayout(new QVBoxLayout(this))
	, topLayout(new QHBoxLayout(this))
	, botLayout(new QHBoxLayout(this))

	, l_Format(new QLabel(this))
	, l_Duration(new QLabel(this))
	, l_Position(new QLabel(this))
	, l_SelecText(new QLabel(this))
	, l_SelecLenght(new QLabel(this))
	, l_SelecEnd(new QLabel(this))
{
	QSizePolicy labelsPolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	QSize labelsSize(50, 20);


	//l_Format->setAlignment(Qt::AlignHCenter);
	INIT_LABEL(l_Format)
	l_Format->setText("|");
	INIT_LABEL(l_Duration)
	l_Duration->setText(TC_ZERO_VALUE);
	INIT_LABEL(l_Position);
	l_Position->setText(TC_ZERO_VALUE);
	
	topLayout->addWidget(l_Format);
	topLayout->addWidget(l_Duration);
	topLayout->addWidget(l_Position);


	INIT_LABEL(l_SelecText);
	l_SelecText->setText("Selection:");
	INIT_LABEL(l_SelecLenght);
	l_SelecLenght->setText(TC_ZERO_VALUE);
	INIT_LABEL(l_SelecEnd);
	l_SelecEnd->setText(TC_ZERO_VALUE);

	botLayout->addWidget(l_SelecText);
	botLayout->addWidget(l_SelecLenght);
	botLayout->addWidget(l_SelecEnd);


	mainLayout->addLayout(topLayout);
	mainLayout->addLayout(botLayout);

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
