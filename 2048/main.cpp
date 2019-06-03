#define SDL_MAIN_HANDLED
#include"SDL.h"
#include"SDL_ttf.h"
#include<time.h>
#include<string>
#include<iostream>
#include<numeric>
#include <sstream>

namespace patch
{
	template < typename T > std::string to_string(const T& n)
	{
		std::ostringstream stm;
		stm << n;
		return stm.str();
	}
}

SDL_Color white = { 255,255,255,255 };
class Tile {
public:
	int val;
	Tile() { if ((rand() % 11) > 8)val = 4; else val = 2; }
	Tile(int val) :val(val) {}
	const int GetVal() const { return val; }
};
class Board {
public:
	TTF_Font* font = TTF_OpenFont("Montserrat-Regular.ttf", 32);
	Tile* BoardMat[4][4];
	Board() {
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				BoardMat[i][j] = NULL;
		int row = rand() % 4;
		int col = rand() % 4;
		BoardMat[row][col] = new Tile();
	}
	void draw(SDL_Renderer * renderer) {

		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
			{
				SDL_Rect r = { 100 * i,100 * j,100,100 };
				if (BoardMat[i][j] != NULL)
				{
					int value = BoardMat[i][j]->GetVal();
					SDL_SetRenderDrawColor(renderer, (10 * value) % 256, (20 * value) % 256, (30 * value) % 256, 255);
					SDL_Surface* surface = NULL;
					SDL_Texture* texture = NULL;
					surface = TTF_RenderText_Solid(font, patch::to_string(value).c_str(), white);
					texture = SDL_CreateTextureFromSurface(renderer, surface);
					int recw, rech;
					SDL_QueryTexture(texture, NULL, NULL, &recw, &rech);
					SDL_Rect dstrect = { 100 * i + 29,100 * j + 29,recw,rech };
					SDL_RenderFillRect(renderer, &r);
					SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
					SDL_RenderCopy(renderer, texture, NULL, &dstrect);
					SDL_FreeSurface(surface);
					SDL_DestroyTexture(texture);
				}
				else SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
			}
	}
	void moveright()
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
			{
				if (BoardMat[i][j] != NULL)
				{
					if (i < 3) {
						if (BoardMat[i + 1][j] == NULL) {
							BoardMat[i + 1][j] = BoardMat[i][j];
							BoardMat[i][j] = NULL;
						}
						else if (BoardMat[i + 1][j]->val == BoardMat[i][j]->val) {
							BoardMat[i + 1][j]->val = 2 * (BoardMat[i + 1][j]->val);
							BoardMat[i][j] = NULL;
						}

					}

					else continue;
				}

			}
		spawn();
	}
	void moveleft()
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
			{
				if (BoardMat[i][j] != NULL)
				{
					if (i > 0) {
						if (BoardMat[i - 1][j] == NULL) {
							BoardMat[i - 1][j] = BoardMat[i][j];
							BoardMat[i][j] = NULL;
						}
						else if (BoardMat[i - 1][j]->val == BoardMat[i][j]->val) {
							BoardMat[i - 1][j]->val = 2 * (BoardMat[i - 1][j]->val);
							BoardMat[i][j] = NULL;
						}

					}

					else continue;
				}

			}
		spawn();
	}
	void moveup()
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
			{
				if (BoardMat[i][j] != NULL)
				{
					if (j > 0) {
						if (BoardMat[i][j - 1] == NULL) {
							BoardMat[i][j - 1] = BoardMat[i][j];
							BoardMat[i][j] = NULL;
						}
						else if (BoardMat[i][j - 1]->val == BoardMat[i][j]->val) {
							BoardMat[i][j - 1]->val = 2 * (BoardMat[i][j - 1]->val);
							BoardMat[i][j] = NULL;
						}

					}

					else continue;
				}

			}
		spawn();
	}
	void movedown()
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
			{
				if (BoardMat[i][j] != NULL)
				{
					if (j < 3) {
						if (BoardMat[i][j + 1] == NULL) {
							BoardMat[i][j + 1] = BoardMat[i][j];
							BoardMat[i][j] = NULL;
						}
						else if (BoardMat[i][j + 1]->val == BoardMat[i][j]->val) {
							BoardMat[i][j + 1]->val = 2 * (BoardMat[i][j + 1]->val);
							BoardMat[i][j] = NULL;
						}

					}

					else continue;
				}

			}
		spawn();
	}
	void spawn() {
		while (1) {
			int row = rand() % 4;
			int col = rand() % 4;
			if (BoardMat[row][col] == NULL) { BoardMat[row][col] = new Tile(); break; }
		}
	}
	~Board() {
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				delete BoardMat[i][j];
			}
		}

	}
};
int main(int* argc, char** argv)
{
	//srand(unsigned int(time(NULL)));
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	SDL_Window* window = SDL_CreateWindow("2048", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 400, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 2);
	SDL_Event event;
	bool isRunning = true;
	Board board;
	SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
	while (isRunning) {
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)isRunning = false;
			if (event.type = SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:isRunning = false; break;
				case SDLK_RIGHT:board.moveright(); std::cout << "press"; break;
				case SDLK_LEFT:board.moveleft(); break;
				case SDLK_UP:board.moveup(); break;
				case SDLK_DOWN:board.movedown(); break;
				}
			}
			if (event.type = SDL_KEYUP)
			{
				switch (event.key.keysym.sym) {
				case SDLK_RIGHT:break;
				}
			}
		}
		SDL_RenderClear(renderer);
		board.draw(renderer);
		SDL_RenderPresent(renderer);

	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();
	return 0;
}
