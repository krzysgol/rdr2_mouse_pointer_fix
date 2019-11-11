# rdr2_mouse_pointer_fix
A very simple workaround for a mouse pointer reappearing at the center of RDR2 game screen

This is mostly usable for people who play RDR2 using a **controller**. May not be adequate for keyboard/mouse usage.

#### How does it work ####
1. Run *rdr2_mouse.exe* before running the game.

2. Upon detection of a running instance of RDR2 this app starts periodically repositioning the mouse pointer to the rightmost edge of the rightmost display.

3. The app will exit automaticaly when you quit the game.

#### Build prerequisites ####
* CMake
* Visual Studio 2017
* Windows SDK

#### Binary release ####
https://github.com/krzysgol/rdr2_mouse_pointer_fix/releases
