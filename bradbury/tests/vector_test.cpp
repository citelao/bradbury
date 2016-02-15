//
//  vector_test.cpp
//  bradbury
//
//  Created by Ben Stolovitz on 12/14/14.
//  Copyright (c) 2014 citelao. All rights reserved.
//

#include "vector.h"
#include <vector>


TEST_CASE("vectors can be created with proper stats", "[vector]") {
    std::vector<double> traditionalStaticBase = {4, 6, 10, 12};
    std::vector<Vector<4>> staticVectors = {
        Vector<4>(4, 6, 10, 12),        // standard instantiation
        {4, 6, 10, 12},                 // list instantiation
        traditionalStaticBase           // std::vector instantiation
    };
    
    double dx = rand() % 10000 / 100.0;
    double dy = rand() % 10000 / 100.0;
    double dz = rand() % 10000 / 100.0;
    double dt = rand() % 10000 / 100.0;
    std::vector<double> traditionalDynamicBase = {dx, dy, dz, dt};
    std::vector<Vector<4>> dynamicVectors = {
        Vector<4>(dx, dy, dz, dt),        // standard instantiation
        {dx, dy, dz, dt},                 // list instantiation
        traditionalDynamicBase            // std::vector instantiation
    };
    
    SECTION("special dimensions init") {
        Vector<1> d1(1);
        Vector<2> d2(1, 2);
        Vector<3> d3(1, 2, 3);
        Vector<4> d4(1, 2, 3, 4);
        
        REQUIRE(d1.x() == 1);
        REQUIRE(d2.x() == 1);
        REQUIRE(d3.x() == 1);
        REQUIRE(d4.x() == 1);
        
        REQUIRE_THROWS(d1.y());
        REQUIRE(d2.y() == 2);
        REQUIRE(d3.y() == 2);
        REQUIRE(d4.y() == 2);
        
        REQUIRE_THROWS(d1.z());
        REQUIRE_THROWS(d2.z());
        REQUIRE(d3.z() == 3);
        REQUIRE(d4.z() == 3);
        
        REQUIRE_THROWS(d1.t());
        REQUIRE_THROWS(d2.t());
        REQUIRE_THROWS(d3.t());
        REQUIRE(d4.t() == 4);
    }
    
    SECTION("default value init") {
        Vector<4> v(4.2);
        REQUIRE(v.x() == 4.2);
        REQUIRE(v.y() == 4.2);
        REQUIRE(v.z() == 4.2);
        REQUIRE(v.t() == 4.2);
        
        Vector<4> w;
        REQUIRE(w.x() == 0);
        REQUIRE(w.y() == 0);
        REQUIRE(w.z() == 0);
        REQUIRE(w.t() == 0);
    }
    
    SECTION("wrong size protection") {
        Vector<3> v;
        
        REQUIRE_THROWS_AS((v = {4, 6, 10, 12}), std::length_error);
        REQUIRE_THROWS_AS((v = Vector<4>(4, 6, 10, 12)), std::length_error);
        REQUIRE_THROWS_AS((v = traditionalStaticBase), std::length_error);
        
        std::vector<double> tooSmall = {4, 6};
        REQUIRE_THROWS_AS((v = {4, 6}), std::length_error);
        REQUIRE_THROWS_AS((v = Vector<2>(4, 6)), std::length_error);
        REQUIRE_THROWS_AS((v = tooSmall), std::length_error);
        
        REQUIRE_NOTHROW(v = 4);
    }
    
    SECTION("static example access") {
        for(Vector<4> v : staticVectors) {
            REQUIRE(v.x() == v[0]);
            REQUIRE(v.y() == v[1]);
            REQUIRE(v.z() == v[2]);
            REQUIRE(v.t() == v[3]);
            REQUIRE(v.w() == v[3]);
            
            REQUIRE_THROWS_AS(v[4], std::out_of_range);
            
            REQUIRE(v.x() == 4);
            REQUIRE(v.y() == 6);
            REQUIRE(v.z() == 10);
            REQUIRE(v.t() == 12);
            REQUIRE(v.w() == 12);
        }
        
        Vector<1> v = {0};
        REQUIRE_THROWS_AS(v[1], std::out_of_range);
        REQUIRE_THROWS_AS(v[2], std::out_of_range);
        REQUIRE_THROWS_AS(v[3], std::out_of_range);
        REQUIRE_THROWS_AS(v.y(), std::out_of_range);
        REQUIRE_THROWS_AS(v.z(), std::out_of_range);
        REQUIRE_THROWS_AS(v.t(), std::out_of_range);
        REQUIRE_THROWS_AS(v.w(), std::out_of_range);
    }
    
    SECTION("dynamic example access") {
        for(Vector<4> v : dynamicVectors) {
            REQUIRE(v.x() == v[0]);
            REQUIRE(v.y() == v[1]);
            REQUIRE(v.z() == v[2]);
            REQUIRE(v.t() == v[3]);
            REQUIRE(v.w() == v[3]);
            
            REQUIRE_THROWS_AS(v[4], std::out_of_range);
            
            REQUIRE(v.x() == dx);
            REQUIRE(v.y() == dy);
            REQUIRE(v.z() == dz);
            REQUIRE(v.t() == dt);
            REQUIRE(v.w() == dt);
        }
    }

    SECTION("double static example") {
        Vector<3> v = Vector<3>(4.2, 5.2, 6.2);
        REQUIRE(v.x() == 4.2);
        REQUIRE(v.y() == 5.2);
        REQUIRE(v.z() == 6.2);
    }
}

TEST_CASE("vectors can do math on each other", "[vector]") {
    int ax = rand() % 100;
    int ay = rand() % 100;
    int az = rand() % 100;
    Vector<3> a = {ax, ay, az};
    
    int bx = rand() % 100;
    int by = rand() % 100;
    int bz = rand() % 100;
    Vector<3> b = {bx, by, bz};
    
    double cx = rand() % 10000 / 100.0;
    double cy = rand() % 10000 / 100.0;
    double cz = rand() % 10000 / 100.0;
    double ct = rand() % 10000 / 100.0;
    Vector<4> c = {cx, cy, cz, ct};
    
    double dx = rand() % 10000 / 100.0;
    double dy = rand() % 10000 / 100.0;
    double dz = rand() % 10000 / 100.0;
    double dt = rand() % 10000 / 100.0;
    Vector<4> d = {dx, dy, dz, dt};
    
    SECTION("can add") {
        Vector<3> v = a + b;
        Vector<3> w = b + a;
        
        REQUIRE(v == w);
        REQUIRE(v.x() == ax + bx);
        REQUIRE(v.y() == ay + by);
        REQUIRE(v.z() == az + bz);
        
        Vector<4> x = c + d;
        Vector<4> y = d + c;
        
        REQUIRE(x == y);
        REQUIRE(x.x() == cx + dx);
        REQUIRE(x.y() == cy + dy);
        REQUIRE(x.z() == cz + dz);
        REQUIRE(x.t() == ct + dt);
    }

    SECTION("can subtract") {
        Vector<3> v = a - b;
        Vector<3> w = b - a;
        
        REQUIRE(v != w);
        REQUIRE(v.x() == ax - bx);
        REQUIRE(v.y() == ay - by);
        REQUIRE(v.z() == az - bz);
        
        REQUIRE(w.x() == bx - ax);
        REQUIRE(w.y() == by - ay);
        REQUIRE(w.z() == bz - az);
        
        Vector<4> x = c - d;
        Vector<4> y = d - c;
        
        REQUIRE(x != y);
        REQUIRE(x.x() == cx - dx);
        REQUIRE(x.y() == cy - dy);
        REQUIRE(x.z() == cz - dz);
        REQUIRE(x.t() == ct - dt);
        
        REQUIRE(y.x() == dx - cx);
        REQUIRE(y.y() == dy - cy);
        REQUIRE(y.z() == dz - cz);
        REQUIRE(y.t() == dt - ct);
    }
    
    SECTION("can negate") {
        Vector<3> nega = -a;
        
        REQUIRE(a.x() == -nega.x());
        REQUIRE(a.y() == -nega.y());
        REQUIRE(a.z() == -nega.z());
        
        Vector<4> negc = -c;
        
        REQUIRE(c.x() == -negc.x());
        REQUIRE(c.y() == -negc.y());
        REQUIRE(c.z() == -negc.z());
        REQUIRE(c.t() == -negc.t());
    }
    
    SECTION("can static dot product") {
        double dot = Vector<3>(4, 5, 6) * Vector<3>(7, 8, 9);
        
        REQUIRE(dot == 4 * 7 + 5 * 8 + 6 * 9);
        
        FAIL("need to test dot product in 4 dimensions");
    }
    
//    SECTION("can dynamic dot product") {
//        double ab = a * b;
//        double ba = b * a;
//        
//        // * is an alias for dot
//        double bdota = b.dot(a);
//        
//        REQUIRE(ab == ba);
//        REQUIRE(ab == bdota);
//        REQUIRE(ab == a.x() * b.x() +
//                    a.y() * b.y() +
//                    a.z() * b.z());
//    }
//    
//    SECTION("can static cross product") {
//        Vector cross = Vector(4, 5, 6).cross(Vector(7, 8, 9));
//        
//        REQUIRE(cross.x() == 5 * 9 - 6 * 8);
//        REQUIRE(cross.y() == - 4 * 9 + 6 * 7);
//        REQUIRE(cross.z() == 4 * 8 - 5 * 7);
//    }
//    
//    SECTION("can dynamic cross product") {
//        Vector ab = a.cross(b);
//        Vector ba = b.cross(a);
//        
//        REQUIRE(ab == -ba);
//        REQUIRE(ab.x() == ay * bz - by * az);
//        REQUIRE(ab.y() == - ax * bz + bx * az);
//        REQUIRE(ab.z() == ax * by - bx * ay);
//    }
}
//
//TEST_CASE("vectors can do math with numbers", "[vector]") {
//    int x = rand() % 100;
//    int y = rand() % 100;
//    int z = rand() % 100;
//    Vector v = Vector(x, y, z);
//    double m = ((double)(rand() % 100)) / 10;
//    
//    SECTION("can multiply") {
//        Vector vm = v * m;
//        Vector mv = m * v;
//        
//        REQUIRE(vm == mv);
//        REQUIRE(vm.x() == x * m);
//        REQUIRE(vm.y() == y * m);
//        REQUIRE(vm.z() == z * m);
//    }
//    
//    SECTION("can divide") {
//        Vector vm = v / m;
//        
//        REQUIRE(vm.x() == x / m);
//        REQUIRE(vm.y() == y / m);
//        REQUIRE(vm.z() == z / m);
//    }
//}
//
