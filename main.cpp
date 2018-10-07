#include "SDL2/SDL.h"
#include <OpenGL/gl.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
//#include <GLFW/glfw3.h>

int main(int argc, char** argv){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("OpenGL", 100, 100, 900, 500, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(window);
    glClearColor(0,0,0,1);

    /*unsigned char texData[] = {
        255,0,0,255,     0,255,0,255,     0,0,255,255,
        0,0,255,255,     255,0,0,255,     0,255,0,255,
        0,255,0,255,     0,0,255,255,     255,0,0,255,
    };*/

    int w, h, n;
    unsigned char *texData = stbi_load("JediCat.jpg", &w, &h, &n, 0);

    unsigned int textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glEnable(GL_TEXTURE_2D);

    SDL_Event event;
    bool isRunning = true;
    while(isRunning){
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT: {
                    isRunning = false;
                }
                case SDL_KEYDOWN: {
                    if(event.key.keysym.sym == SDLK_ESCAPE){
                        isRunning = false;
                    }
                    break;
                }
            }
        }
        glClear(GL_COLOR_BUFFER_BIT);

        //glfwWindowHint(GLFW_SAMPLES, 4);
        //glEnable(GL_MULTISAMPLE);

        glBegin(GL_TRIANGLES);

        //triangle 1
        glTexCoord2f(0, 1);
        glVertex2f(-0.8,-0.8);
        glTexCoord2f(0, 0);
        glVertex2f(-0.8,0.8);
        glTexCoord2f(1, 1);
        glVertex2f(0.8,-0.8);

        //triangle 2
        glTexCoord2f(1, 0);
        glVertex2f(0.8,0.8);
        glTexCoord2f(0, 0);
        glVertex2f(-0.8,0.8);
        glTexCoord2f(1, 1);
        glVertex2f(0.8,-0.8);

        glEnd();

        SDL_GL_SwapWindow(window);
    }

    SDL_DestroyWindow(window);
    return 0;
}