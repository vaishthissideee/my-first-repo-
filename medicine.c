#include <stdio.h>
#include <string.h>

int id[50], qty[50], n = 0;
float price[50];
char name[50][30];

void save()
{
    FILE *f = fopen("medicine.txt", "w");
    if (f == NULL)
        return;

    for (int i = 0; i < n; i++)
        fprintf(f, "%d %s %d %.2f\n", id[i], name[i], qty[i], price[i]);

    fclose(f);
}

void load()
{
    FILE *f = fopen("medicine.txt", "r");
    if (f == NULL)
        return;

    while (n < 50 && fscanf(f, "%d %29s %d %f",
                           &id[n], name[n], &qty[n], &price[n]) == 4)
        n++;

    fclose(f);
}

void add()
{
    if (n >= 50)
    {
        printf("Inventory full!\n");
        return;
    }

    int x;
    printf("Enter ID: ");
    if (scanf("%d", &x) != 1)
    {
        printf("Invalid ID!\n");
        return;
    }

    for (int i = 0; i < n; i++)
        if (id[i] == x)
        {
            printf("ID already exists!\n");
            return;
        }

    id[n] = x;

    printf("Enter Name, Quantity and Price: ");
    if (scanf("%29s %d %f", name[n], &qty[n], &price[n]) != 3)
    {
        printf("Invalid details!\n");
        return;
    }

    if (qty[n] < 0 || price[n] < 0)
    {
        printf("Invalid details!\n");
        return;
    }

    n++;
    save();
    printf("Medicine added!\n");
}

void display()
{
    for (int i = 0; i < n; i++)
        printf("%d %s %d %.2f\n", id[i], name[i], qty[i], price[i]);
}

void search()
{
    int x;
    printf("Enter ID: ");
    if (scanf("%d", &x) != 1)
    {
        printf("Invalid ID!\n");
        return;
    }

    for (int i = 0; i < n; i++)
        if (id[i] == x)
        {
            printf("%s Quantity:%d Price:%.2f\n", name[i], qty[i], price[i]);
            return;
        }

    printf("Medicine not found!\n");
}

void update()
{
    int x;
    printf("Enter ID: ");
    if (scanf("%d", &x) != 1)
    {
        printf("Invalid ID!\n");
        return;
    }

    for (int i = 0; i < n; i++)
        if (id[i] == x)
        {
            printf("Enter new quantity: ");
            if (scanf("%d", &qty[i]) != 1)
            {
                printf("Invalid quantity!\n");
                return;
            }

            if (qty[i] < 0)
            {
                printf("Invalid quantity!\n");
                return;
            }

            save();
            printf("Updated!\n");
            return;
        }

    printf("Medicine not found!\n");
}

void deleteMedicine()
{
    int x;
    printf("Enter ID: ");
    if (scanf("%d", &x) != 1)
    {
        printf("Invalid ID!\n");
        return;
    }

    for (int i = 0; i < n; i++)
        if (id[i] == x)
        {
            for (int j = i; j < n - 1; j++)
            {
                id[j] = id[j + 1];
                qty[j] = qty[j + 1];
                price[j] = price[j + 1];
                strcpy(name[j], name[j + 1]);
            }

            n--;
            save();
            printf("Deleted!\n");
            return;
        }

    printf("Medicine not found!\n");
}

void lowStock()
{
    for (int i = 0; i < n; i++)
        if (qty[i] < 10)
            printf("%s has low stock!\n", name[i]);
}

void expiryCheck()
{
    int day, month, year, ed, em, ey;

    printf("Enter today's date (DD MM YYYY): ");
    if (scanf("%d%d%d", &day, &month, &year) != 3)
    {
        printf("Invalid date!\n");
        return;
    }

    for (int i = 0; i < n; i++)
    {
        printf("Expiry date of %s (DD MM YYYY): ", name[i]);
        if (scanf("%d%d%d", &ed, &em, &ey) != 3)
        {
            printf("Invalid expiry date!\n");
            return;
        }

        if (ey < year || (ey == year && em < month) ||
            (ey == year && em == month && ed < day))
            printf("%s is expired!\n", name[i]);
        else
            printf("%s is not expired.\n", name[i]);
    }
}

void sort()
{
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (price[j] > price[j + 1])
            {
                int t = id[j];
                id[j] = id[j + 1];
                id[j + 1] = t;

                t = qty[j];
                qty[j] = qty[j + 1];
                qty[j + 1] = t;

                float p = price[j];
                price[j] = price[j + 1];
                price[j + 1] = p;

                char s[30];
                strcpy(s, name[j]);
                strcpy(name[j], name[j + 1]);
                strcpy(name[j + 1], s);
            }

    save();
    display();
}

void sell()
{
    int x, a;
    printf("Enter ID and quantity sold: ");
    if (scanf("%d%d", &x, &a) != 2)
    {
        printf("Invalid quantity!\n");
        return;
    }

    for (int i = 0; i < n; i++)
        if (id[i] == x)
        {
            if (a > 0 && a <= qty[i])
            {
                qty[i] -= a;
                printf("Total: %.2f\n", (float)a * price[i]);
                save();
            }
            else
                printf("Invalid quantity!\n");

            return;
        }

    printf("Medicine not found!\n");
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

        if (scanf("%d", &ch) != 1)
        {
            printf("Invalid choice!\n");
            ch = -1;
            continue;
        }

        switch (ch)
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
    } while (ch != 0);

    return 0;
}
