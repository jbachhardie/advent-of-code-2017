[%bs.raw {|require('./Styles/index.css')|}];

[@bs.module "./registerServiceWorker"] external register_service_worker : unit => unit = "default";

ReactDOMRe.renderToElementWithId(<App message="Advent of Code 2017!" />, "root");

register_service_worker();
