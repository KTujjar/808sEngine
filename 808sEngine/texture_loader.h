#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <SDL.h>
#include "stb_image.h"

bool LoadTextureFromMemory(const void* data, size_t data_size, SDL_Renderer* renderer, SDL_Texture** out_texture, int* out_width, int* out_height);

bool LoadTextureFromFile(const char* file_name, SDL_Renderer* renderer, SDL_Texture** out_texture, int* out_width, int* out_height);