type route =
  | Home
  | NotFound;

let getRoutePath = route => {
  Js.log(route);
  switch (route) {
  | Home => "/"
  | NotFound => "/404"
  };
}

let getRouteFromUrl = url => {
  Js.log(url);
  switch (url) {
  | [] => Home
  | _ => NotFound
  };
}

let push = route => ReasonReactRouter.push(getRoutePath(route));