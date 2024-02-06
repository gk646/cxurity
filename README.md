## cxurity

`cxurity` is intended to be an AI powered surveillance platform both on a micro (running per process) and macro (running per networks).
This system aims to connect anomaly detection for each running process on each pc , their change over time and its behaviour inside a network to detect malicious activity.
The vision is to use AI in the following scenarios:
- Analyze each process in a snapshot per computer (taken all few seconds) and compare it to pretrained base models
  - This includes memory usage, cpu time and network usage
- Analyze the change over time and compare it to pretrained models
- Analyze the behaviour of each entity inside a network (including assignable roles)
  - This includes data like device name, physical information and uptime

By combining multiple levels of detection and vast amounts of data this system aims to secure against malicious software in real time.

### Platforms

Already built with multiplatform in mind, currently only working on Windows.

### UI

UI is done using raylib and raygui and custom components in a tree hierarchy.

### Installation 

The CMakeLists.txt is quite comprehensive. It downloads all necessary libraries ([`cxstructs`](https://github.com/gk646/CXStructures), `raylib`, `raygui` + style headers) and includes them. 
This should already run out of the box like this.

#### Needs to be run as administrator (on Windows) for proper use
