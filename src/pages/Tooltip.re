let visibleToDisplay = visible => visible ? "block" : "none";

[@react.component]
let make = (~isVisible: bool, ~label: string, ~description: string) => { 
    <div
      style={ReactDOMRe.Style.make(
        ~display=isVisible->visibleToDisplay,
        ~backgroundColor="#aaa",
        ~position="absolute",
        ~top="20px",
        ~left="20px",
        ~width="300px",
        ~height="150px",
        ~borderRadius="10px",
        ~padding="5px",
        ~color="#fff",
        ~fontFamily="Source Sans Pro, sans-serif",
        (),
      )}>
      <h3 style={ReactDOMRe.Style.make(~margin="0", ())}>
        {React.string(label)}
      </h3>
      <p> {React.string(description)} </p>
    </div>
};