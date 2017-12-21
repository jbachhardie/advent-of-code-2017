let balance = (input) => {
  let rec reduce = (pastStates, state) =>
    if (List.mem(state, pastStates)) {
      List.length(pastStates);
    } else {
      let newState = Array.copy(state);
      /* TODO: index logic is broken */
      let (initialBlocks, initialIndex) =
        Array.fold_left(
          ((blocks, index), bank) => bank > blocks ? (bank, index + 1) : (blocks, index + 1),
          (0, 0),
          state
        );
      Js.log(initialIndex);
      newState[initialIndex] = 0;
      let i = ref(initialIndex + 1);
      Js.log(i^);
      for (_ in 0 to initialBlocks) {
        if (i^ == Array.length(state)) { i := 0 };
        newState[i^] = newState[i^] + 1;
        i := i^ + 1;
      };
      reduce([state, ...pastStates], newState)
    };
  reduce([], input);
};

let run = (fn, input) =>
  switch (
    input |> String.trim |> Js.String.splitByRe([%re "/[\t ]+/"]) |> Array.map(int_of_string)
  ) {
  | array => array |> fn |> Js.Int.toString
  | exception (Failure("int_of_string")) => "ERROR: Invalid input"
  };