// TODO: Change the color of the pixel for different numbers of
    if (steps <= 5) {
      color.red = 250 - (2*steps);
      color.green = 125 + (5*steps);
      color.blue = 150 - (2*steps);
    } else if (steps <= 15) {
      color.red = 240 - 4*(steps - 5);
      color.green = 150 - (steps - 5);
      color.blue = 140 + (10*(steps - 5));
    } else if (steps <= 25) {
      color.red = 3*(steps - 15) + 200;
      color.green = 100 + 8*(steps - 15);
      color.blue = 240 + (steps - 15);
    } else if (steps <= 225) {
      color.red = 230 - steps;
      color.green = 180;
      color.blue = 250;
    } else if (steps <= 250) {
      color.red = 160;
      color.green = 255;
      color.blue = 240;
    } else {
      color.red = 255;
      color.green = 255;
      color.blue = 255;
    }
