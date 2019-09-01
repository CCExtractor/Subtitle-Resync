/*
* Author: Suyash Bajpai
* Email: 7suyashbajpai@gmail.com
* Github: https://github.com/sypai
*/

#ifndef RESYNC_TOOL_H
#define RESYNC_TOOL_H

#include <string>
#include <vector>
#include <utility>
#include <unistd.h>
#include <algorithm>

#include "align_fingerprints.h"

namespace Subtitle_Resync {

    class Tool
    {
    private:
        std::string m_OriginalAudioFile;
        std::string m_ModifiedAudioFile;
        std::string m_OriginalSubtitleFile;
        int m_LogLevel;

    public:
        Tool();
        Tool(std::string OriginalAudioFile, std::string ModifiedAudioFile, std::string OriginalSubtitleFile, int LogLevel);
        void sync();
        ~Tool();
    };


} // namespace Subtitle_Resync

#endif //RESYNC_TOOL_H
