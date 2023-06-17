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
#include "ui_SubMerge.h"

#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QAudioOutput>
#include <QFileInfo>
#include <QAudio>

#include "Audio_player.h"
#include "TimelineFrame.h"


class SM_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    SM_MainWindow(QWidget *parent = nullptr);    // Constructeur
    ~SM_MainWindow();                            // Destructeur


public slots:
        // Mediaplayer control
    void on_PlayButton_Clicked();   // Start audio playing
    void on_PauseButton_Clicked();  // Pause audio playing
    void on_Volume_changed(int volumePos);  // Change the audio output volume
    void on_DurationChanged(int duration);  // make the slider fit the duration of the audio file
    void on_actionPlayPause_triggered();    // Play or pause the Audio when hitting space-bar

        //Controls for pitch and time
    void on_sliderPitch_moved(int pitchPosition);
    void on_sliderTime_moved(int timePosition);
        
        // Menu controls
    void on_OpenFile_triggered();   // Open a new file and start playing it.

        // Timeline controls
    // void on_SliderPosition_moved(int newPosition);
    void on_playerProgress(int position);   // make the slider move as the player progress.


private:
    Ui::SubMergeClass ui;

    QFileInfo* currentFileInfo;
    AudioPlayer* player;

    TimelineFrame* Timeline;
    

private slots:
    void displayAudioDecodingError(QAudioDecoder::Error error);     // Prompt an error popup for an audio decoding error
    void displayAudioDeviceError(QAudio::Error error);  // Prompt an error popup for an audio device error
    

};



#endif // !SUBMERGE_H