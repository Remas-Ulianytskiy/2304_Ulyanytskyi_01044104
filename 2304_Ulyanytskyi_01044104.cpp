#include <iostream>

using namespace std;

class PaintApi {
public:
    PaintApi() {}
    virtual ~PaintApi() {}
    virtual void DrawRectangle(int x, int y, int endx, int endy) = 0;
};

class Figure {
protected:
    unique_ptr<PaintApi> api;

public:
    Figure(unique_ptr<PaintApi> pApi) : api(move(pApi)) {}

    virtual ~Figure() = default;

    virtual void DrawFigure() const = 0;
};

class Rectangle : public Figure {
private:
    int x;
    int y;
    int endx;
    int endy;

public:
    Rectangle(int pX, int pY, int pEndX, int pEndY, unique_ptr<PaintApi> pApi)
        : Figure(move(pApi)), x(pX), y(pY), endx(pEndX), endy(pEndY)
    {}

    virtual ~Rectangle() = default;

    void DrawFigure() const override { api->DrawRectangle(x, y, endx, endy); }
};

class BlackRectangle : public PaintApi {
public:
    BlackRectangle() {}

    virtual ~BlackRectangle() {}

    void DrawRectangle(int x, int y, int endx, int endy) override 
    {
        cout << "Draw Black Rectangle\n x = " << x << " y = " << y << " endx = " << endx << " endy = " << endy << endl;
    }
};

class BlueRectangle : public PaintApi {
public:
    BlueRectangle() {}

    virtual ~BlueRectangle() {}

    void DrawRectangle(int x, int y, int endx, int endy) override 
    {
        cout << "Draw Blue Rectangle\n x = " << x << " y = " << y << " endx = " << endx << " endy = " << endy << endl;
    }
};

int main() {
    unique_ptr<Figure> blackRectangle = make_unique<Rectangle>(10, 10, 100, 100, make_unique<BlackRectangle>());
    unique_ptr<Figure> blueRectangle = make_unique<Rectangle>(20, 20, 200, 200, make_unique<BlueRectangle>());

    blackRectangle->DrawFigure();
    blueRectangle->DrawFigure();

    return 0;
}
