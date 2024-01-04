/* --------------------------------------------------------------------------------------
* Author : Gabriel Wulveryck.
* Year : 2023
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
    Main Window class header.
*/

#ifndef SUBMERGE_H
#define SUBMERGE_H

#include <QtWidgets/QMainWindow>
//#include "ui_SubMerge.h"
#include "SM_MainWindow_UI.h"

#include "Audio_player.h"
#include "TimelineFrame.h"
#include "FocusedFile.h"


class SM_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    SM_MainWindow(QWidget *parent = nullptr);    // Constructeur
    ~SM_MainWindow();                            // Destructeur



private:
    // Ui::SubMergeClass ui;
    SM_MainWindow_UI view;

};



#endif // !SUBMERGE_H