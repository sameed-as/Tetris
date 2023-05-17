/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You need to define the required function in the part instructed here below.
 * Avoid making any unnecessary changes, particularly the ones you don't understand.
 * The different pieces should be defined using an array - uncomment the following code once you are done creating the array.
 * TIP: Understand thoroughly before getting started with coding.
 * */

//---Piece Starts to Fall When Game Starts---//
void fallingPiece(float& timer, float& delay, int& colour_num, int &number){
    int n = 0;
    if (timer>delay){
        for (int i=0;i<4;i++){
            point_2[i][0]=point_1[i][0];
            point_2[i][1]=point_1[i][1];
            point_1[i][1]+=1;                   //How much units downward
        }
        if (!anamoly()){
        	for(int i = 0; i < 4;i++)
        		gameGrid[point_2[i][1]][point_2[i][0]] = colour_num;
           
            n=rand()%8 ;
            //--- Un-Comment this Part When You Make BLOCKS array---//
            if(n != 7 && number  != 10)
            {
            	 colour_num = rand()%7 + 1;
                 for (int i=0;i<4;i++){
                    point_1[i][0] = BLOCKS[n][i] % 2 + (N/2) - 1;
                    point_1[i][1] = BLOCKS[n][i] / 2;
                }
            }
        }
        timer=0;
        if(n == 7 || number == 10)
        {
        number = 10;
        colour_num = rand()%7 + 1;
                 for (int i=0;i<4;i++){
                    point_1[i][0] = BLOCKS[n - 1][i] % 2 + (N/2) - 1;
                    point_1[i][1] = BLOCKS[n - 1][i] / 2;
                }
        }
    }
}

/////////////////////////////////////////////
///*** START CODING YOUR FUNTIONS HERE ***///

//To display score
sf::Text score(int points, sf::Font font, bool gameover)
{
	// variable of type sf::Text
	
      	sf::Text t;
      	t.setFont(font);
      	t.setString("Score : " + std::to_string(points));
      	t.setCharacterSize(12);
      	if(!gameover)
      	{
      		t.setPosition(240,200);
      		t.setFillColor(sf::Color(255, 250, 160));
      		return t;
      	}
      	else
      	{
      		t.setPosition(85,200);
      		t.setFillColor(sf::Color(255, 250, 160));
      		return t;
      	}
}

int highest()
{
	int highest = 0;
	int x = 0;
	bool flag = true;
	// to find the lowest block in the shape
	for(int i = 0; i < 4; i++)
	{
		if(highest < point_1[i][1])
			highest = point_1[i][1];
	}
	
	//to find the difference between the lowest point and the bottom
	for(int i = 1; i < 20; i++)
	{
		flag = true;
		for(int j = 0; j < 4; j++)
		{
			//keep on iterating rows until end is reached
			if(gameGrid[point_1[j][1] + i][point_1[j][0]] != 0 || highest == M - 1)
			{
				flag = false;
				break;
			}
		}
		//iterate the variable 'x' when a row can be moved downwards
		if(flag)
		{
			highest += 1;
			x++;
		}
		else
			break;
	}
	return x;
}

//to show shadow of four seperate blocks
//shadow of first block
sf::Sprite shadow_block1(sf::Sprite &shadow, int x)
{
	shadow.setPosition((point_1[0][0]+1.55) * 18  , (point_1[0][1] + x + 1.70)*18);
	return shadow;
}
//shadow of second block
sf::Sprite shadow_block2(sf::Sprite &shadow, int x)
{
	shadow.setPosition((point_1[1][0]+1.55) * 18  , (point_1[1][1] + x + 1.70)*18);
	return shadow;
}
//shadow of third block
sf::Sprite shadow_block3(sf::Sprite &shadow, int x)
{
	shadow.setPosition((point_1[2][0]+1.55) * 18  , (point_1[2][1] + x + 1.70)*18);
	return shadow;
}
//shadow of fourth block
sf::Sprite shadow_block4(sf::Sprite &shadow, int x)
{
	shadow.setPosition((point_1[3][0]+1.55) * 18  , (point_1[3][1] + x + 1.70)*18);
	return shadow;
}

//to deploy the bomb
void bombing(sf::Sprite &bomb, bool  &bomb_falling, int &number, float &timer, float delay, int &bombx, int &bomby, int &bomby2, int &bomb_colour, int colour_num)
{
	// generates random column for bomb
	if(!bomb_falling)
	{
		bombx = rand()%N;
		
	}
	if(timer>delay - 0.2)
	{
	//std::cout << bomby << "asass" << std::endl;
	// adds 1 in next row of bomb
		bomby2++;
		// bomby2 check the future position of row of the bomb is less then number of rows
		if(bomby2<M - 1)
		{
			// checks if the next row of bomb have a block
			if(gameGrid[bomby2 + 1][bombx] == 0)
			{	
				// stores the next value in current			
				bomby = bomby2;	
			}
			else
			{
				//bomb_falling becomes false and number becomes less then 10 so normal peices can start falling
				if(gameGrid[bomby2 + 1][bombx] == bomb_colour)
				// if colour of bomb matches with that of the block it lands on
				{
					for(int i = 0; i < M; i++)
						for(int j = 0; j < N; j++)
						{
							gameGrid[i][j] = 0;
						}
				}
				// if the colour of bomb does not match with colour of block it lands on
				else
				{
				int count = 0;
				int rowNum = 0, colNum = 0;
					for(int j = bombx; j < bombx + 2; j++)
					{
						for(int i = bomby2 + 1; i < bomby2 + 3; i++)
						{
							if(i < M && j < N)
								gameGrid[i][j] = 0;
						}
					}
				}
				
				number = 1;
				bomb_falling = false;
				bomby2 = 0;
				bomby = 0;
				bombx = 0;
			}
		}
		else
			{
				//bomb_falling becomes false and number becomes less then 10 so normal peices can start falling
				number = 1;
				bomb_falling = false;
				bomby2 = 0;
				bomby = 0;
				bombx = 0;
			}
	timer = 0;
	}
	
	//std::cout << bomby2 << std::endl;
}

void colourBomb(sf::Sprite &bomb, int &bomb_colour)
{
	bomb_colour = rand()%7 + 1;
	switch(bomb_colour)
	{
		case 1:
			bomb.setColor(sf::Color::Red);
			break;
		case 2:
			bomb.setColor(sf::Color::Green);
			break;
		case 3:
			bomb.setColor(sf::Color(255, 192, 203));
			break;
		case 4:
			bomb.setColor(sf::Color(255, 165, 0));
			break;
		case 5:
			bomb.setColor(sf::Color::Blue);
			break;
		case 6:
			bomb.setColor(sf::Color(0, 0, 139));
			break;
		case 7:
			bomb.setColor(sf::Color::Yellow);
			break;
	}
}

//for rotating the block
void rotator(bool rotate)
{
	int offsetx;
	int offsety;
	int wallKick = 0;
	int flag = true;
	int extreme = 0;
	
	for(int i = 0; i <= 10;i++)
	{
	// to check if shape is a block
		if(point_1[0][0] - i == 0 && point_1[1][0] - i == 1 && point_1[2][0] - i == 0 && point_1[3][0] - i == 1)
		{
			rotate = false;
		}
	}
	if(rotate)
	{
		for(int i = 0; i < 4; i++)
		{
			//calculating the diffrence between the block of rotation and other blocks
			offsetx = point_1[i][0] - point_1[2][0];    
			offsety = point_1[i][1] - point_1[2][1];
		
			point_1[i][1] = point_1[2][1]  - offsetx;
			point_1[i][0] = point_1[2][0] + offsety;
		}
		// to make sure pieces dont go out of bound when rotated
		
		
		// for line piece as it needs to be moved 2 tmes
		for(int i = 0; i < 4; i++)
		{
			if(point_1[i][0] < 0)
			{
				for(int j = 0; j < 4; j++)
				{
					if(point_1[j][0] < extreme)
						extreme = point_1[j][0];
					wallKick = -extreme;
				}

			}
			else if(point_1[i][0] > 9)
			{
				for(int j = 0; j < 4; j++)
				{
					if(point_1[j][0] > extreme)
						extreme = point_1[j][0];
					wallKick = -extreme + 9;
				}

			}
		}
		for(int i = 0; i < 4; i++)
			point_1[i][0] = point_1[i][0] + wallKick;
		
		for(int i = 0; i < 4; i++)
			if(gameGrid[point_1[i][1]][point_1[i][0]] != 0)
			{
				flag = false;
				break;
			}
		if(flag == false)
		{
			for(int i = 0; i < 4; i++)
			point_1[i][0] = point_1[i][0] - wallKick;
			for(int i = 0; i < 4; i++)
			{
				//calculating the diffrence between the block of rotation and other blocks
				offsetx = point_1[i][0] - point_1[2][0];    
				offsety = point_1[i][1] - point_1[2][1];
		
				point_1[i][1] = point_1[2][1]  + offsetx;
				point_1[i][0] = point_1[2][0] - offsety;
			}
		}
		
	}
}

//To move the piece to left
void moveLeft(int x, int colour_num)
{	
	bool can_move = true;	// to check if peice can move left or right
	
	for (int i=0;i<4;i++)
	{
		if(point_2[i][0] == 0 || gameGrid[point_2[i][1] + 1][point_2[i][0] - 1]) // To check if blocks are already placed in neighbouring cells
		{
			can_move = false;
			break;
   		}
   	}
   	if(can_move != false)
   	{
   		for(int j = 0; j < 4; j++)
		{
   			point_1[j][0] = point_1[j][0]  - 1;      //amount of blocks to move to left
   			point_2[j][0] = point_1[j][0];
			point_2[j][1] = point_1[j][1];
    		}
    	}
}

//To move the piece to right
void moveRight(int x, int colour_num)
{
	bool can_move = true;       // to check if peice can move left or right
	for (int i=0;i<4;i++)
	{
		if(point_2[i][0] == 9 || gameGrid[point_2[i][1] + 1][point_2[i][0] + 1]) // To check if blocks are already placed in neighbouring cells
		{
			can_move = false;
			break;
   		}
   	}
   	if(can_move != false)
   	{
   		for(int j = 0; j < 4; j++)
		{
   			point_1[j][0] = point_1[j][0] + 1;       //amount of blocks to move to Right
   			point_2[j][0] = point_1[j][0];
			point_2[j][1] = point_1[j][1];
			
    		}
    	
    	}
    
}

// when space key is pressed move block down instantly
void instant_down(bool is_pressed)
{
	static int val;
	bool flag;
	// checks if key is pressed
	if(is_pressed == true)
	{
		//checks if check variable is zero
		if(val == 0)
		{
			// changes the value of check variable so command is executed once
			val =1;
			// loop to check all the rows
			for(int i = 0; i < M; i++)
			{
				flag = true;
				for(int j = 0; j < 4; j++)
				{
					//checks if the value in next row below columns of shape is filled on game grid
					if (gameGrid[point_1[j][1] + 1][point_1[j][0]] != 0 || point_1[j][1] == M - 1)
					{
						//If row is filled the loop breaks
						flag = false;
						break;
					}
				}
				// if row is empty shape moves down by one
				if(flag == true)
				{
					for(int j = 0; j < 4; j++)
					{
						point_1[j][1] += 1;
						point_2[j][1] = point_1[j][1];
					}
				}
				// if row is filled the loop break setting the value
				else
				{
					break;
				}
			}
		}
	}
	//when space key is release check variable becomes zero so ftn can execute again
	else
	{
		val = 0;
	}
}

// to check if lines are made
int linebreaker( ) 
{
	int points = 0;
	bool matched = true;
	int row[20] = {0};
    	int multiplier = 1;
            for(int i = 0; i < M; i++)
            {
            	matched = true;
            	for(int j =0; j < N; j++) //check which rows are matched
            	{
            		if(gameGrid[i][j] == 0)
            		{
            			matched = false;
            		}	
            	}
            	if(matched == true)  //store the number of row that is matched
            	{
            		row[i] = 1;
            		points += multiplier * 10;
            		multiplier+= 1;
            	}
            }
            //multiplier = 0;
            int offset = 0;
            
            for(int i = M - 1; i >= 0; i--)
            {
            	if(row[i] == 1)
            	{
            		for(int j = i; j >= 1; j--)
            		{
            			for(int k =0; k < N; k++) 
            			{
            				gameGrid[j + offset][k] = gameGrid[j - 1 + offset][k];  // replace the matched row with one above
            			}
            			
            		}
            		offset++;
            	}
            }
	    return points;
}

//to pause the game
void pause(bool &gamepause)
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::H))
	{
		gamepause = true;
	}	
}

int pause_menu(sf::Vector2i pos)
{
	if((pos.x > 55 && pos.y > 150) && (pos.x < 181 && pos.y <179))
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		return 1;
	
	if((pos.x > 55 && pos.y > 150 + 50) && (pos.x < 181 && pos.y <179 + 50))
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		return 2;	
		
	if((pos.x > 55 && pos.y > 150 + 100) && (pos.x < 181 && pos.y <179 + 100))
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		return 3;	
	
	if((pos.x > 55 && pos.y > 150 + 150) && (pos.x < 181 && pos.y <179 + 150))
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		return 4;	
	
	if((pos.x > 55 && pos.y > 150 + 200) && (pos.x < 181 && pos.y <179 + 200))
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		return 5;
	
	return 0;
}
//checks if the game is over
void game_over(bool &gameover)
{
	for(int i = 5; i < 7; i++)
	{
		if(gameGrid[0][i] != 0 || gameGrid[1][i] != 0)
		{
			for(int j = 0; j < M; j++)
				for(int k = 0; k < N; k++)
					gameGrid[j][k] = 0;
			gameover = true;
		}
	}
}
// to create menu
int menu(bool &gamestart, sf::Vector2i pos)
{
	if((pos.x > 55 && pos.y > 150) && (pos.x < 181 && pos.y <179))
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		return 1;
	
	if((pos.x > 55 && pos.y > 150 + 50) && (pos.x < 181 && pos.y <179 + 50))
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		return 2;	
		
	if((pos.x > 55 && pos.y > 150 + 100) && (pos.x < 181 && pos.y <179 + 100))
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		return 3;	
	
	if((pos.x > 55 && pos.y > 150 + 150) && (pos.x < 181 && pos.y <179 + 150))
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		return 4;	
	return 0;
}

//to count time passed
sf::Text timePassed(int time_passed, sf::Font font, bool gameover, int mins_passed)
{
	// variable of type sf::Text
	
      	sf::Text t;
      	t.setFont(font);
		if (time_passed < 10)
		{
			t.setString("Time: " + std::to_string(mins_passed) + " : " + '0' + std::to_string(time_passed));	
		}
		else
		{
			t.setString("Time: " + std::to_string(mins_passed) + " : " + std::to_string(time_passed));
		}
      	//t.setString("Time: " + std::to_string(mins_passed) + " : " + std::to_string(time_passed));
      	t.setCharacterSize(12);
      	if(!gameover)
      	{
      		t.setPosition(240,300);
      		t.setFillColor(sf::Color(255, 250, 160));
      		return t;
      	}
      	else
      	{
      		t.setPosition(85,300);
      		t.setFillColor(sf::Color(255, 250, 160));
      		return t;
      	}
}

void levelNum(int &level, int time_passed)
{
		level = time_passed + 1;
		//std::cout << level;
}

sf::Text lvl_disp(sf::Font font, int lvlNum, bool gameover)
{
	sf::Text t;
      	t.setFont(font);
      	t.setString("Level: " + std::to_string(lvlNum));
      	t.setCharacterSize(12);
      	if(!gameover)
      	{
      		t.setPosition(240,250);
      		t.setFillColor(sf::Color(255, 250, 160));
      		return t;
      	}
      	else
      	{
      		t.setPosition(85,250);
      		t.setFillColor(sf::Color(255, 250, 160));
      		return t;
      	}
}

//to operate the menue of gameover
int GO_menu(sf::Vector2i pos, bool &gameover)
{
	if((pos.x > 45 && pos.y > 330) && (pos.x < 117 && pos.y <359))
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			gameover = false;
			return 1;
		}
	if((pos.x > 125 && pos.y > 330) && (pos.x < 197 && pos.y <359))
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			return 2;
	return 0;
}

//calculate highscore
void highscore_ftn()
{
	
}
///*** YOUR FUNCTIONS END HERE ***///
/////////////////////////////////////
