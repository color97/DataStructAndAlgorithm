#include <vector>
#include <string>

using namespace std;

void radixSortA(vector<string>& arr, int stringLen)
{
    const int BUCKET_SIZE = 256;
    vector<vector<string>>  buckets(BUCKET_SIZE);

    for(int pos = stringLen - 1; pos >= 0; --pos)
    {
        for(string & str : arr)
        {
            buckets[ str[ pos ]].push_back(std::move(str));
        }
        
        int index = 0;
        for(auto& bucket : buckets)
        {
            for(string& str : bucket)
            {
                arr[index++] = std::move(str);
            }

            bucket.clear();
        }
    }
}


void countingRadixSort(vector<string>& arr, int stringLen)
{
    const int BUCKET_SIZE = 256;
    const int N = arr.size();
    vector<string> buffer(N);

    vector<string>* in = &arr;
    vector<string>* out = &buffer;

    for(int pos = stringLen - 1; pos >= 0; --pos)
    {
        vector<int> count(BUCKET_SIZE + 1, 0);

        for(int i = 0; i < N; ++i)
        {
            ++count[ (*in)[ i ][ pos ] + 1 ];
        }
        for(int k = 1; k <= BUCKET_SIZE; ++k)
        {
            count[ k ] += count[ k - 1 ];
        }

        for(int i = 0; i < N; ++i)
        {
            (*out)[ count[ (*in )[ i ][ pos ] ]++ ] = std::move( (*in)[ i ] );
        }

        std::swap(in, out);
    }

    if (stringLen % 2 == 1)
    {
        (*in) = std::move(*(out));
    }
}

void radixSort(vector<string>& arr, int maxLen)
{
    const int BUCKET_SIZE = 256;

    vector<vector<string>>  wordsByLength(maxLen + 1);
    vector<vector<string>>  buckets(BUCKET_SIZE);

    for(string& str : arr)
    {
        wordsByLength[ str.length() ].push_back(std::move(str));
    }
    
    int index = 0;
    for(auto& wordList : wordsByLength)
    {
        for(string& str: wordList)
        {
            arr[index++] = std::move(str);
        }
    }

    int startingIndex = arr.size();
    for(int pos = maxLen - 1; pos >= 0; --pos)
    {
        startingIndex -= wordsByLength[ pos + 1].size();
        
        for( int i = startingIndex; i < arr.size(); ++i)
        {
            buckets[ arr[i][pos] ].push_back(std::move(arr[i]));
        }
        
        index = startingIndex;
        for(auto& bucket : buckets)
        {
            for(string& str : bucket)
            {
                arr[index++] = std::move(str);
            }

            bucket.clear();
        }
    }
}