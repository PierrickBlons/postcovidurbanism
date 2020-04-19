[@react.component]
let make = () => {
  let route = Routing.getRouteFromUrl(ReasonReactRouter.useUrl().path);
  switch (route) {
  | Home => <Home />
  | _ => React.string("Not found")
  };
};