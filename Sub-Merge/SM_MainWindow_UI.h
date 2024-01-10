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


class SM_MainWindow_UI
{
public:
	SM_MainWindow_UI(QMainWindow* MainWindow);
	~SM_MainWindow_UI();

public:		// Ui objects declaration
	MainMenu* MenuBar;


private:
	QWidget* centralWidget;
		// Layout and containers instance for main UI.
	QFrame* F_upInfo;
	QFrame* F_playing;
	QGridLayout* centralLout;
	QGridLayout* F_up_Lout;
	QGridLayout* F_playing_Lout;


		// stored here for potential reuse. Not sure if it'll be usefull.
	QMainWindow* parentWindow;

};


#endif // !MAIN_WINDOW_UI_H