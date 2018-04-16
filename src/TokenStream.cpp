#include <TokenStream.h>

TokenStream::TokenStream(std::vector<TOKEN> tokensIn){
    tokens = tokensIn;
    tokenPtr = &tokens[0];    
}

TokenStream::~TokenStream(){
    delete [] tokenPtr;
}

TOKEN TokenStream::peekCurrent(){
    return *tokenPtr;
}
TOKEN TokenStream::peekNext(){
    TOKEN nextToken = *++tokenPtr;
    tokenPtr--;
    return nextToken;
}

TOKEN TokenStream::pop(){
    TOKEN token = *tokenPtr;
    tokenPtr++;
    return token;
}

void TokenStream::moveToNext(){
    tokenPtr++;
}
