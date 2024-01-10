#pragma once

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
	QAction* prefAct;

		//Playback menu actions
	QAction* playpauseAct;

		//Help Menu init
	QAction* aboutAct;
private:
	QMenu* FileM;
	QMenu* PlaybackM;
	QMenu* HelpM;

};


