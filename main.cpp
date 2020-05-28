#include <SFML/Graphics.hpp>
#include <iostream>
#include <conio.h>
#include <windows.h> //for sleep() operation
#include <ctime>
#include <cstdlib> // contains srand() & rand()

using namespace std;
using namespace sf;

#define rows 50
#define cols 50
#define size 10
#define pos_x 0
#define pos_y 0

int num_of_neighbours;
bool field[rows][cols];
bool update[rows][cols];

void rand_fill(){
    srand(time(NULL));
    for(int i =0; i<rows; i++)
        for(int j = 0; j<cols; j++){
            int secret = rand() % 2 + 1;
            if(secret%2==0)
                field[i][j] = true;
            else
                field[i][j] = false;
    }
}
//replace the arrays
void change(){
    for(int i=0; i<rows; i++)
        for(int j =0;j<cols; j++)
            field[i][j] = update[i][j];
}

void clear_the_field(bool arr[rows][cols]){
    for(int i =0; i<rows; i++)
        for(int j =0; j<cols; j++)
            arr[i][j] = false;
}

int res(int y, int x){
    num_of_neighbours = 0;
    if(x==0 && y == 0){
        if(field[y+1][x]==true)
            num_of_neighbours++;
        if(field[y][x+1]==true)
            num_of_neighbours++;
        if(field[y+1][x+1]==true)
            num_of_neighbours++;
    }
    else if(x==0 && y == rows-1){ //Left down angle
        if(field[y-1][x]==true)
            num_of_neighbours++;
        if(field[y-1][x+1]==true)
            num_of_neighbours++;
        if(field[y][x+1]==true)
            num_of_neighbours++;
    }
    else if(y==0 && x==cols-1){ //right upper angle
        if(field[y+1][x]==true)
            num_of_neighbours++;
        if(field[y+1][x-1]==true)
            num_of_neighbours++;
        if(field[y][x-1]==true)
            num_of_neighbours++;
    }
    else if(x==cols-1 && y == rows-1){ //right down  angle
        if(field[y-1][x]==true)
            num_of_neighbours++;
        if(field[y][x-1]==true)
            num_of_neighbours++;
        if(field[y-1][x-1]==true)
            num_of_neighbours++;
    }
    else if(y==0 && (x>0 && x<cols-1)){ //up
        if(field[y][x-1]==true)
            num_of_neighbours++;
        if(field[y+1][x]==true)
            num_of_neighbours++;
        if(field[y+1][x-1]==true)
            num_of_neighbours++;
        if(field[y+1][x+1]==true)
            num_of_neighbours++;
        if(field[y][x+1]==true)
            num_of_neighbours++;
    }
    else if(y==rows-1 && (x>0 && x<cols-1)){//down
        if(field[y-1][x]==true)
            num_of_neighbours++;
        if(field[y][x-1]==true)
            num_of_neighbours++;
        if(field[y][x+1]==true)
            num_of_neighbours++;
        if(field[y-1][x+1]==true)
            num_of_neighbours++;
        if(field[y-1][x-1]==true)
            num_of_neighbours++;
    }
    else if(x==0 && (y>0 && y<rows-1)){ //left
        if(field[y][x+1]==true)
            num_of_neighbours++;
        if(field[y+1][x]==true)
            num_of_neighbours++;
        if(field[y-1][x]==true)
            num_of_neighbours++;
        if(field[y-1][x+1]==true)
            num_of_neighbours++;
        if(field[y+1][x+1]==true)
            num_of_neighbours++;
    }
    else if(x==cols-1 && (y>0 && y<rows-1)){ //right
        if(field[y+1][x]==true)
            num_of_neighbours++;
        if(field[y-1][x]==true)
            num_of_neighbours++;
        if(field[y][x-1]==true)
            num_of_neighbours++;
        if(field[y+1][x-1]==true)
            num_of_neighbours++;
        if(field[y-1][x-1]==true)
            num_of_neighbours++;
    }
    else{
    if(field[y-1][x-1] == true)
        num_of_neighbours++;
    if(field[y-1][x] == true)
        num_of_neighbours++;
    if(field[y-1][x+1] == true)
        num_of_neighbours++;
    if(field[y][x+1] == true)
        num_of_neighbours++;
    if(field[y+1][x+1] == true)
        num_of_neighbours++;
    if(field[y+1][x] == true)
        num_of_neighbours++;
    if(field[y+1][x-1] == true)
        num_of_neighbours++;
    if(field[y][x-1] == true)
        num_of_neighbours++;
    }
    return num_of_neighbours;
}


int main()
{
    Font font;
    font.loadFromFile("calibri.ttf");

    int mouse_x;
    int mouse_y;
    int k = 2 ;

    Text text("Adding the cells..", font);
    text.setCharacterSize(30);
    text.setStyle(sf::Text::Regular);
    text.setFillColor(sf::Color::Red);
    text.setPosition(10, rows*size+k*cols);

    Text text2("Clear", font);
    text2.setCharacterSize(30);
    text2.setStyle(sf::Text::Regular);
    text2.setFillColor(sf::Color::Red);
    text2.setPosition(cols*size+k*cols - 250, rows*size+k*cols+45);

    Text text1("Fill Random", font);
    text1.setCharacterSize(30);
    text1.setStyle(sf::Text::Regular);
    text1.setFillColor(sf::Color::Red);
    text1.setPosition(cols*size+k*cols - 250, rows*size+k*cols+5);

    RectangleShape rectangle;
    rectangle.setSize(Vector2f(size, size));
    rectangle.setPosition(pos_x, pos_y);

    clear_the_field(field);
    clear_the_field(update);

    RenderWindow window(VideoMode(cols*size+k*cols-k, rows*size+k*cols+50+100), "Game of Life");

    while (window.isOpen()){
        Event event;
        while (window.pollEvent(event)){
        switch (event.type){
        // window is closed
        case sf::Event::Closed:
            window.close();
            break;
        // START THE GAME
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Space){
                while(!GetAsyncKeyState(VK_RETURN) ){
                    for(int i = 0; i<rows; i++)
                        for(int j = 0; j<cols; j++){
                            if( res(i, j) >= 4 || res(i, j) < 2 )
                                update[i][j] = false;
                            if(field[i][j] == true && (res(i, j) == 3 || res(i, j) == 2))
                                update[i][j] = true;
                            if(field[i][j] == false && res(i, j) == 2)
                                update[i][j] = false;
                            if(field[i][j] == false && res(i, j) == 3)
                                update[i][j] = true;

                        }
                        change();
                        window.clear();
                        for(int i = 0; i<rows; i++)
                            for(int j = 0; j<cols;  j++){
                                if(field[i][j] == true){
                                    rectangle.setSize(Vector2f(size, size));
                                    rectangle.setPosition(pos_x + j*size + k*j, pos_y + i*size+ k*i );
                                    rectangle.setFillColor(Color::Black);
                                    window.draw(rectangle);
                                }
                                else {
                                    rectangle.setSize(Vector2f(size, size));
                                    rectangle.setPosition(pos_x + j*size + k*j, pos_y + i*size+ k*i );
                                    rectangle.setFillColor(Color::White);
                                    window.draw(rectangle);
                                }
                            }
                        text.setString("Process");
                        text.setFillColor(sf::Color::Green);
                        window.draw(text);
                        window.display();
                        Sleep(50);
                }
                break;
            }
            break;
        // mouse is clicked
        case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Left){
                if(event.mouseButton.x >= cols*size+k*cols - 275 && event.mouseButton.x <= cols*size+k*cols - 75)
                    if(event.mouseButton.y >= rows*size+k*cols+10 && event.mouseButton.y <= rows*size+k*cols+40)
                        rand_fill();
                if(event.mouseButton.x >= cols*size+k*cols - 275 && event.mouseButton.x <= cols*size+k*cols - 75)
                    if(event.mouseButton.y >= rows*size+k*cols+50 && event.mouseButton.y <= rows*size+k*cols+80)
                        clear_the_field(field);
                mouse_x = event.mouseButton.x;
                mouse_y = event.mouseButton.y;
                field[(int)mouse_y/(size+k)][(int)mouse_x/(size+k)] = true;
            }
            else {
                mouse_x = event.mouseButton.x;
                mouse_y = event.mouseButton.y;
                field[(int)mouse_y/(size+k)][(int)mouse_x/(size+k)] = false;

            }
        default:
            break;
        }
    }
        window.clear();
        // Draw the field
        for(int i = 0; i<rows; i++)
            for(int j = 0; j<cols;  j++){
                if(field[i][j] == true){
                    rectangle.setSize(Vector2f(size, size));
                    rectangle.setPosition(pos_x + j*size + k*j, pos_y + i*size+ k*i );
                    rectangle.setFillColor(Color::Black);
                    window.draw(rectangle);
                }
                else {
                    rectangle.setSize(Vector2f(size, size));
                    rectangle.setPosition(pos_x + j*size + k*j, pos_y + i*size+ k*i );
                    rectangle.setFillColor(Color::White);
                    window.draw(rectangle);
                }
            }
        text.setString("Adding the cells");
        text.setFillColor(sf::Color::Red);
        window.draw(text);
        rectangle.setFillColor(Color::White);
        rectangle.setSize(Vector2f(200, 30));
        rectangle.setPosition(cols*size+k*cols - 275, rows*size+k*cols+10);
        window.draw(rectangle);
        rectangle.setFillColor(Color::White);
        rectangle.setSize(Vector2f(200, 30));
        rectangle.setPosition(cols*size+k*cols - 275, rows*size+k*cols+50);
        window.draw(rectangle);
        window.draw(text1);
        window.draw(text2);
        window.display();
    }
    return 0;
}
