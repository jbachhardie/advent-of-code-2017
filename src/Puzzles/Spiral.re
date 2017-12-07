type direction =
  | Left
  | Right
  | Up
  | Down;

type vector = {
  mutable x: int,
  mutable y: int
};

let vec = (x, y) => {x, y};

let rotateCounterClockwise = (direction) =>
  switch direction {
  | Left => Down
  | Right => Up
  | Up => Left
  | Down => Right
  };

let stepInDirectionVector = (direction) =>
  switch direction {
  | Right => vec(1, 0)
  | Left => vec(-1, 0)
  | Up => vec(0, 1)
  | Down => vec(0, -1)
  };

let vectorSum = (a, b) => {
  a.x = a.x + b.x;
  a.y = a.y + b.y;
};

let takeStep = (stepCount, stepLimit, direction) =>
  switch (stepCount == stepLimit, direction) {
  | (false, _) => (stepCount + 1, stepLimit, direction)
  | (true, Up)
  | (true, Down) => (0, stepLimit + 1, rotateCounterClockwise(direction))
  | (true, _) => (0, stepLimit, rotateCounterClockwise(direction))
  };

let turtle = (layFn, max) => {
  let coords = vec(100, 100);
  let plane = Array.make_matrix(201, 201, 0);
  let lay = () => {
    let newVal = layFn(plane, coords);
    plane[coords.x][coords.y] = newVal;
    newVal;
  };
  let rec takeStep = (stepCount, stepLimit, direction) =>
    if (lay() <= max) {
      vectorSum(coords, stepInDirectionVector(direction));
      switch (stepCount == stepLimit, direction) {
      | (false, _) => takeStep(stepCount + 1, stepLimit, direction)
      | (true, Up)
      | (true, Down) => takeStep(0, stepLimit + 1, rotateCounterClockwise(direction))
      | (true, _) => takeStep(0, stepLimit, rotateCounterClockwise(direction))
      };
    } else {
      (coords, plane);
    };
  takeStep(0, 0, Right);
};

let cartesianManhattanDistance = (a, b) => abs(a.x - b.x) + abs(a.y - b.y);

let manhattanDistance = (limit) => {
  let i = ref(0);
  let (finalCoords, _finalState) =
    turtle(
      (_, _) => {
        i := i^ + 1;
        i^;
      },
      limit - 1
    );
  cartesianManhattanDistance(vec(100, 100), finalCoords);
};

let maxSurroundingSum = (limit) => {
  let (finalCoords, finalState) =
    turtle(
      (plane, coords) =>
        max(
          1,
          plane[coords.x - 1][coords.y - 1]
          + plane[coords.x - 1][coords.y]
          + plane[coords.x - 1][coords.y + 1]
          + plane[coords.x][coords.y + 1]
          + plane[coords.x][coords.y - 1]
          + plane[coords.x + 1][coords.y - 1]
          + plane[coords.x + 1][coords.y]
          + plane[coords.x + 1][coords.y + 1]
        ),
      limit
    );
  finalState[finalCoords.x][finalCoords.y];
};

let run = (fn, input) =>
  switch (input |> int_of_string) {
  | number => number |> fn |> Js.Int.toString
  | exception (Failure("int_of_string")) => "ERROR: Invalid input"
  };