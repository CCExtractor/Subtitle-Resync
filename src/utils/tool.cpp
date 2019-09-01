/*
* Author: Suyash Bajpai
* Email: 7suyashbajpai@gmail.com
* Github: https://github.com/sypai
*/

#include "tool.h"

Subtitle_Resync::Tool::Tool()
= default;

Subtitle_Resync::Tool::Tool(std::string OriginalAudioFile, std::string ModifiedAudioFile, std::string OriginalSubtitleFile, int LogLevel)
{
    m_OriginalAudioFile = std::move(OriginalAudioFile);
    m_ModifiedAudioFile = std::move(ModifiedAudioFile);
    m_OriginalSubtitleFile = std::move(OriginalSubtitleFile);
    m_LogLevel = LogLevel;
}

Subtitle_Resync::Tool::~Tool()
= default;

void Subtitle_Resync::Tool::sync()
{
    Subtitle_Resync::AlignFP *co;

    co = new Subtitle_Resync::AlignFP(m_OriginalAudioFile, m_ModifiedAudioFile, m_OriginalSubtitleFile, m_LogLevel);
    co->brum_brum();

    delete co;
}