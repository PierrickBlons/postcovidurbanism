open Styles;

let visibleToDisplay = visible => visible ? "block" : "none";
let isEmpty = content => content !== "";

[@react.component]
let make =
    (~isVisible: bool, ~label: string, ~description: string, ~authorName) => {

  let hasAuthor = authorName->isEmpty;

  <div className=Styling.tooltipStyle(isVisible)>
      <h3 className=Styling.noMargin>
         {React.string(label)} </h3>
      <h4 className=Styling.title4(hasAuthor)>
        {React.string("Par: ")}
        <a href="">{React.string(authorName)}</a> 
      </h4>
      <p> {React.string(description)} </p>
    </div>;
};