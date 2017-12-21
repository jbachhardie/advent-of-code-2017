open Jest;

test("balance", () => Expect.(expect(MemoryManagement.run(MemoryManagement.balance, "0 2 7 0")) |> toBe("5")))