#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

using namespace std;

struct Warrior {
    string weapon;
    int power;
};

//Feel free to modify the parameters if you need other values
bool skirmish(Warrior*** protectors, Warrior*** invaders, int skirmish_row,
		      int rows, int cols, int colsInv, int &emptyCnt, int &reserves, ofstream &output)
{
    //returns true if the invaders breach the walls.
    

    for (int i = 0; i < rows; i++)
    {
          

            if ((protectors[i][skirmish_row]->weapon == "axe") && (invaders[skirmish_row][i]->weapon == "sword"))
            {
                output << "Invader killed" << endl;
                invaders[skirmish_row][i]->weapon = "empty";
                emptyCnt++;

            }
            else if ((protectors[i][skirmish_row]->weapon == "sword") && (invaders[skirmish_row][i]->weapon == "axe"))
            {

                if (emptyCnt == 0)
                {
                    output << "Protector killed" << endl;
                }

                else
                {

                    for (int a = 0; a < colsInv; a++)
                    {
                        if(invaders[skirmish_row][a]->weapon == "empty")
                        {
                            invaders[skirmish_row][a]->weapon = protectors[i][skirmish_row]->weapon;
                             invaders[skirmish_row][a]->power = protectors[i][skirmish_row]->power;

                             emptyCnt--;

                             if (reserves > 0)
                             {
                                protectors[i][skirmish_row]->weapon = "axe";
                                protectors[i][skirmish_row]->power = 100;
                                reserves--;

                             }

                             else 
                             {
                                protectors[i][skirmish_row]->weapon = "empty";
                                protectors[i][skirmish_row]->power = 0;
                             }

                           
                            break;
                        }
                    }
                    output << "Protector defected" << endl;
                }
                 

            }
             else if (((protectors[i][skirmish_row]->weapon == "axe") && (invaders[skirmish_row][i]->weapon == "empty"))|| ((protectors[i][skirmish_row]->weapon == "sword") && (invaders[skirmish_row][i]->weapon == "empty")))
           {
                output << "No assault" << endl;
           }

           else if (((protectors[i][skirmish_row]->weapon == "empty") && (invaders[skirmish_row][i]->weapon == "axe"))||((protectors[i][skirmish_row]->weapon == "empty") && (invaders[skirmish_row][i]->weapon == "sword")))
           {
                output << "Winner: invaders" << endl;
                return true;
           }


            else 
            {
                if (protectors[i][skirmish_row]->power > invaders[skirmish_row][i]->power)
                {
                    output << "Invader killed";
                    invaders[skirmish_row][i]->weapon = "empty";
                    emptyCnt++;
                }
                else if (protectors[i][skirmish_row]->power < invaders[skirmish_row][i]->power)
                {
                    if (emptyCnt == 0)
                    {
                        output << "Protector killed" << endl;
                    }

                    else
                    {

                        for (int a = 0; a < colsInv; a++)
                        {
                            if(invaders[skirmish_row][a]->weapon == "empty")
                            {
                                invaders[skirmish_row][a]->weapon = protectors[i][skirmish_row]->weapon;
                                 invaders[skirmish_row][a]->power = protectors[i][skirmish_row]->power;

                                 emptyCnt--;

                                 if (reserves > 0)
                                 {
                                    protectors[i][skirmish_row]->weapon = "axe";
                                    protectors[i][skirmish_row]->power = 100;
                                    reserves--;

                                 }

                                 else 
                                 {
                                    protectors[i][skirmish_row]->weapon = "empty";
                                    protectors[i][skirmish_row]->power = 0;
                                 }

                               
                                break;
                            }
                        }
                        output << "Protector defected" << endl;
                    }
              }

              else 
              {
                output << "Duel ends in draw" << endl;
              }

           }

          
    
}

return false;


}

int main(int argc, char* argv[])
{
    if (argc < 3) {
	   cerr << "Please provide an input and output file" << endl;
	   return -1;
    }

    ifstream input(argv[1]);
    ofstream output(argv[2]);

    int rows;
    int cols;
    int reserve;
    int skirmishes;

    //read the input file and initialize the values here.

    input >> rows >> cols >> reserve >> skirmishes;



    Warrior ***protectors = new Warrior** [rows];

    for (int a = 0; a < rows; a++)
    {
        protectors[a] = new Warrior* [cols];
    }

    for (int n = 0; n < rows; n++)
   {    
        for (int m = 0; m < cols; m++)
        {
            protectors[n][m] = new Warrior();
        }
   }

    Warrior ***invaders = new Warrior**[cols];
    for (int b = 0; b < cols; b++)
    {
        invaders[b] = new Warrior*[rows];
    }

   for (int s = 0; s < cols; s++)
   {    
        for (int d = 0; d < rows; d++)
        {
            invaders[s][d] = new Warrior();
        }
   }

    //initialize the protectors and invaders here.


    for (int x = 0; x < rows; x++)
    {
        for (int y = 0; y < cols; y++)
        {
            if (x%2 == 0)
            {
                protectors[x][y]->weapon = "axe";
            }
            else 
            {
                protectors[x][y]->weapon = "sword";
            }

            protectors[x][y]->power = (x*10+(y+1)*10);
        }
    }

    int colsInv= rows;
    for (int r = 0; r < cols; r++)
    {
        for (int c = 0; c < rows; c++)
        {
            if (r%2 == 0)
            {
                invaders[r][c]->weapon = "sword";
            }
            else 
            {
                invaders[r][c]->weapon = "axe";
            }

            invaders[r][c]->power = (r*10+(c+1)*10);
        }
    }

    int emptyCnt = 0;

    for (int i=1; i <= skirmishes; i++){
        int skirmish_row;
         
        //read the input file to find the value for skirmish row
        input >> skirmish_row;

        if (skirmish_row >= 0 && skirmish_row < cols)
        {
            bool end = skirmish(protectors, invaders, skirmish_row, rows, cols,colsInv, emptyCnt, reserve, output);

            if (end == true)
            {
                return 0;
            }
        }
        //In general, it is bad style to throw everything into your main function
        
    }

    //output the winner and deallocate your memory.
      output << "Winners: protectors" <<endl;
    


    for (int n = 0; n < rows; n++)
   {    
        for (int m = 0; m < cols; m++)
        {
            delete protectors[n][m];
        }

        delete [] protectors[n];
   }
   

    delete [] protectors;


   for (int n = 0; n < cols; n++)
   {    
        for (int m = 0; m < rows; m++)
        {
            delete invaders[n][m];
        }

        delete [] invaders[n];
   }

    

    delete [] invaders;


   
    return 0;
}
