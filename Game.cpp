//
// Created by Fridr on 16.11.2019.
//

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <vector>
//#include <pair>

class Game {
public:
    class PlayingArea{
    private:
        float pos_x = 0, pos_y = 0;
        float width = 0, height = 0;
    public:
        PlayingArea(float pos_x, float pos_y, float width, float height){
            this->pos_x = pos_x;
            this->pos_y = pos_y;
            this->width = width;
            this->height = height;
        }
        float getPosX() {return pos_x;}
        float getPosY() {return pos_y;}
        float getWidth() {return width;}
        float getHeight() {return height;}
    };
    enum GameMode {PLAY, EDIT};
    enum EditMode {SET, REMOVE};
private:
    std::vector<std::pair<std::string, sf::Color>> gamemode_conf =
            {{"play", sf::Color(32, 178, 170)},
             {"edit", sf::Color(220, 20, 60)}};
//    std::string gamemode_str[2] = {"play", "edit"};
//    sf::Color gamemode_color[2] = {sf::Color(32, 178, 170), sf::Color(220, 20, 60)};
    PlayingArea field = PlayingArea(0,0,0,0);

    GameMode current_gamemode = EDIT;

    int cell_size = 10;
    int SIZE_X = 0; // Длинна в клетках
    int SIZE_Y = 0; // Ширина в клетках
    int** cells;    // Массив клеток игровой области
    int** map;      // Массив для промежуточного хода

    // Цвет живых клеток
    sf::Color cell_color = sf::Color(0,200,0,255);
    // Шаблоны для стен и клеток
    sf::RectangleShape walls_draw, cell_draw;
    sf::Text gamemode_draw, help_draw;

    /**
     * @brief Функция, заполняющая массив карты поля
     */
    void makeMap(){
        for(int x = 0; x < SIZE_X; x++){
            for(int y = 0; y < SIZE_Y; y++){
                map[x][y] = 0;
            }
        }

        for(int x = 0; x < SIZE_X; x++){
            for(int y = 0; y < SIZE_Y; y++){
                    map[x][y] = 0;
                    map[x][y] += cells[(x+1) % SIZE_X][y];              //Точка справа
                    map[x][y] += cells[(SIZE_X + x - 1) % SIZE_X][y];   //Точка слева
                    map[x][y] += cells[x][(y + 1) % SIZE_Y ];           //Точка снизу
                    map[x][y] += cells[x][(SIZE_Y + y - 1) % SIZE_Y];   //Точка сверху
//                    map[x][y] += cells[x][y];                           //Сама точка
                    map[x][y] += cells[(x + 1) % SIZE_X][(SIZE_Y + y - 1) % SIZE_Y];              //Точка сверху справа
                    map[x][y] += cells[(SIZE_X + x - 1) % SIZE_X][(SIZE_Y + y - 1) % SIZE_Y];   //Точка сверху слева
                    map[x][y] += cells[(x + 1) % SIZE_X][(y + 1) % SIZE_Y];                       //Точка снизу справа
                    map[x][y] += cells[(SIZE_X + x - 1) % SIZE_X][(y + 1) % SIZE_Y];            //Точка снизу слева
            }
        }
    }

    void fillMap(){
        for(int x = 0; x < SIZE_X; x++){
            for(int y = 0; y < SIZE_Y; y++){
                if ( cells[x][y] == 1 && (map[x][y] == 3 || map[x][y] == 2) ||
                        cells[x][y] == 0 && map[x][y] == 3){
                    cells[x][y] = 1;
                } else {
                    cells[x][y] = 0;
                }
            }
        }
    }

public:
    sf::Color background_color = sf::Color(0,0,0,255);
    sf::Font main_font = sf::Font();

    Game(PlayingArea field, int cell_size = 10){
        this->field = field;
        this->cell_size = cell_size;
        SIZE_X = (int)field.getWidth() / cell_size;
        SIZE_Y = (int)field.getHeight() / cell_size;
        map = new int*[SIZE_X];
        cells = new int*[SIZE_X];
        for (int x = 0; x < SIZE_X; ++x) {
            map[x] = new int[SIZE_Y];
            cells[x] = new int[SIZE_Y];
            for (int y = 0; y < SIZE_Y; ++y) {
                map[x][y] = 0;
                cells[x][y] = 0;
            }
        }

        //Шрифт
        main_font.loadFromFile("D:\\Projects\\C++\\Goo\\fonts\\PressStart2P-Regular.ttf");

        // Инициализация интерфейса
        walls_draw = sf::RectangleShape(sf::Vector2f(field.getWidth(), field.getHeight()));
        walls_draw.setOutlineColor(sf::Color::Yellow);
        walls_draw.setOutlineThickness(5);
        walls_draw.setFillColor(sf::Color(0,0,0,0));
        walls_draw.setPosition(sf::Vector2f(field.getPosX(), field.getPosY()));

        // Вывод текущего режима на экран
        gamemode_draw.setFont(main_font);
        gamemode_draw.setCharacterSize(14);
        gamemode_draw.setString(gamemode_conf[current_gamemode].first);
        gamemode_draw.setFillColor(gamemode_conf[current_gamemode].second);
        gamemode_draw.setPosition(sf::Vector2f(field.getPosX() + field.getWidth()*2/3, field.getPosY() - 30));

        // Вывод подсказкт
        help_draw.setFont(main_font);
        help_draw.setCharacterSize(12);
        help_draw.setString("A - auto mode\n"
                                "E - edit mode\n"
                                "S - make step\n"
                                "R - reset\n"
                                "LMB|RMB - set|remove cell");
        help_draw.setFillColor(sf::Color::White);
        help_draw.setPosition(sf::Vector2f(field.getPosX() + 10, field.getPosY() - 120));


        // Шаблон для клеток
        cell_draw = sf::RectangleShape(sf::Vector2f(cell_size, cell_size));
    }

    void step(){
        makeMap();
        fillMap();
    }

    void update(){
        if (current_gamemode == GameMode::PLAY) {
            step();
        }
    }

    void draw(sf::RenderWindow *window){
        for(int x = 0; x < SIZE_X; x++) {
            for (int y = 0; y < SIZE_Y; y++) {
                sf::RectangleShape cell(cell_draw);
                cell.setFillColor(cells[x][y] == 0 ? background_color : cell_color);
                cell.setOutlineColor(background_color);
                cell.setOutlineThickness(2);
                cell.setPosition(field.getPosX() + cell_size * x,
                                 field.getPosY() + cell_size * y);
                window->draw(cell);
            }
        }
        window->draw(walls_draw);
        window->draw(gamemode_draw);
        window->draw(help_draw);
    }

    void setGameMode(GameMode mode){
        current_gamemode = mode;
        gamemode_draw.setString(gamemode_conf[current_gamemode].first);
        gamemode_draw.setFillColor(gamemode_conf[current_gamemode].second);
    }

    void alterCell(int x, int y, EditMode mode){
        int cell_x = -1, cell_y = -1;
        cell_x = (x - (int)field.getPosX()) / cell_size;
        cell_y = (y - (int)field.getPosY()) / cell_size;
        if (cell_x >= 0 && cell_x < SIZE_X &&
                cell_y >= 0 && cell_y < SIZE_Y){
            cells[cell_x][cell_y] = (mode == EditMode::SET ? 1 : 0);
        }
    }

    void reset(){
        for (int x = 0; x < SIZE_X; ++x) {
            for (int y = 0; y < SIZE_Y; ++y) {
                map[x][y] = 0;
                cells[x][y] = 0;
            }
        }

        setGameMode(GameMode::EDIT);
    }
};