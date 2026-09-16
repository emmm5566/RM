// //Enter a score, output "pass" if greater than 60, and "fail" if less than 60 (using switch).

// #include <iostream>
// using namespace std;

// int main()
// {
//     double score = 0;
//     cin >> score;
    
//     int flag = 0;  //mark failing grades as 0
//     if(score >= 60)
//     {
//         flag = 1;
//     }

//     ////The "either-or" choice can be simplified using the ternary operator.
//     //int flag = (score >= 60) ? 1 : 0;

//     switch(flag)
//     {
//         case 0:
//             cout << "Fail" << endl;
//             break;
//         case 1:
//             cout << "Pass" << endl;
//             break;
//         default:
//             cout << "Error" << endl;
//      }

//     return 0;
// }