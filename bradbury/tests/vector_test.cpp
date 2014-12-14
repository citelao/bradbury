//
//  vector_test.cpp
//  bradbury
//
//  Created by Ben Stolovitz on 12/14/14.
//  Copyright (c) 2014 citelao. All rights reserved.
//

#include "vector.h"

TEST_CASE("vectors can be created with proper stats") {
    SECTION("integer static example") {
        Vector v = Vector(4, 5, 6);
        REQUIRE(v.x() == 4);
        REQUIRE(v.y() == 5);
        REQUIRE(v.z() == 6);
    }
    
    SECTION("integer dynamic example") {
        int x = rand() % 100;
        int y = rand() % 100;
        int z = rand() % 100;
        Vector v = Vector(x, y, z);
        REQUIRE(v.x() == x);
        REQUIRE(v.y() == y);
        REQUIRE(v.z() == z);
    }
    
    SECTION("double static example") {
        Vector v = Vector(4.2, 5.2, 6.2);
        REQUIRE(v.x() == 4.2);
        REQUIRE(v.y() == 5.2);
        REQUIRE(v.z() == 6.2);
    }
    
    SECTION("one static number") {
        double a = 4;
        Vector v = Vector(a);
        REQUIRE(v.x() == a);
        REQUIRE(v.y() == a);
        REQUIRE(v.z() == a);
    }
    
    SECTION("one dynamic number") {
        double a = rand() % 100;
        Vector v = Vector(a);
        REQUIRE(v.x() == a);
        REQUIRE(v.y() == a);
        REQUIRE(v.z() == a);
    }
}

TEST_CASE("vectors can do math on each other") {
    int ax = rand() % 100;
    int ay = rand() % 100;
    int az = rand() % 100;
    Vector a = Vector(ax, ay, az);
    
    int bx = rand() % 100;
    int by = rand() % 100;
    int bz = rand() % 100;
    Vector b = Vector(bx, by, bz);
    
    SECTION("can add") {
        Vector v = a + b;
        Vector w = b + a;
        
        REQUIRE(v == w);
        REQUIRE(v.x() == ax + bx);
        REQUIRE(v.y() == ay + by);
        REQUIRE(v.z() == az + bz);
    }
    
    SECTION("can subtract") {
        Vector v = a - b;
        Vector w = b - a;
        
        REQUIRE(v != w);
        REQUIRE(v.x() == ax - bx);
        REQUIRE(v.y() == ay - by);
        REQUIRE(v.z() == az - bz);
        
        REQUIRE(w.x() == bx - ax);
        REQUIRE(w.y() == by - ay);
        REQUIRE(w.z() == bz - az);
    }
    
    SECTION("can negate") {
        Vector nega = -a;
        
        REQUIRE(a.x() == -nega.x());
        REQUIRE(a.y() == -nega.y());
        REQUIRE(a.z() == -nega.z());
    }
    
    SECTION("can static dot product") {
        double dot = Vector(4, 5, 6) * Vector(7, 8, 9);
        
        REQUIRE(dot == 4 * 7 + 5 * 8 + 6 * 9);
    }
    
    SECTION("can dynamic dot product") {
        double ab = a * b;
        double ba = b * a;
        
        // * is an alias for dot
        double bdota = b.dot(a);
        
        REQUIRE(ab == ba);
        REQUIRE(ab == bdota);
        REQUIRE(ab == a.x() * b.x() +
                    a.y() * b.y() +
                    a.z() * b.z());
    }
    
    SECTION("can static cross product") {
        Vector cross = Vector(4, 5, 6).cross(Vector(7, 8, 9));
        
        REQUIRE(cross.x() == 5 * 9 - 6 * 8);
        REQUIRE(cross.y() == - 4 * 9 + 6 * 7);
        REQUIRE(cross.z() == 4 * 8 - 5 * 7);
    }
    
    SECTION("can dynamic cross product") {
        Vector ab = a.cross(b);
        Vector ba = b.cross(a);
        
        REQUIRE(ab == -ba);
        REQUIRE(ab.x() == ay * bz - by * az);
        REQUIRE(ab.y() == - ax * bz + bx * az);
        REQUIRE(ab.z() == ax * by - bx * ay);
    }
}

TEST_CASE("vectors can do math with numbers") {
    int x = rand() % 100;
    int y = rand() % 100;
    int z = rand() % 100;
    Vector v = Vector(x, y, z);
    double m = ((double)(rand() % 100)) / 10;
    
    SECTION("can multiply") {
        Vector vm = v * m;
        Vector mv = m * v;
        
        REQUIRE(vm == mv);
        REQUIRE(vm.x() == x * m);
        REQUIRE(vm.y() == y * m);
        REQUIRE(vm.z() == z * m);
    }
    
    SECTION("can divide") {
        Vector vm = v / m;
        
        REQUIRE(vm.x() == x / m);
        REQUIRE(vm.y() == y / m);
        REQUIRE(vm.z() == z / m);
    }
}

