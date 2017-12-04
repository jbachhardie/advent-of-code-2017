type direction =
  | Left
  | Right
  | Up
  | Down;

let rotateCounterClockwise = (direction) =>
  switch direction {
  | Left => Down
  | Right => Up
  | Up => Left
  | Down => Right
  };

let spiralToCartesian = (spiralIndex) => {
  let x = ref(-1);
  let y = ref(0);
  let direction = ref(Right);
  let steps = ref(-1);
  let stepLimit = ref(1);
  for (_ in 1 to spiralIndex) {
    switch direction^ {
    | Right => x := x^ + 1
    | Left => x := x^ - 1
    | Up => y := y^ + 1
    | Down => y := y^ - 1
  };
  steps := steps^ + 1;
  if (steps^ == stepLimit^) {
    direction := rotateCounterClockwise(direction^);
    steps := 0;
    if (direction^ == Left || direction^ == Right) {
      stepLimit := stepLimit^ + 1;
    };
  };
  };
  (x^, y^);
};

let cartesianManhattanDistance = ((p1, p2), (q1, q2)) => abs(p1 - q1) + abs(p2 - q2);

let manhattanDistance = (spiralIndex) =>
  spiralIndex |> spiralToCartesian |> cartesianManhattanDistance((0, 0));

let run = (fn, input) =>
  switch (input |> int_of_string) {
  | number => number |> fn |> Js.Int.toString
  | exception (Failure("int_of_string")) => "ERROR: Invalid input"
  };