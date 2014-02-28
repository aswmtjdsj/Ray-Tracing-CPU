#include "Testing.h"

void testing() {

	/*Point f( 0, 0, 0.5), t( 2, 3, 2.3);
    
    Vector ft(f, t);
    ft.print("ft");

    Vector V(1, 1, 1);
    V.print("V");

    (f+V).print("f+V");
    (V+f).print("V+f");
    (f-V).print("f-V");

    (V * 2.).print("V*2");
    (2. * V).print("2*V");

    V += Vector(1, 2, 3);
    V.print("V");

    V = -V;
    V.print("V");

    V.unit().print("V_e");
    printf("%lf\n", V.unit() * V.unit());

    Normal bla;
    bla.print("N_bla");

	Ray ray(f, V);
	ray.print("ray");

	RTdouble tc[3];
	tc[0] = RT_ONE;
	tc[1] = RT_ONE;
	tc[2] = RT_ZERO;
	RGBColor temp(tc), temp_2 = temp + temp;
	temp.print("temp");
	temp_2.print("temp_2");
	temp_2 += temp_2;
	temp_2.print("temp_2 += temp_2");
	temp_2 *= 2.;
	temp_2.print("temp_2 * 2");
	temp_2 -= temp_2 * 0.5;
	temp_2.print("temp_2 -= temp_2 * 0.5");
	temp_2 -= temp_2 / 2;
	temp_2.print("temp_2 -= temp_2 / 2");

	RGBColor test_pow(0.3, 0.4, 0.5);
	test_pow.print("test_pow");
	test_pow = test_pow^2;
	test_pow.print("test_pow^2");

	Plane plane(t, bla);
	plane.print("plane");

	Sphere sphere(t, (RTdouble)1.);
	sphere.print("sphere"); */

	/*Matrix mat;
	mat.print("mat");
	mat.setRow(5);
	mat.setColumn(5);
	for(int i = 0; i < 5; i++) {
		for(int j = 0; j < 5; j++) {
			mat.setValue(i, j, (i*5+j));
		}
	}
	mat.print("mat modified");
	Matrix mat_c(mat);
	mat_c.print("mat_c copied");

	Matrix m1(1, 2), m2(2, 1);
	m1.setValue(0, 0, 3);
	m1.setValue(0, 1, 2);
	m2.setValue(0, 0, 3);
	m2.setValue(1, 0, 2);
	(m2 * m1).print("m1 * m2");

	Point a(0, 0, 1), b(0, 0, 2), c(0, 0, 8);
	((b-a) ^ (c-b)).print("(b-a)^(c-b)");

	Point a1(0, 0, 0), b1(0, 1, 0), c1(1, 0, 0);
	((b1-a1) ^ (c1-a1)).print("(b1-a1)^(c1-a1)");

	Point p[3];
	p[0] = Point(0);
	p[1] = Point(1, 0, 0);
	p[2] = Point(0, 1, 0);
	vector <Point> vp;
	vp.push_back(p[0]);
	vp.push_back(p[1]);
	vp.push_back(p[2]);
	Polygon pp(vp);
	pp.print("polygon test");

	Point tp(0.5, 0.6, 0);
	RTdouble bla = RT_ZERO;
	for(int i = 0; i < 3; i++) {
		bla += acos((p[i] - tp) * (p[(i+1)%3] - tp) / (p[i] - tp).length() / (p[(i+1)%3] - tp).length());
	}
	printf("bla: %.2lf, 2pi: %.2lf\n", bla, 2. * RT_PI);

	Normal pp_n;
	pp.getNormal(pp_n);
	pp_n.print("normal of pp");*/

	World w;
	w.build();
	w.work();
}
