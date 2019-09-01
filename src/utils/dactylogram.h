/*
* Author: Suyash Bajpai
* Email: 7suyashbajpai@gmail.com
* Github: https://github.com/sypai
*/

#ifndef SUBTITLE_RESYNC_DACTYLOGRAM_H
#define SUBTITLE_RESYNC_DACTYLOGRAM_H

#include <utility>
#include <chrono>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include "read_wav_file.h"
#include "src/chromaprint.h"
#include "src/utils/scope_exit.h"

// Number of channels in the audio
const static int NumOfChannels = 1;

// Sample rate of the audio
const static int SampleRate = 16000;

// Duration of the audio to be processed (in seconds)
static double MaxDuration;

// Split the audio into chunks of this duration
const static int MaxChunkDuration = 1;

namespace Subtitle_Resync{

    class Dactylogram
    {
    private:
        int m_LogLevel;
        std::string m_AudioFileName;
        std::vector<int16_t> m_Samples;
        unsigned long int m_NumberOfSamples;
        double m_NumberOfSecondsPrecise;
        int m_NumberOfSeconds;
        long int m_NumberOfMilliSeconds;
        unsigned long int m_temp_sample_num;
        std::vector<std::vector<uint32_t> > m_AudioFingerprints;
        std::vector<uint32_t> m_AllFingerprints;
        ChromaprintContext *m_ctx;

    public:
        Dactylogram();
        Dactylogram(std::string FileName, int LogLevel);
        ~Dactylogram();
        void collectFingerprints();

        std::vector<std::vector<uint32_t> > getFingerprints() const ;
        std::vector<uint32_t> getAllFingerprints() const ;
        double getAudioLength_secs() const ;
        long int getAudioLength_ms() const ;

    private:
        void readAudio();
        void igniteChromaprint();
    };
} // namespace Subtitle_Resync

#endif //SUBTITLE_RESYNC_DACTYLOGRAM_H
