[@react.component]
let make = () => {
  let route = Routing.getRouteFromUrl(ReasonReactRouter.useUrl().path);

  switch (route) {
  | Home =>
    <div> 
      <header> {React.string("My future menu")} </header> 
      <Home /> 
    </div>
  | _ => React.string("Not found")
  };
};