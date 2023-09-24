#include <iostream>
#include <cstdlib>

//The game is set on a matrix called world
//Every space in world is called a block
//A block can contain a mine or a treasure or nothing
// 0 = empty block "█"
// 1 = mine "█"
// 2 = digged block " "
// 3 = digged mine block "✕"
// 4 = near mine block "⚠"
// 5 = treasure "█"
// 6 = near treasure block "✦"
// 7 = digged treasure block "★"


using str = std::string;
const str END = "\n";
struct dimensions
{
    int height;
    int width;
};

bool checkExecution(){
    return 1;
}

int random(int offset, int range)
{
    return(offset+(rand()%range));
};

int* getUserInput(str message, int amount)//Wont be used if implemented on GUI
{
    int* input = new int[amount];

    std::cout<<message<<END;
    for(int i=0; i<amount; i++)
    {
        std::cin>>input[i];
    }
    return input;
}

void checkNearBlocks(int **world, int x, int y)
{
    bool nearDanger=0;
    bool nearTreasure=0;
    int* mine;
    int* treasure;
    int chance;
    int NEAREST_BLOCKS[8][2] =
                  {{y-1,x-1},{y,x-1},{y+1,x-1},
                   {y-1,x  },        {y+1,x  },
                   {y-1,x+1},{y,x+1},{y+1,x+1}};

    std::cout<<"Current block: "<<world[x][y]<<END;
    for(int* block:NEAREST_BLOCKS)
    {
        std::cout<<"Near Block: "<<block[1]<<" "<<block[0]<<END;   
        if(block[1]>-1 && block[2]>-1){         
            if(world[block[1]][block[0]]==1)
            {
                std::cout<<"This block contains a mine"<<END;
                nearDanger=1;
                mine=block;
            }
            if (world[block[1]][block[0]]==5)
            {
                std::cout<<"This block contains the treasure"<<END;
                nearTreasure=1;
                treasure=block; 
            }
        }
    }

    if(nearDanger)
    {
        chance = random(0,4);
        if(chance = 4 && world[x][y]!=4)
        {
            world[x][y]=4;
            world[mine[1]][mine[0]]=3;
            checkNearBlocks(world, x, y);
        }
        
    }
    if(nearTreasure)
    {
        chance = random(0,4);
        world[x][y]=6;
        if(chance==4)
        {
            world[treasure[1]][treasure[0]]=7;
        };
    }
};

void digBlock(int**world, int x, int y, bool alive, bool rich)
{
    alive = (world[x][y]!=1);

    std::cout<<"Alive: "<<alive<<END;
    std::cout<<"Block: "<<world[x][y]<<END;
    std::cout<<"Coord: "<<x<<" "<<y<<END;

    if(alive)
    {
        if(world[x][y]==5)
        {
            world[x][y]==7;
            rich = 1;
        }
        else
        {
            world[x][y]=2;
            checkNearBlocks(world, x, y);

            std::cout<<"Alive: "<<alive<<END;
            std::cout<<"Block: "<<world[x][y]<<END;
            std::cout<<"Coord: "<<x<<" "<<y<<END;
        };
    };
}

bool isValid(int x, int y, int width, int height){
    return(x>-1 && x<width+1 && y>-1 && y<height+1);
};

bool chooseBlock(int** world, bool alive, bool rich, int width, int height)//Wont be used if implemented on GUI
{   
    int x=(getUserInput("Digite a coluna do bloco: ",1))[0];
    int y=(getUserInput("Digite a linha do bloco: ",1))[0];
    
    if(isValid(x,y,width, height)){
        digBlock(world,x-1,y-1,alive,rich);
    }
    else
    {
        std::cout<<"Essas coordenadas não são válidas."<<END;
    }
    
    return 1;
};

void printWorld(int** world, int width, int height)
{
    for(int i=0; i<height; i++)
    {
        std::cout<<i+1<<" ";
        for(int j=0; j<width; j++)
        {
            // std::cout<<world[i][j];
            switch (world[i][j])
            {
                case 0:
                    std::cout<<"█";
                    break;
                case 1:
                    std::cout<<"█";
                    break;
                case 2:
                    std::cout<<" ";
                    break;
                case 3:
                    std::cout<<"X";
                    break;
                case 4:
                    std::cout<<"!";
                    break;
                case 5:
                    std::cout<<"█";
                    break;
                case 6:
                    std::cout<<"✦";
                    break;
                case 7:
                    std::cout<<"★";
                    break;
                default:
                    std::cout<<"█";
                    break;
            }
        }
        std::cout<<END;
    }
}

dimensions selectDimensions(int difficulty){
    dimensions world_dimensions;

    switch(difficulty){
        case 1:
            world_dimensions.height=5;
            world_dimensions.width=10;
            break;
        case 2:
            world_dimensions.height=9;
            world_dimensions.width=20;
            break;
        case 3:
            world_dimensions.height=20;
            world_dimensions.width=40;
            break;
    };

    return world_dimensions;
};

int **generateMatrix(int width, int height)
{
    int **world = new int*[height];
    for (int i=0; i<height; i++)
    {
        world[i]=new int[width];
    }
    
    return world;
};
    
void **generateWorld(int **world, int width, int height)
{
    //Mines and Sand
    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
            if((random(0,3))==1){

                world[i][j]=1;
            } 
            else 
            {
                world[i][j]=0;
            }
        }
    }
    //Treasure
    world[random(0,height)][random(0,width)]=5;
};

int main()
{
    int**world;
    bool rich=0;
    bool alive=1;

    int difficulty=(getUserInput("Dificuldade:\n1: Fácil\n2: Médio\n3: Difícil",1))[0];
    dimensions world_dimensions = selectDimensions(difficulty);
    world = generateMatrix(world_dimensions.width, world_dimensions.height);
    generateWorld(world, world_dimensions.width, world_dimensions.height);

    std::cout<<"Tem um tesouro e várias minas nesse terreno, selecione um bloco para cavar."<<END;
    printWorld(world, world_dimensions.width, world_dimensions.height);

    while(alive && !rich){
        bool choosen=0;
        while(!choosen){
            try{
                if(chooseBlock(world, alive, rich, world_dimensions.width, world_dimensions.height))
                {
                    choosen=1;
                }
                else
                {
                    throw(1);
                }
            }
            catch(int value)
            {
                std::cout<<"Ocorreu uma exceção "<<value;
            }
        }
        printWorld(world, world_dimensions.width, world_dimensions.height);
    }
    return 0;
};