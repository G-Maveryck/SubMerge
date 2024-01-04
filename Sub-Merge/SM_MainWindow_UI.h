#pragma once

#include<qlayout.h>
#include<QVBoxlayout>
#include<QHBoxlayout>
#include<qframe.h>

#include<qwidget.h>
#include<qpushbutton.h>
#include<qslider.h>

#include<qmenubar.h>
#include<qmainwindow.h>
#include<qsplitter.h>

#include<qsizepolicy.h>
#include<qaction.h>


class SM_MainWindow_UI
{
public:
	SM_MainWindow_UI(QMainWindow* MainWindow);
	~SM_MainWindow_UI();

public:
	QMainWindow* parentWindow;


};

