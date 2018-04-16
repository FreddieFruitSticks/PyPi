#ifndef TOKEN_STREAM_H
#define TOKEN_STREAM_H
#include <vector>
#include <Scanner.h>

class TokenStream{
    private:
        std::vector<TOKEN> tokens;
        TOKEN* tokenPtr;
    public:
        TokenStream(std::vector<TOKEN> tokens);
        ~TokenStream();
        TOKEN peekCurrent();
        TOKEN peekNext();
        TOKEN pop();
        void moveToNext();
};

#endif