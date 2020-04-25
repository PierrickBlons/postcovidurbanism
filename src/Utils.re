let resultToOption =
  fun
  | Belt.Result.Ok(value) => Some(value)
  | Belt.Result.Error(error) => {
      Js.log(error);
      None;
    };
