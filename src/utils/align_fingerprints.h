/*
* Author: Suyash Bajpai
* Email: 7suyashbajpai@gmail.com
* Github: https://github.com/sypai
*/

#ifndef SUBTITLE_RESYNC_ALIGN_FINGERPRINTS_H
#define SUBTITLE_RESYNC_ALIGN_FINGERPRINTS_H


#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <string>

#include "SiftSRT.h"
#include "utils/dactylogram.h"
#include "src/utils/gradient.h"
#include "NumCpp.hpp"

namespace Subtitle_Resync {

    class AlignFP
    {
    private:
        int m_LogLevel;
        const static uint32_t mask = 2863311520;
        constexpr static double chroma_factor = (4096.0 / 3) / 11025.0;

        std::string m_OriginalAudioFile;
        std::string m_ModifiedAudioFile;
        std::string m_OriginalSubtitleFile;
        size_t m_size;
        std::vector<int> m_offsets_peaks;
        std::vector<double> m_counts_peaks;
        std::vector<double> m_seconds;
        std::vector<double> m_score;
        std::vector<std::vector<int> > m_regions;
        std::vector<uint32_t> m_fp1, m_fp2;
        double m_len1, m_len2;
        std::vector<std::vector<long int> > m_Segments;
        std::vector<std::vector<long int> > m_InsideSegment;
        uint32_t m_curr_hash;
        double m_secs;
        bool m_over;


    private:
        static void printVector(std::vector<int> InVector);
        static void printVector(std::vector<uint32_t > InVector);
        static void printVector(const std::vector<std::vector<uint32_t > >& InVector);
        static void printVector(std::vector<long int> InVector);
        static void printVector(std::vector<float> InVector);
        static void printVector(std::vector<double > InVector);
        static void printMap(std::map <uint32_t, std::vector<int> > InMap);
        static void printMap(std::map <int32_t, int> InMap);

        void cat(std::vector<int > *s0, const std::vector<int> &gradient1_peaks, int len);
        void SumThem(std::vector<int > *s0, const std::vector<int> &gradient1_peaks, const std::vector<int> &gradient2_peaks);
        void DivideThem(std::vector<double > *s0, const std::vector<double> &gradient1_peaks, const std::vector<double> &gradient2_peaks);
        void sumIt(std::vector<uint32_t > *s0, const std::vector<std::vector<uint32_t > > &z);
        void bitwise_and(std::vector<std::vector<uint32_t > > *s0, const std::vector<std::vector<uint32_t > > &z, const std::vector<uint32_t > &y);
        void right_shift(std::vector<std::vector<uint32_t > > *s0, const std::vector<std::vector<uint32_t > > &z, const std::vector<uint32_t > &y);
        static double index_to_secs(int index);
        static double mean(const std::vector<double> &InVector);
        static int min(std::map<int32_t, int> InMap);
//        static int min(int a, int b);
        static int max(std::map<int32_t, int> InMap);
        static double findMax(std::vector<double> InVector);
        static int findMax(std::vector<int> InVector);
        static std::vector<int> arange(int lb, int ub);
        static std::vector<uint32_t> arange1(int lb, int ub);
        static double roundIt(double i);
        static bool freqNot1(const std::vector<double> &InVector);

        std::vector<uint32_t> slice(int lb, int ub);
        std::vector<uint32_t> slice2(int lb, int ub);
        std::vector<uint32_t > sliceIt0(const std::vector<uint32_t > &InArray, int lb, int ub);
        std::vector<double> sliceIt(const std::vector<double> &InArray, int lb, int ub);

        void ground_zero();
        void next(int i);
        void next_comm(int i);
        int align_fingerprints(const std::vector<uint32_t > &fp1_seg, bool print=false);
        int matching_regions(double seconds, int offset, bool local=false);
//        void align_fingerprints();
        void segment_it();

    public:
        AlignFP();
        AlignFP(std::string &OriginalAudioFile, std::string &ModifiedAudioFile, std::string &OriginalSubtitleFile, int LogLevel);

        void brum_brum();
        ~AlignFP();
    };
}

#endif //SUBTITLE_RESYNC_ALIGN_FINGERPRINTS_H
