#include <stdio.h>
#include <string.h>
#include <xenos/xenos.h>
#include <console/console.h>
#include <usb/usbmain.h>
#include <input/input.h>
#include <time/time.h>

static void show_pad(int idx) {
    struct controller_data_s c;
    if (get_controller_data(&c, idx) == 0)
        return;

    printf("Controle %d: ", idx);
    if (c.a)     printf("A ");
    if (c.b)     printf("B ");
    if (c.x)     printf("X ");
    if (c.y)     printf("Y ");
    if (c.up)    printf("UP ");
    if (c.down)  printf("DOWN ");
    if (c.left)  printf("LEFT ");
    if (c.right) printf("RIGHT ");
    if (c.start) printf("START ");
    if (c.back)  printf("BACK ");
    printf("| LX=%d LY=%d", c.s1_x, c.s1_y);
    printf("\n");
}

int main(void) {
    xenos_init(VIDEO_MODE_AUTO);
    console_init();
    usb_init();
    usb_do_poll();

    for (;;) {
        usb_do_poll();
        console_clrscr();
        printf("== Teste de controles Xbox 360 ==\n");
        printf("Conecte um controle e aperte botoes.\n\n");
        for (int i = 0; i < 4; i++)
            show_pad(i);
        mdelay(100);
    }
    return 0;
}
