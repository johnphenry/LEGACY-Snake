# Snake
Highly portable C version of the game Snake. Separates the dependent code from the independent code, maximises portability to other platforms.
When porting this game to other platforms, you need only change the code in DEP.c. Every other file is portable.
Note that headers for libraries such as SDL2 are not incuded in other headers, only here in this file.
This speeds up compilation times by a lot because headers are only included where they are needed.
The actual implementation of the functions in this file does not matter to any of the other files in the game.
This forces that only the dependent code can be used here, and nowhere else.
I consider even the usage of that standard library to be dependent code.
For instance, when using libGCCVB, a virtual boy compiler, the standard library actually has not been implemented for that platform!
