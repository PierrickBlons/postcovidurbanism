let visibleToDisplay = visible => visible ? "block" : "none";
let isEmpty = content => content !== "";

[@react.component]
let make = (~isVisible: bool, ~label: string, ~description: string, ~authorName) => { 
    <div
      style={ReactDOMRe.Style.make(
        ~display=isVisible->visibleToDisplay,
        ~backgroundColor="#aaa",
        ~position="absolute",
        ~top="20px",
        ~left="20px",
        ~width="300px",
        ~borderRadius="10px",
        ~padding="5px",
        ~color="#fff",
        ~fontFamily="Source Sans Pro, sans-serif",
        (),
      )}>
      <h3 style={ReactDOMRe.Style.make(~margin="0", ())}>
        {React.string(label)}
      </h3>
      <h4 style={ReactDOMRe.Style.make(~display=(authorName->isEmpty->visibleToDisplay), ())}>{React.string("Par: " ++ authorName)}</h4>
      <p> {React.string(description)} </p>
    </div>
};