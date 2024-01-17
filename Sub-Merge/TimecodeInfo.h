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
	Ui object used to show informations about the selected file.
	Show duration, current position of the playhed, duration of the selection,
	and audio format (Samplerate|Bitrate).

	Showed in this form (exemple) :
		|  96|24  |  00:15  |  00:08  |
		Selection :  00:02  |  00:10  |

	//----------------------------------------------------

	UI Hierarchy :

		TimeInfo
			|---QVBoxLayout
					|---QHboxLayout
					|		|---l_Format
					|		|---l_Duration
					|		|---l_Position
					|
					|---QHboxLayout
							|---l_SelText
							|---l_SelecLenght
							|---l_SelecEnd
*/



#ifndef TIMECODEINFO_H
#define TIMECODEINFO_H

	// Helper macro to avoid boilerplate.
#define CONFIGURE_LABEL(name) name->setFixedSize(labelsSize); name->setSizePolicy(labelsPolicy); name->setAlignment(Qt::AlignCenter);

#include <qwidget.h>
#include <QLayout.h>
#include <qlabel.h>


class TimecodeInfo : public QWidget
{
	Q_OBJECT

public:
	TimecodeInfo(QWidget* parent);
	~TimecodeInfo();

	// void setDuration(int newDuration);


protected:
	virtual void paintEvent(QPaintEvent* event);

private:
	QVBoxLayout* mainLayout;
	QHBoxLayout* topLayout;
	QHBoxLayout* botLayout;

	QLabel* l_Format;
	QLabel* l_Duration;
	QLabel* l_Position;
	QLabel* l_SelecText;
	QLabel* l_SelecLenght;
	QLabel* l_SelecEnd;


};


#endif // !TIMECODEINFO_H