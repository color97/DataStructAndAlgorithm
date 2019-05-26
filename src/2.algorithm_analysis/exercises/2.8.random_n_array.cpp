#include <vector>
#include <iostream>
#include <random>
#include <ctime>

using namespace std;

int randInt(int low, int high)
{
    static std::random_device rd;  //Will be used to obtain a seed for the random number engine
    static std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dis(low, high);
    return dis(gen); // generate random int [low, high]
}

// O((N^2)logN)
vector<int> random_n_array_1(int N)
{
    vector<int> randomArray(N);

    for (size_t i = 0; i < N; i++)
    {
        // loop until break
        while (true)
        {
            const int thisRandom = randInt(1, N);
            bool isRepeat = false;
            for (size_t j = 0; j < i; j++)
            {
                if(randomArray[j] == thisRandom)
                {
                    isRepeat = true;
                    break;
                }
            }

            if (!isRepeat)
            {
                randomArray[i] = thisRandom;
                break;
            }           
        }       
    }

    return randomArray;
}

// O(NlogN)
vector<int> random_n_array_2(int N)
{
    vector<int> randomArray(N);
    // N + 1, because randomArray [1, N]
    vector<bool> used(N + 1, false);

    for (size_t i = 0; i < N; i++)
    {
        while (true)
        {
            const int thisRandom = randInt(1, N);

            if (!used[thisRandom])
            {
                randomArray[i] = thisRandom;
                used[thisRandom] = true;
                break;
            }           
        }       
    }

    return randomArray;
}

// O(N)
vector<int> random_n_array_3(int N)
{
    vector<int> randomArray(N);
    for (size_t i = 0; i < N; i++)
    {
        randomArray[i] = i + 1;
    }

    for (size_t i = 1; i < N; i++)
    {
        swap(randomArray[i], randomArray[randInt(0, i - 1)]);
    }
     
    return randomArray;
}


int main()
{
    const vector<vector<int> > nArrays = {
        {250, 500, 1000, 2000},
        {25000, 50000, 100000, 200000, 400000, 800000},
        {100000, 200000, 400000, 800000, 1600000, 3200000, 6400000}
    };
    
    for (size_t i = 0; i < nArrays.size(); i++)
    {
        for (size_t j = 0; j < nArrays[i].size(); j++)
        {
            clock_t beginTime = clock();
            for (size_t k = 0; k < 10; k++)
            {
                switch (i)
                {
                case 0:
                    random_n_array_1(nArrays[i][j]);
                    break;
                case 1:
                    random_n_array_2(nArrays[i][j]);
                    break;
                case 2:
                    random_n_array_3(nArrays[i][j]);
                    break;                
                default:
                    break;
                }
            }            
            clock_t endTime = clock();
            double averageTime = (endTime - beginTime) / (CLOCKS_PER_SEC * 10.0);
            cout<<"program("<<i+1<<"), for N = "<<nArrays[i][j]<<", average time: "<<averageTime<<"s\n";
        }    
    }
    
    return 0;
}