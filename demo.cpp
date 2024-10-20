#include "device.c"
#include <iostream>
using namespace std;

void bresenham(void);

int main(void)
{
        clrscr();
        int height = get_window_height();
        int width  = get_window_width();

        int n, x, y;
        cout << "Device Dimensions: " << height << " x " << width << endl;
        cout << "Number of lines to draw : ";
        cin >> n;
        for (int i = 0; i < n; i++) { bresenham(); }
        getch();
        return 0;
}

void bresenham(void)
{
        int x0, y0, x1, y1;
        cout << "Enter a pair of coordinates:(x1 y1 x2 y2): ";
        cin >> x0 >> y0 >> x1 >> y1;
        bool steep = false;
        if (abs(x0 - x1) < abs(y0 - y1)) {
                swap(x0, y0);
                swap(x1, y1);
                steep = true;
        }
        if (x0 > x1) {
                swap(x0, x1);
                swap(y0, y1);
        }
        int dx      = x1 - x0;
        int dy      = y1 - y0;
        int derror2 = abs(dy) * 2;
        int error2  = 0;
        int y       = y0;
        for (int x = x0; x <= x1; x++) {
                if (steep) {
                        put_pixel(y, x, '#');
                } else {
                        put_pixel(x, y, '#');
                }
                error2 += derror2;
                if (error2 > dx) {
                        y += (y1 > y0 ? 1 : -1);
                        error2 -= dx * 2;
                }
        }
}
