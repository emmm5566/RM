#include <iostream>
#include <vector>



void print_vector(std::vector<int>& v)
{
    for(std::vector<int>::iterator it = v.begin(); it != v.end(); it++)
    {
        std::cout << *it << " ";
    }
    std::cout << "\n" << std::endl;
}

int is_prime(int n)
{
    for (int i = 3; i*i < n; i+=2)   //1、2和偶数都解决了
    {
        if (n % i == 0)
        {
            return 0;   //不是质数
        }
    }
    return 1;   //是质数
}



int main()
{
    //使用数组存1~10000中13的倍数
    std::vector<int> vec1;
    for(int i=1; i<=10000; i++)
    {
        if(0 == i%13)
        {
            vec1.push_back(i);
        }
    }
    print_vector(vec1);



    //使用vector存1~10000中13的倍数
    std::vector<int> vec2;
    for(int i=1; i<=100; i++)
    {
        vec2.push_back(i);
    }
    print_vector(vec2);
    for(int i=vec2.size(); i>0; i--)
    {
        if(vec2[i-1]%2 != 0)
        {
            vec2.erase(vec2.begin() +i -1);
        }
    }
    print_vector(vec2);



    //使用vector存放分别存储1到100之间的单数、1到100之间的双数、1到100之间的质数的vector，并输出同时是单数和质数的数值
    std::vector<int> vOdd, vEven, vPrime;
    for (int i = 1; i <= 100; i++)
    {
        if (1 == i)
        {
            vOdd.push_back(i);
        }
        else if (2 == i)
        {
            vEven.push_back(i);
            vPrime.push_back(i);
        }
        else if (i % 2 == 0)   //偶数不是质数
        {
            vEven.push_back(i);
        }
        else
        {
            vOdd.push_back(i);
            if (is_prime(i))
            {
                vPrime.push_back(i);
                std::cout << i << " ";
            }
        }
    }
    

    return 0;
}
