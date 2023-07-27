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

#ifndef FOCUSED_FILE_H
#define FOCUSED_FILE_H

#include <QObject>
#include <taglib/fileref.h>
#include <taglib/audioproperties.h>
#include <QFileInfo>
#include <QAudioBuffer>
#include <vector>
#include <list>

#include "ProcessThread.h"


class FocusedFile : public QObject
{
	Q_OBJECT

public:
	FocusedFile(QObject* parent = nullptr);
	~FocusedFile();

	void setNewFile(QString filePath);
	TagLib::AudioProperties* getAudioProperties();
	
	void cacheDecodedBuffer(QAudioBuffer newBuffer);
	void cacheWaveformData();
	
protected:
	void clearCache();

private:
	ProcessThread* m_Processor;		// Used to decode the audiofile and process waveform drawing
	QFileInfo* m_FileInfo;		// Used to get the usual file informations
	TagLib::FileRef* m_AudioFileInfo;		// Used to extract the audio specific file info

	std::vector<QAudioBuffer> cachedBuffers;		// Store the decoded audiobuffers
	std::vector<std::vector<int>> ChannelWaveformData;		// Store the waveform information used for drawing.

	// Properties
	bool m_hasCachedData;
	
signals:
	void newDataCached();

};


#endif // !FOCUSED_FILE_H