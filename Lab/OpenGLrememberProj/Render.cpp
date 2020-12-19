#include "Render.h"

#include <Windows.h>
#include <GL\GL.h>
#include <GL\GLU.h>

#include <cmath>

// для кривой Безье третьего порядка
double _bezier(double p1, double p2, double p3, double p4, double t) {
	return pow(1 - t, 3) * p1 + 3 * t * pow(1 - t, 2) * p2 + 3 * pow(t, 2) * (1 - t) * p3 + pow(t, 3) * p4;
}

// для кривой Эрмита 
double _ermit(double p1, double p4, double r1, double r4, double t) {
	return p1 * (2 * pow(t, 3) - 3 * pow(t, 2) + 1) + p4 * (-2 * pow(t, 3) + 3 * pow(t, 2)) + r1 * (pow(t, 3) - 2 * pow(t, 2) + t) + r4 * (pow(t, 3) - pow(t, 2));
}


void ErmitCurve(double P1[3], double P4[3], double R1[3], double R4[3]) {
	double P[3];

	glLineWidth(3); //ширина линии
	glColor3d(0, 1, 0);
	glBegin(GL_LINE_STRIP);
	for (double t = 0; t <= 1.001; t += 0.01)
	{
		P[0] = _ermit(P1[0], P4[0], R1[0], R4[0], t);
		P[1] = _ermit(P1[1], P4[1], R1[1], R4[1], t);
		P[2] = _ermit(P1[2], P4[2], R1[2], R4[2], t);
		glVertex3dv(P); //Рисуем точку P
	}

	glEnd();

	// красивости
	R1[0] = P1[0] + R1[0];
	R1[1] = P1[1] + R1[1];
	R1[2] = P1[2] + R1[2];

	R4[0] = P4[0] + R4[0];
	R4[1] = P4[1] + R4[1];
	R4[2] = P4[2] + R4[2];

	glColor3d(1, 0, 1);
	glLineWidth(1); //возвращаем ширину линии = 1
	glPointSize(10);

	glBegin(GL_LINES); // отрезки
	glVertex3dv(P1);
	glVertex3dv(R1);

	glVertex3dv(P4);
	glVertex3dv(R4);
	glEnd();

	glColor3d(1, 0, 0);
	glBegin(GL_POINTS); // точки
	glVertex3dv(P1);
	glVertex3dv(P4);

	glColor3d(1, 0, 1);
	glVertex3dv(R1);
	glVertex3dv(R4);
	glEnd();
}

void BezierCurve(double P1[3], double P2[3], double P3[3], double P4[3]) {
	double P[3];

	glLineWidth(3); //ширина линии
	glColor3d(0, 1, 0);
	glBegin(GL_LINE_STRIP);
	for (double t = 0; t <= 1.001; t += 0.01)
	{
		P[0] = _bezier(P1[0], P2[0], P3[0], P4[0], t);
		P[1] = _bezier(P1[1], P2[1], P3[1], P4[1], t);
		P[2] = _bezier(P1[2], P2[2], P3[2], P4[2], t);
		glVertex3dv(P); //Рисуем точку P
	}
	glEnd();

	// красивости
	glColor3d(1, 0, 1);
	glLineWidth(1); //возвращаем ширину линии = 1
	glPointSize(10);
	glBegin(GL_LINE_STRIP); // отрезки
	glVertex3dv(P1);
	glVertex3dv(P2);
	glVertex3dv(P3);
	glVertex3dv(P4);
	glEnd();

	glColor3d(1, 0, 0);
	glBegin(GL_POINTS); // точки
	glVertex3dv(P1);
	glVertex3dv(P2);
	glVertex3dv(P3);
	glVertex3dv(P4);
	glEnd();
}



void Render(double delta_time)
{

	double P1_1[] = { 0, 0, 0 }; 
	double P2_1[] = { -2, 3, 3 };
	double P3_1[] = { 4, 2, 4 };
	double P4_1[] = { -2, 3, 1 };
	BezierCurve(P1_1, P2_1, P3_1, P4_1);

	double P1_2[] = { 6, 5, 6 }; 
	double P2_2[] = { 7, 5, 3 };
	double P3_2[] = { 10, 5, 7 };
	double P4_2[] = { 10, 10, 1 };
	BezierCurve(P1_2, P2_2, P3_2, P4_2);

	double P1_3[] = { -5, -5, -3 };
	double P4_3[] = { -3, -1, 3 };
	double R1_1[] = { 1, 0, 1 };
	double R4_1[] = { 0, -4, 1 };
	ErmitCurve(P1_3, P4_3, R1_1, R4_1);

	double P1_4[] = { -1, -1, -5 };
	double P4_4[] = { -1, -3, -3 };
	double R1_2[] = { 2, 2, 1 };
	double R4_2[] = { 1, 2, 0 };
	ErmitCurve(P1_4, P4_4, R1_2, R4_2);


}