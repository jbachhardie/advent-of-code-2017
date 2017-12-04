open Jest;

testAll(
  "spiral manhattan",
  [(1, 0), (4, 1), (12, 3), (23, 2), (1024, 31)],
  ((input, expected)) => Expect.(expect(Spiral.manhattanDistance(input)) |> toBe(expected))
);