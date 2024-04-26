#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        unsigned long long wValues[5] = {0,0,0,0,0};
        
        int wValueNumber = 4;
        int size = k.size();
        
        HASH_INDEX_T helper[6]; //Stores the 0-35 number of the 6 characters, or the decimal value
        for (int i = size; i > 0; i-=6)
        {
            std::string substr;
            if (i < 6)
            {
                //int length = size % 6;
                substr = k.substr(0, i);
                for (int index = 0; index < 6-i; index++)
                {
                    substr = "a" + substr;
                }
            }
            else
            {
                substr = k.substr(i-6, 6);
            }
            
            for (size_t j = 0; j < substr.size(); j++)
            {
                helper[j] = letterDigitToNumber(substr[j]);
                //std::cout << substr[j] << std::endl;
            }
            
            wValues[wValueNumber] = (unsigned long long) helper[0];
            for (int k = 1; k < 6; k++)
            {
                wValues[wValueNumber] = wValues[wValueNumber] * 36 + helper[k];
            }
            //std::cout << "w[" << wValueNumber << "] = " << wValues[wValueNumber] << std::endl;
            wValueNumber--;
        }
        
        HASH_INDEX_T ret = rValues[0] * wValues[0];
        for (int a = 1; a <= 4; a++)
        {
            ret += (rValues[a] * wValues[a]);
        }
        
        return ret;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        letter = tolower(letter);
        if (letter >= 'a' && letter <= 'z')
        {
            return letter - 'a';
        }
        else
        {
            return letter - '0' + 26;
        }

    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
