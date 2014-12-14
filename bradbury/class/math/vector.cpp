//
//  vector.cpp
//  bradbury
//
//  Created by Ben Stolovitz on 12/14/14.
//  Copyright (c) 2014 citelao. All rights reserved.
//

#include "vector.h"

double Vector::x() const {
    return _x;
}

double Vector::y() const {
    return _y;
}

double Vector::z() const {
    return _z;
}

bool Vector::operator==(const Vector &nv) const {
    Vector diff = nv - *this;
    
    return (diff.x() < tolerance &&
            diff.y() < tolerance &&
            diff.z() < tolerance);
}

bool Vector::operator!=(const Vector &nv) const {
    return !this->operator==(nv);
}

Vector Vector::operator+(const Vector &nv) const {
    return Vector(x() + nv.x(),
                  y() + nv.y(),
                  z() + nv.z());
}

Vector Vector::operator-(const Vector &nv) const {
    return Vector(x() - nv.x(),
                  y() - nv.y(),
                  z() - nv.z());
}

Vector Vector::operator-() const {
    return Vector(-x(), -y(), -z());
}

double Vector::operator*(const Vector &nv) const {
    return this->dot(nv);
}

double Vector::dot(const Vector &nv) const {
    return x() * nv.x() +
        y() * nv.y() +
        z() * nv.z();
}

Vector Vector::operator*(const double &d) const {
    return Vector(x() * d,
                  y() * d,
                  z() * d);
}

Vector Vector::cross(const Vector &nv) const {
    return Vector(y() * nv.z() - z() * nv.y(),
                  - x() * nv.z() + z() * nv.x(),
                  x() * nv.y() - y() * nv.x());
}

Vector operator*(const double &d, const Vector &v) {
    return v * d;
}

Vector Vector::operator/(const double &d) const {
    return Vector(x() / d,
                  y() / d,
                  z() / d);
}