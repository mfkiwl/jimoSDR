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
wxWidgets will be installed during the installation of xtd.

4. Download and build jimoSDR:
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
