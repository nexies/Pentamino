#ifndef SECOND_TRY_H
#define SECOND_TRY_H

#include <iostream>
#include <vector>

struct pnt
{
    pnt(int px, int py): x(px), y(py) {}
    pnt(): x(0), y(0) {}
    int x, y;
};

pnt *copy_fig(pnt *to, pnt *from, int len = 5);
pnt *rotate(pnt * fig, int rotation, int len = 5);
pnt *mirror(pnt *fig, int mirror, int len = 5);
pnt *shift(pnt *fig, int xs, int ys, int len = 5);


class figure5{
public:
    figure5(){
        for_output = new pnt [5];
    }
    figure5(pnt * p_fig): original(p_fig){
        for_output = new pnt [5];
    };

    ~figure5(){
        delete [] for_output;
    }
public:
    pnt * original;
    pnt * for_output;
    uint8_t rotations = 4;
    uint8_t mirroring = 2;

    void set_figure(pnt * p_fig){
        this->original = p_fig;
    }

    pnt * variant(uint8_t rot, uint8_t mir){
        pnt * out = copy_fig(for_output, original);
        mirror(out, mir % mirroring);
        rotate(out, rot % rotations);
        return out;
    }

    pnt * place(uint8_t rot, uint8_t mir, int x, int y){
        pnt * out = variant(rot, mir);
        return shift(out, x, y);
    }
};


class canvas{
public:

    canvas(int p_height, int p_width);
    canvas(pnt * p_list);
    canvas(): canvas(1, 1) {}
    canvas(canvas & other);

    ~canvas(){
        for(int i = 0; i < height; i++)
            delete [] map[i];
        delete [] map;
    }

public:
    pnt list[60];
    char ** map = 0;
    int height, width;

public:
    char check(int x, int y);
    char check(pnt point);
    void display_map();
    void set_list(pnt * p_list);

//    bool place_figure(pnt * fig, int idx, bool force = false);

    uint64_t mask_figure(pnt * fig, int len = 5);
    bool has_loney_cell(uint64_t mask);

    void draw_figure(uint64_t mask);

    void copy(const canvas &other);

    canvas & operator = (const canvas & other){
        this->copy(other);
        return * this;
    }
};


class PentaminoSolver
{
public:
    PentaminoSolver() {
        masks.resize(12);
        this->init_figures();
    }
    PentaminoSolver(pnt * field_list);
public:
    canvas field;
    std::vector<std::vector<uint64_t>> masks;
    std::vector<figure5> figures = std::vector<figure5>(12);

public:
    void init_figures();
    void init_field(pnt * field_list);
    void init_masks();

private:
#define FULLY_SOLVED 0x0FFFFFFFFFFFFFFF
    int res [12];
    bool recursive_search(int step = 0, uint64_t mask = 0);
    bool every_tile_can_be_covered();
public:
    bool solution();
    bool solution(pnt * field);
    void display_solution();


};

#endif // SECOND_TRY_H
