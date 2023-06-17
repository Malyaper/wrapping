#include "visualization.h"
#include <SDL.h>
#include <iostream>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

void draw_points(SDL_Renderer* renderer, const std::vector<Point>& points, const std::vector<int>& labels) {
    for (size_t i = 0; i < points.size(); ++i) {
        int cluster_label = labels[i];

        // Вибираю колір відповідно до номеру кластера
        switch (cluster_label) {
        case 0:
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            break;
        case 1:
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
            break;
        case 2:
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            break;
        default:
            SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
            break;
        }

        SDL_Rect rect;
        rect.x = static_cast<int>(points[i].x) + SCREEN_WIDTH / 2 - 2;
        rect.y = static_cast<int>(points[i].y) + SCREEN_HEIGHT / 2 - 2;
        rect.w = 4;
        rect.h = 4;

        SDL_RenderFillRect(renderer, &rect);
    }
}

void draw_hull(SDL_Renderer* renderer, const std::vector<Point>& hull_points) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    for (size_t i = 0; i < hull_points.size(); ++i) {
        size_t next_i = (i + 1) % hull_points.size();
        SDL_RenderDrawLine(renderer,
            static_cast<int>(hull_points[i].x) + SCREEN_WIDTH / 2,
            static_cast<int>(hull_points[i].y) + SCREEN_HEIGHT / 2,
            static_cast<int>(hull_points[next_i].x) + SCREEN_WIDTH / 2,
            static_cast<int>(hull_points[next_i].y) + SCREEN_HEIGHT / 2);
    }
}

void visualize(const std::vector<Point>& points, const std::vector<int>& labels, const std::vector<Point>& hull_points) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_Window* window = SDL_CreateWindow("K-means clustering and convex hull", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    SDL_Event e;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        draw_points(renderer, points, labels);
        draw_hull(renderer, hull_points);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
