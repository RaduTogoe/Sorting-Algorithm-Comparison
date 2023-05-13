#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
void    print(int*, int, FILE*);
void    optimized_bubble_sort(int*, int);
void    bubble_sort(int*, int);
void    selection_sort(int*, int);
int*    desc(int);
int*    cresc(int);
void    insertion_sort(int*, int);
void    merge(int*, int,  int, int);
void    merge_sort(int*, int, int);
int    get_max(int*, int);
int     maxim(int*, int);
void    countSort(int*, int);
void    countingSort(int*, int, int);
void    radix_sort(int*, int);
void    quick_sort(int*, int, int);
int     pivot(int*, int, int);
int     *generare(int);

int main()
{
    int i, k1, k2, nr_lists, *v;
    long long int nr_elem;
    FILE *f = fopen("liste.out", "w");
    time_t t;
    srand((unsigned) time(&t));
    printf("What should be the number of lists?\n");
    scanf("%d", &nr_lists);
    printf("What should be the number of elements of each list?\n");
    scanf("%lld", &nr_elem);
    printf("How should the data be sorted before applying the sorting algorithm?\n");
    printf("1.Increasing Order\t2.Decreasing Order\t3.Random Order\n");
    scanf("%d", &k2);
    double time = 0;
    printf("Execution time for each sorted list\n");
    for (i = 1; i <= nr_lists; i++)
    {
        
        double time_spent = 0.0;
        switch (k2)
        {
            case 1:
                v = cresc(nr_elem);
                break;
            case 2:
                v = desc(nr_elem);
                break;
            case 3:
                v = generare(nr_elem);
                break;
        }
            clock_t  begin = clock();
            radix_sort(v, nr_elem);
            clock_t end = clock();

       
        time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
        print(v, nr_elem, f);
        free(v); 
        printf("\n%lf\n", time_spent);
    }
}

int getMax(int a[], int n) {  
   int max = a[0];  
   for(int i = 1; i<n; i++) {  
      if(a[i] > max)  
         max = a[i];  
   }  
   return max;  
}  
  
void countSort(int a[], int n)  
{  
   int output[n+1];  
   int max = getMax(a, n);  
   int count[max+1]; 
  
  
  for (int i = 0; i <= max; ++i)   
  {  
    count[i] = 0; 
  }  
    
  for (int i = 0; i < n; i++) 
  {  
    count[a[i]]++;  
  }  
  
   for(int i = 1; i<=max; i++)   
      count[i] += count[i-1];   
  
  
   for(int i = 0; i<n; i++) {  
      a[i] = output[i];
   }  
}  

void    merge(int *v, int st, int mij, int dr)
{
    int i, j, x;
    int n1 = mij-st+1;
    int n2 = dr-mij;
    int v1[n1];
    int v2[n2];
    for (i = 0; i < n1; i++)
        v1[i] = v[st + i];
    for (j = 0; j < n2; j++)
        v2[j] = v[mij + 1 + j];
    i = 0;
    j = 0;
    x = st;
    while (i < n1 && j < n2)
    {
        if (v1[i] < v2[j])
            v[x] = v1[i++];
        else
            v[x] = v2[j++];
        x++;
    }
    while (i < n1)
        v[x++] = v1[i++];
    while (j < n2)
        v[x++] = v2[j++];
}

void    merge_sort(int *v, int st, int dr)
{
    if (st < dr)
    {
        int mij = st + (dr-st) / 2;
        merge_sort(v, st, mij);
        merge_sort(v, mij+1, dr);
        merge(v, st, mij, dr);
    }
}

int     pivot(int *v, int st, int dr)
{
    int mij = v[(st + dr) / 2];
    int aux;
    while (st <= dr)
    {
        while (v[st] < mij)
            st++;
        while (v[dr] > mij)
            dr--;
        if (st <= dr)
        {
            aux = v[st];
            v[st] = v[dr];
            v[dr] = aux;
            dr--;
            st++;
        }
    }
    return (st);
}

void    quick_sort(int *v, int st, int dr)
{
    if (st >= dr)
        return;
    int q = pivot(v, st, dr);
    quick_sort(v, st, q-1);
    quick_sort(v, q, dr);
}

void    print(int *v, int n, FILE *f)
{
    int i;
    for (i = 0; i < n; i++)
        fprintf(f, "%d ", v[i]);
    fprintf(f, "\n");
}

int*    cresc(int nr_elem)
{
    int i;
    int *v = malloc(sizeof(int) * nr_elem);

    for (int i = 0; i < nr_elem; i++)
        v[i] = i + 1;
    return (v);
}

int*    desc(int nr_elem)
{
    int i, k;
    int *v = malloc(sizeof(int) * nr_elem);

    k = nr_elem;
    for (i = 0; i < nr_elem; i++)
        v[i] = k--;
    return (v);
}

void    insertion_sort(int *v, int n)
{
    int i, j, aux;
    for (i = 1; i < n; i++)
    {
        aux = v[i];
        j = i-1;
        while (j >= 0 && v[j] > aux)
        {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = aux;
    }
}

void    selection_sort(int *v, int n)
{
    int i, j, aux;
    for (i = 0; i < n - 1; i++)
    {
        int minim = i;;
        for (j = i + 1; j < n; j++)
            if (v[j] < v[minim])
                minim = j;
        aux = v[minim];
        v[minim] = v[i];
        v[i] = aux;
    }
}

void    bubble_sort(int *v, int n)
{
    int i, j;

    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (v[j] > v[j+1])
            {
                int aux = v[j];
                v[j] = v[j+1];
                v[j+1] = aux;
            }
}

void    optimized_bubble_sort(int *v, int n)
{
    int ok = 1, i;

    do{
        ok = 1;
        for (i = 0; i < n - 1; i++)
            if (v[i] > v[i + 1])
            {
                int aux = v[i];
                v[i] = v[i + 1];
                v[i + 1]= aux;
                ok = 0;
            }
    }while (ok == 0);
}  
  
void countingSort(int a[], int n, int place) {  
  int output[n + 1];  
  int count[10] = {0};    
  
   for (int i = 0; i < n; i++)  
    count[(a[i] / place) % 10]++;  
      
   for (int i = 1; i < 10; i++)  
    count[i] += count[i - 1];  
    
  for (int i = n - 1; i >= 0; i--) {  
    output[count[(a[i] / place) % 10] - 1] = a[i];  
    count[(a[i] / place) % 10]--;  
  }  
  
  for (int i = 0; i < n; i++)  
    a[i] = output[i];  
}  
  
  
void radix_sort(int a[], int n) {  
  int max = getMax(a, n);  
  for (int place = 1; max / place > 0; place *= 10)  
    countingSort(a, n, place);  
}  

int     *generare(int nr_elem)
{
    int i, k = 0;

    int *v = malloc(sizeof(int) * nr_elem);
    for (i = 1; i <= nr_elem; i++)
        v[k++] = rand() % 100000;
    return (v);
}
