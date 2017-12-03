open Jest;

test(
  "calculate",
  (_) => Expect.(expect(Spreadsheet.calculate({|5 1 9 5
7 5 3
2 4 6 8|})) |> toBe("18"))
);

test(
    "parse_tsv",
    (_) => Expect.(expect(Spreadsheet.parse_tsv({|5 1 9 5
7 5 3
2 4 6 8|})) |> toEqual([|[|5, 1, 9, 5|], [|7, 5, 3|], [|2, 4, 6, 8|]|]))
  );