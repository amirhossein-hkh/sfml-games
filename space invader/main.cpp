#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include<stdlib.h>
#include<time.h>
#include <stdio.h>
#include<math.h>
using namespace sf;
using namespace std;
RenderWindow window(VideoMode(800,600),"Galatic Attack");
Sprite spaceship;
Sprite rocket1;
Sprite rocket2;
vector <Sprite> a1(10);
vector <Sprite> a2(10);
vector <Sprite> a3(10);
vector <RectangleShape>HP(112,RectangleShape(Vector2f(6,6)));
int arr1[10]={0};
int arr2[10]={0};
int arr3[10]={0};
Sprite alienshot;
Clock timer;
int yr1,yr2,value=0;
float position[10];
float p;
int hp=112;
int counting;
struct coordinate{
    float x=0;
    float y=0;
}address1[10],address2[10],address3[10];

void check1(int xrocket1,int yrocket1){
  for(int i=0;i<10;i++){
        if(xrocket1-address1[i].x<60 && xrocket1-address1[i].x>-10&& yrocket1-address1[i].y>-40&& yrocket1-address1[i].y<50){
                if(arr1[i]==0){
                counting++;
                arr1[i]=1;
                }
                return;
        }
        if(xrocket1-address2[i].x<60 && xrocket1-address2[i].x>-10&& yrocket1-address2[i].y>-40&& yrocket1-address2[i].y<50){
            if(arr2[i]==0){
                counting++;
                arr2[i]=1;
                }
            return;
        }
        if(xrocket1-address3[i].x<60 && xrocket1-address3[i].x>-10&& yrocket1-address3[i].y>-40&& yrocket1-address3[i].y<50){
                if(arr3[i]==0){
                counting++;
                arr3[i]=1;
                }
                 return;
        }
    }
}
void check2(int xrocket2,int yrocket2){
    for(int i=0;i<10;i++){
        if(xrocket2-address1[i].x<60  && xrocket2-address1[i].x>-10&& yrocket2-address1[i].y>-40 && yrocket2-address1[i].y<50){
                if(arr1[i]==0){
                    counting++;
                    arr1[i]=1;
                }
        }
        if(xrocket2-address2[i].x<60  && xrocket2-address2[i].x>-10&& yrocket2-address2[i].y>-40 && yrocket2-address2[i].y<50){
                if(arr2[i]==0){
                    counting++;
                    arr2[i]=1;
            }
        }
        if(xrocket2-address3[i].x<60  && xrocket2-address3[i].x>-10&& yrocket2-address3[i].y>-40 && yrocket2-address3[i].y<50){
            if(arr3[i]==0){
                counting++;
                arr3[i]=1;
            }
        }
    }
}
void display(){
    window.clear();
    for(int i=0 ; i<10 ; i++){
        if(arr1[i]==0)
            window.draw(a1[i]);
        if(arr2[i]==0)
            window.draw(a2[i]);
        if(arr3[i]==0)
            window.draw(a3[i]);
    }
    window.draw(spaceship);
    window.draw(rocket1);
    window.draw(rocket2);
    window.draw(alienshot);
   for(int i=0;i<hp;i++)
        window.draw(HP[i]);
    window.display();
}
void reset(int x){
    rocket1.setPosition(372+x,483);
    rocket2.setPosition(430+x,483);
    yr1=0;
    yr2=0;
}
void restart(){
    static int c=0;
    for(int i=0 ; i<10 ; i++){
        position[i]=(i+1)*50+(i*5)+55;
    }
    for(int i=0;i<10;i++){
        a1[i].setPosition(position[i],20);
        a2[i].setPosition(position[i],70);
        a3[i].setPosition(position[i],120);
        address1[i].x=position[i];
        address1[i].y=20;
        address2[i].x=position[i];
        address1[i].y=70;
        address3[i].x=position[i];
        address3[i].y=120;
    }

}
int random_alien(int c1,int place){
    int row,i;
    static float x,y,change=0;
    row=rand()%3+1;
    while(counting<=30){
        i=rand()%10;
        if(row==1){
            if(arr1[i]==0){
            break;
            }
        }
        if(row==2){
            if(arr2[i]==0){
            break;
            }
        }
        if(row==3){
            if(arr3[i]==0){
            break;
            }
        }
    }
    if(value==0){
        if(row==1){
            if(c1%2==1){
                x=position[i]+p+5;
               y=50*sin(position[i])+49;
               alienshot.setPosition(x,y);
            }
            else{
                x=position[i]+p+5;
                y=50*cos(position[i])+49;
                alienshot.setPosition(x,y);
            }
        }
        if(row==2){
            if(c1%2==1){
                x=position[i]+p+5;
                y=60*cos(position[i])+99;
                alienshot.setPosition(x,y);
            }
            else{
                x=position[i]+p+5;
                y=60*sin(position[i])+99;
                alienshot.setPosition(x,y);
            }
        }
        if(row==3){
             if(c1%2==1){
                x=position[i]+p+5;
                y=50*sin(position[i])+149;
                alienshot.setPosition(x,y);
             }
            else{
                x=position[i]+p+5;
                y=50*cos(position[i])+149;
                alienshot.setPosition(x,y);
            }
        }
    }
    value++;
    alienshot.setPosition(x,y+change);
    change+=2;
    if(y+change>500){
            value=0;
            change=0;
        if(x>place&&x<place+80){
            hp--;
            spaceship.setPosition(365,500);
            rocket1.setPosition(372,483);
            rocket2.setPosition(430,483);
    return 1;
        }
    }
    return 0;
}
void attack(int place,float Elapsedtime,int c1){
    static float m=-1;
    static int i;
    static int row=0;
    static struct coordinate firstplace;
    static struct coordinate currentposition;
    if(Elapsedtime>=5){
        row=rand()%3+1;
        i=rand()%10;
        firstplace.x=position[i]+p;
        if(row==1){
            if(c1%2==1){
                m=(500-50*sin(position[i])-40)/(place-position[i]-p);
                firstplace.y=50*sin(position[i])+40;
            }
            else{
                m=(500-50*cos(position[i])-40)/(place-position[i]-p);
                firstplace.y=50*cos(position[i])+40;
            }
        }
        if(row==2){
            if(c1%2==1){
                m=(500-60*cos(position[i])-90)/(place-position[i]-p);
                firstplace.y=60*cos(position[i])+90;
            }
            else{
                m=(500-60*sin(position[i])-90)/(place-position[i]-p);
                firstplace.y=60*sin(position[i])+90;
            }
        }
        if(row==3){
            if(c1%2==1){
                m=(500-50*sin(position[i])-140)/(place-position[i]-p);
                firstplace.y=50*sin(position[i])+140;
            }
            else{
                m=(500-50*cos(position[i])-140)/(place-position[i]-p);
                firstplace.y=50*cos(position[i])+140;
            }
        }
        timer.restart();
    }
    if(row==1){
      a1[i].setPosition(currentposition.x+firstplace.x,(currentposition.y)+firstplace.y);
      currentposition.y+=1;
      if(m<0){
        currentposition.x+=1;
      }
      if(m>0){
        currentposition.x-=1;
      }
      if(currentposition.y+firstplace.y>600||currentposition.y+firstplace.y<0){
        a1[i].setPosition(position[i]+p,50*sin(position[i])+40);
        currentposition.y=0;
        currentposition.x=0;
        row=0;
      }
    }
    if(row==2){
       a2[i].setPosition(currentposition.x+firstplace.x,(currentposition.y)+firstplace.y);
       currentposition.y+=1;
       if(m<0){
        currentposition.x+=1;
       }
       if(m>0){
        currentposition.x-=1;
       }
       if(currentposition.y+firstplace.y>600||currentposition.y+firstplace.y<0){
            a2[i].setPosition(position[i]+p,50*sin(position[i])+90);
            currentposition.y=0;
            currentposition.x=0;
            row=0;
       }
    }
    if(row==3){
        a3[i].setPosition(currentposition.x+firstplace.x,(currentposition.y)+firstplace.y);
        currentposition.y+=1;
        if(m<0){
          currentposition.x+=1;
        }
        if(m>0){
          currentposition.x-=1;
        }
        if(currentposition.y+firstplace.y>600||currentposition.y+firstplace.y<0){
            a3[i].setPosition(position[i]+p,50*sin(position[i])+140);
            currentposition.y=0;
            currentposition.x=0;
            row=0;
        }
    }
}
int main(){
    int x=0;
    int c=0;
    int value=0;
    Texture alien1;
    Texture alien2;
    Texture alien3;
    Texture alien4;
    Texture rocket;
    Texture space_ship;
    Texture enemyshot;
    spaceship.setPosition(365,500);
    rocket1.setPosition(372,483);
    rocket2.setPosition(430,483);
    alien1.loadFromFile("images/alien 1.png");
    alien2.loadFromFile("images/alien 2.png");
    alien3.loadFromFile("images/alien 3.png");
    rocket.loadFromFile("images/rocket.jpg");
    enemyshot.loadFromFile("images/alienshot.jpg");
    space_ship.loadFromFile("images/spaceship.jpg");
    for(int i=0;i<hp;i++){
        HP[i].setPosition(6*i+i,590);
        HP[i].setFillColor(Color::Red);
    }
    for(int i=0 ; i<10 ; i++){
        a1[i].setTexture(alien1);
        a2[i].setTexture(alien2);
        a3[i].setTexture(alien3);
    }
    alienshot.setTexture(enemyshot);
    rocket2.setTexture(rocket);
    spaceship.setTexture(space_ship);
    rocket1.setTexture(rocket);
    for(int i=0 ; i<10 ; i++){
        position[i]=(i+1)*50+(i*5)+55;
    }
    for(int i=0 ; i<10  ; i++){
        a1[i].setPosition(position[i],20);
        a2[i].setPosition(position[i],70);
        a3[i].setPosition(position[i],120);
        address1[i].x=position[i];
        address1[i].y=20;
        address2[i].x=position[i];
        address1[i].y=70;
        address3[i].x=position[i];
        address3[i].y=120;
    }
    alienshot.setPosition(600,800);
    Time wait=seconds(2);
    display();
    sleep(wait);
    int counter=0;
    int c1=0;
    srand(time(NULL));
    while(window.isOpen()){
        sf::Event event;
        for(int i=0 ; i<10 ; i++)
            position[i]+=0.005;
        if(c1%2==0){
        for(int i=9 ; i>=0 ; i--){
            if(position[i]+p>=800)
                position[i]=-1*p;
        }
        for(int i=0 ; i<10  ; i++){
            a1[i].setPosition(position[i]+p,50*sin(position[i])+40);
            a2[i].setPosition(position[i]+p,60*cos(position[i])+90);
            a3[i].setPosition(position[i]+p,50*sin(position[i])+140);
            address1[i].x=position[i]+p;
            address1[i].y=50*sin(position[i])+40;
            address2[i].x=position[i]+p;
            address2[i].y=60*cos(position[i])+90;
            address3[i].x=position[i]+p;
            address3[i].y=50*sin(position[i])+140;
            p+=0.001;
          }
        }
        else{
           for(int i=9 ; i>=0 ; i--){
            if(position[i]+p>=800)
                position[i]=-1*p;
        }
        for(int i=0 ; i<10  ; i++){
            a1[i].setPosition(position[i]+p,50*cos(position[i])+40);
            a2[i].setPosition(position[i]+p,60*sin(position[i])+90);
            a3[i].setPosition(position[i]+p,50*cos(position[i])+140);
            address1[i].x=position[i]+p;
            address1[i].y=50*cos(position[i])+40;
            address2[i].x=position[i]+p;
            address2[i].y=60*sin(position[i])+90;
            address3[i].x=position[i]+p;
            address3[i].y=cos(position[i])+140;
            p+=0.001;
            c1++;
          }
        }
        while(window.pollEvent(event)){
            if(event.type==Event::Closed)
                window.close();
            if(event.type==Event::KeyPressed){
                if(event.key.code==Keyboard::Right){
                    if(x+360<765){
                        x+=30;
                        rocket1.setPosition(372+x,483);
                        rocket2.setPosition(430+x,483);
                        spaceship.setPosition(365+x,500);
                    }
                }
            }
            if(event.type==Event::KeyPressed){
                if(event.key.code==Keyboard::Left){
                    if(x+365>0){
                    x-=30;
                    rocket1.setPosition(372+x,483);
                    rocket2.setPosition(430+x,483);
                    spaceship.setPosition(365+x,500);
                    }
                }
            }
            if(event.type==Event::KeyPressed){
                if(event.key.code==Keyboard::Up){
                    if(counter%2==0){
                        c=1;
                            counter++;
                    }
                    else
                        c=2;
                    }
                }
        }
        if(c==1){
            yr1+=5;
            rocket1.setPosition(372+x,483-yr1);
            check1(372+x,483-yr1);
        }
        if(c==2){
            yr2+=5;
            yr1+=5;
            rocket1.setPosition(372+x,483-yr1);
            rocket2.setPosition(430+x,483-yr2);
            check1(372+x,483-yr1);
            check2(430+x,483-yr2);
            if(483-yr2<0){
            reset(x);
            counter++;
            c=0;
            }
        }
        value=random_alien(c1,375+x);
       if(value){
            x=0;
        }
                    if(counting==30){
                window.close();
                break;
            }
        attack(375+x,timer.getElapsedTime().asSeconds(),c1);
        display();
        if(hp==0)
            break;
    }
    return 0;
}
