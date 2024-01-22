#include "MainMenu.h"

#include<qmenubar.h>
#include<qmenu.h>
#include<qaction.h>
#include<qsizepolicy.h>


MainMenu::MainMenu(QMainWindow* parent = (QMainWindow*)nullptr)
	:QMenuBar(parent)
		//Menus init
	,FileM(new QMenu("Files", this))
	,PlaybackM(new QMenu("Playback", this))
	,HelpM(new QMenu("Help", this))

		// File menu actions initialization
	,openAct(new QAction("Open", this))
	,closeAct(new QAction("Close", this))
	,prefAct(new QAction("Preferences", this))
		//Playback Menu actions init
	,playpauseAct(new QAction("Play-Pause", this))
		// Help Menu actions init
	,aboutAct(new QAction("About SubMerge", this))
{
	FileM->addAction(openAct);
	FileM->addAction(closeAct);
	FileM->addSeparator();
	FileM->addAction(prefAct);

	PlaybackM->addAction(playpauseAct);

	HelpM->addAction(aboutAct);


	addMenu(FileM);
	addMenu(PlaybackM);
	addMenu(HelpM);

}

MainMenu::~MainMenu()
{
}

