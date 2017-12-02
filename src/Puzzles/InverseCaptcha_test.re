open Jest;

test(
  "1122 small step",
  (_) => Expect.(expect(InverseCaptcha.execute(~bigStep=false, "1122")) |> toBe("3"))
);

test(
  "1111 small step",
  (_) => Expect.(expect(InverseCaptcha.execute(~bigStep=false, "1111")) |> toBe("4"))
);

test(
  "1234 small step",
  (_) => Expect.(expect(InverseCaptcha.execute(~bigStep=false, "1234")) |> toBe("0"))
);

test(
  "91212129 small step",
  (_) => Expect.(expect(InverseCaptcha.execute(~bigStep=false, "91212129")) |> toBe("9"))
);

test(
  "1212 big step",
  (_) => Expect.(expect(InverseCaptcha.execute(~bigStep=true, "1212")) |> toBe("6"))
);

test(
  "1221 big step",
  (_) => Expect.(expect(InverseCaptcha.execute(~bigStep=true, "1221")) |> toBe("0"))
);

test(
  "123425 big step",
  (_) => Expect.(expect(InverseCaptcha.execute(~bigStep=true, "123425")) |> toBe("4"))
);

test(
  "123123 big step",
  (_) => Expect.(expect(InverseCaptcha.execute(~bigStep=true, "123123")) |> toBe("12"))
);

test(
  "12131415 big step",
  (_) => Expect.(expect(InverseCaptcha.execute(~bigStep=true, "12131415")) |> toBe("4"))
);