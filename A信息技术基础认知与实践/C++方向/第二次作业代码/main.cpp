#include <iostream>
#include <easyx.h>
#include <conio.h>
#include <functional>
#include <utility>
#include <unordered_map>

#define  WINDOW_WIDTH  1024
#define  WINDOW_HEIGHT 768

#define  GRID_N   15
#define  GRID_SIZE 30
#define  OFFSET_X  100
#define  OFFSET_Y  100
#define  HALF_GRID (int)(1/2.0*GRID_SIZE)

int man_X = 7;
int man_Y = 7;

IMAGE pic_back;
IMAGE pic_man;
IMAGE pic_black;
IMAGE pic_white;

enum PieceType {
    None = 0,
    Black,
    White
};

int board[GRID_N][GRID_N] = {0};
int currentPiece = Black;

void loadImage() {
    loadimage(&pic_back,"img\\back.jpg",WINDOW_WIDTH,WINDOW_HEIGHT);
    loadimage(&pic_man,"img\\man.png",GRID_SIZE,GRID_SIZE);
    loadimage(&pic_black,"img\\hei.png",GRID_SIZE,GRID_SIZE);
    loadimage(&pic_white,"img\\bai.png",GRID_SIZE,GRID_SIZE);
}

void init() {
    loadImage();
    initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
}

void transparentImage(IMAGE *dstimg, int x, int y, IMAGE *srcimg) {
    DWORD *dst = GetImageBuffer(dstimg);
    DWORD *src = GetImageBuffer(srcimg);
    int src_width  = srcimg->getwidth();
    int src_height = srcimg->getheight();
    int dst_width  = (dstimg == NULL ? getwidth()  : dstimg->getwidth());
    int dst_height = (dstimg == NULL ? getheight() : dstimg->getheight());

    int iwidth = (x + src_width > dst_width) ? dst_width - x : src_width;
    int iheight = (y + src_height > dst_height) ? dst_height - y : src_height;
    if (x < 0) { src += -x; iwidth -= -x; x = 0; }
    if (y < 0) { src += src_width * -y; iheight -= -y; y = 0; }

    dst += dst_width * y + x;

    for (int iy = 0; iy < iheight; iy++) {
        for (int ix = 0; ix < iwidth; ix++) {
            int sa = ((src[ix] & 0xff000000) >> 24);
            int sr = ((src[ix] & 0xff0000) >> 16);
            int sg = ((src[ix] & 0xff00) >> 8);
            int sb = src[ix] & 0xff;
            int dr = ((dst[ix] & 0xff0000) >> 16);
            int dg = ((dst[ix] & 0xff00) >> 8);
            int db = dst[ix] & 0xff;

            dst[ix] = ((sr + dr * (255 - sa) / 255) << 16)
                      | ((sg + dg * (255 - sa) / 255) << 8)
                      |  (sb + db * (255 - sa) / 255);
        }
        dst += dst_width;
        src += src_width;
    }
}

void paint() {
    BeginBatchDraw();
    putimage(0, 0, &pic_back);

    for (int i = 0; i < GRID_N; i++) {
        line(OFFSET_X, OFFSET_Y + i * GRID_SIZE, OFFSET_X + (GRID_N - 1) * GRID_SIZE, OFFSET_Y + i * GRID_SIZE);
        line(OFFSET_X + i * GRID_SIZE, OFFSET_Y, OFFSET_X + i * GRID_SIZE, OFFSET_Y + (GRID_N - 1) * GRID_SIZE);
    }

    for (int y = 0; y < GRID_N; y++) {
        for (int x = 0; x < GRID_N; x++) {
            int draw_x = OFFSET_X + x * GRID_SIZE - HALF_GRID;
            int draw_y = OFFSET_Y + y * GRID_SIZE - HALF_GRID;
            if (board[y][x] == Black) {
                transparentImage(NULL, draw_x, draw_y, &pic_black);
            } else if (board[y][x] == White) {
                transparentImage(NULL, draw_x, draw_y, &pic_white);
            }
        }
    }

    transparentImage(NULL, OFFSET_X + man_X * GRID_SIZE - HALF_GRID, OFFSET_Y + man_Y * GRID_SIZE - HALF_GRID, &pic_man);
    setbkmode(TRANSPARENT);
    outtextxy(600, 600, "2024303504 lizimeng");
    EndBatchDraw();
}

class InputMapper {
public:
    InputMapper() {
        m_mapper['w'] = [this]() { if (man_Y > 0) man_Y--; };
        m_mapper['s'] = [this]() { if (man_Y < GRID_N - 1) man_Y++; };
        m_mapper['a'] = [this]() { if (man_X > 0) man_X--; };
        m_mapper['d'] = [this]() { if (man_X < GRID_N - 1) man_X++; };
        m_mapper[' '] = [this]() {
            if (board[man_Y][man_X] == None) {
                board[man_Y][man_X] = currentPiece;
                currentPiece = (currentPiece == Black ? White : Black);
            }
        };
    }

    void map(char key, std::function<void()> func) {
        m_mapper[key] = std::move(func);
    }

    void operator()(char key) {
        key = tolower(key);
        auto it = m_mapper.find(key);
        if (it != m_mapper.end()) {
            it->second();
        }
    }

private:
    std::unordered_map<char, std::function<void()>> m_mapper;
};

int main() {
    InputMapper mapper;
    init();
    while (true) {
        if (_kbhit()) {
            char ch = _getch();
            mapper(ch);
        }
        paint();
        Sleep(10);
    }
    return 0;
}
