//
// Created by Fridr on 16.11.2019.
//

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Game {
public:
    class PlayingArea{
    private:
        double pos_x, pos_y = 0;
        double width, height;
    public:
        double PADDING = 10.f;
        PlayingArea(double pos_x, double pos_y, double width, double height){
            this->pos_x = pos_x;
            this->pos_y = pos_y;
            this->width = width;
            this->height = height;
        }
        double getPosX() {return pos_x;}
        double getPosY() {return pos_y;}
        double getWidth() {return width;}
        double getHeight() {return height;}
    };
private:
    const static int SIZE_X = 40; // Длинна в клетках
    const static int SIZE_Y = 30; // Ширина в клетках
    const static int ARRAY_SIZE = SIZE_X * SIZE_Y;
    //int cells[ARRAY_SIZE] = {0};  // Массив клеток игровой области
    int cells[SIZE_X][SIZE_Y] = {};
    int map[SIZE_X][SIZE_Y];  // Массив для промежуточного хода

    sf::Color cell_color = sf::Color(0,200,0,255);
    double cell_size;

    void makeMap(){
        for(int x = 0; x < SIZE_X; x++){
            for(int y = 0; y < SIZE_Y; y++){
                map[x][y] = 0;
            }
        }

        for(int x = 0; x < SIZE_X; x++){
            for(int y = 0; y < SIZE_Y; y++){
                if(cells[x][y] == 1){
                    //map[(x+1)%SIZE_X][y] ++;    //Точка справа
                    map[(SIZE_X + x - 1)%SIZE_X][y] ++; //Точка слева
                    map[x][(y + 1)%SIZE_Y] ++; //Точка снизу
                    //map[x][(SIZE_Y + y - 1)%SIZE_Y] ++; //Точка сверху
                    map[x][y] ++; //Сама точка
                    map[(x+1)%SIZE_X][(SIZE_Y + y - 1)%SIZE_Y] ++;    //Точка сверху справа
                    //map[(SIZE_X + x - 1)%SIZE_X][(SIZE_Y + y - 1)%SIZE_Y] ++; //Точка сверху слева
                    map[(x+1)%SIZE_X][(y + 1)%SIZE_Y] ++; //Точка снизу справа
                    map[(SIZE_X + x - 1)%SIZE_X][(y + 1)%SIZE_Y] ++; //Точка снизу слева
                }
            }
        }
        for(int x = 0; x < SIZE_X; x++){
            for(int y = 0; y < SIZE_Y; y++){
                if(cells[x][y] == 1){
                    map[x][y] = (map[x][y] > 1? 0 : 3);
                }
            }
        }

    }
    void fillMap(){
        for(int x = 0; x < SIZE_X; x++){
            for(int y = 0; y < SIZE_Y; y++){
                cells[x][y] = ((map[x][y] >= 2) ? 1 : 0);
            }
        }
    }

public:
    sf::Color background_color = sf::Color(0,0,0,255);

    Game(PlayingArea field){
        cell_size = field.getWidth() / SIZE_X;
        cells[5][3] = 1;
        cells[6][4] = 1;
        cells[4][5] = 1;
        cells[5][5] = 1;
        cells[6][5] = 1;
    }
    void Update(){
        makeMap();
        fillMap();
    }
    void Draw(sf::RenderWindow *window, PlayingArea field){

        for(int x = 0; x < SIZE_X; x++) {
            for (int y = 0; y < SIZE_Y; y++) {
                sf::RectangleShape cell(sf::Vector2f(cell_size, cell_size));
                cell.setFillColor(cells[x][y] == 0 ? background_color : cell_color);
                cell.setPosition(field.getPosX() + cell_size * (1 + x) + x % SIZE_X,
                                 field.getPosY() + cell_size * (1 + y) + y % SIZE_X);
                window->draw(cell);
            }
        }
    }
};