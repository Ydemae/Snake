g++ main.cpp -o main.exe -Wall -std=c++20 -Wno-missing-braces -I include/ -L Lib/ -lraylib -lopengl32 -lgdi32 -lwinmm

g++ MySnake.cpp -o MySnake.exe -Wall -std=c++20 -Wno-missing-braces -I include/ -L Lib/ -lraylib -lopengl32 -lgdi32 -lwinmm

gcc main.c -o main.exe -Wall -std=c99 -Wno-missing-braces -I include/ -L Lib/ -lraylib -lopengl32 -lgdi32 -lwinmm


Pour sans console
g++ MySnake.cpp -o MySnake.exe -Wall -mwindows -std=c++20 -Wno-missing-braces -I include/ -L Lib/ -lraylib -lopengl32 -lgdi32 -lwinmm