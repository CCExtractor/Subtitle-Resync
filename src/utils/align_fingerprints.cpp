/*
* Author: Suyash Bajpai
* Email: 7suyashbajpai@gmail.com
* Github: https://github.com/sypai
*/

#include "align_fingerprints.h"


#define hashes(sec) ((sec - 2.6) / chroma_factor)
#define time(hash) ((hash * chroma_factor) + 2.6)
#define next15(hash) ((hash + 100))
#define next30(hash) ((hash + 221))
#define next60(hash) ((hash + 463))
#define next120(hash) ((hash + 948))
#define MATCH(delta) (((delta > -0.1 && delta < 0.1) ? true : false))

void Subtitle_Resync::AlignFP::cat(std::vector<int> *s0,const std::vector<int> &gradient1_peaks, int len)
{
    s0->emplace_back(0);
    if(!gradient1_peaks.empty()) {
        for (const auto &i : gradient1_peaks) {
            s0->emplace_back(i);
        }
    }
    s0->emplace_back(len);
}

void Subtitle_Resync::AlignFP::SumThem(std::vector<int> *s0, const std::vector<int> &gradient1_peaks,
                                const std::vector<int> &gradient2_peaks)
{
    size_t size1 = gradient1_peaks.size();
    size_t size2 = gradient2_peaks.size();
    int ul;
    if(size1!=size2)
    {
        ul = size1 < size2 ? size1 : size2;
    }
    else{
        ul = size1;
    }

    for(int i = 0 ; i < ul; i++)
    {
        int sum = 0;
        sum = gradient1_peaks[i] + gradient2_peaks[i];
        s0->emplace_back(sum);
    }
}

void Subtitle_Resync::AlignFP::DivideThem(std::vector<double> *s0, const std::vector<double> &gradient1_peaks,
                                   const std::vector<double> &gradient2_peaks)
{
    size_t size1 = gradient1_peaks.size();
    size_t size2 = gradient2_peaks.size();
    int ul;
    if(size1!=size2)
    {
        ul = size1 < size2 ? size1 : size2;
    }
    else{
        ul = size1;
    }

    for(int i = 0 ; i < ul; i++)
    {
        double quo = 0;
        if(gradient2_peaks[i] != 0) {
            quo = gradient1_peaks[i] / gradient2_peaks[i];
        }
        s0->emplace_back(quo);
    }
}

void Subtitle_Resync::AlignFP::sumIt(std::vector<uint32_t > *s0, const std::vector<std::vector<uint32_t > > &z)
{
    for(const auto &i : z)
    {
        s0->emplace_back(std::accumulate(i.begin(), i.end(), 0.0));
    }
}

void Subtitle_Resync::AlignFP::bitwise_and(std::vector<std::vector<uint32_t > > *s0, const std::vector<std::vector<uint32_t > > &z, const std::vector<uint32_t > &y)
{
    for(auto i : z)
    {
        std::vector<uint32_t > p;
        for(auto j: y)
        {
            p.emplace_back(i.at(0) & j);
        }
        s0->emplace_back(p);
    }
}

void Subtitle_Resync::AlignFP::right_shift(std::vector<std::vector<uint32_t > > *s0, const std::vector<std::vector<uint32_t > > &z, const std::vector<uint32_t > &y)
{
    for(const auto& i : z)
    {
        std::vector<uint32_t > p;
        for(auto j=0; j < 32; j++)
        {
            p.emplace_back(i.at(j) >> y[j]);
        }
        s0->emplace_back(p);
    }
}

void Subtitle_Resync::AlignFP::printVector(std::vector<int> InVector)
{
    if(!InVector.empty())
    {
        std::cout << "[";
        for(int i : InVector) {
            std::cout << i << ", ";
        }
        std::cout << "]" << std::endl;
    }
}

void Subtitle_Resync::AlignFP::printVector(std::vector<uint32_t > InVector)
{
    if(!InVector.empty())
    {
        std::cout << "[";
        for(uint32_t i : InVector) {
            std::cout << i << ", ";
        }
        std::cout << "]" << std::endl;
    }
}

void Subtitle_Resync::AlignFP::printVector(const std::vector<std::vector<uint32_t > >& InVector)
{
    if(!InVector.empty())
    {
        std::cout << "[";
        for(auto i : InVector) {
            std::cout << "[";
            for(auto j : i) {
                std::cout << j ;
            }
            std::cout << "]";
            std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }
}

void Subtitle_Resync::AlignFP::printVector(std::vector<long int> InVector)
{
    if(!InVector.empty())
    {
        std::cout << "[";
        for(int i : InVector) {
            std::cout << i << ", ";
        }
        std::cout << "]" << std::endl;
    }
}

void Subtitle_Resync::AlignFP::printVector(std::vector<float> InVector)
{
    if(!InVector.empty())
    {
        std::cout << "[";
        for(float i : InVector) {
            std::cout << i << ", ";
        }
        std::cout << "]" << std::endl;
    }
}

void Subtitle_Resync::AlignFP::printVector(std::vector<double > InVector)
{
    if(!InVector.empty())
    {
        std::cout << "[";
        for(double i : InVector) {
            std::cout << i << ", ";
        }
        std::cout << "]" << std::endl;
    }
}

void Subtitle_Resync::AlignFP::printMap(std::map <uint32_t, std::vector<int> > InMap)
{
    if (!InMap.empty())
    {
        auto itr = InMap.begin();
        while (itr != InMap.end()) {
            std::cout << itr->first << ": [";
            for (int i : itr->second) {
                std::cout << i << ", ";
            }
            std::cout << "]" << std::endl;
            itr++;
        }
    }
    else
    {
        std::cout << "Nothing in here!" <<std::endl;
    }
}

void Subtitle_Resync::AlignFP::printMap(std::map <int32_t, int> InMap)
{
    if (!InMap.empty())
    {
        auto itr = InMap.begin();
        while(itr != InMap.end())
        {
            std::cout << itr->first << ": " ;
            std::cout << itr->second << std::endl;
            itr++;
        }
    }
    else
    {
        std::cout << "Nothing in here!" <<std::endl;
    }
}

double Subtitle_Resync::AlignFP::mean(const std::vector<double> &InVector)
{
    if(!InVector.empty())
    {
        return std::accumulate(InVector.begin(), InVector.end(), 0.0)/ InVector.size();
    }
    return 0;
}

double Subtitle_Resync::AlignFP::index_to_secs(int index)
{
    return index * chroma_factor;
}

int Subtitle_Resync::AlignFP::min(std::map<int32_t, int> InMap)
{
    if (!InMap.empty())
    {
        auto itr = InMap.begin();
        return itr->first;
    }

    return INT32_MAX;
}


int Subtitle_Resync::AlignFP::max(std::map<int32_t, int> InMap)
{
    if (!InMap.empty())
    {
        auto itr = InMap.rbegin();
        return itr->first;
    }

    return INT32_MIN;
}

double Subtitle_Resync::AlignFP::findMax(std::vector<double> InVector)
{
    return *std::max_element(InVector.begin(), InVector.end());;
}

int Subtitle_Resync::AlignFP::findMax(std::vector<int> InVector) {
    if (!InVector.empty()) {
        return *std::max_element(InVector.begin(), InVector.end());;
    }
    return INT32_MIN;
}

std::vector<int> Subtitle_Resync::AlignFP::arange(int lb, int ub)
{
    std::vector<int> arangeIt;

    arangeIt.clear();
    arangeIt.reserve(ub - lb + 1);

    for (auto i = lb; i < ub; i++) {
        arangeIt.emplace_back(i);
    }

    return arangeIt;
}

std::vector<uint32_t > Subtitle_Resync::AlignFP::arange1(int lb, int ub)
{
    std::vector<uint32_t > arangeIt;

    arangeIt.clear();
    arangeIt.reserve(ub - lb + 1);

    for (int i = lb; i < ub; i++) {
        arangeIt.emplace_back(i);
    }

    return arangeIt;
}

std::vector<uint32_t > Subtitle_Resync::AlignFP::sliceIt0(const std::vector<uint32_t > &InArray, int lb, int ub)
{
    std::vector<uint32_t > tempFP;
    for(auto i = lb; i < ub; i++)
    {
        tempFP.emplace_back(InArray.at(i));
    }
    return tempFP;
}

std::vector<double> Subtitle_Resync::AlignFP::sliceIt(const std::vector<double> &InArray, int lb, int ub)
{
    std::vector<double> tempFP;
    for(auto i = lb; i < ub; i++)
    {
        tempFP.emplace_back(InArray.at(i));
    }
    return tempFP;
}

std::vector<uint32_t > Subtitle_Resync::AlignFP::slice(int lb, int ub)
{
    size_t size = m_fp1.size();
    std::vector<uint32_t > tempFP;
    for(auto i = lb; i < ub; i++)
    {
        if(i >= size)
        {
            return slice(lb, size);
        }
        tempFP.emplace_back(m_fp1.at(i));
    }
    return tempFP;
}

std::vector<uint32_t > Subtitle_Resync::AlignFP::slice2(int lb, int ub)
{
    size_t size = m_fp2.size();
    std::vector<uint32_t > tempFP;
    for(auto i = lb; i < ub; i++)
    {
        if(i >= size)
        {
            return slice2(lb, size);
        }
        tempFP.emplace_back(m_fp2.at(i));
    }
    return tempFP;
}

double Subtitle_Resync::AlignFP::roundIt(double var)
{
    double value = (int)(var * 100 + .5);
    return (double)value / 100;
}

bool Subtitle_Resync::AlignFP::freqNot1(const std::vector<double> &InVector)
{
    std::map <double, int> freqMap;
    for(double i : InVector)
    {
        i = roundIt(i);
        freqMap[i]+=1;
    }
    auto itr = freqMap.begin();
    while(itr!=freqMap.end())
    {
        if(itr->second > 1)
        {
            return true;
        }
        itr++;
    }
    return false;
}

Subtitle_Resync::AlignFP::AlignFP()
= default;

Subtitle_Resync::AlignFP::AlignFP(std::string &OriginalAudioFile, std::string &ModifiedAudioFile, std::string &OriginalSubtitleFile, int LogLevel)
{
    m_OriginalAudioFile = OriginalAudioFile;
    m_ModifiedAudioFile = ModifiedAudioFile;
    m_OriginalSubtitleFile = OriginalSubtitleFile;
    m_LogLevel = LogLevel;
}

int Subtitle_Resync::AlignFP::matching_regions(double seconds, int offset, bool local)
{
    std::vector<uint32_t > fp1_seg, fp2_seg;
//    int n = 221;

    fp1_seg = slice(hashes(seconds), next30(hashes(seconds)));

    if(offset > 0) {
        fp2_seg = slice2(offset, offset + 221);
    }

    else if(offset < 0){
        fp1_seg = slice(-offset, -offset+221);
        fp2_seg = m_fp2;
    }
    size_t size1 = fp1_seg.size();
    size_t size2 = fp2_seg.size();

    int n = size1 > size2 ? size2 : size1;

    fp1_seg = sliceIt0(fp1_seg, 0, n);
    fp2_seg = sliceIt0(fp2_seg, 0, n);

    nc::NdArray<uint32_t > fp_diff, fp_new;
    auto afp1 = nc::NdArray<uint32_t > (fp2_seg);
    auto afp2 = nc::NdArray<uint32_t > (fp1_seg);

    std::vector<uint32_t > x = arange1(0, 32);
    std::vector<uint32_t > y = {1,          2,          4,          8,         16,
                                32,         64,        128,        256,        512,
                                1024,       2048,       4096,       8192,      16384,
                                32768,      65536,     131072,     262144,     524288,
                                1048576,    2097152,    4194304,    8388608,   16777216,
                                33554432,   67108864,  134217728,  268435456,  536870912,
                                1073741824, 2147483648};
    std::vector<uint32_t > a_;
    std::vector<std::vector<uint32_t > > z;
    fp_diff = nc::bitwise_xor(afp1, afp2);

    for(auto &i: fp_diff)
    {
        a_.emplace_back(i);
        z.emplace_back(a_);
        a_.clear();
    }

    std::vector<std::vector<uint32_t > > a, img;
    bitwise_and(&a, z, y);

//    for(const auto& i : a)
//    {
////        printVector(i);
//    }

    right_shift(&img, a, x);

//    for(const auto& i : img)
//    {
////        printVector(i);
//    }

    std::vector<uint32_t > ber;
    sumIt(&ber, img);

//    std::cout << "ber\n\n";
//    printVector(ber);

    auto ber_nc = nc::NdArray<uint32_t >(ber);
    auto ber2 = nc::filter::gaussianFilter1d(ber_nc.astype<double>(), 3.6, nc::filter::Boundary::NEAREST);

    std::vector<double > ber2_temp;
    for(auto i : ber2)
    {
        ber2_temp.emplace_back(i);
    }

    auto ber3 = nc::filter::gaussianFilter1d(ber2, 3.6);

//    std::cout << "\n\n";
    for(auto i : ber3)
    {
//        std::cout << i << ", ";
    }

    std::vector<double > plz;
    for(auto i: ber2)
    {
        plz.emplace_back(i);
    }

    std::vector<double> gradient0(plz.size());
    chromaprint::Gradient(plz.begin(), plz.end(), gradient0.begin());

//    std::cout << "\n\n";
    for(auto i : gradient0)
    {
//        std::cout << i << ", ";
    }

    auto gradient0_nc = nc::NdArray<double >(gradient0);
    auto gradient_nc = nc::filter::gaussianFilter1d(gradient0_nc, 3.6, nc::filter::Boundary::CONSTANT);

//    std::cout << "\n\n";
    for(auto i : gradient_nc)
    {
//        std::cout << i << ", ";
    }

    std::vector<double > gradient1;

    for(auto i: gradient_nc)
    {
        gradient1.emplace_back(i);
    }

//    std::cout << "\n\n";
    for(auto i : gradient1)
    {
//        std::cout << i << ", ";
    }

    std::vector<double> gradient(gradient1.size());
    chromaprint::Gradient(gradient1.begin(), gradient1.end(), gradient.begin());

    for (size_t i = 0; i < gradient.size(); i++) {
        gradient1[i] = std::abs(gradient1[i]);
    }

//    std::cout << "\n\ngradient1";
    for(auto i : gradient1)
    {
//        std::cout << i << ", ";
    }

//    std::cout << "\n\n";
    std::vector<int> gradient1_peaks;
    for (size_t i = 0; i < gradient.size(); i++) {
        const auto gi = gradient1[i];
//        if (i > 0 && i < gradient11.size() - 1 && gi > 0. && gi >= gradient1[i - 1] && gi >= gradient1[i + 1]) {
        if (i > 0 && i < gradient1.size() - 1  && gi >= gradient1[i - 1] && gi >= gradient1[i + 1]) {
            if (gradient1_peaks.empty() || gradient1_peaks.back() + 1 < i) {
                gradient1_peaks.emplace_back(i);
//                std::cout <<gradient1[i] << ", ";
            }
        }
    }

    std::vector<int> edges;
    cat(&edges, gradient1_peaks, n);

    auto diff0 = nc::diff(nc::NdArray<int >(edges)) / 2;

    std::vector<int> diff;
    for(auto i : diff0)
    {
        diff.emplace_back(i);
    }

    std::vector<int> mid_peaks;
    SumThem(&mid_peaks, edges, diff);

    for(auto i: mid_peaks)
    {
//        std::cout << i << ", ";
    }

    std::vector<double> s;
    for(auto i: gradient1_peaks)
    {
        s.emplace_back(1 + (plz.at(i) / 4));
    }

//    std::cout << "\n\n s \n ";
//    printVector(s);

    std::vector<double> r_;


    for(auto i: mid_peaks)
    {
        r_.emplace_back(plz.at(i));
    }

    auto diff1 = nc::diff(nc::NdArray<double>(r_));

    std::vector<double> r;
    for(auto i : diff1)
    {
        r.emplace_back(i);
    }

    for (size_t i = 0; i < r.size(); i++) {
        r[i] = std::abs(r[i]);
    }

    std::vector<double> mid_gradient;
    DivideThem(&mid_gradient, r, s);

//    std::cout << "\n\n mid_gradient\n ";
//    printVector(mid_gradient);

    std::vector<int> top_peaks;

    for(int i = 0; i < mid_gradient.size(); i++)
    {
        auto peak = mid_gradient[i];
        if(peak > 1.5)
        {
            top_peaks.emplace_back(gradient1_peaks[i]);
        }
    }
//    std::cout << "\n\n Living the dream!!\n ";
//    printVector(top_peaks);

    edges.clear();
    cat(&edges, top_peaks, n);

    size_t size_eg = edges.size();

    m_regions.clear();
    m_score.clear();
    for(int i = 0; i+1 < size_eg; i++)
    {
        std::vector<int> seg;
        seg.emplace_back(edges[i]);
        seg.emplace_back(edges[i+1]);
        m_regions.emplace_back(seg);
    }

    for(auto & segment : m_regions)
    {
        double score;
        auto s1 = sliceIt(ber2_temp, segment[0], segment[1]);
        auto sc = nc::filter::gaussianFilter1d(nc::NdArray<double>(s1), 0.3, nc::filter::Boundary::NEAREST);

        std::vector<double > temp1;
        for(auto i : sc)
        {
            temp1.emplace_back(i);
        }
        score = mean(temp1);
        m_score.emplace_back(score);
    }

//    printVector(edges);
    if(local){
        if(!top_peaks.empty())
            return top_peaks[0];
    }
    return findMax(top_peaks);
}

int Subtitle_Resync::AlignFP::align_fingerprints(const std::vector<uint32_t > &fp1_seg, bool print)
//void Subtitle_Resync::AlignFP::align_fingerprints()
{
    std::map<uint32_t, std::vector<int> > abs_offsets;
    std::map<int32_t, int> rel_offsets;

    std::vector<uint32_t> fp1, fp2;
    fp1 = m_fp2;
    fp2 = fp1_seg;
//    size_t fp1_size = fp1.size();
//    size_t fp2_size = fp2.size();

    std::vector<double> raw_counts;

    std::vector<double> counts;

    std::vector<int> gradient_peaks;
    std::vector<int> peaks;

    abs_offsets.clear();
    for (auto i = 0; i < fp1.size(); i++) {
        abs_offsets[fp1.at(i) & mask].push_back(i + 1);
    }
    for (auto i = 0; i < fp2.size(); i++) {
        abs_offsets[fp2.at(i) & mask].push_back(-(i + 1));
    }

    auto itr0 = abs_offsets.begin();

    while (itr0 != abs_offsets.end()) {
        auto hash_abs_offsets = itr0->second;
        size_t len_hash_abs_offsets = hash_abs_offsets.size();

        if (len_hash_abs_offsets <= 1) {
            itr0++;
            continue;
        }

        for (int i = 0; i < len_hash_abs_offsets; i++) {
            int o1 = hash_abs_offsets[i];

            if (o1 <= 0) {
                continue;
            }
            for (int j = 0; j < len_hash_abs_offsets; j++) {
                int o2 = hash_abs_offsets[j];
                if (o2 >= 0) {
                    continue;
                }

                rel_offsets[o1 + o2] += 1;
            }
        }
        itr0++;
    }

    int mn = min(rel_offsets);
    int mx = max(rel_offsets);

    auto offsets = arange(mn, mx + 1);

    raw_counts.assign((1 + mx - mn), 0.0);

    auto itr1 = rel_offsets.begin();

    while (itr1 != rel_offsets.end()) {
        raw_counts[itr1->first - mn] = itr1->second;
        itr1++;
    }

    auto a = nc::NdArray<double>(raw_counts);
    auto b = nc::filter::gaussianFilter1d(a, 0.6);

    for (auto i : b) {
        counts.emplace_back(i);
    }

    size_t counts_size = counts.size();
    std::vector<float> gradient(counts_size);

    chromaprint::Gradient(counts.begin(), counts.end(), gradient.begin());

    for (size_t i = 0; i < counts.size(); i++) {
        counts[i] = std::abs(counts[i]);
    }

//    for (size_t i = 0; i < counts.size(); i++) {
//        const auto gi = gradient[i];
//        if (i > 0 && i < counts.size() - 1 && gi > 0 && gi >= gradient[i - 1] && gi >= gradient[i + 1]) {
//            if (gradient_peaks.empty() || gradient_peaks.back() + 1 < i) {
//                gradient_peaks.emplace_back(i);
//            }
//        }
//    }

    for (size_t i = 0; i < counts.size(); i++) {
        const auto gi = counts[i];
        if (i > 0 && i < counts.size() - 1 && gi > 0 && gi >= counts[i - 1] && gi >= counts[i + 1]) {
            if (gradient_peaks.empty() || gradient_peaks.back() + 1 < i) {
                gradient_peaks.emplace_back(i);
            }
        }
    }

    auto threshold = findMax(counts) * 0.1;

    std::map<double, std::vector<int> >counts_peaks;
    peaks.clear();
    peaks.reserve(counts.size());

    for (int i : gradient_peaks) {
        auto ci = counts[i];
        if (ci > threshold) {
            counts_peaks[ci].emplace_back(i);
        }
    }

    auto itr2 = counts_peaks.rbegin();
    while (itr2 != counts_peaks.rend())
    {
        for(auto &i : itr2->second)
            peaks.emplace_back(i);
        itr2++;
    }


//    std::sort(peaks.begin(), peaks.end(), std::greater<>());

    m_offsets_peaks.clear();
    m_counts_peaks.clear();
    m_seconds.clear();
    for(auto item : peaks)
    {
        m_offsets_peaks.emplace_back(offsets.at(item));
        m_counts_peaks.emplace_back(counts.at(item));
        m_seconds.emplace_back(index_to_secs(offsets.at(item)));
    }

    m_size = m_offsets_peaks.size();

    if(print)
    {
        std::cout << "abs_offsets: size= " << abs_offsets.size() << std::endl;
        printMap(abs_offsets);

        std::cout << "rel_offsets: size= " << rel_offsets.size() << std::endl;
        printMap(rel_offsets);

        std::cout << "offsets" << std::endl;
        printVector(offsets);

        std::cout << "counts" << std::endl;
        printVector(counts);

        std::cout << "peaks" << std::endl;
        printVector(peaks);

        for (int i = 0; i < m_size; i++)
        {
            std::cout << "\n" << i <<") OFFSETS_PEAKS: " << m_offsets_peaks[i];
            std::cout << ", COUNTS_PEAKS: " << m_counts_peaks[i];
            std::cout << ", SECS: " << m_seconds[i] << std::endl;
        }
    }

    if(m_Segments.empty())
    {
        if(m_seconds[0] > 100) {
            return 3;
        }
    }

    if(!(m_size > 0 && m_size < 10))
    {
        if(!m_Segments.empty()) {
            matching_regions(m_secs, m_offsets_peaks[0]);
            if (m_score[0] < 15.0) {
                return 2;
            }
        }
        return 3;
    }

    else
    {
        auto delta = (m_seconds[0]) + 2.6;
        if(! (delta > -0.1 && delta < 0.1))
        {
            if(freqNot1(m_counts_peaks))
            {
                if(matching_regions(m_secs, m_offsets_peaks[0], true) > 25) {
                    if (m_score[0] > 12.0) {
                        return 3;
                    }
                }
            }
            return 2; // local match
        }

        else
        {
            return 1; // match
        }
    }
}

void Subtitle_Resync::AlignFP::ground_zero()
{
    int flag = 0;

    double delta=0;
    double aligned_secs = 0;
    double prev_aligned_secs = 0;
    long int aligned_ms = 0;

    double secs = 2.6;
    uint32_t curr_hash = hashes(secs);
    secs = 0;
    std::vector<long int> Segment;
    std::vector<uint32_t> fp1_seg;

    while(curr_hash <= m_fp1.size())
    {
        uint32_t used_hash = next15(curr_hash);  // FIRST 15 seconds
        secs += 15;
        m_secs = secs;
        fp1_seg = slice(curr_hash, used_hash);

        flag = align_fingerprints(fp1_seg);

        if(flag == 3) // NO MATCH
        {
            curr_hash = hashes(secs);
            used_hash = next30(curr_hash);
            fp1_seg = slice(curr_hash, used_hash);

            flag = align_fingerprints(fp1_seg);

            if (flag == 2) // LOCAL MATCH
            {
                while(flag != 1)
                {
                    delta = (m_seconds[0]) + 2.6;
                    aligned_secs = secs - delta;

                    if (!MATCH(delta))
                    {
                        flag = 2;
                        curr_hash = hashes(aligned_secs);
                        used_hash = next30(curr_hash);
                        fp1_seg = slice(curr_hash, used_hash);

                        align_fingerprints(fp1_seg);
                        prev_aligned_secs = aligned_secs;
                    }

                    aligned_ms = (long int) (prev_aligned_secs * 1000.0);

                    if(MATCH(delta))
                    {
                        flag = 1;

                        Segment.emplace_back(0);
                        Segment.emplace_back(aligned_ms);
                        Segment.emplace_back(0);
                        m_Segments.emplace_back(Segment);

                        secs = prev_aligned_secs;
                        curr_hash = hashes(secs);
                    }
                }
            }

            else if(flag == 1)
            {
                Segment.emplace_back(0);
                Segment.emplace_back(15000);
                Segment.emplace_back(0);
                m_Segments.emplace_back(Segment);
            }
        }

        else if(flag == 2) //LOCAL MATCH
        {
            while(flag != 1)
            {
                delta = (m_seconds[0]) + 2.6;
                aligned_secs = secs - delta;

                if (!MATCH(delta)) {
                    flag = 2;
                    curr_hash = hashes(aligned_secs);
                    used_hash = next30(curr_hash);
                    fp1_seg = slice(curr_hash, used_hash);

                    align_fingerprints(fp1_seg);
                    prev_aligned_secs = aligned_secs;
                }
                aligned_ms = (long int) (prev_aligned_secs * 1000.0);

                if(MATCH(delta))
                {
                    flag = 1;

                    Segment.emplace_back(0);
                    Segment.emplace_back(aligned_ms);
                    Segment.emplace_back(0);
                    m_Segments.emplace_back(Segment);

                    secs = prev_aligned_secs;
                    curr_hash = hashes(secs);
                }
            }
        }

        m_curr_hash = curr_hash;
        m_secs = secs;
        break;
    }
}

void Subtitle_Resync::AlignFP::next(int i)
{
    int flag = 0, offset, locate = 0;;

    std::vector<long int> Segment;
    std::vector<uint32_t> fp1_seg;

    double secs = m_secs;
    uint32_t curr_hash = hashes(secs);
    uint32_t used_hash;

    while(flag != 3)
    {
        used_hash = next30(curr_hash);
        fp1_seg.clear();
        fp1_seg = slice(curr_hash, used_hash);

        flag = align_fingerprints(fp1_seg);

        secs += 30;
        m_secs += 30;
        curr_hash = hashes(secs);
    }

    Segment.clear();
    secs -= 30;

    while(flag != 2)
    {
        secs -= 10;
        curr_hash = hashes(secs);
        used_hash = next30(curr_hash);
        fp1_seg = slice(curr_hash, used_hash);
        flag = align_fingerprints(fp1_seg);
    }

    offset = m_offsets_peaks[0];
    int adjust = matching_regions(secs, offset);

    if(adjust != INT32_MIN)
    {
        locate = time(adjust)-2.6;
    }

    Segment.emplace_back(m_Segments[i-1][1]);
    Segment.emplace_back((time(curr_hash)+locate)*1000.0);
    Segment.emplace_back(1);

    m_Segments.emplace_back(Segment);
    Segment.clear();

    std::vector<double> check_points(3);
    std::vector<long int> new_points(3);
    double duration = (m_Segments[i][1] - m_Segments[i][0])/ 1000.0;
    double stPt = m_Segments[i][0]/1000.0;
    check_points[0] = stPt + 0.25*duration;
    check_points[1] = stPt + 0.5*duration;
    check_points[2] = stPt + 0.75*duration;

    Segment.emplace_back(2);
    Segment.emplace_back(i+1);

    for(int itr=0; itr<3; itr++)
    {
        curr_hash = hashes(check_points[itr]);
        used_hash = next30(curr_hash);
        fp1_seg = slice(curr_hash, used_hash);

        flag = align_fingerprints(fp1_seg);
        if(flag == 2)
        {
            new_points[itr] = (m_seconds[0] + 2.6)*1000;
        }
        else
        {
            new_points[itr] = check_points[itr]*1000;
        }

        Segment.emplace_back(check_points[itr]*1000);
        Segment.emplace_back(new_points[itr]);
    }

    m_InsideSegment.emplace_back(Segment);
}

void Subtitle_Resync::AlignFP::next_comm(int i)
{
    std::vector<uint32_t> fp1_seg;
    std::vector<long int> Segment;
    double prev_check_time = m_secs - 30;
    double a = 0.0;

    uint32_t curr_hash = hashes(prev_check_time);
    uint32_t used_hash = next30(curr_hash);
    fp1_seg = slice(curr_hash, used_hash);

    int flag = align_fingerprints(fp1_seg);
    if(flag == 2)
    {
        a = prev_check_time - (m_seconds[0]) - 2.6;
    }

    double duration = 0.0;
    double check_time = m_secs - 30.0 + 360.0;

    if(check_time > m_len1)
    {
        m_over = true;
        check_time -= 180;
        while(check_time > m_len1)
        {
            check_time -= 180;
        }
    }

    else
    {
        curr_hash = hashes(check_time);
        used_hash = next30(curr_hash);
        fp1_seg = slice(curr_hash, used_hash);

        flag = align_fingerprints(fp1_seg);

        while(flag!=2)
        {
            check_time -= 60;
            curr_hash = hashes(check_time);
            used_hash = next30(curr_hash);
            fp1_seg = slice(curr_hash, used_hash);

            flag = align_fingerprints(fp1_seg);
        }

        duration = check_time - (m_seconds[0]) - 2.6 - a;

        if(duration > m_len1/4)
        {
            m_over = true;
            duration = m_len1 - m_Segments[i-1][1]/1000.0;
        }
    }

    Segment.clear();
    Segment.emplace_back(m_Segments[i-1][1]);
    Segment.emplace_back(m_Segments[i-1][1] + duration * 1000.0);
    Segment.emplace_back(0);
    m_Segments.emplace_back(Segment);
}

void Subtitle_Resync::AlignFP::segment_it()
{
    /*
     * flag:
     * 0 = Starting the segmentation process
     * 1 = match
     * 2 = local match
     * 3 = no match
     * */

    int i = 0, j=0;
    ground_zero();

    if(!m_Segments.empty())
    {
        if(m_LogLevel)
        {
        DEBUG0<< "Segment " << i+1 << ": ";
        printVector(m_Segments[i]);
    }}

    while(m_curr_hash <= m_fp1.size() && !m_over)
    {
        i++;

        if(m_Segments.empty()){
            i = 0;
            m_secs = 0;
        }
        else {
            m_secs = (m_Segments[i - 1][1]) / 1000.0;
        }
        next(i);

        std::cout << "\n";
        if(m_LogLevel) {
            DEBUG0 << "Segment " << i + 1 << ": ";
            printVector(m_Segments[i]);

            DEBUG0<< "Inside Segment " << i+1 << ": ";
            printVector(m_InsideSegment[j]);
        }

        if(m_Segments[i][1] < m_Segments[i][0])
        {
            break;
        }
        j++;i++;

        m_secs = (m_Segments[i-1][1]) / 1000.0;
        next_comm(i);

        std::cout << "\n";
        if(m_LogLevel) {
            DEBUG0 << "Segment " << i + 1 << ": ";
            printVector(m_Segments[i]);
        }
        if(m_Segments[i][1] < m_Segments[i][0])
        {
            break;
        }

        m_curr_hash = hashes(m_secs);
    }
}

void Subtitle_Resync::AlignFP::brum_brum()
{
    Subtitle_Resync::Dactylogram *org;
    org = new Subtitle_Resync::Dactylogram(m_OriginalAudioFile, m_LogLevel);
    org->collectFingerprints();
    m_fp1 = org->getAllFingerprints();

    Subtitle_Resync::Dactylogram *mod;
    mod = new Subtitle_Resync::Dactylogram(m_ModifiedAudioFile, m_LogLevel);
    mod->collectFingerprints();
    m_fp2 = mod->getAllFingerprints();

    m_len1 = m_fp1.size() * chroma_factor;
    m_len2 = m_fp2.size() * chroma_factor;

    if(m_LogLevel) {
        DEBUG0 << "\n Finding the different segments...\n";
    } else{
        std::cout << "Finding the different segments..." << std::endl;
    }
    segment_it();

    delete org;
    delete mod;

    std::map<long int, long int> Dactylogram;

    for(const auto &Seg : m_Segments)
    {
        uint32_t curr_hash, used_hash;
        std::vector<uint32_t > fp1_seg;

        if(Seg[2] == 0)
        {
            curr_hash = hashes(Seg[1]/1000.0);
            used_hash = next30(curr_hash);
            fp1_seg = slice(curr_hash, used_hash);

            int flag = align_fingerprints(fp1_seg);
            if(flag != 3)
            {
                if(m_seconds[0] + 2.6 > 0) {
                    Dactylogram[Seg[1]] = (m_seconds[0] + 2.6)*1000.0;
                }
                else
                {
                    Dactylogram[Seg[1]] = 0;
                }
            }
        }
    }

    for(const auto&i : m_InsideSegment)
    {
        for(int itr = 2; itr + 1 < i.size(); itr+=2)
        {
            Dactylogram[i[itr]] = i[itr+1];
        }
    }

    SubtitleParserFactory *spf;
    spf = new SubtitleParserFactory(m_OriginalSubtitleFile);

    SubtitleParser *parser;
    parser = spf->getParser();

    std::vector<SubtitleItem *> sub;
    sub = parser->getSubtitles();

    co_oCCurEditor *edit;
    edit = new co_oCCurEditor(sub);

    edit->Adjust(m_OriginalSubtitleFile, m_Segments, Dactylogram);

    auto file = edit->getOutFile();

    if(m_LogLevel) {
        DEBUG0 << "OUTPUT SUBTITLE FILE: " << file;
    } else{
        std::cout<< "OUTPUT SUBTITLE FILE: " << file << std::endl;
    }
    delete spf;
    delete edit;
}

Subtitle_Resync::AlignFP::~AlignFP()
= default;


