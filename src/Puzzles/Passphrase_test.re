open Jest;

testAll(
  "isUnique",
  [("aa bb cc dd ee", true), ("aa bb cc dd aa", false), ("aa bb cc dd aaa", true)],
  ((input, expected)) =>
    Expect.(expect(Passphrase.validate(Passphrase.isUnique, input)) |> toBe(expected))
);

testAll(
  "isNonAnagram",
  [
    ("abcde fghij", true),
    ("abcde xyz ecdab", false),
    ("a ab abc abd abf abj", true),
    ("iiii oiii ooii oooi oooo", true),
    ("oiii ioii iioi iiio", false)
  ],
  ((input, expected)) =>
    Expect.(expect(Passphrase.validate(Passphrase.isNonAnagram, input)) |> toBe(expected))
);