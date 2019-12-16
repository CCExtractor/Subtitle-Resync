/*
* Author: Suyash Bajpai
* Email: 7suyashbajpai@gmail.com
* Github: https://github.com/sypai
*/
#include "subtitle_resync.h"

void CLIHeader()
{
    std::cout << "Subtitle-Resync 0.00, CCExtractor Development." << std::endl;
    std::cout << "-------------------------------------------------------------\n" << std::endl;
}

void PrintUsage()
{
    std::string usage;
    usage = R"(Syntax:
    ./resync -org /path/to/original/wav/file -mod /path/to/modified/wav/file -s /path/to/SRT

    Options:
        -org OR -o   FILE: Original Audio file
        -mod OR -m   FILE: Modified Audio file
        -srt OR -s   FILE: Original Subtitle file

    Example: ./resync -org episode1.wav -mod episode1_W/OCommercial.wav -s input.srt)";

    std::cout << usage << std::endl;
}

int ParseOptions(int arg_c, char* arg_v[])
{
    Subtitle_Resync::resync *sync;
    sync = new Subtitle_Resync::resync();

    if (arg_c < 2)
    {
        PrintUsage();
        return 11;
    }

    for (int i=1; i<arg_c; i++)
    {
        std::string parameter(arg_v[i]);

        if ((parameter == "-org" || parameter == "-o") && i + 1 < arg_c)
        {
            sync->setOriginalAudio(arg_v[i+1]);
            i++;
        }

        else if ((parameter == "-mod" || parameter == "-m") && i + 1 < arg_c)
        {
            sync->setModifiedAudio(arg_v[i+1]);
            i++;
        }

        else if ((parameter == "-srt" || parameter == "-s") && i + 1 < arg_c)
        {
            sync->setOriginalSubtitle(arg_v[i+1]);
            i++;
        }

        else if ((parameter == "-out") && i + 1 < arg_c)
        {
            sync->setOutputName(arg_v[i+1]);
            i++;
        }

        else if ((parameter == "-debug"))
        {
            sync->setLogLevel();
            i++;
        }

        else
        {
            std::cout << "[ERROR] : Wrong input format." << std::endl;
            PrintUsage();
            return 11;
        }
    }

    sync->init();
    delete sync;
    return 0;
}

void CLIFooter()
{
    std::cout << "\n-------------------------------------------------------------" << std::endl;
    std::cout << "Issues? Open a ticket here" << std::endl;
    std::cout << "https://github.com/CCExtractor/Subtitle_Resync/issues" << std::endl;
}

int main(int argc, char *argv[])
{
    CLIHeader();
    ParseOptions(argc, argv);
    CLIFooter();

    return 0;
}


