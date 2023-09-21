#include "Head.h"

using namespace std;
int main()
{
    system("title Maze"); // смена текста в заголовке консольлного окна

    // дескриптор (идентификатор), уникальный номер окна консоли
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

    // скрываем мигающий курсор в консоли
    CONSOLE_CURSOR_INFO info;
    info.bVisible = false;
    info.dwSize = 100; // 1...100
    SetConsoleCursorInfo(h, &info);

    const int height = 25; // высота
    const int width = 80; // ширина
    int maze[height][width] = {};//заготовка для лабиринта ввиде двумерноо массива заполненного 0

    // enumeration - перечисление
    // набор целочисленных констант
    // читаемость кода существенно повышается
    //enum Directions { LEFT = 75, RIGHT = 77, DOWN = 80, UP = 72 };
    //enum Colors { RED = 12, BLACK = 0, GREEN = 10, YELLOW = 14, PINK = 13, WHITE = 7 };
    //enum Objects { HALL = 0, WALL = 1, COIN = 2, ENEMY = 3, HEAL = 4 };

    srand(time(0));

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {

            maze[y][x] = rand() % 5;
            // установка стен по бокам (делаем рамки)
            if (x == 0 || x == width - 1 || y == 0 || y == height - 1)
            {
                maze[y][x] = WALL;


            }
            //определение точки входа и выхода из лабиринта
            if (x == 0 && y == 2 || x == width - 1 && y == height - 3 || x == width - 2 && y == height - 3 || x == 1 && y == 2 || x == 2 && y == 2)
            {
                maze[y][x] = HALL;
            }
            if (maze[y][x] == ENEMY)
            {
                int r;
                r = rand() % 10;
                if (r != 0)
                {
                    maze[y][x] = HALL;
                }
            }
            else if (maze[y][x] == HEAL)
            {
                int j;
                j = rand() % 20;
                if (j != 0)
                {
                    maze[y][x] = HALL;
                }
            }

            if (maze[y][x] == HALL)
            {
                SetCursor(x, y, BLACK, "",(char)0);
            }
            else if (maze[y][x] == WALL)
            {
                SetCursor(x, y, WHITE, "", (char)178);
            }
            else if (maze[y][x] == COIN)
            {
                SetCursor(x, y, YELLOW, "", (char)46);
            }
            else if (maze[y][x] == ENEMY)
            {
                SetCursor(x, y, RED, "", (char)1);
            }
            else if (maze[y][x] == HEAL)
            {
                SetCursor(x, y, GREEN, "",(char)43);
            }
        }
        cout << "\n";
    }
    //пример установки курсора в любые координаты консоли
    COORD position; // координати гг
    position.X = 0;
    position.Y = 2;   
  
    SetCursor(position.X, position.Y, MAGENTA, "", (char)2);

    COORD heals;
    heals.X = 0;
    heals.Y = 0;
    int coins = 0, health = 100;
    bool ok = true;
    while (true)
    {

        int code = _getch();//get character -получуние кода нажатой клавиши        
        SetCursor(position.X, position.Y, BLACK, "", (char)0);
        
        if (code == 224)//если нажата какая-то стрелка
        {
            code = _getch();
        }        
        if (heals.X > 0 || !ok)
        {
            SetCursor(heals.X, heals.Y, GREEN, "", (char)43);
            ok = true;
        }
        if (code == RIGHT and maze[position.Y][position.X + 1] != WALL) //right               
            position.X++;
        else if (code == LEFT and maze[position.Y][position.X - 1] != WALL)//left           
            position.X--;
        else if (code == UP and maze[position.Y - 1][position.X] != WALL)//up    
            position.Y--;
        else if (code == DOWN and maze[position.Y + 1][position.X] != WALL)//down    
            position.Y++;

        SetCursor(position.X, position.Y, MAGENTA, "", (char)2);
        ///////////////////////////////////////////////////////////////////////////////
                
        SetCursor(width + 2, 1, YELLOW, "COINS:", (char)0);
        SetCursor(width + 8, 1, YELLOW, to_string(coins), (char)0);
        
        SetCursor(width + 2, 2, RED, "HEALTH:", (char)0);
        SetCursor(width + 9, 2, RED, to_string(health), (char)0);
        
        if (maze[position.Y][position.X] == COIN)
        {

            coins++;
            maze[position.Y][position.X] = HALL;
            
            SetCursor(width + 2, 1, YELLOW, "COINS:", (char)0);
            SetCursor(width + 8, 1, YELLOW, to_string(coins), (char)0);

        }
        else if (maze[position.Y][position.X] == ENEMY)
        {

            health -= 25;
            maze[position.Y][position.X] = HALL;
            
            SetCursor(width + 2, 2, RED, "HEALTH:", (char)0);
            SetCursor(width + 9, 2, RED, to_string(health), (char)0);                       

            if (health <= 0)
            {
                int answer;
                answer = MessageBoxA(0, "You death", "Loser", MB_YESNO);
                system("cls");
                if (answer == IDYES)
                {
                    main();
                }
                else
                {
                    exit(0);
                }
            }
        }

        else if (maze[position.Y][position.X] == HEAL)
        {
            
            if (health == 100)
            {  
                if (ok)
                {
                    heals.X = position.X;
                    heals.Y = position.Y;
                    ok = false;
                }
                
            }
            else
            {
                health += 25;
                maze[position.Y][position.X] = HALL;
            }           
            SetCursor(width + 2, 2, RED, "HEALTH:", (char)0);
            SetCursor(width + 9, 2, RED, to_string(health), (char)0);            
        }
        ///////////////////////////////////////////////////////////////////////////////
        //проверка на выход

        if (position.Y == height - 3 and position.X == width - 1)
        {
            int user;
            user = MessageBoxA(0, "You win", "Congratulations", MB_YESNO);
            system("cls");
            if (user == IDYES)
            {
                main();
            }
            else
            {
                exit(0);

            }
        }

    }

    Sleep(INFINITE);//пауза на 10 сек

    //коридоры - 0
    //стены - 1
    //монетки - 2
    //враги - 3

}
//232 былo 220 стало итого 12 строк