#ifndef SUBMERGE_H
#define SUBMERGE_H



#include <QtWidgets/QMainWindow>
#include "ui_SubMerge.h"

#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QAudioOutput>

class SM_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    SM_MainWindow(QWidget *parent = nullptr);    // Constructeur
    ~SM_MainWindow();                            // Destructeur


private slots:
    
    void on_PlayButton_Clicked();
    void on_PauseButton_Clicked();
    void on_OpenFile_triggered();
    void on_Slider_Postion_moved();



private:
    Ui::SubMergeClass ui;



    QUrl m_currentFilePath;
    QString m_currentFileName;

    QMediaPlayer* player;
    QAudioOutput* audioOutput;

};



#endif // !SUBMERGE_H