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
    Main Window class Controller.
    This class is the main controller of the application.
    This contain the connection between UI signal and controller slots.
    Also contain the Slots definitions, intended to be the "back-end" of the application

*/

#ifndef SUBMERGE_H
#define SUBMERGE_H


#include <QtWidgets/QMainWindow>
#include <qsettings.h>

#include "SM_MainWindow_UI.h"
#include "PrefDialog.h"

#include "Audio_player.h"
#include "FocusedFile.h"
#include "SearchResultModel.h"


class SM_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    SM_MainWindow(QWidget *parent = (QWidget*)nullptr);
    ~SM_MainWindow();                            

protected:
    void on_prefAct_trigger();
    void on_OpenFile_triggered();

private:
    SM_MainWindow_UI view;      // View class (front-end)
    SearchResultModel* SearchResultsMod;
    
    QSettings* settings;

};



#endif // !SUBMERGE_H