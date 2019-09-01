/*
* Author: Suyash Bajpai
* Email: 7suyashbajpai@gmail.com
* Github: https://github.com/sypai
*/

#include "subtitle_resync.h"


Subtitle_Resync::resync::resync()
= default;

void Subtitle_Resync::resync::setOriginalAudio(std::string OriginalAudioName)
{
    m_OriginalAudioFileName = std::move(OriginalAudioName);
}

void Subtitle_Resync::resync::setModifiedAudio(std::string ModifiedAudioName)
{
    m_ModifiedAudioFileName = std::move(ModifiedAudioName);
}

void Subtitle_Resync::resync::setOriginalSubtitle(std::string OriginalSRTName)
{
    m_OriginalSRTFileName = std::move(OriginalSRTName);
}

void Subtitle_Resync::resync::setOutputName(std::string OutputSRTName)
{
    m_OutputSRTName = std::move(OutputSRTName);
}

void Subtitle_Resync::resync::setLogLevel()
{
   m_LogLevel = 1;
}

void Subtitle_Resync::resync::init()
{
        Subtitle_Resync::Tool* handle;
        handle = new Subtitle_Resync::Tool(m_OriginalAudioFileName, m_ModifiedAudioFileName, m_OriginalSRTFileName, m_LogLevel);

        handle->sync();

        delete handle;
}

Subtitle_Resync::resync::~resync()
= default;
