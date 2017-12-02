let char_to_int = (c: char) => {
  let number = Char.code(c) - 48;
  if (number < 0 || number > 9) {
    raise(Failure("char_to_int"))
  } else {
    number
  }
};

let execute = (~bigStep=false, input: string) => {
  let length = String.length(input);
  let step = bigStep ? length / 2 : 1;
  let rec circular_index_to_linear = (i) => i < 0 ? circular_index_to_linear(length + i) : i;
  let rec sum_if_matches = (i, sum) =>
    if (i < length) {
      let prevIndex = circular_index_to_linear(i - step);
      let current = input.[i] |> char_to_int;
      let prev = input.[prevIndex] |> char_to_int;
      sum_if_matches(i + 1, current == prev ? sum + current : sum)
    } else {
      sum
    };
  switch (sum_if_matches(0, 0)) {
  | value => Js.Int.toString(value)
  | exception (Failure("char_to_int")) => "ERROR: Invalid input"
  }
};