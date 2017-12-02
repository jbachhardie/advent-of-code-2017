[%bs.raw {|require('./app.css')|}];

[@bs.module] external logo : string = "./logo.svg";

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
  Hashtbl.add(table, "InverseCaptcha", InverseCaptcha.execute(~bigStep=false));
  Hashtbl.add(table, "InverseCaptcha2", InverseCaptcha.execute(~bigStep=true));
  table
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
      let output = switch (Hashtbl.find(puzzleFnTable, state.selectedPuzzle)) {
      | fn => fn(state.input)
      | exception Not_found => "ERROR: Function not found!"
      };
      ReasonReact.Update({...state, output})
    },
  render: (self) =>
    <div className="App">
      <div className="App-header">
        <img src=logo className="App-logo" alt="logo" />
        <h2> (ReasonReact.stringToElement(message)) </h2>
      </div>
      <p className="App-intro">
        <form onSubmit=(self.reduce((event) => {ReactEventRe.Form.preventDefault(event); Submit}))>
          <label>
            <h3> (ReasonReact.stringToElement("Select Algorithm")) </h3>
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
            </select>
          </label>
          <label>
            <h3> (ReasonReact.stringToElement("Input")) </h3>
            <input
              _type="text"
              value=self.state.input
              onChange=(
                self.reduce(
                  (event) =>
                    InputChange(ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value)
                )
              )
            />
          </label>
        </form>
        <h3> (ReasonReact.stringToElement("Output")) </h3>
        <p> (ReasonReact.stringToElement(self.state.output)) </p>
      </p>
    </div>
};