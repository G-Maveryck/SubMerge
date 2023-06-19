#include "AudioFileProperties.h"

#include "DebugMacro.h"


AudioFileProperties::AudioFileProperties(const QString& filePath, QObject* parent) :
		QFileInfo(filePath),
		m_fileRef(new TagLib::FileRef(filePath.toStdString().c_str()) ),
		m_properties{}
{

	fillPropertiesStruct();

	QLOG("AudioFileProperties constructed !");
	QLOG("Properties : ");
	QLOG("Channels count = " << m_properties.channelCount);
	QLOG("Bitrate = " << m_properties.bitRate);
	QLOG("Duration = " << m_properties.duration);
	QLOG("Sample Rate = " << m_properties.sampleRate);
	QLOG("Total Samples per channels = " << m_properties.channelSamplesCount);
	QLOG("Total Samples = " << m_properties.totalSamplesCount);
	QLOG("File Path = " << m_properties.path);

	
}

AudioFileProperties::~AudioFileProperties()
{
	delete m_fileRef;
}



AudioProperties AudioFileProperties::getAudioProperties()
{
	return m_properties;
}

inline void AudioFileProperties::fillPropertiesStruct()
{
	m_properties.path = canonicalFilePath();
				
	m_properties.channelCount = m_fileRef->audioProperties()->channels();
	m_properties.duration = m_fileRef->audioProperties()->lengthInMilliseconds();
	m_properties.sampleRate = m_fileRef->audioProperties()->sampleRate();
	m_properties.channelSamplesCount = m_properties.sampleRate * m_fileRef->audioProperties()->lengthInSeconds();
	m_properties.totalSamplesCount = m_properties.channelSamplesCount * m_properties.channelCount;
	m_properties.bitRate = m_fileRef->audioProperties()->bitrate();

}


void AudioFileProperties::clearProperties()
{
	m_properties.path = (QString)"";
				
	m_properties.channelCount = -1;
	m_properties.duration = -1;
	m_properties.sampleRate = -1;
	m_properties.channelSamplesCount = -1;
	m_properties.totalSamplesCount = -1;
	m_properties.bitRate = -1;

}