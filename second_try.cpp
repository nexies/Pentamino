#include "second_try.h"

using namespace std;

pnt fig1 [5] = {{0, 0}, {0, 1}, {-1, 1}, {0, 2}, {1, 2}};    // F
pnt fig2 [5] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}};     // I
pnt fig3 [5] = {{0, 0}, {1, 0}, {0, 1}, {0, 2}, {0, 3}};     // L
pnt fig4 [5] = {{0, 0}, {0, 1}, {0, 2}, {1, 2}, {1, 3}};     // N
pnt fig5 [5] = {{0, 0}, {1, 0}, {0, 1}, {1, 1}, {1, 2}};     // P
pnt fig6 [5] = {{0, 0}, {0, 1}, {0, 2}, {-1, 2}, {1, 2}};    // T
pnt fig7 [5] = {{0, 0}, {0, 1}, {1, 0}, {2, 0}, {2, 1}};     // U
pnt fig8 [5] = {{0, 0}, {0, 1}, {0, 2}, {1, 0}, {2, 0}};     // V
pnt fig9 [5] = {{0, 0}, {0, 1}, {1, 0}, {1, -1}, {2, -1}};   // W
pnt fig10[5] = {{0, 0}, {0, 1}, {1, 0}, {-1, 0}, {0, -1}};   // X
pnt fig11[5] = {{0, 0}, {0, 1}, {0, 2}, {0, 3}, {-1, 2}};    // Y
pnt fig12[5] = {{0, 0}, {0, 1}, {-1, 1}, {0, -1}, {1, -1}};  // Z

pnt *copy_fig(pnt *to, pnt *from, int len)
{
    memcpy(to, from, sizeof(pnt) * len);
    return to;
}

pnt *rotate(pnt * fig, int rotation, int len)
{
    rotation %= 4;
    switch(rotation){
    case 0:
        return fig;
    case 1:
        for(int i = 0; i < len; i++){
            int x = fig[i].x;
            fig[i].x = - fig[i].y + 2;
            fig[i].y = x;
        }
        return fig;
    case 2:
        for(int i = 0; i < len; i++){
            fig[i].x = -fig[i].x + 2;
            fig[i].y = -fig[i].y + 2;
        }
        return fig;
    case 3:
        for(int i = 0; i < len; i++){
            int x = fig[i].x;
            fig[i].x = fig[i].y;
            fig[i].y = - x + 2;
        }
        return fig;
    default:
        return fig;
    }
}

pnt *mirror(pnt *fig, int mirror, int len)
{
    mirror &= 1;
    switch(mirror){
    case 0:
        return fig;
    case 1:
        for(int i = 0; i < len; i++){
            fig[i].x = -fig[i].x + 2;
        }
        return fig;
    default:
        return fig;
    }
}

pnt *shift(pnt *fig, int xs, int ys, int len)
{
    for(int i = 0; i < len; i++){
        fig[i].x += xs;
        fig[i].y += ys;
    }
    return fig;
}

canvas::canvas(int p_height, int p_width): height(p_height), width(p_width){
    this->map = new char * [height];
    for(int i = 0; i < height; i++){
        this->map[i] = new char [width];
        for(int j = 0; j < width; j++)
            map[i][j] = -1;
    }
}

canvas::canvas(canvas &other) : canvas(other.height, other.width) { this->copy(other); }

canvas::canvas(pnt *p_list){
    this->set_list(p_list);
}


inline char canvas::check(int x, int y){
    if ((x < 0 || x >= height) || (y < 0 || y >= width))
        return -1;
    return map[x][y];
}

inline char canvas::check(pnt point)
{
    return this->check(point.x, point.y);
}

uint64_t canvas::mask_figure(pnt *fig, int len)
{
    uint64_t out = 0;
    for(int i = 0; i < len; i++){
        char t = this->check(fig[i]);
        if(t <= -1)
            return 0;
        out |= 1LL<<t;
    }
    return out;
}

bool canvas::has_loney_cell(uint64_t mask)
{
    int x, y;
    for(int i = 0; i < 60; i++){
        x = this->list[i].x;
        y = this->list[i].y;

        if(mask & (1LL << check(x, y)))
            continue;
        if((check(x + 1, y) != -1) && !(mask & (1LL << check(x + 1, y))))
            continue;
        if((check(x - 1, y) != -1) && !(mask & (1LL << check(x - 1, y))))
            continue;
        if((check(x, y + 1) != -1) && !(mask & (1LL << check(x, y + 1))))
            continue;
        if((check(x, y - 1) != -1) && !(mask & (1LL << check(x, y - 1))))
            continue;
        return true;
    }
    return false;
}

void canvas::draw_figure(uint64_t mask)
{
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            switch(map[i][j]){
            case -1:
                printf("* ");
                break;
            default:
                if(mask & (1LL << map[i][j]))
                    printf("# ");
                else
                    printf("  ");
                break;
            }
        }
        printf("\n");
    }
}

void canvas::copy(const canvas &other){
    memcpy(this->list, other.list, sizeof(pnt) * 60);

    if(this->map != 0){
        for(int i = 0; i < height; i++)
            delete [] map[i];
        delete [] map;
    }

    this->height = other.height;
    this->width = other.width;
    this->map = new char * [height];
    for(int i = 0; i < height; i++){
        this->map[i] = new char [width];
        memcpy(this->map[i], other.map[i], sizeof(int) * width);
    }
}

void canvas::display_map()
{
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++)
            switch(map[i][j]){
            case -1:
                printf("* ");
                break;
            default:
                printf("%2i", map[i][j]);
            }
        std::cout << std::endl;
    }
}

void canvas::set_list(pnt * p_list)
{
    if (this->map != 0){
        for(int i = 0; i < height; i++)
            delete [] map[i];
        delete [] map;
    }

    copy_fig(this->list, p_list, 60);

    int minx = list[0].x, maxx = list[0].x;
    int miny = list[0].y, maxy = list[0].y;

    for(int i = 1; i < 60; i++){
        minx = list[i].x > minx? minx : list[i].x;
        maxx = list[i].x < maxx? maxx : list[i].x;
        miny = list[i].y > miny? miny : list[i].y;
        maxy = list[i].y < maxy? maxy : list[i].y;
    }

    shift(list, -minx + 1, -miny + 1, 60);

    this->height = maxx - minx + 3;
    this->width  = maxy - miny + 3;

    this->map = new char * [height];
    for(int i = 0; i < height; i++){
        this->map[i] = new char [width];
        for(int j = 0; j < width; j++){
            this->map[i][j] = -1;
        }
    }

    for(int i = 0; i < 60; i++)
        this->map[list[i].x][list[i].y] = i;



}


/*
//inline bool canvas::place_figure(pnt *fig, int idx, bool force){
//    if(!force)
//        for(int i = 0; i < 5; i++){
//            if(this->map[fig[i].x][fig[i].y] != 0)
//                return false;
//        }

//    for(int i = 0; i < 5; i++){
//        this->map[fig[i].x][fig[i].y] = idx;
//    }
//    return true;
//}



*/

PentaminoSolver::PentaminoSolver(pnt *field_list): PentaminoSolver()
{
    this->init_field(field_list);
    this->init_masks();
}

void PentaminoSolver::init_figures()
{
    this->figures[0].set_figure(fig1); // F

    this->figures[1].set_figure(fig2); // I
    this->figures[1].rotations = 2;
    this->figures[1].mirroring = 1;

    this->figures[2].set_figure(fig3); // L

    this->figures[3].set_figure(fig4); // N

    this->figures[4].set_figure(fig5); // P

    this->figures[5].set_figure(fig6); // T
    this->figures[5].mirroring = 1;

    this->figures[6].set_figure(fig7); // U
    this->figures[6].mirroring = 1;

    this->figures[7].set_figure(fig8); // V
    this->figures[7].mirroring = 1;

    this->figures[8].set_figure(fig9); // W
    this->figures[8].mirroring = 1;

    this->figures[9].set_figure(fig10); // X
    this->figures[9].rotations = 1;
    this->figures[9].mirroring = 1;

    this->figures[10].set_figure(fig11); // Y

    this->figures[11].set_figure(fig12); // Z
    this->figures[11].rotations = 2;
}

void PentaminoSolver::init_field(pnt *field_list)
{
    this->field.set_list(field_list); // = canvas(field_list)
}

void PentaminoSolver::init_masks()
{
    for(int fignum = 0; fignum < 12; fignum++)
        masks[fignum].clear();

    int height = this->field.height;
    int width = this->field.width;

    uint64_t spare;
    for(int fignum = 0; fignum < 12; fignum++){

        int R = figures[fignum].rotations;
        int M = figures[fignum].mirroring;
        this->masks[fignum].resize(M*R*height*width);
        int index = 0;

        for(int r = 0; r < R; r++){
            for(int m = 0; m < M; m++){
                for(int x = -5; x < height + 5; x++){
                    for(int y = -5; y < width + 5; y++){
                        spare = field.mask_figure(figures[fignum].place(r, m, x, y), 5);
                        if(spare == 0)
                            continue;
                        if(field.has_loney_cell(spare))
                            continue;
//                        this->field.draw_figure(spare);
                        this->masks[fignum][index++] = spare;
                    }
                }
            }
        }
        this->masks[fignum].erase(masks[fignum].begin() + index, masks[fignum].end());
    }
}


#include <bitset>

bool PentaminoSolver::recursive_search(int step, uint64_t total)
{
    static unsigned long long calls = 0;
    calls++;
    if(calls % 100000 == 0)
        printf("Operation %10i, step %i\n", calls, step);
//    cout << bitset<64>(total) << endl;

    if(step == 12) return true;
    if(this->field.has_loney_cell(total)) return false;

    int len = this->masks[step].size();
    for(int i = 0; i < len; i++){
        if((this->masks[step][i] & total)) continue;   // если пересекаются

        res[step] = i;
        if (recursive_search(step + 1, total | masks[step][i])) return true;

    }
    return false;
}

bool PentaminoSolver::every_tile_can_be_covered()
{
    uint64_t all_tiles = 0;
    for(int figure = 0; figure < 12; figure++){
        for(int i = 0; i < (int)masks[figure].size(); i++){
            all_tiles |= masks[figure][i];
        }
    }
    if(all_tiles == 0x0FFFFFFFFFFFFFFF) return true;
    return false;
}

bool PentaminoSolver::solution()
{
    if(!every_tile_can_be_covered()){
        cout << "Cannot find a solution : some tiles can't be covered" << endl;
        return false;
    }

    cout << "Start searching for solution" << endl;

    if(recursive_search()){
        cout << "Found the solution" << endl;
        display_solution();
        return true;
    }else{
        cout << "Could not find the solution" << endl;
        return false;
    }
}


bool PentaminoSolver::solution(pnt * field)
{
    this->init_field(field);
    this->init_masks();
    return solution();

}


void PentaminoSolver::display_solution()
{
    int ** out = new int * [this->field.height];
    for(int i = 0; i < field.height; i++){
        out[i] = new int [this->field.width];
        for(int j = 0; j < field.width; j++){
            switch(field.map[i][j]){
            case -1:
                out[i][j] = -1;
                break;
            default:
                int idx = 0;
                for(idx = 0; idx < 12; idx++){
                    if(masks[idx][res[idx]] & (1LL << field.map[i][j])){
                        out[i][j] = idx;
                        break;
                    }
                }
                break;
            }
        }
    }
    for(int i = 0; i < field.height; i++){
        for(int j = 0; j < field.width; j++){
            switch(out[i][j]){
            case -1:
                printf("   ");
                break;
            default:
                printf("%2i ", out[i][j]);
            }
        }
        printf("\n");
    }

   for(int i = 0; i < field.height; i++){
       delete [] out[i];
   }
   delete [] out;
}

/*
void PentaminoSolver::display_solution()
{
    int ** out = new int * [this->field.height];
    for(int i = 0; i < this->field.height; i++){
        out[i] = new int [this->field.width];
        for(int j = 0; j < field.width; j++)
            out[i][j] = -1;
    }

    for(int fignum = 0; fignum < 12; fignum++){
        for(int i = 0; i < 60; i++)
            if(masks[fignum][res[fignum]] & (1L << i)){
                int x = this->field.list[i].x;
                int y = this->field.list[i].y;
                out[x][y] = fignum;
            }
    }

    for(int x = 0; x < field.height; x++){
        for(int y = 0; y < field.width; y++){
            switch(out[x][y]){
            case -1:
                printf("    ");
                break;
            default:
                printf("%2i  ", out[x][y]);
                break;
            }
        }
        printf("\n");
    }

    for(int i = 0; i < field.height; i++)
        delete [] out [i];
    delete [] out;

}*/
