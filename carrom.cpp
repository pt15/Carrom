#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <cmath>
#include <time.h>

using namespace std;

#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)

//const float BOX_SIZE = 7.0f; //The length of each side of the cube
//float _angle = 0;            //The rotation of the box


void drawScene();
void drawBall(float rad);
void drawSquare(float len);
void drawCircle(float rad);
void show_pow();
void display_score();

class coin{
	public:
		double rad;
		double x;
		double y;
		double vel_x;
		double vel_y;
		double mass;
		coin(double vx, double vy, double r,double m);
		void update_pos( double x1, double y1);
		void update_vel( double v_x, double v_y);
			
};
//coin attributes are (x_pos) (y_pos) (vel_x) (vel_y) (rad) (mass)
coin::coin(double vx, double vy, double r, double m){
	vel_x = vx;
	vel_y = vy;
	rad=r;
	mass=m;
}

void coin::update_pos( double x1, double y1){
	x = x1;
	y = y1;
}

void coin::update_vel( double v_x, double v_y){
	vel_x = v_x;
	vel_y = v_y;
}

class strike: public coin{
	public:
		double power;
		double angle;
		void reinitialise(void);
		strike(double vx, double vy, double r, double m):coin(vel_x,vel_y,rad,mass){
                        vel_x=vx;
                        vel_y=vy;
                        angle=0.0f;
                        power=0.0f;
                        rad=r;
                        x=0;
                        y=-1.30f;
			mass=m;
                }
		void shoot(void);
		void set_power(double pow);
		void set_angle(double ang);
};

void strike::reinitialise(void){
	update_pos(0.0f,-1.30f);
	update_vel(0.0f,0.0f);
	power=0.00f;
	angle=0.0f;
}

void strike::set_power(double pow){
	power=pow;
}

void strike::set_angle(double ang){
	angle=ang;
}
void strike::shoot(void){
	update_vel(power*sin(DEG2RAD(angle)), power*cos(DEG2RAD(angle)));
}
//Global Variables
coin* coins[19];
double friction=0.98;
strike striker(0.0f,0.0f,0.12f,1.75f);
//int gameflag;			//flag to check game state-> begin, play, end
class GamePlay{
	public:
		int coin_num;
		double rad;
		int points;
		GamePlay(int coins1);
                void loadCoins();	//set initial coin position for new game
		void drawBoard();
};

GamePlay::GamePlay(int coins1){
	points=30;
	coin_num=coins1;
	rad=0.075;
	for(int i=0;i<coin_num;i++){
		coins[i]= new coin(0,0,0.075,1);
	}
	drawBoard();
}

void GamePlay::drawBoard(){

	//glRotatef(-30, 1.0f, 0.0f, 0.0f);
	//carrom board
	glPushMatrix();
        glTranslatef(0.0f, 0.0f, -11.0f);
        glColor3f(0.0f, 0.0f, 0.0f);
        drawSquare(7.0f);
        glPopMatrix();
	
	glPushMatrix();
        glTranslatef(0.0f, 0.0f, -10.0f);
        glColor3f(0.4f, 0.2f, 0.2f);
        drawSquare(6.0f);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0.0f, 0.0f , -9.0f);
        glColor3f(0.5f, 0.25f, 0.15f);
        drawSquare(5.0f);
	glPopMatrix();
	

//pockets
	glColor3f(0.2,0.2,0.2);
	glPushMatrix();
	glTranslatef(1.835f,1.835f,-7.0f);
	drawBall(3*rad/2);
	glPopMatrix();
	
        glPushMatrix();
        glTranslatef(1.835f,-1.835f,-7.0f);
        drawBall(3*rad/2);
        glPopMatrix();
        
	glPushMatrix();
        glTranslatef(-1.835f,1.835f,-7.0f);
        drawBall(3*rad/2);
        glPopMatrix();
       
	glPushMatrix();
        glTranslatef(-1.835f,-1.835f,-7.0f);
        drawBall(3*rad/2);
        glPopMatrix();

//Lines
	glLineWidth(2.5);
	glColor3f(0.2, 0.2, 0.1);
//left line
	glBegin(GL_LINES);
	glVertex3f(-1.40f, -1.175f+3*rad, -7.0f);
	glVertex3f(-1.40f, 1.175f-3*rad, -7.0f);
	glEnd();

	glBegin(GL_LINES);
        glVertex3f(-1.20f, -1.175f+3*rad, -7.0f);
        glVertex3f(-1.20f, 1.175f-3*rad, -7.0f);
        glEnd();
	
	glPushMatrix();
	glTranslatef(-1.30f, -1.00f, -7.0f);
	drawBall(3*rad/2);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-1.30f, 1.00f, -7.0f);
	drawBall(3*rad/2);
	glPopMatrix();
//right line
	glBegin(GL_LINES);
	glVertex3f(1.40f, -1.175f+3*rad, -7.0f);
	glVertex3f(1.40f, 1.175f-3*rad, -7.0f);
	glEnd();

	glBegin(GL_LINES);
        glVertex3f(1.20f, -1.175f+3*rad, -7.0f);
        glVertex3f(1.20f, 1.175f-3*rad, -7.0f);
        glEnd();
	
	glPushMatrix();
	glTranslatef(1.30f, -1.00f, -7.0f);
	drawBall(3*rad/2);
	glPopMatrix();
	
	glPushMatrix();
        glTranslatef(1.30f, 1.00f, -7.0f);
        drawBall(3*rad/2);
        glPopMatrix();
//lower line
	glBegin(GL_LINES);
	glVertex3f(-1.125f+3*rad, -1.40f, -7.0f);
	glVertex3f(1.125f-3*rad, -1.40f, -7.0f);
	glEnd();

	glBegin(GL_LINES);
        glVertex3f(-1.125f+3*rad, -1.20f, -7.0f);
        glVertex3f(1.125f-3*rad, -1.20f, -7.0f);
        glEnd();

	glPushMatrix();
        glTranslatef(-0.95f, -1.30f, -7.0f);
        drawBall(3*rad/2);
        glPopMatrix();

	glPushMatrix();
        glTranslatef(0.95f, -1.30f, -7.0f);
        drawBall(3*rad/2);
        glPopMatrix();
//upper line
	glBegin(GL_LINES);
	glVertex3f( 1.125f-3*rad, 1.40f, -7.0f);
	glVertex3f( -1.125f+3*rad, 1.40f, -7.0f);
	glEnd();

	glBegin(GL_LINES);
        glVertex3f( 1.125f-3*rad, 1.20f, -7.0f);
        glVertex3f( -1.125f+3*rad, 1.20f, -7.0f);
        glEnd();

	glPushMatrix();
        glTranslatef(0.95f, 1.30f, -7.0f);
        drawBall(3*rad/2);
        glPopMatrix();

	glPushMatrix();
        glTranslatef(-0.95f, 1.30f, -7.0f);
        drawBall(3*rad/2);
        glPopMatrix();
//centre
	glPushMatrix();
	glTranslatef(-0.0f, 0.0f, -7.0f);
	glColor3f((255.0f/255.0f), (69.0f)/(255.0f), (0.0f)/(255.0f));
	glLineWidth(2.5);
	drawCircle(6*rad);
	drawCircle(5*rad);
	glColor3f(0.0f,0.0f,0.0f);
	drawCircle(7*rad);
	glPopMatrix();
}

void GamePlay::loadCoins(){
	int i,rotationAngle=0;
	//initialise queen
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -5.0f);
	glColor3f(1.0f, 0.0f, 0.1f);
	drawBall(rad);
	coins[18]->update_pos(0,0);
	glPopMatrix();
	//initialise coins
	for(i=0;i<6;i++){
		glPushMatrix();
		glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);
		glTranslatef(2.5*rad,0.0f,-5.0f);
		if(i%2 ==0)
			glColor3f(1.0f, 1.0f, 1.0f);
		else
			glColor3f(0.0f, 0.0f, 0.0f);
		coins[i]->update_pos(2.5*rad*cos(DEG2RAD(rotationAngle)),2.5*rad*sin(DEG2RAD(rotationAngle)));
		drawBall(rad);
		glPopMatrix();
		rotationAngle+=60;
	}
	rotationAngle=0;
	for(i=6;i<coin_num-1; i++) {
		glPushMatrix();
		glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);
		if( rotationAngle % 60 == 0 )
			glTranslatef(5*rad,0.0f,-5.0f);
		coins[i]->update_pos(5*rad*cos(DEG2RAD(rotationAngle)),5*rad*sin(DEG2RAD(rotationAngle)));
		if(i%2==0)
			glColor3f(1.0f, 1.0f, 1.0f);
		else
			glColor3f(0.0f, 0.0f, 0.0f);
		drawBall(rad);
		glPopMatrix();
		rotationAngle+=30;
	}
}

GamePlay game(19);
//int flag=0,queen_check=0;
void handleKeypress(unsigned char key, int x, int y) {
	switch(key){
		case 27:	//Esc to exit
			exit(0);
			break;
		case ' ': 	//SPACE to shoot or start
		/*	if(gameflag==0){
				gameflag==1;
			}
			else if(gameflag==-1){
				gameflag=1;
			}*/
			/*else */if(/*gameflag==1 &&*/ striker.vel_x == 0 && striker.vel_y == 0 && striker.y == -1.30f){
				striker.shoot();
				/*if(queen_check==1)
					queen_check=-1;
				else if(queen_check==-1){
					if(flag==1){
						coins[18]->x=0.0f;
						coins[18]->y=0.0f;
					}
					queen_check=0;
				}*/
			}
			break;
		case 'a':	//set angle anticlockwise
			if(striker.vel_x == 0 && striker.vel_y == 0 && striker.y == -1.30f){
                                if(striker.angle > -90)
					striker.angle -= 5;
                        }
                        break;
		case 'c':	//set angle clockwise
			if(striker.vel_x == 0 && striker.vel_y == 0 && striker.y == -1.30f){
                                if(striker.angle < 90)
					striker.angle += 5;
                        }
                        break;
			
		case 'r':	//r to reset the striker//Also to save my and your time :P
			striker.reinitialise();
			break;
	}
}

void handleKeypress2(int key, int x, int y) {
	if(striker.vel_x == 0 && striker.vel_y == 0 && striker.y == -1.30f){
                if (key == GLUT_KEY_LEFT){
                        if(striker.x>-0.9f)
                                striker.x-=0.07;
                }
                if(key == GLUT_KEY_RIGHT){
                        if( striker.x<0.9f)
                                striker.x+=0.07;
                }
		if(key == GLUT_KEY_UP){
			if( striker.power<0.25f)
				striker.power+=0.005f;
		}
		if(key == GLUT_KEY_DOWN){
			if(striker.power>0.0f)
				striker.power-=0.005f;
		}
        }
}
int pressflag=1;
void handleMouseclick(int button, int state, int x, int y){
	if(striker.vel_x == 0 && striker.vel_y == 0 && striker.y == -1.30f){
		if (state == GLUT_DOWN){
       			if (button == GLUT_LEFT_BUTTON){
/*	GLint v[4];
        GLdouble m[16],p[16];
        glGetDoublev(GL_MODELVIEW_MATRIX,m);
        glGetDoublev(GL_PROJECTION_MATRIX,p);
        glGetIntegerv(GL_VIEWPORT,v);
        double a,b,c;
        gluUnProject(x,y,0,m,p,v,&a,&b,&c);
        cout<< a;
        cout<<'\n';
        cout<<b;*/
				if(y<= 555 && y>= 525 && x>= (651-16+((striker.x*16)/0.12)) && x<= (651+16+((striker.x*16)/0.12))){
					pressflag=0;
					striker.power=0;
                               	 	striker.angle=0;
				}
			}
    		}
		if (state == GLUT_UP && pressflag==0){
			if(button == GLUT_LEFT_BUTTON){
				pressflag=1;
				striker.shoot();
			}
		}
		
	}
}
void handleMouseMotion(int x, int y){
	if(pressflag==0){
		double p=(sqrt( ( (x-651-((striker.x*16)/0.12)) * (x-651-((striker.x*16)/0.12)) ) + ((y-540)*(y-540))))/320;
		if(p>0.25)
			p=0.25;
		striker.power=p;
                if(y<=540)
                	striker.angle=90;
                else
                	striker.angle=(180/PI)*atan2((651-x+((striker.x*16)/0.12)),(y-540));
	}
}
void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glClearColor(0.4f, 0.4f, 0.4f, 1.0f);		//background color
}


void handleResize(int w, int h) {
	glViewport(0, 0, w, h);				//camera position and lookup
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();				//clear camera perspectives
	gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0);
}


void drawSquare(float len) {
	glBegin(GL_QUADS);
	glVertex2f(-len / 2, -len / 2);
	glVertex2f(len / 2, -len / 2);
	glVertex2f(len / 2, len / 2);
	glVertex2f(-len / 2, len / 2);
	glEnd();
}
void drawBall(float rad) {
	glBegin(GL_TRIANGLE_FAN);
	for(int i=0; i<360; i++) {
		glVertex2f(rad * cos(DEG2RAD(i)), rad * sin(DEG2RAD(i)));
	}
	glEnd();
}
void drawCircle(float rad){
	glBegin(GL_LINE_STRIP);
	for (int i=0; i<360; i++) {
		float degInRad = DEG2RAD(i);
		glVertex2f(cos(degInRad)*rad,sin(degInRad)*rad);
	}
	glEnd();
}
void score_time_display (double posx, double posy, double posz, int scorevar)
{
        int j,p,k;
	GLvoid *font_style = GLUT_BITMAP_TIMES_ROMAN_24;
	time_t rawtime;
        time(&rawtime);
        string clock=ctime(&rawtime);
	int len=clock.size();
	string note="Note!";
	string note2="1 Point deducted every 3 seconds";
	
	for(j=0;j<len;j++){
		glRasterPos3f(-2.2+(j*(0.15)),-2.4,-7);
		glutBitmapCharacter(font_style,clock[j]);
	}
	
	len=note2.length();
	double y=posy,f=0;
	for(j=0;j<len;j++){
		if(j==17){
			y -= 0.17;
			f=-17;
		}
		glColor3f(0.5,0,0.2);
                glRasterPos3f(-5+((j+f)*(0.15)),y-1,-7);
                glutBitmapCharacter(font_style,note2[j]);
        }
	len=note.length();
	for(j=0;j<len;j++){
                glColor3f(0,0,0);
                glRasterPos3f(-5+(j*(0.15)),posy-0.5,-7);
                glutBitmapCharacter(font_style,note[j]);
        }

        p = scorevar;
	j=k=0;
	string score="Your Score is";
	for(j=0;j<13;j++){
		glColor3f(0,0,0);
		glRasterPos3f(-5+(j*0.1),posy,-7);
		glutBitmapCharacter(font_style,score[j]);
	}
        while(p > 9)
	{
		k = p % 10;
		glRasterPos3f ((posx-(j*0.1)),posy, posz);   
		glutBitmapCharacter(font_style,48+k);
		j++;
		p /= 10;
	}
            glRasterPos3f ((posx-(j*0.1)), posy, posz);   
            glutBitmapCharacter(font_style,48+p);
      
}
int black=0;
void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
/*	if(gameflag==0){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        	glMatrixMode(GL_MODELVIEW);
        	glLoadIdentity();
		GLvoid *font_style = GLUT_BITMAP_TIMES_ROMAN_24;
                string begin="Press Space To Begin Game";
                for(int j=0;j<26;j++){
                        glColor3f(0,0,0);
                        glRasterPos3f(-1+(j*0.1),0,-7);
                        glutBitmapCharacter(font_style,begin[j]);
                }
	}
	else*/ if(game.points<0 || (black==9 && game.points<120) /*&& gameflag==1*/){
		GLvoid *font_style = GLUT_BITMAP_TIMES_ROMAN_24;
		string end="Game Over!";
		for(int j=0;j<10;j++){
			glColor3f(0,0,0);
			glRasterPos3f(-1+(j*0.1),0,-7);
			glutBitmapCharacter(font_style,end[j]);
		}
		string end_m="Thank you for playing! :)";
                for(int j=0;j<25;j++){
                        glColor3f(0,0,0);
                        glRasterPos3f(-2.5+(j*0.1),-2,-7);
                        glutBitmapCharacter(font_style,end_m[j]);
              }
	}
	else if(game.points>=125){
		GLvoid *font_style = GLUT_BITMAP_TIMES_ROMAN_24;
                string won="Congratulations!! You won the game :)";
                for(int x=0;x<37;x++){
                        glColor3f(0,0,0);
                        glRasterPos3f(-1+(x*0.1),0,-7);
                        glutBitmapCharacter(font_style,won[x]);
                }
                string exit="Press Esc to exit";
                for(int x=0;x<17;x++){
                        glColor3f(0,0,0);
                        glRasterPos3f(-2.5+(x*0.1),-2,-7);
                        glutBitmapCharacter(font_style,exit[x]);
              }
	}
	else /*if(gameflag==1)*/{
		game.drawBoard();
		score_time_display(-2,1.6,-7,game.points);
		//striker
		glPushMatrix();
		glTranslatef(striker.x, striker.y, -7.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		drawBall(striker.rad);
		glPopMatrix();
		//queen
		glPushMatrix();
		glTranslatef(coins[18]->x, coins[18]->y, -7.0f);
		glColor3f(1.0f, 0.0f, 0.1f);
		drawBall(coins[18]->rad);
		glPopMatrix();

		for(int i=0;i < (game.coin_num-1) ;i++){
			glPushMatrix();
			glTranslatef(coins[i]->x, coins[i]->y, -7.0f);
			if(i%2==0)
				glColor3f(1.0f,1.0f,1.0f);
			else
				glColor3f(0.0f,0.0f,0.0f);
			drawBall(coins[i]->rad);
			glPopMatrix();
		}
		if(striker.vel_x==0 && striker.vel_y==0  && striker.y==-1.30f){
			show_pow();
		}
		display_score();
	}
	glutSwapBuffers();		//send the 3d scene to the screen

}
void collisions(){
	int i,j;
	for(i=0 ; i < 19; i++){
		if((coins[i]->x + 0.075 > 1.95f && coins[i]->vel_x>0) || (coins[i]->x - 0.075 < -1.95f && coins[i]->vel_x<0)){
			
			coins[i]->vel_x *= -1;
		}
		if((coins[i]->y + 0.075 > 1.95f && coins[i]->vel_y>0) || (coins[i]->y - 0.075 < -1.95f && coins[i]->vel_y<0))
			coins[i]->vel_y *= -1;
		for(j = i+1; j<19 ; j++){
			if(sqrt(pow(coins[i]->x-coins[j]->x, 2)+pow(coins[i]->y-coins[j]->y, 2)) <= coins[i]->rad + coins[j]->rad ){
				if((coins[i]->x - coins[j]->x)*(coins[i]->vel_x - coins[j]->vel_x) + (coins[i]->y - coins[j]->y)*(coins[i]->vel_y - coins[j]->vel_y) < 0){
					double dx,dy,z,v1_proj,v2_proj,v1_par,v2_par,v1_perp,v2_perp;
					dx=coins[j]->x - coins[i]->x;
					dy=coins[j]->y - coins[i]->y;
					z=sqrt(dx*dx+dy*dy); // |z|
					//parallel velocity before collision
					v1_proj=(dx*coins[i]->vel_x + dy*coins[i]->vel_y)/z;
					v2_proj=(dx*coins[j]->vel_x + dy*coins[j]->vel_y)/z;
					//parallel velocity after collison
					v1_par=((coins[i]->mass - coins[j]->mass)*v1_proj + (2*coins[j]->mass)*v2_proj)/(coins[i]->mass + coins[j]->mass);
					v2_par=((coins[j]->mass - coins[i]->mass)*v2_proj + (2*coins[i]->mass)*v1_proj)/(coins[i]->mass + coins[j]->mass);
					v1_perp=(dy*coins[i]->vel_x - dx*coins[i]->vel_y)/z;
					v2_perp=(dy*coins[j]->vel_x - dx*coins[j]->vel_y)/z;
					coins[i]->vel_x=((v1_par*dx+v1_perp*dy)/z);
					coins[i]->vel_y=((v1_par*dy-v1_perp*dx)/z);
					coins[j]->vel_x=((v2_par*dx+v2_perp*dy)/z);
					coins[j]->vel_y=((v2_par*dy-v2_perp*dx)/z);
				}
			}
		}
		if(sqrt(pow(coins[i]->x-striker.x, 2)+pow(coins[i]->y-striker.y, 2)) <= coins[i]->rad + striker.rad ){
			if((coins[i]->x - striker.x)*(coins[i]->vel_x - striker.vel_x) + (coins[i]->y - striker.y)*(coins[i]->vel_y - striker.vel_y) < 0){
                                double z1,z2,q1,q2,q1f,q2f,q11,q22,z;
				z1=striker.x - coins[i]->x;
                                z2=striker.y - coins[i]->y;
                                z=sqrt(z1*z1+z2*z2); // |z|
                                q1=(z1*coins[i]->vel_x + z2*coins[i]->vel_y)/z;
                                q2=(z1*striker.vel_x + z2*striker.vel_y)/z;
                                q1f=((coins[i]->mass - striker.mass)*q1 + (2*striker.mass)*q2)/(coins[i]->mass + striker.mass);
                                q2f=((striker.mass - coins[i]->mass)*q2 + (2*coins[i]->mass)*q1)/(coins[i]->mass + striker.mass);
				q11=(z2*coins[i]->vel_x - z1*coins[i]->vel_y)/z;
                                q22=(z2*striker.vel_x - z1*striker.vel_y)/z;
                                coins[i]->vel_x=((q1f*z1+q11*z2)/z);
                                coins[i]->vel_y=((q1f*z2-q11*z1)/z);
                                striker.vel_x=((q2f*z1+q22*z2)/z);
                                striker.vel_y=((q2f*z2-q22*z1)/z);
                	}
		}
	}
}
int a[2],b[2],c[2],d[2],e[2],f[2],g[2];

void decode(int num,int color){
	int x,y,i;
	if(color==1){
		x=1;
		y=0;
		i=0;
	}
	else{
		x=0;
		y=1;
		i=1;
	}

	switch(num){
		case 0:
			a[i]=b[i]=c[i]=d[i]=e[i]=f[i]=x;
			g[i]=y;
			break;
                case 1:
			a[i]=b[i]=x;
			c[i]=d[i]=e[i]=f[i]=g[i]=y;
			break;
                case 2:
			b[i]=c[i]=y;
			a[i]=d[i]=e[i]=f[i]=g[i]=x;
			break;
                case 3:
			c[i]=d[i]=y;
			a[i]=b[i]=e[i]=f[i]=g[i]=x;
			break;
                case 4:
			d[i]=e[i]=f[i]=y;
			a[i]=b[i]=c[i]=g[i]=x;
			break;
                case 5:
			a[i]=d[i]=y;
			b[i]=c[i]=e[i]=f[i]=g[i]=x;
			break;
                case 6:
			a[i]=y;
			b[i]=c[i]=d[i]=e[i]=f[i]=g[i]=x;
			break;
		case 7:
			a[i]=b[i]=e[i]=x;
			c[i]=d[i]=f[i]=g[i]=y;
			break;
		case 8:
			a[i]=b[i]=c[i]=d[i]=e[i]=f[i]=g[i]=x;
			break;
		case 9:
			d[i]=y;
			a[i]=b[i]=c[i]=e[i]=f[i]=g[i]=x;
			break;
	}
}
void pocket_points(void){
	static int w=0,b=0;
	for(int i=0;i<19;i++){
		if(((coins[i]->x >= 1.835-0.113) || (coins[i]->x <= -1.835+0.113)) && ((coins[i]->y >= 1.835-0.113) || (coins[i]->y <= -1.835+0.113) ) ){
			coins[i]->vel_x=0;
			coins[i]->vel_y=0;
			if(i == 18){
				coins[i]->x= 3.8f;
				coins[i]->y= 1.65f;
				game.points += 50;
				//flag=1;
				//queen_check=1;
			}
			if(i%2 == 0 && i != 18){
				coins[i]->x = 2.80f;
				coins[i]->y= 1.65 - (2.5*w*(coins[i]->rad));
				w++;
				game.points -=5;
				decode(w,1);
			}
			if(i%2 !=0){
				coins[i]->x= 3.3f;
				coins[i]->y = 1.65f - (2.5*b*(coins[i]->rad));
				b++;
				black=b;
				game.points += 10;
				/*if(flag==1){
					if(queen_check==-1)
						game.points += 0;
					flag=0;
				}*/
				decode(b,0);
			}
		}
	}
	if(((striker.x >= 1.835-0.113) || (striker.x <= -1.835+0.113)) && ((striker.y >= 1.835-0.113) || (striker.y <= -1.835+0.113) ) ){
		striker.reinitialise();
	}
}

void display_score(void){
/*	glPushMatrix();
	string menu = "Hello!";
  	glColor3f(0.0f, 0.0f, 0.0f);
    	glTranslatef(3.0f,0.0f,-7.0f);
    	int len = menu.length();
    	for (int i = 0; i < len; i++) {
        	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, menu[i]);
    	}
	glPopMatrix();*/

	glPushMatrix();
	glColor3f(0,0,0);
	glTranslatef(2.8f,2.0f,-7.0f);
	drawSquare(0.5f);
	glPopMatrix();
	
        glBegin(GL_LINES);
        glColor3f(b[0],b[0],b[0]);
	glVertex3f(3.52-0.5,1.78,-7.0f);
        glVertex3f(3.52-0.5,1.99,-7.0f);
        glEnd();
        glBegin(GL_LINES);
        glColor3f(a[0],a[0],a[0]);
	glVertex3f(3.52-0.5,2.01,-7.0f);
        glVertex3f(3.52-0.5,2.22,-7.0f);
        glEnd();
        glBegin(GL_LINES);
        glColor3f(c[0],c[0],c[0]);
	glVertex3f(3.08-0.5,2.01,-7.0f);
        glVertex3f(3.08-0.5,2.22,-7.0f);
        glEnd();
        glBegin(GL_LINES);
        glColor3f(d[0],d[0],d[0]);
	glVertex3f(3.08-0.5,1.78,-7.0f);
        glVertex3f(3.08-0.5,1.99,-7.0f);
        glEnd();
        glBegin(GL_LINES);
        glColor3f(f[0],f[0],f[0]);
	glVertex3f(3.11-0.5,1.78,-7.0f);
        glVertex3f(3.49-0.5,1.78,-7.0f);
        glEnd();
        glBegin(GL_LINES);
	glColor3f(e[0],e[0],e[0]);
        glVertex3f(3.11-0.5,2.22,-7.0f);
        glVertex3f(3.49-0.5,2.22,-7.0f);
        glEnd();
        glBegin(GL_LINES);
	glColor3f(g[0],g[0],g[0]);
        glVertex3f(3.11-0.5,2.0,-7.0f);
        glVertex3f(3.49-0.5,2.0,-7.0f);
        glEnd();	
	
	glPushMatrix();
        glColor3f(1,1,1);
        glTranslatef(3.3f,2.0f,-7.0f);
        drawSquare(0.5f);
	glPopMatrix();
	
	glBegin(GL_LINES);
	glColor3f(b[1],b[1],b[1]);
        glVertex3f(3.52,1.78,-7.0f);
        glVertex3f(3.52,1.99,-7.0f);
        glEnd();
	glBegin(GL_LINES);
	glColor3f(a[1],a[1],a[1]);
        glVertex3f(3.52,2.01,-7.0f);
        glVertex3f(3.52,2.22,-7.0f);
        glEnd();
	glBegin(GL_LINES);
	glColor3f(c[1],c[1],c[1]);
        glVertex3f(3.08,2.01,-7.0f);
        glVertex3f(3.08,2.22,-7.0f);
        glEnd();
	glBegin(GL_LINES);
	glColor3f(d[1],d[1],d[1]);
        glVertex3f(3.08,1.78,-7.0f);
        glVertex3f(3.08,1.99,-7.0f);
        glEnd();
	glBegin(GL_LINES);
	glColor3f(f[1],f[1],f[1]);
        glVertex3f(3.11,1.78,-7.0f);
        glVertex3f(3.49,1.78,-7.0f);
        glEnd();
	glBegin(GL_LINES);
	glColor3f(e[1],e[1],e[1]);
        glVertex3f(3.11,2.22,-7.0f);
        glVertex3f(3.49,2.22,-7.0f);
        glEnd();
	glBegin(GL_LINES);
	glColor3f(g[1],g[1],g[1]);
        glVertex3f(3.11,2.0,-7.0f);
        glVertex3f(3.49,2.0,-7.0f);
        glEnd();

}
void show_pow(void){
	double y=cos(DEG2RAD(striker.angle));
	double x=sin(DEG2RAD(striker.angle));
	glPushMatrix();
	glColor3f(0,0,0);
	glTranslatef(striker.x, striker.y, -7.0f);
	glBegin(GL_LINES);
	glVertex3f(striker.rad*x,striker.rad*y,0);
	glVertex3f((striker.rad*x)+(striker.power*x*2),(striker.rad*y)+(striker.power*y*2),0);
	glEnd();
	glPopMatrix();
}
void update(int value){
	int i,flag=0;
	collisions();
	pocket_points();
	if((striker.x + striker.rad > 1.95f && striker.vel_x>0) || (striker.x - striker.rad < -1.95f && striker.vel_x<0))
        	striker.vel_x *= -1;
    	if((striker.y + striker.rad > 1.95f && striker.vel_y>0) || (striker.y - striker.rad < -1.95f && striker.vel_y<0))
        	striker.vel_y *= -1;
        striker.x+=striker.vel_x;
        striker.y+=striker.vel_y;
	striker.vel_x*=friction;
	striker.vel_y*=friction;
	if((striker.vel_x*striker.vel_x)<0.000000005 && (striker.vel_y*striker.vel_y)<0.000000005){
		striker.vel_x=0;
                striker.vel_y=0;
	}
	for(i=0; i<19;i++){
		coins[i]->x += coins[i]->vel_x;
        	coins[i]->y += coins[i]->vel_y;
        	coins[i]->vel_x*=friction;
        	coins[i]->vel_y*=friction;
        	if((coins[i]->vel_x*coins[i]->vel_x)<0.000000005 && (coins[i]->vel_y*coins[i]->vel_y)<0.000000005){
                	coins[i]->vel_x=0;
                	coins[i]->vel_y=0;
        	}
	}
	for(i=0;i<19;i++){
		if(coins[i]->vel_x!=0 || coins[i]->vel_y!=0){
			flag=1;
		}
	}
	if(flag==0){
		if(striker.vel_x==0 && striker.vel_y==0  && striker.y!=-1.30f)
			striker.reinitialise();
	}
	else
		flag=0;
	//i=glutGet(GLUT_ELAPSED_TIME);	
	glutTimerFunc(/*glutGet(GLUT_ELAPSED_TIME)-i*/5,update,0);
}
void deduct(int value){
	if(striker.vel_x==0 && striker.vel_y==0 && striker.y==-1.30f){
		game.points -= 1;
		glutTimerFunc(3000, deduct, 0);
	}
	else
		glutTimerFunc(10, deduct, 0);
}
int main(int argc, char** argv) {
	//glutInitWindowSize(1000, 1000);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
//	gameflag=1;
  	int w = glutGet(GLUT_SCREEN_WIDTH);
 	int h = glutGet(GLUT_SCREEN_HEIGHT);
	int windowWidth = w;
 	int windowHeight = h;
	glutInitWindowSize(windowWidth, windowHeight);
 	glutInitWindowPosition((w - windowWidth) / 2, (h - windowHeight) / 2);
	glutCreateWindow("Carrom");  // Setup the window
	initRendering();
	// Register callbacks
	a[0]=1;b[0]=1;c[0]=1;d[0]=1;e[0]=1;f[0]=1;g[0]=0;a[1]=0;b[1]=0;c[1]=0;d[1]=0;e[1]=0;f[1]=0;g[1]=1;
	glutDisplayFunc(drawScene);
	game.loadCoins();
	glutIdleFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutSpecialFunc(handleKeypress2);
	glutMouseFunc(handleMouseclick);
	glutReshapeFunc(handleResize);
	glutTimerFunc(5, update, 0);
	glutTimerFunc(5000, deduct, 0);
	glutMotionFunc(handleMouseMotion);
	glutMainLoop();
	return 0;
}
