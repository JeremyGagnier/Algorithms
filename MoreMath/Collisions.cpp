#include "Collisions.h"
#include <ctime>
#include <chrono>
#include <cstdlib>

using namespace std;

double randrange(double min, double max)
{
	return(min + static_cast<double>(rand()) / static_cast<double>(RAND_MAX) * (max - min));
}

int randrange(int min, int max)
{
	return(min + rand() % (max - min + 1));
}

int main()
{
	srand(static_cast<unsigned>(time(0)));

	Vector p0;
	Vector p1(1, 2);
	Vector p2(5, -2);
	Vector p3(0, 0);
	Vector p4(-1, 4);
	Vector p5(2, 2);
	Vector p6(5, 4);
	Vector p7(2, 2);
	Vector p8(-4, -2);
	Line l0;
	Line l1(Vector(0, 0), Vector(2, 0));
	Line l2(Vector(1, -1), Vector(0, 2));
	Line l3(Vector(2, -1), Vector(0, 2));
	Line l4(Vector(1, 1), Vector(2.5, -1));
	Line l5(Vector(-1, -1), Vector(2, 2));
	Line l6(Vector(0, 0), Vector(1, 1));
	Line l7(Vector(5, 1), Vector(0, 4));
	Sphere s0;
	Sphere s1(Vector(5,-4), 4);
	Sphere s2(Vector(-3,1), 2);
	Sphere s3(Vector(-5,-5), 6);
	Sphere s4(Vector(1,-2), 1);
	Sphere s5(Vector(1, -0.9), 1);
	Sphere s6(Vector(4.6, -0.9), 3);
	Sphere s7(Vector(0, 1), 0.9);
	Sphere s8(Vector(0, 1), 0.7);
	Sphere s9(Vector(1, 2), 0.9);
	Sphere s10(Vector(5, 4), 1);
	Box b0;
	Box b1(Vector(-2, 5), Vector(1, 2));
	Box b2(Vector(8, 3), Vector(3, 3));
	Box b3(Vector(1, 1), Vector(5, 1));
	Box b4(Vector(-3, -4), Vector(4, 7));
	Box b5(Vector(3, 3), Vector(3, 3));
	Box b6(Vector(-3, -2), Vector(1, 1));
	
	
	cout << StaticLineToLine(l1, l0) << " True" << endl;
	cout << StaticLineToLine(l1, l3) << " True" << endl;
	cout << StaticLineToLine(l1, l4) << " False" << endl;
	cout << StaticLineToLine(l3, l4) << " True" << endl;
	cout << StaticPointToLine(p0, l1) << " True" << endl;
	cout << StaticPointToLine(p1, l1) << " False" << endl;
	cout << StaticPointToLine(p3, l5) << " True" << endl;
	cout << StaticPointToLine(p4, l4) << " False" << endl;
	cout << StaticCircleToRect(s1, b1) << " False" << endl;
	cout << StaticCircleToRect(s2, b2) << " False" << endl;
	cout << StaticCircleToRect(s3, b3) << " False" << endl;
	cout << StaticCircleToRect(s4, b4) << " True" << endl;
	cout << StaticLineToCircle(l1, s5) << " True" << endl;
	cout << StaticLineToCircle(l6, s7) << " True" << endl;
	cout << StaticLineToCircle(l1, s8) << " False" << endl;
	cout << StaticLineToCircle(l2, s9) << " False" << endl;
	cout << DynamicPointToPoint(p0, p0, p1, p2) << " True" << endl;
	cout << DynamicPointToPoint(p5, p6, p7, p8) << " True" << endl;
	cout << DynamicPointToPoint(p1, p2, p3, p4) << " False" << endl;
	cout << DynamicPointToPoint(p4, p3, p2, p1) << " False" << endl;
	cout << DynamicPointToLine(p0, l0, p1, p2) << " True" << endl;
	cout << DynamicPointToLine(p5, l7, p7, p8) << " True" << endl;
	cout << DynamicPointToLine(p1, l2, p3, p4) << " False" << endl;
	cout << DynamicPointToLine(p4, l3, p2, p1) << " True" << endl;
	cout << DynamicPointToCircle(p0, s0, p1, p2) << " True" << endl;
	cout << DynamicPointToCircle(p5, s10, p7, p8) << " True" << endl;
	cout << DynamicPointToCircle(p1, s1, p3, p4) << " False" << endl;
	cout << DynamicPointToCircle(p4, s2, p2, p1) << " False" << endl;
	cout << DynamicPointToRect(p0, b0, p1, p2) << " True" << endl;
	cout << DynamicPointToRect(p5, b5, p7, p8) << " True" << endl;
	cout << DynamicPointToRect(p1, b1, p3, p4) << " False" << endl;
	cout << DynamicPointToRect(p4, b2, p2, p1) << " False" << endl;
	cout << DynamicLineToLine(l0, l0, p1, p2) << " True" << endl;
	cout << DynamicLineToLine(l1, l7, p7, p8) << " True" << endl;
	cout << DynamicLineToLine(l1, l4, p3, p4) << " False" << endl;
	cout << DynamicLineToLine(l7, l3, p2, p1) << " False" << endl;
	cout << DynamicLineToCircle(l0, s0, p1, p2) << " True" << endl;
	cout << DynamicLineToCircle(l1, s10, p7, p8) << " True" << endl;
	cout << DynamicLineToCircle(l1, s4, p5, p4) << " False" << endl;
	cout << DynamicLineToCircle(l7, s3, p2, p1) << " False" << endl;
	cout << DynamicLineToRect(l0, b0, p1, p2) << " True" << endl;
	cout << DynamicLineToRect(l1, b5, p7, p8) << " True" << endl;
	cout << DynamicLineToRect(l1, b6, p5, p4) << " False" << endl;
	cout << DynamicLineToRect(l7, b1, p2, p1) << " False" << endl;
	cout << DynamicCircleToCircle(s0, s0, p1, p2) << " True" << endl;
	cout << DynamicCircleToCircle(s9, s10, p7, p8) << " True" << endl;
	cout << DynamicCircleToCircle(s1, s2, p3, p4) << " False" << endl;
	cout << DynamicCircleToCircle(s4, s10, p2, p1) << " False" << endl;
	cout << DynamicCircleToRect(s0, b0, p1, p2) << " True" << endl;
	cout << DynamicCircleToRect(s9, b5, p7, p8) << " True" << endl;
	cout << DynamicCircleToRect(s1, b2, p3, p4) << " False" << endl;
	cout << DynamicCircleToRect(s4, b3, p2, p1) << " False" << endl;
	cout << DynamicRectToRect(b0, b0, p1, p2) << " True" << endl;
	cout << DynamicRectToRect(b6, b5, p7, p8) << " True" << endl;
	cout << DynamicRectToRect(b1, b2, p3, p4) << " False" << endl;
	cout << DynamicRectToRect(b6, b1, p2, p1) << " False" << endl;
	
	/*
	chrono::duration<double> diff;
	chrono::high_resolution_clock::time_point end;
	chrono::high_resolution_clock::time_point start;
	const int LIST_SIZES = 2800;
	const int BIG_LOOP_TIMES = 10;
	int numCollisions;
	Vector velocities1[LIST_SIZES];
	Vector velocities2[LIST_SIZES];
	Vector points1[LIST_SIZES];
	Vector points2[LIST_SIZES];
	Line lines1[LIST_SIZES];
	Line lines2[LIST_SIZES];
	Sphere spheres1[LIST_SIZES];
	Sphere spheres2[LIST_SIZES];
	Box boxes1[LIST_SIZES];
	Box boxes2[LIST_SIZES];
	
	double sppTime = 0;
	double splTime = 0;
	double spcTime = 0;
	double sprTime = 0;
	double sllTime = 0;
	double slcTime = 0;
	double slrTime = 0;
	double sccTime = 0;
	double scrTime = 0;
	double srrTime = 0;
	double dppTime = 0;
	double dplTime = 0;
	double dpcTime = 0;
	double dprTime = 0;
	double dllTime = 0;
	double dlcTime = 0;
	double dlrTime = 0;
	double dccTime = 0;
	double dcrTime = 0;
	double drrTime = 0;

	for(int bigLoops = 0; bigLoops < BIG_LOOP_TIMES; ++bigLoops)
	{
		system("cls");

		numCollisions = 0;
		for(int i = 0; i < LIST_SIZES; ++i)
		{
			points1[i] = Vector(randrange(-9, 9), randrange(-8, 8));
			points2[i] = Vector(randrange(-9, 9), randrange(-8, 8));
		}

		start = chrono::high_resolution_clock::now();
	
		for(int i = 0; i < LIST_SIZES; ++i)
		{
			for(int j = 0; j < LIST_SIZES; ++j)
			{
				numCollisions += (int)StaticPointToPoint(points1[i], points2[j]);
			}
		}

		end = chrono::high_resolution_clock::now();
		diff = chrono::duration_cast<chrono::duration<double> >(end - start);
		cout << diff.count() << " Static Point-Point " << numCollisions << endl;
		sppTime += diff.count();

	
		numCollisions = 0;
		for(int i = 0; i < LIST_SIZES; ++i)
		{
			points1[i] = Vector(randrange(-100, 100), randrange(-100, 100));
			lines1[i] = Line(Vector(randrange(-90, 90), randrange(-90, 90)),
							Vector(randrange(-8, 8), randrange(-8, 8)));
		}

		start = chrono::high_resolution_clock::now();
	
		for(int i = 0; i < LIST_SIZES; ++i)
		{
			for(int j = 0; j < LIST_SIZES; ++j)
			{
				numCollisions += (int)StaticPointToLine(points1[i], lines1[j]);
			}
		}
		end = chrono::high_resolution_clock::now();
		diff = chrono::duration_cast<chrono::duration<double> >(end - start);
		cout << diff.count() << " Static Point-Line " << numCollisions << endl;
		splTime += diff.count();
	
	
		numCollisions = 0;
		for(int i = 0; i < LIST_SIZES; ++i)
		{
			points1[i] = Vector(randrange(-100, 100), randrange(-100, 100));
			spheres1[i] = Sphere(Vector(randrange(-100.0, 100.0), randrange(-100.0, 100.0)), randrange(1.0, 10.0));
		}

		start = chrono::high_resolution_clock::now();
	
		for(int i = 0; i < LIST_SIZES; ++i)
		{
			for(int j = 0; j < LIST_SIZES; ++j)
			{
				numCollisions += (int)StaticPointToCircle(points1[i], spheres1[j]);
			}
		}
		end = chrono::high_resolution_clock::now();
		diff = chrono::duration_cast<chrono::duration<double> >(end - start);
		cout << diff.count() << " Static Point-Circle " << numCollisions << endl;
		spcTime += diff.count();
	
	
		numCollisions = 0;
		for(int i = 0; i < LIST_SIZES; ++i)
		{
			points1[i] = Vector(randrange(-100, 100), randrange(-100, 100));
			boxes1[i] = Box(Vector(randrange(-100.0, 100.0), randrange(-100.0, 100.0)), 
							Vector(randrange(5.0, 17.0), randrange(5.0, 17.0)));
		}

		start = chrono::high_resolution_clock::now();
	
		for(int i = 0; i < LIST_SIZES; ++i)
		{
			for(int j = 0; j < LIST_SIZES; ++j)
			{
				numCollisions += (int)StaticPointToRect(points1[i], boxes1[j]);
			}
		}
		end = chrono::high_resolution_clock::now();
		diff = chrono::duration_cast<chrono::duration<double> >(end - start);
		cout << diff.count() << " Static Point-Rect " << numCollisions << endl;
		sprTime += diff.count();
	
	
		numCollisions = 0;
		for(int i = 0; i < LIST_SIZES; ++i)
		{
			lines1[i] = Line(Vector(randrange(-100.0, 100.0), randrange(-100.0, 100.0)), 
							 Vector(randrange(-18.0, 18.0), randrange(-18.0, 18.0)));
			lines2[i] = Line(Vector(randrange(-100.0, 100.0), randrange(-100.0, 100.0)), 
							 Vector(randrange(-18.0, 18.0), randrange(-18.0, 18.0)));
		}

		start = chrono::high_resolution_clock::now();
	
		for(int i = 0; i < LIST_SIZES; ++i)
		{
			for(int j = 0; j < LIST_SIZES; ++j)
			{
				numCollisions += (int)StaticLineToLine(lines1[i], lines2[j]);
			}
		}
		end = chrono::high_resolution_clock::now();
		diff = chrono::duration_cast<chrono::duration<double> >(end - start);
		cout << diff.count() << " Static Line-Line " << numCollisions << endl;
		sllTime += diff.count();
	
	
		numCollisions = 0;
		for(int i = 0; i < LIST_SIZES; ++i)
		{
			lines1[i] = Line(Vector(randrange(-100.0, 100.0), randrange(-100.0, 100.0)), 
							 Vector(randrange(-15.0, 15.0), randrange(-15.0, 15.0)));
			spheres1[i] = Sphere(Vector(randrange(-100.0, 100.0), randrange(-100.0, 100.0)), randrange(1.0, 9.0));
		}

		start = chrono::high_resolution_clock::now();
	
		for(int i = 0; i < LIST_SIZES; ++i)
		{
			for(int j = 0; j < LIST_SIZES; ++j)
			{
				numCollisions += (int)StaticLineToCircle(lines1[i], spheres1[j]);
			}
		}
		end = chrono::high_resolution_clock::now();
		diff = chrono::duration_cast<chrono::duration<double> >(end - start);
		cout << diff.count() << " Static Line-Circle " << numCollisions << endl;
		slcTime += diff.count();
	
	
		numCollisions = 0;
		for(int i = 0; i < LIST_SIZES; ++i)
		{
			lines1[i] = Line(Vector(randrange(-100.0, 100.0), randrange(-100.0, 100.0)), 
							 Vector(randrange(-15.0, 15.0), randrange(-15.0, 15.0)));
			boxes1[i] = Box(Vector(randrange(-100.0, 100.0), randrange(-100.0, 100.0)), 
							Vector(randrange(2.0, 9.2), randrange(2.0, 9.2)));
		}

		start = chrono::high_resolution_clock::now();
	
		for(int i = 0; i < LIST_SIZES; ++i)
		{
			for(int j = 0; j < LIST_SIZES; ++j)
			{
				numCollisions += (int)StaticLineToRect(lines1[i], boxes1[j]);
			}
		}
		end = chrono::high_resolution_clock::now();
		diff = chrono::duration_cast<chrono::duration<double> >(end - start);
		cout << diff.count() << " Static Line-Rect " << numCollisions << endl;
		slrTime += diff.count();
	
	
		numCollisions = 0;
		for(int i = 0; i < LIST_SIZES; ++i)
		{
			spheres1[i] = Sphere(Vector(randrange(-100.0, 100.0), randrange(-100.0, 100.0)), randrange(1.0, 5.0));
			spheres2[i] = Sphere(Vector(randrange(-100.0, 100.0), randrange(-100.0, 100.0)), randrange(1.0, 4.5));
		}

		start = chrono::high_resolution_clock::now();
	
		for(int i = 0; i < LIST_SIZES; ++i)
		{
			for(int j = 0; j < LIST_SIZES; ++j)
			{
				numCollisions += (int)StaticCircleToCircle(spheres1[i], spheres2[j]);
			}
		}
		end = chrono::high_resolution_clock::now();
		diff = chrono::duration_cast<chrono::duration<double> >(end - start);
		cout << diff.count() << " Static Circle-Circle " << numCollisions << endl;
		sccTime += diff.count();
	
	
		numCollisions = 0;
		for(int i = 0; i < LIST_SIZES; ++i)
		{
			spheres1[i] = Sphere(Vector(randrange(-100.0, 100.0), randrange(-100.0, 100.0)), randrange(1.0, 5.0));
			boxes1[i] = Box(Vector(randrange(-100.0, 100.0), randrange(-100.0, 100.0)), 
							Vector(randrange(2.0, 8.0), randrange(2.0, 8.0)));
		}

		start = chrono::high_resolution_clock::now();
	
		for(int i = 0; i < LIST_SIZES; ++i)
		{
			for(int j = 0; j < LIST_SIZES; ++j)
			{
				numCollisions += (int)StaticCircleToRect(spheres1[i], boxes1[j]);
			}
		}
		end = chrono::high_resolution_clock::now();
		diff = chrono::duration_cast<chrono::duration<double> >(end - start);
		cout << diff.count() << " Static Circle-Rect " << numCollisions << endl;
		scrTime += diff.count();
	
	
		numCollisions = 0;
		for(int i = 0; i < LIST_SIZES; ++i)
		{
			boxes1[i] = Box(Vector(randrange(-100.0, 100.0), randrange(-100.0, 100.0)), 
							Vector(randrange(2.0, 9.0), randrange(2.0, 9.0)));
			boxes2[i] = Box(Vector(randrange(-100.0, 100.0), randrange(-100.0, 100.0)), 
							Vector(randrange(2.0, 9.0), randrange(2.0, 9.0)));
		}

		start = chrono::high_resolution_clock::now();
	
		for(int i = 0; i < LIST_SIZES; ++i)
		{
			for(int j = 0; j < LIST_SIZES; ++j)
			{
				numCollisions += (int)StaticRectToRect(boxes1[i], boxes2[j]);
			}
		}
		end = chrono::high_resolution_clock::now();
		diff = chrono::duration_cast<chrono::duration<double> >(end - start);
		cout << diff.count() << " Static Rect-Rect " << numCollisions << endl;
		srrTime += diff.count();
	
	
		numCollisions = 0;
		for(int i = 0; i < LIST_SIZES; ++i)
		{
			points1[i] = Vector(randrange(-100, 100), randrange(-100, 100));
			points2[i] = Vector(randrange(-100, 100), randrange(-100, 100));
			velocities1[i] = Vector(randrange(-10, 10), randrange(-10, 10));
			velocities2[i] = Vector(randrange(-10, 10), randrange(-10, 10));
		}

		start = chrono::high_resolution_clock::now();
	
		for(int i = 0; i < LIST_SIZES; ++i)
		{
			for(int j = 0; j < LIST_SIZES; ++j)
			{
				numCollisions += (int)DynamicPointToPoint(points1[i], points2[j], velocities1[i], velocities2[j]);
			}
		}
		end = chrono::high_resolution_clock::now();
		diff = chrono::duration_cast<chrono::duration<double> >(end - start);
		cout << diff.count() << " Dynamic Point-Point " << numCollisions << endl;
		dppTime += diff.count();
	
	
		numCollisions = 0;
		for(int i = 0; i < LIST_SIZES; ++i)
		{
			points1[i] = Vector(randrange(-100.0, 100.0), randrange(-100.0, 100.0));
			lines1[i] = Line(Vector(randrange(-100.0, 100.0), randrange(-100.0, 100.0)),
							 Vector(randrange(-25.0, 25.0), randrange(-25.0, 25.0)));
			velocities1[i] = Vector(randrange(-10.0, 10.0), randrange(-10.0, 10.0));
			velocities2[i] = Vector(randrange(-10.0, 10.0), randrange(-10.0, 10.0));
		}

		start = chrono::high_resolution_clock::now();
	
		for(int i = 0; i < LIST_SIZES; ++i)
		{
			for(int j = 0; j < LIST_SIZES; ++j)
			{
				numCollisions += (int)DynamicPointToLine(points1[i], lines1[j], velocities1[i], velocities2[j]);
			}
		}
		end = chrono::high_resolution_clock::now();
		diff = chrono::duration_cast<chrono::duration<double> >(end - start);
		cout << diff.count() << " Dynamic Point-Line " << numCollisions << endl;
		dplTime += diff.count();
	
	
		numCollisions = 0;
		for(int i = 0; i < LIST_SIZES; ++i)
		{
			points1[i] = Vector(randrange(-100.0, 100.0), randrange(-100.0, 100.0));
			spheres1[i] = Sphere(Vector(randrange(-100.0, 100.0), randrange(-100.0, 100.0)),randrange(3.0, 10.0));
			velocities1[i] = Vector(randrange(-10.0, 10.0), randrange(-10.0, 10.0));
			velocities2[i] = Vector(randrange(-10.0, 10.0), randrange(-10.0, 10.0));
		}

		start = chrono::high_resolution_clock::now();
	
		for(int i = 0; i < LIST_SIZES; ++i)
		{
			for(int j = 0; j < LIST_SIZES; ++j)
			{
				numCollisions += (int)DynamicPointToCircle(points1[i], spheres1[j], velocities1[i], velocities2[j]);
			}
		}
		end = chrono::high_resolution_clock::now();
		diff = chrono::duration_cast<chrono::duration<double> >(end - start);
		cout << diff.count() << " Dynamic Point-Circle " << numCollisions << endl;
		dpcTime += diff.count();
	
	
		numCollisions = 0;
		for(int i = 0; i < LIST_SIZES; ++i)
		{
			points1[i] = Vector(randrange(-100.0, 100.0), randrange(-100.0, 100.0));
			boxes1[i] = Box(Vector(randrange(-100.0, 100.0), randrange(-100.0, 100.0)),
							Vector(randrange(3.0, 11.0), randrange(3.0, 11.0)));
			velocities1[i] = Vector(randrange(-10.0, 10.0), randrange(-10.0, 10.0));
			velocities2[i] = Vector(randrange(-10.0, 10.0), randrange(-10.0, 10.0));
		}

		start = chrono::high_resolution_clock::now();
	
		for(int i = 0; i < LIST_SIZES; ++i)
		{
			for(int j = 0; j < LIST_SIZES; ++j)
			{
				numCollisions += (int)DynamicPointToRect(points1[i], boxes1[j], velocities1[i], velocities2[j]);
			}
		}
		end = chrono::high_resolution_clock::now();
		diff = chrono::duration_cast<chrono::duration<double> >(end - start);
		cout << diff.count() << " Dynamic Point-Rect " << numCollisions << endl;
		dprTime += diff.count();
	
	
		numCollisions = 0;
		for(int i = 0; i < LIST_SIZES; ++i)
		{
			lines1[i] = Line(Vector(randrange(-100.0, 100.0), randrange(-100.0, 100.0)),
							 Vector(randrange(-10.0, 10.0), randrange(-10.0, 10.0)));
			lines2[i] = Line(Vector(randrange(-100.0, 100.0), randrange(-100.0, 100.0)),
							 Vector(randrange(-10.0, 10.0), randrange(-10.0, 10.0)));
			velocities1[i] = Vector(randrange(-10.0, 10.0), randrange(-10.0, 10.0));
			velocities2[i] = Vector(randrange(-10.0, 10.0), randrange(-10.0, 10.0));
		}

		start = chrono::high_resolution_clock::now();
	
		for(int i = 0; i < LIST_SIZES; ++i)
		{
			for(int j = 0; j < LIST_SIZES; ++j)
			{
				numCollisions += (int)DynamicLineToLine(lines1[i], lines2[j], velocities1[i], velocities2[j]);
			}
		}
		end = chrono::high_resolution_clock::now();
		diff = chrono::duration_cast<chrono::duration<double> >(end - start);
		cout << diff.count() << " Dynamic Line-Line " << numCollisions << endl;
		dllTime += diff.count();
	
	
		numCollisions = 0;
		for(int i = 0; i < LIST_SIZES; ++i)
		{
			lines1[i] = Line(Vector(randrange(-100.0, 100.0), randrange(-100.0, 100.0)),
							 Vector(randrange(-10.0, 10.0), randrange(-10.0, 10.0)));
			spheres1[i] = Sphere(Vector(randrange(-100.0, 100.0), randrange(-100.0, 100.0)),randrange(0.5, 4.0));
			velocities1[i] = Vector(randrange(-10.0, 10.0), randrange(-10.0, 10.0));
			velocities2[i] = Vector(randrange(-10.0, 10.0), randrange(-10.0, 10.0));
		}

		start = chrono::high_resolution_clock::now();
	
		for(int i = 0; i < LIST_SIZES; ++i)
		{
			for(int j = 0; j < LIST_SIZES; ++j)
			{
				numCollisions += (int)DynamicLineToCircle(lines1[i], spheres1[j], velocities1[i], velocities2[j]);
			}
		}
		end = chrono::high_resolution_clock::now();
		diff = chrono::duration_cast<chrono::duration<double> >(end - start);
		cout << diff.count() << " Dynamic Line-Circle " << numCollisions << endl;
		dlcTime += diff.count();
	
	
		numCollisions = 0;
		for(int i = 0; i < LIST_SIZES; ++i)
		{
			lines1[i] = Line(Vector(randrange(-100.0, 100.0), randrange(-100.0, 100.0)),
							 Vector(randrange(-10.0, 10.0), randrange(-10.0, 10.0)));
			boxes1[i] = Box(Vector(randrange(-100.0, 100.0), randrange(-100.0, 100.0)),
							Vector(randrange(1.5, 5.0), randrange(1.5, 5.0)));
			velocities1[i] = Vector(randrange(-10.0, 10.0), randrange(-10.0, 10.0));
			velocities2[i] = Vector(randrange(-10.0, 10.0), randrange(-10.0, 10.0));
		}

		start = chrono::high_resolution_clock::now();
	
		for(int i = 0; i < LIST_SIZES; ++i)
		{
			for(int j = 0; j < LIST_SIZES; ++j)
			{
				numCollisions += (int)DynamicLineToRect(lines1[i], boxes1[j], velocities1[i], velocities2[j]);
			}
		}
		end = chrono::high_resolution_clock::now();
		diff = chrono::duration_cast<chrono::duration<double> >(end - start);
		cout << diff.count() << " Dynamic Line-Rect " << numCollisions << endl;
		dlrTime += diff.count();
	
	
		numCollisions = 0;
		for(int i = 0; i < LIST_SIZES; ++i)
		{
			spheres1[i] = Sphere(Vector(randrange(-100.0, 100.0), randrange(-100.0, 100.0)), randrange(1.0, 3.0));
			spheres2[i] = Sphere(Vector(randrange(-100.0, 100.0), randrange(-100.0, 100.0)), randrange(1.0, 3.0));
			velocities1[i] = Vector(randrange(-10.0, 10.0), randrange(-10.0, 10.0));
			velocities2[i] = Vector(randrange(-10.0, 10.0), randrange(-10.0, 10.0));
		}

		start = chrono::high_resolution_clock::now();
	
		for(int i = 0; i < LIST_SIZES; ++i)
		{
			for(int j = 0; j < LIST_SIZES; ++j)
			{
				numCollisions += (int)DynamicCircleToCircle(spheres1[i], spheres2[j], velocities1[i], velocities2[j]);
			}
		}
		end = chrono::high_resolution_clock::now();
		diff = chrono::duration_cast<chrono::duration<double> >(end - start);
		cout << diff.count() << " Dynamic Circle-Circle " << numCollisions << endl;
		dccTime += diff.count();
	
	
		numCollisions = 0;
		for(int i = 0; i < LIST_SIZES; ++i)
		{
			spheres1[i] = Sphere(Vector(randrange(-100.0, 100.0), randrange(-100.0, 100.0)), randrange(1.0, 3.0));
			boxes1[i] = Box(Vector(randrange(-100.0, 100.0), randrange(-100.0, 100.0)),
							Vector(randrange(1.5, 5.0), randrange(1.5, 5.0)));
			velocities1[i] = Vector(randrange(-10.0, 10.0), randrange(-10.0, 10.0));
			velocities2[i] = Vector(randrange(-10.0, 10.0), randrange(-10.0, 10.0));
		}

		start = chrono::high_resolution_clock::now();
	
		for(int i = 0; i < LIST_SIZES; ++i)
		{
			for(int j = 0; j < LIST_SIZES; ++j)
			{
				numCollisions += (int)DynamicCircleToRect(spheres1[i], boxes1[j], velocities1[i], velocities2[j]);
			}
		}
		end = chrono::high_resolution_clock::now();
		diff = chrono::duration_cast<chrono::duration<double> >(end - start);
		cout << diff.count() << " Dynamic Circle-Rect " << numCollisions << endl;
		dcrTime += diff.count();
	
	
		numCollisions = 0;
		for(int i = 0; i < LIST_SIZES; ++i)
		{
			boxes1[i] = Box(Vector(randrange(-100.0, 100.0), randrange(-100.0, 100.0)),
							Vector(randrange(1.5, 5.0), randrange(1.5, 5.0)));
			boxes2[i] = Box(Vector(randrange(-100.0, 100.0), randrange(-100.0, 100.0)),
							Vector(randrange(1.5, 5.0), randrange(1.5, 5.0)));
			velocities1[i] = Vector(randrange(-10.0, 10.0), randrange(-10.0, 10.0));
			velocities2[i] = Vector(randrange(-10.0, 10.0), randrange(-10.0, 10.0));
		}

		start = chrono::high_resolution_clock::now();
	
		for(int i = 0; i < LIST_SIZES; ++i)
		{
			for(int j = 0; j < LIST_SIZES; ++j)
			{
				numCollisions += (int)DynamicRectToRect(boxes1[i], boxes2[j], velocities1[i], velocities2[j]);
			}
		}
		end = chrono::high_resolution_clock::now();
		diff = chrono::duration_cast<chrono::duration<double> >(end - start);
		cout << diff.count() << " Dynamic Rect-Rect " << numCollisions << endl;
		drrTime += diff.count();


		while(chrono::duration_cast<chrono::duration<double> >(chrono::high_resolution_clock::now() - end).count() < 1){}
	}
	
	cout << sppTime / BIG_LOOP_TIMES << endl;
	cout << splTime / BIG_LOOP_TIMES << endl;
	cout << spcTime / BIG_LOOP_TIMES << endl;
	cout << sprTime / BIG_LOOP_TIMES << endl;
	cout << sllTime / BIG_LOOP_TIMES << endl;
	cout << slcTime / BIG_LOOP_TIMES << endl;
	cout << slrTime / BIG_LOOP_TIMES << endl;
	cout << sccTime / BIG_LOOP_TIMES << endl;
	cout << scrTime / BIG_LOOP_TIMES << endl;
	cout << srrTime / BIG_LOOP_TIMES << endl;
	cout << dppTime / BIG_LOOP_TIMES << endl;
	cout << dplTime / BIG_LOOP_TIMES << endl;
	cout << dpcTime / BIG_LOOP_TIMES << endl;
	cout << dprTime / BIG_LOOP_TIMES << endl;
	cout << dllTime / BIG_LOOP_TIMES << endl;
	cout << dlcTime / BIG_LOOP_TIMES << endl;
	cout << dlrTime / BIG_LOOP_TIMES << endl;
	cout << dccTime / BIG_LOOP_TIMES << endl;
	cout << dcrTime / BIG_LOOP_TIMES << endl;
	cout << drrTime / BIG_LOOP_TIMES << endl;
	*/

	system("pause");

	return 0;
}
