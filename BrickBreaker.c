#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
#include<GL/gl.h>
#include<stdbool.h>
#include<string.h>
static GLfloat shooter[4][2]={{-0.8,-1},{-0.6,-1},{-0.6,-0.9},{-0.8,-0.9}};
GLfloat colorarr[5][3]={{0.0,0.0,0.0},{1.0,0.0,0.0},{0.0,0.0,0.0},{1.0,0.0,0.0},{0.8,0.8,0.8}};
static int flag=0;
float tx=0.0,ty=0.0,tz=0.0, s=0.001,incremental_x=0.001,incremental_y=0.001,x,y, ball_z=0.1;
int score = 0,d,k=9,hiscore = 0,i=0,j=9,check=0;
bool gameover;
char buffer[50];

typedef struct
	{
	float x1,y1,x2,y2;
	int color;
	}bricktype;
bricktype br[10][20];

void drawString (void * font, char *s, float x, float y){
     unsigned int i;
     glRasterPos2f(x, y);
     for (i = 0; i < strlen (s); i++)
          glutBitmapCharacter (font, s[i]);
}

void updateBall()
{
int w1,w2,o;
int b=(int)(x*10);
int c=(int)(y*10);
float q1=shooter[0][0];
float q2=shooter[1][0];
            if (x + incremental_x < -1)
                incremental_x = s;
            if (x + incremental_x > 1)
                incremental_x = -s;
            if (y + incremental_y < -0.9)
	{
	
	if((q1<=x&&q2>=x)||(q1>=x&&q2<=x))
                	incremental_y = s;
	else	
		gameover = true;
	}
            if (y + incremental_y > 0)
	{
	w1=10-abs(b);
	w2=10+b;
	o=9-c;	  
	  
	  if(b<0)
		{
		
		if(br[o][w1].color<=3)
			{
			incremental_y = -s;
			br[o][w1].color=4;
			score = score + 100;
			if(score > hiscore)
				  hiscore = score;
			}

		}
                else
		{
		if(br[o][w2].color<=3)
			{
			incremental_y = -s;
			br[o][w2].color=4;
			score = score + 100;
			if(score > hiscore)
				  hiscore = score;
			}	
		}	
	

	}   
		      
            x = x + incremental_x;
            y = y + incremental_y;
}

void Keys(int key,int x1,int y1)
	{
	int j;
	
		switch(key)
			{
			case GLUT_KEY_LEFT:	
			if(shooter[0][0]>=-0.9)
				{
				for(j=0;j<4;j++)
        					shooter[j][0]-=0.2;
				glutPostRedisplay();
			 	}

			break;
			case GLUT_KEY_RIGHT:
		
			if(shooter[0][0]<=0.6)
				{
				for(j=0;j<4;j++)
					shooter[j][0]+=0.2;
				glutPostRedisplay();
				}														
			break;
			}

}

void display()
	{
	int j,i,d;		
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	for(j=1;j<10;j++)
		{
		for(i=0;i<20;i++)
			{
			glColor3fv(colorarr[br[j][i].color]);
			glBegin(GL_POLYGON);
			glVertex2f(br[j][i].x1,br[j][i].y1);
			glVertex2f(br[j][i].x2,br[j][i].y1);
			glVertex2f(br[j][i].x2,br[j][i].y2);
			glVertex2f(br[j][i].x1,br[j][i].y2);
			glEnd();
			}
		}
	glClearColor(0.8,0.8,0.8,1.0);
	glPushMatrix();
	glColor3f(0,0,0);
	glTranslatef(x,y,ball_z);
	glutSolidSphere(0.03,20,20);
	glPopMatrix();
	glColor3f(1.0,0.6,0.1);
	glBegin(GL_POLYGON);
		glVertex2f(shooter[0][0],shooter[0][1]);
		glVertex2f(shooter[1][0],shooter[1][1]);
       		glVertex2f(shooter[2][0],shooter[2][1]);
       		glVertex2f(shooter[3][0],shooter[3][1]);
	glEnd();
	

	

	glColor3f(0, 0, 0);
		drawString(GLUT_BITMAP_HELVETICA_18, "Score:", -0.8, 0.95);	
		snprintf (buffer, 10, "%d",score); 
		drawString(GLUT_BITMAP_HELVETICA_18, buffer, -0.6, 0.95);

		glColor3f(0, 0, 0);
		drawString(GLUT_BITMAP_HELVETICA_18, "Hi-Score:", 0.3, 0.95);	
		snprintf (buffer,10, "%d",hiscore); 
		drawString(GLUT_BITMAP_HELVETICA_18, buffer, 0.6, 0.95);
		
		if(gameover == true)
		{
			glColor3f(0, 0, 0);
			drawString(GLUT_BITMAP_HELVETICA_18, "Game Over", -0.2,-0.2); //display Game Over on the screen
			
		}
		else
			updateBall();	

glFlush();
}
int main(int argc, char** argv)
	{
	int i,j,d;
	float temp,Temp,k1,k2;
	glutInit(&argc,argv);
	Temp=1;
	for(j=0;j<10;j++)
		{
		temp=-1;
		k1=Temp-0.1;
		k2=Temp;
		Temp=k1;
		
		for(i=0;i<20;i++)
			{
			d=(i+j)%4;
			if(d==0)
				br[j][i].color=0;				
			else if(d==1)					
				br[j][i].color=1;
			else if(d==2)
				br[j][i].color=2;	
			else
				br[j][i].color=3;
			
			br[j][i].x1=temp;
			br[j][i].y1=k1;
			br[j][i].x2=temp+0.1;
			temp=br[j][i].x2;
			br[j][i].y2=k2;
			}

		}

	glutInitWindowSize(600,600);
	glutInitWindowPosition(0,0);
	glutCreateWindow("BrickBreaker");
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutSpecialFunc(Keys);
	glutMainLoop();
	}

