#ifndef WALL_H
#define WALL_H

struct wall{
    bool brickWall[8][12] = { false };
    int border[4][2] = {{0, 300}, {300, 600}, {600, 900}, {900, 120}};
};

#endif // WALL_H
