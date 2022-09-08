# jimoSDR
A software defined radio receiver

This project is in the very early stages of development. While the
intention is to produce executables for Windows 10/11, Linux, and MacOS,
I am currently developing on an Apple Silicon computer using Macos 12.5+.
Therefore, I am only providing instructions for building on that system

# Building jimoSDR

## MacOS (Apple Silicon)
You need to install the following:

1. Xcode 11.6 or later from the App Store and install "Command line tools".
2. Homebrew. Installation instructions are provided [here](https://docs.brew.sh/Installation).
3. The latest version of xtd:
```
cd <your-root-projects-directory>
git clone https://github.com/gammasoft71/xtd.git
cd xtd
./install
```
If not already on your system, wxWidgets will be installed during the installation of xtd.

4. Additional libraries:
 ```
brew install SoapySDR
brew install SoapyRTLSDR
```

5. Download and build jimoSDR:
```
cd <your-root-projects-directory>
git clone https://github.com/jimorc/jimoSDR.git
cd jimoSDR
mkdir build
cd build
cmake ..
make
```
If you wish to build jimoSDR using an IDE, modify the <code>cmake</code>
command as appropriate for that IDE and ignore the make command, above.

# Limitations
1. As already mentioned above, I am developing jimoSDR on a MacOS system, so build instructions
are only provided for that operating system. As the project evolves, instructions for building on
Windows 10/11 and Linux will be added. However, since there is no useful functionality in jimoSDR
yet, there is no value in adding those instructions at this time. Of course, if you want to
contribute to this project, that is one area where help would be appreciated.
1. jimoSDR is very early in its development. At this time, only work on the GUI is underway.
No SDR signals are yet retrieved from SDR dongles, so there is no signal processing.
1. I only have RTL-SDR dongles, so this is the only type of SDR hardware that jimoSDR currently
supports. This will change once jimoSDR processes signals from that SDR dongle type.
1. All RTL-SDR dongles report the same information, so there is no way to distinguish between
multiple RTL-SDRs.
1. jimoSDR uses the xtd GUI library. This library is actively under development, but is still
early in its development. Because of this, some of the placements of widgets do not appear
correct. This will be fixed as more functionality is added to xtd.

