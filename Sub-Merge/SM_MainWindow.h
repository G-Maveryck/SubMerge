#ifndef SUBMERGE_H
#define SUBMERGE_H



#include <QtWidgets/QMainWindow>
#include "ui_SubMerge.h"

#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QAudioOutput>
#include <QFileInfo>
#include <QAudio>

#include "Audio_player.h"



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
    void on_Volume_changed(int volumePos);  // Change the audio
    void on_DurationChanged(int duration);
    void on_actionPlayPause_triggered();

        // Menu controls
    void on_OpenFile_triggered();

        // Timeline controls
    // void on_SliderPosition_moved(int newPosition);
    void on_playerProgress(int position);


private:
    Ui::SubMergeClass ui;

    QFileInfo* currentFileInfo;

    AudioPlayer* player;

   


private slots:
    void displayAudioDecodingError(QAudioDecoder::Error error); 
    // Prompt an error popup for an audio decoding error


    void displayAudioDeviceError(QAudio::Error error);
    // Prompt an error popup for an audio device error

};



#endif // !SUBMERGE_H