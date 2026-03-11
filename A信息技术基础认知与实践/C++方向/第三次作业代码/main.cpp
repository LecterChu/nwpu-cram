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

int winner = None;

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

bool checkDirection(int x, int y, int dx, int dy, int type) {
    int count = 1;
    for (int i = 1; i < 5; i++) {
        int nx = x + i * dx;
        int ny = y + i * dy;
        if (nx >= 0 && nx < GRID_N && ny >= 0 && ny < GRID_N && board[ny][nx] == type)
            count++;
        else break;
    }
    for (int i = 1; i < 5; i++) {
        int nx = x - i * dx;
        int ny = y - i * dy;
        if (nx >= 0 && nx < GRID_N && ny >= 0 && ny < GRID_N && board[ny][nx] == type)
            count++;
        else break;
    }
    return count >= 5;
}

bool checkWin(int x, int y, int type) {
    return checkDirection(x, y, 1, 0, type) ||
           checkDirection(x, y, 0, 1, type) ||
           checkDirection(x, y, 1, 1, type) ||
           checkDirection(x, y, 1, -1, type);
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

    if (winner != None) {
        settextcolor(RED);
        outtextxy(600, 550, winner == Black ? "Black win!!" : "White win!!");
    }

    EndBatchDraw();
}

int countConnected(int x, int y, int dx, int dy, int type) {
    int count = 1;
    for (int i = 1; i < GRID_N; i++) {
        int nx = x + i * dx;
        int ny = y + i * dy;
        if (nx >= 0 && nx < GRID_N && ny >= 0 && ny < GRID_N && board[ny][nx] == type)
            count++;
        else break;
    }
    for (int i = 1; i < GRID_N; i++) {
        int nx = x - i * dx;
        int ny = y - i * dy;
        if (nx >= 0 && nx < GRID_N && ny >= 0 && ny < GRID_N && board[ny][nx] == type)
            count++;
        else break;
    }
    return count;
}

bool isLongLink(int x, int y) {
    board[y][x] = Black;

    bool result = false;
    if (countConnected(x, y, 1, 0, Black) > 5) result = true;
    if (countConnected(x, y, 0, 1, Black) > 5) result = true;
    if (countConnected(x, y, 1, 1, Black) > 5) result = true;
    if (countConnected(x, y, 1, -1, Black) > 5) result = true;

    board[y][x] = None;
    return result;
}


int countLiveThree(int x, int y, int dx, int dy) {
    int count = 0;
    std::string pattern;

    for (int i = -4; i <= 4; i++) {
        int nx = x + i * dx;
        int ny = y + i * dy;
        if (nx < 0 || ny < 0 || nx >= GRID_N || ny >= GRID_N) {
            pattern += "X";
        } else if (nx == x && ny == y) {
            pattern += "1";
        } else {
            pattern += (board[ny][nx] == Black ? '1' : board[ny][nx] == None ? '0' : '2');
        }
    }

    if (pattern.find("01110") != std::string::npos) count++;
    if (pattern.find("010110") != std::string::npos) count++;
    return count;
}

bool isDoubleThree(int x, int y) {
    board[y][x] = Black;
    int cnt = 0;
    cnt += countLiveThree(x, y, 1, 0);
    cnt += countLiveThree(x, y, 0, 1);
    cnt += countLiveThree(x, y, 1, 1);
    cnt += countLiveThree(x, y, 1, -1);
    board[y][x] = None;
    return cnt >= 2;
}

bool isForbidden(int x, int y) {
    return isLongLink(x, y) || isDoubleThree(x, y);
}


class InputMapper {
public:
    InputMapper() {
        m_mapper['w'] = [this]() { if (man_Y > 0) man_Y--; };
        m_mapper['s'] = [this]() { if (man_Y < GRID_N - 1) man_Y++; };
        m_mapper['a'] = [this]() { if (man_X > 0) man_X--; };
        m_mapper['d'] = [this]() { if (man_X < GRID_N - 1) man_X++; };
        m_mapper[' '] = [this]() {
            if (board[man_Y][man_X] == None && winner == None) {
                if (currentPiece == Black && isForbidden(man_X, man_Y)) {
                    MessageBox(GetHWnd(), "Forbidden!", "Message", MB_OK | MB_ICONWARNING);
                    return;
                }

                board[man_Y][man_X] = currentPiece;
                if (checkWin(man_X, man_Y, currentPiece)) {
                    winner = currentPiece;
                } else {
                    currentPiece = (currentPiece == Black ? White : Black);
                }
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
