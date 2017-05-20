//
//  main.cpp
//  inheritance_lection
//
//  Created by Vadim on 25.03.17.
//  Copyright © 2017 Vadim. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;

struct model
{
    //
};

struct vec3 {
    int x, y, z;
    
    vec3(int x = 0, int y = 0, int z = 0)
    : x(x), y(y), z(z)
    {}
    
    vec3 operator + (vec3 b) const
    {
        return vec3(x + b.x, y + b.y, z + b.z);
    }
    
    vec3 operator - (vec3 b) const
    {
        return vec3(x - b.x, y - b.y, z - b.z);
    }
    
};

struct GameObject
{
    vec3 position;
    vec3 velocity;
    model* model;
    
    virtual void rendor()
    {
        cerr << "rendor in GO\n";
    }
    
    void update()
    {
        cerr << "update in GO\n";
    }
};

struct player : GameObject
{
    string name = "player1";
    
    void rendor()
    {
        cerr << "rendor in player\n";
    }
    
    void update()
    {
        cerr << "update in player\n";
    }
    
};

//return std::move x;



int main(int argc, const char * argv[]) {
    GameObject a;
    player b;
    
    GameObject& ra = a;
    GameObject& rb = b;
    
    a.rendor();
    b.rendor();
    ra.rendor();
    rb.rendor();
    
    cerr << endl;

    a.update();
    b.update();
    ra.update();
    rb.update();
    return 0;
}
