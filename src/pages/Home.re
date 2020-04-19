let initialViewState: DeckGl.viewport = {
  longitude: 1.091269,
  latitude: 49.443268,
  zoom: 13,
  pitch: 0,
  bearing: 0,
};

let layerLineId = "layer-id";
let lineColor: (int, int, int, int) = (36, 142, 128, 255);
let lineWidth: int = 7;

type state = {
  label: string,
  visible: bool,
  description: string,
};

type action =
  | Click(DeckGl.Layers.Line.info);

let initialState = {label: "Titre de la Proposition", description: "Description de la proposition", visible: true};

let visibleToDisplay = visible => visible ? "block" : "none";

[@react.component]
let make = () => {
  let (proposals, _) = Queries.useProposalsListQuery();

  let (state, dispatch) =
    React.useReducer(
      (_, action) =>
        switch (action) {
        | Click(info) => {label: info.detail.label, description: info.detail.description, visible: true}
        },
      initialState,
    );

  let renderTooltip = () => {
    <div
      style={ReactDOMRe.Style.make(
        ~display=state.visible->visibleToDisplay,
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
      <h3 style={ReactDOMRe.Style.make(~margin="0",())}>{React.string(state.label)}</h3>
      <p>{React.string(state.description)}</p>
    </div>;
  };

  let data =
    switch (proposals) {
    | Data(data) =>
      data##proposal
      ->Belt.Array.map(proposal => {
          switch (proposal##startLatitude, proposal##startLongitude, proposal##endLatitude, proposal##endLongitude) {
          | (Some(startLatitude), Some(startLongitude), Some(endLatitude), Some(endLongitude)) =>
            {
              DeckGl.Layers.Line.label: proposal##title,
              DeckGl.Layers.Line.description: proposal##description->Belt.Option.getWithDefault(""),
              DeckGl.Layers.Line.sourcePosition: (
                Js.Json.decodeNumber(startLongitude)
                ->Belt.Option.getWithDefault(0.),
                Js.Json.decodeNumber(startLatitude)
                ->Belt.Option.getWithDefault(0.),
              ),
              DeckGl.Layers.Line.targetPosition: (
                Js.Json.decodeNumber(endLongitude)
                ->Belt.Option.getWithDefault(0.),
                Js.Json.decodeNumber(endLatitude)
                ->Belt.Option.getWithDefault(0.),
              ),
            };
          | _ => {label: "", description: "", sourcePosition: (0., 0.), targetPosition: (0., 0.)}
          }
        })
    | _ => [||]
    };

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
