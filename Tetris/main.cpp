/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You don't need to change anything in the driver code/main function except the part(s) where instructed.
 * You are expected to define your functionalities in the "functionality.h" header and call them here in the instructed part(s).
 * The game is started with a small box, you need to create other possible in "pieces.h" file in form of array.
    E.g., Syntax for 2 pieces, each having four coordinates -> int Pieces[2][4];
 * Load the images into the textures objects from img directory.
 * Don't make any changes to the "utils.h" header file except for changing the coordinate of screen or global variables of the game.
 * SUGGESTION: If you want to make changes in "utils.h", do it once you complete rest of the functionalities.
 * TIP: You can study SFML for drawing scenes, sprites and window.
 * */

#include<iostream>
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <time.h>
#include "utils.h"
#include "pieces.h"
#include "functionality.h"
using namespace sf;
int main(){
    srand(time(0));
    RenderWindow window(VideoMode(320, 480), title);
    Texture obj1, obj2, obj3;
    Texture obj4, obj5, obj6;
    //Load "frames.png","tiles.png" and "background.png" for Texture objects
    obj1.loadFromFile("img/tiles.png");
    obj2.loadFromFile("img/background.png");
    obj3.loadFromFile("img/frame.png");
    
    obj4.loadFromFile("img/shadow.png");
    Sprite shadow(obj4);
    
    obj5.loadFromFile("img/bomb.png");
    Sprite bomb(obj5);
    
    obj6.loadFromFile("img/button.png");
    Sprite button(obj6);
    button.setScale(0.7f, 0.7f);
    button.setColor(sf::Color(255,255,255,200));
    
    sf :: Font font;
    font.loadFromFile("fonts/Gameplay.ttf");
    
    sf::Music theme_song;
    theme_song.openFromFile("sound/main_track.ogg");
    theme_song.play();
    
    sf::SoundBuffer bomb_buffer;
    bomb_buffer.loadFromFile("sound/explosion.ogg");
    
    sf::Sound bomb_sound;
    bomb_sound.setBuffer(bomb_buffer);
    //bomb_sound.play();
    
    Sprite sprite(obj1), background(obj2), frame(obj3);
    int delta_x=0, colorNum= rand()%7 + 1, bomb_colour = 0;
    float timer=0, delay=0.3;
    bool rotate=0;
    int points = 0;
    int delta_shadow = 0;
    bool bomb_falling = false;
    int number = rand()%10, bombx = 0, bomby = 0,bomby2 = 0;
    bool gameover = false,gamepause = false , gamestart = false, help = false, high = false, closewindow = false;
    int selection = 0, pause_selection = 0, GO_selection = 0;
    float time_passed = 0, mins_passed = 0;;
    int level = 1;
    
    
    Clock clock;
    int first_block = rand() % 7;
    for (int i=0;i<4;i++)
    {
        point_1[i][0] = BLOCKS[first_block][i] % 2 + (N/2) - 1;
        point_1[i][1] = BLOCKS[first_block][i]  /  2;
    }
    window.setVisible(true);
    while (window.isOpen()){
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;
	
        //---Event Listening Part---//
        Event e;
        while (window.pollEvent(e)){                    //Event is occurring - until the game is in running state
            if (e.type == Event::Closed)                   //If cross/close is clicked/pressed
                window.close();                            //Opened window disposes
            if (e.type == Event::KeyPressed) {             //If any other key (not cross) is pressed
                if (e.key.code == Keyboard::Up)            //Check if the other key pressed is UP key
                    rotate = true;                         //Rotation gets on
                else if (e.key.code == Keyboard::Left)     //Check if the other key pressed is LEFT key
                    delta_x = -1;                          //Change in X-Axis - Negative
                else if (e.key.code == Keyboard::Right)    //Check if the other key pressed is RIGHT key
                    delta_x = 1;                           //Change in X-Axis - Positive
            }
        }
        // to insure that delay does not change when bomb falls
        if(bomb_falling == false && number < 10)
		{
        	if (Keyboard::isKeyPressed(Keyboard::Down))   //Just another way to detect key presses without event listener
            	delay=0.05 - (level - 1) * 0.001;                                    //If DOWN key is pressed, delay in falling piece decreases from 0 to 0.05
		}	

        ///////////////////////////////////////////////
        ///*** START CALLING YOUR FUNCTIONS HERE ***///
	
	
      	
      	if(gamestart)
      	{
      		game_over(gameover);
			bomb_sound.play();
			if(!gameover)
			{
				//theme_song.play();
				pause(gamepause);
			
				if(!gamepause)
				{
					levelNum(level, mins_passed);
					if(bomb_falling == false && number < 10)
					{
						//points += linebreaker();
					
						bomby2 = 0;
						fallingPiece(timer, delay, colorNum, number);
						instant_down(Keyboard::isKeyPressed(Keyboard::Space));
        		
      		 			if(delta_x == -1)
        				{
        					moveLeft(delta_x, colorNum);
        				}
        				else if(delta_x == 1)
        				{
        					moveRight(delta_x, colorNum);
        				}
        	
        				fallingPiece(timer, delay, colorNum, number);               //Example: fallingPiece() function is called here
       					points += linebreaker();
       					rotator(rotate);
        			}
        			else if(number == 10)
        			{
        				if(bomb_falling == true)
        				{
        					bombing(bomb, bomb_falling, number, timer, delay, bombx, bomby, bomby2, bomb_colour, colorNum);
        					bomb.setPosition(bombx*18,bomby*18);
        				}
        				else
        				{	
        					fallingPiece(timer, delay, colorNum, number);
        					colourBomb(bomb, bomb_colour);
        					bombing(bomb, bomb_falling, number, timer, delay, bombx, bomby, bomby2, bomb_colour, colorNum);
        					bomb_falling = true;
        					bomb.setPosition(bombx*18,0*18);
        				}
        			}
        				
       				delta_shadow = highest();
        	
        			delay=0.3 - (level - 1)* 0.05;
    				rotate=false;
    				delta_x = 0;
        		}
        		else if(gamepause == true && help == false && high == false)
        		{
        			Vector2i mousePosition;
        			mousePosition = sf::Mouse::getPosition(window);
        			
        			pause_selection = pause_menu(mousePosition);
        			int first_block_after_pause;
        			switch(pause_selection)
        			{
        				case 1:
        					gamestart = true;
        					gamepause = false;
        					points = 0;
        					time_passed = 0;
        					mins_passed = 0;
        					level = 0;
        					first_block_after_pause = rand() % 7;
    						for (int i=0;i<4;i++)
    						{
        						point_1[i][0] = BLOCKS[first_block_after_pause][i] % 2 + (N/2) - 1;
        						point_1[i][1] = BLOCKS[first_block_after_pause][i]  /  2;
    						}
    						for(int j = 0; j < M; j++)
								for(int k = 0; k < N; k++)
									gameGrid[j][k] = 0;
        					break;
        				case 2:
        					high = true;
        					break;
	        			case 3:
    	    				help = true;
        					break;
        				case 4:
        					closewindow = true;
        					break;
   		     			case 5:
        					gamepause = false;
        					break;
        			}
        		}
        	}
			else
			{
				Vector2i mousePosition;
        		mousePosition = sf::Mouse::getPosition(window);

				GO_selection = GO_menu(mousePosition, gameover);
        		int first_block_after_pause;
        		switch(GO_selection)
        		{
    				case 1:
    					gamestart = true;
        				gamepause = false;
        				points = 0;
        				time_passed = 0;
        				mins_passed = 0;
    					level = 0;
    					first_block_after_pause = rand() % 7;
    					for (int i=0;i<4;i++)
    					{
        					point_1[i][0] = BLOCKS[first_block_after_pause][i] % 2 + (N/2) - 1;
        					point_1[i][1] = BLOCKS[first_block_after_pause][i]  /  2;
    					}
    					for(int j = 0; j < M; j++)
							for(int k = 0; k < N; k++)
								gameGrid[j][k] = 0;
        				break;
					case 2:
						closewindow = true;
						break;
				}
			}
        }
        else if(gamestart == false && help == false && high == false)
        {
        	Vector2i mousePosition;
        	mousePosition = sf::Mouse::getPosition(window);
        	
        	selection = menu(gamestart, mousePosition);
        	switch(selection)
        	{
	        	case 1:
    	    		gamestart = true;
        			break;
	        	case 2:
    	    		high = true;
        			break;
      		  	case 3:
        			help = true;
        			break;
	        	case 4:
    	    		closewindow = true;
        			break;
        	}
        }
        if(closewindow)
        {
        	
        	Event closer;
        	while (window.pollEvent(closer))	//Event is occurring - until the game is in running state
        	{                    
        		if (closewindow)                   //If exit button is pressed 
            		window.close();
            }
                closewindow = false;
        }
        ///*** YOUR CALLING STATEMENTS END HERE ***///
        //////////////////////////////////////////////
	
        window.clear(Color::Black);
        window.draw(background);
        
        if(gamestart == true && gamepause == false)
    	{
			//to draw score
        	window.draw(score(points, font, gameover));
        	if(!gameover)
        	{
				time_passed += time;
			}

			//to calculate time in mins and sec
        	if((int)time_passed == 60)
        	{
        		mins_passed += 1;
        		time_passed = 0;	
        	}
        	
			//to draw level and time and place it acording to requirement
        	window.draw(timePassed((int)time_passed, font, gameover, mins_passed));
        	window.draw(lvl_disp(font, level, gameover));
        	
    	}
        
		//text displayed when game is over
        if(gameover)
        {
        	Text GO;
        	GO.setFont(font);
        	GO.setPosition(60, 150);
        	GO.setCharacterSize(18);
        	GO.setFillColor(Color(255, 250, 160));
        	GO.setString("GAME OVER");
        	window.draw(GO);

			button.setPosition(45,330);
			button.setScale(0.40f, 0.7f);
		    button.setColor(sf::Color(255,255,255,200));
			window.draw(button);
			Text restart;
			restart.setFont(font);
        	restart.setPosition(51, 338);
        	restart.setCharacterSize(12);
        	restart.setFillColor(Color(255, 250, 160));
        	restart.setString("Restart");
        	window.draw(restart);


			button.setPosition(125,330);
			button.setScale(0.40f, 0.7f);
		    button.setColor(sf::Color(255,255,255,200));
			window.draw(button);
			Text exit;
			exit.setFont(font);
        	exit.setPosition(146, 338);
        	exit.setCharacterSize(12);
        	exit.setFillColor(Color(255, 250, 160));
        	exit.setString("Exit");
        	window.draw(exit);
        }

        //to draw shadow of each individual block
        if(gameover == false && gamestart == true && gamepause == false)
        {
        	if(!bomb_falling)
        	{
        		window.draw(shadow_block1(shadow, delta_shadow));
        		window.draw(shadow_block2(shadow, delta_shadow));
        		window.draw(shadow_block3(shadow, delta_shadow));
        		window.draw(shadow_block4(shadow, delta_shadow));
        	}
        }
        
        //bomb.setPosition(bombx*18,bomby*18);
		//bomb droping animation
        bomb.move(28,31);
        if(bomb_falling)
        	window.draw(bomb);
        
        for (int i=0; i<M; i++){
            for (int j=0; j<N; j++){
                if (gameGrid[i][j]==0)
                    continue;
                sprite.setTextureRect(IntRect(gameGrid[i][j]*18,0,18,18));
                sprite.setPosition(j*18,i*18);
                sprite.move(28,31); //offset
                window.draw(sprite);
            }
        }
        if(gameover == false && gamestart == true && gamepause == false)
        {
        	if(!bomb_falling)
        	{
        		for (int i=0; i<4; i++){
            		sprite.setTextureRect(IntRect(colorNum*18,0,18,18));
            		sprite.setPosition(point_1[i][0]*18,point_1[i][1]*18);
            		sprite.move(28,31);
            		window.draw(sprite);
          		}
        	}
        }

        //drawing the pause menu
        if(gamepause == true && help == false && high == false)
        {
        	Text m;
        	m.setFont(font);
        	m.setPosition(35, 105);
        	m.setCharacterSize(22);
        	m.setFillColor(Color(255, 250, 160));
        	m.setString("GamePaused");
        	window.draw(m);
        	
        	button.setPosition(55,150);
			window.draw(button);
			Text startnewgame;
        	startnewgame.setFont(font);
        	startnewgame.setPosition(58, 158);
        	startnewgame.setCharacterSize(12);
        	startnewgame.setFillColor(Color(255, 250, 160));
        	startnewgame.setString("Start New Game");
        	window.draw(startnewgame);
        	
			button.setPosition(55,200);
			window.draw(button);
        	Text high;
        	high.setFont(font);
        	high.setPosition(75, 208);
        	high.setCharacterSize(12);
        	high.setFillColor(Color(255, 250, 160));
        	high.setString("High Scores");
        	window.draw(high);
        	
        	button.setPosition(55,250);
			window.draw(button);
        	Text help;
        	help.setFont(font);
        	help.setPosition(100, 258);
        	help.setCharacterSize(12);
        	help.setFillColor(Color(255, 250, 160));
        	help.setString("Help");
        	window.draw(help);
        	
        	button.setPosition(55,300);
			window.draw(button);
        	Text exit;
        	exit.setFont(font);
        	exit.setPosition(100, 308);
        	exit.setCharacterSize(12);
        	exit.setFillColor(Color(255, 250, 160));
        	exit.setString("Exit");
        	window.draw(exit);
        	
        	button.setPosition(55,350);
			window.draw(button);
        	Text cont;
        	cont.setFont(font);
        	cont.setPosition(85, 358);
        	cont.setCharacterSize(12);
        	cont.setFillColor(Color(255, 250, 160));
        	cont.setString("continue");
        	window.draw(cont);
        }

		//drawing the main menu
        if(gamestart == false && help == false && high == false)
        {
        	Text m;
        	m.setFont(font);
        	m.setPosition(80, 105);
        	m.setCharacterSize(24);
        	m.setFillColor(Color(255, 250, 160));
        	m.setString("MENU");
        	window.draw(m);
        	
        	button.setPosition(55,150);
			window.draw(button);
			Text startnewgame;
        	startnewgame.setFont(font);
        	startnewgame.setPosition(58, 158);
        	startnewgame.setCharacterSize(12);
        	startnewgame.setFillColor(Color(255, 250, 160));
        	startnewgame.setString("Start New Game");
        	window.draw(startnewgame);
        	
			button.setPosition(55,200);
			window.draw(button);
        	Text high;
        	high.setFont(font);
        	high.setPosition(75, 208);
        	high.setCharacterSize(12);
        	high.setFillColor(Color(255, 250, 160));
        	high.setString("High Scores");
        	window.draw(high);
        	
        	button.setPosition(55,250);
			window.draw(button);
        	Text help;
        	help.setFont(font);
        	help.setPosition(100, 258);
        	help.setCharacterSize(12);
        	help.setFillColor(Color(255, 250, 160));
        	help.setString("Help");
        	window.draw(help);
        	
        	button.setPosition(55,300);
			window.draw(button);
        	Text exit;
        	exit.setFont(font);
        	exit.setPosition(100, 308);
        	exit.setCharacterSize(12);
        	exit.setFillColor(Color(255, 250, 160));
        	exit.setString("Exit");
        	window.draw(exit);
        }
        
		//drawing the help menu
        if(help == true)
        {
        	Text hel;
        	hel.setFont(font);
        	hel.setPosition(37, 50);
        	hel.setCharacterSize(10);
        	hel.setFillColor(Color(255, 250, 160));
        	hel.setString("Press left arrow key to\n move left \n\nPress right arrow key to\n move right \n\nPress space to hard drop\n \nPress down arrow key to \nreduce delay\n \nPress up arrow key to \nrotate\n \nForm lines to earn \npoints\n\n\n\nPress right mouse button \nto go back");
        	window.draw(hel);
        	//if(timer > 0.5)
        	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        		help = false;
        }

		//drawing the highscore menue
        if(high == true)
        {
        	Text highscore;
        	highscore.setFont(font);
        	highscore.setPosition(37, 208);
        	highscore.setCharacterSize(10);
        	highscore.setFillColor(Color(255, 250, 160));
        	highscore.setString("High Scores ...\n\n\n\nPress right mouse button\n to go back");
        	window.draw(highscore);
        	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
        		high = false;
        }
        //---The Final on Which Everything is Drawn Over is Loaded---//
        window.draw(frame);
        //---The Window that now Contains the Frame is Displayed---//
        window.display();
    }
    return 0;
}
