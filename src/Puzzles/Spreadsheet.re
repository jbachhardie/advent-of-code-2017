let parse_tsv = (tsv) =>
  Js.String.split("\n", tsv)
  |> Array.map(
       (row) =>
         String.trim(row)
         |> Js.String.splitByRe([%re "/[\t ]+/"])
         |> Array.map((number) => Int32.of_string(number) |> Int32.to_int));

let row_check_diff = (row) => {
    Array.sort(Pervasives.compare, row);
    row[Array.length(row) - 1] - row[0]
};

let checksum = (array) => 
    Array.fold_left((acc, row) => acc + row_check_diff(row), 0, array);

let calculate = (input) =>
  switch (parse_tsv(input)) {
  | array => checksum(array) |> Js.Int.toString
  | exception (Failure("int_of_string")) => "ERROR: Invalid input"
  };