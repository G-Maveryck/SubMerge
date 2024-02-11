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
	Main Menu class, that represent the Menu Bar. Inherit from QMenuBar
	Instanciate QActions and QMenu for each menu.
	Set properties, text, etc.

	QActions are public to be accessible from the MainWindow constructor,
	for connecting signals easily.
*/

#ifndef MAIN_MENU_H
#define MAIN_MENU_H


#include<qmainwindow.h>

#include<qmenubar.h>
#include<qmenu.h>
#include<qaction.h>
#include<qlist.h>


class MainMenu : public QMenuBar
{
	Q_OBJECT

public:
	MainMenu(QMainWindow* parent);
	~MainMenu();

public:		// Public Attribute for Signal connection
		//	File Menu
	QAction* openAct;
	QAction* closeAct;
	QAction* openPrefsAct;

		//Database Menu
	QAction* addDbAct;
	QAction* indexDirAct;

		//Playback menu actions
	QAction* playpauseAct;

		//Help Menu init
	QAction* aboutAct;


private:
	QMenu* FileM;
	QMenu* DatabaseM;
	QMenu* PlaybackM;
	QMenu* HelpM;

};


#endif // !MAIN_MENU_H