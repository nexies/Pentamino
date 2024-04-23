#ifndef FIGURES_H
#define FIGURES_H

#include <iostream>
#include <vector>

struct Point{
    Point(int x, int y): x(x), y(y){};
    Point(int * l) : Point(l[0], l[1]) {};
    Point(): Point(0, 0) {};
    int x;
    int y;
};

Point * copy_fig(Point * fig, int len = 5);
Point * rotate(Point * fig, int rotation, int len = 5);
Point * mirror(Point * fig, int mirror, int len = 5);
Point * shift (Point * fig, int xs, int ys, int len = 5);

class Figure{
public:
    Figure(){}
    Figure(Point * p_fig): fig(p_fig){};
public:
    Point * fig;
    uint8_t rotations = 4;
    uint8_t mirroring = 2;

    Point * variant(uint8_t rot, uint8_t mir){
        Point * out = copy_fig(fig);

        mirror(out, rot % rotations);
        rotate(out, mir % mirroring);
        return out;
    }

    Point * place(uint8_t rot, uint8_t mir, int x, int y){
        Point * out = variant(rot, mir);
        return shift(out, x, y);
    }

};

Figure * make_figures();

class Field{
public:

    Field(int p_height, int p_width);

    Field(int p_height, int p_width, Point * p_list);

    Field(): Field(1, 1) {}

    Field(Field & other);

    ~Field(){
        for(int i = 0; i < height; i++)
            delete [] map[i];
        delete [] map;
    }

public:
    Point list[60];
    int ** map;
    int height, width;

public:
    int status(int x, int y);
    bool place_figure(Point * fig, int idx, bool force = false);
    void display_map();

    void copy(const Field &other);

    Field & operator = (const Field & other){
        this->copy(other);
        return * this;
    }
};

class Solver
{
public:
    Solver(){
        this->figs = make_figures();
    }
    Solver(Point * p_list);

    ~Solver(){
        delete [] figs;
    }
public:
    Field field;
    Figure * figs;
private:
    bool recursive_search(int idx);
    bool find_lonely_cell();
public:
    bool find_solution();

};

#endif // FIGURES_H
