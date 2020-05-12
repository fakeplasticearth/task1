#include <bits/stdc++.h>
#include <stdio.h>
#include <graphics.h>
#include <cstdlib>
using namespace std;

int X[100];
int Y[100];
int F[100][100];//покрашена или нет
int G[100][100];//граф
int n;
int C[100];//цвет вершин

void DrawGraph(bool ans = 1)
{
    int radius = 15 * n;
    int gm;
    int gd = DETECT;
    initgraph(&gd, &gm, "");
    settextstyle(BOLD_FONT, HORIZ_DIR, 7);
    int x_c = 250, y_c = 250;
    for (int i = 1;i <= n;i++)
    {
        if (ans == 1)
            setcolor(C[i]);
        else
            setcolor(1);
        setlinestyle(0, 0, 30);
        char* ver;
        X[i] = trunc(radius * cos((i - 1) * 2 * M_PI / n)) + x_c;
        Y[i] = trunc(radius * sin((i - 1) * 2 * M_PI / n)) + y_c;
        circle(X[i], Y[i], 5);
        setcolor(0);
        setlinestyle(0, 0, 3);
        //outtextxy(X[i+1], Y[i+1], to_string(i));
    }
    for (int i = 1;i <= n;i++)
    {
        for (int j = i + 1;j <= n ;j++)
            if(G[i][j] == 1)
            {
                setcolor(1);
                line(X[i], Y[i], X[j], Y[j]);
            }
    }
    readkey();
    closegraph();
}

int A[100][100];
void ColorAllVertex()
{
    int colour = 1;
    for (int i = 1;i <= n;i++)
    {
        if (C[i] > 0)
            continue;
        C[i] = colour;
        int num_not_coloured_non_neighbours = 0;
        for (int j = 1;j <= n;j++)
            if (A[i][j] == 0 && A[j][i] == 0 && C[j] == 0)
                num_not_coloured_non_neighbours++;
        while (num_not_coloured_non_neighbours > 0)
        {
            num_not_coloured_non_neighbours = 0;
            int v = i + 1;
            while(v <= n)
            {
                if (A[i][v] == 0 && C[v] == 0)
                    break;
                v++;
            }
            if (v == n + 1)
                break;
            C[v] = colour;
            for (int j = 1;j <= n ;j++)
                A[i][j] = A[i][j] | A[v][j];
            for (int j = 1;j <= n;j++)
                if (A[i][j] == 0 && A[j][i] == 0 && C[j] == 0)
                    num_not_coloured_non_neighbours++;
        }
        colour++;
    }
    return;
}

int main()
{
    int kr;
    cout << "Graph coloring greedy algorithm (undirected graph)\n";
    ifstream in("input.txt");
    in >> n;
    for (int i = 1;i <= n;i++)
        for (int j = 1;j <= n;j++)
        {
            in >> G[i][j];
            A[i][j] = G[i][j];
        }
    in.close();
    DrawGraph(0);
    ColorAllVertex();
    DrawGraph();
    return 0;
}
