#include <iostream>
#include "../SiftSRT.h"


void createTempSRT(std::vector<SubtitleItem*> sub)
{
    std::ofstream myfile;
    myfile.open("../temp.srt");

    for (SubtitleItem* element : sub)
    {
        int subNo = element->getSubtitleNumber();

        long int startTime = element->getStartTime();
        long int endTime = element->getEndTime();
        int duration = endTime - startTime;

        std::string payload = element->getText();

        myfile << "BEGIN" << std::endl;
        myfile << subNo << std::endl;
        myfile << "start= " << startTime  << std::endl;
        myfile << "end= " << endTime << std::endl;
        myfile << "duration= " << duration << std::endl;
        myfile << std::endl;
        myfile << "payload= " << payload << std::endl;
        myfile << "fingerprint= " << "NO" << std::endl;
        myfile << "END"<< std::endl;
        myfile << std::endl;
    }

    myfile.close();
}

int main(int argc, char* argv[]) {

    if (argc < 2) {
        std::cout << "[No argument passed] " << "Enter the name of the subtitle file to sift!" << std::endl;
        return 0;
    }

    SubtitleParserFactory *spf;
    spf = new SubtitleParserFactory(argv[1]);

    SubtitleParser *parser;
    parser = spf->getParser();

    std::vector<SubtitleItem *> sub;
    sub = parser->getSubtitles();

    createTempSRT(sub);

    std::vector<std::string> fingerprints;
    std::vector<long int> timestamps;

    fingerprints.emplace_back("HASGFDHASGSFHGADHGFAS+/SDSFJHGDSHJFSG");
    timestamps.emplace_back(7000);

    fingerprints.emplace_back("HASGFDHFJHGDSHJFSG");
    timestamps.emplace_back(12000);

    fingerprints.emplace_back("HASGFDHADSFSDFRIUEYHKJSGSFHGADHGFASashbv3535SDSFJHGDSHJFSG");
    timestamps.emplace_back(17000);

    co_oCCurEditor *edit;
    edit = new co_oCCurEditor(sub);
    edit->EnrichSRT("temp.srt", fingerprints, timestamps);
    edit->AdjustSRT("example.srt", 2000, true);

    co_oCCurParser *parse;
    parse = new co_oCCurParser(sub);
    auto substring =parse->SpeechActivityDetection(10);

    int i=0;
    for (int j=0; j < sub.at(sub.size()-1)->getEndTime();j+=10)
    {
        std::cout << j << "ms : " << substring.at(i) << std::endl;
        i+=1;
    }

    return 0;


    return 0;
}