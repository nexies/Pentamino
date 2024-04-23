#include "figures.h"
#include "string.h"
#include <windows.h>

using namespace std;

Point fig1 [5] = {{0, 0}, {0, 1}, {-1, 1}, {0, 2}, {1, 2}};    // F
Point fig2 [5] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}};    // I
Point fig3 [5] = {{0, 0}, {1, 0}, {0, 1}, {0, 2}, {0, 3}};    // L
Point fig4 [5] = {{0, 0}, {0, 1}, {0, 2}, {1, 2}, {1, 3}};    // N
Point fig5 [5] = {{0, 0}, {1, 0}, {0, 1}, {1, 1}, {1, 2}};    // P
Point fig6 [5] = {{0, 0}, {0, 1}, {0, 2}, {-1, 2}, {1, 2}};    // T
Point fig7 [5] = {{0, 0}, {0, 1}, {1, 0}, {2, 0}, {2, 1}};    // U
Point fig8 [5] = {{0, 0}, {0, 1}, {0, 2}, {1, 0}, {2, 0}};    // V
Point fig9 [5] = {{0, 0}, {0, 1}, {1, 0}, {1, -1}, {2, -1}};    // W
Point fig10[5] = {{0, 0}, {0, 1}, {1, 0}, {-1, 0}, {0, -1}};    // X
Point fig11[5] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}, {-1, 2}};    // Y
Point fig12[5] = {{0, 0}, {0, 1}, {-1, 1}, {0, -1}, {1, -1}};    // Z

Point *rotate(Point * fig, int rotation, int len)
{
    rotation %= 4;
    switch(rotation){
    case 0:
        return fig;
    case 1:
        for(int i = 0; i < len; i++){
            int x = fig[i].x;
            fig[i].x = - fig[i].y;
            fig[i].y = x;
        }
        return fig;
    case 2:
        for(int i = 0; i < len; i++){
            fig[i].x = -fig[i].x;
            fig[i].y = -fig[i].y;
        }
        return fig;
    case 3:
        for(int i = 0; i < len; i++){
            int x = fig[i].x;
            fig[i].x = fig[i].y;
            fig[i].y = - x;
        }
        return fig;
    default:
        return fig;
    }
}

Point *mirror(Point *fig, int mirror, int len)
{
    mirror &= 1;
    switch(mirror){
    case 0:
        return fig;
    case 1:
        for(int i = 0; i < len; i++){
            fig[i].y = -fig[i].y;
        }
        return fig;
    default:
        return fig;
    }
}

Point *shift(Point *fig, int xs, int ys, int len)
{
    for(int i = 0; i < len; i++){
        fig[i].x += xs;
        fig[i].y += ys;
    }
    return fig;
}

Point *copy_fig(Point *fig, int len)
{
    Point * out = new Point[len];
    memcpy(out, fig, sizeof(Point) * len);
    return out;
}

Figure * make_figures() {
    Figure * out = new Figure [12];
    out[0] = Figure(fig1); // F

    out[1] = Figure(fig2); // I
    out[1].rotations = 2;
    out[1].mirroring = 1;

    out[2] = Figure(fig3); // L

    out[3] = Figure(fig4); // N

    out[4] = Figure(fig5); // P

    out[5] = Figure(fig6); // T
    out[5].mirroring = 1;

    out[6] = Figure(fig7); // U
    out[6].mirroring = 1;

    out[7] = Figure(fig8); // V
    out[7].mirroring = 1;

    out[8] = Figure(fig9); // W
    out[8].mirroring = 1;

    out[9] = Figure(fig10); // X
    out[9].rotations = 1;
    out[9].mirroring = 1;

    out[10] = Figure(fig11); // Y

    out[11] = Figure(fig12); // Z
    out[11].rotations = 2;

    return out;
}

Field::Field(int p_height, int p_width): height(p_height), width(p_width){
    this->map = new int * [height];
    for(int i = 0; i < height; i++){
        this->map[i] = new int [width];
        for(int j = 0; j < width; j++)
            map[i][j] = -1;
    }
}

Field::Field(int p_height, int p_width, Point *p_list): Field(p_height, p_width){
    for(int i = 0; i < 60; i++){
        this->list[i] = p_list[i];
        this->map[list[i].x][list[i].y] = 0;
    }
}

Field::Field(Field &other) : Field(other.height, other.width) { this->copy(other); }

inline int Field::status(int x, int y){
    if ((x < 0 || x >= height) || (y < 0 || y >= width))
        return -1;
    return map[x][y];
}

inline bool Field::place_figure(Point *fig, int idx, bool force){
    if(!force)
        for(int i = 0; i < 5; i++){
            if(this->map[fig[i].x][fig[i].y] != 0)
                return false;
        }

    for(int i = 0; i < 5; i++){
        this->map[fig[i].x][fig[i].y] = idx;
    }
    return true;
}

void Field::display_map()
{
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++)
            switch(map[i][j]){
            case -1:
                printf("* ");
                break;
            case 0:
                printf("  ");
                break;
            default:
                printf("%2i", map[i][j]);
            }
        std::cout << std::endl;
    }
}

void Field::copy(const Field &other){
    memcpy(this->list, other.list, sizeof(Point) * 60);
    for(int i = 0; i < height; i++)
        delete [] map[i];
    delete [] map;
    this->height = other.height;
    this->width = other.width;
    this->map = new int * [height];
    for(int i = 0; i < height; i++){
        this->map[i] = new int [width];
        memcpy(this->map[i], other.map[i], sizeof(int) * width);
    }
}

Solver::Solver(Point *p_list): Solver()
{
    int minx = p_list[0].x, maxx = p_list[0].x;
    int miny = p_list[0].y, maxy = p_list[0].y;

    for(int i = 1; i < 60; i++){
        minx = p_list[i].x > minx? minx : p_list[i].x;
        maxx = p_list[i].x < maxx? maxx : p_list[i].x;
        miny = p_list[i].y > miny? miny : p_list[i].y;
        maxy = p_list[i].y < maxy? maxy : p_list[i].y;
    }

    shift(p_list, -minx + 1, -miny + 1, 60);
    this->field = Field(maxx - minx + 3, maxy - miny + 3, p_list);
}

bool Solver::recursive_search(int idx)
{
    /*
     * 1) Разместить фигуру fig[idx]
     *      Если не размещается: return false;
     *      Если размещается: шаг 2
     *
     * 2) Если idx < 11:
     *      if (recursive_search(idx + 1)):
     *          return true;
     *      else:
     *          шаг 1
     *
     *    Если idx == 11:
     *      проверка полноты покрытия
     *      return true;
    */
    if(idx == 12)
        return true;


    for(Point cell: this->field.list){
        for(int r = 0; r < this->figs[idx].rotations; r++){
            for(int m = 0; m < this->figs[idx].mirroring; m++){

                Point * temp = this->figs[idx].place(r, m, cell.x, cell.y);
                if(this->field.place_figure(temp, idx + 1)){
                    system("cls");
                    this->field.display_map();
//

                    if(!find_lonely_cell()){
                        this->field.place_figure(temp, 0, true);
                        continue;
                    }

                    if(!recursive_search(idx + 1)){
                        this->field.place_figure(temp, 0, true);
                        continue;
                    }


                    return true;

                }
                delete [] temp;
            }
        }
    }
//    this->field.display_map();
//    printf("Removed figure %i\n", idx);

    return false;

}

bool Solver::find_lonely_cell()
{
    int x, y;
    for(auto cell: this->field.list){
        x = cell.x;
        y = cell.y;

        if(this->field.status(x, y) != 0)
            continue;
        if(this->field.status(x+1, y) == 0)
            continue;
        if(this->field.status(x-1, y) == 0)
            continue;
        if(this->field.status(x, y+1) == 0)
            continue;
        if(this->field.status(x, y-1) == 0)
            continue;
        return false;
    }
    return true;
}

bool Solver::find_solution()
{
    recursive_search(0);
}

