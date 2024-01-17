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

#include <qobject.h>
#include <QPushButton>

#include <QFileDialog>
#include <QString>
#include <QMessageBox>

#include <QDebug>


SM_MainWindow::SM_MainWindow(QWidget* parent)
    :QMainWindow(parent)
    , view(this)
    , prefDial(nullptr)
    
{
    connect(view.MenuBar->prefAct, &QAction::trigger,
        this, &SM_MainWindow::on_prefAct_trigger);
   

}

SM_MainWindow::~SM_MainWindow()
{
    
}

void SM_MainWindow::on_prefAct_trigger()
{

}

