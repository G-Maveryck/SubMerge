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



#ifndef MAIN_WINDOW_UI_H
#define MAIN_WINDOW_UI_H


#include<qmainwindow.h>

#include<qwidget.h>
#include<qlayout.h>
#include<QVBoxlayout>
#include<QHBoxlayout>
#include<qframe.h>

#include<qpushbutton.h>
#include<qslider.h>
#include<qlabel.h>

#include<qsplitter.h>

#include<qsizepolicy.h>


#include"MainMenu.h"
#include"TimelineFrame.h"
#include"WaveformWidget.h"
#include"TimecodeInfo.h"


class SM_MainWindow_UI
{
public:
	SM_MainWindow_UI(QMainWindow* MainWindow);
	~SM_MainWindow_UI();

public:	
		// Ui objects declaration, public for being accessible to the controller
	MainMenu* MenuBar;

	QLabel* l_trackName;
	TimelineFrame* timeLine;

		//Playing Control objects
	QPushButton* p_PlayPause;
	QSlider* s_Volume;
	TimecodeInfo* TimeInfo;


private:
	QWidget* centralWidget;
	//QSplitter* playingSplitter;

		//Ui elements : Frame Up

		// Layout and containers instance for main UI.
	QFrame* F_search;
	QSplitter* v_Splitter;
	QFrame* F_playing;
	QGridLayout* centralLout;
	QHBoxLayout* lout_search;
	QGridLayout* lout_F_playing;
	QHBoxLayout* lout_ControlBar;


		// stored here for potential reuse. Not sure if it'll be usefull.
	QMainWindow* parentWindow;

};


#endif // !MAIN_WINDOW_UI_H