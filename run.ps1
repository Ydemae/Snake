g++ main.cpp -o main.exe -Ol -Wall -std=c99 -Wno-missing-braces -I include/ -L Lib/ -lraylib -lopengl32 -lgdi32 -lwinmm


gcc main.c -o main.exe -Wall -std=c99 -Wno-missing-braces -I include/ -L Lib/ -lraylib -lopengl32 -lgdi32 -lwinmm