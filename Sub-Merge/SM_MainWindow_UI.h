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
	Seperated class for all UI definition and construction.
	This choise is made for "cleaning" the code, and have a proper seperation 
	between front-end and back-end / View and Controller.
	This class is intended to contain the View only.


	UI Hierachy :

	MainWindow
		|---CentralWidget			QWidget
			|---centralLayout		QGridLayout
				|---v_Splitter		QSplitter - Vertical
						|---f_Search					QFrame
						|		|---lout_Search			QGridLayout
						|				|---searchBox				QLineEdit
						|				|---spacerSearch			QSpacerItem
						|				|---SearchResults			QTableView
						|
						|---f_Playing					QFrame
								|---lout_F_playing					QGridLayout
									|---lout_ControlBar				QHLayout
									|		|---s_Volume			QSlider - Horizontal
									|		|---p_PlayPause			QPushButton
									|		|---spacerControlBar1	QSpacerItem
									|		|---l_TrackName			QLabel
									|		|---spacerControlBar2	QSpacerItem
									|		|---TimeInfo			QWidget
									|
									|---Timeline
								
*/



#ifndef MAIN_WINDOW_UI_H
#define MAIN_WINDOW_UI_H


#include <qmainwindow.h>
		 
#include <qwidget.h>
#include <qlayout.h>
#include <QVBoxlayout>
#include <QHBoxlayout>
#include <qsplitter.h>
#include <qsizepolicy.h>
#include <qsize.h>
		 
#include <qframe.h>
#include <qpushbutton.h>
#include <qslider.h>
#include <qlabel.h>
		 
#include <qlineedit.h>
#include <qtableview.h>
		 
#include <qpalette.h>
		 
#include "MainMenu.h"
#include "TimelineFrame.h"
#include "WaveformWidget.h"
#include "TimecodeInfo.h"


class SM_MainWindow_UI
{
public:
	SM_MainWindow_UI(QMainWindow* MainWindow);
	~SM_MainWindow_UI();

public:	
		// Ui objects declaration, public for being accessible to the controller
	MainMenu* MenuBar;

		// F_Search Objects
	QLineEdit* searchBox;
	QTableView* TableResults;

		//F_playing objects
		//Playing ControlBar objects
	QSlider* s_Volume;
	QPushButton* p_PlayPause;
	QLabel* l_TrackName;
	TimecodeInfo* TimeInfo;

	TimelineFrame* Timeline;


private:
	QWidget* centralWidget;
	
		// Containers instance for main UI.
	QSplitter* v_Splitter;
	QFrame* f_Search;
	QFrame* f_Playing;

		// Layout
	QGridLayout* centralLout;
	QGridLayout* lout_search;
	QGridLayout* lout_F_playing;
	QHBoxLayout* lout_ControlBar;

		// stored here for potential reuse. Not sure if it'll be usefull.
	QMainWindow* parentWindow;

	

};


#endif // !MAIN_WINDOW_UI_H