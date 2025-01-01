/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
/* Ahmed Ali Zahid CS-A 22i-1271*/
/////////////////////////////////////////////
///*** FUNTIONS Start HERE ***///
void initGameGrid(){
  for(int i=0; i<M; i++){
    for(int j=0; j<N; j++){
      gameGrid[i][j] = -1;
    }
  }
}

void nxtBlockFn(int &nxtPiece, int &nxtColor, int nxtBlock[4][2])
{                        // nextBlock Guess Function
  nxtPiece = rand() % 7 ; // next piece
  nxtColor = rand() % 8 + 1 ; // next color
  for (int i = 0; i < 4; i++)
  {
    nxtBlock[i][0] = BLOCKS[nxtPiece][i] % 2;
    nxtBlock[i][1] = BLOCKS[nxtPiece][i] / 2;
  }
}

//---Piece Starts to Fall When Game Starts---//
void fallingPiece(float &timer, float &delay, int &colorNum, int &nxtPiece, int &nxtColor, int nextBlock[4][2])
{
  if (timer > delay)
  {
    for (int i = 0; i < 4; i++)
    {
      point_2[i][0] = point_1[i][0];
      point_2[i][1] = point_1[i][1];
      point_1[i][1] += 1; // How much units downward
    }
    if (!anamoly())
    {
      for (int i = 0; i < 4; i++)
      {
        gameGrid[point_2[i][1]][point_2[i][0]] = colorNum; // for storing the shape in gamegrid, color will be colorNum
      }
      int n = nxtPiece;
      colorNum = nxtColor;
      nxtBlockFn(nxtPiece, nxtColor, nextBlock);
      //--- Un-Comment this Part When You Make BLOCKS array---//

      for (int i = 0; i < 4; i++)
      {
        point_1[i][0] = BLOCKS[n][i] % 2; // it will extract random piece from BLOCKS, using value of n, as in BLOCKS array, each row has a different piece
        point_1[i][1] = BLOCKS[n][i] / 2; // same as above
      }
    }
    timer = 0;
  }
}

void checkLine(int &points, int &lines) // checks if a line is completely filled, if filled it clears it
{
  int k = M - 1, currLines = 0;
  for (int i = M - 1; i > 0; i--) // loop will run till length of rows
  {
    int filledCols = 0;
    for (int j = 0; j < N; j++) // till columns
    {
      if (gameGrid[i][j]) // as it is in loop, only a specific row and a specific column will be checked, if 1 or filled
      {
        filledCols++; // in a single row it will tell how many columns are 1 or filled
      }
      gameGrid[k][j] = gameGrid[i][j];
    }
    if (filledCols < N) // if filled columns is less than total columns ( N=10), it means a whole row is not filled
    {
      k--;
    }
    if (filledCols == N)
    {
      points += 10; // 10 points wille be added
      lines++;
      currLines++;
    }
  }
  if (currLines == 2)
    points += 10; //(10*2) + 10=30
  else if (currLines == 3)
    points += 30; // 10*3 + 30 =60
  else if (currLines == 4)
    points += 60; // 10*4 + 60 = 100
  else if (currLines == 5)
    points += 100; // 10*5 + 100=150
}
void movementFn(int delta_x) // movement function (left and right movement)
{
  for (int i = 0; i < 4; i++)
  {
    point_2[i][0] = point_1[i][0];
    point_1[i][0] += delta_x; // as point_1[i][0] is x-axis, we add value of delta_x to move it left or right
  }
  if (!anamoly()) // restricting the blocks in GameField or from overlapping each other
  {
    for (int i = 0; i < 4; i++)
    {
      point_1[i][0] = point_2[i][0]; // if block overlaps or is out of gamegrid, we replace it with previous location
    }
  }
}
void rotationFn() // Rotation Function
{
  int temp_a, temp_b, centre_0 = point_1[1][0], centre_1 = point_1[1][1];
  // centre_0 is x-axis pivot, while center_1 is y-axis pivot, [1][0] or [1][1]
  for (int i = 0; i < 4; i++)
  {
    temp_a = point_1[i][1] - centre_1;
    temp_b = point_1[i][0] - centre_0;
    point_1[i][0] = centre_0 - temp_a;
    point_1[i][1] = centre_1 + temp_b;
  }
  if (!anamoly())
  {
    // if anamoly is 0 i.e. block is out of gamegrid or overlaps another block we replace it with it previous location i.e. point_2
    for (int i = 0; i < 4; i++)
    {
      point_1[i][0] = point_2[i][0];
      point_1[i][1] = point_2[i][1];
    }
  }
}

void firstRunFn(int &colorNum, int &nxtPiece, int &nxtColor, int nxtBlock[4][2]) // a fn to remove a single piece as first shape when game starts
{
  int n = rand() % 7;
  colorNum = rand() % 7;
  for (int i = 0; i < 4; i++)
  {
    point_1[i][0] = BLOCKS[n][i] % 2;
    point_1[i][1] = BLOCKS[n][i] / 2;
  }
  nxtBlockFn(nxtPiece, nxtColor, nxtBlock);
}
void instantDrop(int &colorNum)
{
  while (anamoly())
  {
    for (int i = 0; i < 4; i++)
    {
      // it is similar to fallingPiece fn but here it will keep falling until it reaches gameBoundary or another block i.e. anomaly is 0
      point_2[i][0] = point_1[i][0];
      point_2[i][1] = point_1[i][1];
      point_1[i][1] += 1;
    }
    if (!anamoly())
    {
      for (int i = 0; i < 4; i++)
      {
        // if anamoly is 0 i.e. block might overlap or get out of grid
        // as point_2 is previous most locaton of point_1, we replace point_1 with it
        point_1[i][0] = point_2[i][0];
        point_1[i][1] = point_2[i][1];
      }
      break;
    }
  }
}
bool shadowAnamoly(int tmp1[4][2], int tmp2[4][2]) // prevents shadow from overlapping other blocks or getting out of gamegrid
{
  for (int i = 0; i < 4; i++)
    if (tmp1[i][0] < 0 || tmp1[i][0] >= N || tmp1[i][1] >= M)
      return 0;
    else if (gameGrid[tmp1[i][1]][tmp1[i][0]])
      return 0;
  return 1;
}
void shadowMove(int delta_x, int tmp1[4][2], int tmp2[4][2]) // left or right movement fn for shadow
{
  for (int i = 0; i < 4; i++)
  {
    tmp1[i][0] = tmp2[i][0];
    tmp1[i][0] += delta_x; // as point_1[i][0] is x-axis, we add value of delta_x to move it left or right
  }
  if (!shadowAnamoly(tmp1, tmp2)) // restricting the blocks in GameField or from overlapping each other
  {
    for (int i = 0; i < 4; i++)
    {
      tmp1[i][0] = tmp2[i][0];
    }
  }
}

void shadowFn(int delta_x, int colorNum, int tmp_1[4][2], int tmp_2[4][2]) // down movement fn for shadow, it also syncs colorNum with original color of block
{
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 2; j++)
    {
      tmp_1[i][j] = point_1[i][j];
      tmp_2[i][j] = point_1[i][j];
    }
  }

  while (shadowAnamoly(tmp_1, tmp_2)) // shadow will keep moving down, till it hits other blocks, as this happens in a single iteration of while window.isOpen, hence shadow will always be at bottom, similar to instant drop fn
  {
    for (int i = 0; i < 4; i++)
    {
      tmp_2[i][0] = tmp_1[i][0];
      tmp_2[i][1] = tmp_1[i][1];
      tmp_1[i][1] += 1;
    }
  }

  if (delta_x) // if blocks moves shadow also moves
  {
    shadowMove(delta_x, tmp_1, tmp_2); // calling shadow movement fn
  }
}
void resetFn()
{
  for (int i = M; i > 0; i--)
  {
    for (int j = N; j > 0; j--)
    {
      gameGrid[i][j] = 0;
    }
  }
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 2; j++)
    {
      point_1[i][j] = 0;
      point_2[i][j] = 0;
    }
  }
  return;
}
bool gameEnd() // GameOver Fn
{
  for (int i = 0; i < 4; i++)
  {
    if (gameGrid[1][point_1[i][0]])
      return 0;
  }
  return 1;
}

void lvlUp(int &points, float &delay) // Level Up Function
{
  if (points > 200) // if user has a score greater than 200, lvl up
    delay = 0.2;
}
void defaults(int &delta_x, float &delay, bool &rotate, bool &skip) // resetting to defaults
{
  delta_x = 0, delay = 0.3, rotate = false, skip = false;
}

///*** YOUR FUNCTIONS END HERE ***///
/////////////////////////////////////
