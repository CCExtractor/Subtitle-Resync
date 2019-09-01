<!-- PROJECT LOGO -->

<br />
<p>
  <h1 style="color:#1C9963;">Subtitle-Resync</h1>
  <h3>High-speed subtitle synchronization tool</h3>
  <h4>GSoC 2019 | CCExtractor Development</h4>
</p>

[![GSoC](https://img.shields.io/badge/GSoC-2019-green.svg)]
[![GPLv3 license](https://img.shields.io/badge/License-GPLv3-blue.svg)](http://perso.crans.org/besson/LICENSE.html)

**Subtitle-Resync** is a high-speed subtitle synchronization tool, capable
of automatically generating *in-sync* subtitles of different versions of
the same base audiovisual content (such as, with and without commercials). 
<br />
It has been developed under GSoC 2019 with **CCExtractor development**.

<br /> See [what is it & how does it work](https://sypai.github.io/Subtitle-Resync/)
 
## Usage

Refer the [docs](https://github.com/CCExtractor/Subtitle-Resync/tree/master/docs/)
for a detailed guide to [install](https://github.com/CCExtractor/Subtitle-Resync/tree/master/docs/compiling.adoc) 
and [use](https://github.com/CCExtractor/Subtitle-Resync/tree/master/docs/usage.adoc) Subtitle-Resync.

1. Clone the repository from Github:

```bash
git clone https://github.com/CCExtractor/Subtitle-Resync.git
```

2. Navigate to `install` directory:

```bash
cd install
```

3. Run `build.sh`

```bash
./build.sh
```

5. Sync!

```bash
./resync -o /path/to/original/audio.wav -m /path/to/modified/audio.wav -s /path/to/original/subtitle.srt
```

## Notes

### Requirements
Refer the [docs](https://github.com/CCExtractor/Subtitle-Resync/tree/master/docs/)
for [installing](https://github.com/CCExtractor/Subtitle-Resync/tree/master/docs/installing_dependencies.adoc)
the dependencies of Subtitle-Resync.

* CMake 
    
    Minimum version 3.14 is required.
    
* Boost Libraries
    
    Minimum version 1.60 is required.

### Building the blocks
 Running `build.sh` can result in:

```bash
bash: ./build.sh: Permission denied
```

Possible Turnaround:
* Give it execute permission (only possible if the file-system gives RW rights)

    ```bash
    cd Subtitle-Resync/install
    chmod +x build.sh
    ./build.sh
    ```

* Use CMake to build it

    ```bash
    # Root Directory
    cmake ./
    make
    ```

### Argument properly

Refer the
[documentation](https://github.com/CCExtractor/Subtitle-Resync/tree/master/docs/)
for proper usage of the tool.

* Audio Files

    Make sure the audio is uncompressed raw PCM (16-bit signed int), mono sampled at 16000 Hz (Enough to cover human speech frequency range).

    Using [ffmpeg](https://ffmpeg.org/documentation.html) you can run:

    ```bash
    ffmpeg -i /path/to/video.ts -acodec pcm_s16le -ac 1 -ar 16000 output/path/name.wav 
    ```

* Subtitle Files

    The input subtitle file should be a clean and proper SubRip (SRT) file.

## Quick Demo

You can find the list of parameters and their brief description by running `resync` without any arguments.

* IN:
```bash
./resync -o /path/to/original/audio.wav -m /path/to/modified/audio.wav -s /path/to/original/subtitle.srt
```

What will this trigger?

1. Read the original audio and modified audio.
2. Extract audio fingerprints from the audio files.
3. Compare the fingerprints and detect the different segments in the original content. 
4. Adjust the subtitle file and generate an *in-sync* subtitle file.

See **Subtitle-Resync** in action here.


## License
GNU General Public License 3.0 (GPL-v3.0)

Check [LICENSE.md](https://github.com/CCExtractor/Subtitle-Resync/blob/master/LICENSE.md) for details on
**Subtitle-Resync's** license.
<br />
The individual licenses of the libraries used can be found in [license]()
directory.

## Community
You may reach CCExtractor community through the slack channel
where most CCExtractor developers hang out.

* CCExtractor Development on [Slack](https://ccextractor.org/public:general:support?)

We foster a welcoming and respectful community. &#128080;

## Contributing 
Any contribution to the project would be highly appreciated! 
