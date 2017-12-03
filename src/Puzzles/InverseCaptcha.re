let char_to_int = (c: char) => {
  let number = Char.code(c) - 48;
  if (number < 0 || number > 9) {
    raise(Failure("char_to_int"))
  } else {
    number
  }
};

let string_to_int_list = (s) => {
  let rec reduce = (i, acc) => i < 0 ? acc : reduce(i - 1, [char_to_int(s.[i]), ...acc]);
  reduce(String.length(s) - 1, [])
};

let circular_matching_sum = (l, step) => {
  let rec circular_index_to_linear = (i) => i < 0 ? circular_index_to_linear(List.length(l) + i) : i;  
  let get_prev = (i) => List.nth(l, circular_index_to_linear(i - step));
  let sum = ref(0);
  List.iteri((i, current) => current == get_prev(i) ? sum := sum^ + current : (),l);
  sum^
};

let calculate = (~bigStep=false, input: string) => {
  let step = bigStep ? String.length(input) / 2 : 1;
  switch (string_to_int_list(input)) {
  | integer_list => circular_matching_sum(integer_list, step) |> Js.Int.toString
  | exception (Failure("char_to_int")) => "ERROR: Invalid input"
  }
};