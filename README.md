## cxurity

`cxurity` is intended to be an AI powered surveillance platform with two parts: a entity application running on each computer detection anomaly in process behaviors (including static analysis) and a system program run once per network that analyzes action takes by each user.

This system aims to connect anomaly detection for each running process (including memory and network usage) on each pc , their change over time (time series analysis) and the behaviour of each entity in a system to detect malicious activity.

The vision is to use AI in the following scenarios:
- Analyze each process in a snapshot taken per computer (taken all few seconds) and compare it to pretrained base models (problematic to solve)
  - This includes memory usage, cpu time and network usage, thread count...
- Analyze the change over time and compare it to pretrained models
- Analyze the behaviour of each entity inside a network (including assignable roles)
  - This includes data like device name, physical information and uptime and possibly configurable actions like accessing a server or database

By combining multiple levels of detection and vast amounts of data this system aims to secure against malicious software in real time more catered towards sophisticated threats.

### Implementation Status

Application-Design and UI are both basic feature complete. The specific implementation and usage of machine learning early on.

### Platforms

Already built with multiplatform in mind (tested on windows, no os specific features for unix yet).
Containers like the `Process` class are built with abstraction in mind and functions are defined per OS (`CXU_HOST_SYSTEM_ WIN/UNIX`).

### UI

UI is done using raylib and raygui and custom components in a tree hierarchy. By natures this is multiplatform. For Windows there are native API calls to make the window prettier.

### Application

The design follows a tree hierarchy with more specific components towards the leafs. The thread model is as follows:
- Main thread is the ui drawing (as raylib has a global state that relies on the main thread)
- Logic thread is started to update the application components
  - All work non-trivial work is sent to a worker system with a configurable amount of threads executing tasks `Worker.h`


### Machine Learning

The machine learning is done by libTorch the C++ library version of pyTorch.


### Installation 

The CMakeLists.txt is quite comprehensive. It downloads all necessary libraries ([`cxstructs`](https://github.com/gk646/CXStructures), `raylib`, `raygui` + style headers) and includes them. 
You will need to supply the source for libTorch (CUDA enabled, debug version) https://download.pytorch.org/libtorch/cu118/libtorch-win-shared-with-deps-debug-2.2.0%2Bcu118.zip. 
Like this it should run out of the box.

#### Needs to be run as administrator (on Windows) for proper use
