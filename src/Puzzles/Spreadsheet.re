let parseTSV = (tsv) =>
  Js.String.split("\n", tsv)
  |> Array.map(
       (row) =>
         String.trim(row)
         |> Js.String.splitByRe([%re "/[\t ]+/"])
         |> Array.map((number) => Int32.of_string(number) |> Int32.to_int)
     );

let differenceBetweenMaxAndMin = (row) => {
  Array.sort(Pervasives.compare, row);
  row[Array.length(row) - 1] - row[0];
};

let findDivisor = (dividendIndex, row) => {
  let result = ref(None);
  let dividend = row[dividendIndex];
  let i = ref(0);
  while (result^ == None && i^ < Array.length(row)) {
    let divisorCandidate = row[i^];
    if (i^ != dividendIndex && dividend mod divisorCandidate == 0) {
      result := Some(divisorCandidate);
    } else {
      i := i^ + 1;
    };
  };
  result^;
};

let findWholeDivision = (row) => {
  let result = ref(None);
  let i = ref(0);
  while (result^ == None && i^ < Array.length(row)) {
    switch (findDivisor(i^, row)) {
    | Some(divisor) => result := Some(row[i^] / divisor)
    | None => i := i^ + 1
    };
  };
  result^;
};

let wholeDivisionOrZero = (row) =>
  switch (findWholeDivision(row)) {
  | Some(result) => result
  | None => 0
  };

let checksum = (fn, array) => Array.fold_left((acc, row) => acc + fn(row), 0, array);

let run = (fn, input) =>
  switch (parseTSV(input)) {
  | array => checksum(fn, array) |> Js.Int.toString
  | exception (Failure("int_of_string")) => "ERROR: Invalid input"
  };