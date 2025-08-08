// Date: 18.03.2025
// plik: Lab2

#include <GL/glut.h>	
//=======================================================================================================================
// ZMNIENNE GLOBALNE

double kat = 0, kat1 = 0, kat2 = 0;
double radius, radius2;
int color1 = 1;

//mouse 
int mouBut = -1; //stan przycisku myszki
GLdouble click_x = 0, click_y = 0; //zmienne wsp�rz�dnych myszki 
float rot_x, rot_y;
float zoom = 1;
static GLdouble coordX = 0.0, coordY = 0.0;

//=======================================================================================================================
// WINDOW BG COLOUR

void InitGL(void)
{
	// Setting background colour
	glClearColor(0.5, 1.0, 0.5, 0.0); // Colour light green
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST); //rysowanie z g��bi� ekranu
}

//========================================================================================================================
// ANGLES AND RADIUS 

void Idle(void) {
	kat += 0.3; // zwi�kszenie k�ta obrotu o 5, to samo co kat = kat +5
	kat1 = 0.2;
	kat2 = 0.1;
	radius = 10;
	radius2 = 5;
	glutPostRedisplay();
}

//=======================================================================================================================
// TEXT AND FONT

void text(const char* string)
{
	const char* p;
	for (p = string; *p; p++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *p);

}

//=======================================================================================================================
// SCREEN

void reshape(int w, int h)
{
	GLdouble aspect = (GLdouble)w / h;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h) // ( aspect < 1.0 ) 
		glOrtho(-250., 250.0, -250. / aspect, 250.0 / aspect, -150, 150);
	else
		glOrtho(-250. * aspect, 250. * aspect, -250, 250, -150.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//=======================================================================================================================
// OBJECTS

void draw(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //czyszczenie bufor�w

	// Lab 3 Program 8; Adding text and using function void text(const char* string)

	glLoadIdentity();

	glColor3d(1, 1, 1);
	glRasterPos2f(-200, 200);
	text("Kolory 1-4: Only one sad cube");

	//przed rysowaniem obiekt�w 
	glTranslatef(coordX, coordY, 0); //przesuni�cie o coordX i coordY
	glRotatef(rot_x, 0, 1, 0); //obr�t o k�t rot_x
	glRotatef(rot_y, 1, 0, 0);
	glScalef(zoom, zoom, zoom); //skalowanie

	//-------------------------------
	// pierwsza kostka
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3d(0.0, 0.0, 2.0); // colour (lighter) blue
	
	
	//glRotatef(8.0, 1.0, 8.0, 5.0);
	glRotatef(kat, 1.0, 3.0, 5.0); // Makes it spin
	//glTranslate(1.0, 1, 0);

	// Assigning different colours to different cases to be used later in Keyboard function

	if (color1 == 1) glColor3d(1, 0, 1); //2 razy znak = Sprawdzamy ile wynosi zmienna
	if (color1 == 2) glColor3d(0, 1, 1);
	if (color1 == 3) glColor3d(1, 0, 0);
	if (color1 == 4) glColor3d(1, 1, 1);

	glutSolidCube(150);

	//-------------------------------
	//drugi obiekt
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3d(0.0, 5.0, 0.0); // colour saturated green

	glRotatef(kat1, 5.0, 1.0, 0.0); // Makes it spin

	glutSolidTorus(radius, 170, 10, 10);

	//-------------------------------
	//trzeci obiekt
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3d(0.0, 8.0, 0.0); // colour saturated green

	glRotatef(kat2, 1.0, 3.0, -8.0); // Makes it spin

	glutSolidTorus(radius2, 210, 10, 10);

	glFlush();
	glutSwapBuffers();	//zamienia buforyW
}
//============================================================================================================================================
// KEYBOARD

void Klawiatura(unsigned char key, int x, int y)
{
	switch (key) //albo if(key == 'r') color1 = 1;
	{
	case '1': //je�eli wci�ni�ty klawisz �1�
		color1 = 1; //warto�� zmiennej color1 b�dzie 1
		break;
	case '2': //je�eli wci�ni�ta �2�
		color1 = 2; //warto�� zmiennej color1 b�dzie 2
		break;
	case '3': //je�eli wci�ni�ta �2�
		color1 = 3; //warto�� zmiennej color1 b�dzie 2
		break;
	case '4': //je�eli wci�ni�ta �2�
		color1 = 4; //warto�� zmiennej color1 b�dzie 2
		break;
	case 27: case 'q': case 'Q': //je�eli wci�ni�te �q�, lub Esc (kod 27)
		exit(0); // wyj�cie z programu
		break;
	}
}

//============================================================================================================================================
// MOUSE

void myMouse(int button, int state, int mouseX, int mouseY)
{
	if (state == GLUT_DOWN) { //je�eli wci�ni�ty
		switch (button) {
		case GLUT_LEFT_BUTTON: //lewy prycisk
			mouBut = 0;
			break;
		case GLUT_MIDDLE_BUTTON: //�rodkowy (pokr�t�o)
			mouBut = 1;
			break;
		case GLUT_RIGHT_BUTTON: //prawy
			mouBut = 2;
			break;
		}
	}
	click_x = mouseX; //wsp�rz�dne myszki w moment klikni�cia
	click_y = mouseY;
}

//============================================================================================================================================
// MOTION

void myMotion(int mouseX, int mouseY)
{
	if (mouBut == 0) //je�eli wci�ni�ty lewy przycisk
	{
		coordX -= (click_x - mouseX); //przesuni�cie od wsp�rz. click_x do mouseX
		coordY += (click_y - mouseY);
	}
	else if (mouBut == 1) //je�eli pokr�t�o
	{
		zoom += (click_x - mouseX) * 0.05; //zmiana wsp�czynnika skalowania 
	}
	else if (mouBut == 2) //wci�ni�ty prawy przycisk
	{
		rot_x -= (click_x - mouseX); //zmiana k�ta obrotu zale�na od click_x i mouseX
		rot_y += (click_y - mouseY);
	}

	click_x = mouseX;
	click_y = mouseY;
	glutPostRedisplay();
}

//=======================================================================================================================
//================================================= MAIN ================================================================

int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Cube.");

	InitGL();

	//o�wietlenie 
	float pos[4] = { 1.50F, 3.50F, 0.25F, 0.00F };
	float dir[3] = { -1,-1,-1 };
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);

	glutReshapeFunc(reshape);
	glutDisplayFunc(draw);
	
	// Adding mouse functionality
	glutMouseFunc(myMouse);
	glutMotionFunc(myMotion);
	glutIdleFunc(Idle);

	// Adding keyboard functionality
	glutKeyboardFunc(Klawiatura);
	glutMainLoop();

	return 0;
}

//=======================================================================================================================
