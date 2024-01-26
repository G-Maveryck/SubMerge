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
	This class implement the preferences dialog window.
	The user can set various preferences here, and it is stored into a QSettings.

	Temporary for now, it will evolve.
*/


#ifndef PREF_DIALOG_H
#define PREF_DIALOG_H


#include <qdialog.h>
#include <qgridlayout.h>
#include <qpushbutton.h>

#include <qsettings.h>


class PrefDialog : public QDialog
{
	Q_OBJECT

public:
	PrefDialog(QWidget* parent);
	~PrefDialog();

private:
		// UI Elements.
	QGridLayout* mainLayout;

	QPushButton* b_Reset;
	QPushButton* b_Accept;
	QPushButton* b_Exit;

	QSettings* settings;

};


#endif // !PREF_DIALOG_H