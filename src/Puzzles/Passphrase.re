let anagramHash = (word) =>
  word
  |> Js.String.split("")
  |> Array.to_list
  |> List.sort(compare)
  |> List.fold_left(Js.String.concat, "");

let isNonAnagram = (sut, rest) =>
  List.for_all((word) => anagramHash(word) != anagramHash(sut), rest);

let isUnique = (sut, rest) => ! List.mem(sut, rest);

let validate = (validator, phrase) => {
  let rec reduce = (acc, wordList) =>
    switch (acc, wordList) {
    | (false, _) => false
    | (true, [sut, ...rest]) => reduce(validator(sut, rest), rest)
    | (true, []) => true
    };
  phrase |> Js.String.split(" ") |> Array.to_list |> reduce(true);
};

let run = (validator, input) => {
  let phraseSet = Js.String.split("\n", input);
  Array.fold_left((acc, phrase) => validate(validator, phrase) ? acc + 1 : acc, 0, phraseSet)
  |> string_of_int;
};