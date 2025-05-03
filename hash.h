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
        std:: string lower_key = k;
        for(size_t i =0; i<lower_key.length(); ++i){
            if(std::isupper(lower_key[i])){
                lower_key[i]= std::tolower(lower_key[i]);
            }
        }
        int len = lower_key.length();
        unsigned long long w[5] = {0};
        int group = 0;
        for(int i = len -1; group<5 && i>=0; ++group)
        {
        
            unsigned long long pow= 1;
            unsigned long long val =0;
            for (int j =0; i>=0 && j<6; ++j, --i){
                val+= letterDigitToNumber(lower_key[i])*pow;
                pow*=36;
            }
            w[4-group] = val;
        }


        HASH_INDEX_T hashVal = 0;
        for( int i=0; i<5;++i){
            hashVal+=w[i]*rValues[i];
        }
       
        return hashVal;


    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if(letter>='a'&&letter <='z'){
            return letter - 'a';
        }
        else if(letter <='9'&& letter>='0'){
            return letter -'0'+26;
        }
        else{
            return 0;
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
