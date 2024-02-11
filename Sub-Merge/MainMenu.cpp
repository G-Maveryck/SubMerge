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
	Implementation of the MenuBar.
*/

#include "MainMenu.h"

#include<qmenubar.h>
#include<qmenu.h>
#include<qaction.h>
#include<qsizepolicy.h>


MainMenu::MainMenu(QMainWindow* parent = (QMainWindow*)nullptr)
	: QMenuBar(parent)
		//Menus init
	, FileM(new QMenu("Files", this))
	, DatabaseM(new QMenu("Database", this))
	, PlaybackM(new QMenu("Playback", this))
	, HelpM(new QMenu("Help", this))
	  
	 	// File menu actions initialization
	, openAct(new QAction("Open", this))
	, closeAct(new QAction("Close", this))
	, openPrefsAct(new QAction("Preferences", this))

	 	//Playback Menu actions init
	, playpauseAct(new QAction("Play-Pause", this))

		//Database Menu actions init
	, addDbAct(new QAction("Add existing Database", this))
	, indexDirAct(new QAction("Index Directory", this))

	 	// Help Menu actions init
	, aboutAct(new QAction("About SubMerge", this))
{
		// File Menu
	FileM->addAction(openAct);
	FileM->addAction(closeAct);
	FileM->addSeparator();
	FileM->addAction(openPrefsAct);

		// Database Menu
	DatabaseM->addAction(addDbAct);
	DatabaseM->addAction(indexDirAct);

		// PlayBack Menu
	PlaybackM->addAction(playpauseAct);

		// Help Menu
	HelpM->addAction(aboutAct);


	addMenu(FileM);
	addMenu(DatabaseM);
	addMenu(PlaybackM);
	addMenu(HelpM);

}

MainMenu::~MainMenu()
{
}

