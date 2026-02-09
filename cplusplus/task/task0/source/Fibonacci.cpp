// #include <iostream>
// #include <cstdlib>
// #include <ctime>
// using namespace std;

// int main()
// {
//     ////srand((unsigned int)time(NULL));
//     srand(time(0));

//     int A = 0;         //experience value at last status 0
//     int count0 = 0;    //status 0 appears
//     int last0 = 0;     //accumulated experience value
//     int pre1 = 1, pre2 = 0;   //FibonacciSequence, previous 1 or 2 item

//     while(1)
//     {

//     //set random status
//     int status = rand() % 2;

//     //reward mechanism
//     switch(status)
//     {
//         case 0:
//         {
//             count0++;
//             ////currentExp doesn't depend on previous calculations, so it is placed inside the loop
//             ////it is syntactically correct when placed outside the loop, but semantically incorrect and unsafe
//             ////pre1 and pre2 rely on previous calculations, so they are placed outside the loop
//             int currentExp = 0;     //experience value for today, recalculated with each cycle

//             ////it is right to write if(count0<=2){currentExp=1;}, which is logically uncorrect
//             if(count0 == 1)
//             {
//                 currentExp = 1;
//             }
//             else if(count0 == 2)
//             {
//                 currentExp = 1;
//                 pre2 = 1;
//             }
//             else
//             {
//                 currentExp = pre1 + pre2;
//                 pre2 = pre1;
//                 pre1 = currentExp;
//             }
//             last0 = currentExp;
//             A += currentExp;
//             break;
//         }
//         case 1:
//         {
//             ////add boundary case handing: experience is reduced only when count0>0
//             ////if(count0 > 0)
//             ////the integer operation loses accuracy and can be changed to double type
//             ////double A -= last0 / 2.0;
//             A -= last0/2;
//             break;
//         }
//         default:
//             break;
//     }

//     ////change the while loop condition to while(A<100)
//     if(A >= 100)
//     {
//         cout << "YOU ARE WELCOME TO JOIN PIONEER!" << endl;
//         break;
//     }

//     }

//     return 0;
// }