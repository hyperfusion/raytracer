#include <iostream>
using namespace std;

#include "bmpimage.hh"
#include "scene.hh"

int rnd(int x) {
    // returns from -x to x
    int a = rand() % x;
    return a - x/2;
}

double rndf() {
    // returns from 0 to 1
    return (rand() % 1000) / 1000.0;
}

int main(int argc, char *argv[]) {
    Scene scene(640, 480, Vec3(0, 0, -600), 600);

    Light light1(Vec3(-200, 200, 0), Color(0., 1., 1.));
    scene.add(light1);

    Light light2(Vec3(-200, -200, -100), Color(1., 0., 1.));
    scene.add(light2);

    Sphere s1(Vec3(0, 0, 0), 100);
    s1.material.color = Color(1., 1., 1.);
    s1.name = "s1";    
    scene.add(s1);

    Sphere s2(Vec3(100, 100, -60), 65);
    s2.material.color = Color(0., 0., 1.);
    s2.name = "s2"; 
    scene.add(s2);

    BMPImage bmp("test.bmp", 640, 480);
    scene.render(bmp);
    bmp.write();

    // have a little fun--render n random spheres
    /*srand(time(NULL));
    Scene scene(640, 480, Vec3(0, 0, -100), 500);

    Light light(Vec3(0, 0, 0), Color(1, 1, 1));
    scene.add(light);

    const int num = 30;
    Sphere *spheres = new Sphere[num];
    for (int i = 0; i < num; ++i) {
        spheres[i].center(Vec3(rnd(70), rnd(70), rnd(70)));
        spheres[i].radius(rnd(20));
        spheres[i].material().color().x(rndf());
        spheres[i].material().color().y(rndf());
        spheres[i].material().color().z(rndf());
        scene.add(spheres[i]);
        cout << spheres[i].center() << " " << spheres[i].material().color() << endl;
    }

    BMPImage bmp("test.bmp", 640, 480);
    scene.render(bmp);
    bmp.write();

    delete [] spheres;*/

    return 0;
}
