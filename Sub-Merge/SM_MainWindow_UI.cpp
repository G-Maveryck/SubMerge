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


#include "SM_MainWindow_UI.h"

#include <QLayout.h>
#include <qgridlayout.h>
		 
#include <qlabel.h>
#include <qsizepolicy.h>
#include <qmargins.h>
#include <qtableview.h>
#include <qheaderview.h>


SM_MainWindow_UI::SM_MainWindow_UI(QMainWindow* MainWindow = (QMainWindow*)nullptr)
	: parentWindow(MainWindow)
	
	// ui elements init
	, MenuBar(new MainMenu(MainWindow))

	, centralWidget(new QWidget(MainWindow))
	, centralLout(new QGridLayout(centralWidget))

	, f_Search(new QFrame(MainWindow))
	, f_Playing(new QFrame(MainWindow))
	, lout_search(new QGridLayout(f_Search))
	, lout_F_playing(new QGridLayout(f_Playing))
	, v_Splitter(new QSplitter(MainWindow))

	//UI Elements : Frame up / F_Search
	, searchBox(new QLineEdit(MainWindow))
	, TableResults(new QTableView(MainWindow))

	//UI Elements : Frame Down / F_Playing
	, lout_ControlBar(new QHBoxLayout(f_Playing))
	, Timeline(new TimelineFrame(MainWindow))

	//Playing Control
	, p_PlayPause(new QPushButton(MainWindow))
	, s_Volume(new QSlider(MainWindow))
	, l_TrackName(new QLabel(MainWindow))
	, TimeInfo(new TimecodeInfo(MainWindow))

{	
		// Configuring the main window
	if (MainWindow->objectName().isEmpty()) {
		MainWindow->setObjectName("SM_MainWindow");
	}
		//General window settings
	MainWindow->setWindowModality(Qt::ApplicationModal);
	MainWindow->setDockNestingEnabled(true);		//MacOS feature only
	MainWindow->resize(1200, 720);		//tmp Size
	MainWindow->setMinimumSize(480, 260);

	MainWindow->setWindowFlags(MainWindow->windowFlags() | 
		Qt::CustomizeWindowHint |
		Qt::WindowMinimizeButtonHint |
		Qt::WindowMaximizeButtonHint |
		Qt::WindowCloseButtonHint
	);

	MainWindow->setWindowTitle("SubMerge - Version 0.0.1");

	
	//--------------------------------------------------


		//Begin building UI.
		
		//Define the global Content Margin policy for the main window. Will be reused.
	QMargins globalContentMargin(0, 0, 0, 0);

	MainWindow->setMenuBar(MenuBar);
	centralLout->setContentsMargins(2, 2, 2, 2);
	centralWidget->setContentsMargins(globalContentMargin);
	MainWindow->setCentralWidget(centralWidget);


		//Frame up building : Search bar and TableView for search results.
	searchBox->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
	searchBox->setMinimumSize(300, 10);
	searchBox->setPlaceholderText("Search...");

	QSpacerItem* spacerSearch(new QSpacerItem(400, 50, 
		QSizePolicy::Expanding, QSizePolicy::Fixed)
	);

	TableResults->setSelectionBehavior(QAbstractItemView::SelectRows);
	TableResults->setSortingEnabled(true);
	TableResults->horizontalHeader()->setSectionsMovable(true);
	

	lout_search->setContentsMargins(3,3,3,3);
	lout_search->addWidget(searchBox, 0, 0);
	lout_search->addItem(spacerSearch, 0, 1);
	lout_search->addWidget(TableResults, 1, 0, 1, 2);

	f_Search->setLayout(lout_search);
	f_Search->setBaseSize(1200, 500);
	f_Search->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

		
	// ----------------------------------------------------------------------
	

		// Bottom Frame building : Playing control and timeline.

		// Playing control bar layout : configuring widgets
	QSizePolicy policyControlBar(QSizePolicy::Fixed, QSizePolicy::Fixed);
	QSize sizeControlBar(50, 30);
	
	p_PlayPause->setText("Play");
	p_PlayPause->setFixedSize(sizeControlBar);
	p_PlayPause->setSizePolicy(policyControlBar);

	s_Volume->setOrientation(Qt::Horizontal);
	s_Volume->setToolTip("Volume control");
	s_Volume->setMinimum(0);
	s_Volume->setMaximum(100);
	s_Volume->setSliderPosition(80);
	s_Volume->setFixedSize(150, 20);
	s_Volume->setSizePolicy(policyControlBar);
	
	QSpacerItem* spacerControlBar1(new QSpacerItem(
		50, 50, QSizePolicy::Fixed, QSizePolicy::Fixed)
		);

	l_TrackName->setText("No file selected.");

	QSpacerItem* spacerControlBar2(new QSpacerItem(
		200, 50, QSizePolicy::Expanding, QSizePolicy::Fixed)
		);

	TimeInfo->setSizePolicy(policyControlBar);
	TimeInfo->setFixedSize(200, 40);


		// Insert widget in controlBar layout
	lout_ControlBar->setContentsMargins(globalContentMargin);

	lout_ControlBar->addWidget(s_Volume);
	lout_ControlBar->addWidget(p_PlayPause);

	lout_ControlBar->addItem(spacerControlBar1);
	lout_ControlBar->addWidget(l_TrackName);

	lout_ControlBar->addItem(spacerControlBar2);
	lout_ControlBar->addWidget(TimeInfo);

	
		//Timeline part
	Timeline->setBaseSize(720, 200);
	Timeline->setMinimumSize(480, 150);
		
	lout_F_playing->setContentsMargins(1, 1, 1, 1);
	lout_F_playing->addLayout(lout_ControlBar, 0, 0);
	lout_F_playing->addWidget(Timeline, 1, 0);

	
	f_Playing->setBaseSize(720, 100);
	f_Playing->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
	f_Playing->setLayout(lout_F_playing);


		// Adding frame to splitter
	v_Splitter->setOrientation(Qt::Vertical);
	v_Splitter->setHandleWidth(10);
	v_Splitter->setCollapsible(0, false);

	v_Splitter->addWidget(f_Search);
	v_Splitter->addWidget(f_Playing);


		// Adding Splitter to central Layout
	centralLout->addWidget(v_Splitter, 0, 0);
	
	centralWidget->setLayout(centralLout);
}

SM_MainWindow_UI::~SM_MainWindow_UI()
{

}

