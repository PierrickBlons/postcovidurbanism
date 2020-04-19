let initialViewState: DeckGl.viewport = {
  longitude: 1.091269,
  latitude: 49.443268,
  zoom: 13,
  pitch: 0,
  bearing: 0,
};

let layerLineId = "layer-id";
let lineColor: (int, int, int) = (255, 0, 0);
let lineWidth: int = 3;

type state = {
  label: string,
  posX: int,
  posY: int,
  visible: bool,
};

type action =
  | Click(DeckGl.Layers.Line.info);

let initialState = {label: "default", posX: 0, posY: 0, visible: false};

let visibleToDisplay = visible => visible ? "block" : "none";

[@react.component]
let make = () => {
  let (proposals, _) = Queries.useProposalsListQuery();

  let (state, dispatch) =
    React.useReducer(
      (_, action) =>
        switch (action) {
        | Click(info) => {label: info._object.label, posX: info.x, posY: info.y, visible: true}
        },
      initialState,
    );

  let renderTooltip = () => {
    <div
      style={ReactDOMRe.Style.make(
        ~display=state.visible->visibleToDisplay,
        ~position="absolute",
        ~top=state.posY->string_of_int ++ "px",
        ~left=state.posX->string_of_int ++ "px",
        (),
      )}>
      {React.string(state.label)}
    </div>;
  };

  let data =
    switch (proposals) {
    | Data(data) =>
      data##proposal
      ->Belt.Array.map(proposal => {
          switch (proposal##latitude, proposal##longitude) {
          | (Some(latitude), Some(longitude)) =>
            Js.log2(latitude, longitude);
            {
              DeckGl.Layers.Line.label: proposal##title,
              DeckGl.Layers.Line.sourcePosition: (
                Js.Json.decodeNumber(longitude)
                ->Belt.Option.getWithDefault(0.),
                Js.Json.decodeNumber(latitude)
                ->Belt.Option.getWithDefault(0.),
              ),
              DeckGl.Layers.Line.targetPosition: (0., 0.),
            };
          | _ => {label: "", sourcePosition: (0., 0.), targetPosition: (0., 0.)}
          }
        })
    | _ => [||]
    };

  Js.log(data);

  let layers = [|
    DeckGl.Layers.Line.create({
      id: layerLineId,
      data,
      getColor: lineColor,
      getWidth: lineWidth,
      onClick: info => dispatch(Click(info)),
      pickable: true,
    }),
  |];

  <DeckGl reuseMaps=true initialViewState layers controller=true>
    <DeckGl.StaticMap
      viewState=initialViewState
      mapStyle="mapbox://styles/mapbox/dark-v10"
      mapboxApiAccessToken=Env.mapbox_token_api
    />
    {renderTooltip()}
  </DeckGl>;
};
