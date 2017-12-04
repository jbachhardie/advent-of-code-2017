[%bs.raw {|require('../Styles/App.css')|}];

[@bs.module] external logo : string = "../Assets/Logo.svg";

type action =
  | Selection(string)
  | InputChange(string)
  | Submit;

type state = {
  selectedPuzzle: string,
  input: string,
  output: string
};

let puzzleFnTable = {
  let table = Hashtbl.create(50);
  Hashtbl.add(table, "InverseCaptcha", InverseCaptcha.calculate(~bigStep=false));
  Hashtbl.add(table, "InverseCaptcha2", InverseCaptcha.calculate(~bigStep=true));
  Hashtbl.add(table, "Spreadsheet", Spreadsheet.run(Spreadsheet.differenceBetweenMaxAndMin));
  Hashtbl.add(table, "SpreadsheetDivision", Spreadsheet.run(Spreadsheet.wholeDivisionOrZero));
  Hashtbl.add(table, "SpiralManhattan", Spiral.run(Spiral.manhattanDistance));
  table;
};

let component = ReasonReact.reducerComponent("App");

let make = (~message, _children) => {
  ...component,
  initialState: () => {selectedPuzzle: "InverseCaptcha", input: "", output: ""},
  reducer: (action, state) =>
    switch action {
    | Selection(selectedPuzzle) => ReasonReact.Update({...state, selectedPuzzle})
    | InputChange(input) => ReasonReact.Update({...state, input})
    | Submit =>
      let output =
        switch (Hashtbl.find(puzzleFnTable, state.selectedPuzzle)) {
        | fn => fn(state.input)
        | exception Not_found => "ERROR: Function not found!"
        };
      ReasonReact.Update({...state, output});
    },
  render: (self) =>
    <div className="App">
      <div className="App-header">
        <img src=logo className="App-logo" alt="logo" />
        <h2> (ReasonReact.stringToElement(message)) </h2>
      </div>
      <form
        className="App-intro"
        onSubmit=(
          self.reduce(
            (event) => {
              ReactEventRe.Form.preventDefault(event);
              Submit;
            }
          )
        )>
        <label>
          (ReasonReact.stringToElement("Puzzle: "))
          <select
            value=self.state.selectedPuzzle
            onChange=(
              self.reduce(
                (event) =>
                  Selection(ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value)
              )
            )>
            <option value="InverseCaptcha">
              (ReasonReact.stringToElement("1.1 Inverse Captcha"))
            </option>
            <option value="InverseCaptcha2">
              (ReasonReact.stringToElement("1.2 Inverse Captcha big Step"))
            </option>
            <option value="Spreadsheet">
              (ReasonReact.stringToElement("2.1 Spreadsheet Checksum"))
            </option>
            <option value="SpreadsheetDivision">
              (ReasonReact.stringToElement("2.2 Spreadsheet Whole Division Checksum"))
            </option>
            <option value="SpiralManhattan">
              (ReasonReact.stringToElement("3.1 Spiral Manhattan Distance"))
            </option>
          </select>
        </label>
        <br />
        <label>
          (ReasonReact.stringToElement("Input: "))
          <textarea
            rows=20
            cols=120
            value=self.state.input
            onChange=(
              self.reduce(
                (event) =>
                  InputChange(ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value)
              )
            )
          />
        </label>
        <br />
        <input _type="submit" value="Go!" />
        <h3> (ReasonReact.stringToElement("Output")) </h3>
        <p> (ReasonReact.stringToElement(self.state.output)) </p>
      </form>
    </div>
};