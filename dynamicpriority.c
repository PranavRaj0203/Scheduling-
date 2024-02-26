#include <stdio.h>
#include <conio.h>
#include <string.h>
struct process
{
    int pno, at, bt, turn, wait, pr, rem;
} p[20], temp;
void sort(int);
int n, clock = 0, cst[20], opt, d = 0;
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
        printf("Priority: ");
        scanf("%d", &p[i].pr);
        p[i].rem = p[i].bt;
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
    int totalwait = 0, totalturn = 0, idle = 0, idcst[20];
    memset(idcst, 0, n * sizeof(idcst[0]));
    for (i = 0; i < n; i++)
    {
        if (clock < p[i].at)
        {
            idle += p[i].at - clock;
            if (clock)
            {
                idcst[d] = 1;
                cst[d++] = clock;
            }
            clock = p[i].at;
            idcst[d] = 2;
        }
        cst[d++] = clock;
        while (p[i].rem != 0)
        {
            sort(i);
            clock++;
            p[i].rem--;
        }
        p[i].turn = clock - p[i].at;
        p[i].wait = p[i].turn - p[i].bt;
        totalwait += p[i].wait;
        totalturn += p[i].turn;
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
    printf("\nInput:\n");
    printf("------------------------------------------------------------------------\n");
    printf("Process id\tArrival Time(in ms)\tBurst Time(in ms)\tPriority\n");
    printf("------------------------------------------------------------------------\n");
    for (i = 0; i < n; i++)
        printf("%d\t\t%d\t\t\t%d\t\t\t%d\n", p[i].pno, p[i].at, p[i].bt, p[i].pr);
    printf("------------------------------------------------------------------------\n");
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
    printf("\nContext Switch: %d", d);
    printf("\nCPU Utilization percentage: %.2f percent", ut);
    printf("\nCPU Idle Time: %dms", idle);
    printf("\nContext switches:\n");
    for (i = 0; i < d; i++)
    {
        printf("%dms -> ", cst[i]);
        if (i == 0)
            printf("OS Context-> Process Context\n");
        else if (idcst[i] == 1)
            printf("Process Context -> OS Context\n");
        else if (idcst[i] == 2)
            printf("OS Context -> Process Context\n");
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
        else if (idcst[i] == 1)
            printf("User Mode -> Kernel Mode\n");
        else if (idcst[i] == 2)
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
    int i = x, j, min, flag = 0;
    min = p[x].pr;
    for (j = x + 1; j < n; j++)
    {
        if (p[j].at > clock)
            break;
        if (p[j].pr < min)
        {
            min = p[j].pr;
            i = j;
            flag = 1;
        }
        else if (p[j].pr == min && (p[j].at < p[i].at || (p[j].at == p[i].at && p[j].pno < p[i].pno)))
        {
            i = j;
            flag = 1;
        }
    }
    if (flag)
    {
        if (cst[d - 1] != clock)
            cst[d++] = clock;
        temp = p[x];
        p[x] = p[i];
        p[i] = temp;
    }
}