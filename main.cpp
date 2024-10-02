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
/* Ahmed Ali Zahid CS-A 22i-1271*/
#include <SFML/Graphics.hpp>
#include <sstream>
#include <time.h>
#include "utils.h"
#include "pieces.h"
#include "functionality.h"
using namespace sf;
int main()
{
    initializeGrid();
    srand(time(0));
    RenderWindow window(VideoMode(320, 480), title);
    Texture obj1, obj2, obj3, obj4, obj5, obj6;
    obj1.loadFromFile("img/tiles.png");
    obj2.loadFromFile("img/image.png");
    obj3.loadFromFile("img/frame.png");
    obj4.loadFromFile("img/dim.png");
    obj5.loadFromFile("img/tiles.png");
    obj6.loadFromFile("img/blast.png");
    /*
        Load "frames.png","tiles.png" and "background.png" for Texture objects
    */

    // text part i.e. score, lines cleared etc.
    Font design;
    design.loadFromFile("font/Carlito-Bold.ttf");
    Text score, line, scoreName, linesName, ovrMsg1, ovrMsg2, nxtShape;
    score.setFont(design);
    line.setFont(design);
    nxtShape.setFont(design);
    scoreName.setFont(design);
    linesName.setFont(design);
    ovrMsg1.setFont(design);
    ovrMsg2.setFont(design);
    score.setCharacterSize(15);
    line.setCharacterSize(15);
    ovrMsg1.setCharacterSize(25);
    ovrMsg2.setCharacterSize(25);
    scoreName.setCharacterSize(15);
    linesName.setCharacterSize(15);
    nxtShape.setCharacterSize(15);

    nxtShape.setString("Next Shape");
    scoreName.setString("Score");
    linesName.setString("Lines Cleared");
    ovrMsg1.setString("Game Over!");
    ovrMsg2.setString("Press Enter to Exit");

    // End of text part

    Sprite sprite(obj1), background(obj2), frame(obj3), shadow(obj4), nextBlock(obj5), bomb(obj6);

    // Variables Declaration
    int delta_x = 0, points = 0, elapsed = 0, lines = 0, colorNum = rand() % 8, nxtPiece = rand() % 7, nxtColor = rand() % 8;
    int nxtBlock[4][2], tmp_1[4][2], tmp_2[4][2];           // tmp arrays are for shadow
    int bomb_1[1][1], bomb_2[1][1], colorBomb = rand() % 8; // for bomb coordinates and colors
    float timer = 0, delay = 0.3;
    std::stringstream scr, lns, scrT, lnsT;

    // skip will skip fallingpiece fn in case instant/hard drop fn is called
    // firstRun run when game starts thus replacing the first single block tetromino
    bool rotate = false, firstRun = true, lvlUP = false, skip = false; // bomb=false;
    // Variables Declaration End

    Clock clock;
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        //---Event Listening Part---//
        Event e;
        while (window.pollEvent(e))
        {                                // Event is occurring - until the game is in running state
            if (e.type == Event::Closed) // If cross/close is clicked/pressed
                window.close();          // Opened window disposes
            if (e.type == Event::KeyPressed)
            {                                           // If any other key (not cross) is pressed
                if (e.key.code == Keyboard::Up)         // Check if the other key pressed is UP key
                    rotate = true;                      // Rotation gets on
                else if (e.key.code == Keyboard::Left)  // Check if the other key pressed is LEFT key
                    delta_x = -1;                       // Change in X-Axis - Negative
                else if (e.key.code == Keyboard::Right) // Check if the other key pressed is RIGHT key
                    delta_x = 1;                        // Change in X-Axis - Positive
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Down))  // Just another way to detect key presses without event listener
            delay = 0.05;                            // If DOWN key is pressed, delay in falling piece decreases from 0 to 0.05
        if (Keyboard::isKeyPressed(Keyboard::Space)) // Will instantly move a shape to bottom of gamegrid
        {
            instantDrop(colorNum);
            skip = true;
        }

        ///////////////////////////////////////////////
        if (firstRun)
        {
            firstRunFn(colorNum, nxtPiece, nxtColor, nxtBlock);
            firstRun = false;
        } // first run function to get rid of first block

        if (!skip)
            fallingPiece(timer, delay, colorNum, nxtPiece, nxtColor, nxtBlock);
        // Example: fallingPiece() function is called here

        shadowFn(delta_x, colorNum, tmp_1, tmp_2); // shadow function

        if (delta_x)
            movementFn(delta_x); // Calling the movement function (left and right movement)

        if (rotate)
            rotationFn();
        checkLine(points, lines); // checks if a line is completely filled, if filled it clears it

        if (!gameEnd())
        {
            // Displaying GameOver Menu
            window.clear(Color::Black);
            scrT << points; // updating points i.e. score
            lnsT << lines;  // updating lines cleared
            score.setString(scrT.str());
            line.setString(lnsT.str());
            while (!(Keyboard::isKeyPressed(Keyboard::Enter)))
            {
                scoreName.setPosition(135, 100);
                score.setPosition(150, 130);
                linesName.setPosition(110, 155);
                line.setPosition(150, 180);
                ovrMsg1.setPosition(90, 210); // GameOver
                ovrMsg2.setPosition(60, 250); // Press Enter to Continue
                window.draw(background);
                window.draw(scoreName);
                window.draw(score);
                window.draw(linesName);
                window.draw(line);
                window.draw(ovrMsg1);
                window.draw(ovrMsg2);
                window.display();
            }
            break;
        }

        defaults(delta_x, delay, rotate, skip);

        lvlUp(points, delay);
        ///*** YOUR CALLING STATEMENTS END HERE ***///
        //////////////////////////////////////////////

        window.clear(Color::Black);
        window.draw(background);
        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (gameGrid[i][j] == -1)
                    continue;
                sprite.setTextureRect(IntRect(gameGrid[i][j] * 18, 0, 18, 18));
                sprite.setPosition(j * 18, i * 18);
                sprite.move(28, 31); // offset
                window.draw(sprite);
            }
        }

        // setting position of shadow and drawing it on screen
        for (int i = 0; i < 4; i++)
        {
            shadow.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
            shadow.setPosition(tmp_2[i][0] * 18, tmp_2[i][1] * 18);
            shadow.move(28, 31);
            window.draw(shadow);
        }
        for (int i = 0; i < 4; i++)
        {
            sprite.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
            sprite.setPosition(point_1[i][0] * 18, point_1[i][1] * 18);
            sprite.move(28, 31);
            window.draw(sprite);
        }
        // setting position of next block on screen and displaying it
        for (int i = 0; i < 4; i++)
        {
            nextBlock.setTextureRect(IntRect(nxtColor * 18, 0, 18, 18));
            nextBlock.setPosition(nxtBlock[i][0] * 18, nxtBlock[i][1] * 18);
            nextBlock.move(260, 150);
            window.draw(nextBlock);
        }

        // displaying scores,lines
        std::stringstream scr, lns;      // scr for score,lns for lines
        scr << points;                   // updating points i.e. score
        lns << lines;                    // updating lines cleared
        nxtShape.setPosition(240, 110);  // nxt shape heading position
        scoreName.setPosition(250, 250); // score string position
        score.setString(scr.str());      // storing points in string
        score.setPosition(265, 280);     // setting points position
        linesName.setPosition(230, 310); // setting lines string position
        line.setString(lns.str());       // updating lines cleared value in string
        line.setPosition(265, 340);      // setting lines cleared value position

        // drawing next shape,score,lines
        window.draw(nxtShape);
        window.draw(scoreName);
        window.draw(score);
        window.draw(linesName);
        window.draw(line);

        //---The Final on Which Everything is Drawn Over is Loaded---//
        window.draw(frame);
        //---The Window that now Contains the Frame is Displayed---//
        window.display();
    }
    return 0;
}
