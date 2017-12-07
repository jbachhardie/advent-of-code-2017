open Jest;

testAll(
  "spiral manhattan",
  [(1, 0), (4, 1), (12, 3), (23, 2), (1024, 31)],
  ((input, expected)) => Expect.(expect(Spiral.manhattanDistance(input)) |> toBe(expected))
);

testAll(
  "spiral adjacent sum",
  [(1, 2), (4, 5), (12, 23), (23, 25), (362, 747)],
  ((input, expected)) => Expect.(expect(Spiral.maxSurroundingSum(input)) |> toBe(expected))
);