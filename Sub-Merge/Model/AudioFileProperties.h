#ifndef AUDIO_FILE_PROPERTIES_H
#define AUDIO_FILE_PROPERTIES_H

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
	This class is mean to acces and extract properties from audio files.
	All the use full informations can be accessed from this class, like the file lenght
	in sec, milisec, the number of channels, etc..

*/



#include <qobject.h>

#include <taglib/fileref.h>
#include <qfileinfo.h>

class AudioFileProperties : public QFileInfo
{
	Q_OBJECT

public:
	AudioFileProperties(QObject* parent = nullptr);
	virtual ~AudioFileProperties();


private:
	TagLib::FileRef* m_tagFRef;

};


#endif // !AUDIO_FILE_PROPERTIES_H


