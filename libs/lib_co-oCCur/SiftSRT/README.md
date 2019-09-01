<!-- PROJECT ABOUT -->

<br />
<p align="center">
  <h1 style="color:#1C9963;">SiftSRT: A complete Subtitle Parser & Editor</h1>
  
[![GSoC](https://img.shields.io/badge/GSoC-2019-green.svg)](https://summerofcode.withgoogle.com/dashboard/project/6506536917008384/overview/) 
<span style="font-size: 2rem;">&#160; CCExtractor Development</span>

[![GPLv3 license](https://img.shields.io/badge/License-GPLv3-blue.svg)](http://perso.crans.org/besson/LICENSE.html)

<br />

[SiftSRT](https://github.com/SiftSRT) is a [single header](https://github.com/SiftSRT/blob/master/SiftSRT.h), simple and complete SRT parsing and editing library. It allows easy handling, processing and modifying subtitle files in SRT format. It is fast and efficient. It is an extension of a simple [subtitle-parser](https://github.com/young-developer/subtitle-parser) by Oleksii Maryshchenko which was modified as [simple-yet-powerful-subtitle-parser](https://github.com/saurabhshri/simple-yet-powerful-srt-subtitle-parser-cpp) by Saurabh Shrivastava.


<!-- HOW TO USE -->

## How to use SiftSRT

`demo` directory contains usage examples. Check it out.

* Download the header file `SiftSRT.h` from [SiftSRT](https://github.com/SiftSRT).
* As any other header file, `include` it in your program.

Create a `SubtitleParserFactory` object using the subtitle file to be edited.
```
SubtitleParserFactory* spf = new SubtitleParserFactory("inputFile.srt");
```

Use the `SubtitleParserFactory` object get a `SubtitleParser` object. Use this to get the subtitles.
```
SubtitleParser* sub;
sub = spf->getParser();

std::vector<SubtitleItem*> sub;
sub = parser->getSubtitles();
``` 

Using the SubtitleParser object create a `co_oCCurEditor` object.
```
co_oCCurEditor* edit;
edit = new co_oCCurEditor(sub);
```

Using the SubtitleParser object create a `co_oCCurParser` object.
```
co_oCCurParser* parse;
parse = new co_oCCurParser(sub);
```

The objects `sub`, `edit` and `parse` can be used to **sift** the given SRT file and are to be used for Subtitle Parsing and Editing.


## Documentation

An extensive list of all the methods can be found @ [sypai.github.io/SiftSRT](https://sypai.github.io/SiftSRT).

## Contribution

Contributions of any kind, suggestions, feedback, bug reports/fixes are will be highly appreciated! 

