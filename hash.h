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
        unsigned long long w[5]= {0,0,0,0,0};
        int strleftlen= k.size();
        int wIndex =4;

        while(strleftlen>0)
        {
          if(strleftlen >6 && wIndex >=0)
          {
            int count =0;
            for( int i =strleftlen -1; i>= strleftlen -6; i--)
            {
              w[wIndex]+= letterDigitToNumber(k[i])* pow(36, count);
              count++;
            }
            strleftlen -= 6; 
            wIndex--;
          }
          else if(strleftlen != 0 && wIndex >=0)
          {
            int count_ =0;
            for( int i =strleftlen -1; i>= 0; i--)
            {
              w[wIndex]+= letterDigitToNumber(k[i])* pow(36, count_);
              count_++;
            }
            strleftlen =0; 
          }
        }

        HASH_INDEX_T hashes =0;
        for(int i =0; i< 5; i++)
        {
          hashes += rValues[i] * w[i];
        }
        return hashes; 

    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
       if(letter >= 48 && letter <= 57){
            return letter - 22;
        }

        // if capital convert to lower
        else if(letter >= 65 && letter <= 90){
            letter = letter + 32;
        }

        return letter - 97;

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
