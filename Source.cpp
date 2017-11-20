#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <glut.h>
#include <windows.h>

int Kx, Ky, Kz, Mx, My, Mz;
int angleMx, angleMy=30, angleMz, angleKx, angleKy=30, angleKz;
int modeLight;
bool lightEnable;

void enableLight() {
	//glShadeModel(GL_FLAT);  // однотонная заливка без сглаживания (лучше рельеф виден на 
	//буквах)
	// по умолчанию GL_SMOOTH - сглаживание разрешено


	// освещение
	// задаем свойства материала
	GLfloat mat_dif[] = { (GLfloat)0.0,  (GLfloat)0.8,  (GLfloat)1.0,  (GLfloat)1.0 };   // цвет RGBA диффузной составляющей  материала
	GLfloat mat_amb[] = { (GLfloat)0.0,  (GLfloat)0.7,  (GLfloat)0.9,  (GLfloat)1.0 }; // цвет материала в тени 
	GLfloat mat_spec[] = { (GLfloat)0.0,  (GLfloat)0.4,  (GLfloat)0.4,  (GLfloat)1.0 }; // зеркальный цвет материала
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_dif);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec); 

	//установка источников света
	switch (modeLight) {
	case 1: {
		// направленный источник света
		GLfloat light0_dif[] = { (GLfloat)0.0, (GLfloat)0.6, (GLfloat)0.8 }; // цвет диффузного освещения
		GLfloat light0_dir[] = { (GLfloat)0.0,(GLfloat) 0.0, (GLfloat)1000.0, (GLfloat)0.0 };  // направление, бесконечно удаленный источник
		glEnable(GL_LIGHT0);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_dif);
		glLightfv(GL_LIGHT0, GL_POSITION, light0_dir);
		glLightf(GL_LIGHT0, GL_LIGHT_MODEL_TWO_SIDE, true);
		break;
	}
	case 2: {
		// точечный источник света
		// убывание интенсивности с расстоянием  отключено (по умолчанию)
		GLfloat light1_diffuse[] = { (GLfloat)0.0, (GLfloat)0.6, (GLfloat)0.8 }; // цвет диффузного освещения
		GLfloat light1_position[] = { (GLfloat)0.0,(GLfloat) 0.0, (GLfloat)-200.0, (GLfloat)1.0 }; // положение источника
		glEnable(GL_LIGHT1);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
		glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
		break;
	}
	case 3: {
		// точечный источник света
		// убывание интенсивности с расстоянием
		// задано функцией f(d) = 1.0 / (0.015 * d * d + 0.01 * d)
		GLfloat light2_diffuse[] = { (GLfloat) 0.0, (GLfloat)0.6, (GLfloat)0.8 };
		GLfloat light2_position[] = { (GLfloat)-200.0, (GLfloat)0.0, (GLfloat)-200.0, (GLfloat)1.0 };
		glEnable(GL_LIGHT2);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
		glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
		glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0.015);
		glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.01);
		glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.0);
		break;
	}
	case 4: {
		// прожектор
		// убывание интенсивности с расстоянием отключено (по умолчанию)
		// половина угла при вершине 50 градусов
		// направление на центр плоскости
		GLfloat light3_diffuse[] = { (GLfloat)0.0, (GLfloat)0.6, (GLfloat)0.8 };  // цвет диффузного света
		GLfloat light3_amb[] = { (GLfloat)0.0, (GLfloat)0.3, (GLfloat)0.4 };       // цвет рассеянного света
		GLfloat light3_spec[] = { (GLfloat)0.0, (GLfloat)0.7, (GLfloat)0.9 };    // цвет зеркального света
		GLfloat light3_position[] = { (GLfloat)590.0, (GLfloat)150.0, (GLfloat)-60.0, (GLfloat)1.0 };  // положение прожектора
		GLfloat light3_spot_direction[] = { (GLfloat)0.0, (GLfloat)-20.0, (GLfloat)-700.0 };  // направление прожектора
		glEnable(GL_LIGHT3);
		glLightfv(GL_LIGHT3, GL_DIFFUSE, light3_diffuse);
		glLightfv(GL_LIGHT3, GL_AMBIENT, light3_amb);
		glLightfv(GL_LIGHT3, GL_SPECULAR, light3_spec);
		glLightfv(GL_LIGHT3, GL_POSITION, light3_position);
		glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 50);
		glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, light3_spot_direction);
		break;
	}
	}
}

void drawLetterM(float height) {
	glLoadIdentity();
	enableLight();
	gluLookAt(
		0., 0., height*10,
		0., 0., 0.,
		0., 1., 0.);
	glRotatef(angleMx, 1., 0., 0.);
	glRotatef(angleMy, 0., 1., 0.);
	glRotatef(angleMz, 0., 0., 1.);
	glTranslatef(Mx, My, Mz);
	
	glColor3ub(250, 198, 0);
	//glBegin(GL_POLYGON);// V figure for M
	//glNormal3f(0., 0., 1.);
	//glVertex3f(0-height, 0 , height);//center V bottom
	//glVertex3f(2.*height - height, 2.*height , height);//right V bottom
	//glVertex3f(2.*height - height, 3.*height , height);//right V top
	//glVertex3f(0-height, height, height);//center V top
	//glVertex3f(-2.*height - height, 3.*height , height);//left V top
	//glVertex3f(-2.*height - height, 2.*height , height);//left V bottom
	//glEnd();


	glBegin(GL_POLYGON);// V figure for M
	glNormal3f(0., 0., 1.);
	glVertex3f(0 - height, 0, height);//center V bottom
	glVertex3f(2.*height - height, 2.*height, height);//right V bottom
	glVertex3f(2.*height - height, 3.*height, height);//right V top
	glVertex3f(0 - height, height, height);//center V top
	glEnd();

	glBegin(GL_POLYGON);// V figure for M
	glNormal3f(0., 0., -1.);
	glVertex3f(0 - height, 0, height);//center V bottom
	glVertex3f(-2.*height - height, 2.*height, height);//left V bottom
	glVertex3f(-2.*height - height, 3.*height, height);//left V top
	glVertex3f(0 - height, height, height);//center V top
	glEnd();


	glBegin(GL_POLYGON);//Left figure
	glNormal3f(0., 0., 1.);
	glVertex3f(-height - height, 2. * height-1.*height, height);//right top
	glVertex3f(-2.*height - height, 2. * height, height);//left top
	glVertex3f(-2.*height - height, -2.*height , height);//left bottom
	glVertex3f(-height - height, -2.*height , height);//right bottom
	glEnd();

	
	glBegin(GL_POLYGON);//right figure
	glNormal3f(0., 0., -1.);
	glVertex3f(height - height, 2. * height-height, height);//left top
	glVertex3f(2*height - height, 2. * height, height);//right top
	glVertex3f(2. * height - height, -2.*height, height);//right bottom
	glVertex3f(height - height, -2.*height, height);//left bottom
	glEnd();

	glColor3ub(255, 0, 0);

	//left bottom square
	glBegin(GL_QUADS);
	glNormal3f(0., 1., 0.);
	glVertex3f(-2.*height - height, -2.*height, height);//left bottom
	glVertex3f(-height - height, -2.*height, height);//right bottom
	glVertex3f(-height - height, -2.*height, height-height);
	glVertex3f(-height-height - height, -2.*height, height-height);
	glEnd();

	//right bottom square
	glBegin(GL_QUADS);
	glNormal3f(0., -1., 0.);
	glVertex3f(2. * height - height, -2.*height, height);//right bottom
	glVertex3f(height - height, -2.*height, height);//left bottom
	glVertex3f(height - height, -2.*height, height-height);
	glVertex3f(2. * height - height, -2.*height, height-height);
	glEnd();

	glColor3ub(200, 54, 190);

	//back right figure
	glBegin(GL_POLYGON);
	glNormal3f(0., 0., -1.);
	glVertex3f(height - height, 2. * height - height, height-height);//backleft top
	glVertex3f(2 * height - height, 2. * height, height-height);//back right top
	glVertex3f(2. * height - height, -2.*height, height-height);//back right bottom
	glVertex3f(height - height, -2.*height, height-height);//back left bottom
	glEnd();

	//back left figure
	glBegin(GL_POLYGON);//Left figure
	glNormal3f(0., 0., 1.);
	glVertex3f(-height - height, 2. * height - 1.*height, height-height);//back right top
	glVertex3f(-2.*height - height, 2. * height, height-height);//back left top
	glVertex3f(-2.*height - height, -2.*height, height-height);//back left bottom
	glVertex3f(-height - height, -2.*height, height-height);//back right bottom
	glEnd();

	//back V figure
	//glBegin(GL_POLYGON);// V figure for M
	//glNormal3f(0., 0., 1.);
	//glVertex3f(0 - height, 0, height-height);//back center V bottom
	//glVertex3f(2.*height - height, 2.*height, height-height);//back right V bottom
	//glVertex3f(2.*height - height, 3.*height, height-height);//back right V top
	//glVertex3f(0-height, height, height-height);//back center V top
	//glVertex3f(-2.*height - height, 3.*height, height-height);//back left V top
	//glVertex3f(-2.*height - height, 2.*height, height-height);//back left V bottom
	//glEnd();

	glBegin(GL_POLYGON);// V figure for M
	glNormal3f(0., 0., 1.);
	glVertex3f(0 - height, 0, 0);//center V bottom
	glVertex3f(2.*height - height, 2.*height, 0);//right V bottom
	glVertex3f(2.*height - height, 3.*height, 0);//right V top
	glVertex3f(0 - height, height, 0);//center V top
	glEnd();

	glBegin(GL_POLYGON);// V figure for M
	glNormal3f(0., 0., -1.);
	glVertex3f(0 - height, 0, 0);//center V bottom
	glVertex3f(-2.*height - height, 2.*height, 0);//left V bottom
	glVertex3f(-2.*height - height, 3.*height, 0);//left V top
	glVertex3f(0 - height, height, 0);//center V top
	glEnd();

	glColor3ub(120, 100, 160);

	//right wall
	glBegin(GL_POLYGON);
	glNormal3f(1., 0., 0.);
	glVertex3f(2.*height - height, 3.*height, height - height);//back right V top
	glVertex3f(2.*height - height, 3.*height, height);// right V top
	glVertex3f(2. * height - height, -2.*height, height);//right bottom
	glVertex3f(2. * height - height, -2.*height, height - height);//right bottom
	glEnd();

	//right inside wall
	glBegin(GL_POLYGON);
	glNormal3f(1., 0., 0.);
	glVertex3f(1. * height - height, -2.*height, height);//right bottom
	glVertex3f(1. * height - height, -2.*height, height - height);
	glVertex3f(height - height, 2. * height - height, height - height);//backleft top
	glVertex3f(height - height, 2. * height - height, height);//backleft top
	glEnd();

	glBegin(GL_POLYGON);//Left figure left
	glNormal3f(1., 0., 0.);
	glVertex3f(-2.*height - height, 3. * height, 0);//left top
	glVertex3f(-2.*height - height, 3. * height, height);//left top
	glVertex3f(-2.*height - height, -2.*height, height);//left bottom
	glVertex3f(-2.*height - height, -2.*height, 0);//left bottom
	glEnd();

	glBegin(GL_POLYGON);// V figure for M top right
	glNormal3f(-1., 1., 0.);
	glVertex3f(2.*height - height, 3.*height, height);//right V bottom
	glVertex3f(2.*height - height, 3.*height, 0);//right V bottom
	glVertex3f(0 - height, height, 0);//center V top
	glVertex3f(0 - height, height, height);//center V top
	glEnd();

	glBegin(GL_POLYGON);// V figure for M top left
	glNormal3f(-1., -1., 0.);
	glVertex3f(0 - height, height, 0);//center V top
	glVertex3f(0 - height, height, height);//center V top
	glVertex3f(-2.*height - height, 3.*height, height);//left V top
	glVertex3f(-2.*height - height, 3.*height, 0);//left V top
	glEnd();

	glBegin(GL_POLYGON);// V figure for M down right
	glNormal3f(-1., 1., 0.);
	glVertex3f(0 - height, 0, 0);//center V bottom
	glVertex3f(0 - height, 0, height);//center V bottom
	glVertex3f(2.*height - height, 2.*height, height);//right V bottom
	glVertex3f(2.*height - height, 2.*height, 0);//right V bottom
	glEnd();

	glBegin(GL_POLYGON);// V figure for M down left
	glNormal3f(1., -1., 0.);
	glVertex3f(0 - height, 0, 0);//center V bottom
	glVertex3f(0 - height, 0, height);//center V bottom
	glVertex3f(-2.*height - height, 2.*height, height);//left V bottom
	glVertex3f(-2.*height - height, 2.*height, 0);//left V bottom
	glEnd();

	glBegin(GL_POLYGON);//Left figure right
	glNormal3f(1., 0., 0.);
	glVertex3f(-height - height, 2. * height - 1.*height, 0);//right top
	glVertex3f(-height - height, 2. * height - 1.*height, height);//right top
	glVertex3f(-height - height, -2.*height, height);//right bottom
	glVertex3f(-height - height, -2.*height, 0);//right bottom
	glEnd();
}

void drawLetterK(float height) {
	glLoadIdentity();
	enableLight();
	gluLookAt(
		0., 0., height * 10,
		0., 0., 0.,
		0., 1., 0.);

	glRotatef(angleKx, 1., 0., 0.);
	glRotatef(angleKy, 0., 1., 0.);
	glRotatef(angleKz, 0., 0., 1.);
	glTranslatef(Kx, Ky, Kz);

	glColor3ub(104, 16, 56);

	glBegin(GL_POLYGON);//Left figure
	glNormal3f(0., 0., 1);
	glVertex3f(-height+3.7*height, 3. * height, height);//right top
	glVertex3f(-2.*height + 3.7*height, 3. * height, height);//left top
	glVertex3f(-2.*height + 3.7*height, -2.*height, height);//left bottom
	glVertex3f(-height + 3.7*height, -2.*height, height);//right bottom
	glEnd();

	glBegin(GL_QUADS);//top trapetion
	glNormal3f(0., 0., -1);
	glVertex3f(-height + 3.7*height, 1.5*height, height);//left top
	glVertex3f(0.1*height + 3.7*height, 3. * height, height);//right top
	glVertex3f(1.*height + 3.7*height, 3. * height, height);//right top 2
	glVertex3f(-height + 3.7*height, 0 * height, height);//bottom
	glEnd();

	glBegin(GL_QUADS);//bottom trapetion
	glNormal3f(0., 0., -1);
	glVertex3f(-height + 3.7*height, 0.01*height, height);
	glVertex3f(-0.6*height + 3.7*height+0.04*height, 0.7 * height-0.02*height, height);
	glVertex3f(1.5*height + 3.7*height, -2. * height, height);
	glVertex3f(0.4*height + 3.7*height, -2. * height, height);
	glEnd();


	glColor3ub(104, 110, 56);
	glBegin(GL_POLYGON);//Left figure
	glNormal3f(0., 0., 1);
	glVertex3f(-height + 3.7*height, 3. * height, height - height);//right top
	glVertex3f(-2.*height + 3.7*height, 3. * height, height - height);//left top
	glVertex3f(-2.*height + 3.7*height, -2.*height, height - height);//left bottom
	glVertex3f(-height + 3.7*height, -2.*height, height - height);//right bottom
	glEnd();

	glBegin(GL_QUADS);//top trapetion
	glNormal3f(0., 0., -1);
	glVertex3f(-height + 3.7*height, 1.5*height, height - height);
	glVertex3f(0.1*height + 3.7*height, 3. * height, height - height);
	glVertex3f(1.*height + 3.7*height, 3. * height, height - height);
	glVertex3f(-height + 3.7*height, 0 * height, height - height);
	glEnd();

	glBegin(GL_QUADS);//bottom trapetion
	glNormal3f(0., 0., -1);
	glVertex3f(-height + 3.7*height, 0.01*height, 0);
	glVertex3f(-0.6*height + 3.7*height + 0.04*height, 0.7 * height - 0.02*height, 0);
	glVertex3f(1.5*height + 3.7*height, -2. * height, height - height);
	glVertex3f(0.4*height + 3.7*height, -2. * height, height - height);
	glEnd();

	glColor3ub(200, 54, 60);

	//bottom squares
	glBegin(GL_QUADS);
	glNormal3f(0., 1., 0);
	glVertex3f(-2.*height + 3.7*height, -2.*height, height);//left bottom
	glVertex3f(-height + 3.7*height, -2.*height, height);//right bottom
	glVertex3f(-height + 3.7*height, -2.*height, height - height);//right bottom
	glVertex3f(-2.*height + 3.7*height, -2.*height, height - height);//left bottom
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(0., -1., 0);
	glVertex3f(1.5*height + 3.7*height, -2. * height, height);
	glVertex3f(0.4*height + 3.7*height, -2. * height, height);
	glVertex3f(0.4*height + 3.7*height, -2. * height, height - height);
	glVertex3f(1.5*height + 3.7*height, -2. * height, height - height);
	glEnd();

	//top squards
	glBegin(GL_QUADS);
	glNormal3f(0., 1., 0);
	glVertex3f(-2.*height + 3.7*height, 3.*height, height);//left bottom
	glVertex3f(-height + 3.7*height, 3.*height, height);//right bottom
	glVertex3f(-height + 3.7*height, 3.*height, height - height);//right bottom
	glVertex3f(-2.*height + 3.7*height, 3.*height, height - height);//left bottom
	glEnd();


	glBegin(GL_QUADS);
	glNormal3f(0., 1., 0);
	glVertex3f(0.1*height + 3.7*height, 3. * height, height);//right top
	glVertex3f(1.*height + 3.7*height, 3. * height, height);//right top 2
	glVertex3f(1.*height + 3.7*height, 3. * height, height - height);
	glVertex3f(0.1*height + 3.7*height, 3. * height, height - height);
	glEnd();

	//left wall
	glBegin(GL_QUADS);
	glNormal3f(-1., 0., 0);
	glVertex3f(1.7*height, 3. * height, height);//right top
	glVertex3f(1.7*height, 3. * height, height - height);//right top
	glVertex3f(1.7*height, -2.*height, height - height);//left bottom
	glVertex3f(1.7*height, -2.*height, height);//right bottom
	glEnd();

	//right wall
	glBegin(GL_QUADS);
	glNormal3f(-1., 0., 0);
	glVertex3f(-1 * height + 3.7*height, 3. * height, height);//right top
	glVertex3f(-1 * height + 3.7*height, 3. * height, height - height);//right top
	glVertex3f(-1 * height + 3.7*height, -2.*height, height - height);//left bottom
	glVertex3f(-1.*height + 3.7*height, -2.*height, height);//right bottom
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(-1., 1., 0);
	glVertex3f(-height + 3.7*height, 1.5*height, height - height);
	glVertex3f(-height + 3.7*height, 1.5*height, height);
	glVertex3f(0.1*height + 3.7*height, 3. * height, height);
	glVertex3f(0.1*height + 3.7*height, 3. * height, height - height);
	glEnd();
	
	glBegin(GL_POLYGON);
	glNormal3f(1., -1., 0);
	glVertex3f(-0.6*height + 3.7*height + 0.04*height, 0.7 * height - 0.02*height, 0);
	glVertex3f(-0.6*height + 3.7*height + 0.04*height, 0.7 * height - 0.02*height, height);
	glVertex3f(1.5*height + 3.7*height, -2. * height, height);
	glVertex3f(1.5*height + 3.7*height, -2. * height, height - height);
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(-1., 1., 0);
	glVertex3f(-height + 3.7*height, 0.01*height, 0);
	glVertex3f(-height + 3.7*height, 0.01*height, height);
	glVertex3f(0.4*height + 3.7*height, -2. * height, height);
	glVertex3f(0.4*height + 3.7*height, -2. * height, height - height);
	glEnd();

	glBegin(GL_QUADS);//top trap wall
	glNormal3f(1., -1., 0);
	glVertex3f(1.*height + 3.7*height, 3. * height, height - height);
	glVertex3f(1.*height + 3.7*height, 3. * height, height);
	glVertex3f(-height + 3.7*height, 0 * height, height);
	glVertex3f(-height + 3.7*height, 0 * height, height - height); 
	glEnd();

	//*********************************************************************
	/*
	glBegin(GL_QUADS);//Left figure
	glNormal3f(0., 0., -1);
	for (float i = -2.; i < 3.; i += 0.01) {
		glVertex3f(-height + 3.7*height, (i + 0.01) * height, height);//right top
		glVertex3f(-2.*height + 3.7*height, (i+0.01) * height, height);//left top
		glVertex3f(-2.*height + 3.7*height, i*height, height);//left bottom
		glVertex3f(-height + 3.7*height, i*height, height);//right bottom
	}
	glEnd();


	glBegin(GL_QUADS);//top trapetion
	glNormal3f(0., 0., 1);
	for (float i1 = 2.7, i2 = 2.7, j1 = 1.5, j2 = 0; i1 < 3.8 - 0.011; i1 += 0.011, j1 += 0.015, i2 += 0.02, j2 += 0.03) {
		glVertex3f(i1*height, j1*height, height);//left top
		glVertex3f((i1+0.011)*height, (j1+0.015) * height, height);//right top
		glVertex3f((i2+0.02)*height, (j2+0.03) * height, height);//right top 2
		glVertex3f(i2*height, j2 * height, height);//bottom
	}
	glEnd();

	glBegin(GL_QUADS);//bottom trapetion
	glNormal3f(0., 0., 1);
	for (float i1 = 2.5, i2 = 3.1, j1 = 0.05, j2 = 0.7; i1 < 4.1; i1 += 0.016, i2 += 0.021, j1 -= 0.0205, j2 -= 0.027) {
		glVertex3f(i1*height, j1*height, height);
		glVertex3f(i2*height, j2 * height, height);
		glVertex3f((i2+0.021)*height, (j2-0.027) * height, height);
		glVertex3f((i1+0.016)*height, (j1-0.0205) * height, height);
	}
	glEnd();


	//back K
	glColor3ub(104, 110, 56);
	glBegin(GL_POLYGON);//Left figure
	glNormal3f(0., 0., -1); 
	for (float i = -2.; i < 3.; i += 0.01) {
		glVertex3f(-height + 3.7*height, (i + 0.01) * height, 0);//right top
		glVertex3f(-2.*height + 3.7*height, (i + 0.01) * height, 0);//left top
		glVertex3f(-2.*height + 3.7*height, i*height, 0);//left bottom
		glVertex3f(-height + 3.7*height, i*height, 0);//right bottom
	}
	glEnd();

	glBegin(GL_QUADS);//top trapetion
	glNormal3f(0., 0., 1);
	for (float i1 = 2.7, i2 = 2.7, j1 = 1.5, j2 = 0; i1 < 3.8 - 0.011; i1 += 0.011, j1 += 0.015, i2 += 0.02, j2 += 0.03) {
		glVertex3f(i1*height, j1*height, 0);//left top
		glVertex3f((i1 + 0.011)*height, (j1 + 0.015) * height, 0);//right top
		glVertex3f((i2 + 0.02)*height, (j2 + 0.03) * height, 0);//right top 2
		glVertex3f(i2*height, j2 * height, 0);//bottom
	}
	glEnd();

	glBegin(GL_QUADS);//bottom trapetion
	glNormal3f(0., 0., 1);
	for (float i1 = 2.5, i2 = 3.1, j1 = 0.05, j2 = 0.7; i1 < 4.1; i1 += 0.016, i2 += 0.021, j1 -= 0.0205, j2 -= 0.027) {
		glVertex3f(i1*height, j1*height, 0);
		glVertex3f(i2*height, j2 * height, 0);
		glVertex3f((i2 + 0.021)*height, (j2 - 0.027) * height, 0);
		glVertex3f((i1 + 0.016)*height, (j1 - 0.0205) * height, 0);
	}
	glEnd();
	glColor3ub(200, 54, 60);
	//bottom squares
	glBegin(GL_QUADS);
	glNormal3f(0., -1., 0);
	for (float i = 0; i < 1; i += 0.034) {
		glVertex3f(1.7*height, -2.*height, (i+0.034)*height);//left bottom
		glVertex3f(2.7*height, -2.*height, (i+0.034)*height);//right bottom
		glVertex3f(2.7*height, -2.*height, i*height);//right bottom
		glVertex3f(1.7*height, -2.*height, i*height);//left bottom
	}
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(0., 1., 0);
	for (float i = 0; i < 1; i += 0.034) {
		glVertex3f(5.2*height, -2. * height, (i + 0.034)*height);
		glVertex3f(4.1*height, -2. * height, (i+0.034)*height);
		glVertex3f(4.1*height, -2. * height, i*height);
		glVertex3f(5.2*height, -2. * height, i*height);
	}
	glEnd();
	//top squards
	glBegin(GL_QUADS);
	glNormal3f(0., -1., 0);
	for (float i = 0; i < 1; i += 0.034) {
		glVertex3f(1.7*height, 3.*height, (i+0.034)*height);//left bottom
		glVertex3f(2.7*height, 3.*height, (i+0.034)*height);//right bottom
		glVertex3f(2.7*height, 3.*height, i*height);//right bottom
		glVertex3f(1.7*height, 3.*height, i*height);//left bottom
	}
	glEnd();
	//left wall
	glBegin(GL_QUADS);
	glNormal3f(1., 0., 0);
	for (float i = -2; i < 3-0.05; i += 0.05) {
		glVertex3f(1.7*height, (i+0.05)* height, height);//right top
		glVertex3f(1.7*height, (i+0.05) * height, 0);//right top
		glVertex3f(1.7*height, i*height, 0);//left bottom
		glVertex3f(1.7*height, i*height,height);//right bottom
	}
	glEnd();
	//right wall
	glBegin(GL_QUADS);
	glNormal3f(1., 0., 0);
	for (float i = -2; i < 3-0.05; i += 0.05) {
		glVertex3f(2.7*height, (i+0.05) * height, height);//right top
		glVertex3f(2.7*height, (i+0.05) * height, 0);//right top
		glVertex3f(2.7*height, i*height, 0);//left bottom
		glVertex3f(2.7*height, i*height, height);//right bottom
	}
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(1., -1., 0);
	for (float i = 2.7, j = 1.5; i < 3.8 - 0.011; i += 0.011, j +=0.015) {
	glVertex3f(i*height, j*height, 0);
	glVertex3f(i*height, j*height, height);
	glVertex3f((i+0.011)*height, (j+0.015) * height, height);
	glVertex3f((i+0.011)*height, (j + 0.015) * height, 0);
	}
	glEnd();

	glBegin(GL_QUADS);
	glNormal3f(-1., 1., 0);
	for (float i = 3.1, j = 0.7; i < 5.2 - 0.021; i += 0.021, j -= 0.027) {
		glVertex3f(i*height, j * height, 0);
		glVertex3f(i*height, j * height, height);
		glVertex3f((i + 0.021)*height, (j - 0.027) * height, height);
		glVertex3f((i + 0.021)*height, (j - 0.027) * height, 0);
	}
	glEnd();
	glBegin(GL_QUADS);
	glNormal3f(1., -1., 0);
	for (float i = 2.5, j = 0.05; i < 4.1; i += 0.016, j -= 0.0205) {
	glVertex3f(i*height, j*height, 0);
	glVertex3f(i*height, j*height, height);
	glVertex3f((i + 0.016)*height, (j - 0.0205) * height, height);
	glVertex3f((i + 0.016)*height, (j - 0.0205) * height, 0);
	}
	glEnd();

	glBegin(GL_QUADS);//top trap wall
	glNormal3f(-1., 1., 0);
	for (float i = 2.7, j = 0; i < 4.7 - 0.02; i += 0.02, j += 0.03) {
		glVertex3f(i*height, j * height, 0);
		glVertex3f(i*height, j * height, height);
		glVertex3f((i+0.02)*height, (j+0.03) * height, height);
		glVertex3f((i + 0.02)*height, (j + 0.03) * height, 0);
	}
	glEnd();
	*/

 }

void DetectSpecKeys(int key, int x, int y)
{
	switch (key)
	{
	case '27': {
		exit(0);
		break;
	}
	case GLUT_KEY_UP: {
		Ky += 10;
		My += 10;
		break;
	}
	case GLUT_KEY_DOWN: {
		Ky -= 10;
		My -= 10;
		break;
	}
	case GLUT_KEY_LEFT: {
		Kx -= 10;
		Mx -= 10;
		break;
	}
	case GLUT_KEY_RIGHT: {
		Kx += 10;
		Mx += 10;
		break;
	}
	case GLUT_KEY_PAGE_UP:{
		Kz += 10;
		Mz += 10;
		break;
	}
	case GLUT_KEY_PAGE_DOWN: {
		Kz -= 10;
		Mz -= 10;
		break;
	}
	case GLUT_KEY_F1: {
		angleMx += 10;
		angleKx += 10;
		break;
	}
	case GLUT_KEY_F2: {
		angleMx -= 10;
		angleKx -= 10;
		break;
	}
	case GLUT_KEY_F3: {
		angleMy += 10;
		angleKy += 10;
		break;
	}
	case GLUT_KEY_F4: {
		angleMy -= 10;
		angleKy -= 10;
		break;
	}
	case GLUT_KEY_F5: {
		angleMz += 10;
		angleKz += 10;
		break;
	}
	case GLUT_KEY_F6: {
		angleMz -= 10;
		angleKz -= 10;
		break;
	}
	}
}

void DetectKeys(unsigned char key, int x, int y)
{
	switch (key)
	{
		//letter M
	case 'q': {
		angleMx += 10;
		break;
	}
	case 'a': {
		angleMx -= 10;
		break;
	}
	case 'w': {
		angleMy += 10;
		break;
	}
	case 's': {
		angleMy -= 10;
		break;
	}
	case 'e': {
		angleMz += 10;
		break;
	}
	case 'd': {
		angleMz -= 10;
		break;
	}
	case 'z': {
		Mx += 10;
		break;
	}
	case 'Z':{
		Mx -= 10;
		break;
	}
	case 'x': {
		My += 10;
		break;
	}
	case 'X': {
		My -= 10;
		break;
	}
	case 'c': {
		Mz += 10;
		break;
	}
	case 'C': {
		Mz -= 10;
		break;
	}
	//letter K
	case 'r': {
		angleKx += 10;
		break;
	}
	case 'f': {
		angleKx -= 10;
		break;
	}
	case 't': {
		angleKy += 10;
		break;
	}
	case 'g': {
		angleKy -= 10;
		break;
	}
	case 'y': {
		angleKz += 10;
		break;
	}
	case 'h': {
		angleKz -= 10;
		break;
	}
	case 'v': {
		Kx += 10;
		break;
	}
	case 'V': {
		Kx -= 10;
		break;
	}
	case 'b': {
		Ky += 10;
		break;
	}
	case 'B': {
		Ky -= 10;
		break;
	}
	case 'n': {
		Kz += 10;
		break;
	}
	case 'N': {
		Kz -= 10;
		break;
	}
	
	}
	if (lightEnable) {
		switch (key) {
		case '1': modeLight = 1; break;
		case '2': modeLight = 2; break;
		case '3': modeLight = 3; break;
		case '4': modeLight = 4; break;
		case '0': modeLight = 0; break;
		}
	}
}

void ExecuteMenu(int option) {

	switch (option) {
	case 1: {
		glDisable(GL_LIGHTING);
		lightEnable = false;
		glClearColor(1, 0.82, 0.8, 1.0);//устанавливает цвет, которым будет заполнен буфер кадра
		break;
	}
	case 2: {
		glEnable(GL_LIGHTING);
		lightEnable = true;
		glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
		glClearColor(0.3, 0.3, 0.3, 1.0);
		break;
	}
	}
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
	glutPostRedisplay();

}
void createMenu() {
	glutCreateMenu(ExecuteMenu);
	glutAddMenuEntry("Выключить освещение", 1);
	glutAddMenuEntry("Включить освещение", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void RenderScene(){
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	drawLetterM(48.);
	drawLetterK(48.);

	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHT2);
	glDisable(GL_LIGHT3);
	glDisable(GL_LIGHT4);
	glDisable(GL_LIGHT5);
	glDisable(GL_LIGHT6);
	glDisable(GL_LIGHT7);


	glFlush(); // В буфер вводятся команды рисования
	glutSwapBuffers();
}

void ChangeWindowSize(int width, int height)
{

	// Предотвращаем деление на нуль
	if (height == 0)   height = 1;
	// Устанавливаем поле просмотра с размерами окна
	glViewport(0, 0, width, height);
	// Устанавливает матрицу преобразования в режим проецирования
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Устанавливаем размеры перспективы (отсекающего объема)
	// (left, right, bottom, top, near, far)
	GLfloat aspectRatio = (GLfloat)width / (GLfloat)height;// Для коррекции

	glViewport(0, 0, width, height);
	// установить корректную перспективу
	gluPerspective(45.0f, aspectRatio, 1., 10000.0);

	// Восстанавливает матрицу преобразования в исходный режим вида
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char* argv[])
{

	modeLight = 0;
	lightEnable = false;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1024, 720);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Katcay, PK-15-1");

	glClearColor(1, 0.82, 0.8, 1.0);//устанавливает цвет, которым будет заполнен буфер кадра
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
	createMenu();
	glutDisplayFunc(RenderScene);
	glutIdleFunc(RenderScene);
	glutReshapeFunc(ChangeWindowSize);
	glutSpecialFunc(DetectSpecKeys);
	glutKeyboardFunc(DetectKeys);
	glutMainLoop();

	return 0;
}