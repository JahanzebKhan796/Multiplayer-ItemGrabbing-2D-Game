#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <cstring>
#include <pthread.h>
#include <unistd.h>
#include <atomic>
#include <X11/Xlib.h>
using namespace std;

atomic<int> x, y, x2, y2;
atomic<int> n,k,sc, sc2, item_count;
int** arr;
sf::Sprite player;
sf::Sprite player2;
sf::Sprite* apples;
sf::Text score;
sf::Text score2;

void* mplayer1(void* argc){
	
sf::RenderWindow* window_ptr = (sf::RenderWindow*) argc;
bool lflag;
lflag = false;
	
	 while (window_ptr->isOpen()){
		
	    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            	if(lflag==false){
            	if(y!=0){
            	y -= 40;
            	player.setPosition(x,y);
            	lflag=true;
            	
            	}
            	}
            	continue;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            	if(lflag==false){
            	if(y!=40*(n-1)){
            	y += 40;
            	player.setPosition(x,y);
            	lflag=true;
            	
            	}
            	}
            	continue;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            	if(lflag==false){
            	if(x!=40*(n-1)+5){
            	x += 40;
            	player.setPosition(x,y);
            	lflag=true;
            	}
            	}
            	continue;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            	if(lflag==false){
            	if(x!=5){
            	x -= 40;
            	player.setPosition(x,y);
            	lflag=true;
            	}
            	}
            	continue;
            }
            
            for(int i = 0; i<k; i++){
            	if(arr[i][0]==(x-5)/40 && arr[i][1]==y/40 && apples[i].getScale().x==0.05f){
            		apples[i].setScale(0,0);
            		sc +=5;
            		string score_str = "Score p1: " + to_string(sc);
            		score.setString(score_str);
            		item_count = item_count+1;
            		}
            }
			
	lflag = false;
        
	}
	return NULL;
}


void* mplayer2(void* argc){
	
sf::RenderWindow* window_ptr = (sf::RenderWindow*) argc;
bool lflag;
lflag = false;
	
	 while (window_ptr->isOpen()){
		
	    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            	if(lflag==false){
            	if(y2!=0){
            	y2 -= 40;
            	player2.setPosition(x2,y2);
            	lflag=true;
            	}
            	}
            	continue;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            	if(lflag==false){
            	if(y2!=40*(n-1)){
            	y2 += 40;
            	player2.setPosition(x2,y2);
            	lflag=true;
            	}
            	}
            	continue;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            	if(lflag==false){
            	if(x2!=40*(n-1)+5){
            	x2 += 40;
            	player2.setPosition(x2,y2);
            	lflag=true;}
            	}
            	continue;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            	if(lflag==false){
            	if(x2!=5){
            	x2 -= 40;
            	player2.setPosition(x2,y2);
            	lflag=true;}
            	}
            	continue;
            }
            
            for(int i = 0; i<k; i++){
            	if(arr[i][0]==(x2-5)/40 && arr[i][1]==y2/40 && apples[i].getScale().x==0.05f){
            		apples[i].setScale(0,0);
            		sc2 +=5;
            		string score_str = "Score p2: " + to_string(sc2);
            		score2.setString(score_str);
            		item_count = item_count+1;
            		}
            }
			
	lflag = false;
	}
	return NULL;
}

int main()
{
   XInitThreads();
   
   int c = 0;
   sc = 0;
   sc2 = 0;
	
    srand(time(0));
    n = rand()%90 + 10;
    n = n*9; //last digit of my rollnumber is 9
    n = 210419/n;
    n = n%25;
if(n<10)
	n+=15;	
	


 
    sf::RenderWindow window(sf::VideoMode(n*40, n*40 + 40), "Thread Game!");
    window.setFramerateLimit(60);
    
    sf::RenderWindow* window_ptr = &window;
    
    sf::RectangleShape** board;
    board = new sf::RectangleShape*[n];
    for(int i=0;i<n;i++)
    	board[i] = new sf::RectangleShape[n];
    
    for(int i=0;i<n;i++){
    	for(int j=0;j<n;j++){
    		board[i][j].setSize(sf::Vector2f(40,40));
    		board[i][j].setPosition(j*40,i*40);
    		if(c%2==0)
    			board[i][j].setFillColor(sf::Color::Yellow);
    		else
    			board[i][j].setFillColor(sf::Color::Blue);
    		c++;		
    	}
    	if(n%2==0)
    		c++;
    }
    
    sf::Font f;
    f.loadFromFile("OpenSans-ExtraBold.ttf");
    
    string score_str = "Score p1: " + to_string(sc); 
   string score_str2 = "Score p2: " + to_string(sc2);
   
    score.setFont(f);
    score.setString(score_str);
    score.setFillColor(sf::Color::Red);
    score.setPosition(0, 40*n);
    
    score2.setFont(f);
    score2.setString(score_str);
    score2.setFillColor(sf::Color::Red);
    score2.setPosition(200, 40*n);
    
    k = n+15;
    
    sf::Texture a;
    a.loadFromFile("apple.png");
    apples = new sf::Sprite[k]; 
    	
    arr = new int*[k];
    for(int i=0;i<k;i++)
    	arr[i] = new int[2];
    	
    for(int i=0;i<k;i++){
    	arr[i][0]= 0 ;
    	arr[i][1] = 0;
    }
    
    int index = 0;
    	
    	for(int i=0;i<k;i++){
    		apples[i].setTexture(a);
    		apples[i].setScale(0.05f,0.05f);
    		bool flag = true;
    		int xc, yc;
    		do{
    		flag = true;
    		xc = rand()%n;
    		yc = rand()%n;
    		for(int j = 0; j<index; j++){
    			if((xc == arr[j][0] && yc == arr[j][1]) || (xc==0 && yc==0))
    				flag = false;
    		}
    		}while(flag==false);
    		
    		apples[i].setPosition(xc*40 + 5,yc*40 + 5);
    		arr[index][0] = xc;
    		arr[index][1] = yc;	
    		index++;
    				
    	}
    	
    	
    	
    	

    
    sf::Texture p;
    p.loadFromFile("player.png");
    player.setTexture(p);
    player.setScale(0.02f,0.02f);
    x=5;
    y=0;
    player.setPosition(x,y);
    
    sf::Texture p2;
    p2.loadFromFile("player2.png");
    player2.setTexture(p2);
    player2.setScale(0.02f,0.02f);
    x2=5;
    y2=0;
    player.setPosition(x2,y2);
    
    
    bool flag = true;
    	
    item_count = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
                
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            	window.close();
            	
                
        }
        
      window.clear();
      if(item_count<k){      

        
        for(int i=0;i<n;i++){
    		for(int j=0;j<n;j++){
    			window.draw(board[i][j]);		
    		}	
    	}
    	window.draw(score);
    	window.draw(score2);
    	window.draw(player);
    	window.draw(player2);
    	for(int i=0;i<k;i++)
    		window.draw(apples[i]);
        
        }
        
        else{
        if(sc>sc2){
        	score_str = "Player 1 wins! \n Score: ";
        	score_str += to_string(sc);
        }
        else if(sc2>sc){
        	score_str = "Player 2 wins! \n Score: ";
        	score_str += to_string(sc2);
        	}
        else{
        	score_str = "It's a Draw! \n Score: ";
        	score_str += to_string(sc);
        }
        
        score.setString(score_str);
        score.setPosition(40*((n-5)/2), 40*((n-1)/2));
        window.draw(score);
        }
        window.display();
        
        if(flag==true){
        pthread_attr_t ta1,ta2;
	pthread_attr_init(&ta1);
	pthread_attr_init(&ta2);
	pthread_attr_setdetachstate(&ta1 ,PTHREAD_CREATE_DETACHED);
	pthread_attr_setdetachstate(&ta2 ,PTHREAD_CREATE_DETACHED);
	
	pthread_t t1, t2;
	
	pthread_create(&t1,&ta1,mplayer1,(void*) window_ptr);
	pthread_attr_destroy(&ta1);
	pthread_join(t1,NULL);
	
	pthread_create(&t2,&ta2,mplayer2,(void*) window_ptr);
	pthread_attr_destroy(&ta2);
	pthread_join(t2,NULL);
	flag = false;
	}
    
    }

    return 0;
}
