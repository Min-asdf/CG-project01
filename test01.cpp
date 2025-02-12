#include <GL/freeglut.h>

// flatshading과 Wireframe을 토글링하기 위한 부울 변수
int FlatShaded = 0;
int Wireframed = 0;

// 마우스 움직임에 따라 시점을 바꾸기 위한 변수 
int ViewX = 0, ViewY = 0;

void InitLight() {
	GLfloat mat_diffuse[] = { 0.5, 0.4, 0.3, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_ambient[] = { 0.5, 0.4, 0.3, 1.0 };
	GLfloat mat_shininess[] = { 15.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat light_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat light_position[] = { -3, 6, 3.0, 0.0 };
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

// *마우스 움직임 X,Y를 전역 변수인 ViewX, ViewY에 할당
void MyMouseMove(GLint X, GLint Y) {
	ViewX = X;
	ViewY = Y;
	glutPostRedisplay();
}

void MyKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'q': case 'Q': case '\033':
		exit(0);
		break;
	case 's':
		if (FlatShaded) {
			FlatShaded = 0;
			glShadeModel(GL_SMOOTH);
		}
		else {
			FlatShaded = 1;
			glShadeModel(GL_FLAT);
		}
		glutPostRedisplay();
		break;

		// *와이어 프레임 토글링
	case 'w':
		if (Wireframed) {
			Wireframed = 0;
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		else {
			Wireframed = 1;
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		glutPostRedisplay();
		break;
	}
}

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// *마우스의 움직임에 따라 시점변환
	gluLookAt(ViewX * 0.001, ViewY * 0.001, 0.0, 0.0, 0.0, -1.0, 0.0, 1.0, 0.0);

	// *도넛
	glPushMatrix();
	// * x 0.4, y 0.3, z -0.3 이동
	glTranslatef(0.4, 0.2, -0.3);
	glutSolidTorus(0.1, 0.3, 10, 10);
	glPopMatrix();

	// *찻주전자
	glutSolidTeapot(0.2);

	// *찻잔
	glPushMatrix();
	// * x -0.5, y -0.1 이동
	glTranslatef(-0.5, -0.1, 0);
	glutSolidTeacup(0.2);
	glPopMatrix();

	// *원
	glPushMatrix();
	// * x 0.5, y -0.05 이동
	glTranslatef(0.5, -0.05, 0);
	glutSolidSphere(0.1, 10, 10);
	glPopMatrix();

	// *책상 위치 이동 y -0.2
	glTranslatef(0, -0.2, 0);

	glBegin(GL_QUADS);
	//* Front
	glVertex3f(-1.0, 0.05, 1.0);
	glVertex3f(-1.0, -0.05, 1.0);
	glVertex3f(1.0, -0.05, 1.0);
	glVertex3f(1.0, 0.05, 1.0);

	//* Back
	glVertex3f(1.0, 0.05, -1.0);
	glVertex3f(1.0, -0.05, -1.0);
	glVertex3f(-1.0, -0.05, -1.0);
	glVertex3f(-1.0, 0.05, -1.0);

	//* Left
	glVertex3f(-1.0, 0.05, -1.0);
	glVertex3f(-1.0, -0.05, -1.0);
	glVertex3f(-1.0, -0.05, 1.0);
	glVertex3f(-1.0, 0.05, 1.0);

	//* Right
	glVertex3f(1.0, 0.05, 1.0);
	glVertex3f(1.0, -0.05, 1.0);
	glVertex3f(1.0, -0.05, -1.0);
	glVertex3f(1.0, 0.05, -1.0);

	//* Top
	glVertex3f(-1.0, 0.05, 1.0);
	glVertex3f(1.0, 0.05, 1.0);
	glVertex3f(1.0, 0.05, -1.0);
	glVertex3f(-1.0, 0.05, -1.0);

	//* Bottom
	glVertex3f(1.0, -0.05, 1.0);
	glVertex3f(-1.0, -0.05, 1.0);
	glVertex3f(-1.0, -0.05, -1.0);
	glVertex3f(1.0, -0.05, -1.0);
	glEnd();
	
	//* x축 90 회전
	glRotatef(90, 1.0, 0, 0);
	//* 책상 받침
	glutSolidCylinder(0.1, 0.6, 10, 10);

	//* 바닥
	glPushMatrix();
	//* z 0.6 이동
	glTranslatef(0, 0, 0.6);
	glBegin(GL_QUADS);
	//* 바닥 크기 설정
	glVertex3f(-3.0, 3.0, 0.0);
	glVertex3f(3.0, 3.0, 0.0);
	glVertex3f(3.0, -3.0, 0.0);
	glVertex3f(-3.0, -3.0, 0.0);
	glEnd();
	glPopMatrix();

	glFlush();
}


void MyReshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("OpenGL Sample Drawing");

	glClearColor(0.4, 0.4, 0.4, 0.0);
	InitLight();
	glutDisplayFunc(MyDisplay);
	glutKeyboardFunc(MyKeyboard);
	glutMotionFunc(MyMouseMove);
	glutReshapeFunc(MyReshape);
	glutMainLoop();
}