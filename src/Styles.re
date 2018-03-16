open Css;

global("html, body", [
  margin(px(0)),
  padding(px(0))
]);

let root = fetching =>
  style([
    padding(px(50)),
    fontSize(px(16)),
    opacity(fetching ? 0.5 : 1.0),
    selector("& a", [
      textDecoration(none),
      borderBottomWidth(px(1)),
      borderBottomStyle(solid)
    ])
  ]);

let error = style([
  color(red),
  selector("& button", [
    marginLeft(px(10))
  ])
]);

let line = style([
  selector("& > * + *", [
    marginLeft(px(10))
  ])
]);
