#include <stdio.h>
#include <conio.h>
struct process
{
    int pno, at, bt, turn, wait;
} p[20], temp;
void sort(int);
int n, clock = 0;
int main()
{
    int i, j;

    printf("Enter the number of processes: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        printf("\nProcess P%d", i + 1);
        p[i].pno = i + 1;
        printf("\nArrival time: ");
        scanf("%d", &p[i].at);
        printf("Burst time: ");
        scanf("%d", &p[i].bt);
    }
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (p[j].at > p[j + 1].at)
            {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
    int totalwait = 0, totalturn = 0, idle = 0, cs = 1, idle1 = 0, cst[20], d = 0;
    for (i = 0; i < n; i++)
    {
        cst[d++] = clock;
        if (clock < p[i].at)
        {
            idle += p[i].at - clock;
            clock = p[i].at;
            cst[d++] = clock;
        }
        sort(i);
        p[i].wait = clock - p[i].at;
        p[i].turn = p[i].wait + p[i].bt;
        totalwait += p[i].wait;
        totalturn += p[i].turn;
        clock += p[i].bt;
        ++cs;
    }
    cst[d++] = clock;
    ++cs;
    float avgwait = (float)totalwait / n;
    float avgturn = (float)totalturn / n;
    int y = clock - idle;
    // int x = y + cs;
    float ut = (float)y / clock;
    ut *= 100;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (p[j].pno > p[j + 1].pno)
            {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
    printf("\nInput:\n");
    printf("---------------------------------------------------------\n");
    printf("Process id\tArrival Time(in ms)\tBurst Time(in ms)\n");
    printf("---------------------------------------------------------\n");
    for (i = 0; i < n; i++)
        printf("%d\t\t%d\t\t\t%d\n", p[i].pno, p[i].at, p[i].bt);
    printf("---------------------------------------------------------\n");
    printf("\nOutput:\n");
    printf("-----------------------------------------------------------\n");
    printf("Process id\tTurnaround time(in ms)\tWaiting time(in ms)\n");
    printf("-----------------------------------------------------------\n");
    for (i = 0; i < n; i++)
        printf("%d\t\t%d\t\t\t%d\n", p[i].pno, p[i].turn, p[i].wait);
    printf("-----------------------------------------------------------\n");
    printf("\nAverage Turnaround Time: %.2fms", avgturn);
    printf("\nAverage Waiting Time: %.2fms", avgwait);
    printf("\nCPU Utilization Time: %dms", y);
    printf("\nContext Switch: %d", cs);
    printf("\nCPU Utilization percentage: %.2f percent", ut);
    printf("\nCPU Idle Time: %dms", idle);
    printf("\nContext switches:\n");
    for (i = 0; i < d; i++)
    {
        printf("%dms -> ", cst[i]);
        if (i == 0)
            printf("OS Context-> Process Context\n");
        else if (i == d - 1)
            printf("Process Context -> OS Context\n");
        else
            printf("Process context -> OS Context -> Process Context\n");
    }
    printf("\nMode Switches:\n");
    for (i = 0; i < d; i++)
    {
        printf("%dms -> ", cst[i]);
        if (i == 0)
            printf("Kernel Mode -> User Mode\n");
        else if (i == d - 1)
            printf("User Mode -> Kernel Mode\n");
        else
            printf("User Mode -> Kernel Mode -> User Mode\n");
    }
    return 0;
}
void sort(int x)
{
    int i, j;

    for (i = x; i < n; i++)
    {
        if (p[i].at > clock)
            continue;

        for (j = i + 1; j < n; j++)
        {
            if (p[j].bt < p[i].bt && p[j].at <= clock)
            {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}