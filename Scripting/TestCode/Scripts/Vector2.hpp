#pragma once

struct Vector2 {
    float x;
    float y;
    
    float Length() {
        return x*x + y*y;
    }

    Vector2 operator + (const Vector2& v) {
        return {x+v.x, y+v.y};
    }
    
    Vector2 operator - (const Vector2& v) {
        return {x-v.x, y-v.y};
    }

    Vector2& operator += (const Vector2& v) {
        
        x += v.x;
        y += v.y;

        return *this;
    }
};

