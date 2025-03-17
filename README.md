# GREPLOG - Analyse your log files

![main pipeline](https://github.com/ocirnexam/greplog/actions/workflows/.pipeline.yml/badge.svg)

Greplog is a tool that lets you easily analyse your logfiles. Instead of searching in all files for specific search attributes, only log files are considered.
The logfiles that should be checked are stored in ~/.logfind.
If you enter more than one search attribute, the search attributes can either be linked with logical and, or with or. The default is and. To use or, the second program
argument has to be '-o'.

## Installation

```
git clone git@github.com:ocirnexam/greplog.git
mkdir build && cd build
cmake ..
make
cd ..
sudo chmod +x install.sh
sudo ./install.sh
```

## Usage

```
greplog [-o] <search_attribute1> <search_attribute2> ...
greplog -h
```
