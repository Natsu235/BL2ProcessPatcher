# BL2ProcessPatcher

An ASI plugin for *Borderlands 2* used to patch various things at game launch, such as disabling checksum verification performed on generic packages (Startup.upk, Willowgame.upk) or simply re-enabing the in-game console command.
Using this, you can for example bypass the executable protection of the *Assault on Dragon Keep* standalone on Steam to grants yourself developer perks by editing the WillowGame.upk package.

### How to build ###

To build this project using **Visual Studio 2022**, you need to install the [wolfSSL library](https://github.com/wolfSSL/wolfssl) and set the project properties as follow:

* Configuration Properties > Advanced > Character Set: ```Not Set```
* C/C++ > General > Additional Include Directories > ```X:\wolfssl\5.7.0``` (replace 'X' with your drive letter)
* C/C++ > Precompiled Headers > Precompiled Header File > ```include/pch.h```
* Linker > General > Additional Library Directories > ```X:\wolfssl\5.7.0\Release\Win32``` (replace 'X' with your drive letter)
* Linker > Input > Additional Dependencies > ```Shlwapi.lib;sslSniffer.lib;wolfssl.lib```

Then, simply set the project target configuration to ```Release x86``` and build the solution.

### Installation ###

To use this plugin, build the project or download the [latest available build](https://github.com/Natsu235/BL2ProcessPatcher/releases).
Then, put the files **BL2ProcessPatcher.asi** and **BL2ProcessPatcher.ini** in: ```Borderlands 2\Binaries\Win32\Plugins``` and edit **BL2ProcessPatcher.ini** as required.

### Licence ###

This project is licensed under the GPLv3 License. See the [LICENSE](LICENSE) file for details.
