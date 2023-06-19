#ifndef AUDIO_FILE_PROPERTIES
#define AUDIO_FILE_PROPERTIES


#include <qfileinfo.h>
#include <taglib/fileref.h>
#include <string>


struct AudioProperties      // Struct to store and handle audio properties.
{
    int channelCount;       // Number of audio channels
    int duration;           // Duration of the audio in millisec
    int sampleRate;         // Sample rate of the audio stream (samples/sec)
    int channelSamplesCount;// Total number of samples per channels in the audio (= frameCount)
    int totalSamplesCount;  // Total number of samples in the audio 
    int bitRate;            // Bits per samples

    QString path;       // Path of the original file on the file system.
};

class AudioFileProperties :
    public QFileInfo
{
    

public:
    AudioFileProperties(const QString& filePath, QObject* parent = nullptr);
    virtual ~AudioFileProperties();

    AudioProperties getAudioProperties();

protected:
    inline void fillPropertiesStruct();
    void clearProperties();

private:
    TagLib::FileRef* m_fileRef;
    AudioProperties m_properties;

};

#endif // !AUDIO_FILE_PROPERTIES
