// snake and ladder.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

#include<dos.h>
#include<stdio.h>
#include<conio.h>
#include<ctype.h>
#include<math.h>
#include<stdlib.h>
#include<stdarg.h>
#include<graphics.h>

void thnk(int*, int, int);
void ext();
int face();
void new();
union REGS i, o;
char na[7][9];
struct palettetype pal;
void far *pl[7];
int nopl;
/* This funtion is for initialising Mouse */
int initmouse()
{
	i.x.ax = 0;
	int86(0x33, &i, &o);
	return(o.x.ax);
}

/* This funtion is for shows Mouse pointer on screen */
void showmptr()
{
	i.x.ax = 1;
	int86(0x33, &i, &o);
}

/* This is the funtion for hiding the Mouse pointer */
void hidemptr()
{
	i.x.ax = 2;
	int86(0x33, &i, &o);
}

/* This is the funtion for Restricting the Mouse pointer on the screen */
void resmptr(int x1, int y1, int x2, int y2)
{
	i.x.ax = 7;
	i.x.cx = x1;
	i.x.dx = x2;
	int86(0x33, &i, &o);
	i.x.ax = 8;
	i.x.cx = y1;
	i.x.dx = y2;
	int86(0x33, &i, &o);
}

/* This funtion is for getting Mouse coordinate on the screen at that
   instance of time */
void getmpos(int *but, int*x, int*y)
{
	i.x.ax = 3;
	int86(0x33, &i, &o);
	*but = o.x.bx;
	*x = o.x.cx;
	*y = o.x.dx;
}

/* This is the funtion for drawing a four vertices color filled
  polynomial on the screen at the given coordinates */
void rect(int x1, int y1, int x2, int y2, int c)
{
	int x, y, l, b;
	int poly[10];
	x = (x2 + x1) / 2; y = (y2 + y1) / 2; l = x2 - x1; b = y2 - y1;
	poly[0] = x - (l / 2); poly[1] = y - (b / 2); poly[2] = x + (l / 2); poly[3] = y - (b / 2);
	poly[4] = x + (l / 2); poly[5] = y + (b / 2); poly[6] = x - (l / 2); poly[7] = y + (b / 2);
	poly[8] = poly[0]; poly[9] = poly[1];
	setfillstyle(1, c);
	fillpoly(5, poly);
}

/* This is the funtion for Printing the text charecters and variable
   values dynamically */

void gprintf(int *x, int *y, char *fmt, ...)
{
	va_list ptr;
	char str[100];
	hidemptr();
	va_start(ptr, fmt);
	vsprintf(str, fmt, ptr);
	outtextxy(*x, *y, str);
	*y = *y + textheight("H") + 2;
	va_end(ptr);
	showmptr();
}

/*  This is the funtion for inputing the the playes names */

void names(int r)
{
	char c;
	int a, i, x, y;
	hidemptr();
	for (i = 1; i <= r; i++)
	{
		rect(1, 1, 640, 480, 15);
		setcolor(4);
		settextstyle(1, 0, 2);
		x = 100; y = 100;
		gprintf(&x, &y, "  ENTER PLAYER %d NAME   :", i);
		a = 0;
		do
		{
			c = getch();
			if (c == 13)
			{
				if (a == 0)
					continue;
				else
					break;
			}
			else if (c == 8 && a > 0)
				na[i][--a] = 0;
			if (c != 8)
			{
				na[i][a] = c;
				a++;
				na[i][a] = 0;
			}
			sound(4000);
			delay(20);
			setcolor(15);
			rect(400, 100, 600, 250, 15);
			settextstyle(3, 0, 2);
			setcolor(3);
			outtextxy(400, 100, na[i]);
			nosound();
		} while (a < 8);
		na[i][0] = toupper(na[i][0]);
	}
	showmptr();
}

/* This is the funtion for turning Die on screen when player want */

void turn(int x, int y)
{
	int i, j, n;
	int poly[10];
	char st[2];
	poly[0] = x - 33; poly[1] = y; poly[2] = x; poly[3] = y + 33; poly[4] = x + 33;
	poly[5] = y; poly[6] = x; poly[7] = y - 33;
	poly[8] = poly[0]; poly[9] = poly[1];
	for (i = 0; i < 10; i++)
	{
		setcolor(6);
		rectangle(x - 23, y - 23, x + 23, y + 23);
		setfillstyle(1, 15);
		floodfill(x, y, 6);
		n = random(6);
		itoa(n + 1, st, 10);
		settextstyle(0, 0, 0);
		outtextxy(x, y, st);
		sound(5000);
		delay(100);
		nosound();
		setcolor(0);
		settextstyle(0, 0, 0);
		outtextxy(x, y, st);
		setfillstyle(1, 0);
		floodfill(x, y, 6);
		rectangle(x - 23, y - 23, x + 23, y + 23);
		setcolor(6);
		setfillstyle(1, 15);
		fillpoly(5, poly);
		n = random(6);
		itoa(n + 1, st, 10);
		settextstyle(0, 1, 0);
		outtextxy(x, y, st);
		sound(4000);
		delay(100);
		nosound();
		setcolor(0);
		setfillstyle(1, 0);
		fillpoly(5, poly);
		settextstyle(0, 1, 0);
		outtextxy(x, y, st);
	}
}

/* This is the funtion for design of cone in starting Banner */

void vsnake(int x1, int y1, int x, int y)
{
	setcolor(4);
	setfillstyle(9, 15);
	fillellipse(x1, y1, 10, 5);
	line(x1 - 10, y1 + 3, x, y);
	line(x1 + 10, y1 + 3, x, y);
	floodfill((x1 + x) / 2, (y1 + y) / 2, 4);
	setfillstyle(8, 15);
	line(x1 - 10, y1 + 3, x, y);
	line(x1 + 10, y1 + 3, x, y);
	floodfill((x1 + x) / 2, (y1 + y) / 2, 4);
}

/* This is the funtion for creating Ladder by using two coordinates */

void ladder(int x1, int y1, int x, int y)
{
	int t, i, sx1, sx2, sy1, sy2, m, n;
	setcolor(12);
	line(x1 - 6, y1, x - 6, y);
	line(x1 + 6, y1, x + 6, y);
	line(x1 - 7, y1, x - 7, y);
	line(x1 + 7, y1, x + 7, y);
	line(x1 - 8, y1, x - 8, y);
	line(x1 + 8, y1, x + 8, y);
	t = ((x - x1)*(x - x1)) + ((y - y1)*(y - y1));
	if (t < 0)
		t = -t;
	t = sqrt(t);
	t /= 20;
	for (m = 0, n = t; m <= t; m++, n--)
	{
		sx1 = ((m*(x - 6)) + (n*(x1 - 6))) / (m + n);
		sx2 = ((m*(x + 6)) + (n*(x1 + 6))) / (m + n);
		sy1 = ((m*y) + (n*y1)) / (m + n);
		sy2 = ((m*y) + (n*y1)) / (m + n);
		line(sx1, sy1, sx2, sy2);
		line(sx1, sy1 + 1, sx2, sy2 + 1);
	}
}

/* This is the funtion for getting original coordinates of
	the center of the perticular cell given as one cell number
	on the board */

void pix(int i, int *x, int *y)
{
	if (i % 10 == 0 || i % 10 == 1)
	{
		if ((i / 10) % 2 == 0)
		{
			*x = 30;
			if (i % 10 == 0)
				*y = 440 - (((i / 10) - 1) * 40);
			else
				*y = 440 - (((i / 10)) * 40);
		}
		else
		{
			*x = 480;
			if (i % 10 == 0)
				*y = 440 - (((i / 10) - 1) * 40);
			else
				*y = 440 - ((i / 10) * 40);
		}
	}
	else
	{
		if ((i / 10) % 2 == 0)
		{
			*y = 440 - (((i / 10)) * 40);
			*x = 30 + (((i % 10) - 1) * 50);
		}
		else
		{
			*y = 440 - (((i / 10)) * 40);
			*x = 480 - (((i % 10) - 1) * 50);
		}
	}
}

/* This funtion for drawing ladder on board basing on two cell numbers */

void drlad(int i, int j)
{
	int x1, x2, y1, y2;
	pix(i, &x1, &y1);
	pix(j, &x2, &y2);
	ladder(x1, y1, x2, y2);
}

/* This is the funtion for drawing game borad on the screen by using one
	file that contains the total image of the board ,but that is not
	original  image file, it is a data file ".Dat" type, file contains
	information  about the image of that file.it is user made file. */

void board()
{
	int u1, u2;
	FILE *f;
	f = fopen("bor.dat", "r");
	if (f == NULL)
	{
		outtextxy(100, 200, "Requried file (bor.dat) missing...Press any key to Exit ");
		getch();
		ext();
	}
	hidemptr();
	for (u1 = 5; u1 < 505; u1++)
		for (u2 = 60; u2 < 460; u2++)
			putpixel(u1, u2, getc(f));
	fclose(f);
	showmptr();
}
/* This is the funtion for placing or repositioning the corrrect
position of players coin after player throws die */

void pos(int *a, int pr, int pp)
{
	int i = pp, x, y, y1, x1, cd = 1, dl = 50, frq = 1500;
	hidemptr();
	settextstyle(0, 0, 2);
	if (pr < a[pp])
	{
		if ((a[pp] - pr) > 6)
			cd = 4;
	}
	else
	{
		frq = 3000;
		cd = 2;
		dl = 200;
	}
	if (pr != 0)
	{
		pix(pr, &x, &y);
		if (i == 0)
		{
			x1 = x; y1 = y;
		}
		else if (i == 1)
		{
			x1 = x - 18; y1 = y - 13;
		}
		else if (i == 2)
		{
			x1 = x - 18; y1 = y + 13;
		}
		else if (i == 3)
		{
			x1 = x + 18; y1 = y - 13;
		}
		else if (i == 4)
		{
			x1 = x + 18; y1 = y + 13;
		}
		else if (i == 5)
		{
			x1 = x; y1 = y - 13;
		}
		else if (i == 6)
		{
			x1 = x; y1 = y + 13;
		}
		putimage(x1 - 6, y1 - 6, pl[pp], 0);
	}
	pix(a[i], &x, &y);
	if (i == 0)
	{
		x1 = x; y1 = y;
	}
	else if (i == 1)
	{
		x1 = x - 18; y1 = y - 13;
	}
	else if (i == 2)
	{
		x1 = x - 18; y1 = y + 13;
	}
	else if (i == 3)
	{
		x1 = x + 18; y1 = y - 13;
	}
	else if (i == 4)
	{
		x1 = x + 18; y1 = y + 13;
	}
	else if (i == 5)
	{
		x1 = x; y1 = y - 13;
	}
	else if (i == 6)
	{
		x1 = x; y1 = y + 13;
	}
	getimage(x1 - 6, y1 - 6, x1 + 6, y1 + 6, pl[pp]);
	if (pp != 0)
	{
		setcolor(i);
		setfillstyle(1, i);
		fillellipse(x1, y1, 6, 6);
		do
		{
			setcolor(0);
			circle(x1, y1, 2);
			sound(frq);
			delay(dl);
			nosound();
			setcolor(15);
			circle(x1, y1, 3);
			delay(dl);
			sound(frq + 500);
			setcolor(15);
			circle(x1, y1, 2);
			delay(dl);
			nosound();
			setcolor(0);
			circle(x1, y1, 3);
			delay(dl);
			sound(frq + 1000);
			delay(dl);
			nosound();
			cd--;
		} while (cd > 0);
	}
	else
	{
		setcolor(0);
		setfillstyle(1, 0);
		fillellipse(x1, y1, 6, 6);
		do
		{
			setcolor(0);
			rectangle(x1 - 2, y1 - 2, x1 + 2, y1 + 2);
			sound(frq);
			delay(dl);
			setcolor(0);
			rectangle(x1 - 3, y1 - 3, x1 + 3, y1 + 3);
			nosound();
			delay(dl);
			sound(frq + 500);
			setcolor(15);
			rectangle(x1 - 2, y1 - 2, x1 + 2, y1 + 2);
			delay(dl);
			nosound();
			setcolor(14);
			rectangle(x1 - 3, y1 - 3, x1 + 3, y1 + 3);
			delay(dl);
			sound(frq + 1000);
			delay(dl);
			nosound();
			cd--;
		} while (cd > 0);
	}
	showmptr();
}

/* This is the funtion for creating a Die */
void die(int i, int j, int n, int c)
{
	int t, c1;
	if (c == 0) { t = 0; c1 = 0; }
	else { t = 6; c1 = 15; }
	setcolor(t);
	setfillstyle(1, c1);
	bar3d(i - 21, j - 23, i + 21, j + 23, 11, 1);
	floodfill(i, j, t);
	floodfill(i + 3, j - 24, t);
	floodfill(i + 23, j, t);
	settextstyle(0, 0, 0);
	if (n <= 4)
	{
		setcolor(0);
		gprintf(&i, &j, "%d", n);
		setcolor(t);
		i += 23; j -= 15;
		if (n == 4)n = 0;
		gprintf(&i, &j, "%d", n + 1);
		i -= 19; j -= 34;
		outtextxy(i, j, "5");
	}
	else
	{
		setcolor(0);
		gprintf(&i, &j, "%d", n);
		setcolor(t);
		i += 23; j -= 15;
		gprintf(&i, &j, "%d", n - 3);
		i -= 19; j -= 34;
		gprintf(&i, &j, "%d", n - 2);
	}
}

/* this is the funtion to change the foreground color and background
color of the option bar, when Mouse placed in it  */

void title(int x1, int y1, int x2, int y2, int *b, int *x, int *y, int *px, int *py, int *r, char *s)
{
	if ((*x) > x1 && (*x) < x2 && (*y) > y1 && (*y) < y2)
	{
		if (((*b) & 1) == 1)
		{
			if (y1 == 275)
				*r = (x1 / 200) + 1;
			else if (y1 == 325)
				*r = (x1 / 200) + 4;
			else if (y1 == 40)
			{
				if (x1 == 100)
					*r = 10;
				else
					*r = 11;
			}
			else if (y1 == 10)
				*r = 1;
			else if ((x1 == 425) && (y1 == 100))
				*r = 15;
			else if ((x1 == 450) && (y1 == 200))
				*r = 25;
		}
		if (!((*px) > x1 && (*px) < x2 && (*py) > y1 && (*py) < y2))
		{
			hidemptr();
			rect(x1, y1, x2, y2, 4);
			setcolor(15);
			settextstyle(3, 0, 2);
			outtextxy(x1 + 5, y1, s);
			showmptr();
		}
	}
	else
	{
		if ((*px) > x1 && (*px) < x2 && (*py) > y1 && (*py) < y2)
		{
			hidemptr();
			setcolor(4);
			rect(x1, y1, x2, y2, 15);
			settextstyle(1, 0, 2);
			outtextxy(x1 + 5, y1, s);
			showmptr();
		}
	}
}

/* This is funtion for displaying the help when user wants what
 exactly he has to do for playing this game */

int help()
{
	int px, py, x, y, b, r = 0;
	hidemptr();
	rect(1, 1, 640, 480, 15);
	setcolor(4);
	settextstyle(1, 0, 2);
	rect(475, 10, 540, 40, 15);
	outtextxy(480, 10, "BACK");
	setcolor(1);
	settextstyle(8, 0, 2);
	outtextxy(230, 10, "HELP INDEX");
	outtextxy(230, 30, "~~~~~~~~~");
	setcolor(0);
	settextstyle(2, 0, 5);
	outtextxy(10, 50, "=> Welcome to our game ,");
	outtextxy(40, 70, " This is totally mouse oriented game .");
	setcolor(4);
	outtextxy(40, 90, " Key board work's only at inputing player names in other case it will n't work.");
	setcolor(0);
	outtextxy(40, 110, " Minimum two players and maximum seven players are to be played .");
	outtextxy(40, 130, " Computer must be the one of the player .");
	outtextxy(40, 150, " Frist select number of players excluding computer .");
	setcolor(4);
	outtextxy(40, 170, " For every time u must use mouse left click button only  .");
	setcolor(0);
	outtextxy(40, 190, " After selecting, u enter into game .");
	outtextxy(40, 210, " Every player starts at zero and he must reach destination at hundred by ");
	outtextxy(10, 230, " tossing dice .");
	outtextxy(40, 250, " For tossing, click on die and wait few seconds for result .");
	outtextxy(40, 270, " If player reach bottem of ladder then he automatically he dragged to top of ");
	outtextxy(10, 290, "the ladder and get bonus chance,If he reaches head of the snake then he dragged ");
	outtextxy(10, 310, "to tail of snake .");
	outtextxy(40, 330, " The player who reaches frist destination exactly,then he win the game and he ");
	outtextxy(10, 350, "left out of game then remaining players are played while one player is remaining");
	outtextxy(10, 370, "at game . Then after computer sets ranking to them by fast reaching destination");
	setcolor(2);
	settextstyle(2, 0, 6);
	outtextxy(250, 400, "Thank you ");
	outtextxy(300, 430, " -ur's Srikanth varma");
	showmptr();
	getmpos(&b, &x, &y);
	do
	{
		px = x; py = y;
		getmpos(&b, &x, &y);
		title(475, 10, 540, 40, &b, &x, &y, &px, &py, &r, "BACK");
		if (r != 0)
			break;
	} while (1);
	return face();
}
/* This funtion for getting the no. of players that users want to play */
int face()
{
	int px, py, x, y, b, r = 0, i;
	setcolor(1);
	hidemptr();
	cleardevice();
	rectangle(5, 5, 625, 465);
	rectangle(0, 0, 630, 470);
	rect(10, 10, 620, 460, 10);
	setcolor(0);
	settextstyle(5, 0, 2);
	outtextxy(380, 350, "Design'd by");
	setcolor(1);
	settextstyle(1, 0, 1);
	outtextxy(400, 380, "M.V.Srikanth Varma");
	outtextxy(400, 400, "II MCA");
	outtextxy(400, 420, "Dr.L.Bullayya.PG.College");
	setcolor(13);
	settextstyle(3, 0, 2);
	outtextxy(20, 400, "MSrikanthvarma@Yahoo.Co.in");
	setcolor(0);
	settextstyle(4, 0, 6);
	for (i = 0; i < 3; i++)
	{
		outtextxy(19 + i, 80, "SNAKES  ");
		outtextxy(359 + i, 80, "LADDERS");
	}
	vsnake(350, 40, 230, 200);
	vsnake(250, 40, 370, 200);
	floodfill(250, 50, 4);
	ladder(300, 20, 300, 200);
	rect(30, 275, 180, 300, 15);
	rect(240, 275, 390, 300, 15);
	rect(100, 40, 160, 65, 15);
	rect(450, 40, 510, 65, 15);
	rect(450, 275, 600, 300, 15);
	rect(30, 325, 180, 350, 15);
	rect(240, 325, 390, 350, 15);
	rect(450, 325, 600, 350, 15);
	setcolor(4);
	settextstyle(1, 0, 2);
	outtextxy(35, 275, "ONE PLAYER");
	outtextxy(245, 275, "TWO PLAYER");
	outtextxy(105, 40, "HELP");
	outtextxy(455, 40, "EXIT");
	outtextxy(455, 275, "THREE PLAYER");
	outtextxy(35, 325, "FOUR PLAYER");
	outtextxy(245, 325, "FIVE PLAYER");
	outtextxy(455, 325, "SIX PLAYER");
	showmptr();
	getmpos(&b, &x, &y);
	do
	{
		px = x; py = y;
		getmpos(&b, &x, &y);
		title(30, 275, 180, 300, &b, &x, &y, &px, &py, &r, "ONE PLAYER");
		if (r != 0)
			break;
		title(240, 275, 390, 300, &b, &x, &y, &px, &py, &r, "TWO PLAYER");
		if (r != 0)
			break;
		title(100, 40, 160, 65, &b, &x, &y, &px, &py, &r, "HELP");
		if (r != 0)
			break;
		title(450, 40, 510, 65, &b, &x, &y, &px, &py, &r, "EXIT");
		if (r != 0)
			break;
		title(450, 275, 600, 300, &b, &x, &y, &px, &py, &r, "THREE PLAYER");
		if (r != 0)
			break;
		title(30, 325, 180, 350, &b, &x, &y, &px, &py, &r, "FOUR PLAYER");
		if (r != 0)
			break;
		title(240, 325, 390, 350, &b, &x, &y, &px, &py, &r, "FIVE PLAYER");
		if (r != 0)
			break;
		title(450, 325, 600, 350, &b, &x, &y, &px, &py, &r, "SIX PLAYER");
		if (r != 0)
			break;
	} while (1);
	if ((r != 10) && (r != 11))
		return r;
	else if (r == 11)
	{
		closegraph();
		exit(0);
	}
	else if (r == 10)
		return help();
	return r;
}

/* this funtion for clearing messages every time besides the board */
void outlook(int n)
{
	int i, j;
	rect(507, 1, 640, 480, 0);
	rect(510, 70, 640, 70 + ((n + 2) * 25), 15);
	setcolor(0);
	rectangle(507, 1, 640, 460);
	rect(5, 1, 505, 60, 0);
	die(550, 360, 4, 1);
}
/* This funtion is for getting a random number generation on the die
   when it is turning  */
int toss(int x)
{
	int i, j, b, n, k;
	do
	{
		getmpos(&b, &i, &j);
		ext();
		if ((((b & 1) == 1) && (i > 525 && i < 580 && j>325 && j < 385)) || (x == 0))
		{
			hidemptr();
			die(550, 360, n + 1, 0);
			turn(550, 360);
			randomize();
			k = 200 + random(500);
			n = random(k);
			n = n % 6;
			die(550, 360, n + 1, 1);
			showmptr();
			return n + 1;
		}
	} while (1);
}

/* This is the funtion that sets the position of coin when user passes
	through the ladders or snakes */
void mov(int *a, int *y)
{
	switch (*a)
	{
	case 5:
		*a = 26;
		*y = 1;
		break;
	case 13:
		*a = 35;
		*y = 1;
		break;
	case 22:
		*a = 38;
		*y = 1;
		break;
	case 28:
		*a = 53;
		*y = 1;
		break;
	case 36:
		*a = 57;
		*y = 1;
		break;
	case 40:
		*a = 79;
		*y = 1;
		break;
	case 43:
		*a = 77;
		*y = 1;
		break;
	case 50:
		*a = 91;
		*y = 1;
		break;
	case 54:
		*a = 88;
		*y = 1;
		break;
	case 61:
		*a = 99;
		*y = 1;
		break;
	case 62:
		*a = 96;
		*y = 1;
		break;
	case 17:
		*a = 3;
		*y = 2;
		break;
	case 21:
		*a = 2;
		*y = 2;
		break;
	case 25:
		*a = 16;
		*y = 2;
		break;
	case 32:
		*a = 9;
		*y = 2;
		break;
	case 52:
		*a = 11;
		*y = 2;
		break;
	case 68:
		*a = 19;
		*y = 2;
		break;
	case 59:
		*a = 18;
		*y = 2;
		break;
	case 89:
		*a = 51;
		*y = 2;
		break;
	case 83:
		*a = 22;
		*y = 2;
		break;
	case 94:
		*a = 37;
		*y = 2;
		break;
	case 98:
		*a = 28;
		*y = 2;
		break;
	default:
		*y = 0;
		break;
	}
}

/* This is the funtion to Quit from the game when user clicks on exit bar*/

void ext()
{
	int x, y, b;
	getmpos(&b, &x, &y);
	getmpos(&b, &x, &y);
	if (((b & 1) == 1) && (x > 540 && x < 595 && y>10 && y < 30))
	{
		thnk(&b, 6, 0);
		for (x = 0; x < 6; x++)
			farfree(pl[x]);
		closegraph();
	}
}

/* This is the funtion to display the positions of all palyer coins on
	the screen,it displays on the right side of the game board */
void score(int *a, int n, int c)
{
	int i, j, f, k;
	settextstyle(7, 0, 1);
	setcolor(12);
	c++;
	hidemptr();
	outtextxy(520, 40, "POSITIONS");
	settextstyle(0, 0, 2);
	for (k = 0; k <= n; k++)
	{
		if (k == 0)
			setcolor(0);
		else
			setcolor(k);
		setfillstyle(1, k);
		fillellipse(519, 89 + (27 * k), 6, 6);
		if (k == 0)
		{
			setcolor(15);
			rectangle(517, 87 + (27 * k), 521, 91 + (27 * k));
			setcolor(14);
			rectangle(516, 86 + (27 * k), 522, 92 + (27 * k));
		}
		else
		{
			setcolor(0);
			circle(519, 89 + (27 * k), 3);
			setcolor(15);
			circle(519, 89 + (27 * k), 2);
		}
	}
	settextstyle(2, 0, 5);
	setcolor(8);
	i = 530; j = 80;
	gprintf(&i, &j, "COMPUTER :%d", a[0]);
	for (f = 1; f <= n; f++)
	{
		j += 13;
		setcolor(f);
		gprintf(&i, &j, "%s :%d", na[f], a[f]);
	}
	showmptr();
}

/* This is the funtion for displaying the ranks of the players
   based on their fast reaching destination */

void thnk(int *xt, int n, int w1)
{
	int px, py, x, y, b, r = 0;
	int a = 100, bt = 80, i, t;
	cleardevice();
	setcolor(1);
	hidemptr();
	rectangle(5, 5, 625, 465);
	rectangle(0, 0, 630, 470);
	rect(10, 10, 620, 460, 12);
	rect(425, 100, 550, 125, 15);
	rect(450, 200, 515, 225, 15);
	setcolor(4);
	rectangle(425, 100, 550, 125);
	rectangle(450, 200, 515, 225);
	settextstyle(1, 0, 2);
	outtextxy(430, 100, "NEW GAME");
	outtextxy(455, 200, "EXIT");
	if (w1 == 1)
	{
		setcolor(5);
		settextstyle(1, 0, 2);
		outtextxy(110, 50, "WINNING RANKS");
		outtextxy(110, 70, "~~~~~~~~~~~~~~~~~~");
		setcolor(0);
		for (i = 0; i <= n; i++)
		{
			t = i + 1;
			bt += 20;
			if (xt[i] == 0)
				gprintf(&a, &bt, "COMPUTER -> %d", t);
			else
				gprintf(&a, &bt, "%s  -> %d", na[xt[i]], t);
		}
	}
	showmptr();
	getmpos(&b, &x, &y);
	do
	{
		px = x; py = y;
		getmpos(&b, &x, &y);
		title(425, 100, 550, 125, &b, &x, &y, &px, &py, &r, "NEW GAME");
		if (r != 0)
			break;
		title(450, 200, 515, 225, &b, &x, &y, &px, &py, &r, "EXIT");
		if (r != 0)
			break;
	} while (1);
	if (r == 15)
		new();
	else if (r == 25)
	{
		farfree(pl);
		closegraph();
		exit(0);
	}
}

/* This is the very important funtion that does the process of
	whole game, and it sets present game to the new game
	and displys the interactive messages and all funtions that we
	are having, will be called by this funtion */

void new()
{
  int i,j,mx,my,b,p,a[7],r,c,po[7],q = 0,l,so,pr,ig = 3;
  for (i = 0; i < 7; i++)
	a[i] = 0;
  p = face(); nopl = p;
  so = imagesize(1,1,19,19);
  for (i = 0; i <= p; i++)
   {
	pl[i] = (void far *)malloc(so);
	if (pl[i] == NULL)
 {
   outtextxy(100,200,"U Have Not Enough Memory To Exicute This Programme......");
   outtextxy(100,300,"Press Any Key And Exit......Srikanth Varma");
   for (j = 0; j < i; j++)
	 farfree(pl[j]);
   exit(1);
 }
   }
  hidemptr();
  names(p);
  cleardevice();
  settextstyle(0,0,0);
  board();
  outlook(p);
  hidemptr();
  rect(540,10,595,35,4);
  showmptr();
  setcolor(15);
  settextstyle(3,0,2);
  outtextxy(545,5,"EXIT");
  showmptr();
  score(a,p,15);
  ext();
  setcolor(10);
  settextstyle(8,0,4);
  hidemptr();
  outtextxy(40,10,"WELCOME");
  showmptr();
  delay(2000);
  hidemptr();
  rect(5,1,505,60,0);
  showmptr();
  for (i = 5; i >= 0; i--)
   {
 r = 40; c = 10;
 ext();
 hidemptr();
 gprintf(&r,&c,"START %d",i);
 showmptr();
 delay(500);
 ext();
 delay(500);
 hidemptr();
 rect(5,1,505,60,0);
 showmptr();
   }
  do
   {
 for (i = 0; i <= p; i++)
 {
   if (a[i] == 100)
	 continue;
   do
	{
	  mx = a[i];
	  r = 50; c = 10;
	  setcolor(15);
	  settextstyle(8,0,4);
	  hidemptr();
	  if (i != 0)
		gprintf(&r,&c,"%s",na[i]);
	  else
		outtextxy(r,c,"COMPUTER");
	  showmptr();
	  ext();
	  delay(2000);
	  if (i != 0)
	   {
	 hidemptr();
	 rect(5,1,505,60,0);
	 outtextxy(15,10,"Please CLICK On Dice");
	 showmptr();
	 settextstyle(1,0,1);
	 setcolor(14);
	 r = 530; c = 395;
	 hidemptr();
	 gprintf(&r,&c,"%s",na[i]);
	 showmptr();
	   }
	  else
	   {
	 r = 530; c = 395;
	 setcolor(14);
	 settextstyle(1,0,1);
	 hidemptr();
	 gprintf(&r,&c,"COMPUTER");
	 showmptr();
	   }
	  pr = mx;
	  j = toss(i);
	  mx += j;
	  settextstyle(1,0,1);
	  setcolor(14);
	  r += 20;
	  hidemptr();
	  gprintf(&r,&c,"GOT %d",j);
	  showmptr();
	  ext();
	  delay(2000);
	  ext();
	  setcolor(0);
	  hidemptr();
	  rect(530,390,640,460,0);
	  if (mx > 100)
		{
	 rect(5,1,505,60,0);
	 showmptr();
	 break;
		}
	  rect(510,70,640,70 + ((p + 2) * 25),15);
	  showmptr();
	  if (mx == 100)
		{
	  settextstyle(7,0,3);
	  for (j = 0; j < 4; j++)
		{
		  ext();
		  ig = 1;
		  while (ig > 0)
		   {
		  sound(200 + (ig * 1000));
		  delay(150);
		  sound(1200 + (ig * 1000));
		  delay(125);
		  sound(200 + (ig * 1000));
		  delay(150);
		  sound(1200 + (ig * 1000));
		  delay(75);
		  sound(2000 + (ig * 1000));
		  delay(200);
		  sound(5000 + (ig * 1000));
		  delay(250);
		  sound(2300 + (ig * 1000));
		  delay(300);
		  nosound();
		  ig--;
			}
		   setcolor(4);
		   r = 20; c = 10;
		   hidemptr();
		   rect(5,1,505,60,0);
		   if (i != 0)
		 gprintf(&r,&c,"%s Reach Destination",na[i]);
		   else
		 gprintf(&r,&c,"Computer Reach Destination");
		   showmptr();
		   ext();
		   delay(500);
		   hidemptr();
		   rect(5,1,505,60,0);
		   showmptr();
		   ext();
		   delay(500);
		   nosound();
		}
	  mx = 100;
	  a[i] = mx;
	  po[q] = i;
	  q++;
	  if (q == p)
	   {
		 l = 0;
		 do
		   {
		 if (a[l] < 100)
		  {
			po[p] = l;
			break;
		  }
		 else
			l++;
		   } while (l <= p);
		 thnk(po,p,1);
	   }
		}
	  a[i] = mx;
	  mov(&a[i],&my);
	  pos(a,pr,i);
	  mx = a[i];
	  if (my == 2)
		{
	 mov(&a[i],&my);
	 if (my == 0)
	   my = 2;
	 else
	  {
		pos(a,mx,i);
		hidemptr();
		rect(5,1,505,60,0);
		showmptr();
		settextstyle(7,0,3);
		for (j = 0; j < 3; j++)
		  {
		   ext();
		   r = 20; c = 10;
		   hidemptr();
		   if (i != 0)
		 gprintf(&r,&c,"%s Eaten By Snake ",na[i]);
		   else
		 gprintf(&r,&c,"Computer Eaten By Snake");
		   showmptr();
		   sound(3000);
		   delay(500);
		   nosound();
		   ext();
		   rect(5,1,505,60,0);
		   delay(500);
		  }
	  }
		}
	  hidemptr();
	  rect(5,1,505,60,0);
	  showmptr();
	  score(a,p,15);
	  if (my == 1)
	   {
		settextstyle(8,0,3);
		for (j = 0; j < 4; j++)
	 {
	   ext();
	   setcolor(4);
	   r = 20; c = 10;
	   if (i != 0)
		 gprintf(&r,&c,"%s Got Bonus Chance",na[i]);
	   else
		 gprintf(&r,&c,"Computer Got Bonus Chance");
	   ext();
	   sound(4000);
	   delay(500);
	   nosound();
	   hidemptr();
	   rect(5,1,505,60,0);
	   showmptr();
	   ext();
	   delay(500);
	 }
	   }
	 else if (my == 2)
	   {
	 setcolor(6);
	 settextstyle(8,0,3);
	 for (j = 0; j < 3; j++)
	  {
		ext();
		r = 20; c = 10;
		hidemptr();
		if (i != 0)
		  gprintf(&r,&c,"%s Eaten By Snake ",na[i]);
		else
		  gprintf(&r,&c,"Computer Eaten By Snake ");
		showmptr();
		sound(3000);
		delay(500);
		nosound();
		ext();
		hidemptr();
		rect(5,1,505,60,0);
		showmptr();
		delay(500);
	  }
	   }
	} while (my == 1);
   ext();
 }
   } while (1);
}

/* this is the main funtion which calls the "new()" funtion  */

void main()
{
	int gd = DETECT, gm, errorcode, mx, my;
	initgraph(&gd, &gm, "");
	errorcode = graphresult();
	if (errorcode != grOk)
	{
		printf("\nPlease dont copy EXE file'only'.Copy whole ZIP file(Supporting files also)");
		printf("\n\n\tClose this window to exit.....");
		printf("\n\n\n\n\n\t\tThank u....... U'rs Srikanth varma....%c %c %c", 3, 3, 3);
		exit(1);
	}
	cleardevice();
	mx = getmaxx();
	my = getmaxy();
	getpalette(&pal);
	setrgbpalette(pal.colors[6], 35, 33, 25);
	setrgbpalette(pal.colors[1], 135, 33, 125);
	setviewport(1, 1, mx - 1, my - 1, 1);
	if (initmouse() == 0)
	{
		closegraph();
		restorecrtmode();
		printf("MOUSE DRIVER IS NOT LOADED ....Press any key to exit");
		getch();
		exit(1);
	}
	resmptr(1, 1, mx - 10, my - 1);
	cleardevice();
	showmptr();
	new();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
