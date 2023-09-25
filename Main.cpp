#include <iostream>
#include <cstdlib>

//#####################################################

//Coded by Okamitk (Francisco Felipe) on GitHub
//The game is set on a matrix called world
//Every space in world is called a block
//A block can contain a mine or a treasure or nothing
// 0 = empty block "█"
// 1 = mine "█"
// 2 = digged block " "
// 3 = digged mine block "X"
// 4 was supposed to be a ! sign, but was replaced by the amount of mines
// 5 = treasure "█"
// 6 = near treasure block "✦"
// 7 = digged treasure block "★"

//##################################################

using str = std::string;

const str END = "\n";

struct dimensions
{
    int height;
    int width;
};

//#################################################

int random(int offset, int range)
{
    return(offset+(rand()%range));
};

int* input(str message, int amount)//Wont be used if implemented on GUI
{
    int* input = new int[amount];

    std::cout<<message<<END;
    for(int i=0; i<amount; i++)
    {
        std::cin>>input[i];
    }
    return input;
};

bool isValid(int x, int y, int width, int height){
    return(x>-1 && x<width && y>-1 && y<height);
};

//#################################################

void deathDialog(int chance){
    str Dialogs[5] =
            {
                "Enquanto procura pelo tesouro, a última coisa que você ouve é um clique. \n\n Você morreu.",
                "Enquanto procurava pelo tesouro, você atingiu uma mina com uma pá, ela deveria estar desativada já que você estava pisando nela o tempo todo... Mas então você ouviu um clique. \n\n Você morreu.",
                "Você encontrou uma coisa de metal, mas acontece que não era realmente um tesouro. Bem, venderia por um pouco de prata se não estivesse prestes a explodir. \n\n Você morreu, ",
                "Você pisou em uma mina. No final a busca pelo tesouro não valeu muita coisa...\n\n Você morreu.",
                "Enquanto procurava pelo tesouro, você atingiu uma mina com sua pá. 5 segundos se passaram como se fossem horas, mas nada aconteceu.\n\n Você recebeu uma nova chance."
            };
    std::cout << 
        " _____                        _____                \n"
        "|  __ \\                      |  _  |               \n"
        "| |  \\/ __ _ _ __ ___   ___  | | | |_   _____ _ __ \n"
        "| | __ / _` | '_ ` _ \\ / _ \\ | | | \\ \\ / / _ \\ '__|\n"
        "| |_\\ \\ (_| | | | | | |  __/ \\ \\_/ /\\ V /  __/ |   \n"
        " \\____/\\__,_|_| |_| |_|\\___|  \\___/  \\_/ \\___|_|         \n"
        "";
    std::cout << Dialogs[chance] << END;
};

void digDialog(){
    str Dialogs[5] =
            {
                "Você cavou, cavou e cavou mas não encontrou nada.",
                "Depois de cavar por algum tempo você não encontrou nada.",
                "Não há nada aqui.",
                "Cavando por vários minutos, a única coisa que você encontrou foi terra e pedras, muitas pedras.",
                "Você cavou, mas não há nada valioso."
            };
    std::cout << END << END << END << END << END << Dialogs[random(0,4)] << END;
};

void nearDangerDialog(int chance){
    str  Dialogs[5] =
            {
                "Você pode sentir o cheiro de pólvora vindo das paredes da escavação. Há uma mina por perto.",
                "Você sente um calafrio horrível. Tem algo próximo.",
                "Você consegue ouvir o impacto da sua pá ecoando em alguma mina próxima.",
                "Há polvora misturada na areia que você acabou de cavar. Tem um bomba por perto",
                "Você bateu forte demais com a pá e sentiu o chão tremer, uma mina explodiu por perto."
            };
    std::cout << END << END << END << END << END << Dialogs[chance] << END;
};

void nearTreasureDialog(){
    str Dialogs[5] =
            {
                "Antes de sair você encontrou uma moeda de ouro sob seu pé, talvez o tesouro esteja próximo.",
                "Depois de inspecionar com mais cuidado, você encontrou a peça de um relógio de ouro, talvez o tesouro esteja próximo.",
                "Um pó dourado misturado na areia brilha enquanto você sai do buraco, o tesouro deve estar próximo.",
                "Havia uma pequena pérola brilhando na terra que você acabou de cavar, o tesouro está próximo.",
                "Depois de olhar com mais cuidado você vê há um anel de prata na terra. O tesouro deve estar próximo."
            };
    std::cout << END << END << END << END << END << Dialogs[random(0,4)] << END;
};

void TreasureDialog(){
    str Dialogs[5] =
            {
                "Depois de encontrar um baú, você ficou tão aliviado que cai de joelhos e sente que poderia morrer em paz agora, bem, não exatamente agora.\n\n Você encontrou o tesouro",
                "Você encontrou um baú contendo várias joias e algumas moedas antigas. Você pode viver bem agora\n\n Você encontrou o tesouro.",
                "Você encontrou um baú contendo muitas moedas de ouro. A moeda em si não é utilizável, mas o ouro sim. Você pode viver em paz agora\n\n Você encontrou o tesouro.",
                "Você encontrou uma caixa de madeira coom várias barras de ouro. Você agora, não precisando mais arriscar sua própria vida, vai para casa com cuidado.\n\n Você encontrou o tesouro.",
                "Você acerta um pedaço de metal com sua pá e toda a sua vida passa diante de seus olhos. Depois de quase desmaiar de medo, você percebe que a tal caixa tem na verdade milhões em pérolas. Você agora vive o resto de sua vida em paz.\n\n Você encontrou o tesouro."
            };
    std::cout <<
        "__   __            _    _ _       _ \n"
        "\\ \\ / /           | |  | (_)     | |\n"
        " \\ V /___  _   _  | |  | |_ _ __ | |\n"
        "  \\ // _ \\| | | | | |/\\| | | '_ \\| |\n"
        "  | | (_) | |_| | \\  /\\  / | | | |_|\n"
        "  \\_/\\___/ \\__,_|  \\/  \\/|_|_| |_(_)";
    std::cout << Dialogs[random(0,4)];
};

//###################################################

void check(int** world, int x, int y, int width, int height){
    int mines = 0;
    int near[8][2] =
                {
                {y-1,x-1}, {y,x-1}, {y+1,x-1},
                {y-1,x  },          {y+1,x  },
                {y-1,x+1}, {y,x+1}, {y+1,x+1}
                };

    world[x][y] = 2;
    for(int* block:near)
    {
        if(isValid(x, y, width, height))
        {
            if(world[block[1]][block[0]] == 1)
            {
                mines++;
                if(mines>0){
                    world[x][y]=10+mines;
                }
            }
            else if(world[block[1]][block[0]] == 5){
                world[x][y] = 6;
            };
        };
    };
};

void checkNear(int **world, int x, int y, int* previous_exploded, int width, int height)
{
    int mines = 0;
    int near[8][2] =
                {
                {y-1,x-1},{y,x-1},{y+1,x-1},
                {y-1,x  },        {y+1,x  },
                {y-1,x+1},{y,x+1},{y+1,x+1}
                };

    bool nearTreasure = 0;
    int* mine;

    check(world, previous_exploded[1], previous_exploded[0], width, height);

    for(int* block:near)
    {
        if(isValid(block[1], block[0], width, height))
        {         
            if(world[block[1]][block[0]] == 1)
            {
                mine = block;
                mines++;
            }
            else if(world[block[1]][block[0]] == 5)
            {
                nearTreasure = 1;
            }
        }
    }

    if(mines>0){
        if(random(0,6) == 6  && world[x][y]!= 4)
        {
            world[mine[1]][mine[0]] = 3;
            nearDangerDialog(4);
            previous_exploded = mine;
        }
        else
        {
            nearDangerDialog(random(0,3));
        }
        world[x][y]=10+mines;
    }
    
    else if(nearTreasure)
    {
        world[x][y] = 6;
        nearTreasureDialog();
    }

    else
    {
        digDialog();
    }
};

void digBlock(int**world, int x, int y, bool alive, bool rich, int* previous_exploded, int width, int height)
{
        if(world[x][y]==5)
        {
            world[x][y]==7;
            rich = 1;
        }
        else
        {
            world[x][y]=2;
            checkNear(world, x, y, previous_exploded, width, height);
        };
}

bool chooseBlock(int** world, bool alive, bool rich, int width, int height, int* previous_exploded)
{   
    int x = (input("Digite a coluna do bloco: ",1))[0];
    int y = (input("Digite a linha do bloco: ",1))[0];
    int chance = random(0,4);
    
    if(isValid(x, y, width, height))
    {
        alive = (world[x][y]!=1);
        if(alive && !rich)
        {
            digBlock(world, x-1, y-1, alive, rich, previous_exploded, width, height);
        }
        else if(!alive)
        {
            if(chance==4){
                alive=1;
            }

            deathDialog(chance);
            world[x][y] = 3;
        }
        else if(rich)
        {
            TreasureDialog();
        }
    }
    else
    {
        std::cout << "Essas coordenadas não são válidas." << END;
    }
    
    return 1;
};

void printWorld(int** world, int width, int height)
{
    for(int i = 0; i < height; i++)
    {
        std::cout << i+1 << " ";
        for(int j = 0; j < width; j++)
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
                    std::cout<<(world[i][j])-10;
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

void **generateWorld(int **world, int width, int height)
{
    //Mines and Sand
    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
            if((random(0,6))==1){

                world[i][j]=1;
            } 
            else 
            {
                world[i][j]=0;
            }
        }
    }
    //Treasure
    check(world, 1, 1, width, height);
    world[random(0,height)][random(0,width)]=5;
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


int main()
{
    int**world;
    bool rich=0;
    bool alive=1;
    int previous_exploded[2] = {1,1};

    int difficulty = (input("Dificuldade:\n1: Fácil\n2: Médio\n3: Difícil",1))[0];
    dimensions world_dimensions = selectDimensions(difficulty);
    world = generateMatrix(world_dimensions.width, world_dimensions.height);
    generateWorld(world, world_dimensions.width, world_dimensions.height);

    std::cout << END << "        _                                   _   _____                                        \n"
        "  /\\/\\ (_)_ __   ___  ___    __ _ _ __   __| | /__   \\_ __ ___  __ _ ___ _   _ _ __ ___  ___ \n"
        " /    \\| | '_ \\ / _ \\/ __|  / _` | '_ \\ / _` |   / /\\/ '__/ _ \\/ _` / __| | | | '__/ _ \\/ __|\n"
        "/ /\\/\\ \\ | | | |  __/\\__ \\ | (_| | | | | (_| |  / /  | | |  __/ (_| \\__ \\ |_| | | |  __/\\__ \\\n"
        "\\/    \\/_|_| |_|\\___||___/  \\__,_|_| |_|\\__,_|  \\/   |_|  \\___|\\__,_|___/\\__,_|_|  \\___||___/"<<END;
    std::cout<<"Tem um tesouro e várias minas nesse terreno, selecione um bloco para cavar."<<END;
    printWorld(world, world_dimensions.width, world_dimensions.height);

    while(alive && !rich){
        bool choosen=0;
        while(!choosen){
            try{
                if(chooseBlock(world, alive, rich, world_dimensions.width, world_dimensions.height, previous_exploded))
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
            }
        }
        printWorld(world, world_dimensions.width, world_dimensions.height);
    }
    return 0;
};