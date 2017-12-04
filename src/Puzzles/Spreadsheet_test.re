open Jest;

test(
  "difference between max and min checksum",
  (_) =>
    Expect.(
      expect(Spreadsheet.run(Spreadsheet.differenceBetweenMaxAndMin, {|5 1 9 5
7 5 3
2 4 6 8|}))
      |> toBe("18")
    )
);

test(
  "whole division checksum",
  (_) =>
    Expect.(
      expect(Spreadsheet.run(Spreadsheet.wholeDivisionOrZero, {|5 9 2 8
9 4 7 3
3 8 6 5|}))
      |> toBe("9")
    )
);

test(
  "find divisions",
  () => Expect.(expect(Spreadsheet.wholeDivisionOrZero([|5, 9, 2, 8|])) |> toBe(4))
);

test(
  "parse_tsv",
  (_) =>
    Expect.(
      expect(Spreadsheet.parseTSV({|5 1 9 5
7 5 3
2 4 6 8|}))
      |> toEqual([|[|5, 1, 9, 5|], [|7, 5, 3|], [|2, 4, 6, 8|]|])
    )
);