/*
 * Author: Suyash Bajpai
 * Email: 7suyashbajpai@gmail.com
 * Github: https://github.com/sypai
 *
 * Based on "subtitle-parser" by Oleksii Maryshchenko
 * Email: young_developer@mail.ru
 * Link: https://github.com/young-developer/subtitle-parser
 *
 * And modified as "simple-yet-powerful-srt-subtitle-parser-cpp" by Saurabh Shrivastava
 * Email: saurabh.shrivastava54@gmail.com
 * Link: https://github.com/saurabhshri/simple-yet-powerful-srt-subtitle-parser-cpp
 */

#ifndef SIFT_SRT_H
#define SIFT_SRT_H

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <cmath>
#include <algorithm>
#include <map>

/* Split a string using the passed delimiter
 *
 * @param s : String to be parsed and split
 * @param delimiter : Character to use as the delimiter
 * @param tokens : Vector of strings to return the split tokens
 *
 * @return A vector of strings containing all the split tokens, split using the delimiter
 */
inline std::vector<std::string> &split(const std::string &s, char delimiter, std::vector<std::string> &tokens)
{
    std::stringstream ss(s);
    std::string item;

    while (getline(ss, item, delimiter))
    {
        tokens.push_back(item);
    }
    return tokens;
}

/** Class Definitions **/

// ===============================================================

class SubtitleWord
{
private:
    std::string m_Text;

public:
    SubtitleWord(void);
    SubtitleWord(std::string text);
    virtual std::string getText() const;
    ~SubtitleWord(void);
};

// ===============================================================

class SubtitleItem
{
protected:
    long int m_StartTime;
    std::string m_StartTimeString;

    long int m_EndTime;
    std::string m_EndTimeString;

    int m_SubtitleNumber;

    std::string m_Text;

    bool m_Ignore;

    int m_SpeakerCount;
    std::vector<std::string> m_Speakers;

    int m_NonDialogueCount;
    std::vector<std::string> m_NonDialogue;

    std::string m_JustDialogue;
    int m_WordCount;
    std::vector<std::string> m_Words;

    int m_StyleTagCount;
    std::vector<std::string> m_StyleTag;


    std::vector<long int> m_WordStartTime;
    std::vector<long int> m_WordEndTime;
    std::vector<long int> m_WordDuration;

    std::vector<std::string> m_Fingerprints;
    std::vector<long int> m_FPTimestamps;

    bool m_Fingerprint;
public:
    long int getStartTime() const;
    long int getEndTime() const;
    std::string getStartTimeString() const;
    std::string getEndTimeString() const;

    int getSubtitleNumber() const;

    std::string getText() const;

    bool getFPstatus() const ;
    bool getIgnoreStatus() const;

    std::string getDialogue(bool doNotIgnoreNonDialogues = 0,  bool doNotRemoveSpeakerNames = 0); //returns processed subtitle

    int getSpeakerCount() const;
    int getNonDialogueCount() const;
    int getStyleTagCount() const;
    int getWordCount() const;

    std::vector<std::string> getIndividualWords();
    std::string getWordByIndex(int index);

    std::vector<long int> getWordStartTimes();
    std::vector<long int> getWordEndTimes();
    long int getWordStartTimeByIndex(int index);
    long int getWordEndTimeByIndex (int index);

    std::vector<std::string> getSpeakerNames();
    std::vector<std::string> getNonDialogueWords();
    std::vector<std::string> getStyleTags();

    void setStartTime(long int startTime);
    void setEndTime(long int endTime);
    void setText(std::string text);
    void setWordTimes(std::vector<long int> wordStartTime, std::vector<long int> wordEndTime, std::vector<long int> wordDuration);  //assign time to individual words

    SubtitleItem(void);

    SubtitleItem(int subNo, std::string text, bool fingerprint);  //default constructor

    SubtitleItem(int subNo, std::string startTime,std::string endTime, std::string text, bool fingerprint, bool ignore = false,
                 std::string justDialogue = "" , int speakerCount = 0, int nonDialogueCount = 0,
                 int styleTagCount = 0, int wordCount = 0, std::vector<std::string> speaker = std::vector<std::string>(),
                 std::vector<std::string> nonDialogue = std::vector<std::string>(),
                 std::vector<std::string> styleTags = std::vector<std::string>(),
                 std::vector<std::string> word = std::vector<std::string>());  //default constructor
    ~SubtitleItem(void);

protected:
    long int timeToMS(const std::string& timeString);
    std::string MSToSRTTime(long int milliseconds);

    void extractInfo(bool doNotIgnoreNonDialogues = 0,  bool doNotRemoveSpeakerNames = 0);

};

// ===============================================================

class SubtitleParser
{
protected:
    std::vector<SubtitleItem*> m_Subtitles;
    std::string m_FileName;

public:
    virtual std::vector<SubtitleItem*> getSubtitles();
    std::string getFileData();

    SubtitleParser(void);
    virtual ~SubtitleParser(void);

protected:
    virtual void parse(std::string fileName) = 0;
};

// ===============================================================


class co_oCCurParser : public SubtitleItem
{
private:
    int m_SegmentWindow;
    std::vector<SubtitleItem*> m_SubtitleItems;
    int m_TotalSubtitles;

public:
    std::vector<std::string> getFingerprints();
    std::vector<long int> getFPTimestamps();
    int getTotalSubtitles();

    std::vector<char> SpeechActivityDetection(int SegmentWindow);

    explicit co_oCCurParser(std::vector<SubtitleItem*> sub);
    ~co_oCCurParser();
};


// ===============================================================

class co_oCCurEditor : public SubtitleItem
{
private:
    std::string m_FileName;
    std::string m_FileNameOut;
    std::vector<SubtitleItem*> m_SubtitleItems;
    std::vector<long int> m_StartTimeArray;
//    std::vector<long int> m_StartTimeArray;
//    std::vector<long int> m_comm_seg;

public:
    void EnrichSRT(std::string FileName, std::vector<std::string> fingerprints, std::vector<long int> FPTimestamps);
    void AdjustSRT(const std::string& FileName, long int delay, bool inc_or_dec);
    void Adjust(const std::string& FileName, const std::vector<std::vector<long int> > &Segments,  const std::map<long int, long int > &Dactylogram);
    std::string getOutFile();
    explicit co_oCCurEditor(std::vector<SubtitleItem*> sub);
    ~co_oCCurEditor();

private:
    int locate(long int num);
    bool IsInRange(long int num, long int lower, long int upper);
    int indexOf(SubtitleItem* sub);
    void getStartTimeArray();
    int getIndex(std::vector<long int> StartTimeArray, long int low, long int high, long FPTimestamp);
    int getIndex(std::vector<long int> StartTimeArray, int low, int high, long FPTimestamp);
};

// ===============================================================

class SubtitleParserFactory
{
private:
    std::string m_FileName;
public:
    SubtitleParser* getParser();
    SubtitleParserFactory(std::string fileName);
    ~SubtitleParserFactory(void);
};

// ===============================================================

class SubRipParser : public SubtitleParser
{
private:
    void parse(std::string fileName);

public:
    SubRipParser(void);
    SubRipParser(const std::string& fileName);
    ~SubRipParser(void);
};


/** Method Definitions **/


// ===============================================================
// 1. SubtitleParserFactory

inline SubtitleParserFactory::SubtitleParserFactory(std::string fileName)
{
    m_FileName = fileName;
}

inline SubtitleParser* SubtitleParserFactory::getParser()
{
    return new SubRipParser(m_FileName);
}

inline SubtitleParserFactory::~SubtitleParserFactory()
{

}

// ===============================================================
// 2. SubtitleParser

inline std::vector<SubtitleItem*> SubtitleParser::getSubtitles()
{
    return m_Subtitles;
}

inline std::string SubtitleParser::getFileData()
{
    std::ifstream infile(m_FileName);
    std::string allData;
    allData = "";
    std::string line;

    while(std::getline(infile, line))
    {
        std::istringstream iss(line);
        allData += line + "\n";
    }

    return allData;
}

inline SubtitleParser::SubtitleParser()
{

}

inline SubtitleParser::~SubtitleParser()
{

}

// ===============================================================
// 3. SubRipParser

inline SubRipParser::SubRipParser()
{

}

inline void SubRipParser::parse(std::string fileName)
{
    std::ifstream inFile(fileName);

    std::string line, start, end, completeLine="", timeLine="";
    int subNo;
    int turn=0;

    /*
     * turn = 0 -> Add Subtitle Number
     * turn = 1 -> Add String to timeLine
     * turn > 1 -> Add String to completeLine
     * */

    while (std::getline(inFile, line))
    {
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());

        if (line.compare(""))
        {
            if (!turn)
            {
                subNo = atoi(line.c_str());
                turn++;
                continue;
            }

            if (line.find("-->") != std::string::npos)
            {
                timeLine += line;

                std::vector<std::string> srtTime;
                srtTime = split(timeLine, ' ', srtTime);

                start = srtTime[0];
                end = srtTime[2];
            }

            else
            {
                if (!completeLine.empty())
                    completeLine += " ";

                if(completeLine.empty())
                    completeLine += line;
                else
                    completeLine += "\n" + line;
            }

            turn++;
        }

        else
        {
            turn = 0;
            m_Subtitles.push_back(new SubtitleItem(subNo, start, end, completeLine, false));
            completeLine = "";
            timeLine = "";
        }

        if (inFile.eof())
        {
            m_Subtitles.push_back(new SubtitleItem(subNo, start, end, completeLine, false));
        }
    }
}

inline SubRipParser::SubRipParser(const std::string& fileName)
{
    m_FileName = fileName;
    parse(fileName);
}

inline SubRipParser::~SubRipParser()
{
    for (int i=0; i != m_Subtitles.size(); ++i)
    {
        if (m_Subtitles[i])
            delete m_Subtitles[i];
    }
}

// ===============================================================
// 4. SubtitleItem

inline SubtitleItem::SubtitleItem(void)
{

}

inline SubtitleItem::SubtitleItem(int subNo, std::string text, bool Fingerprint)
{
    m_Text = text;
    m_SubtitleNumber = subNo;
    m_Fingerprint = Fingerprint;
    extractInfo();
}

inline SubtitleItem::SubtitleItem(int subNo, std::string startTime,std::string endTime, std::string text, bool fingerprint, bool ignore,
                                  std::string justDialogue, int speakerCount, int nonDialogueCount,
                                  int styleTagCount, int wordCount, std::vector<std::string> speaker,
                                  std::vector<std::string> nonDialogue,
                                  std::vector<std::string> styleTags,
                                  std::vector<std::string> word)
{
    m_StartTime = timeToMS(startTime);
    m_EndTime = timeToMS(endTime);
    m_Text = text;
    m_SubtitleNumber = subNo;
    m_StartTimeString = startTime;
    m_EndTimeString = endTime;
    m_Ignore = ignore;
    m_JustDialogue = justDialogue;
    m_SpeakerCount = speakerCount;
    m_NonDialogueCount = nonDialogueCount;
    m_WordCount = wordCount;
    m_Speakers = speaker;
    m_StyleTagCount = styleTagCount;
    m_StyleTag = styleTags;
    m_NonDialogue = nonDialogue;
    m_Words = word;
    m_Fingerprint = fingerprint;
    extractInfo();
}

inline long int SubtitleItem::timeToMS(const std::string& value)
{
    std::vector<std::string> t, secs;
    int hours, mins, seconds, milliseconds;

    t = split(value, ':', t);
    hours = atoi(t[0].c_str());
    mins = atoi(t[1].c_str());

    secs = split(t[2], ',', secs);
    seconds = atoi(secs[0].c_str());
    milliseconds = atoi(secs[1].c_str());

    return hours * 3600000 + mins * 60000 + seconds * 1000 + milliseconds;
}

inline std::string SubtitleItem::MSToSRTTime(long int milliseconds)
{
    int seconds = floor(milliseconds / 1000);
    int minutes = floor(seconds / 60);
    int hours = floor(minutes / 60);

    milliseconds = milliseconds % 1000;
    seconds = seconds % 60;
    minutes = minutes % 60;

    return (hours < 10 ? "0" : "") + std::to_string(hours) + ":"
           + (minutes < 10 ? "0" : "") + std::to_string(minutes) + ":"
           + (seconds < 10 ? "0" : "") + std::to_string(seconds) + ","
           + (milliseconds < 100 ? "0" : "") + (milliseconds < 10 ? "0" : "") + std::to_string(milliseconds);
}

inline long int SubtitleItem::getStartTime() const
{
    return m_StartTime;
}
inline long int SubtitleItem::getEndTime() const
{
    return m_EndTime;
}

inline std::string SubtitleItem::getText() const
{
    return m_Text;
}

inline void SubtitleItem::setStartTime(long int startTime)
{
    m_StartTime = startTime;
}
inline void SubtitleItem::setEndTime(long int endTime)
{
    m_EndTime = endTime;
}
inline void SubtitleItem::setText(std::string text)
{
    m_Text = text;
}
inline void SubtitleItem::setWordTimes(std::vector<long int> wordStartTime, std::vector<long int> wordEndTime, std::vector<long int> wordDuration)
{
    m_WordStartTime = wordStartTime;
    m_WordEndTime = wordEndTime;
    m_WordDuration = wordDuration;
}
inline int SubtitleItem::getSubtitleNumber() const
{
    return m_SubtitleNumber;
}
inline std::string SubtitleItem::getStartTimeString() const
{
    return m_StartTimeString;
}

inline std::string SubtitleItem::getEndTimeString() const
{
    return m_EndTimeString;
}

inline bool SubtitleItem::getFPstatus() const
{
    return m_Fingerprint;
}

inline bool SubtitleItem::getIgnoreStatus() const
{
    return m_Ignore;

}

inline void SubtitleItem::extractInfo(bool doNotIgnoreNonDialogues, bool doNotRemoveSpeakerNames)   //process subtitle
{
    std::string output = m_Text;

    //stripping non dialogue data e.g. (applause)

    if(!doNotIgnoreNonDialogues)
    {
        /*
         * TODO : Before erasing, extract the words.
         * std::vector<std::string> getNonDialogueWords();
         * int getNonDialogueCount() const;
         * std::vector<std::string> _nonDialogue;
         * int _nonDialogueCount;
         */

        int countP = 0;
        for(char& c : output)   // replacing (...) with ~~~~
        {
            if(c=='(')
            {
                countP++;
                c = '~';
            }

            else
            {
                if(countP!=0)
                {
                    if(c != ')')
                        c = '~';

                    else if(c ==')')
                    {
                        c = '~';
                        countP--;
                    }
                }
            }
        }
    }

    output.erase(std::remove(output.begin(), output.end(), '~'), output.end()); // deleting all ~

    //Extracting speaker names
    if(!doNotRemoveSpeakerNames)
    {
        for(int i=0; output[i]!='\0';i++)
        {
            int colonIndex = 0, nameBeginIndex = 0;
            if(output[i]==':')  //speaker found; travel back
            {
                m_SpeakerCount++;
                colonIndex = i;

                int tempIndex = 0, foundEvilColon = 0, continueFlag = 0, spaceBeforeColon = 0;

                if(output[i-1] == ' ')
                    spaceBeforeColon = 2;


                for(int j=i - spaceBeforeColon; j>=0;j--)
                {
                    if(output[j] == '.' || output[j] == '!' || output[j] == ',' || output[j] == '?' || output[j] == '\n'
                       || output[j] == ' ' || j== 0)
                    {

                        if(output[j] == '.' || output[j] == '!' || output[j] == ',' || output[j] == '?' || j == 0)
                        {
                            if((continueFlag && j == 0))
                            {
                                if(!isupper(output[j]))
                                {
                                    nameBeginIndex = tempIndex;
                                    break;
                                }

                                else
                                    tempIndex = j;

                            }

                            else if(j!=0)
                                tempIndex = j + 1;
                        }

                        else if(output[j] == ' ' && isupper(output[j+1]))
                        {
                            tempIndex = j;
                            continueFlag = 1;

                            continue;
                        }

                        else if(output[j] == ' ' && !isupper(output[j+1] && tempIndex == 0))
                        {
                            m_SpeakerCount--;
                            foundEvilColon = 1;
                            break;
                        }

                        nameBeginIndex = tempIndex;
                        break;
                    }
                }

                if(foundEvilColon)
                    continue;

                i = nameBeginIndex; //compensating the removal and changes in index

                //check if there's a space after colon i.e. A: Hello vs A:Hello
                int removeSpace = 0;
                if(output[colonIndex + 1]==' ')
                    removeSpace = 1;

                m_Speakers.push_back(output.substr(nameBeginIndex, colonIndex - nameBeginIndex));
                output.erase(nameBeginIndex, colonIndex - nameBeginIndex + removeSpace);
            }

        }

    }

    // removing more than one whitespaces with one space
    unique_copy (output.begin(), output.end(), std::back_insert_iterator<std::string>(m_JustDialogue),
                 [](char a,char b)
                 {
                     return isspace(a) && isspace(b);
                 });

    // trimming whitespaces
    const char* whiteSpaces = " \t\n\r\f\v";
    m_JustDialogue.erase(0, m_JustDialogue.find_first_not_of(whiteSpaces));
    m_JustDialogue.erase(m_JustDialogue.find_last_not_of(whiteSpaces) + 1);

    if(m_JustDialogue.empty() || m_JustDialogue == " ")
        m_Ignore = true;

    else
    {
        m_Words = split(m_JustDialogue, ' ', m_Words); //extracting individual words
        m_WordCount = m_Words.size();
    }
}

inline std::string SubtitleItem::getDialogue(bool doNotIgnoreNonDialogues,  bool doNotRemoveSpeakerNames)
{
    if(m_JustDialogue.empty())
        extractInfo(doNotIgnoreNonDialogues, doNotRemoveSpeakerNames);

    return m_JustDialogue;
}

inline int SubtitleItem::getSpeakerCount() const
{
    return m_SpeakerCount;
}

inline int SubtitleItem::getNonDialogueCount() const
{
    return m_NonDialogueCount;
}

inline int SubtitleItem::getStyleTagCount() const
{
    return m_StyleTagCount;
}

inline int SubtitleItem::getWordCount() const
{
    return m_WordCount;
}

inline std::vector<std::string> SubtitleItem::getSpeakerNames()
{
    return m_Speakers;
}

inline std::vector<std::string> SubtitleItem::getNonDialogueWords()
{
    return m_NonDialogue;
}

inline std::vector<std::string> SubtitleItem::getIndividualWords()
{
    return m_Words;
}

inline std::string SubtitleItem::getWordByIndex(int index)
{
    return m_Words[index];
}

inline std::vector<long int> SubtitleItem::getWordStartTimes()
{
    return m_WordStartTime;
}

inline std::vector<long int> SubtitleItem::getWordEndTimes()
{
    return m_WordEndTime;
}

inline long int SubtitleItem::getWordStartTimeByIndex(int index)
{
    return m_WordStartTime[index];
}

inline long int SubtitleItem::getWordEndTimeByIndex(int index)
{
    return m_WordEndTime[index];
}

inline std::vector<std::string> SubtitleItem::getStyleTags()
{
    return m_StyleTag;
}

inline SubtitleItem::~SubtitleItem(void)
{

}

// ===============================================================
// 5. co_oCCurEditor

inline co_oCCurEditor::co_oCCurEditor(std::vector<SubtitleItem*> sub)
{
    m_SubtitleItems = std::move(sub);
}

inline bool co_oCCurEditor::IsInRange(long int num, long int lower, long int upper)
{
    return (((num - lower) * (num - upper)) <= 0);
}

inline int co_oCCurEditor::indexOf(SubtitleItem *sub)
{
    std::vector<SubtitleItem*>::iterator itr = std::find(m_SubtitleItems.begin(), m_SubtitleItems.end(), sub);

    if ( itr != m_SubtitleItems.cend())
        return std::distance(m_SubtitleItems.begin(), itr);
    else
        return -1;
}

inline void co_oCCurEditor::getStartTimeArray()
{
    for (SubtitleItem* element : m_SubtitleItems)
    {
        m_StartTimeArray.push_back(element->getStartTime());
    }
}

inline int co_oCCurEditor::getIndex(std::vector<long int> StartTimeArray, int low, int high, long int FPTimestamp)
{
    if (low > high)
        return -1;

    // If last element is smaller than x
    if (FPTimestamp >= StartTimeArray.at(high))
        return high;

    // Find the middle point
    int mid = (low+high)/2;

    // If middle point is FPTimestamp.
    if (StartTimeArray.at(mid) == FPTimestamp)
        return mid;

    // If FPTimestamp lies between mid-1 and mid
    if (mid > 0 && StartTimeArray.at(mid-1) <= FPTimestamp && FPTimestamp < StartTimeArray.at(mid))
        return mid-1;

    // If FPTimestamp is smaller than mid, FPTimestamp
    // must be in left half.
    if (FPTimestamp < StartTimeArray.at(mid))
        return getIndex(StartTimeArray, low, mid - 1, FPTimestamp);

    // If mid-1 is not FPTimestamp and FPTimestamp is
    // greater than StartTimeArray[mid],
    return getIndex(StartTimeArray, mid + 1, high,FPTimestamp);
}

inline int co_oCCurEditor::getIndex(std::vector<long int> StartTimeArray, long int low, long int high, long int FPTimestamp)
{
    if (low > high)
        return -1;

    // If last element is smaller than x
    if (FPTimestamp >= StartTimeArray.at(high))
        return high;

    // Find the middle point
    long int mid = (low+high)/2;

    // If middle point is FPTimestamp.
    if (StartTimeArray.at(mid) == FPTimestamp)
        return mid;

    // If FPTimestamp lies between mid-1 and mid
    if (mid > 0 && StartTimeArray.at(mid-1) <= FPTimestamp && FPTimestamp < StartTimeArray.at(mid))
        return mid-1;

    // If FPTimestamp is smaller than mid, FPTimestamp
    // must be in left half.
    if (FPTimestamp < StartTimeArray.at(mid))
        return getIndex(StartTimeArray, low, mid - 1, FPTimestamp);

    // If mid-1 is not FPTimestamp and FPTimestamp is
    // greater than StartTimeArray[mid],
    return getIndex(StartTimeArray, mid + 1, high,FPTimestamp);
}


inline void co_oCCurEditor::EnrichSRT(std::string fileName, std::vector<std::string> fingerprints, std::vector<long int> FPTimestamps)
{
    m_Fingerprints = std::move(fingerprints);
    m_FPTimestamps = std::move(FPTimestamps);
    m_FileName = std::move(fileName);

    auto SubtitleItems_copy = m_SubtitleItems;

    std::string originalFileName = m_FileName;
    std::vector<std::string> temp;
    temp = split(originalFileName, '.', temp);
    std::string enrichedFileName = "../" + temp[0] + "_rich.srt";
    std::ofstream writeToFile;

    std::vector<int> indices;
    std::vector<SubtitleItem*> FPItems;

    getStartTimeArray();

    int turnFP = 0;
    for (int i = 0; i < m_FPTimestamps.size(); i++)
    {
        int index = getIndex(m_StartTimeArray, 0, m_SubtitleItems.size() - 1, m_FPTimestamps.at(i));
        indices.push_back(index);

        SubtitleItem* FPItem;
        FPItem = new SubtitleItem(indices.at(i) + turnFP + 2, m_Fingerprints.at(i), true);

        FPItem->setStartTime(m_FPTimestamps[i]);
        FPItem->setEndTime(m_FPTimestamps[i]);

        FPItems.push_back(FPItem);
        turnFP++;
    }

    turnFP = 0;
    for (int i = 0; i < indices.size() ; i++)
    {
        auto itr = SubtitleItems_copy.begin();
        advance(itr, indices.at(i)+turnFP+1);
        SubtitleItem* sub = FPItems.at(i);
        SubtitleItems_copy.insert(itr, sub);
        turnFP++;
    }


    writeToFile.open(enrichedFileName);

    turnFP = 0;
    for (SubtitleItem* element : m_SubtitleItems)
    {
        int subNo = 1;
        long int startTime = element->getStartTime();
        long int endTime = element->getEndTime();
        int duration = endTime - startTime;
        std::string payload = element->getText();
        const char* isFP;

        if (element->getFPstatus())
        {
            isFP = "YES";
            subNo = element->getSubtitleNumber();
            payload = "#fingerprint# " + payload;
            turnFP++;
        }
        else
        {
            isFP = "NO";
            subNo = element->getSubtitleNumber()+turnFP;
        }

        writeToFile << "BEGIN" << std::endl;
        writeToFile << subNo << std::endl;
        writeToFile << "start= " << startTime  << std::endl;
        writeToFile << "end= " << endTime << std::endl;
        writeToFile << "duration= " << duration << std::endl;
        writeToFile << std::endl;
        writeToFile << "payload= " << payload << std::endl;
        writeToFile << "fingerprint= " << isFP << std::endl;
        writeToFile << "END"<< std::endl;
        writeToFile << std::endl;
    }
    writeToFile.close();
}

inline void co_oCCurEditor::AdjustSRT(const std::string& FileName, long int delay, bool inc_or_dec)
{
    std::vector<std::string> temp;
    temp = split(FileName, '.', temp);
    std::vector<std::string> temp1;
    temp1 = split(FileName, '/', temp1);
    std::string adjustedFileName = temp[0] + ".srt";
    std::string co_oCCurFileName = "../co_oCCur-" + temp1[temp1.size() - 1];

    std::ofstream writeToFile;

    writeToFile.open(co_oCCurFileName);

    for (SubtitleItem* element : m_SubtitleItems)
    {
        int subNo = element->getSubtitleNumber();
        long int startTime=element->getStartTime();
        long int endTime=element->getEndTime();

        if (inc_or_dec)
        {
            startTime += delay;
            endTime += delay;
        }
        else
        {
            startTime -= delay;
            endTime -= delay;
        }

        std::string StartTimeString = MSToSRTTime(startTime);
        std::string EndTimeString = MSToSRTTime(endTime);

        std::string payload = element->getText();

        writeToFile << subNo << std::endl;
        writeToFile << StartTimeString << " --> " << EndTimeString << std::endl;
        writeToFile << payload << std::endl;
        writeToFile << std::endl;
    }

}

inline void co_oCCurEditor::Adjust(const std::string &FileName, const std::vector<std::vector<long int> > &Segments, const std::map<long int, long int > &Dactylogram)
{
    std::vector<std::string> temp;
    temp = split(FileName, '.', temp);
    std::vector<std::string> temp1;
    temp1 = split(FileName, '/', temp1);
    std::string adjustedFileName = temp[0] + ".srt";
    std::string co_oCCurFileName = "../co_oCCur-" + temp1[temp1.size() - 1];

    std::ofstream writeToFile;
    m_FileNameOut = co_oCCurFileName;
    writeToFile.open(co_oCCurFileName);

    std::vector<long int> segments;
    std::vector<long int> anchors;

    for(int i = 0; i < Segments.size() - 1; i++)
    {
        segments.emplace_back(Segments[i][1]);
    }

    anchors.clear();

    auto itr = Dactylogram.begin();
    while(itr!=Dactylogram.end())
    {
        anchors.emplace_back(itr->first);
        itr++;
    }
    itr = Dactylogram.begin();

    long int prev_org_startTime=0;
    long int prev_mod_startTime=0;
    int prev_anchor_index=0;

    int first_anchor = 0;
    int subNo = 0;
    for (SubtitleItem* element : m_SubtitleItems)
    {
        long int org_startTime = element->getStartTime();
        long int mod_startTime=0;
        long int org_endTime = element->getEndTime();
        long int mod_endTime=0;
        long int length = org_endTime - org_startTime;

        int segment_index = getIndex(segments, 0, segments.size()-1, org_startTime) + 1;
        int anchor_index = getIndex(anchors, 0, anchors.size()-1, org_startTime) + 1;

        if(segment_index >= Segments.size() || anchor_index > anchors.size() + 1)
        {
            break;
        }

        if(Segments[segment_index][2] == 0)
        {
            // Commercial segment
            continue;
        }

        long int delta=0;

        if(Segments[segment_index][2] == 1)
        {
            if(first_anchor == 0)
            {
                auto org_time = itr->first;
                auto mod_time = itr->second;
                delta = org_startTime - org_time;
                mod_startTime = mod_time + delta;
                first_anchor++;
            }

            else if(anchor_index != prev_anchor_index)
            {
                std::advance(itr, anchor_index-1);
                auto org_time = itr->first;
                auto mod_time = itr->second;
                delta = org_startTime - org_time;
                mod_startTime = mod_time + delta;
                itr = Dactylogram.begin();
            }

            else
            {
                delta = org_startTime - prev_org_startTime;
                mod_startTime = prev_mod_startTime + delta;
            }

            subNo++;
            prev_org_startTime = org_startTime;
            prev_mod_startTime = mod_startTime;
            prev_anchor_index = anchor_index;
        }

        mod_endTime = mod_startTime + length;
        std::string StartTimeString = MSToSRTTime(mod_startTime);
        std::string EndTimeString = MSToSRTTime(mod_endTime);
        std::string payload = element->getText();

        writeToFile << subNo << std::endl;
        writeToFile << StartTimeString << " --> " << EndTimeString << std::endl;
        writeToFile << payload << std::endl;
        writeToFile << std::endl;
    }
}

inline std::string co_oCCurEditor::getOutFile()
{
    return m_FileNameOut;
}
inline co_oCCurEditor::~co_oCCurEditor()
{
}

// ===============================================================
// 4. co_oCCurParser

inline co_oCCurParser::co_oCCurParser(std::vector<SubtitleItem*> sub)
{
    m_SubtitleItems = std::move(sub);
}

inline std::vector<std::string> co_oCCurParser::getFingerprints()
{
    return m_Fingerprints;
}

inline std::vector<long int> co_oCCurParser::getFPTimestamps()
{
    return m_FPTimestamps;
}

inline int co_oCCurParser::getTotalSubtitles()
{
    return m_SubtitleItems.size();
}

inline std::vector<char> co_oCCurParser::SpeechActivityDetection(int SegmentWindow)
{
    m_SegmentWindow = SegmentWindow;
    std::vector<char> subtitleString;
    long int previousEndTime = 0;
    int first_check = 0;

    for (SubtitleItem* element : m_SubtitleItems)
    {
        int subNo = element -> getSubtitleNumber();
        long int startTime = element->getStartTime();
        long int endTime = element->getEndTime();

        long int UL = 0;
        long int LL = 0;
        int frame_size = 0;
        int window_count = 0;

        if (first_check == 0)
        {
            LL = 0;
            UL = startTime;
            frame_size = UL - LL;

            if (frame_size % SegmentWindow == 0)
                window_count = frame_size / SegmentWindow;
            else
                window_count = frame_size / SegmentWindow + 1;

            for ( int i = 0; i < window_count; i++)
            {
                subtitleString.emplace_back('0');
            }
        }

        if (subNo > 1)
        {
            LL = previousEndTime;
            UL = startTime;
            frame_size = UL - LL;

            if (frame_size % SegmentWindow == 0)
                window_count = frame_size / SegmentWindow;
            else
                window_count = frame_size / SegmentWindow + 1;

            for ( int i = 0; i < window_count; i++)
            {
                subtitleString.emplace_back('0');
            }
        }

        if (first_check == 0 || subNo > 0)
        {
            LL = startTime;
            UL = endTime;
            frame_size = UL - LL;

            if (frame_size % SegmentWindow == 0)
                window_count = frame_size / SegmentWindow;
            else
                window_count = frame_size / SegmentWindow + 1;

            for (int i = 0; i < window_count; i++)
            {
                subtitleString.emplace_back('1');
            }
        }

        previousEndTime = endTime;
        first_check++;
    }

    return subtitleString;
}

inline co_oCCurParser::~co_oCCurParser()
{

}

// ===============================================================
// 5. SubtitleWord

inline SubtitleWord::SubtitleWord(void)
{
    m_Text = "";
}

inline SubtitleWord::SubtitleWord(std::string text)
{
    m_Text = text;
}

inline std::string SubtitleWord::getText() const
{
    return m_Text;
}

inline SubtitleWord::~SubtitleWord(void)
{

}

#endif //SIFT_SRT_H