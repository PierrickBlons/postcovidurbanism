module Styling = {
  open Css;

  let tooltipStyle = isVisible =>
    style([
      display(isVisible ? block : none),
      position(absolute),
      top(px(20)),
      left(px(20)),
      width(px(300)),
      padding(px(5)),
      borderRadius(px(5)),
      backgroundColor(rgb(170, 170, 170)),
      color(rgb(255, 255, 255)),
    ]);

  let noMargin = style([margin(px(0))]);

  let title4 = isVisible =>
    Css.merge([
      noMargin, 
      style([
        display(isVisible ? block : none),
        fontStyle(italic), 
        fontWeight(lighter)
      ]
    )]);
};

Css.(
  global("body", [
    fontFamily(`custom("Noto Sans")),
    fontSize(em(0.8))
  ])
);