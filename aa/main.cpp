#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>
#include <math.h>
#include<stdio.h>
#include<sstream>

#define PI 3.14159265
#define CIRCLE_IN_NUM 5
#define CIRCLE_OUT_NUM 9
#define CIRCLE_RADIUS 10
#define CIRCLE_CENTER_RADIUS 40
#define RAY_LENGTH 130
#define CENTER_X 170
#define CENTER_Y 125
#define SPEED 0.0001

using namespace std;

sf::RenderWindow window(sf::VideoMode(400,500), "aa");
sf::CircleShape center_circle(CIRCLE_CENTER_RADIUS);
vector <sf::CircleShape> circles_in(CIRCLE_IN_NUM+CIRCLE_OUT_NUM,sf::CircleShape(CIRCLE_RADIUS));
vector <sf::CircleShape> circles_out(CIRCLE_OUT_NUM,sf::CircleShape(CIRCLE_RADIUS));
vector <sf::RectangleShape> rays(CIRCLE_IN_NUM+CIRCLE_OUT_NUM,sf::RectangleShape(sf::Vector2f(RAY_LENGTH,1)));
sf::Text level_text;

int counter = 0; //number of circles that made it to the center
int level = 1;

struct coordinate{
    double x;
    double y;
}address[CIRCLE_IN_NUM+CIRCLE_OUT_NUM];

string convert_string(int num){
    stringstream p;
    p << num;
    return p.str();
}

void display(){
    window.clear(sf::Color::White);
    //draw the circles and lines around center
    for(int i=0 ; i<5+counter ; i++){
        window.draw(circles_in[i]);
        window.draw(rays[i]);
    }
    //draw  the circles in the buttom
    for(int i=counter ; i<9 ; i++){
        window.draw(circles_out[i]);
    }
    //draw the center
    window.draw(center_circle);
    
    window.draw(level_text);
    window.display();
}

bool lose(){
    //check the collision of the circle and the circles around the center 
    for(int i=0 ; i<CIRCLE_IN_NUM+counter ; i++){
        for(int j=i+1; j<CIRCLE_IN_NUM+counter ; j++){
            if(sqrt(pow(address[i].x-address[j].x,2)+pow(address[i].y-address[j].y,2)) <= 2 * CIRCLE_RADIUS ){
                return true;
            }
        }
    }
    return false;
}

int main()
{
    //initilizing
    sf::Time postpone = sf::seconds(2);
    
    sf::Font font;
    font.loadFromFile("OLDENGL.TTF");
    
    center_circle.setFillColor(sf::Color::Black);
    center_circle.setPosition(CENTER_X,CENTER_Y);
    
    for(int i=0; i<CIRCLE_IN_NUM+CIRCLE_OUT_NUM ;i++){
        rays[i].setPosition(210,165);
    }
    
    for(int i=0 ; i<CIRCLE_OUT_NUM ; i++){
        circles_out[i].setFillColor(sf::Color::Black);
        circles_out[i].setPosition(195-25*i,360);
    }
    
    double angles[CIRCLE_OUT_NUM+CIRCLE_OUT_NUM]={0,1.25,2.5,3.75,5,PI/2,PI/2,PI/2,PI/2,PI/2,PI/2,PI/2,PI/2,PI/2};
    
    while (window.isOpen())
    {
        sf::Event event;
        
        for(int i=0; i<CIRCLE_IN_NUM+counter; i++){
            rays[i].setFillColor(sf::Color::Black);
            rays[i].setRotation(angles[i]*180/PI);
            circles_in[i].setPosition(130*cos(angles[i])+202,130*sin(angles[i])+152);
            circles_in[i].setFillColor(sf::Color::Black);
            address[i].x=130*cos(angles[i])+200;
            address[i].y=130*sin(angles[i])+150;
            angles[i]+= SPEED * level;
        }
        
        window.clear(sf::Color::White);
        
        //check wining 
        if(counter==CIRCLE_OUT_NUM){
            window.clear(sf::Color::Green);
            sf::Text text;
            text.setFont(font);
            text.setString("WIN");
            text.setCharacterSize(50);
            text.setStyle(sf::Text::Bold | sf::Text::Underlined);
            window.draw(text);
            window.display();
            sleep(postpone);
            counter=0;
            level++;
            
            //reinitiliz the setting
            angles[0]=0;
            angles[1]=1.25;
            angles[2]=2.5;
            angles[3]=3.75;
            angles[4]=5;
            
            for(int i=5;i<=CIRCLE_OUT_NUM+CIRCLE_OUT_NUM;i++){
                angles[i]=PI/2;
            }
            for(int i=0;i<CIRCLE_OUT_NUM;i++){
                circles_out[i].setPosition(195-25*i,360);
            }
            
        }
        
        //handling event (Keyboard and exit)
        while (window.pollEvent(event))
        {
            switch(event.type){
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if(event.key.code==sf::Keyboard::Up){
                        int y = 360;
                        while(y>=280){
                            circles_out[counter].setPosition(195,y);
                            y-=2;
                            display();
                        }
                        
                        circles_in[CIRCLE_IN_NUM+counter].setPosition(195,280);
                        address[CIRCLE_IN_NUM+counter].x=195;
                        address[CIRCLE_IN_NUM+counter].y=280;
                        counter++;
                        
                        int x=1;
                        while(x<=25){
                            for(int i=counter ; i<CIRCLE_OUT_NUM ;i++){
                                circles_out[i].setPosition(195-25*i+x*counter,360);
                            }
                            x+=2;
                            display();
                        }
                        
                    }
                    break;
            }
        }
        
        //level text
        level_text.setFont(font);
        level_text.setPosition(CENTER_X+30,CENTER_Y+15);
        level_text.setCharacterSize(40);
        level_text.setString(convert_string(level));
        
        //check losing
        if(lose()){
            window.clear(sf::Color::Red);
            sf::Text text;
            text.setFont(font);
            text.setString("Game Finished!!!!");
            text.setCharacterSize(50);
            text.setFillColor(sf::Color::Blue);
            text.setStyle(sf::Text::Bold | sf::Text::Underlined);
            window.draw(text);
            window.display();
            sleep(postpone);
            break;
        }
        
        display();
    }

    return 0;
}
