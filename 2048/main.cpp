#define SDL_MAIN_HANDLED
#include"SDL.h"
#include"SDL_ttf.h"
#include<time.h>
#include<string>
#include<iostream>
SDL_Color white = { 255,255,255,255 };
class Tile {
public:
	int val;
	Tile() { if ((rand() % 11) > 8)val = 4; else val = 2; }
	Tile(int val) :val(val) {}
	const int GetVal() const{ return val; }
};
class Board {
public:
	TTF_Font* font = TTF_OpenFont("Roboto-Light.ttf", 32);
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
					SDL_SetRenderDrawColor(renderer, (10 * value) % 256, (20 * value) % 256, (30 * value) % 256, 255);
					SDL_Surface* surface = nullptr;
					SDL_Texture* texture = nullptr;
					surface = TTF_RenderText_Solid(font,std::to_string(value).c_str(),white);
					texture = SDL_CreateTextureFromSurface(renderer, surface);
					int recw, rech;
					SDL_QueryTexture(texture,NULL,NULL,&recw,&rech);
					SDL_Rect dstrect = { 100*i+29,100*j+29,recw,rech};
					SDL_RenderFillRect(renderer, &r);
					SDL_RenderCopy(renderer, texture, NULL, &dstrect);
					SDL_FreeSurface(surface);
					SDL_DestroyTexture(texture);
				}
			}
	}
	void moveright() 
	{
		for(int i=0;i<4;i++)
			for (int j = 0; j < 4; j++)
			{	
				if (BoardMat[i][j] != nullptr)
				{
					if (i < 3) {
						if (BoardMat[i+1][j] == nullptr)
						BoardMat[i+1][j] = BoardMat[i][j];
						BoardMat[i][j] = nullptr;
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
			if(BoardMat[row][col]==nullptr) { BoardMat[row][col] = new Tile();break; }
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
	srand(unsigned int(time(NULL)));
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
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
				case SDLK_RIGHT:board.moveright(); break;
				case SDLK_LEFT:board.moveright(); break;
				case SDLK_UP:board.moveright(); break;
				case SDLK_DOWN:board.moveright(); break;
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