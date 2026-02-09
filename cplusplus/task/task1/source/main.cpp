
#include <cstdlib>
#include <ctime>
#include <vector>

#include "add.hpp"
#include "ball.hpp"

void reward_projectile()
{
    cout << "Congratulations on your success, you will receive the following rewards:\n" << endl;

    //instantiate projectiles
    Projectile BigProjectile;        
    BigProjectile.set_projectile("BigProjectile", 42, 0.958, false);
    Projectile SmallProjectile;       
    SmallProjectile.set_projectile("SmallProjectile", 17, 1.598, true);


    
    //Use vector to store any number of "projectile" classes and try to output
    vector<Projectile> projectiles;
    int totalCount = rand()%10 + 1;
    for(int i=0; i<totalCount; i++)
    {
        if(rand()%2 == 0)
        {
            projectiles.push_back(BigProjectile);
        }
        else
        {
            projectiles.push_back(SmallProjectile);
        }
    }
    for(int i=0; i<projectiles.size(); i++)
    {
        cout << "No." << (i+1) << " projectile" << endl;
        projectiles[i].set_Fluorescent();
        projectiles[i].print_projectile();
        cout << endl;
    }
}

int main()
{
    int A = 0;
    int count0 = 0;
    int last0 = 0;
    int day = 0;
    int pre2 = 1, pre1 = 1;     //Fibonacci

    srand(time(0));     //set the random state

    while(A<100)
    {
        day++;
        int status = rand()%2;
        int currentExp = 0;

        switch(status)
        {
            case 0:     //addition mechanism
            {
                count0++;
                if(count0 <= 2)
                {
                    currentExp = 1;
                }
                else
                {
                    currentExp = add(pre2, pre1);     //pass-by-value
                    pre2 = pre1;
                    pre1 = currentExp;
                }
                last0 = currentExp;
                A += last0;
                cout << "day" << day << ":study\n"
                     << "gain experience " << currentExp << ", A=" << A << '\n' << endl;
                break;
            }
            case 1:     //deduction mechanism
            {
                int rec = last0 / 2;
                int temp = - rec;
                add(A, temp, A);     //pass-by-reference
                if(A < 0)
                {
                    A = 0;
                }
                cout << "day" << day << ":play game\n"
                     << "reduce experience " << rec<< ", A=" << A << '\n' << endl;
                break;
            }
            default:
                break;
        }
    }
    
    //reward
    cout << "YOU ARE WELCOME TO PIONEER!" << endl;
    reward_projectile();

    return 0;
}