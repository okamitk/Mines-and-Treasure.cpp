#include <iostream>
#include <cstdlib>

//##############################################
//Coded by Okamitk (Francisco Felipe) and available on GitHub
//The game is set on a matrix called world
//Every space im world is called a block
//A block can contain either a mine, a treasure or just nothing
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

struct difficulty
{
    int height;
    int width;
    int mine_spawn_rate; //Lower number results in more chances of a mine being created
    int near_explosion_rate; //Lower number results in more chances of a mine exploding for each block selected.
    int treasure_quantity; //Lower numbers results in less treasures for each world generated
};

struct character{
    str profile;
    str near_danger;
    str digging;
    str exploding;
    str finding_treasure;
    str near_treasure;
};

//#####################################################

int random(int offset, int range)
{
    return(offset + (rand() % range));
};

int* input(str message, int amount)
{
    int* input = new int[amount];
    std::cout << message << END;
    for (int i=0; i<amount; i++)
    {
        std::cin >> input[i];
    }
    return input;
};

bool isValid(int x, int y, int width, int height)
{
    return(x>-1 && x-1<width && y>-1 && y<height);
};

character createCharacter(){
    character explorer;

    explorer.profile =
    "                                                  \n"
    "      ██████     ▒▒█████████████████              \n"
    "      █    ▒█▒  ▒███               ▒█             \n"
    "      █▒ █▒▒ ▒█▒███▒         ▒▒▒▒▒  ▒█▒           \n"
    "       █▒▒ ▒█▒██████▒▒▒▒▒▒▒▒▒███▒█▒▒▒██           \n"
    "         ▒▒█▒███████▒▒▒█▒█▒█▒█▒▒▒█▒▒▒██▒▒▒        \n"
    "       ▒▒████████████████████████████████████▒▒   \n"
    "       ████████████████▒███████████▒███████████   \n"
    "             █████████▒▒▒███▒██▒ ▒▒  █████▒▒▒     \n"
    "   █████     █████████████▒▒█   ████  ██ █        \n"
    "  █▒    ██████████████▒████ ▒   ██ █  ██ █▒       \n"
    " █▒         ▒████████▒ ▒██▒     ██   ████ █       \n"
    " █            ▒██████                ▒███ █       \n"
    " █       ██    ▒█▒▒██                 ███ █       \n"
    " █▒          ▒█▒   ▒██    ██████    ▒███ █        \n"
    "  █▒    ▒█▒ ▒██     ▒██▒▒          ▒█████ █       \n"
    "   █▒     ██▒ ▒█▒▒▒    ███▒  ▒▒▒▒████▒ ▒█         \n"
    "    █▒▒  ▒████▒ ▒█████▒▒▒▒▒███████▒█▒▒▒▒▒         \n"
    "     ██▒▒█ ▒▒███  ▒█▒▒▒▒▒█▒▒███▒▒▒   ▒█▒          \n"
    "       ██     ███▒ ▒██▒▒█████▒▒▒▒▒▒▒█▒▒█          \n"
    "             █▒ ███▒  ▒▒▒ ▒█▒▒▒████▒▒▒█           \n"
    "            ▒█   ▒██   ▒▒▒▒██▒  ▒▒ ▒███▒▒         \n"
    "           ▒██     █     ███  █      ▒▒███        \n"
    "           ██      █▒   ██▒ ▒           ██▒       \n"
    "                         ▒▒▒                      \n";

    explorer.near_danger =
    "                 ███                              \n"
    "               ▒█   █▒                            \n"
    "              ██  █  █                            \n"
    "              █  █   █                            \n"
    "             █▒  █▒▒████████████                  \n"
    "             █  ▒▒ █ ██████ ▒▒█████               \n"
    "             █  ███▒ █    █       █               \n"
    "              ██     █    █      ▒█               \n"
    "         █████████   █    █ █████████████         \n"
    "      ▒██     ██  ██  ████▒███▒█▒▒▒▒     ███      \n"
    "     ▒█        ██████      ▒                █     \n"
    "     █                 ██                 ▒ █     \n"
    "      ███             ▒██▒         ▒▒▒▒▒████      \n"
    "         ██████████████▒▒███████████████          \n"
    "            █▒▒███    █████     ████   █          \n"
    "            █  ██ ██████████████ ████  █          \n"
    "            █ ███ ██ ███████ ███ ██▒█  ▒█         \n"
    "           █▒ █████████████████   █ █   █         \n"
    "           █  ███████             █▒█  ▒█         \n"
    "           ▒█ ██       ██        ▒██ ▒█▒          \n"
    "            ▒████▒             ▒█████▒            \n"
    "              ▒▒██▒███████████▒████               \n"
    "              ▒█▒███     █  ▒▒▒██▒▒█▒             \n"
    "              ▒   ███▒▒▒ █▒▒▒▒▒▒    ▒▒            \n"
    "                    █    ▒                        \n";

    explorer.digging =
    "                                                  \n"
    "                                                  \n"
    "                                                  \n"
    " █                     ▒█▒▒█▒               █     \n"
    " █                 █████▒█▒▒█               █     \n"
    "  █             ███       ▒█▒█              █     \n"
    "  █           ██ ███        ▒▒█             █     \n"
    "  █           █▒ ▒▒▒▒▒▒▒▒ ▒ ▒██             █     \n"
    "  █            ██▒█▒█▒▒█▒█▒▒██              █     \n"
    "  ██            █ █▒▒  ▒▒█   ███            █     \n"
    "    ██           █▒██████▒▒██▒ █            █     \n"
    "     █            ██ ▒▒███   ███           ██     \n"
    "     ██          █ ▒█▒█  █▒█▒ █           ██      \n"
    "      █         ████▒▒█▒▒▒▒█  █          ██       \n"
    "      ██      ██  ▒▒▒█   ▒█▒██▒         ██        \n"
    "       █      █ ▒▒▒███▒███  ██         █          \n"
    "       ██   ██████▒▒ █ ▒██  ██       ██           \n"
    "         █ ██ ██ ▒█  ██▒ ████      ██             \n"
    "          █████████████████████████               \n";

    explorer.exploding =
    "                                                  \n"
    "         ▒       ▒   ▒                            \n"
    "                 █                                \n"
    "                █ █    █                 ▒▒▒      \n"
    "                █ █                    ▒███▒▒     \n"
    "      ▒     ▒   █ █                 ▒▒▒███▒       \n"
    "          ▒ █▒  █  █               ███████        \n"
    "            ██▒ █  █               █████          \n"
    " ▒          █ █ █  █           ▒ ▒██████          \n"
    "            █  █   █          ▒▒███▒▒▒▒       ▒▒  \n"
    "    ▒    ▒  █  ▒   █▒ ▒█    ▒▒ ▒██▒          ▒███ \n"
    "            █       █▒██  ▒▒ ▒████       █▒▒▒█████\n"
    "            █       █▒ █▒▒  █████▒       ████████ \n"
    "      ████  █          ▒  ▒███            ██████▒ \n"
    "       ▒█▒███            ▒███▒▒▒    ▒▒▒  ██████▒  \n"
    "        ▒█      ▒▒▒▒    ▒▒▒          ███████▒▒    \n"
    "         ██    █▒  ▒▒█  ▒▒▒▒▒       ██████▒▒      \n"
    "       ▒▒▒██            ▒   █  ▒▒▒▒▒█████▒        \n"
    "    ▒▒▒███████▒       ▒▒▒▒█▒▒▒▒█████████▒         \n"
    "             ▒█  █▒▒██              ▒▒▒▒          \n"
    "              ▒█▒█                                \n"
    "                ▒                                 \n";

    explorer.finding_treasure = 
    "          █▒▒▒▒▒▒▒▒▒▒█▒▒▒▒█▒▒▒▒▒▒▒▒▒▒▒█           \n"
    "          █▒▒▒▒▒▒▒▒▒▒█▒▒▒▒█▒▒▒▒▒▒▒▒▒▒▒█           \n"
    "           █                         █            \n"
    "           █            ▒▒▒█▒▒▒▒█▒   █            \n"
    "           █▒█▒▒▒▒▒▒█▒▒█▒▒▒ ▒▒▒▒ ▒█▒ █            \n"
    "          █████████████████████████████           \n"
    "          █ █▒▒▒▒▒▒▒ █ ██ █   ▒▒▒▒▒▒█▒█           \n"
    "       █▒▒█▒▒        ██████           █           \n"
    "       ▒▒▒█▒█                       █▒█           \n"
    "     ▒█▒▒██ ▒▒█████████████████████████▒█▒▒█▒     \n"
    "     ▒█   ▒▒█▒████▒▒▒▒▒▒▒▒▒▒▒▒▒▒███ ▒█▒▒   █▒     \n"
    "      ▒█▒  ▒▒ ▒███▒▒▒▒▒▒▒▒▒▒▒▒▒▒██▒  ▒   ▒█▒      \n"
    "        ██▒▒   ███████████████████▒   ▒▒██        \n"
    "        █▒ ▒▒▒▒███▒▒█▒▒▒▒ █▒ ██▒ ██▒▒▒▒ ▒█        \n"
    "         █     ██   ▒█ ▒ █▒   ██▒ █     █         \n"
    "         █▒    ██  ▒█     █▒  █▒█ █    ▒█         \n"
    "          █     █  ▒▒▒▒▒▒▒▒▒█ ▒▒██▒    ██         \n"
    "          ▒█    ██ █████████▒  ███    ▒█▒         \n"
    "           █    ▒██▒███████▒▒▒▒██▒    █▒          \n"
    "           ▒█    ▒▒█▒▒▒█     ▒▒▒█    █▒           \n"
    "            █      █   █▒▒▒▒▒▒▒▒     █            \n"
    "            ▒▒     █   █▒█▒▒▒▒▒     █▒            \n"
    "             ▒     █   █ █          ▒             \n"
    "                   █   █ █                        \n"
    "                   ▒   ▒                          \n";

    explorer.near_treasure = 
    "                                                  \n"
    "                                                  \n"
    "                                                  \n"
    "     ▒▒▒▒                                         \n"
    "     █ ▒ ▒▒▒                                      \n"
    "     █  ▒▒ ▒▒▒                                    \n"
    "      ▒▒▒▒▒▒▒█▒▒▒▒▒▒▒███▒                         \n"
    "           ████▒▒▒▒▒▒█▒▒▒▒                        \n"
    "        ▒▒█▒██         ▒▒█▒▒▒▒            ▒▒▒▒    \n"
    "      ▒█████▒▒█▒█▒█▒▒█▒▒▒▒    ▒▒         █    █   \n"
    "      ████████████▒▒▒▒▒▒      ▒▒         █    █   \n"
    "      ▒██████▒             ▒▒▒           ▒▒  ▒▒   \n"
    "         ████████▒▒▒▒▒▒▒██▒█▒             █  █    \n"
    "        ▒████▒██▒▒▒▒▒   ▒ █▒ █            ▒▒▒▒    \n"
    "        █████ ██ ▒ ██   █ ▒█ █             ▒▒     \n"
    "        █████ ██   ▒▒      █ █            █  █    \n"
    "        █████▒██      ▒   ▒█ █            ▒█▒     \n"
    "         ████████▒▒▒▒▒▒▒▒▒▒▒█           ▒▒▒ █▒▒▒  \n"
    "        ▒▒█████▒▒▒█▒▒▒▒▒▒▒▒█▒         ▒▒█ ▒██  █  \n"
    "       █▒▒█████   ▒▒▒▒██████       ▒▒▒  ██▒▒▒▒▒   \n"
    "      ▒█▒ ▒███ █▒▒ ██▒▒     ▒▒▒▒▒▒▒     ▒███▒     \n"
    "      ██   ███ █   ██                     █▒      \n"
    "       ██▒████ █   ██     ██▒▒          ▒▒        \n"
    "       ▒  ▒▒       ▒▒      ▒▒██▒    ▒▒▒▒          \n"
    "                              ▒▒▒▒▒▒              \n";

    return explorer;
};

const character explorer = createCharacter();
//#################################################
void storyDialog(int index)
{
    str Dialogs[10] =
            {
                 "O clima não está bom hoje, na verdade nunca esteve desde o início da guerra. \nEstamos empobrecendo a cada dia",
                 "Lembrar da sua esposa, padecendo por uma doença desconhecida te dá ânimo de continuar escavando ao mesmo tempo em que te deixa triste.",
                 "O terreno em que você está procurando este tesouro já foi o leito de um rio relativamente raso. \nSoldados e algumas máquinas estranhas passavam diariamente sobre este solo, era uma área bem disputada.",
                 "A 7 anos atrás, um convoio destruído por algumas das minas que estão aqui. \nA carga valiosa foi enterrada por alguns dos sobreviventes por ser pesada demais. \nApós perderem a guerra, ninguém nunca mais veio aqui em busca desse tesouro. \nProvavelmente dá para repartir e levar um pouco dessa carga de cada vez.",
                 "Existem diversas peças destruídas e retorcidas espalhadas pelo chão. \nA distância entre cada uma delas é tão grande que é difícil acreditar que tenha sido essas minas que fez isso."
            };
};

void deathDialog(int chance){
    str Dialogs[5] =
            {
                "Enquanto procura pelo tesouro, a última coisa que você ouve é um clique. \n\n Você morreu.",
                "Enquanto procurava pelo tesouro, você atingiu uma mina com uma pá, ela deveria estar desativada já que você estava pisando nela o tempo todo... Mas então você ouviu um clique. \n\n Você morreu.",
                "Você encontrou uma coisa de metal, mas acontece que não era realmente um tesouro. Bem, venderia por um pouco de prata se não estivesse prestes a explodir. \n\n Você morreu, ",
                "Você pisou em uma mina. No final a busca pelo tesouro não valeu muita coisa...\n\n Você morreu.",
                "Enquanto procurava pelo tesouro, você atingiu uma mina com sua pá. 5 segundos se passaram como se fossem horas, mas nada aconteceu.\n\n Você recebeu uma nova chance."
            };
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
    std::cout << Dialogs[random(0,4)] <<END;
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
    std::cout << Dialogs[chance] << END;
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
    std::cout << Dialogs[random(0,4)] << END;
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
    std::cout << Dialogs[random(0,4)] << END;
};

//###################################################

void check(int** world, int x, int y, int width, int height)
{
    int mines = 0;
    int near[8][2] =
            {
            {y-1,x-1}, {y,x-1}, {y+1,x-1},
            {y-1,x  },          {y+1,x  },
            {y-1,x+1}, {y,x+1}, {y+1,x+1}
            };
    world[x][y]=2;
    for(int* block:near)
    {
        if(isValid(x, y, width, height))
        {
            if(world[block[1]][block[0]] == 1)
            {
                mines++;
                if(mines > 0)
                {
                    world[x][y]=10+mines;
                }
            }
            else if(world[block[1]][block[0]] == 5)
            {
                world[x][y] = 6;
            };
        };
    };
};

void checkNear(int** world, int x, int y, int width, int height, int chances)
{
    int* mine;
    int mines = 0;
    int near[8][2] = 
        {
            {y-1,x-1},{y,x-1},{y+1,x-1},
            {y-1,x  },        {y+1,x  },
            {y-1,x+1},{y,x+1},{y+1,x+1}
        };
    bool nearTreasure = 0;

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
    if(mines>0)
        {
            system("clear");
            std::cout << explorer.near_danger;
            nearDangerDialog(random(0,3));
            if(random(0,chances)==1)
            {
                world[mine[1]][mine[0]] = 3;
                std::cout << "Você sente um tremor, uma mina explodiu por perto." << END;
            }
            world[x][y]=10+mines;
        }
        else if(nearTreasure)
        {
            world[x][y] = 6;
        }
        else
        {
            system("clear");
            std::cout << explorer.digging;
            digDialog();
        }
};

void digBlock(int**world, int x, int y, bool alive, bool rich, int width, int height, int chances)
{
    if (world[x][y]==5)
    {
        world[x][y]==7;
        rich = 1;
    }
    else
    {
        world[x][y]=2;
        checkNear(world, x, y, width, height, chances);
    };
}
 
bool chooseBlock(int** world, bool alive, bool rich, int width, int height, int chances)
{
    int x = (input("Digite a coluna do bloco: ", 1))[0];
    int y = (input("Digite a linha do bloco: ", 1))[0];
    int chance = random(0,4);

    x--;
    y--;
    
    if(isValid(x, y, width, height))
    {
        alive = (world[x][y] != 1);
        if(alive && !rich)
        {
            digBlock(world, x, y, alive, rich, width, height, chances);
        }
        else if(!alive)
        {
            if(chance==4){
                alive=1;
            }
            system("clear");
            std::cout << explorer.exploding;
            deathDialog(chance);
            world[x][y] = 3;
        }
        else if(rich)
        {
            system("clear");
            std::cout << explorer.near_treasure;
            TreasureDialog();
        }
    }
    else
    {
        std::cout << "Essas coordenadas não são válidas." << END;
    }
    return alive;
}
void worldOut(int** world, int width, int height)
{
    for(int i = 0; i < height; i++)
    {
        std::cout << i+1 << " ";
        for(int j = 0; j < width; j++)
        {
            switch(world[i][j])
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

difficulty selectDifficulty(){
    int level = (input("Dificuldade:\n1: Fácil\n2: Médio\n3: Difícil",1))[0];
    difficulty setDifficulty;
    switch(level)
    {
        case 1:
            setDifficulty.height = 6;
            setDifficulty.width = 12;
            setDifficulty.mine_spawn_rate = 6;
            setDifficulty.treasure_quantity = 2;
            setDifficulty.near_explosion_rate = 4;
            break;
        case 2:
            setDifficulty.height = 9;
            setDifficulty.width = 18;
            setDifficulty.mine_spawn_rate = 5;
            setDifficulty.treasure_quantity = 2;
            setDifficulty.near_explosion_rate = 6;
            break;
        case 3:
            setDifficulty.height = 9;
            setDifficulty.width = 20;
            setDifficulty.mine_spawn_rate = 3;
            setDifficulty.treasure_quantity = 1;
            setDifficulty.near_explosion_rate = 10;
            break;
    }
    return setDifficulty;
};

void **generateWorld(int **world, difficulty level)
{
    int width = level.width;
    int height = level.height;

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            if((random(0,level.mine_spawn_rate) == 1))
            {
                world[i][j] = 1;
            }
            else
            {
                world[i][j] = 0;
            }
        }
    }
    
    world[0][0]=0;
    world[0][1]=0;
    world[0][2]=0;
    world[1][0]=0;
    world[1][1]=0;
    world[2][0]=0;
    world[3][0]=0;

    check(world, 0, 0, width, height);
    check(world, 0, 1, width, height);
    check(world, 0, 2, width, height);
    check(world, 1, 0, width, height);
    check(world, 1, 1, width, height);
    check(world, 2, 0, width, height);

    if(level.treasure_quantity==2)
    {
        world[random(0, level.height)][random(0, level.width)] = 5;
        world[random(0, level.height)][random(0, level.width)] = 5;
    }
    else
    {
        world[random(0, level.height)][random(0, level.width)] = 5;
    };
};

int **generateMatrix(int width, int height)
{
    int** world = new int*[height];
    for (int i = 0; i < height; i++)
    {
        world[i] = new int[width];
    }

    return world;
};

int main()
{
    int**world;
    bool rich = 0;
    bool alive = 1;
    int counter;
    char enter;

    difficulty level = selectDifficulty();
    world = generateMatrix(level.width, level.height);
    generateWorld(world, level);

    std::cout <<  
        "        _                                   _   _____                                        \n"
        "  /\\/\\ (_)_ __   ___  ___    __ _ _ __   __| | /__   \\_ __ ___  __ _ ___ _   _ _ __ ___  ___ \n"
        " /    \\| | '_ \\ / _ \\/ __|  / _` | '_ \\ / _` |   / /\\/ '__/ _ \\/ _` / __| | | | '__/ _ \\/ __|\n"
        "/ /\\/\\ \\ | | | |  __/\\__ \\ | (_| | | | | (_| |  / /  | | |  __/ (_| \\__ \\ |_| | | |  __/\\__ \\\n"
        "\\/    \\/_|_| |_|\\___||___/  \\__,_|_| |_|\\__,_|  \\/   |_|  \\___|\\__,_|___/\\__,_|_|  \\___||___/"
        << END;

        std::cout << "Neste campo existem mines e tesouros." << END
                  << "Você pode selecionar um bloco usando as coordenadas x e y." << END
                  << "Ao selecionar um bloco vazio você pode ver a quantidade de minas ao redor dele. (Isso se você não explodir)" << END
                  << END
                  << "Pressione ENTER";

        std::cin >> enter;

        system("clear");

        std::cout << explorer.profile << END
                  << "Você é um pobre jovem, vivendo em uma vila isolada."
                  << "Com a vida e o trabalhado assolados pelo frio, fome e doenças, você decide que irá tomar medidas extremas."
                  << END
                  << "Pressione ENTER";

        std::cin >> enter;

        system("clear");

        while(alive && !rich)
        {
            worldOut(world, level.width, level.height);
            chooseBlock(world, alive, rich, level.width, level.height, level.near_explosion_rate);
        }

        return 0;
};
