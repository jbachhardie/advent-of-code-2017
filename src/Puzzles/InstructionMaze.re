let run = (transform, input) => {
  let stepCount = ref(0);
  try {
    let instructionSet =
      input
      |> Js.String.split("\n")
      |> Array.map((char) => char |> Js.String.trim |> int_of_string);
    let i = ref(0);
    while (true) {
      let i' = i^ + instructionSet[i^];
      instructionSet[i^] = transform(instructionSet[i^]);
      i := i';
      stepCount := stepCount^ + 1;
    };
    "ERROR: Unexpected termination";
  } {
  | Failure("int_of_string") => "ERROR: Invalid input"
  | Invalid_argument("index out of bounds") => Js.Int.toString(stepCount^)
  };
};