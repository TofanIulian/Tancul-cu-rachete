#include<windows.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

#define SPACEBAR 32
#define PI 3.14159265

double fluct = 1;
int fps = 10;
double viteza = 0.5;
int f = 0;

class Unit
{
private:
	int x;
	int y;
public:
	Unit(int a, int b)
	{
		x = a;
		y = b;
	}
	Unit(){}
	int getx()
	{
		return x;
	}
	int gety()
	{
		return y;
	}
	void setx(int a)
	{
		x = a;
	}
	void sety(int a)
	{
		y = a;
	}
	virtual void Draw() = 0;
};

class Tank : public Unit
{
private:
	int unghiTun;
public:
	Tank(int a, int b, int u) :Unit(a, b)
	{
		unghiTun = u;
	}
	Tank():Unit(){}
	int getUnghiTun()
	{
		return unghiTun;
	}
	void setUnghiTun(int a)
	{
		unghiTun = a;
	}
	void Draw()
	{
		glPushMatrix();
		glTranslated(getx(), gety(), 0.0);
		glColor3f(0.0, 0.0, 1.0);
		glRecti(-20, -12, 20, 12);

		glPushMatrix();
		glRotated(unghiTun, 0.0, 0.0, 1.0);
		glColor3f(1.0, 0.0, 0.0);
		glRecti(-5, 0, 5, 30);
		glPopMatrix();
		glPopMatrix();
	}
};

class Bomba : public Unit
{
private:
	int unghiBomba;
public:
	Bomba(int a, int b, int u) :Unit(a, b)
	{
		unghiBomba = u;
	}
	Bomba() :Unit() {}
	int getUnghiBomba()
	{
		return unghiBomba;
	}
	void setUnghiBomba(int a)
	{
		unghiBomba = a;
	}
	void Draw()
	{
		glPushMatrix();
		glTranslated(getx(), gety(), 0.0);
		glPushMatrix();
		glRotated(fps*viteza, 0.0, 0.0, 1.0);
		glColor3f(0.0, 1.0, 0.0);
		glRecti(-5, -5, 5, 5);
		glPopMatrix();
		glPopMatrix();
		setx(getx() + fps * cos((unghiBomba + 90) * PI / 180.0));
		sety(gety() + fps * sin((unghiBomba + 90) * PI / 180.0));
	}
};

class Racheta : public Unit
{
private:
	int unghiFlight;
public:
	Racheta(int a, int b, int u):Unit(a,b)
	{
		unghiFlight = u;
	}
	Racheta() :Unit() {}
	int getUnghiFlight()
	{
		return unghiFlight;
	}
	void setUnghiFlight(int a)
	{
		unghiFlight = a;
	}
	void Draw()
	{
		glPushMatrix();
		glTranslated(getx(), gety(), 0.0);
		glPushMatrix();
		glRotated(unghiFlight, 0.0, 0.0, 1.0);
		glColor3f(0.0, 1.0, 0.0);
		glBegin(GL_POLYGON);

		glVertex2i(0, 20);
		glVertex2i(-5, 15);
		glVertex2i(-5, 5);
		glVertex2i(-10, 0);
		glVertex2i(10, 0);
		glVertex2i(5, 5);
		glVertex2i(5, 15);

		glEnd();
		glColor3f(1.0, 0.0, 0.0);
		glPushMatrix();
		glScaled(1, fluct, 1);

		glBegin(GL_POLYGON);

		glVertex2i(-8, -0.2);
		glVertex2i(0, -20);
		glVertex2i(8, -0.2);

		glEnd();
		glPopMatrix();
		glPopMatrix();
		glPopMatrix();

		setx(getx() + fps * cos((unghiFlight + 90) * PI / 180.0));
		sety(gety() + fps * sin((unghiFlight + 90) * PI / 180.0));
	}
};

class Obiect : public Unit
{
public:
	Obiect(int a, int b):Unit(a,b){}
	Obiect() :Unit() {}
	void Draw()
	{
		glPushMatrix();
		glColor3f(0.0, 1.0, 0.0);
		glTranslated(getx(), gety(), 0.0);
		glPushMatrix();
		glRotated(fps*viteza, 0.0, 0.0, 1.0);
		glRecti(-15, -15, 15, 15);
		glPopMatrix();
		glPopMatrix();
	}
};

Tank tank(100, 100, 0);
Racheta *racheta = new Racheta[1000];
int r = 0;

Bomba *bomba = new Bomba[1000];
int b = 0;

Obiect *ob = new Obiect[1000];
int c = 0;

void die(int x)
{
	for (int i = x; i < b-1; i++)
	{
		bomba[i] = bomba[i + 1];
	}
	b--;
}

void dier(int x)
{
	for (int i = x; i < r-1; i++)
	{
		racheta[i] = racheta[i + 1];
	}
	r--;
}

void destroy(int y)
{
	for (int i = y; i < c-1; i++)
	{
		ob[i] = ob[i + 1];
	}
	c--;
}

void check()
{
	for (int x = 0; x < r; x++)
	{
		for (int y = 0; y < c; y++)
		{
			if (ob[y].getx() - 15 <= racheta[x].getx() && ob[y].getx() + 15 >= racheta[x].getx() && racheta[x].gety() >= ob[y].gety() - 15 && racheta[x].gety() <= ob[y].gety() + 15)
			{
				dier(x);
				destroy(y);
			}

		}
		if (racheta[x].getx() > 1800 || racheta[x].getx() < 0 || racheta[x].gety()>1000 || racheta[x].gety() < 0)
			dier(x);
	}

	for (int x = 0; x < b; x++)
	{
		for (int y = 0; y < c; y++)
		{
			if (ob[y].getx() - 15 <= bomba[x].getx() && ob[y].getx() + 15 >= bomba[x].getx() && bomba[x].gety() >= ob[y].gety() - 15 && bomba[x].gety() <= ob[y].gety() + 15)
			{
				die(x);
				destroy(y);
			}

		}
		if (bomba[x].getx() > 1800 || bomba[x].getx() < 0 || bomba[x].gety()>1000 || bomba[x].gety() < 0)
			die(x);
	}
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	gluOrtho2D(0.0, 1800.0, 0.0, 1000.0);
	glShadeModel(GL_FLAT);
}

void ta()
{
	tank.Draw();
}

void ro()
{

	for (int i = 0; i < r; i++)
	{
		racheta[i].Draw();
	}
	check();
}

void bo()
{
	for (int i = 0; i < b; i++) 
	{
		bomba[i].Draw();
	}
	viteza += 0.4;
	check();
}

void pe()
{
	for (int i = 0; i < c; i++)
	{
		ob[i].Draw();
	}
}

void scena(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	ta();
	ro();
	bo();
	pe();
	check();
	Sleep(16);
	glutSwapBuffers();
	glFlush();
}

void keyboard(int key, int x, int y)
{

	switch (key) {
	case GLUT_KEY_UP:
		tank.sety(tank.gety() + 5);
		break;
	case GLUT_KEY_DOWN:
		tank.sety(tank.gety() - 5);
		break;
	case GLUT_KEY_LEFT:
		tank.setx(tank.getx() - 5);
		break;
	case GLUT_KEY_RIGHT:
		tank.setx(tank.getx() + 5);
		break;
	case GLUT_KEY_PAGE_UP:
		tank.setUnghiTun(tank.getUnghiTun() + 3);
		break;
	case GLUT_KEY_PAGE_DOWN:
		tank.setUnghiTun(tank.getUnghiTun() - 3);
		break;
	case GLUT_KEY_END:
	{
		Racheta Roket(tank.getx(), tank.gety(), tank.getUnghiTun());
		racheta[r] = Roket;
		r++;
	}
	break;
	case GLUT_KEY_HOME:
	{
		Bomba Bomb(tank.getx(), tank.gety(), tank.getUnghiTun());
		bomba[b] = Bomb;
		b++;
	}
		break;
	case GLUT_KEY_F1:
		for (int i = 0; i < r; i++)
			racheta[i].setUnghiFlight(racheta[i].getUnghiFlight() + 3);
		break;
	case GLUT_KEY_F2:
		for (int i = 0; i < r; i++)
			racheta[i].setUnghiFlight(racheta[i].getUnghiFlight()-3);
		break;

	}
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1800.0, 0.0, 1000.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void miscare(void)
{
	if (fluct < 1.4 && f == 0)
	{
		fluct = fluct + 0.2;
	}
	if (fluct > 1 && f == 1)
	{
		fluct = fluct - 0.2;
	}
	if (fluct == 1.4)
		f = 1;
	else if (fluct == 1)
		f = 0;

	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
		{

			ob[c].setx(x);
			ob[c].sety(1000 - y);
			c++;
		}

		glutIdleFunc(miscare);
		break;
	default:
		break;
	}
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1800, 1000);
	glutInitWindowPosition(1, 1);
	glutCreateWindow("Tancul cu rachete");
	init();
	glutDisplayFunc(scena);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutSpecialFunc(keyboard);
	glutMainLoop();
}