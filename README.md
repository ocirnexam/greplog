# Logfind - Analyse your log files

![main pipeline](https://github.com/ocirnexam/logfind/actions/workflows/.pipeline.yml/badge.svg)

Logfind is a tool that lets you easily analyse your logfiles. Instead of searching in all files for specific search attributes, only log files are considered.
The logfiles that should be checked are stored in ~/.logfind.
If you enter more than one search attribute, the search attributes can either be linked with logical and, or with or. The default is and. To use or, the second program
argument has to be '-o'.

## Installation

```
git clone git@github.com:ocirnexam/logfind.git
mkdir build && cd build
cmake ..
make
cd ..
sudo chmod +x install.sh
sudo ./install.sh
```

## Usage

```
logfind [-o] <search_attribute1> <search_attribute2> ...
logfind -h
```
