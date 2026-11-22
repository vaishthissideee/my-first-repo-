#include <stdio.h>
#include <string.h>

int id[50], qty[50], n=0;
float price[50];
char name[50][30];

void save()
{
    FILE *f=fopen("medicine.txt","w");
    for(int i=0;i<n;i++)
        fprintf(f,"%d %s %d %.2f\n",id[i],name[i],qty[i],price[i]);
    fclose(f);
}

void add()
{
    printf("Enter ID, Name, Quantity, Price: ");
    scanf("%d %29s %d %f",&id[n],name[n],&qty[n],&price[n]);
    n++;
    save();
}

void display()
{
    for(int i=0;i<n;i++)
        printf("%d %s %d %.2f\n",id[i],name[i],qty[i],price[i]);
}

void search()
{
    int x;
    printf("Enter ID: ");
    scanf("%d",&x);

    for(int i=0;i<n;i++)
        if(id[i]==x)
        {
            printf("%s Quantity:%d Price:%.2f\n",name[i],qty[i],price[i]);
            return;
        }
    printf("Medicine not found!\n");
}

void update()
{
    int x;
    printf("Enter ID and new quantity: ");
    scanf("%d",&x);

    for(int i=0;i<n;i++)
        if(id[i]==x)
        {
            scanf("%d",&qty[i]);
            save();
            return;
        }
    printf("Medicine not found!\n");
}

void deleteMedicine()
{
    int x;
    printf("Enter ID: ");
    scanf("%d",&x);

    for(int i=0;i<n;i++)
        if(id[i]==x)
        {
            for(int j=i;j<n-1;j++)
            {
                id[j]=id[j+1];
                qty[j]=qty[j+1];
                price[j]=price[j+1];
                strcpy(name[j],name[j+1]);
            }
            n--;
            save();
            return;
        }
    printf("Medicine not found!\n");
}

void lowStock()
{
    for(int i=0;i<n;i++)
        if(qty[i]<10)
            printf("%s has low stock!\n",name[i]);
}

void expiryCheck()
{
    int day,month,year;
    printf("Enter today's date (DD MM YYYY): ");
    scanf("%d%d%d",&day,&month,&year);

    for(int i=0;i<n;i++)
    {
        int ed,em,ey;
        printf("Enter expiry date for %s (DD MM YYYY): ",name[i]);
        scanf("%d%d%d",&ed,&em,&ey);

        if(ey<year || (ey==year && em<month) ||
          (ey==year && em==month && ed<day))
            printf("%s is expired!\n",name[i]);
        else
            printf("%s is not expired.\n",name[i]);
    }
}

void sort()
{
    for(int i=0;i<n-1;i++)
        for(int j=0;j<n-i-1;j++)
            if(price[j]>price[j+1])
            {
                int t=id[j]; id[j]=id[j+1]; id[j+1]=t;
                t=qty[j]; qty[j]=qty[j+1]; qty[j+1]=t;

                float p=price[j];
                price[j]=price[j+1]; price[j+1]=p;

                char s[30];
                strcpy(s,name[j]);
                strcpy(name[j],name[j+1]);
                strcpy(name[j+1],s);
            }
    save();
    display();
}

void sell()
{
    int x,a;
    printf("Enter ID and quantity sold: ");
    scanf("%d%d",&x,&a);

    for(int i=0;i<n;i++)
        if(id[i]==x && a>0 && a<=qty[i])
        {
            qty[i]-=a;
            printf("Total amount: %.2f\n",a*price[i]);
            save();
            return;
        }
    printf("Invalid ID or quantity!\n");
}

void load()
{
    FILE *f=fopen("medicine.txt","r");
    if(f==NULL) return;

    while(n<50 && fscanf(f,"%d %29s %d %f",
          &id[n],name[n],&qty[n],&price[n])==4)
        n++;

    fclose(f);
}

int main()
{
    int ch;
    load();

    do
    {
        printf("\n1.Add 2.Display 3.Search 4.Update");
        printf("\n5.Delete 6.Expiry 7.Low Stock");
        printf("\n8.Sort 9.Sell 0.Exit\n");

        scanf("%d",&ch);

        switch(ch)
        {
            case 1: add(); break;
            case 2: display(); break;
            case 3: search(); break;
            case 4: update(); break;
            case 5: deleteMedicine(); break;
            case 6: expiryCheck(); break;
            case 7: lowStock(); break;
            case 8: sort(); break;
            case 9: sell(); break;
            case 0: save(); break;
            default: printf("Invalid choice!\n");
        }
    }while(ch!=0);

    return 0;
}
