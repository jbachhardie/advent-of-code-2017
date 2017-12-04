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

let turtle = (lay, max) => {
  let coords = vec(100, 100);
  let plane = Array.make_matrix(201, 201, 0);
  let direction = ref(Right);
  let stepCount = ref(0);
  let stepLimit = ref(0);
  let prev = ref(0);
  while (prev^ < max) {
    let newValue = lay(plane, coords, prev^);
    plane[coords.x][coords.y] = newValue;
    prev := newValue;
    vectorSum(coords, stepInDirectionVector(direction^));
    let (newStepCount, newStepLimit, newDirection) = takeStep(stepCount^, stepLimit^, direction^);
    stepCount := newStepCount;
    stepLimit := newStepLimit;
    direction := newDirection;
  };
  coords;
};

let cartesianManhattanDistance = (a, b) => abs(a.x - b.x) + abs(a.y - b.y);

let manhattanDistance = (max) =>
  (max - 1)
  |> turtle((_, _, prev) => prev + 1)
  |> cartesianManhattanDistance(vec(100, 100));

let run = (fn, input) =>
  switch (input |> int_of_string) {
  | number => number |> fn |> Js.Int.toString
  | exception (Failure("int_of_string")) => "ERROR: Invalid input"
  };