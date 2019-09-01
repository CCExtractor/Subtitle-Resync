/*
* Author: Suyash Bajpai
* Email: 7suyashbajpai@gmail.com
* Github: https://github.com/sypai
*/

#ifndef SUBTITLE_RESYNC_SUBTITLE_RESYNC_H
#define SUBTITLE_RESYNC_SUBTITLE_RESYNC_H


#include <iostream>
#include <vector>
#include <string>

#include "logger.h"
#include "utils/tool.h"

namespace Subtitle_Resync{

    class resync
    {
    private:
        std::string m_OriginalAudioFileName;
        std::string m_ModifiedAudioFileName;
        std::string m_OriginalSRTFileName;
        std::string m_OutputSRTName;
        int m_LogLevel = 1;

    public:
        resync();
        void setOriginalAudio(std::string OriginalAudioName);
        void setModifiedAudio(std::string ModifiedAudioName);
        void setOriginalSubtitle(std::string OriginalSRTName);
        void setOutputName(std::string OutputSRTName);
        void setLogLevel();
        void init();
        ~resync();
    };
}

#endif //SUBTITLE_RESYNC_SUBTITLE_RESYNC_H
