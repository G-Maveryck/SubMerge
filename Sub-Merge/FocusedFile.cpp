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

*/

#include "FocusedFile.h"

FocusedFile::FocusedFile(QObject* parent) :
	QObject(parent),
	// cachedBuffers(0, QAudioBuffer()),
	m_Processor(new ProcessThread),
	m_FileInfo(new QFileInfo()),
	m_AudioFileInfo(new TagLib::FileRef),
	m_OutputFormat(new QAudioFormat())
{
	
}

FocusedFile::~FocusedFile()
{
	if (m_AudioFileInfo) {
		delete m_AudioFileInfo;
	}
}

void FocusedFile::setNewFile(QString filePath)
{
	if (m_Processor->getProcessingStatus()==ProcessThread::Decoding) 
	{
		m_Processor->abortDecoding();
	}

	m_FileInfo->setFile(filePath);

	if (m_AudioFileInfo != nullptr)
	{
		delete m_AudioFileInfo;
	}
	m_AudioFileInfo = new TagLib::FileRef(
			filePath.toStdString().c_str(),
			true,
			TagLib::AudioProperties::Accurate );
	
	// Setting thread properties for decoding and building Waveform
	/*
	m_Processor->setLength(
		(m_AudioFileInfo->audioProperties()->sampleRate()
			*
		(m_AudioFileInfo->audioProperties()->lengthInMilliseconds() / 1000) )
		);
	*/

	// Decoding stage
	// m_Processor->decodeFile(filePath);

}

TagLib::AudioProperties* FocusedFile::getAudioProperties()
{
	return m_AudioFileInfo->audioProperties();
}

void FocusedFile::startDecoding()
{
	m_Processor->decodeFile(m_FileInfo->canonicalFilePath());
}

void FocusedFile::cacheDecodedBuffer(QAudioBuffer newBuffer)
{
}

	// Configure the QAudioFormat that'll be targeted for decoding,
	// according to the current AudioProperties of the current file in focus.
void FocusedFile::setCurrentAudioFormat()
{
	m_OutputFormat->setSampleFormat(QAudioFormat::Int32);
	m_OutputFormat->setSampleRate(
		m_AudioFileInfo->audioProperties()->sampleRate()
		);

	int tmpChannelNumber(m_AudioFileInfo->audioProperties()->channels());
	m_OutputFormat->setChannelCount(tmpChannelNumber);

	switch (tmpChannelNumber)
	{
	case 1:
		m_OutputFormat->setChannelConfig(QAudioFormat::ChannelConfigMono);
		break;

	case 2:
		m_OutputFormat->setChannelConfig(QAudioFormat::ChannelConfigStereo);
		break;

	case 3:
		m_OutputFormat->setChannelConfig(QAudioFormat::ChannelConfig3Dot0);
		break;

	case 4:
		m_OutputFormat->setChannelConfig(QAudioFormat::ChannelConfigSurround5Dot0);
		break;

	case 5:
		m_OutputFormat->setChannelConfig(QAudioFormat::ChannelConfigSurround5Dot0);
		break;

	case 6:
		m_OutputFormat->setChannelConfig(QAudioFormat::ChannelConfigSurround5Dot1);
		break;

	case 7:
		m_OutputFormat->setChannelConfig(QAudioFormat::ChannelConfigSurround7Dot0);
		break;
	
	case 8:
		m_OutputFormat->setChannelConfig(QAudioFormat::ChannelConfigSurround7Dot1);
		break;

	default:
		m_OutputFormat->setChannelConfig(QAudioFormat::ChannelConfigStereo);
		break;
	}
}




