open Jest;

test(
  "basic sum",
  () => Expect.(expect(InstructionMaze.run((x) => x + 1, {|0
3
0
1
-3|})) |> toBe("5"))
);

test(
  "conditional transform",
  () =>
    Expect.(
      expect(InstructionMaze.run((x) => x > 2 ? x - 1 : x + 1, {|0
3
0
1
-3|})) |> toBe("10")
    )
);