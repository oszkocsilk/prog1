#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <unistd.h>
#include <sys/ioctl.h>

int
main (void)
{
    int xj = 0, xk = 0, yj = 0, yk = 0;
    int mx; 
    int my;
    struct winsize size;

    WINDOW *ablak;
    ablak = initscr ();
    noecho ();
    cbreak ();
    nodelay (ablak, true);

    for (;;)
    {
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	mx = size.ws_col * 2;
	my = size.ws_row * 2;
	my--;
        xj = (xj - 1) % mx;
        xk = (xk + 1) % mx;

        yj = (yj - 1) % my;
        yk = (yk + 1) % my;

        clear ();

	for(int i=0; i< mx-1; i++) {
		mvprintw(0,i, "-");
		mvprintw(my/2,i, "-");
	}

        mvprintw (abs ((yj + (my - yk)) / 2),
                  abs ((xj + (mx - xk)) / 2), "X");

        refresh ();
        usleep (150000);

    }
    return 0;
}
