#include <CTurtle.hpp>
#include <CImg.h>

namespace ct = cturtle;

void tree(ct::Turtle& turtle, int length) {
    if(length > 5){
        turtle.forward(length);
        turtle.right(20);
        tree(turtle, length - 15);
        turtle.left(40);
        tree(turtle, length - 15);
        turtle.right(20);
        turtle.back(length);
    }
}

int main() {
    ct::TurtleScreen screen;
    // screen.tracer(3);//Draw faster.
    ct::Turtle turtle(screen);
    turtle.pencolor({"green"});

    //Make the trees "grow" upwards
    turtle.left(90);

    //Start growing from further down.
    turtle.penup();
    turtle.backward(100);
    turtle.pendown();

    //Draw the tree.
    tree(turtle, 75);

    screen.bye();
    return 0;
}
