#include "SDL.h"
#include "SDL_image.h"
#include "World.h"
#include "Game.h"

#include <vector>
#include <iostream>

// std::vector<SDL_Rect> obs;

// World::World() {
//     obs.push_back(800, 40, 0, 600);
// }

// std::vector<SDL_Rect> World::getObs() {
//     return getObs();
// }

// SDL_Rect obs[3];

std::vector<SDL_Rect> obs;
int tmp = 0;

World::World() {
    SDL_Rect rect;

    rect.w = WIDTH; rect.h = 120; rect.x = 0; rect.y = HEIGHT - 40;
    obs.push_back(rect);

    // ------------------------------------------------ //

    rect.w = 160; rect.h = 20; rect.x = 500; rect.y = 110;
    obs.push_back(rect);

    rect.w = 160; rect.h = 20; rect.x = 100; rect.y = 110;
    obs.push_back(rect);

    rect.w = 160; rect.h = 20; rect.x = 200; rect.y = 140;
    obs.push_back(rect);

    rect.w = 160; rect.h = 20; rect.x = 300; rect.y = 240;
    obs.push_back(rect);

    rect.w = 160; rect.h = 20; rect.x = 450; rect.y = 340;
    obs.push_back(rect);

    rect.w = 160; rect.h = 20; rect.x = 500; rect.y = 440;
    obs.push_back(rect);
}

std::vector<SDL_Rect> World::getObs() {
    return obs;
}

// World::World() {
//     obs[0].w = 320; 
//     obs[0].h = 40;
//     obs[0].x = 400;
//     obs[0].y = (HEIGHT - obs[1].y)/2 + 100;

//     obs[1].w = 800; 
//     obs[1].h = 40;
//     obs[1].x = 0;
//     obs[1].y = 600;

//     obs[2].w = 320; 
//     obs[2].h = 40;
//     obs[2].x = 100;
//     obs[2].y = (HEIGHT - obs[2].y)/2 - 100;
// }

// SDL_Rect *World::getObs() {
//     return obs;
// }

// World::~World() {

// }

// void World::render() {
    
// }

void World::draw(SDL_Renderer* renderer, int scrollY) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for (int i = 0; i < obs.size(); i++) {
        SDL_Rect newObstacle = { obs[i].x, obs[i].y + scrollY, obs[i].w, obs[i].h };
        obs[i] = newObstacle;

        // std::cout << "counter: " << tmp++ << " scroll: " << scrollY << " obs: " << obstacle.y << std::endl;
        // std::cout << "obsAfter: " << obstacle.y;
        SDL_RenderFillRect(renderer, &obs[i]);
    }
}