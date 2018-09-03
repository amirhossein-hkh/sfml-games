#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <iostream>

#define pi 3.14159265
#define INITIAL_BULLETs 10
using namespace std;

sf::RenderWindow window(sf::VideoMode(800,600),"Rifle");
sf::RectangleShape target(sf::Vector2f(80,20));
sf::RectangleShape gun(sf::Vector2f(80,20));
sf::RectangleShape moving_target(sf::Vector2f(20,80));
sf::CircleShape bullet(7);
int x1;
int x2;
sf::RectangleShape leg(sf::Vector2f(80,20));

int number_bullets = INITIAL_BULLETs;
vector <sf::CircleShape> bullets(INITIAL_BULLETs,sf::CircleShape(7));

void display(){
        window.clear(sf::Color::White);
        window.draw(target);
        window.draw(bullet);
        window.draw(gun);
        window.draw(moving_target);
        window.draw(leg);
        for(int i=0;i<number_bullets;i++){
            window.draw(bullets[i]);
        }
        window.display();
}

int main(){
    //initilizing 
    
    int position=400; //position of first target (x)
    float place=20; //position of second target (y)
    int theta=0;
    int tilt=0;
    
    bool dir_down = true;
    bool win = false;
    
    float y=21,x=0,hold;
    
    bullet.setPosition(25,500);
    sf::Texture bullet_texture;
    bullet_texture.loadFromFile("images/bullet.jpg");
    bullet.setTexture(&bullet_texture);
    bullet.setTextureRect(sf::IntRect(20, 20, 100, 100));
    
    target.setPosition(400,0);
    sf::Texture target_texture;
    target_texture.loadFromFile("images/target.jpg");
    target.setTexture(&target_texture);
    target.setTextureRect(sf::IntRect(20, 20, 100, 100));
    
    gun.setPosition(20,500);
    sf::Texture gun_texture;
    gun_texture.loadFromFile("images/Bombard.png");
    gun.setTexture(&gun_texture);
    gun.setTextureRect(sf::IntRect(20, 20, 100, 100));
    
    moving_target.setPosition(760,20);
    moving_target.setTexture(&target_texture);
    moving_target.setTextureRect(sf::IntRect(20, 20, 100, 100));
    
    leg.setPosition(20,500);
    sf::Texture wood_texture;
    wood_texture.loadFromFile("images/Leg.jpg");
    leg.setTexture(&wood_texture);
    leg.setTextureRect(sf::IntRect(20, 20, 100, 100));
    
    
    while(window.isOpen()){
            sf::Event event;
            
            
            for(int i=0;i<number_bullets;i++){
                bullets[i].setPosition(500-40*i,550);
                bullets[i].setTexture(&bullet_texture);
                bullets[i].setTextureRect(sf::IntRect(20, 20, 100, 100));
            }
            
            //check the moving target reached to end 
            if(place>500){
                dir_down = false;
            }else if(place<20){
                dir_down = true;
            }
            
            //move the moving target
            if(dir_down){
                moving_target.setPosition(760,place);
                place+=0.02;
            }else{
              moving_target.setPosition(760,place);
              place-=0.02;
            }
            
        while(window.pollEvent(event)){
            switch(event.type){
                
                case sf::Event::Closed:
                    window.close();
                    break;
                    
                case sf::Event::KeyPressed:
                    //move the target
                    if(event.key.code==sf::Keyboard::Right && position<720){
                        position+=10;
                        target.setPosition(position,0);
                        window.draw(target);
                    }
                    if(event.key.code==sf::Keyboard::Left && position>0){
                        position-=10;
                        target.setPosition(position,0);
                    }
                    //move the gun
                    if(event.key.code==sf::Keyboard::Up&&theta>-90){
                        tilt=-1*theta;
                        theta-=2;
                        gun.setRotation(theta);
                        window.draw(gun);
                        
                    }
                    if(event.key.code==sf::Keyboard::Down&&theta<=0){
                        tilt=-1*theta;
                        theta+=2;
                        gun.setRotation(theta);
                        window.draw(gun);
                    }
                    break;
                
                //handle mouse button
                case sf::Event::MouseButtonPressed:
                    if(event.mouseButton.button == sf::Mouse::Left){
                        while(y>20&&x+25<752){
                            y=-1*tan(tilt*pi/180)*x+500;
                            bullet.setPosition(x+25,y);
                            window.display();
                            x+=0.3;
                            display();
                        }
                        //if hit to the first target
                        if(x>(position-35)&&x<(position+55)){
                            hold=x;
                            x=0;
                            //simulate the second hit
                            while(x+hold+25<740){
                                y=-1*tan(pi-tilt*pi/180)*x+20;
                                bullet.setPosition(x+hold+25,y);
                                x+=0.3;
                                display();
                            }
                            
                            //if hit to second target
                            if(y-7>=place&&y-7<=place+80){
                                win = true;
                            }
                            //didn hit to second target
                            else{
                                bullet.setPosition(25,500);
                                display();
                                y=21;
                                x=0;
                                number_bullets--;
                            }
                        }//if didn't hit to first target
                        else{
                            bullet.setPosition(25,500);
                            display();
                            y=21;
                            x=0;
                            number_bullets--;
                        }
                    x1=0;
                    break;
            }
          }
        }
        
        display();
        
        if(win){
            cout << "you won!!!" << endl;
            break;
        }else if(number_bullets == 0){
            cout << "you lost!!!" << endl;
            break;
        }
    }
    return 0;
}
