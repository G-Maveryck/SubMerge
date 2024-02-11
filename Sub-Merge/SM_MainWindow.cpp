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
	Main Window class implementation.
*/

#include "SM_MainWindow.h"
#include "DebugMacro.h"
#include "Audio_player.h"
#include "TimelineFrame.h"
#include "PrefDialog.h"

#include <qobject.h>
#include <QPushButton>

#include <QFileDialog>
#include <QString>
#include <QMessageBox>

#include <QDebug>
#include <qsettings.h>
#include <qapplication.h>
#include "SearchResultModel.h"


SM_MainWindow::SM_MainWindow(QWidget* parent)
	:QMainWindow(parent)
	, view(this)
	, SearchResultsMod(new SearchResultModel(this))
	, settings(new QSettings(this))
{
	view.TableResults->setModel(SearchResultsMod);


	connect(view.MenuBar->openPrefsAct, &QAction::triggered,
		this, &SM_MainWindow::on_prefAct_trigger);

	connect(view.MenuBar->openAct, &QAction::triggered,
		this, &SM_MainWindow::on_OpenFile_triggered);
}

SM_MainWindow::~SM_MainWindow()
{
	
}

void SM_MainWindow::on_prefAct_trigger()
{
	PrefDialog* prefDial(new PrefDialog(this));
	
	int prefReturnVal = prefDial->exec();
	switch (prefReturnVal)
	{
	case 0:		// Rejected case
		//do noting, just returns.
		QLOG("Rejected, shit yourself");
		break;

	case 1:		// Accepted case
		// do someting, store settings in QSettings, reload some things, etc..
		QLOG("Accepted, Updated setting, closing Dialog");
		break;

	default:
		QLOG("Fart.");
		break;
	}

		// Free the memory before exiting the scope.
	delete prefDial;
}

void SM_MainWindow::on_OpenFile_triggered()
{
	QString filePath = 
		QFileDialog::getOpenFileName(
		this,						// Parent
		tr("Open file"),			// Caption
		tr("D:/"),					// Directory
		tr("All Files (*.*)") );	// Filter

	QLOG(filePath);
}

