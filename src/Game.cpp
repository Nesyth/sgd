#include "Game.h"
#include "Player.h"
#include "World.h"
#include "Background.h"
#include "SDL_image.h"

#include <iostream>
#include <vector>
#include <string>

SDL_Renderer* Game::renderer;
SDL_Texture* playerTexture;
Player* player = nullptr;
World* world = nullptr;
Background* background = nullptr;

std::string collision;
int collisionHeight;
SDL_Rect collisionRect;
int updateScroll = 0;

SDL_Rect camera = { 0, 0, WIDTH, HEIGHT};

Game::Game() {
    window = NULL;
    renderer = NULL;
    playerTexture = NULL;
}

Game::~Game() {}

void Game::init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "SDL innited!\n";
        window = SDL_CreateWindow("SGD Platformer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
        if (window) {
            std::cout << "Window created!\n";
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (renderer) {
                std::cout << "Renderer created!\n";
                int flags = IMG_INIT_PNG;
                int initted = IMG_Init(flags);
                if ((initted&flags) != flags) {
                    std::cout << "IMG_Init: Failed to init required jpg and png support!\n";
                    printf("IMG_Init: %s\n", IMG_GetError());
                    isRunning = false;
                } else {
                    std::cout << "Yeah\n";
                    isRunning = true;

                    Player* player = new Player();
                    World* world = new World();
                    background->init(renderer);
                    player->init(renderer);
                    world->init(renderer);

                    // playerTexture = player->loadImage(renderer); 
                }
            } else {
                std::cout << "Couldn't create a renderer\n";
                isRunning = false;
            }
        } else {
            std::cout << "Couldn't create a window\n";
            isRunning = false;
        }
	} else {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        isRunning = false;
    }
}

void Game::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
			
			case SDL_KEYDOWN:
				// std::cout << ("Key press detected\n");
				break;

			case SDL_KEYUP:
				// std::cout << ("Key release detected\n");
				break;
        }

    player->handleEvents(event);
}

void Game::checkIntersect(SDL_Rect a, std::vector<SDL_Rect> b) {
    SDL_bool hasIntersection = SDL_FALSE;

    for (SDL_Rect rects : b) {
        if (SDL_HasIntersection(&a, &rects)) {
            SDL_IntersectRect(&a, &rects, &collisionRect);
            fixCollision(a, rects, collisionRect);
        }
    }
}

void Game::fixCollision(SDL_Rect a, SDL_Rect b, SDL_Rect collisionRect) {
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    int counter = -1;

    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    int smallest = 100;
    std::string result = "false";

    if (abs(bottomA - topB) < smallest) {
        smallest = abs(bottomA - topB);
        result = "collisionOnTop";
    }

    if (abs(topA - bottomB) < smallest) {
        smallest = abs(topA - bottomB);
        result = "collisionHead";
    }

    if (abs(rightA - leftB) < smallest) {
        smallest = abs(topA - bottomB);
        result = "collisionLeftHand";
    }

    if (abs(leftA - rightB) < smallest) {
        smallest = abs(topA - bottomB);
        result = "collisionRightHand";
    }

    collision = result;
    collisionHeight = collisionRect.h;

    // if ((topA - bottomB >= 10 && topA - bottomB <= -10)) {
    //     collision = "head";
    // } else if ((bottomA - topB > -1 && bottomA - topB < 1) && 
    // (rightA - leftB > 0 && leftA - rightB < 0)) {
    //     collision = "onTop";
    // } else {
    //     collision = "onTop";
    // }
}

void Game::update() {
    SDL_Rect playerRect = player->getRect();

    world->update(player->getScrollY());
    collision = "false";
    checkIntersect(playerRect, world->getObs());
    player->move(collision, collisionHeight);

    camera.x = (playerRect.x + playerRect.w / 2) - WIDTH / 2;
    camera.y = (playerRect.y + playerRect.h / 2) - HEIGHT / 2;

    if (camera.x < 0) { 
        camera.x = 0;
    }

    if (camera.y < 0 ) {
        camera.y = 0;
    }

    if (camera.x > WIDTH - camera.w) {
        camera.x = WIDTH - camera.w;
    }

    if (camera.y > HEIGHT - camera.h) {
        camera.y = HEIGHT - camera.h;
    }
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0, 75, 155, 200);
    SDL_RenderClear(renderer);

    std::cout << "camera.x: " << camera.x << "camera.y: " << camera.y << std::endl;

    background->draw(renderer, 0, 0, &camera);
    player->draw(renderer, camera.x, camera.y);
    world->draw(renderer);

    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    // SDL_DestroyTexture(playerTexture);
    SDL_Quit();
}

bool Game::running() {
    return isRunning;
}