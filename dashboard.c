/* dashboard.c, Raspberry Pi Dashboard, Christian Piper, 2014-04-12 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "VG/openvg.h"
#include "VG/vgu.h"
#include "fontinfo.h"
#include "shapes.h"

void sleepMs(int ms) {
    usleep(ms * 1000);
    return;
}

int returnCmdInt(char command[126]) {
    FILE*pf;
    char data[100];
    pf = popen(command, "r");
    if (!pf) {
        fprintf(stderr, "Could not open pipe for output.\n");
        return 0;
    }

    fgets(data, 100, pf);

    if (pclose(pf) != 0) {
        fprintf(stderr, "Error: Failed to close command stream \n");
    }

    return (int) atoi(data);
}

int barGraph(int perc, int x, int y, int height, int width) {
    int ratio;

    ratio = (height / 100);
    height = (perc * ratio);
    Rect(x, y, width, height);

    return 0;

}

char* concat(char *s1, char *s2) {
    char *result = malloc(strlen(s1) + strlen(s2) + 1);

    strcpy(result, s1);
    strcat(result, s2);

    return result;
}

int main() {
    int width, height, load;
    char string[50];

    init(&width, &height);
    while (1) {
        char text[100];
        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        strftime(text, sizeof (text) - 1, "%d/%m %H:%M:%S", t);
        Start(width, height);
        Background(0, 0, 0);
        Fill(255, 255, 255, 1);
        int temp = returnCmdInt("cat /sys/class/thermal/thermal_zone0/temp") / 1000;
        sprintf(string, "%d", temp);
        char* string2 = concat(string, "'C - ");
        string2 = concat(string2, text);
        Text(20, 430, "Raspberry Pi", SansTypeface, 26);
        Fill(64, 255, 64, 1);
        Text(330, 430, string2, SansTypeface, 26);
        load = returnCmdInt("top -bn 2 -d 0.3 | grep '^%Cpu' | tail -n 2 | tail -n 1 | gawk '{print $2+$4+$6}'");
        Stroke(64, 128, 255, 1);
        StrokeWidth(2);
        Line(840, 410, 0, 410);
        Stroke(255, 128, 128, 1);
        StrokeWidth(5);
        barGraph(load, 30, 30, 400, 50);
        End();
    }

    finish();
    exit(0);
}
