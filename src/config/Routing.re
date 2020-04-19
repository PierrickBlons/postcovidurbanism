type route =
  | Home
  | NotFound;

let getRoutePath = route =>
  switch (route) {
  | Home => "/"
  | NotFound => "/404"
  };

let getRouteFromUrl = url =>
  switch (url) {
  | [route] when route === Env.app_path => Home
  | _ => NotFound
  };

let push = route => ReasonReactRouter.push(getRoutePath(route));