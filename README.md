# cmakeSetup
Credit goes to Low Level IQ i modified his cmake with his youtube guides
---

## What is it?

This is a CMake setup that loads glfw, OpenGL, stb_image, stb_truetype, and ImGUI. It works both on Windows and Linux.

## Why use cmakeSetup?
It is cross-platform with linux,windows and it is easy to add libraries
  [FULL EXAMPLE VIDEO!](https://www.youtube.com/watch?v=zJoXMfCI9LM)
  
  [LONGER VERSION!!](https://www.youtube.com/watch?v=XOs2qynEmNE)
  
  [VIDEO ABOUT THE SETUP](https://www.youtube.com/watch?v=K8f73k9HM8M)

---

<p>Opening the Solution:</p> 

<img src="https://raw.githubusercontent.com/meemknight/photos/master/llge1.gif" width="350">

Or

<img src="https://raw.githubusercontent.com/meemknight/photos/master/llge2.gif" width="500">

Running the setup

Go to CMakeLists.txt, <kbd>CTRL + S</kbd> to make sure the solution was built.

Then, from this dropdown select mygame.exe

<img src="https://raw.githubusercontent.com/meemknight/photos/master/llge3.gif" width="200">

<kbd>Ctrl + F5</kbd> to build (<kbd>F5</kbd> oppens the debugger, you usually want to press <kbd>Ctrl + F5</kbd> because it oppens faster like this.

<p>Adding files:<br>
You should add .cpp in src and .h in include Whenever you add a new file CMake will ask you if you want to add that thing, say NO every time! I am already adding all of the things.
If you accidentally say YES, just remove that file from the CMake.lists
</p>

<p>Refreshing your changes:<br>
After you add a file, the changes should be automatically added but if you want to be sure, you can refresh changes by saving the CMake file. If you want to make a hard refresh (you might have to do that sometimes) close Visual Studio, delete the out folder, reopen VS, <kbd>CTRL + S</kbd> on CMakeLists.txt</p>


# How to use:

you need to have a /textures/ in a folder that is a directory behind the executable file to load textures

  [FULL EXAMPLE VIDEO!](https://www.youtube.com/watch?v=zJoXMfCI9LM)


# IMPORTANT!
  To ship the game: 
  In Cmakelists.txt, set the PRODUCTION_BUILD flag to ON to build a shippable version of your game. This will change the file paths to be relative to your exe (RESOURCES_PATH macro), will remove the console, and also will change the aserts to not allow people to debug them. To make sure the changes take effect I recommend deleting the out folder to make a new clean build!
