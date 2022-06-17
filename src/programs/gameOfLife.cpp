/**
 * @file noise.cpp
 * @author Leo Burke
 * @date 2021-12-06
 * 
 */

#include "zylProg.h"

static class : public zylProg{
private:
	int speed = 1;
	int colorId = 0;
	#define xSize (X_RES + 4)
	#define ySize (Y_RES + 4)
	int board[xSize][ySize] = {{0}};
	int oldBoard[xSize][ySize] = {{0}};
	long nextStepTime = 0;
	int frameTime = 800;										//time between steps in millis
	int waitOnReset = 1000;                 //time to wait between finished game and reset in millis

	void stepGame(){
		for (int stage = 0; stage < 4; stage++){							//iterates over the three calculation stages as each needs to loop over every cell
			for (int x = 0; x < xSize; x++){
				for (int y = 0; y < ySize; y++){
					switch (stage){
					case 0:
						oldBoard[x][y] = board[x][y];									//sets oldBoard to current state
						board[x][y] = 0;															//resets the board
						break;

					case 1:																					//add 1 to every cell adjacient to a positive non border cell
						if (x!=0 && y!=0 && x+1<xSize && y+1<ySize){	//dont iterate over border cells to accomodate -1/+1
							for (int xx = -1; xx < 2; xx++){
								for (int yy = -1; yy < 2; yy++){
									board[x+xx][y+yy] += oldBoard[x][y];
								}
							}
							board[x][y] -= oldBoard[x][y];							//subtracts old value from cell itself as it got added in the loop before
						}
						break;

					case 2:																					//calculate life or death from value
						if (x!=0 && y!=0 && x+1<xSize && y+1<ySize){	//only calculate for non border cells

							if (oldBoard[x][y] == 1)										//for living cells stay alive if 2 or 3 neighbors
								(board[x][y]>1 && board[x][y]<4) ? board[x][y] = 1 : board[x][y] = 0;
							else																				//for dead cells come alive if exactly 3 neighbors
								oldBoard[x][y] == 3 ? board[x][y] = 1 : board[x][y] = 0;
							
						} else {																			//set border cells to 0
							board[x][y] = 0;
						}
						break;
					case 3:
						board[x][y] == 0 ? m_FB[x][y] = CRGB::Black : m_FB[x][y] = zylProgManager::getColor(colorId);
					}
				}
			}
		}
	}
	void setupBoard(){
		int density = random(4,8);
		for (int x = 1; x < xSize-1; x++){
			for (int y = 1; y < ySize-1; y++){
				board[x][y] = (random(0,density) == 0) ? 1 : 0;
			}
		}
	}
public:
	using zylProg::zylProg;
	int init(){
		m_Id = 132;
		return 0;
		setupBoard();
	}
	void render(){
		if (nextStepTime < millis()){
			stepGame();
			FastLED.show();

			if (oldBoard == board) {											//detects a finished game
				setupBoard();
				nextStepTime = millis() + waitOnReset;					//sets a time when the next game will start
			} else {
				nextStepTime = millis() + frameTime;
			}
			
		}
	}

	void input(uint8_t x, uint8_t y, uint8_t z){
		switch(x){
		case 0:
			speed = y;
			break;
		case 1:
			colorId = y;
		}
	}
} gameOfLife(false);