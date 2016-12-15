# Memory Manager 🚀
This is my attempt to creat a custom memory manager for my games. I will be updating this repo with more features and a wiki over the time as it gets developed.

This manager will be implemented as a library, which will be compatible with both, *C* and *C++*.

## How to use it
Currently it only supports compiling inside Visual Studio (I will add a makefile in the future to be able to use it in \*NIX systems).

### Visual Studio
To use it under Visual Studio, add the **vcxproj** as a project, and add the .lib to the linker paths as **$(OutFolder)MemoryManager.lib**.

## Roadmap 🗺
- [x] Implement malloc
- [x] Implement free
- [x] Implement memory manager cleanup
- [ ] Cleanup code
- [ ] Improve efficiency (if possible, and if I have enough time)
