#NOTICE: LEGACY PROJECT
This project is considered "legacy code". The code was written a long time ago and may be subject to code rot.
Disclaimer: The coding style used in this project most likely does not represent my current coding style or methodologies. A legacy repository is kept so long as it has stars/forks, so that other users can continue to view the code.
The original readme reads below:
# Snake
Highly portable C version of the game Snake. Separates the dependent code from the independent code, maximizes portability to other platforms.
When porting this game to other platforms, you need only change the code in LIB.c. Every other file is portable.
Note that headers for libraries such as SDL2 are not incuded in other headers, only locally inside the c file.
This speeds up compilation times by a lot because headers are only included where they are needed.
The actual implementation of the functions in this file does not matter to any of the other files in the game.
This forces that only the dependent code can be used here, and nowhere else.
I consider even the usage of that standard library to be dependent code.
For instance, when using libGCCVB, a virtual boy compiler, the standard library actually has not been implemented for that platform!
# OSX Build
In addition, an OSX build in a .app file has been included in this respository. Because SDL has been compiled statically, it should run on your machine without any linking issues.
