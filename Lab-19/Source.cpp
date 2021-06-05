#include <iostream>
#include<stdio.h>
#pragma warning(default:4716)
using namespace std;
class image
{
private:
    size_t x, y;
    void* content = nullptr;

public:
    image(void* cnt) : content(cnt) {

    }

    image(image* cnt) : content(cnt->get_content()) {

    }

    ~image() {

    }

    void* get_content() { return this->content; }

    virtual void read() = 0;
    virtual void save() = 0;
    virtual void show() = 0;
    virtual void info() = 0;


    bool operator==(image& b) {
        return this->get_content() == b.get_content();
    }
};

class bmp : public image
{
public:
    bmp(void* loc) : image(loc) {}
    ~bmp() {}

    void read() { cout << "Reading bmp image" <<  endl; }
    void save() { cout << "Saving bmp image" <<  endl; }
    void show() { cout << "Showing bmp image" <<  endl; }
    void info() { cout << "Info about bmp image" <<  endl; }

    bmp& operator+(image& b) {
    cout << "Adding bmp images" <<  endl;
         }
    };

class creatorBase {
public:
    virtual image* operator()(void* loc) = 0;

    image* create(void* loc) {
    return this->operator()(loc);
    }
};

class createBmp : public creatorBase
{
public:
    bmp* operator()(void* loc) {
        bmp* tmp = new bmp(loc);
        return tmp;
    }
};

int main(int argc, char* argv[]) {

    creatorBase* bmpBuild = new createBmp();
    image* bmpImage = bmpBuild->operator()((void*)0);

    bmpImage->save();
    bmpImage->read();
    bmpImage->show();
    bmpImage->info();

    cout << ((*bmpImage) == (*bmpImage)) <<  endl;
    cout << (*((bmp*)(bmpImage)) + *((bmp*)(bmpImage))).get_content() <<  endl;
    getchar();
}