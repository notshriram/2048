#define SDL_MAIN_HANDLED
#include"SDL.h"
#include<time.h>
#include<iostream>
class Tile {
public:
	int val;
	Tile() { if ((rand() % 11) > 8)val = 4; else val = 2; }
	Tile(int val) :val(val) {}
	const int GetVal() const{ return val; }
};
class Board {
public:
	Tile* BoardMat[4][4];
	Board() {
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				BoardMat[i][j] = nullptr;
		int row = rand() % 4;
		int col = rand() % 4;
		BoardMat[row][col] = new Tile();
	}
	void draw(SDL_Renderer* renderer) {
		
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
			{
				SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
				SDL_Rect r= {100*i,100*j,100,100};
				if (BoardMat[i][j] != nullptr)
				{
					int value = BoardMat[i][j]->GetVal();
					SDL_SetRenderDrawColor(renderer,(10*value)%256, (20 * value)%256, (30 * value)%256,255);
				}
				SDL_RenderFillRect(renderer, &r);

			}
		
	}

};
int main(int* argc, char** argv)
{
	srand(unsigned int(time(NULL)));
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("2048", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 400, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 2);
	SDL_Event event;
	bool isRunning = true;
	Board board;
	SDL_SetRenderDrawColor(renderer,200,200,200,255);
	while (isRunning) {
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)isRunning = false;
			if (event.type=SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:isRunning = false; break;
				
				}
			}
		}
		SDL_RenderClear(renderer);
		board.draw(renderer);
		SDL_RenderPresent(renderer);
	
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}