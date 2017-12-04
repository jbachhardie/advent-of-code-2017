open Jest;

testAll(
  "spiral manhattan",
  [(1, 0), (12, 3), (23, 2), (1024, 31)],
  ((input, expected)) => Expect.(expect(Spiral.manhattanDistance(input)) |> toBe(expected))
);

testAll(
  "spiral to cartesian",
  [
    (1, (0, 0)),
    (2, (1, 0)),
    (3, (1, 1)),
    (4, (0, 1)),
    (5, ((-1), 1)),
    (6, ((-1), 0)),
    (7, ((-1), (-1))),
    (8, (0, (-1))),
    (9, (1, (-1))),
    (23, (0, (-2)))
  ],
  ((input, expected)) => Expect.(expect(Spiral.spiralToCartesian(input)) |> toEqual(expected))
);