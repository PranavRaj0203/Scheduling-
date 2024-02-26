#include <stdio.h>
#include <conio.h>
struct process
{
    int pno, at, bt, turn, wait;
};
int main()
{
    struct process p[20], temp;
    int n, i, j;
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
    int totalwait = 0, totalturn = 0, clock = 0, idle = 0, cs = 1, idle1 = 0, cst[20], d = 1;
    cst[0] = 0;
    for (i = 0; i < n; i++)
    {
        if (i == 0)
        {
            p[i].wait = 0;
            p[i].turn = p[i].bt;
            totalturn = p[i].bt;
            clock = p[i].bt;
            ++cs;
        }
        else
        {
            if (p[i].at < clock)
            {
                cst[d++] = clock;
                p[i].wait = clock - p[i].at;
                totalwait += p[i].wait;
                clock += p[i].bt;
                p[i].turn = clock - p[i].at;
                totalturn += p[i].turn;
                ++cs;
            }
            else
            {
                p[i].wait = 0;
                cst[d++] = clock;
                idle += (p[i].at - clock);
                idle1 = p[i].at - clock;
                cst[d++] = clock + idle1;
                clock += p[i].bt + idle1;
                p[i].turn = p[i].bt;
                totalturn += p[i].turn;
                ++cs;
            }
        }
    }
    cst[d++] = clock;
    float avgwait = (float)totalwait / n;
    float avgturn = (float)totalturn / n;
    int y = clock - idle;
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
    printf("--------------------------------------------------------------------------------------");
    printf("\nProcess id\tArrival time\tBurst Time\tTurnaround time\t\tWaiting time\n");
    printf("--------------------------------------------------------------------------------------\n");
    for (i = 0; i < n; i++)
        printf("%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", p[i].pno, p[i].at, p[i].bt, p[i].turn, p[i].wait);
    printf("--------------------------------------------------------------------------------------");
    printf("\nAverage Turnaround Time: %.2fms", avgturn);
    printf("\nAverage Waiting Time: %.2fms", avgwait);
    printf("\nCPU Utilization Time: %dms", y);
    // printf("\nContext Switch: %d", cs);
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