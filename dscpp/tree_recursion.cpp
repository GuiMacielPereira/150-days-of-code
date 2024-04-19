#include <CTurtle.hpp>

namespace ct = cturtle;

bool tree(ct::Turtle& turtle, int length) {

  if(length < 5){
    return true;
  }
  turtle.width(double(length)/5);
  turtle.forward(length);

  turtle.right(20);
  tree(turtle, length - 15);
  turtle.left(40);
  if (tree(turtle, length - 15)) {
    turtle.pencolor({"green"});
  } else {
    turtle.pencolor({"brown"});
  };
  turtle.right(20);
  turtle.back(length);
  return false;
}

int main() {
    ct::TurtleScreen screen;
    ct::Turtle turtle(screen);
    turtle.pencolor({"brown"});

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
